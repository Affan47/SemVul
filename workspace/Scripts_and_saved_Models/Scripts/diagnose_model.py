#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_model.py - Diagnose why the model is collapsing

Tests:
1. Can the model overfit on a tiny batch? (10 samples)
2. Are gradients flowing through all layers?
3. Is the input projection killing information?
4. What do intermediate activations look like?

Usage:
    python diagnose_model.py \
        --cache-dir "/path/to/cache" \
        --dataset-name "devign_normfunc_v2" \
        --cache-signature "caffd6ae8652870d" \
        --vocab-dir "/path/to/vocab" \
        --model-type rgat
"""

import argparse
import json
import sys
import random
from pathlib import Path
from collections import defaultdict

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data
from torch_geometric.loader import DataLoader

# Add parent directory for imports
sys.path.insert(0, str(Path(__file__).parent))


def load_vocab(vocab_dir: Path) -> int:
    """Load vocabulary and return number of relations."""
    rel_vocab_path = vocab_dir / "devign_rel_vocab.json"
    if rel_vocab_path.exists():
        with open(rel_vocab_path) as f:
            rel_vocab = json.load(f)
        return len(rel_vocab)
    return 5  # Default


def load_sample_batch(
    cache_dir: Path,
    dataset_name: str, 
    cache_sig: str,
    split: str = "train",
    num_samples: int = 20,
) -> list:
    """Load a small sample of data."""
    import zipfile
    import io
    
    split_dir = cache_dir / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            random.shuffle(pt_files)
            
            for pt_name in pt_files[:num_samples * 2]:  # Load extra in case some fail
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        # Ensure we have both labels
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                        if len(samples) >= num_samples:
                            break
                except:
                    continue
    
    return samples


def create_simple_model(input_dim: int, hidden_dim: int = 128) -> nn.Module:
    """Create a minimal model for testing."""
    
    class SimpleGNN(nn.Module):
        def __init__(self, in_dim, hidden_dim):
            super().__init__()
            self.proj = nn.Linear(in_dim, hidden_dim)
            self.conv1 = torch.nn.Linear(hidden_dim, hidden_dim)  # Fake conv for now
            self.conv2 = torch.nn.Linear(hidden_dim, hidden_dim)
            self.classifier = nn.Linear(hidden_dim, 1)
            
        def forward(self, data):
            x = data.x.float()
            
            # Track activations
            self._input_stats = {
                'mean': x.mean().item(),
                'std': x.std().item(),
                'min': x.min().item(),
                'max': x.max().item(),
            }
            
            # Project
            h = self.proj(x)
            h = F.relu(h)
            
            self._proj_stats = {
                'mean': h.mean().item(),
                'std': h.std().item(),
            }
            
            # Simple aggregation (mean per graph)
            h = F.relu(self.conv1(h))
            h = F.relu(self.conv2(h))
            
            # Global mean pooling
            batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long)
            
            # Manual scatter mean
            num_graphs = batch.max().item() + 1
            graph_emb = torch.zeros(num_graphs, h.size(1), device=h.device)
            counts = torch.zeros(num_graphs, device=h.device)
            
            for i in range(h.size(0)):
                graph_emb[batch[i]] += h[i]
                counts[batch[i]] += 1
            
            graph_emb = graph_emb / counts.unsqueeze(1).clamp(min=1)
            
            self._pool_stats = {
                'mean': graph_emb.mean().item(),
                'std': graph_emb.std().item(),
            }
            
            logits = self.classifier(graph_emb)
            return {"logits": logits}
    
    return SimpleGNN(input_dim, hidden_dim)


def test_overfit(model, samples, device, num_steps=200, lr=1e-2):
    """Test if model can overfit on a tiny batch."""
    
    print("\n" + "=" * 60)
    print("TEST 1: Overfitting on tiny batch")
    print("=" * 60)
    
    loader = DataLoader(samples, batch_size=len(samples), shuffle=False)
    batch = next(iter(loader)).to(device)
    
    model.to(device)
    model.train()
    
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    criterion = nn.BCEWithLogitsLoss()
    
    print(f"Batch size: {len(samples)}")
    print(f"Labels: {batch.y.tolist()}")
    print(f"Learning rate: {lr}")
    print()
    
    initial_loss = None
    
    for step in range(num_steps):
        optimizer.zero_grad()
        
        out = model(batch)
        logits = out["logits"].view(-1)
        y = batch.y.float().view(-1)
        
        loss = criterion(logits, y)
        loss.backward()
        
        # Check gradients
        grad_norms = []
        for name, param in model.named_parameters():
            if param.grad is not None:
                grad_norms.append(param.grad.norm().item())
        
        optimizer.step()
        
        probs = torch.sigmoid(logits)
        preds = (probs > 0.5).long()
        acc = (preds == y.long()).float().mean().item()
        
        if step == 0:
            initial_loss = loss.item()
            print(f"Step {step:3d}: Loss={loss.item():.4f} | Acc={acc:.2%} | Probs={probs.detach().cpu().numpy().round(3)}")
            print(f"          Grad norms: min={min(grad_norms):.2e}, max={max(grad_norms):.2e}")
        
        if step % 50 == 0 or step == num_steps - 1:
            print(f"Step {step:3d}: Loss={loss.item():.4f} | Acc={acc:.2%} | Probs={probs.detach().cpu().numpy().round(3)}")
    
    final_loss = loss.item()
    
    print()
    if final_loss < initial_loss * 0.1:
        print("✅ Model CAN overfit (loss decreased >90%)")
        return True
    elif final_loss < initial_loss * 0.5:
        print("⚠️ Model partially learns (loss decreased 50-90%)")
        return True
    else:
        print("🚨 Model CANNOT overfit! Something is fundamentally broken.")
        return False


def analyze_activations(model, samples, device):
    """Analyze activations at each layer."""
    
    print("\n" + "=" * 60)
    print("TEST 2: Activation Analysis")
    print("=" * 60)
    
    loader = DataLoader(samples, batch_size=len(samples), shuffle=False)
    batch = next(iter(loader)).to(device)
    
    model.to(device)
    model.eval()
    
    with torch.no_grad():
        out = model(batch)
    
    if hasattr(model, '_input_stats'):
        print(f"\nInput features:")
        print(f"  Mean: {model._input_stats['mean']:.4f}")
        print(f"  Std:  {model._input_stats['std']:.4f}")
        print(f"  Range: [{model._input_stats['min']:.4f}, {model._input_stats['max']:.4f}]")
    
    if hasattr(model, '_proj_stats'):
        print(f"\nAfter input projection:")
        print(f"  Mean: {model._proj_stats['mean']:.4f}")
        print(f"  Std:  {model._proj_stats['std']:.4f}")
    
    if hasattr(model, '_pool_stats'):
        print(f"\nAfter pooling:")
        print(f"  Mean: {model._pool_stats['mean']:.4f}")
        print(f"  Std:  {model._pool_stats['std']:.4f}")
    
    logits = out["logits"].view(-1)
    probs = torch.sigmoid(logits)
    
    print(f"\nFinal predictions:")
    print(f"  Logits: {logits.cpu().numpy().round(4)}")
    print(f"  Probs:  {probs.cpu().numpy().round(4)}")
    print(f"  Labels: {batch.y.cpu().numpy()}")
    
    # Check for collapse
    prob_std = probs.std().item()
    if prob_std < 0.05:
        print(f"\n🚨 PREDICTION COLLAPSE: std={prob_std:.4f} (all predictions nearly identical)")
    else:
        print(f"\n✅ Predictions have variance: std={prob_std:.4f}")


def analyze_gradients(model, samples, device):
    """Analyze gradient flow."""
    
    print("\n" + "=" * 60)
    print("TEST 3: Gradient Flow Analysis")
    print("=" * 60)
    
    loader = DataLoader(samples, batch_size=len(samples), shuffle=False)
    batch = next(iter(loader)).to(device)
    
    model.to(device)
    model.train()
    
    out = model(batch)
    logits = out["logits"].view(-1)
    y = batch.y.float().view(-1)
    
    loss = F.binary_cross_entropy_with_logits(logits, y)
    loss.backward()
    
    print(f"\nGradient norms by layer:")
    
    layer_grads = defaultdict(list)
    for name, param in model.named_parameters():
        if param.grad is not None:
            # Group by layer
            layer_name = name.split('.')[0]
            grad_norm = param.grad.norm().item()
            layer_grads[layer_name].append((name, grad_norm))
    
    for layer_name, grads in sorted(layer_grads.items()):
        avg_grad = np.mean([g for _, g in grads])
        max_grad = max([g for _, g in grads])
        min_grad = min([g for _, g in grads])
        print(f"  {layer_name:20s}: avg={avg_grad:.2e}, range=[{min_grad:.2e}, {max_grad:.2e}]")
        
        if avg_grad < 1e-7:
            print(f"    🚨 VANISHING GRADIENTS in {layer_name}!")


def test_input_projection(samples, input_dim, hidden_dims=[64, 128, 256, 512]):
    """Test if different projection sizes help."""
    
    print("\n" + "=" * 60)
    print("TEST 4: Input Projection Analysis")
    print("=" * 60)
    
    # Get a sample batch features
    x_list = []
    for s in samples:
        if hasattr(s, 'x') and s.x is not None:
            x_list.append(s.x)
    x = torch.cat(x_list, dim=0).float()
    
    print(f"\nInput shape: {x.shape}")
    print(f"Input stats: mean={x.mean():.4f}, std={x.std():.4f}")
    
    # Analyze input feature distribution
    nonzero_per_row = (x != 0).sum(dim=1).float()
    print(f"Non-zero features per node: {nonzero_per_row.mean():.1f} ± {nonzero_per_row.std():.1f}")
    
    # Test different projections
    print(f"\nProjection tests (input_dim={input_dim}):")
    
    for hidden_dim in hidden_dims:
        proj = nn.Linear(input_dim, hidden_dim)
        nn.init.xavier_uniform_(proj.weight)
        nn.init.zeros_(proj.bias)
        
        with torch.no_grad():
            h = proj(x)
            h_relu = F.relu(h)
        
        # Check for dead neurons
        dead_neurons = (h_relu.sum(dim=0) == 0).sum().item()
        
        print(f"  {input_dim} → {hidden_dim}: h_mean={h.mean():.4f}, h_std={h.std():.4f}, "
              f"dead_neurons={dead_neurons}/{hidden_dim} ({100*dead_neurons/hidden_dim:.1f}%)")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--vocab-dir", type=Path, required=True)
    parser.add_argument("--hidden-dim", type=int, default=128)
    parser.add_argument("--num-samples", type=int, default=20)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 60)
    print("MODEL DIAGNOSTICS")
    print("=" * 60)
    
    # Load data
    samples = load_sample_batch(
        args.cache_dir,
        args.dataset_name,
        args.cache_signature,
        num_samples=args.num_samples,
    )
    
    if not samples:
        print("[ERROR] Failed to load samples!")
        sys.exit(1)
    
    print(f"Loaded {len(samples)} samples")
    
    # Get dimensions
    input_dim = samples[0].x.size(1)
    num_relations = load_vocab(args.vocab_dir)
    
    print(f"Input dim: {input_dim}")
    print(f"Num relations: {num_relations}")
    
    device = torch.device(args.device)
    print(f"Device: {device}")
    
    # Create simple model for testing
    model = create_simple_model(input_dim, args.hidden_dim)
    print(f"\nTest model parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    # Run tests
    test_input_projection(samples, input_dim)
    analyze_activations(model, samples, device)
    analyze_gradients(model, samples, device)
    can_overfit = test_overfit(model, samples, device, num_steps=200, lr=1e-2)
    
    # Summary
    print("\n" + "=" * 60)
    print("SUMMARY")
    print("=" * 60)
    
    if can_overfit:
        print("✅ Simple model can learn - issue is likely in your complex model architecture")
        print("\nRecommendations:")
        print("  1. Start with a simpler model (GAT or GCN) to establish a baseline")
        print("  2. Gradually add complexity")
        print("  3. Check RGAT implementation for bugs")
    else:
        print("🚨 Even simple model cannot learn - likely data or fundamental issue")
        print("\nRecommendations:")
        print("  1. Check if labels are correct")
        print("  2. Verify features are properly normalized")
        print("  3. Try much higher learning rate (0.1)")


if __name__ == "__main__":
    main()



"""
python diagnose_model.py \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "devign_normfunc_v2" \
    --cache-signature "caffd6ae8652870d" \
    --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
    --num-samples 20






"""