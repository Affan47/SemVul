#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_components.py - Find exactly where the model loses information

Tests each component separately:
1. Input projection
2. GNN layers (message passing)
3. Readout/Pooling (DevignConvHead)
4. Classifier

For each: Does input variance → output variance?
"""

import argparse
import json
import sys
import random
import io
import zipfile
from pathlib import Path
from collections import defaultdict

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, GATConv, global_mean_pool, global_max_pool

sys.path.insert(0, str(Path(__file__).parent))


def load_samples(cache_dir, dataset_name, cache_sig, split="train", num_samples=50):
    """Load sample data."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            random.shuffle(pt_files)
            
            for pt_name in pt_files[:num_samples * 2]:
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                        if len(samples) >= num_samples:
                            break
                except:
                    continue
    
    return samples


def stats(tensor, name=""):
    """Get tensor statistics."""
    if tensor is None or tensor.numel() == 0:
        return f"{name}: None/Empty"
    
    t = tensor.float()
    return (f"{name}: shape={list(t.shape)}, "
            f"mean={t.mean().item():.4f}, std={t.std().item():.4f}, "
            f"min={t.min().item():.4f}, max={t.max().item():.4f}")


class DiagnosticModel(nn.Module):
    """Model with hooks to inspect each component."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3, dropout=0.2):
        super().__init__()
        
        self.input_dim = input_dim
        self.hidden_dim = hidden_dim
        
        # Component 1: Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
        )
        
        # Component 2: GNN layers
        self.convs = nn.ModuleList()
        self.norms = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
            self.norms.append(nn.LayerNorm(hidden_dim))
        
        self.dropout = nn.Dropout(dropout)
        
        # Component 3: Simple pooling (NOT DevignConvHead)
        # We'll test different pooling methods
        
        # Component 4: Classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        # Storage for diagnostics
        self.diagnostics = {}
    
    def forward(self, data, pooling='mean', verbose=False):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # === COMPONENT 1: Input Projection ===
        self.diagnostics['input'] = {
            'mean': x.mean().item(),
            'std': x.std().item(),
            'per_sample_std': [],  # Will compute per-graph variance
        }
        
        h = self.input_proj(x)
        
        self.diagnostics['after_proj'] = {
            'mean': h.mean().item(),
            'std': h.std().item(),
        }
        
        if verbose:
            print(f"  Input: mean={x.mean():.4f}, std={x.std():.4f}")
            print(f"  After proj: mean={h.mean():.4f}, std={h.std():.4f}")
        
        h0 = h.clone()  # Save for skip connection
        
        # === COMPONENT 2: GNN Layers ===
        for i, (conv, norm) in enumerate(zip(self.convs, self.norms)):
            h_prev = h.clone()
            h = conv(h, edge_index)
            h = norm(h)
            h = F.relu(h)
            h = self.dropout(h)
            h = h + h_prev  # Residual
            
            self.diagnostics[f'after_conv_{i}'] = {
                'mean': h.mean().item(),
                'std': h.std().item(),
            }
            
            if verbose:
                print(f"  After conv {i}: mean={h.mean():.4f}, std={h.std():.4f}")
        
        # === COMPONENT 3: Pooling ===
        num_graphs = int(batch.max().item()) + 1
        
        if pooling == 'mean':
            graph_emb = global_mean_pool(h, batch)
        elif pooling == 'max':
            graph_emb = global_max_pool(h, batch)
        elif pooling == 'sum':
            from torch_geometric.nn import global_add_pool
            graph_emb = global_add_pool(h, batch)
        elif pooling == 'mean_max':
            graph_emb = torch.cat([
                global_mean_pool(h, batch),
                global_max_pool(h, batch)
            ], dim=1)
            # Need to project back to hidden_dim
            if not hasattr(self, 'pool_proj'):
                self.pool_proj = nn.Linear(self.hidden_dim * 2, self.hidden_dim).to(h.device)
            graph_emb = self.pool_proj(graph_emb)
        
        self.diagnostics['after_pool'] = {
            'mean': graph_emb.mean().item(),
            'std': graph_emb.std().item(),
            'per_graph_variance': graph_emb.var(dim=0).mean().item(),  # Variance across graphs
        }
        
        if verbose:
            print(f"  After pool ({pooling}): mean={graph_emb.mean():.4f}, std={graph_emb.std():.4f}")
            print(f"  Per-graph variance: {graph_emb.var(dim=0).mean():.6f}")
        
        # === COMPONENT 4: Classifier ===
        logits = self.classifier(graph_emb)
        probs = torch.sigmoid(logits)
        
        self.diagnostics['predictions'] = {
            'logit_mean': logits.mean().item(),
            'logit_std': logits.std().item(),
            'prob_mean': probs.mean().item(),
            'prob_std': probs.std().item(),
        }
        
        if verbose:
            print(f"  Logits: mean={logits.mean():.4f}, std={logits.std():.4f}")
            print(f"  Probs: mean={probs.mean():.4f}, std={probs.std():.4f}")
        
        return logits, probs


def test_pooling_methods(model, batch, device):
    """Test different pooling methods."""
    print("\n" + "=" * 60)
    print("TEST: Pooling Method Comparison")
    print("=" * 60)
    
    model.eval()
    with torch.no_grad():
        for pooling in ['mean', 'max', 'sum']:
            print(f"\n--- {pooling.upper()} pooling ---")
            logits, probs = model(batch, pooling=pooling, verbose=True)
            
            print(f"  Prediction range: [{probs.min():.4f}, {probs.max():.4f}]")
            print(f"  Prediction std: {probs.std():.6f}")


def test_with_random_features(model, batch, device):
    """Test if model can distinguish random features."""
    print("\n" + "=" * 60)
    print("TEST: Random Features (Sanity Check)")
    print("=" * 60)
    
    model.eval()
    
    # Create batch with random features
    batch_random = batch.clone()
    batch_random.x = torch.randn_like(batch.x)
    
    with torch.no_grad():
        logits_real, probs_real = model(batch, pooling='mean')
        logits_rand, probs_rand = model(batch_random, pooling='mean')
    
    print(f"Real features - prob std: {probs_real.std():.6f}")
    print(f"Random features - prob std: {probs_rand.std():.6f}")
    
    if probs_rand.std() > probs_real.std() * 2:
        print("⚠️ Random features produce MORE variance than real features!")
        print("   This suggests real features may be too similar to each other.")


def test_per_graph_features(samples, device):
    """Check if different graphs have different features."""
    print("\n" + "=" * 60)
    print("TEST: Per-Graph Feature Analysis")
    print("=" * 60)
    
    graph_means = []
    graph_stds = []
    
    for data in samples[:20]:
        x = data.x.float()
        graph_means.append(x.mean().item())
        graph_stds.append(x.std().item())
    
    print(f"Feature mean across graphs: {np.mean(graph_means):.4f} ± {np.std(graph_means):.4f}")
    print(f"Feature std across graphs: {np.mean(graph_stds):.4f} ± {np.std(graph_stds):.4f}")
    
    if np.std(graph_means) < 0.01:
        print("🚨 All graphs have nearly identical mean features!")
        print("   This could cause collapse.")


def test_message_passing_effect(model, batch, device):
    """Check if message passing changes representations."""
    print("\n" + "=" * 60)
    print("TEST: Message Passing Effect")
    print("=" * 60)
    
    model.eval()
    
    x = batch.x.float().to(device)
    edge_index = batch.edge_index.to(device)
    
    # Get representations before and after each layer
    h = model.input_proj(x)
    print(f"After input proj: std={h.std():.4f}")
    
    for i, (conv, norm) in enumerate(zip(model.convs, model.norms)):
        h_before = h.clone()
        h = conv(h, edge_index)
        h = norm(h)
        h = F.relu(h)
        
        # Check how much the representation changed
        change = (h - h_before).norm() / h_before.norm()
        cosine_sim = F.cosine_similarity(h.flatten().unsqueeze(0), 
                                          h_before.flatten().unsqueeze(0)).item()
        
        print(f"Layer {i}: relative change={change:.4f}, cosine_sim={cosine_sim:.4f}, std={h.std():.4f}")
        
        h = h + h_before  # Residual (as in original)
    
    if cosine_sim > 0.99:
        print("⚠️ Message passing barely changes representations!")
        print("   GNN layers may not be learning useful patterns.")


def test_gradient_flow(model, batch, device):
    """Test gradient flow through each component."""
    print("\n" + "=" * 60)
    print("TEST: Gradient Flow")
    print("=" * 60)
    
    model.train()
    model.zero_grad()
    
    logits, _ = model(batch, pooling='mean')
    y = batch.y.float().view(-1)
    
    loss = F.binary_cross_entropy_with_logits(logits.view(-1), y)
    loss.backward()
    
    # Check gradients at each layer
    components = [
        ('input_proj', model.input_proj),
        ('convs', model.convs),
        ('classifier', model.classifier),
    ]
    
    for name, module in components:
        grads = []
        for param in module.parameters():
            if param.grad is not None:
                grads.append(param.grad.norm().item())
        
        if grads:
            print(f"{name}: grad_norm mean={np.mean(grads):.2e}, max={np.max(grads):.2e}")
            if np.mean(grads) < 1e-6:
                print(f"  🚨 Very small gradients in {name}!")


def test_overfit_single_batch(model, batch, device, steps=100, lr=0.01):
    """Test if model can overfit on a single batch."""
    print("\n" + "=" * 60)
    print("TEST: Overfit Single Batch")
    print("=" * 60)
    
    model.train()
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    
    y = batch.y.float().view(-1)
    
    for step in range(steps):
        optimizer.zero_grad()
        logits, probs = model(batch, pooling='mean')
        loss = F.binary_cross_entropy_with_logits(logits.view(-1), y)
        loss.backward()
        optimizer.step()
        
        if step % 20 == 0 or step == steps - 1:
            acc = ((probs.view(-1) > 0.5) == y).float().mean().item()
            print(f"Step {step:3d}: loss={loss.item():.4f}, acc={acc:.2%}, prob_std={probs.std():.4f}")


def test_devign_conv_head(samples, hidden_dim, device):
    """Test the DevignConvHead specifically."""
    print("\n" + "=" * 60)
    print("TEST: DevignConvHead Analysis")
    print("=" * 60)
    
    # Import or recreate DevignConvHead
    class DevignConvHead(nn.Module):
        def __init__(self, hidden_dim, dropout=0.2):
            super().__init__()
            self.hidden_dim = hidden_dim
            self.conv1 = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=3, padding=1)
            self.conv2 = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
            self.norm = nn.LayerNorm(hidden_dim)
            self.dropout = nn.Dropout(dropout)
        
        def forward(self, h_input, h_final, batch):
            h = h_input + h_final
            num_graphs = int(batch.max().item()) + 1
            graph_embs = []
            
            for g in range(num_graphs):
                mask = (batch == g)
                h_g = h[mask]
                
                if h_g.size(0) == 0:
                    graph_embs.append(torch.zeros(self.hidden_dim, device=h.device))
                    continue
                
                h_g = h_g.t().unsqueeze(0)
                h_g = F.relu(self.conv1(h_g))
                h_g = self.conv2(h_g)
                h_g = h_g.max(dim=2)[0].squeeze(0)
                graph_embs.append(h_g)
            
            graph_emb = torch.stack(graph_embs, dim=0)
            graph_emb = self.norm(graph_emb)
            return graph_emb
    
    # Create head and test
    head = DevignConvHead(hidden_dim).to(device)
    
    # Create batch
    batch = Batch.from_data_list(samples[:20]).to(device)
    
    # Random node features
    h = torch.randn(batch.x.size(0), hidden_dim, device=device)
    
    out = head(h, h, batch.batch)
    
    print(f"Input h: shape={list(h.shape)}, std={h.std():.4f}")
    print(f"Output: shape={list(out.shape)}, std={out.std():.4f}")
    print(f"Per-graph variance: {out.var(dim=0).mean():.6f}")
    
    # Check if different inputs give different outputs
    h2 = torch.randn_like(h)
    out2 = head(h2, h2, batch.batch)
    
    diff = (out - out2).norm() / out.norm()
    print(f"Different input → output difference: {diff:.4f}")
    
    if diff < 0.1:
        print("🚨 DevignConvHead produces similar outputs for different inputs!")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=3)
    parser.add_argument("--num-samples", type=int, default=50)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 60)
    print("COMPONENT-LEVEL DIAGNOSTICS")
    print("=" * 60)
    
    device = torch.device(args.device)
    
    # Load samples
    samples = load_samples(
        args.cache_dir,
        args.dataset_name,
        args.cache_signature,
        num_samples=args.num_samples,
    )
    
    if not samples:
        print("[ERROR] No samples loaded!")
        sys.exit(1)
    
    print(f"Loaded {len(samples)} samples")
    
    input_dim = samples[0].x.size(1)
    print(f"Input dim: {input_dim}")
    print(f"Hidden dim: {args.hidden_dim}")
    print(f"Num layers: {args.num_layers}")
    
    # Create batch
    batch = Batch.from_data_list(samples).to(device)
    print(f"Batch: {batch.x.size(0)} nodes, {batch.edge_index.size(1)} edges, {batch.num_graphs} graphs")
    
    # Create model
    model = DiagnosticModel(
        input_dim=input_dim,
        hidden_dim=args.hidden_dim,
        num_layers=args.num_layers,
    ).to(device)
    
    print(f"Model parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    # Run tests
    test_per_graph_features(samples, device)
    test_pooling_methods(model, batch, device)
    test_with_random_features(model, batch, device)
    test_message_passing_effect(model, batch, device)
    test_gradient_flow(model, batch, device)
    test_devign_conv_head(samples, args.hidden_dim, device)
    test_overfit_single_batch(model, batch, device, steps=100, lr=0.01)
    
    # Summary
    print("\n" + "=" * 60)
    print("DIAGNOSIS SUMMARY")
    print("=" * 60)
    print("""
Based on the tests above, look for:
1. Per-graph features too similar → Data preprocessing issue
2. Pooling killing variance → Try different pooling
3. Message passing not changing representations → GNN not learning
4. Gradients too small → Learning rate too low
5. DevignConvHead collapsing → Replace with simple pooling
6. Cannot overfit → Fundamental architecture issue
""")


if __name__ == "__main__":
    main()