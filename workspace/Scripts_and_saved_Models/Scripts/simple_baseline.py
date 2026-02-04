#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
simple_baseline.py - Ultra-simple GNN baseline without DevignConvHead

This model strips away all complexity to establish a working baseline:
- Simple linear projection
- Standard GCNConv
- Simple mean/max pooling (NO DevignConvHead)
- Simple classifier

If this learns but the complex model doesn't, the issue is in DevignConvHead.
"""

import argparse
import json
import sys
import random
import io
import zipfile
import warnings
from pathlib import Path
from collections import defaultdict

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, global_mean_pool, global_max_pool

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class SimpleGCN(nn.Module):
    """Ultra-simple GCN - no DevignConvHead, no fancy components."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=3, dropout=0.2):
        super().__init__()
        
        # Simple input projection
        self.input_proj = nn.Linear(input_dim, hidden_dim)
        
        # GCN layers with residuals
        self.convs = nn.ModuleList()
        for _ in range(num_layers):
            self.convs.append(GCNConv(hidden_dim, hidden_dim))
        
        self.dropout = nn.Dropout(dropout)
        
        # Simple classifier
        self.classifier = nn.Linear(hidden_dim, 1)
        
        self._init_weights()
    
    def _init_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.xavier_uniform_(m.weight)
                if m.bias is not None:
                    nn.init.zeros_(m.bias)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        # Input projection
        h = self.input_proj(x)
        h = F.relu(h)
        
        # GCN layers
        for conv in self.convs:
            h_new = conv(h, edge_index)
            h_new = F.relu(h_new)
            h_new = self.dropout(h_new)
            h = h + h_new  # Residual
        
        # Simple mean pooling
        graph_emb = global_mean_pool(h, batch)
        
        # Classifier
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


