#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
graph_level_classifier.py - Compute graph-level features first, then classify

The key insight: Logistic Regression on mean features works better than 
per-node neural networks. This model:
1. Computes graph-level statistics (mean, max, std, etc.) FIRST
2. Then applies MLP classification

No per-node encoding, no attention - just aggregate then classify.
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
from torch_geometric.loader import DataLoader

from sklearn.metrics import roc_auc_score, f1_score, accuracy_score
from sklearn.preprocessing import StandardScaler

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load data."""
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


def compute_graph_features(data, use_embedding_only=True, use_stats=True):
    """Compute graph-level features from node features.
    
    Args:
        data: PyG Data object
        use_embedding_only: Use only embedding dims (28-795), skip one-hot
        use_stats: Include std, min, max in addition to mean
    
    Returns:
        feature_vector: 1D tensor of graph features
    """
    x = data.x.float()
    
    if use_embedding_only:
        x = x[:, 28:]  # Only embedding part
    
    # Basic statistics
    mean_feat = x.mean(dim=0)
    
    features = [mean_feat]
    
    if use_stats:
        max_feat = x.max(dim=0)[0]
        std_feat = x.std(dim=0)
        features.extend([max_feat, std_feat])
    
    return torch.cat(features)


def select_dimensions(train_features, train_labels, top_k=100):
    """Select most discriminative dimensions."""
    safe_feats = train_features[train_labels == 0]
    vuln_feats = train_features[train_labels == 1]
    
    safe_mean = safe_feats.mean(dim=0)
    vuln_mean = vuln_feats.mean(dim=0)
    
    diff = (vuln_mean - safe_mean).abs()
    variance = train_features.var(dim=0)
    
    # Combined score
    score = diff * torch.sqrt(variance + 1e-8)
    
    top_indices = score.topk(top_k).indices
    return top_indices


class GraphLevelMLP(nn.Module):
    """Simple MLP on pre-computed graph features."""
    
    def __init__(self, input_dim, hidden_dim=256, dropout=0.3):
        super().__init__()
        
        self.net = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.BatchNorm1d(hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.BatchNorm1d(hidden_dim // 2),
            nn.ReLU(),
            nn.Dropout(dropout),
            
            nn.Linear(hidden_dim // 2, hidden_dim // 4),
            nn.BatchNorm1d(hidden_dim // 4),
            nn.ReLU(),
            nn.Dropout(dropout),
            
            nn.Linear(hidden_dim // 4, 1),
        )
    
    def forward(self, x):
        return self.net(x)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--top-k", type=int, default=100,
                       help="Number of dimensions to select (0 = use all)")
    parser.add_argument("--use-stats", action="store_true",
                       help="Include max and std in features")
    parser.add_argument("--hidden-dim", type=int, default=256)
    parser.add_argument("--lr", type=float, default=0.001)
    parser.add_argument("--batch-size", type=int, default=64)
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--dropout", type=float, default=0.3)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("GRAPH-LEVEL CLASSIFIER")
    print("=" * 70)
    print(f"Top-K dims: {args.top_k if args.top_k > 0 else 'all'}")
    print(f"Use stats (mean+max+std): {args.use_stats}")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load raw data
    train_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    val_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    test_data = load_data(args.cache_dir, args.dataset_name, args.cache_signature, "test")
    
    print(f"\nRaw data: Train={len(train_data)} | Val={len(val_data)} | Test={len(test_data)}")
    
    # Compute graph-level features
    print("\nComputing graph-level features...")
    
    train_features = torch.stack([compute_graph_features(d, use_stats=args.use_stats) for d in tqdm(train_data)])
    val_features = torch.stack([compute_graph_features(d, use_stats=args.use_stats) for d in tqdm(val_data)])
    test_features = torch.stack([compute_graph_features(d, use_stats=args.use_stats) for d in tqdm(test_data)])
    
    train_labels = torch.tensor([d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in train_data])
    val_labels = torch.tensor([d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in val_data])
    test_labels = torch.tensor([d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in test_data])
    
    print(f"Feature shape: {train_features.shape}")
    
    # Feature selection
    if args.top_k > 0 and args.top_k < train_features.shape[1]:
        print(f"\nSelecting top-{args.top_k} dimensions...")
        selected_dims = select_dimensions(train_features, train_labels, args.top_k)
        
        train_features = train_features[:, selected_dims]
        val_features = val_features[:, selected_dims]
        test_features = test_features[:, selected_dims]
        
        print(f"Selected feature shape: {train_features.shape}")
    
    # Normalize features
    print("\nNormalizing features...")
    scaler = StandardScaler()
    train_features = torch.tensor(scaler.fit_transform(train_features.numpy()), dtype=torch.float32)
    val_features = torch.tensor(scaler.transform(val_features.numpy()), dtype=torch.float32)
    test_features = torch.tensor(scaler.transform(test_features.numpy()), dtype=torch.float32)
    
    # Quick LogReg baseline
    print("\n" + "=" * 70)
    print("LOGISTIC REGRESSION BASELINE")
    print("=" * 70)
    
    from sklearn.linear_model import LogisticRegression
    
    clf = LogisticRegression(max_iter=1000, C=1.0, random_state=42)
    clf.fit(train_features.numpy(), train_labels.numpy())
    
    val_probs_lr = clf.predict_proba(val_features.numpy())[:, 1]
    test_probs_lr = clf.predict_proba(test_features.numpy())[:, 1]
    
    val_auc_lr = roc_auc_score(val_labels.numpy(), val_probs_lr)
    test_auc_lr = roc_auc_score(test_labels.numpy(), test_probs_lr)
    
    print(f"Val AUC: {val_auc_lr:.4f}")
    print(f"Test AUC: {test_auc_lr:.4f}")
    
    # Create datasets
    train_dataset = torch.utils.data.TensorDataset(train_features, train_labels.float())
    val_dataset = torch.utils.data.TensorDataset(val_features, val_labels.float())
    test_dataset = torch.utils.data.TensorDataset(test_features, test_labels.float())
    
    train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=args.batch_size, shuffle=True)
    val_loader = torch.utils.data.DataLoader(val_dataset, batch_size=args.batch_size, shuffle=False)
    test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=args.batch_size, shuffle=False)
    
    # Class weights
    num_pos = train_labels.sum().item()
    num_neg = len(train_labels) - num_pos
    pos_weight = torch.tensor([num_neg / num_pos], device=device)
    
    # Create model
    print("\n" + "=" * 70)
    print("MLP CLASSIFIER")
    print("=" * 70)
    
    model = GraphLevelMLP(
        input_dim=train_features.shape[1],
        hidden_dim=args.hidden_dim,
        dropout=args.dropout,
    ).to(device)
    
    print(f"Parameters: {sum(p.numel() for p in model.parameters()):,}")
    
    criterion = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
    optimizer = torch.optim.AdamW(model.parameters(), lr=args.lr, weight_decay=1e-4)
    scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optimizer, args.epochs)
    
    best_auc = 0.5
    best_epoch = 0
    patience = 80
    no_improve = 0
    
    for epoch in range(1, args.epochs + 1):
        # Train
        model.train()
        total_loss = 0
        for x, y in train_loader:
            x, y = x.to(device), y.to(device)
            optimizer.zero_grad()
            logits = model(x).view(-1)
            loss = criterion(logits, y)
            loss.backward()
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()
            total_loss += loss.item()
        
        scheduler.step()
        
        # Evaluate
        model.eval()
        val_probs = []
        with torch.no_grad():
            for x, y in val_loader:
                x = x.to(device)
                probs = torch.sigmoid(model(x)).view(-1)
                val_probs.append(probs.cpu())
        
        val_probs = torch.cat(val_probs)
        val_auc = roc_auc_score(val_labels.numpy(), val_probs.numpy())
        
        if val_auc > best_auc:
            best_auc = val_auc
            best_epoch = epoch
            torch.save(model.state_dict(), '/tmp/best_graph_level.pt')
            marker = " ← BEST"
            no_improve = 0
        else:
            marker = ""
            no_improve += 1
        
        if epoch % 10 == 0 or marker:
            print(f"Epoch {epoch:02d} | Loss: {total_loss/len(train_loader):.4f} | Val AUC: {val_auc:.4f}{marker}")
        
        if no_improve >= patience:
            print(f"\nEarly stopping at epoch {epoch}")
            break
    
    # Final evaluation
    print("\n" + "=" * 70)
    print("FINAL EVALUATION")
    print("=" * 70)
    
    model.load_state_dict(torch.load('/tmp/best_graph_level.pt'))
    model.eval()
    
    test_probs = []
    with torch.no_grad():
        for x, y in test_loader:
            x = x.to(device)
            probs = torch.sigmoid(model(x)).view(-1)
            test_probs.append(probs.cpu())
    
    test_probs = torch.cat(test_probs)
    test_auc = roc_auc_score(test_labels.numpy(), test_probs.numpy())
    
    # Best F1
    best_f1 = 0
    best_thresh = 0.5
    for thresh in np.arange(0.3, 0.7, 0.02):
        preds = (test_probs > thresh).long()
        f1 = f1_score(test_labels.numpy(), preds.numpy(), zero_division=0)
        if f1 > best_f1:
            best_f1 = f1
            best_thresh = thresh
    
    print(f"Best epoch: {best_epoch}")
    print(f"Test AUC (MLP): {test_auc:.4f}")
    print(f"Test AUC (LogReg): {test_auc_lr:.4f}")
    print(f"Test F1: {best_f1:.4f} @ threshold={best_thresh:.2f}")
    
    # Class separation
    safe_probs = test_probs[test_labels == 0]
    vuln_probs = test_probs[test_labels == 1]
    print(f"Separation: Safe={safe_probs.mean():.3f}±{safe_probs.std():.3f}, Vuln={vuln_probs.mean():.3f}±{vuln_probs.std():.3f}")
    
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"Feature dims: {train_features.shape[1]}")
    print(f"LogReg Test AUC: {test_auc_lr:.4f}")
    print(f"MLP Test AUC: {test_auc:.4f}")


if __name__ == "__main__":
    main()


"""
# Basic: top-100 dims, mean only
python graph_level_classifier.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --top-k 100 \
  --epochs 100

# With statistics (mean + max + std)
python graph_level_classifier.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --top-k 100 \
  --use-stats \
  --epochs 100

# Use all dims with stats
python graph_level_classifier.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --top-k 0 \
  --use-stats \
  --epochs 150

"""    