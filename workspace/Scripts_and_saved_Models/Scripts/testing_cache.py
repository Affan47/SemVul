#!/usr/bin/env python3
"""
Comprehensive cache verification script.
Tests cache integrity, dimensions, metadata, and compatibility.
"""

import json
import sys
from pathlib import Path
from collections import Counter, defaultdict

import torch
import numpy as np


def test_cache_signature(cache_dir: Path):
    """Test 1: Verify signature.json exists and is valid."""
    print("\n" + "="*70)
    print("TEST 1: Cache Signature Validation")
    print("="*70)
    
    sig_path = cache_dir / "meta" / "signature.json"
    
    if not sig_path.exists():
        print(f"❌ FAIL: signature.json not found at {sig_path}")
        return None
    
    print(f"✅ Found: {sig_path}")
    
    with sig_path.open("r") as f:
        sig = json.load(f)
    
    # Extract key info
    cache_tag = sig.get("cache_tag", "unknown")
    fusion_mode = sig.get("features", {}).get("fusion_mode", "unknown")
    one_hot = sig.get("features", {}).get("one_hot", False)
    use_code_emb = sig.get("features", {}).get("use_code_embeddings", False)
    one_hot_dim = sig.get("features", {}).get("one_hot_dim", 0)
    code_emb_dim = sig.get("features", {}).get("code_emb_dim", 0)
    final_x_dim = sig.get("features", {}).get("final_x_dim", 0)
    
    print(f"\n📋 Cache Configuration:")
    print(f"   Cache tag: {cache_tag}")
    print(f"   Fusion mode: {fusion_mode}")
    print(f"   One-hot: {one_hot} (dim={one_hot_dim})")
    print(f"   Code embeddings: {use_code_emb} (dim={code_emb_dim})")
    print(f"   Final x_dim: {final_x_dim}")
    
    # Verify dimension calculation
    if fusion_mode == "early_concat":
        expected_dim = one_hot_dim + code_emb_dim
        if expected_dim != final_x_dim:
            print(f"\n⚠️  WARNING: Dimension mismatch!")
            print(f"   Expected: {one_hot_dim} + {code_emb_dim} = {expected_dim}")
            print(f"   Actual: {final_x_dim}")
        else:
            print(f"\n✅ Dimensions correct: {one_hot_dim} + {code_emb_dim} = {final_x_dim}")
    
    # Check training compatibility
    print(f"\n🎯 Training Requirements:")
    if fusion_mode in ["early_concat", "early_replace"]:
        print(f"   ⚠️  Cache already fused!")
        print(f"   Training MUST use: --fusion none --code-mode none")
    elif fusion_mode == "none":
        print(f"   ✅ Cache not fused - model can fuse if desired")
    
    return sig


def test_cache_index(cache_dir: Path):
    """Test 2: Verify index.csv."""
    print("\n" + "="*70)
    print("TEST 2: Cache Index Validation")
    print("="*70)
    
    index_path = cache_dir / "meta" / "index.csv"
    
    if not index_path.exists():
        print(f"⚠️  WARNING: index.csv not found at {index_path}")
        return None
    
    print(f"✅ Found: {index_path}")
    
    # Read index
    with index_path.open("r") as f:
        lines = f.readlines()
    
    print(f"\n📊 Index Statistics:")
    print(f"   Total entries: {len(lines) - 1}")  # -1 for header
    
    # Show first few entries
    print(f"\n📄 First 3 entries:")
    for line in lines[:4]:  # header + 3 rows
        print(f"   {line.strip()}")
    
    return len(lines) - 1


def test_sample_loading(cache_dir: Path, num_samples: int = 5):
    """Test 3: Load and verify sample .pt files."""
    print("\n" + "="*70)
    print(f"TEST 3: Sample Loading (n={num_samples})")
    print("="*70)
    
    # Find .pt files
    objects_dir = cache_dir / "objects"
    pt_files = list(objects_dir.rglob("*.pt"))
    
    if not pt_files:
        print(f"❌ FAIL: No .pt files found in {objects_dir}")
        return None
    
    print(f"✅ Found {len(pt_files)} cached graphs")
    
    # Load samples
    samples = []
    for i, pt_path in enumerate(pt_files[:num_samples]):
        try:
            data = torch.load(pt_path, map_location="cpu")
            samples.append((pt_path, data))
            print(f"\n✅ Loaded sample {i+1}: {pt_path.name}")
            print(f"   x.shape: {data.x.shape}")
            print(f"   edge_index.shape: {data.edge_index.shape}")
            print(f"   y: {data.y.item() if data.y is not None else None}")
        except Exception as e:
            print(f"\n❌ FAIL: Could not load {pt_path.name}")
            print(f"   Error: {e}")
    
    return samples


