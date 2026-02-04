import torch
import json
import sys
import numpy as np
from pathlib import Path

def inspect_pt_file(pt_path, output_file):
    report = []
    def log(msg):
        print(msg)
        report.append(str(msg))

    pt_path = Path(pt_path)
    meta_path = pt_path.with_suffix('.meta.json')

    log(f"=== DEBUG REPORT FOR: {pt_path.name} ===")
    log(f"Path: {pt_path}")
    
    # 1. LOAD INTEGRITY
    try:
        data = torch.load(pt_path, map_location='cpu')
        log(f"[PASS] File loaded successfully.")
        log(f"      Type: {type(data)}")
    except Exception as e:
        log(f"[FAIL] Could not load .pt file: {e}")
        return

    # 2. LOAD METADATA
    meta = {}
    if meta_path.exists():
        try:
            with open(meta_path, 'r') as f:
                meta = json.load(f)
            log(f"[PASS] Metadata loaded.")
        except Exception as e:
            log(f"[WARN] Metadata file exists but corrupt: {e}")
    else:
        log(f"[WARN] No corresponding .meta.json found.")

    # 3. NODE FEATURE ANALYSIS
    x = getattr(data, 'x', None)
    if x is not None:
        log(f"\n--- NODE FEATURES (x) ---")
        log(f"Shape: {x.shape} (Nodes x Dim)")
        
        # Verify Dimensions
        expected_dim = meta.get('x_dim', 796)
        if x.shape[1] == expected_dim:
            log(f"[PASS] Dimensions match metadata ({expected_dim}).")
        else:
            log(f"[FAIL] Dimension mismatch! Meta says {expected_dim}, Data has {x.shape[1]}")

        # Analyze Content (Assuming 28 OneHot + 768 CodeBERT)
        if x.shape[1] >= 796:
            one_hot_part = x[:, :28]
            emb_part = x[:, 28:]
            
            log(f"   > One-Hot Section (Cols 0-27):")
            log(f"     Max value: {one_hot_part.max().item()} (Should be 1.0)")
            log(f"     Min value: {one_hot_part.min().item()} (Should be 0.0)")
            
            log(f"   > CodeBERT Section (Cols 28-795):")
            log(f"     Mean: {emb_part.mean().item():.6f}")
            log(f"     Std:  {emb_part.std().item():.6f}")
            
            # Check for Dead Embeddings (All Zeros)
            zero_rows = (emb_part.abs().sum(dim=1) == 0).sum().item()
            if zero_rows > 0:
                log(f"[WARN] {zero_rows} nodes have ZERO embeddings (Fallback triggered?)")
            else:
                log(f"[PASS] All nodes have CodeBERT embeddings.")
    else:
        log(f"[FAIL] No 'x' (node features) found in Data object.")

    # 4. EDGE ANALYSIS
    edge_index = getattr(data, 'edge_index', None)
    edge_attr = getattr(data, 'edge_attr', getattr(data, 'edge_type', None))

    if edge_index is not None:
        log(f"\n--- EDGE TOPOLOGY ---")
        log(f"Shape: {edge_index.shape}")
        num_edges = edge_index.shape[1]
        log(f"Count: {num_edges} edges")
        
        # Validity Check
        max_idx = edge_index.max().item()
        num_nodes = x.shape[0] if x is not None else 0
        if max_idx < num_nodes:
            log(f"[PASS] All edge indices are valid (< {num_nodes}).")
        else:
            log(f"[FAIL] Edge index out of bounds! Max index {max_idx} >= Num Nodes {num_nodes}")

        # Edge Types
        if edge_attr is not None:
            log(f"   > Edge Attributes/Types:")
            unique_types, counts = torch.unique(edge_attr, return_counts=True)
            for t, c in zip(unique_types.tolist(), counts.tolist()):
                log(f"     Type {int(t)}: {c} edges")
        else:
            log(f"[WARN] No 'edge_attr' or 'edge_type' found.")
    else:
        log(f"[FAIL] No 'edge_index' found.")

    # 5. LABEL CHECK
    y = getattr(data, 'y', None)
    log(f"\n--- TARGET LABEL (y) ---")
    if y is not None:
        log(f"Value: {y}")
        log(f"Shape: {y.shape}")
        
        meta_label = meta.get('label')
        if meta_label is not None:
            # handle 0 vs [0]
            y_val = y.item() if y.numel() == 1 else y
            if int(y_val) == int(meta_label):
                log(f"[PASS] Label matches metadata ({meta_label}).")
            else:
                log(f"[FAIL] Label mismatch! Meta says {meta_label}, Data has {y_val}")
    else:
        log(f"[WARN] No label 'y' found.")

    # WRITE REPORT
    with open(output_file, 'w') as f:
        f.write('\n'.join(report))
    print(f"\n[Done] Report saved to {output_file}")

if __name__ == "__main__":
    # Hardcoded path based on your prompt
    target_file = "./Clean_exports/cache_devign_v2/devign_normfunc_v2/test/2913d0ac45337fed/objects/00/01/test_func_0001798.c__export__657751f5.pt"
    
    # Allow CLI override, else use hardcoded
    if len(sys.argv) > 1:
        target_file = sys.argv[1]
        
    output_txt = "debug_analysis_result.txt"
    inspect_pt_file(target_file, output_txt)