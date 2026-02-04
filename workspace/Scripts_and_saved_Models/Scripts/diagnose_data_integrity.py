#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_data_integrity.py - Verify data pipeline correctness

Checks:
1. Are labels in cached data consistent with manifest?
2. Do different graphs actually have different features?
3. Is there ANY signal in the data?
4. Sample verification - print actual samples to inspect
"""

import argparse
import json
import sys
import random
import io
import zipfile
import csv
from pathlib import Path
from collections import Counter, defaultdict

import numpy as np
import torch
import torch.nn.functional as F
from torch_geometric.data import Data

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_manifest(manifest_path):
    """Load manifest CSV and return dict of {key: label}."""
    manifest = {}
    with open(manifest_path, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            # Try different column names
            key = row.get('key') or row.get('function_key') or row.get('id') or row.get('name')
            label = row.get('label') or row.get('target') or row.get('vulnerable') or row.get('y')
            
            if key and label is not None:
                # Handle different label formats
                if isinstance(label, str):
                    label = label.strip().lower()
                    if label in ['1', 'true', 'yes', 'vulnerable']:
                        label = 1
                    elif label in ['0', 'false', 'no', 'safe']:
                        label = 0
                    else:
                        try:
                            label = int(label)
                        except:
                            continue
                manifest[key] = int(label)
    
    return manifest


def load_cached_data(cache_dir, dataset_name, cache_sig, split, max_samples=None):
    """Load cached PyG data with filenames."""
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            
            for pt_name in tqdm(pt_files[:max_samples] if max_samples else pt_files, desc=f"Loading {split}"):
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            # Extract key from filename
                            key = pt_name.replace('.pt', '').replace('/', '_')
                            samples.append((key, data))
                except Exception as e:
                    print(f"  Error loading {pt_name}: {e}")
                    continue
    
    return samples


def check_label_distribution(samples):
    """Check label distribution in cached data."""
    print("\n" + "=" * 60)
    print("LABEL DISTRIBUTION IN CACHED DATA")
    print("=" * 60)
    
    labels = [s[1].y.item() if s[1].y.numel() == 1 else s[1].y[0].item() for s in samples]
    counter = Counter(labels)
    
    print(f"Total samples: {len(samples)}")
    for label, count in sorted(counter.items()):
        print(f"  Label {label}: {count} ({count/len(samples)*100:.1f}%)")
    
    # Check for unusual labels
    unusual = [l for l in labels if l not in [0, 1]]
    if unusual:
        print(f"  ⚠️ UNUSUAL LABELS FOUND: {set(unusual)}")
    
    return labels


def check_feature_uniqueness(samples, num_check=100):
    """Check if different graphs have different features."""
    print("\n" + "=" * 60)
    print("FEATURE UNIQUENESS CHECK")
    print("=" * 60)
    
    # Get graph-level representations (mean of node features)
    graph_means = []
    for key, data in samples[:num_check]:
        x = data.x.float()
        graph_mean = x.mean(dim=0)  # [feat_dim]
        graph_means.append(graph_mean)
    
    graph_means = torch.stack(graph_means)  # [num_graphs, feat_dim]
    
    # Check pairwise similarity
    # Normalize
    graph_means_norm = F.normalize(graph_means, dim=1)
    similarity_matrix = torch.mm(graph_means_norm, graph_means_norm.t())
    
    # Get upper triangle (excluding diagonal)
    mask = torch.triu(torch.ones_like(similarity_matrix), diagonal=1).bool()
    similarities = similarity_matrix[mask]
    
    print(f"Checked {num_check} graphs")
    print(f"Mean cosine similarity: {similarities.mean():.4f}")
    print(f"Std cosine similarity: {similarities.std():.4f}")
    print(f"Min similarity: {similarities.min():.4f}")
    print(f"Max similarity: {similarities.max():.4f}")
    
    # Count highly similar pairs
    high_sim_threshold = 0.99
    high_sim_count = (similarities > high_sim_threshold).sum().item()
    total_pairs = len(similarities)
    
    if high_sim_count > total_pairs * 0.1:
        print(f"  🚨 WARNING: {high_sim_count}/{total_pairs} pairs ({high_sim_count/total_pairs*100:.1f}%) have similarity > {high_sim_threshold}")
        print(f"     This suggests many graphs have nearly IDENTICAL features!")
    else:
        print(f"  ✅ Only {high_sim_count}/{total_pairs} pairs have very high similarity")
    
    return similarities


def check_label_feature_correlation(samples, num_check=500):
    """Check if there's ANY correlation between features and labels."""
    print("\n" + "=" * 60)
    print("FEATURE-LABEL CORRELATION CHECK")
    print("=" * 60)
    
    safe_means = []
    vuln_means = []
    
    for key, data in samples[:num_check]:
        x = data.x.float()
        label = data.y.item() if data.y.numel() == 1 else data.y[0].item()
        graph_mean = x.mean(dim=0)
        
        if label == 0:
            safe_means.append(graph_mean)
        else:
            vuln_means.append(graph_mean)
    
    if not safe_means or not vuln_means:
        print("  ❌ Not enough samples of both classes!")
        return
    
    safe_means = torch.stack(safe_means)
    vuln_means = torch.stack(vuln_means)
    
    # Overall statistics
    safe_overall = safe_means.mean(dim=0)
    vuln_overall = vuln_means.mean(dim=0)
    
    # Difference between classes
    diff = (vuln_overall - safe_overall).abs()
    
    print(f"Safe samples: {len(safe_means)}, Vuln samples: {len(vuln_means)}")
    print(f"\nMean feature values:")
    print(f"  Safe: {safe_overall.mean():.4f} ± {safe_overall.std():.4f}")
    print(f"  Vuln: {vuln_overall.mean():.4f} ± {vuln_overall.std():.4f}")
    print(f"  Difference: {diff.mean():.4f}")
    
    # Check per-dimension differences
    significant_dims = (diff > 0.01).sum().item()
    print(f"\nDimensions with |diff| > 0.01: {significant_dims}/{len(diff)}")
    
    # Top differing dimensions
    top_diff_dims = diff.topk(10)
    print(f"\nTop 10 most different dimensions:")
    for idx, val in zip(top_diff_dims.indices.tolist(), top_diff_dims.values.tolist()):
        print(f"  Dim {idx}: diff={val:.4f}")
    
    # Statistical test: Can we separate classes using simple mean?
    safe_norms = safe_means.norm(dim=1)
    vuln_norms = vuln_means.norm(dim=1)
    
    print(f"\nL2 norm of graph embeddings:")
    print(f"  Safe: {safe_norms.mean():.4f} ± {safe_norms.std():.4f}")
    print(f"  Vuln: {vuln_norms.mean():.4f} ± {vuln_norms.std():.4f}")
    
    # Simple linear separability test
    from sklearn.linear_model import LogisticRegression
    from sklearn.metrics import roc_auc_score
    
    X = torch.cat([safe_means, vuln_means], dim=0).numpy()
    y = np.array([0] * len(safe_means) + [1] * len(vuln_means))
    
    # Shuffle
    perm = np.random.permutation(len(y))
    X, y = X[perm], y[perm]
    
    # Train/test split
    split = int(0.8 * len(y))
    X_train, X_test = X[:split], X[split:]
    y_train, y_test = y[:split], y[split:]
    
    try:
        clf = LogisticRegression(max_iter=1000, random_state=42)
        clf.fit(X_train, y_train)
        probs = clf.predict_proba(X_test)[:, 1]
        auc = roc_auc_score(y_test, probs)
        
        print(f"\nLogistic Regression on mean features:")
        print(f"  Test AUC: {auc:.4f}")
        
        if auc > 0.55:
            print(f"  ✅ Some signal exists in mean features")
        elif auc > 0.52:
            print(f"  ⚠️ Very weak signal")
        else:
            print(f"  ❌ NO SIGNAL in mean features!")
    except Exception as e:
        print(f"  Error in LogisticRegression: {e}")