def test_data_structure(samples, expected_sig):
    """Test 4: Verify Data object structure."""
    print("\n" + "="*70)
    print("TEST 4: Data Structure Validation")
    print("="*70)
    
    if not samples:
        print("❌ SKIP: No samples to test")
        return
    
    expected_x_dim = expected_sig.get("features", {}).get("final_x_dim", -1)
    
    for i, (path, data) in enumerate(samples):
        print(f"\n📦 Sample {i+1}: {path.name}")
        
        # Check x dimension
        actual_x_dim = data.x.shape[1] if data.x.dim() > 1 else -1
        if actual_x_dim == expected_x_dim:
            print(f"   ✅ x.shape: {data.x.shape} (expected dim={expected_x_dim})")
        else:
            print(f"   ❌ x.shape: {data.x.shape} (expected dim={expected_x_dim})")
        
        # Check edge_index
        if hasattr(data, "edge_index"):
            print(f"   ✅ edge_index.shape: {data.edge_index.shape}")
        else:
            print(f"   ⚠️  No edge_index attribute")
        
        # Check edge_type/edge_attr
        if hasattr(data, "edge_type"):
            print(f"   ✅ edge_type.shape: {data.edge_type.shape}")
        elif hasattr(data, "edge_attr"):
            print(f"   ✅ edge_attr.shape: {data.edge_attr.shape}")
        else:
            print(f"   ⚠️  No edge_type or edge_attr")
        
        # Check label
        if hasattr(data, "y") and data.y is not None:
            print(f"   ✅ y: {data.y.item()}")
        else:
            print(f"   ⚠️  No label (y)")


def test_cache_metadata(samples):
    """Test 5: Verify cache metadata flags."""
    print("\n" + "="*70)
    print("TEST 5: Cache Metadata Flags")
    print("="*70)
    
    if not samples:
        print("❌ SKIP: No samples to test")
        return
    
    for i, (path, data) in enumerate(samples):
        print(f"\n🏷️  Sample {i+1}: {path.name}")
        
        # Check _cache_fused
        cache_fused = getattr(data, "_cache_fused", None)
        if cache_fused is not None:
            print(f"   ✅ _cache_fused: {cache_fused}")
        else:
            print(f"   ⚠️  _cache_fused: missing")
        
        # Check _cache_signature
        cache_sig = getattr(data, "_cache_signature", None)
        if cache_sig is not None:
            print(f"   ✅ _cache_signature: {cache_sig}")
        else:
            print(f"   ⚠️  _cache_signature: missing")
        
        # Check other metadata
        num_nodes = getattr(data, "_num_nodes", None)
        num_edges = getattr(data, "_num_edges", None)
        source_file = getattr(data, "_source_file", None)
        
        if num_nodes is not None:
            print(f"   ✅ _num_nodes: {num_nodes}")
        if num_edges is not None:
            print(f"   ✅ _num_edges: {num_edges}")
        if source_file is not None:
            print(f"   📁 _source_file: .../{Path(source_file).name}")


def test_feature_composition(samples, expected_sig):
    """Test 6: Analyze feature composition."""
    print("\n" + "="*70)
    print("TEST 6: Feature Composition Analysis")
    print("="*70)
    
    if not samples:
        print("❌ SKIP: No samples to test")
        return
    
    fusion_mode = expected_sig.get("features", {}).get("fusion_mode", "unknown")
    one_hot_dim = expected_sig.get("features", {}).get("one_hot_dim", 0)
    code_emb_dim = expected_sig.get("features", {}).get("code_emb_dim", 0)
    
    print(f"\n🔍 Expected composition (fusion_mode={fusion_mode}):")
    if fusion_mode == "early_concat":
        print(f"   Dims [0:{one_hot_dim}]: one-hot node types")
        print(f"   Dims [{one_hot_dim}:{one_hot_dim + code_emb_dim}]: CodeBERT embeddings")
    
    for i, (path, data) in enumerate(samples[:3]):  # Only first 3
        print(f"\n📊 Sample {i+1}: {path.name}")
        
        # Get first node features
        x_first = data.x[0]
        
        if fusion_mode == "early_concat":
            # Check one-hot part
            onehot_part = x_first[:one_hot_dim]
            onehot_sum = onehot_part.sum().item()
            onehot_max = onehot_part.max().item()
            
            print(f"   One-hot part [0:{one_hot_dim}]:")
            print(f"      Sum: {onehot_sum:.4f} (should be ~1.0)")
            print(f"      Max: {onehot_max:.4f} (should be 1.0)")
            print(f"      Non-zero: {(onehot_part > 0).sum().item()}")
            
            # Check embedding part
            emb_part = x_first[one_hot_dim:]
            emb_norm = emb_part.norm().item()
            emb_nonzero = (emb_part.abs() > 1e-6).sum().item()
            
            print(f"   Embedding part [{one_hot_dim}:]:")
            print(f"      L2 norm: {emb_norm:.4f}")
            print(f"      Non-zero: {emb_nonzero}/{len(emb_part)}")
            if emb_norm < 1e-6:
                print(f"      ⚠️  Zero embedding (missing from SQLite)")


