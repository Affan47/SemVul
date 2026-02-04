#!/usr/bin/env python3
"""
analyze_feature_parts.py - Check which part of features is causing high similarity
"""

import argparse
import io
import zipfile
from pathlib import Path
import torch
import torch.nn.functional as F
import numpy as np

try:
    from tqdm import tqdm
except ImportError:
    def tqdm(x, **kwargs):
        return x


def load_samples(cache_dir, dataset_name, cache_sig, split="train", num_samples=100):
    split_dir = Path(cache_dir) / dataset_name / split / cache_sig[:16]
    zip_path = split_dir / f"cache_{split}.zip"
    
    samples = []
    if zip_path.exists():
        with zipfile.ZipFile(zip_path, 'r') as zf:
            pt_files = [n for n in zf.namelist() if n.endswith('.pt')][:num_samples]
            for pt_name in pt_files:
                try:
                    with zf.open(pt_name) as f:
                        data = torch.load(io.BytesIO(f.read()), map_location='cpu')
                        if hasattr(data, 'y') and data.y is not None:
                            samples.append(data)
                except:
                    continue
    return samples


def analyze_similarity(features, name):
    """Analyze similarity of a set of features."""
    # Normalize
    features_norm = F.normalize(features, dim=1)
    
    # Pairwise similarity
    sim_matrix = torch.mm(features_norm, features_norm.t())
    
    # Upper triangle (excluding diagonal)
    mask = torch.triu(torch.ones_like(sim_matrix), diagonal=1).bool()
    similarities = sim_matrix[mask]
    
    print(f"\n{name}:")
    print(f"  Shape: {features.shape}")
    print(f"  Mean similarity: {similarities.mean():.4f}")
    print(f"  Std similarity: {similarities.std():.4f}")
    print(f"  Min: {similarities.min():.4f}, Max: {similarities.max():.4f}")
    print(f"  Pairs > 0.99: {(similarities > 0.99).sum().item()}/{len(similarities)} ({(similarities > 0.99).float().mean()*100:.1f}%)")
    
    return similarities.mean().item()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cache-dir", type=Path, required=True)
    parser.add_argument("--dataset-name", type=str, required=True)
    parser.add_argument("--cache-signature", type=str, required=True)
    parser.add_argument("--num-samples", type=int, default=100)
    args = parser.parse_args()
    
    print("=" * 60)
    print("FEATURE COMPONENT ANALYSIS")
    print("=" * 60)
    
    samples = load_samples(args.cache_dir, args.dataset_name, args.cache_signature, "train", args.num_samples)
    print(f"Loaded {len(samples)} samples")
    
    # Compute mean features per graph
    full_means = []
    onehot_means = []
    embed_means = []
    
    for data in samples:
        x = data.x.float()
        full_means.append(x.mean(dim=0))
        onehot_means.append(x[:, :28].mean(dim=0))
        embed_means.append(x[:, 28:].mean(dim=0))
    
    full_means = torch.stack(full_means)
    onehot_means = torch.stack(onehot_means)
    embed_means = torch.stack(embed_means)
    
    print("\n" + "=" * 60)
    print("SIMILARITY BY COMPONENT")
    print("=" * 60)
    
    sim_full = analyze_similarity(full_means, "FULL FEATURES (796 dims)")
    sim_onehot = analyze_similarity(onehot_means, "ONE-HOT ONLY (28 dims)")
    sim_embed = analyze_similarity(embed_means, "EMBEDDING ONLY (768 dims)")
    
    print("\n" + "=" * 60)
    print("DIAGNOSIS")
    print("=" * 60)
    
    if sim_onehot > sim_embed:
        print(f"One-hot part is MORE similar ({sim_onehot:.3f} vs {sim_embed:.3f})")
        print("→ Consider using only embedding features (dims 28-795)")
    else:
        print(f"Embedding part is MORE similar ({sim_embed:.3f} vs {sim_onehot:.3f})")
        print("→ GraphCodeBERT produces similar embeddings for different code")
    
    # Check variance per dimension
    print("\n" + "=" * 60)
    print("PER-DIMENSION VARIANCE")
    print("=" * 60)
    
    full_var = full_means.var(dim=0)
    onehot_var = onehot_means.var(dim=0)
    embed_var = embed_means.var(dim=0)
    
    print(f"Full: mean var = {full_var.mean():.6f}, max = {full_var.max():.4f}")
    print(f"One-hot: mean var = {onehot_var.mean():.6f}, max = {onehot_var.max():.4f}")
    print(f"Embedding: mean var = {embed_var.mean():.6f}, max = {embed_var.max():.4f}")
    
    # Top varying dimensions
    top_dims = embed_var.topk(10)
    print(f"\nTop 10 varying embedding dimensions:")
    for idx, var in zip(top_dims.indices.tolist(), top_dims.values.tolist()):
        print(f"  Dim {idx+28}: variance = {var:.4f}")
    
    # Check if there's signal correlation with labels
    print("\n" + "=" * 60)
    print("LABEL CORRELATION (embedding only)")
    print("=" * 60)
    
    labels = torch.tensor([d.y.item() if d.y.numel() == 1 else d.y[0].item() for d in samples])
    safe_embeds = embed_means[labels == 0]
    vuln_embeds = embed_means[labels == 1]
    
    if len(safe_embeds) > 0 and len(vuln_embeds) > 0:
        diff = (vuln_embeds.mean(dim=0) - safe_embeds.mean(dim=0)).abs()
        top_diff = diff.topk(10)
        
        print(f"Safe: {len(safe_embeds)}, Vuln: {len(vuln_embeds)}")
        print(f"\nTop 10 dimensions with class difference:")
        for idx, d in zip(top_diff.indices.tolist(), top_diff.values.tolist()):
            print(f"  Dim {idx+28}: diff = {d:.4f}")
        
        # Try classification with just top-K dimensions
        from sklearn.linear_model import LogisticRegression
        from sklearn.metrics import roc_auc_score
        
        top_k = 50
        top_indices = diff.topk(top_k).indices
        
        X = embed_means[:, top_indices].numpy()
        y = labels.numpy()
        
        clf = LogisticRegression(max_iter=1000)
        clf.fit(X, y)
        probs = clf.predict_proba(X)[:, 1]
        auc = roc_auc_score(y, probs)
        
        print(f"\nLogistic Regression on top-{top_k} dims: AUC = {auc:.4f}")


if __name__ == "__main__":
    main()


"""
python analyze_feature_parts.py \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d"

"""    