def inspect_samples(samples, num_inspect=5):
    """Print details of a few samples for manual inspection."""
    print("\n" + "=" * 60)
    print("SAMPLE INSPECTION")
    print("=" * 60)
    
    # Get some safe and some vulnerable
    safe_samples = [(k, d) for k, d in samples if (d.y.item() if d.y.numel() == 1 else d.y[0].item()) == 0]
    vuln_samples = [(k, d) for k, d in samples if (d.y.item() if d.y.numel() == 1 else d.y[0].item()) == 1]
    
    print(f"\n--- SAFE SAMPLES (label=0) ---")
    for key, data in safe_samples[:num_inspect]:
        x = data.x
        print(f"\nKey: {key}")
        print(f"  Nodes: {x.size(0)}, Features: {x.size(1)}")
        print(f"  Edges: {data.edge_index.size(1)}")
        print(f"  Label: {data.y}")
        print(f"  Feature mean: {x.float().mean():.4f}, std: {x.float().std():.4f}")
        print(f"  Feature range: [{x.float().min():.4f}, {x.float().max():.4f}]")
        
        # Check one-hot part
        onehot = x[:, :28]
        embedding = x[:, 28:]
        print(f"  One-hot part: sum={onehot.sum():.0f}, expected={x.size(0)} (one per node)")
        print(f"  Embedding part: mean={embedding.float().mean():.4f}, std={embedding.float().std():.4f}")
    
    print(f"\n--- VULNERABLE SAMPLES (label=1) ---")
    for key, data in vuln_samples[:num_inspect]:
        x = data.x
        print(f"\nKey: {key}")
        print(f"  Nodes: {x.size(0)}, Features: {x.size(1)}")
        print(f"  Edges: {data.edge_index.size(1)}")
        print(f"  Label: {data.y}")
        print(f"  Feature mean: {x.float().mean():.4f}, std: {x.float().std():.4f}")
        print(f"  Feature range: [{x.float().min():.4f}, {x.float().max():.4f}]")
        
        onehot = x[:, :28]
        embedding = x[:, 28:]
        print(f"  One-hot part: sum={onehot.sum():.0f}, expected={x.size(0)}")
        print(f"  Embedding part: mean={embedding.float().mean():.4f}, std={embedding.float().std():.4f}")