class SimpleGAT(nn.Module):
    """Ultra-simple GAT."""
    
    def __init__(self, input_dim, hidden_dim=256, num_layers=2, heads=4, dropout=0.2):
        super().__init__()
        from torch_geometric.nn import GATConv
        
        self.input_proj = nn.Linear(input_dim, hidden_dim)
        
        self.convs = nn.ModuleList()
        for i in range(num_layers):
            self.convs.append(GATConv(hidden_dim, hidden_dim // heads, heads=heads, concat=True, dropout=dropout))
        
        self.dropout = nn.Dropout(dropout)
        self.classifier = nn.Linear(hidden_dim, 1)
        
        self._init_weights()
    
    def _init_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.xavier_uniform_(m.weight)
                if m.bias is not None:
                    nn.init.zeros_(m.bias)
    
    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch if hasattr(data, 'batch') and data.batch is not None else torch.zeros(x.size(0), dtype=torch.long, device=x.device)
        
        h = self.input_proj(x)
        h = F.relu(h)
        
        for conv in self.convs:
            h_new = conv(h, edge_index)
            h_new = F.elu(h_new)
            h_new = self.dropout(h_new)
            h = h + h_new
        
        graph_emb = global_mean_pool(h, batch)
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


def load_data(cache_dir, dataset_name, cache_sig, split):
    """Load all data from cache."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            
            for pt_name in tqdm(pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                except:
                    continue
    
    return samples


def evaluate(model, loader, device):
    """Evaluate model."""
    model.eval()
    
    all_probs = []
    all_labels = []
    
    with torch.no_grad():
        for batch in loader:
            batch = batch.to(device)
            out = model(batch)
            probs = torch.sigmoid(out["logits"]).view(-1)
            labels = batch.y.view(-1)
            
            all_probs.append(probs.cpu())
            all_labels.append(labels.cpu())
    
    probs = torch.cat(all_probs)
    labels = torch.cat(all_labels)
    
    # Metrics
    from sklearn.metrics import roc_auc_score, f1_score, accuracy_score
    
    preds = (probs > 0.5).long()
    
    try:
        auc = roc_auc_score(labels.numpy(), probs.numpy())
    except:
        auc = 0.5
    
    f1 = f1_score(labels.numpy(), preds.numpy())
    acc = accuracy_score(labels.numpy(), preds.numpy())
    
    # Prediction distribution
    safe_probs = probs[labels == 0]
    vuln_probs = probs[labels == 1]
    
    return {
        'auc': auc,
        'f1': f1,
        'acc': acc,
        'prob_mean': probs.mean().item(),
        'prob_std': probs.std().item(),
        'safe_mean': safe_probs.mean().item() if len(safe_probs) > 0 else 0,
        'safe_std': safe_probs.std().item() if len(safe_probs) > 0 else 0,
        'vuln_mean': vuln_probs.mean().item() if len(vuln_probs) > 0 else 0,
        'vuln_std': vuln_probs.std().item() if len(vuln_probs) > 0 else 0,
    }


def train_epoch(model, loader, optimizer, device):
    """Train one epoch."""
    model.train()
    
    total_loss = 0
    num_batches = 0
    
    for batch in tqdm(loader, desc="Training", leave=False):
        batch = batch.to(device)
        optimizer.zero_grad()
        
        out = model(batch)
        logits = out["logits"].view(-1)
        labels = batch.y.float().view(-1)
        
        loss = F.binary_cross_entropy_with_logits(logits, labels)
        loss.backward()
        
        torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()
        
        total_loss += loss.item()
        num_batches += 1
    
    return total_loss / max(num_batches, 1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--model", type=str, default="gcn", choices=["gcn", "gat"])
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--num-layers", type=int, default=3)
    parser.add_argument("--lr", type=float, default=1e-2)
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--epochs", type=int, default=30)
    parser.add_argument("--dropout", type=float, default=0.2)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 60)
    print("SIMPLE BASELINE TRAINING")
    print("=" * 60)
    print(f"Model: {args.model.upper()}")
    print(f"Hidden dim: {args.hidden_dim}")
    print(f"Layers: {args.num_layers}")
    print(f"Learning rate: {args.lr}")
    print(f"Batch size: {args.batch_size}")
    print("=" * 60)
    
    device = torch.device(args.device)
    
    # Load data
    train_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    val_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    
    print(f"Train: {len(train_data)} samples")
    print(f"Val: {len(val_data)} samples")
    
    if not train_data:
        print("[ERROR] No training data!")
        sys.exit(1)
    
    input_dim = train_data[0].x.size(1)
    print(f"Input dim: {input_dim}")
    
    # Create loaders
    train_loader = DataLoader(train_data, batch_size=args.batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=args.batch_size, shuffle=False)
    
    # Create model
    if args.model == "gcn":
        model = SimpleGCN(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.num_layers,
            dropout=args.dropout,
        )
    else:
        model = SimpleGAT(
            input_dim=input_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.num_layers,
            dropout=args.dropout,
        )
    
    model = model.to(device)
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)
    
    # Training loop
    best_auc = 0
    best_f1 = 0
    
    for epoch in range(1, args.epochs + 1):
        # Train
        train_loss = train_epoch(model, train_loader, optimizer, device)
        
        # Evaluate
        val_metrics = evaluate(model, val_loader, device)
        
        # Print
        print(f"Epoch {epoch:02d} | Loss: {train_loss:.4f} | "
              f"AUC: {val_metrics['auc']:.4f} | F1: {val_metrics['f1']:.4f} | "
              f"Prob std: {val_metrics['prob_std']:.4f}")
        
        # Check for collapse
        if val_metrics['prob_std'] < 0.01:
            print(f"  ⚠️ Low variance! Safe: {val_metrics['safe_mean']:.3f}±{val_metrics['safe_std']:.4f}, "
                  f"Vuln: {val_metrics['vuln_mean']:.3f}±{val_metrics['vuln_std']:.4f}")
        else:
            print(f"  ✓ Safe: {val_metrics['safe_mean']:.3f}±{val_metrics['safe_std']:.3f}, "
                  f"Vuln: {val_metrics['vuln_mean']:.3f}±{val_metrics['vuln_std']:.3f}")
        
        if val_metrics['auc'] > best_auc:
            best_auc = val_metrics['auc']
            best_f1 = val_metrics['f1']
    
    print("\n" + "=" * 60)
    print("FINAL RESULTS")
    print("=" * 60)
    print(f"Best AUC: {best_auc:.4f}")
    print(f"Best F1: {best_f1:.4f}")
    
    if best_auc > 0.55:
        print("\n✅ Simple model LEARNS! Issue is in complex model architecture.")
    elif best_auc < 0.52:
        print("\n🚨 Simple model also fails. Issue may be in data or labels.")
    else:
        print("\n⚠️ Marginal learning. Try higher LR or more epochs.")


if __name__ == "__main__":
    main()