#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_scale.py - Test how dataset size affects learning

Key question: At what point does learning break down?
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
from torch_geometric.nn import GCNConv, global_mean_pool

from sklearn.metrics import roc_auc_score

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


class SimpleGCN(nn.Module):
    """Same as diagnostic."""
    
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


def load_all_samples(cache_dir, dataset_name, cache_sig, split):
    """Load ALL data from cache."""
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


def train_and_evaluate(train_data, val_data, input_dim, device, epochs=20, lr=0.01, batch_size=32):
    """Train and evaluate a fresh model."""
    
    train_loader = DataLoader(train_data, batch_size=batch_size, shuffle=True)
    val_loader = DataLoader(val_data, batch_size=batch_size, shuffle=False)
    
    model = SimpleGCN(input_dim=input_dim, hidden_dim=256, num_layers=3).to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    
    best_auc = 0.5
    final_prob_std = 0.0
    
    for epoch in range(1, epochs + 1):
        # Train
        model.train()
        for batch in train_loader:
            batch = batch.to(device)
            optimizer.zero_grad()
            logits = model(batch).view(-1)
            labels = batch.y.float().view(-1)
            loss = F.binary_cross_entropy_with_logits(logits, labels)
            loss.backward()
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()
        
        # Evaluate
        model.eval()
        all_probs = []
        all_labels = []
        
        with torch.no_grad():
            for batch in val_loader:
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
        
        if auc > best_auc:
            best_auc = auc
        
        final_prob_std = probs.std().item()
    
    return best_auc, final_prob_std


def analyze_data_characteristics(samples, name=""):
    """Analyze data characteristics."""
    labels = [s.y.item() if s.y.numel() == 1 else s.y[0].item() for s in samples]
    num_pos = sum(labels)
    num_neg = len(labels) - num_pos
    
    # Graph sizes
    sizes = [s.x.size(0) for s in samples]
    
    # Feature statistics
    all_features = torch.cat([s.x for s in samples[:100]], dim=0)
    
    print(f"  {name}:")
    print(f"    Samples: {len(samples)} (Pos: {num_pos}, Neg: {num_neg}, Ratio: {num_pos/len(samples):.2%})")
    print(f"    Graph sizes: {np.mean(sizes):.1f} ± {np.std(sizes):.1f} (min={min(sizes)}, max={max(sizes)})")
    print(f"    Feature mean: {all_features.mean():.4f}, std: {all_features.std():.4f}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--device", type=str, default="cuda" if torch.cuda.is_available() else "cpu")
    args = parser.parse_args()
    
    print("=" * 70)
    print("SCALE DIAGNOSTIC")
    print("=" * 70)
    
    device = torch.device(args.device)
    
    # Load ALL data
    print("\nLoading all data...")
    all_train = load_all_samples(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    all_val = load_all_samples(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    
    print(f"\nTotal: Train={len(all_train)}, Val={len(all_val)}")
    
    input_dim = all_train[0].x.size(1)
    
    # Test different dataset sizes
    sizes = [100, 250, 500, 1000, 2000, 5000, 10000, len(all_train)]
    sizes = [s for s in sizes if s <= len(all_train)]
    
    print("\n" + "=" * 70)
    print("TESTING DIFFERENT DATASET SIZES")
    print("=" * 70)
    
    results = []
    
    for n_samples in sizes:
        print(f"\n--- Testing with {n_samples} training samples ---")
        
        # Random subset
        random.shuffle(all_train)
        train_subset = all_train[:n_samples]
        
        # Analyze this subset
        analyze_data_characteristics(train_subset, f"{n_samples} samples")
        
        # Train
        best_auc, prob_std = train_and_evaluate(
            train_subset, all_val, input_dim, device,
            epochs=20, lr=0.01, batch_size=32
        )
        
        status = "✅" if best_auc > 0.55 else "⚠️" if best_auc > 0.52 else "❌"
        collapse = "COLLAPSE" if prob_std < 0.01 else "OK"
        
        print(f"  → Best AUC: {best_auc:.4f}, Prob std: {prob_std:.4f} ({collapse}) {status}")
        
        results.append((n_samples, best_auc, prob_std))
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY: AUC vs Dataset Size")
    print("=" * 70)
    print(f"{'Size':>8} | {'AUC':>6} | {'Prob Std':>8} | Status")
    print("-" * 40)
    
    for n, auc, std in results:
        status = "✅ Works" if auc > 0.55 else "⚠️ Marginal" if auc > 0.52 else "❌ Fails"
        print(f"{n:>8} | {auc:.4f} | {std:.6f} | {status}")
    
    # Diagnosis
    print("\n" + "=" * 70)
    print("DIAGNOSIS")
    print("=" * 70)
    
    # Find breakpoint
    working_sizes = [n for n, auc, _ in results if auc > 0.55]
    failing_sizes = [n for n, auc, _ in results if auc < 0.52]
    
    if working_sizes and failing_sizes:
        breakpoint = max(working_sizes)
        print(f"Learning breaks down between {breakpoint} and {min(failing_sizes)} samples")
        print("\nPossible causes:")
        print("1. Weak signal gets diluted with more diverse data")
        print("2. Model finds local minimum at class prior")
        print("3. Need stronger regularization for larger datasets")
        print("\nRecommendations:")
        print(f"- Train on subset of ~{breakpoint} samples")
        print("- Use curriculum learning (start small, gradually increase)")
        print("- Try contrastive learning to strengthen signal")
    elif not working_sizes:
        print("Model fails at ALL scales - fundamental issue with task/data")
    else:
        print("Model works at all scales - original issue was elsewhere")


if __name__ == "__main__":
    main()


"""
python diagnose_scale.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d"

"""    