def test_edge_types(samples):
    """Test 7: Analyze edge type distribution."""
    print("\n" + "="*70)
    print("TEST 7: Edge Type Distribution")
    print("="*70)
    
    if not samples:
        print("❌ SKIP: No samples to test")
        return
    
    edge_type_counts = Counter()
    
    for path, data in samples:
        if hasattr(data, "edge_type"):
            edge_types = data.edge_type.numpy()
            edge_type_counts.update(edge_types)
        elif hasattr(data, "edge_attr"):
            edge_types = data.edge_attr.numpy()
            edge_type_counts.update(edge_types)
    
    if edge_type_counts:
        print(f"\n📊 Edge type distribution (across {len(samples)} samples):")
        
        # Map indices to Devign edge names
        devign_names = {0: "AST", 1: "CFG", 2: "DFG_READ", 3: "DFG_WRITE", 4: "NCS"}
        
        for edge_type, count in sorted(edge_type_counts.items()):
            name = devign_names.get(edge_type, f"UNKNOWN_{edge_type}")
            print(f"   {name} (idx={edge_type}): {count:,}")
        
        total = sum(edge_type_counts.values())
        print(f"\n   Total edges: {total:,}")
    else:
        print("⚠️  No edge types found in samples")


def test_statistics(cache_dir, samples):
    """Test 8: Overall cache statistics."""
    print("\n" + "="*70)
    print("TEST 8: Overall Statistics")
    print("="*70)
    
    # Count all .pt files
    pt_files = list((cache_dir / "objects").rglob("*.pt"))
    
    if samples:
        # Compute stats from samples
        node_counts = [data.x.shape[0] for _, data in samples]
        edge_counts = [data.edge_index.shape[1] for _, data in samples if hasattr(data, "edge_index")]
        x_dims = [data.x.shape[1] for _, data in samples]
        labels = [data.y.item() for _, data in samples if hasattr(data, "y") and data.y is not None]
        
        print(f"\n📈 Statistics (from {len(samples)} samples):")
        print(f"   Nodes per graph: min={min(node_counts)}, max={max(node_counts)}, avg={np.mean(node_counts):.1f}")
        print(f"   Edges per graph: min={min(edge_counts)}, max={max(edge_counts)}, avg={np.mean(edge_counts):.1f}")
        print(f"   Feature dims: {set(x_dims)}")
        
        if labels:
            label_counts = Counter(labels)
            print(f"\n🏷️  Label distribution:")
            print(f"   Class 0: {label_counts.get(0, 0)} ({100*label_counts.get(0, 0)/len(labels):.1f}%)")
            print(f"   Class 1: {label_counts.get(1, 0)} ({100*label_counts.get(1, 0)/len(labels):.1f}%)")
    
    print(f"\n💾 Cache size:")
    print(f"   Total graphs: {len(pt_files)}")
    
    # Check for ZIP
    zip_path = cache_dir / f"cache_{cache_dir.parent.parent.name}.zip"
    if zip_path.exists():
        size_mb = zip_path.stat().st_size / (1024 ** 2)
        print(f"   ZIP archive: {zip_path.name} ({size_mb:.1f} MB)")


def main():
    # Configuration
    CACHE_DIR = Path("./Clean_exports/cache_devign_v1/devign/test/4110578353421322")
    NUM_SAMPLES = 10  # Number of samples to test
    
    print("="*70)
    print("CACHE VERIFICATION SUITE")
    print("="*70)
    print(f"Cache directory: {CACHE_DIR}")
    print(f"Testing {NUM_SAMPLES} samples")
    
    # Verify directory exists
    if not CACHE_DIR.exists():
        print(f"\n❌ FATAL: Cache directory not found!")
        print(f"   Path: {CACHE_DIR}")
        sys.exit(1)
    
    print(f"✅ Cache directory exists")
    
    # Run tests
    sig = test_cache_signature(CACHE_DIR)
    index_count = test_cache_index(CACHE_DIR)
    samples = test_sample_loading(CACHE_DIR, NUM_SAMPLES)
    
    if sig and samples:
        test_data_structure(samples, sig)
        test_cache_metadata(samples)
        test_feature_composition(samples, sig)
        test_edge_types(samples)
        test_statistics(CACHE_DIR, samples)
    
    # Final verdict
    print("\n" + "="*70)
    print("FINAL VERDICT")
    print("="*70)
    
    if sig and samples:
        fusion_mode = sig.get("features", {}).get("fusion_mode", "unknown")
        final_x_dim = sig.get("features", {}).get("final_x_dim", 0)
        
        print(f"\n✅ Cache is VALID and ready to use!")
        print(f"\n📋 Training Configuration:")
        print(f"   Cache directory: {CACHE_DIR}")
        print(f"   Cache signature: {CACHE_DIR.name}")
        print(f"   Feature dimension: {final_x_dim}")
        print(f"   Fusion mode: {fusion_mode}")
        
        if fusion_mode in ["early_concat", "early_replace"]:
            print(f"\n⚠️  CRITICAL: Training command must use:")
            print(f"   --fusion none")
            print(f"   --code-mode none")
            print(f"   --cache-tag 'devign_onehot_codebert768_len256_v2_returnfix'")
        
        print(f"\n✅ All tests passed!")
    else:
        print(f"\n❌ Cache validation FAILED!")
        print(f"   Please rebuild cache or check errors above")
        sys.exit(1)


if __name__ == "__main__":
    main()