def check_manifest_alignment(samples, manifest_path, num_check=100):
    """Check if manifest labels match cached data labels."""
    print("\n" + "=" * 60)
    print("MANIFEST ALIGNMENT CHECK")
    print("=" * 60)
    
    if not manifest_path or not Path(manifest_path).exists():
        print("  ⚠️ No manifest path provided or file not found")
        return
    
    manifest = load_manifest(manifest_path)
    print(f"Loaded {len(manifest)} entries from manifest")
    
    # Show manifest label distribution
    manifest_labels = list(manifest.values())
    print(f"Manifest labels: {Counter(manifest_labels)}")
    
    # Try to match cached data keys to manifest
    matches = 0
    mismatches = 0
    not_found = 0
    
    for key, data in samples[:num_check]:
        cached_label = data.y.item() if data.y.numel() == 1 else data.y[0].item()
        
        # Try different key formats
        manifest_label = None
        for try_key in [key, key.replace('_', '/'), key.split('_')[-1]]:
            if try_key in manifest:
                manifest_label = manifest[try_key]
                break
        
        if manifest_label is not None:
            if manifest_label == cached_label:
                matches += 1
            else:
                mismatches += 1
                if mismatches <= 5:
                    print(f"  MISMATCH: {key} - cached={cached_label}, manifest={manifest_label}")
        else:
            not_found += 1
    
    print(f"\nChecked {num_check} samples:")
    print(f"  Matches: {matches}")
    print(f"  Mismatches: {mismatches}")
    print(f"  Not found in manifest: {not_found}")
    
    if mismatches > 0:
        print(f"  🚨 LABEL MISMATCH DETECTED!")
    elif not_found > num_check * 0.5:
        print(f"  ⚠️ Many keys not found - manifest format may differ from cache keys")


def check_graph_structure(samples, num_check=100):
    """Check graph structure integrity."""
    print("\n" + "=" * 60)
    print("GRAPH STRUCTURE CHECK")
    print("=" * 60)
    
    issues = []
    
    for key, data in samples[:num_check]:
        num_nodes = data.x.size(0)
        edge_index = data.edge_index
        
        # Check edge indices are valid
        if edge_index.numel() > 0:
            max_idx = edge_index.max().item()
            min_idx = edge_index.min().item()
            
            if max_idx >= num_nodes:
                issues.append(f"{key}: edge index {max_idx} >= num_nodes {num_nodes}")
            if min_idx < 0:
                issues.append(f"{key}: negative edge index {min_idx}")
        
        # Check for self-loops
        if edge_index.size(1) > 0:
            self_loops = (edge_index[0] == edge_index[1]).sum().item()
            if self_loops > num_nodes * 0.5:
                issues.append(f"{key}: many self-loops ({self_loops}/{edge_index.size(1)})")
    
    if issues:
        print(f"Found {len(issues)} issues:")
        for issue in issues[:10]:
            print(f"  - {issue}")
    else:
        print(f"  ✅ All {num_check} graphs have valid structure")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--manifest", type=Path, default=None,
                       help="Path to manifest CSV for alignment check")
    parser.add_argument("--max-samples", type=int, default=1000)
    parser.add_argument("--split", type=str, default="train")
    args = parser.parse_args()
    
    print("=" * 60)
    print("DATA INTEGRITY DIAGNOSTIC")
    print("=" * 60)
    
    # Load cached data
    samples = load_cached_data(
        args.cache_dir, args.dataset_name, args.cache_signature,
        args.split, args.max_samples
    )
    
    if not samples:
        print("❌ No samples loaded!")
        sys.exit(1)
    
    print(f"\nLoaded {len(samples)} samples")
    
    # Run checks
    labels = check_label_distribution(samples)
    check_feature_uniqueness(samples)
    check_label_feature_correlation(samples)
    check_graph_structure(samples)
    inspect_samples(samples)
    
    if args.manifest:
        check_manifest_alignment(samples, args.manifest)
    
    # Final summary
    print("\n" + "=" * 60)
    print("SUMMARY")
    print("=" * 60)
    print("""
Key questions to investigate:
1. Are the labels correctly aligned with the source code?
2. Does the vulnerability ACTUALLY exist in the code?
3. Is the CPG capturing the vulnerability pattern?
4. Are different functions producing different embeddings?

If LogisticRegression AUC < 0.55 on mean features, the problem is:
- Labels are wrong/misaligned, OR
- GraphCodeBERT embeddings don't capture vulnerability, OR
- Mean pooling destroys the signal

Next steps:
- Manually inspect 10 samples to verify labels
- Check if vulnerability is visible in the source code
- Try a simpler baseline: text classification on raw code
""")


if __name__ == "__main__":
    main()

"""
python diagnose_data_integrity.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --max-samples 1000

"""    