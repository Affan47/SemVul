#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
diagnose_data.py - Analyze PyG cached data for issues causing model collapse

This script performs comprehensive analysis of:
1. Feature distribution (embeddings vs one-hot)
2. Embedding sparsity (how many zeros?)
3. Node connectivity
4. Label distribution
5. Feature variance per dimension

Run this BEFORE training to catch data issues.

Usage:
    python diagnose_data.py \
        --cache-dir "/path/to/cache" \
        --dataset-name "devign_normfunc_v2" \
        --cache-signature "caffd6ae8652870d" \
        --split train \
        --sample-size 500
"""

import argparse
import json
import random
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import numpy as np
import torch

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_cached_sample(
    cache_dir: Path,
    dataset_name: str,
    cache_sig: str,
    split: str,
    sample_size: int = 500,
) -> List[torch.Tensor]:
    """Load a sample of cached PyG data objects."""
    
    split_dir = cache_dir / dataset_name / split / cache_sig[:16]
    
    # Check for ZIP file first
    zip_path = split_dir / f"cache_{split}.zip"
    objects_dir = split_dir / "objects"
    
    samples = []
    
    if zip_path.exists():
        import zipfile
        print(f"[INFO] Loading from ZIP: {zip_path}")
        
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')]
            
            if sample_size and sample_size < len(pt_files):
                pt_files = random.sample(pt_files, sample_size)
            
            for pt_name in tqdm(pt_files, desc="Loading samples"):
                try:
                    with zf.open(pt_name) as f:
                        import io
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        samples.append(data)
                except Exception as e:
                    print(f"[WARN] Failed to load {pt_name}: {e}")
    
    elif objects_dir.exists():
        print(f"[INFO] Loading from directory: {objects_dir}")
        
        pt_files = list(objects_dir.rglob("*.pt"))
        
        if sample_size and sample_size < len(pt_files):
            pt_files = random.sample(pt_files, sample_size)
        
        for pt_path in tqdm(pt_files, desc="Loading samples"):
            try:
                data = torch.load(pt_path, map_location='cpu')
                samples.append(data)
            except Exception as e:
                print(f"[WARN] Failed to load {pt_path}: {e}")
    
    else:
        print(f"[ERROR] No cache found at {split_dir}")
        sys.exit(1)
    
    print(f"[INFO] Loaded {len(samples)} samples")
    return samples


def analyze_features(samples: List, one_hot_dim: int = 28, emb_dim: int = 768) -> Dict:
    """Analyze node feature distributions."""
    
    results = {
        "total_nodes": 0,
        "total_graphs": len(samples),
        "feature_dim": None,
        "one_hot_stats": {},
        "embedding_stats": {},
        "per_dim_variance": None,
        "zero_rows": 0,
        "sparse_rows": 0,  # Rows with >90% zeros
        "label_distribution": Counter(),
    }
    
    all_features = []
    
    for data in tqdm(samples, desc="Analyzing features"):
        if not hasattr(data, 'x') or data.x is None:
            continue
        
        x = data.x.float()
        results["total_nodes"] += x.size(0)
        
        if results["feature_dim"] is None:
            results["feature_dim"] = x.size(1)
        
        all_features.append(x)
        
        # Label distribution
        if hasattr(data, 'y') and data.y is not None:
            label = int(data.y.item()) if data.y.numel() == 1 else int(data.y[0].item())
            results["label_distribution"][label] += 1
    
    if not all_features:
        return results
    
    # Concatenate all features
    all_x = torch.cat(all_features, dim=0)
    total_dim = all_x.size(1)
    
    print(f"\n[FEATURE ANALYSIS] Total nodes: {all_x.size(0)}, Feature dim: {total_dim}")
    
    # Check if this is concat format (one-hot + embedding)
    if total_dim == one_hot_dim + emb_dim:
        oh_part = all_x[:, :one_hot_dim]
        emb_part = all_x[:, one_hot_dim:]
        
        print(f"\n=== ONE-HOT PART (dims 0-{one_hot_dim-1}) ===")
        oh_sum = oh_part.sum(dim=1)
        oh_nonzero = (oh_part != 0).sum(dim=1).float()
        
        results["one_hot_stats"] = {
            "mean_sum": oh_sum.mean().item(),
            "std_sum": oh_sum.std().item(),
            "mean_nonzero_per_row": oh_nonzero.mean().item(),
            "all_zero_rows": (oh_sum == 0).sum().item(),
            "proper_one_hot": (oh_sum == 1).sum().item(),  # Exactly one 1 per row
        }
        
        print(f"  Mean sum per row: {results['one_hot_stats']['mean_sum']:.4f}")
        print(f"  Rows with exactly one 1: {results['one_hot_stats']['proper_one_hot']} / {all_x.size(0)}")
        print(f"  All-zero rows: {results['one_hot_stats']['all_zero_rows']}")
        
        print(f"\n=== EMBEDDING PART (dims {one_hot_dim}-{total_dim-1}) ===")
        emb_norm = emb_part.norm(dim=1)
        emb_zeros = (emb_part == 0).sum(dim=1).float()
        emb_all_zero = (emb_norm < 1e-6).sum().item()
        
        results["embedding_stats"] = {
            "mean_l2_norm": emb_norm.mean().item(),
            "std_l2_norm": emb_norm.std().item(),
            "min_l2_norm": emb_norm.min().item(),
            "max_l2_norm": emb_norm.max().item(),
            "all_zero_rows": emb_all_zero,
            "all_zero_pct": 100.0 * emb_all_zero / all_x.size(0),
            "mean_zeros_per_row": emb_zeros.mean().item(),
            "mean_zeros_pct": 100.0 * emb_zeros.mean().item() / emb_dim,
        }
        
        print(f"  Mean L2 norm: {results['embedding_stats']['mean_l2_norm']:.4f}")
        print(f"  L2 norm range: [{results['embedding_stats']['min_l2_norm']:.4f}, {results['embedding_stats']['max_l2_norm']:.4f}]")
        print(f"  🚨 ALL-ZERO EMBEDDING ROWS: {emb_all_zero} / {all_x.size(0)} ({results['embedding_stats']['all_zero_pct']:.1f}%)")
        print(f"  Mean zeros per row: {results['embedding_stats']['mean_zeros_per_row']:.1f} / {emb_dim} ({results['embedding_stats']['mean_zeros_pct']:.1f}%)")
        
        # Check specific embedding positions
        print(f"\n=== EMBEDDING VALUE DISTRIBUTION ===")
        emb_flat = emb_part.flatten()
        print(f"  Min: {emb_flat.min().item():.6f}")
        print(f"  Max: {emb_flat.max().item():.6f}")
        print(f"  Mean: {emb_flat.mean().item():.6f}")
        print(f"  Std: {emb_flat.std().item():.6f}")
        print(f"  Zeros: {(emb_flat == 0).sum().item()} / {emb_flat.numel()} ({100.0 * (emb_flat == 0).sum().item() / emb_flat.numel():.1f}%)")
    
    # Per-dimension variance
    print(f"\n=== PER-DIMENSION VARIANCE ===")
    dim_var = all_x.var(dim=0)
    results["per_dim_variance"] = {
        "mean": dim_var.mean().item(),
        "min": dim_var.min().item(),
        "max": dim_var.max().item(),
        "zero_variance_dims": (dim_var < 1e-8).sum().item(),
    }
    
    print(f"  Mean variance: {results['per_dim_variance']['mean']:.6f}")
    print(f"  Variance range: [{results['per_dim_variance']['min']:.6f}, {results['per_dim_variance']['max']:.6f}]")
    print(f"  🚨 ZERO-VARIANCE DIMENSIONS: {results['per_dim_variance']['zero_variance_dims']} / {total_dim}")
    
    # Find dead dimensions
    dead_dims = torch.where(dim_var < 1e-8)[0].tolist()
    if dead_dims:
        print(f"  Dead dimension indices (first 20): {dead_dims[:20]}")
        
        # Check if dead dims are in embedding part
        if total_dim == one_hot_dim + emb_dim:
            dead_in_emb = [d for d in dead_dims if d >= one_hot_dim]
            dead_in_oh = [d for d in dead_dims if d < one_hot_dim]
            print(f"    - In one-hot part: {len(dead_in_oh)}")
            print(f"    - In embedding part: {len(dead_in_emb)}")
    
    # Row sparsity analysis
    print(f"\n=== ROW SPARSITY ===")
    zero_per_row = (all_x == 0).sum(dim=1).float()
    sparse_threshold = 0.9 * total_dim
    
    results["zero_rows"] = (zero_per_row == total_dim).sum().item()
    results["sparse_rows"] = (zero_per_row > sparse_threshold).sum().item()
    
    print(f"  Completely zero rows: {results['zero_rows']} / {all_x.size(0)}")
    print(f"  >90% zero rows: {results['sparse_rows']} / {all_x.size(0)}")
    
    return results


def analyze_graph_structure(samples: List) -> Dict:
    """Analyze graph connectivity."""
    
    results = {
        "nodes_per_graph": [],
        "edges_per_graph": [],
        "edge_types": Counter(),
        "disconnected_graphs": 0,
        "avg_degree": [],
    }
    
    for data in tqdm(samples, desc="Analyzing structure"):
        num_nodes = data.x.size(0) if hasattr(data, 'x') and data.x is not None else 0
        num_edges = data.edge_index.size(1) if hasattr(data, 'edge_index') and data.edge_index is not None else 0
        
        results["nodes_per_graph"].append(num_nodes)
        results["edges_per_graph"].append(num_edges)
        
        if num_nodes > 0 and num_edges > 0:
            results["avg_degree"].append(2 * num_edges / num_nodes)
        
        # Edge type distribution
        if hasattr(data, 'edge_type') and data.edge_type is not None:
            for et in data.edge_type.tolist():
                results["edge_types"][et] += 1
        elif hasattr(data, 'edge_attr') and data.edge_attr is not None:
            for et in data.edge_attr.tolist():
                results["edge_types"][et] += 1
        
        # Check for disconnected graphs (no edges)
        if num_edges == 0 and num_nodes > 1:
            results["disconnected_graphs"] += 1
    
    print(f"\n=== GRAPH STRUCTURE ===")
    print(f"  Nodes per graph: {np.mean(results['nodes_per_graph']):.1f} ± {np.std(results['nodes_per_graph']):.1f}")
    print(f"  Edges per graph: {np.mean(results['edges_per_graph']):.1f} ± {np.std(results['edges_per_graph']):.1f}")
    print(f"  Avg degree: {np.mean(results['avg_degree']):.2f}")
    print(f"  Disconnected graphs: {results['disconnected_graphs']} / {len(samples)}")
    
    if results["edge_types"]:
        print(f"\n  Edge type distribution:")
        for et, count in sorted(results["edge_types"].items()):
            print(f"    Type {et}: {count} ({100.0 * count / sum(results['edge_types'].values()):.1f}%)")
    
    return results


def diagnose_problems(feature_results: Dict, structure_results: Dict) -> List[str]:
    """Generate list of problems found."""
    
    problems = []
    
    # Feature problems
    if feature_results.get("embedding_stats", {}).get("all_zero_pct", 0) > 50:
        problems.append(
            f"🚨 CRITICAL: {feature_results['embedding_stats']['all_zero_pct']:.1f}% of embedding rows are ALL ZEROS! "
            "This means most nodes have no semantic information - check embedding lookup."
        )
    
    if feature_results.get("embedding_stats", {}).get("all_zero_pct", 0) > 90:
        problems.append(
            "🚨 CRITICAL: >90% zero embeddings - the model is essentially only seeing one-hot features. "
            "Check: 1) Text extraction working? 2) SHA256 normalization matching? 3) Embeddings in DB?"
        )
    
    zero_var_dims = feature_results.get("per_dim_variance", {}).get("zero_variance_dims", 0)
    total_dim = feature_results.get("feature_dim", 1)
    if zero_var_dims > total_dim * 0.5:
        problems.append(
            f"🚨 CRITICAL: {zero_var_dims}/{total_dim} dimensions have ZERO variance! "
            "The model cannot learn from constant features."
        )
    
    # Label imbalance
    label_dist = feature_results.get("label_distribution", {})
    if label_dist:
        total = sum(label_dist.values())
        for label, count in label_dist.items():
            pct = 100.0 * count / total
            if pct < 10 or pct > 90:
                problems.append(
                    f"⚠️ WARNING: Label {label} has {pct:.1f}% of samples - severe class imbalance."
                )
    
    # Structure problems
    if structure_results.get("disconnected_graphs", 0) > len(structure_results.get("nodes_per_graph", [])) * 0.1:
        problems.append(
            f"⚠️ WARNING: {structure_results['disconnected_graphs']} graphs have NO edges. "
            "Check edge extraction in cpg_config.py."
        )
    
    avg_degree = np.mean(structure_results.get("avg_degree", [1]))
    if avg_degree < 2:
        problems.append(
            f"⚠️ WARNING: Average node degree is {avg_degree:.2f} - graphs are very sparse. "
            "GNN message passing will be limited."
        )
    
    return problems


def main():
    parser = argparse.ArgumentParser(description="Diagnose PyG cached data for training issues")
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--split", type=str, default="train", choices=["train", "valid", "test"])
    parser.add_argument("--sample-size", type=int, default=500)
    parser.add_argument("--one-hot-dim", type=int, default=28)
    parser.add_argument("--emb-dim", type=int, default=768)
    args = parser.parse_args()
    
    print("=" * 70)
    print("DATA DIAGNOSTICS")
    print("=" * 70)
    print(f"Cache: {args.cache_dir}")
    print(f"Dataset: {args.dataset_name}")
    print(f"Signature: {args.cache_signature}")
    print(f"Split: {args.split}")
    print("=" * 70)
    
    # Load samples
    samples = load_cached_sample(
        args.cache_dir,
        args.dataset_name,
        args.cache_signature,
        args.split,
        args.sample_size,
    )
    
    if not samples:
        print("[ERROR] No samples loaded!")
        sys.exit(1)
    
    # Analyze features
    feature_results = analyze_features(samples, args.one_hot_dim, args.emb_dim)
    
    # Analyze structure
    structure_results = analyze_graph_structure(samples)
    
    # Label distribution
    print(f"\n=== LABEL DISTRIBUTION ===")
    for label, count in sorted(feature_results["label_distribution"].items()):
        total = sum(feature_results["label_distribution"].values())
        print(f"  Label {label}: {count} ({100.0 * count / total:.1f}%)")
    
    # Diagnose problems
    print("\n" + "=" * 70)
    print("DIAGNOSIS")
    print("=" * 70)
    
    problems = diagnose_problems(feature_results, structure_results)
    
    if problems:
        for i, problem in enumerate(problems, 1):
            print(f"\n{i}. {problem}")
    else:
        print("\n✅ No obvious problems detected!")
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"Total graphs: {feature_results['total_graphs']}")
    print(f"Total nodes: {feature_results['total_nodes']}")
    print(f"Feature dimension: {feature_results['feature_dim']}")
    print(f"Expected: {args.one_hot_dim} (one-hot) + {args.emb_dim} (embedding) = {args.one_hot_dim + args.emb_dim}")
    
    if feature_results.get("embedding_stats"):
        print(f"\nEmbedding coverage: {100.0 - feature_results['embedding_stats']['all_zero_pct']:.1f}% of nodes have embeddings")
    
    print("\n" + "=" * 70)


if __name__ == "__main__":
    main()



"""
python diagnose_data.py \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name "devign_normfunc_v2" \
    --cache-signature "caffd6ae8652870d" \
    --split train \
    --sample-size 1000 \
    --one-hot-dim 28 \
    --emb-dim 768

"""