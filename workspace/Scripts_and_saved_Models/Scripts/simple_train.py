#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
simple_train.py - Standalone simple GCN trainer

Uses the EXACT same model as the diagnostic that works.
Tests if the issue is in data loading or training loop.
"""

import argparse
import json
import sys
import random
import io
import zipfile
from pathlib import Path

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, global_mean_pool

from sklearn.metrics import roc_auc_score, f1_score

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class SimpleGCN(nn.Module):
    """EXACT copy of SimpleGCN_NoNorm from diagnostic."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3):
        super().__init__()
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        self.classifier = nn.Linear(hidden_dim, 1)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = F.relu(self.proj(x))
        
        for conv in self.convs:
            h = conv(h, edge_index)
            h = F.relu(h)
        
        graph_emb = global_mean_pool(h, batch)
        return self.classifier(graph_emb)


def load_all_data(cache_dir, dataset_name, cache_sig, split):
    """Load ALL data from cache (same as Devign_baseline)."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        print(f"[Loading] {zip_path}")
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            
            for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                except Exception as e:
                    continue
    
    print(f"[Loaded] {split}: {len(samples)} samples")
    return samples


def train_epoch(model, loader, optimizer, device):
    """Simple training epoch."""
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
    """Evaluate model."""
    model.eval()
    
    all_probs = []
    all_labels = []
    total_loss = 0
    num_samples = 0
    
    with torch.no_grad():
        for batch in loader:
            batch = batch.to(device)
            logits = model(batch).view(-1)
            labels = batch.y.float().view(-1)
            
            loss = F.binary_cross_entropy_with_logits(logits, labels)
            total_loss += loss.item() * len(labels)
            num_samples += len(labels)
            
            probs = torch.sigmoid(logits)
            all_probs.append(probs.cpu())
            all_labels.append(labels.cpu())
    
    probs = torch.cat(all_probs)
    labels = torch.cat(all_labels)
    
    try:
        auc = roc_auc_score(labels.numpy(), probs.numpy())
    except:
        auc = 0.5
    
    preds = (probs > 0.5).long()
    f1 = f1_score(labels.numpy(), preds.numpy(), zero_division=0)
    
    return {
        'loss': total_loss / num_samples,
        'auc': auc,
        'f1': f1,
        'prob_mean': probs.mean().item(),
        'prob_std': probs.std().item(),
        'prob_min': probs.min().item(),
        'prob_max': probs.max().item(),
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=3)
    parser.add_argument("--lr", type=float, default=0.01)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    parser.add_argument("--no-shuffle", action="store_true", help="Disable shuffling (test bucket sampling effect)")
    args = parser.parse_args()
    
    print("=" * 70)
    print("SIMPLE GCN TRAINER (Diagnostic-Matching)")
    print("=" * 70)
    print(f"Hidden dim: {args.hidden_dim}")
    print(f"Layers: {args.num_layers}")
    print(f"LR: {args.lr}")
    print(f"Batch size: {args.batch_size}")
    print("=" * 70)
    
    device = torch.device(args.device)
    print(f"Device: {device}")
    
    # Load ALL data (same as Devign_baseline)
    train_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    val_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    
    if not train_data:
        print("[ERROR] No training data!")
        sys.exit(1)
    
    input_dim = train_data[0].x.size(1)
    print(f"Input dim: {input_dim}")
    
    # Standard DataLoader (NO bucket sampling!)
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=not args.no_shuffle)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    
    # Create model (EXACT same as diagnostic)
    model = SimpleGCN(
        input_dim=input_dim,
        hidden_dim=args.hidden_dim,
        num_layers=args.num_layers,
    ).to(device)
    
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    # Simple Adam optimizer
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)
    
    # Training loop
    best_auc = 0.5
    
    for epoch in range(1, args.epochs + 1):
        train_loss = train_epoch(model, train_loader, optimizer, device)
        val_metrics = evaluate(model, val_loader, device)
        
        if val_metrics['auc'] > best_auc:
            best_auc = val_metrics['auc']
            marker = " ← NEW BEST"
        else:
            marker = ""
        
        print(f"Epoch {epoch:02d} | Train: {train_loss:.4f} | Val: {val_metrics['loss']:.4f} | "
              f"AUC: {val_metrics['auc']:.4f} | F1: {val_metrics['f1']:.4f} | "
              f"Prob: {val_metrics['prob_mean']:.3f}±{val_metrics['prob_std']:.4f} "
              f"[{val_metrics['prob_min']:.3f}, {val_metrics['prob_max']:.3f}]{marker}")
        
        # Check for collapse
        if val_metrics['prob_std'] < 0.01:
            print(f"  ⚠️ LOW VARIANCE - possible collapse")
    
    print("\n" + "=" * 70)
    print(f"Best AUC: {best_auc:.4f}")
    print("=" * 70)
    
    if best_auc > 0.55:
        print("✅ Model learned! Issue was in Devign_baseline.py complexity.")
    elif best_auc < 0.52:
        print("❌ Model still fails. Issue is in data or fundamental approach.")
    else:
        print("⚠️ Marginal learning.")


if __name__ == "__main__":
    main()

"""
python simple_train.py \
  --cache-dir "./Clean_exports/cache_devign_v2"  \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --hidden-dim 256 \
  --num-layers 3 \
  --lr 0.01 \
  --batch-size 32 \
  --epochs 30

"""    