#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
attention_gcn.py - GCN with attention pooling (not mean pooling)

Mean pooling destroys information at scale. This uses:
1. Global Attention Pooling - learns which nodes matter
2. Multi-head attention over node features
3. Concatenates multiple statistics (mean, max, attention-weighted)
"""

import argparse
import sys
import random
import io
import zipfile
from pathlib import Path

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, global_mean_pool, global_max_pool, GlobalAttention
from torch_geometric.nn import Set2Set

from sklearn.metrics import roc_auc_score, f1_score

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class AttentionPooling(nn.Module):
    """Learn which nodes are important for classification."""
    
    def __init__(self, hidden_dim):
        super().__init__()
        # Attention gate network
        self.gate_nn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 1),
        )
        self.attention = GlobalAttention(self.gate_nn)
    
    def forward(self, x, batch):
        return self.attention(x, batch)


class MultiStatPooling(nn.Module):
    """Concatenate multiple pooling statistics."""
    
    def __init__(self, hidden_dim):
        super().__init__()
        self.hidden_dim = hidden_dim
        # Also compute attention-weighted pool
        self.attention = AttentionPooling(hidden_dim)
    
    def forward(self, x, batch):
        # Mean, max, and attention-weighted
        mean_pool = global_mean_pool(x, batch)
        max_pool = global_max_pool(x, batch)
        attn_pool = self.attention(x, batch)
        
        return torch.cat([mean_pool, max_pool, attn_pool], dim=-1)


class GCN_AttentionPool(nn.Module):
    """GCN with attention pooling instead of mean pooling."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3, pooling='attention'):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        # Pooling
        self.pooling_type = pooling
        if pooling == 'attention':
            self.pool = AttentionPooling(hidden_dim)
            classifier_dim = hidden_dim
        elif pooling == 'set2set':
            self.pool = Set2Set(hidden_dim, processing_steps=3)
            classifier_dim = hidden_dim * 2  # Set2Set outputs 2x
        elif pooling == 'multistat':
            self.pool = MultiStatPooling(hidden_dim)
            classifier_dim = hidden_dim * 3  # mean + max + attention
        else:  # mean (baseline)
            self.pool = None
            classifier_dim = hidden_dim
        
        self.classifier = nn.Linear(classifier_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        
        for conv in self.convs:
            h = conv(h, edge_index)
            h = F.relu(h)
        
        # Pooling
        if self.pool is not None:
            if self.pooling_type == 'set2set':
                graph_emb = self.pool(h, batch)
            else:
                graph_emb = self.pool(h, batch)
        else:
            graph_emb = global_mean_pool(h, batch)
        
        return self.classifier(graph_emb)


def load_all_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load data from cache."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            random.shuffle(pt_files)  # Shuffle before loading
            
            for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                        if max_samples and len(samples) >= max_samples:
                            break
                except:
                    continue
    
    return samples


def train_epoch(model, loader, optimizer, device):
    model.train()
    total_loss = 0
    num_samples = 0
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()
        
        logits = model(batch).view(-1)
        labels = batch.y.float().view(-1)
        
        loss = F.binary_cross_entropy_with_logits(logits, labels)
        loss.backward()
        
        torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()
        
        total_loss += loss.item() * len(labels)
        num_samples += len(labels)
    
    return total_loss / num_samples


def evaluate(model, loader, device):
    model.eval()
    all_probs = []
    all_labels = []
    
    with torch.no_grad():
        for batch in loader:
            batch = batch.to(device)
            logits = model(batch).view(-1)
            probs = torch.sigmoid(logits)
            all_probs.append(probs.cpu())
            all_labels.append(batch.y.cpu().view(-1))
    
    probs = torch.cat(all_probs)
    labels = torch.cat(all_labels)
    
    try:
        auc = roc_auc_score(labels.numpy(), probs.numpy())
    except:
        auc = 0.5
    
    return {
        'auc': auc,
        'prob_mean': probs.mean().item(),
        'prob_std': probs.std().item(),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=3)
    parser.add_argument("--pooling", type=str, default="attention",
                       choices=["mean", "attention", "set2set", "multistat"])
    parser.add_argument("--lr", type=float, default=0.01)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--max-samples", type=int, default=None,
                       help="Limit training samples (for testing)")
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("GCN with ATTENTION POOLING")
    print("=" * 70)
    print(f"Pooling: {args.pooling.upper()}")
    print(f"Hidden dim: {args.hidden_dim}")
    print(f"Layers: {args.num_layers}")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load data
    train_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "train", args.max_samples)
    val_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    
    print(f"Train: {len(train_data)} samples")
    print(f"Val: {len(val_data)} samples")
    
    input_dim = train_data[0].x.size(1)
    
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    
    # Create model
    model = GCN_AttentionPool(
        input_dim=input_dim,
        hidden_dim=args.hidden_dim,
        num_layers=args.num_layers,
        pooling=args.pooling,
    ).to(device)
    
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)
    
    best_auc = 0.5
    
    for epoch in range(1, args.epochs + 1):
        train_loss = train_epoch(model, train_loader, optimizer, device)
        metrics = evaluate(model, val_loader, device)
        
        if metrics['auc'] > best_auc:
            best_auc = metrics['auc']
            marker = " ← NEW BEST"
        else:
            marker = ""
        
        collapse = "⚠️ COLLAPSE" if metrics['prob_std'] < 0.01 else ""
        
        print(f"Epoch {epoch:02d} | Loss: {train_loss:.4f} | "
              f"AUC: {metrics['auc']:.4f} | "
              f"Prob: {metrics['prob_mean']:.3f}±{metrics['prob_std']:.4f} "
              f"{collapse}{marker}")
    
    print(f"\nBest AUC: {best_auc:.4f}")
    
    if best_auc > 0.55:
        print("✅ Success! Attention pooling helps.")
    elif best_auc < 0.52:
        print("❌ Still failing. Issue may be deeper than pooling.")


if __name__ == "__main__":
    main()



"""

# Test attention pooling on FULL dataset
python attention_gcn.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --pooling attention \
  --epochs 30

# Also try multistat (mean + max + attention)
python attention_gcn.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --pooling multistat \
  --epochs 30

# Also try Set2Set
python attention_gcn.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --pooling set2set \
  --epochs 30

# Train on 1000 samples (we know this works)
python attention_gcn.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --pooling mean \
  --max-samples 1000 \
  --epochs 30



"""