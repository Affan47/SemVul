#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
mlp_baseline.py - MLP on pooled features (NO GNN)

Since Logistic Regression achieves 0.60 AUC on mean features,
but GNN achieves 0.50, the GNN is DESTROYING the signal!

This script:
1. Pools node features directly (mean, max, or both)
2. Applies MLP classifier
3. NO message passing!
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
from torch_geometric.nn import global_mean_pool, global_max_pool

from sklearn.metrics import roc_auc_score, f1_score, accuracy_score

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class MLPClassifier(nn.Module):
    """Simple MLP on pooled node features - NO GNN!"""
    
    def __init__(self, input_dim, hidden_dim=256, pooling='mean_max', dropout=0.3):
        super().__init__()
        
        self.pooling = pooling
        
        # Input projection
        self.proj = nn.Linear(input_dim, hidden_dim)
        
        # Pooling determines classifier input dim
        if pooling == 'mean_max':
            pool_dim = hidden_dim * 2
        else:
            pool_dim = hidden_dim
        
        # MLP classifier
        self.classifier = nn.Sequential(
            nn.Linear(pool_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim // 2, 1),
        )
    
    def forward(self, data):
        x = data.x.float()
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Project to hidden dim
        h = F.relu(self.proj(x))
        
        # Pool directly - NO MESSAGE PASSING!
        if self.pooling == 'mean':
            graph_emb = global_mean_pool(h, batch)
        elif self.pooling == 'max':
            graph_emb = global_max_pool(h, batch)
        elif self.pooling == 'mean_max':
            graph_emb = torch.cat([
                global_mean_pool(h, batch),
                global_max_pool(h, batch)
            ], dim=-1)
        
        return self.classifier(graph_emb)


class DeepMLPClassifier(nn.Module):
    """Deeper MLP with skip connections."""
    
    def __init__(self, input_dim, hidden_dim=256, pooling='mean_max', dropout=0.3):
        super().__init__()
        
        self.pooling = pooling
        
        # Multiple projection layers (but NO message passing!)
        self.proj1 = nn.Linear(input_dim, hidden_dim)
        self.proj2 = nn.Linear(hidden_dim, hidden_dim)
        self.proj3 = nn.Linear(hidden_dim, hidden_dim)
        
        self.dropout = nn.Dropout(dropout)
        
        if pooling == 'mean_max':
            pool_dim = hidden_dim * 2
        else:
            pool_dim = hidden_dim
        
        self.classifier = nn.Sequential(
            nn.Linear(pool_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
    
    def forward(self, data):
        x = data.x.float()
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Deep per-node transformation (no message passing!)
        h = F.relu(self.proj1(x))
        h = h + F.relu(self.proj2(h))  # Skip connection
        h = h + F.relu(self.proj3(h))  # Skip connection
        h = self.dropout(h)
        
        # Pool
        if self.pooling == 'mean':
            graph_emb = global_mean_pool(h, batch)
        elif self.pooling == 'max':
            graph_emb = global_max_pool(h, batch)
        elif self.pooling == 'mean_max':
            graph_emb = torch.cat([
                global_mean_pool(h, batch),
                global_max_pool(h, batch)
            ], dim=-1)
        
        return self.classifier(graph_emb)


def load_all_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load data from cache."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            if max_samples:
                random.shuffle(pt_files)
                pt_files = pt_files[:max_samples]
            
            for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                except:
                    continue
    
    return samples


def train_epoch(model, loader, optimizer, device, pos_weight=None):
    model.train()
    total_loss = 0
    num_samples = 0
    
    criterion = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()
        
        logits = model(batch).view(-1)
        labels = batch.y.float().view(-1)
        
        loss = criterion(logits, labels)
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
    
    # Find best threshold
    best_f1 = 0
    best_thresh = 0.5
    for thresh in np.arange(0.3, 0.7, 0.02):
        preds = (probs > thresh).long()
        f1 = f1_score(labels.numpy(), preds.numpy(), zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    preds = (probs > best_thresh).long()
    acc = accuracy_score(labels.numpy(), preds.numpy())
    
    # Class-wise stats
    safe_probs = probs[labels == 0]
    vuln_probs = probs[labels == 1]
    
    return {
        'auc': auc,
        'f1': best_f1,
        'acc': acc,
        'thresh': best_thresh,
        'prob_mean': probs.mean().item(),
        'prob_std': probs.std().item(),
        'safe_mean': safe_probs.mean().item() if len(safe_probs) > 0 else 0,
        'vuln_mean': vuln_probs.mean().item() if len(vuln_probs) > 0 else 0,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--pooling", type=str, default="mean_max",
                       choices=["mean", "max", "mean_max"])
    parser.add_argument("--model", type=str, default="mlp",
                       choices=["mlp", "deep_mlp"])
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=50)
    parser.add_argument("--dropout", type=float, default=0.3)
    parser.add_argument("--max-samples", type=int, default=None)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("MLP BASELINE (NO GNN!)")
    print("=" * 70)
    print(f"Model: {args.model.upper()}")
    print(f"Pooling: {args.pooling}")
    print(f"Hidden dim: {args.hidden_dim}")
    print(f"LR: {args.lr}")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load data
    train_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "train", args.max_samples)
    val_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    test_data = load_all_data(args.cache_dir, args.dataset_name, args.cache_signature, "test")
    
    print(f"Train: {len(train_data)} | Val: {len(val_data)} | Test: {len(test_data)}")
    
    input_dim = train_data[0].x.size(1)
    print(f"Input dim: {input_dim}")
    
    # Class weights
    labels = [d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in train_data]
    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    pos_weight = torch.tensor([num_neg / num_pos], device=device)
    print(f"Pos weight: {pos_weight.item():.4f}")
    
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    test_loader = DataLoader(test_data, batch_size=args.batch_size, shuffle=False)
    
    # Create model
    if args.model == "mlp":
        model = MLPClassifier(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            pooling=args.pooling,
            dropout=args.dropout,
        )
    else:
        model = DeepMLPClassifier(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            pooling=args.pooling,
            dropout=args.dropout,
        )
    
    model = model.to(device)
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr, weight_decay=1e-5)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode='max', factor=0.5, patience=5)
    
    best_auc = 0.5
    best_epoch = 0
    
    for epoch in range(1, args.epochs + 1):
        train_loss = train_epoch(model, train_loader, optimizer, device, pos_weight)
        val_metrics = evaluate(model, val_loader, device)
        
        scheduler.step(val_metrics['auc'])
        
        if val_metrics['auc'] > best_auc:
            best_auc = val_metrics['auc']
            best_epoch = epoch
            torch.save(model.state_dict(), '/tmp/best_mlp.pt')
            marker = " ← BEST"
        else:
            marker = ""
        
        collapse = "⚠️ COLLAPSE" if val_metrics['prob_std'] < 0.05 else ""
        
        print(f"Epoch {epoch:02d} | Loss: {train_loss:.4f} | "
              f"AUC: {val_metrics['auc']:.4f} | F1: {val_metrics['f1']:.4f} | "
              f"Safe: {val_metrics['safe_mean']:.3f} Vuln: {val_metrics['vuln_mean']:.3f} "
              f"{collapse}{marker}")
    
    # Final evaluation
    print("\n" + "=" * 70)
    print("FINAL EVALUATION")
    print("=" * 70)
    
    model.load_state_dict(torch.load('/tmp/best_mlp.pt'))
    test_metrics = evaluate(model, test_loader, device)
    
    print(f"Best epoch: {best_epoch}")
    print(f"Test AUC: {test_metrics['auc']:.4f}")
    print(f"Test F1: {test_metrics['f1']:.4f} (threshold={test_metrics['thresh']:.2f})")
    print(f"Test Acc: {test_metrics['acc']:.4f}")
    print(f"Prob distribution: {test_metrics['prob_mean']:.3f} ± {test_metrics['prob_std']:.3f}")
    print(f"Safe mean: {test_metrics['safe_mean']:.3f}, Vuln mean: {test_metrics['vuln_mean']:.3f}")
    
    if test_metrics['auc'] > 0.58:
        print("\n✅ MLP works! The GNN was destroying the signal.")
        print("   Consider using MLP baseline or fixing the GNN.")
    elif test_metrics['auc'] > 0.55:
        print("\n⚠️ Marginal improvement over random.")
    else:
        print("\n❌ MLP also fails. Issue is in the data/labels.")


if __name__ == "__main__":
    main()


"""
python mlp_baseline.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --pooling mean_max \
  --model deep_mlp \
  --lr 0.001 \
  --epochs 50

"""    