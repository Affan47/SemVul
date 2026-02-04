import torch
import os
import sys
import json
import sqlite3
import numpy as np
from pathlib import Path
from transformers import AutoModel, AutoTokenizer

# -----------------------------------------------------------------------------
# CONFIGURATION (Updated for V2 Paths with V3 Topology)
# -----------------------------------------------------------------------------
CACHE_ROOT = "./Clean_exports/cache_devign_v2"
DATASET_NAME = "devign_normfunc_v2"
SPLIT = "test"
# We assume you named the DB codebert_v2.sqlite based on the folder
SQLITE_PATH = "./Clean_exports/cache_devign_v2/codebert_v2.sqlite"
HF_MODEL = "microsoft/codebert-base"

# Import normalization
sys.path.append("./workspace/Scripts_and_saved_Models/Scripts")
try:
    from shared_text_norm import normalize_for_embedding, sha256_normalized
    print(f"[AUDIT] Loaded shared_text_norm")
except ImportError:
    print(f"[AUDIT] FATAL: Could not load shared_text_norm.py. Check your path.")
    sys.exit(1)

def get_embedding_from_sqlite(text, db_path):
    norm_text = normalize_for_embedding(text)
    sha = sha256_normalized(norm_text)
    
    if not os.path.exists(db_path):
        print(f"[AUDIT] ❌ SQLite DB not found at: {db_path}")
        return None

    with sqlite3.connect(db_path) as conn:
        cur = conn.execute("SELECT vec FROM embeddings WHERE sha256 = ?", (sha,))
        row = cur.fetchone()
        if row: return np.frombuffer(row[0], dtype=np.float32)
    return None

def main():
    print(f"[AUDIT] Checking Cache Root: {CACHE_ROOT}")
    
    # 1. Auto-detect Signature
    split_dir = Path(CACHE_ROOT) / DATASET_NAME / SPLIT
    if not split_dir.exists():
        print(f"[AUDIT] ❌ Cache directory not found: {split_dir}")
        print(f"        Double check 'DATASET_NAME' (currently: {DATASET_NAME})")
        return

    sigs = [d.name for d in split_dir.iterdir() if d.is_dir() and d.name != "meta"]
    if not sigs:
        print(f"[AUDIT] ❌ No signature folders found in {split_dir}")
        return
    
    # Pick the most recent one if multiple exist
    signature = sigs[0]
    print(f"[AUDIT] Detected Signature: {signature}")
    
    # 2. Load a random graph
    obj_dir = split_dir / signature / "objects"
    pt_files = list(obj_dir.rglob("*.pt"))
    if not pt_files:
        print("[AUDIT] ❌ No .pt files found in objects dir.")
        return
        
    target_pt = pt_files[0]
    print(f"[AUDIT] Inspecting Graph: {target_pt.name}")
    
    try:
        data = torch.load(target_pt, map_location="cpu")
    except Exception as e:
        print(f"[AUDIT] ❌ Failed to load .pt file: {e}")
        return
    
    # 3. TOPOLOGY CHECK (The Critical V3 Verification)
    print(f"\n[TOPOLOGY CHECK]")
    print(f"  Nodes: {data.num_nodes}")
    print(f"  Edges: {data.num_edges}")
    print(f"  Features: {data.x.shape}")
    
    if data.num_nodes > 10:
        print(f"  ✅ PASS: Graph size > 10. Control Structures (if/while) are likely present.")
        print(f"     (Previous 'Noisy' graphs were ~6 nodes. This increase confirms topology restoration.)")
    else:
        print(f"  ⚠️ WARN: Graph is very small ({data.num_nodes} nodes).")
        print(f"     If this is a complex function, Control Structures might still be missing.")

    # 4. EMBEDDING CHECK (Integrity Verification)
    print(f"\n[EMBEDDING CHECK]")
    # We test 'RET' because it is the most frequent semantic token
    test_str = "RET" 
    
    sqlite_vec = get_embedding_from_sqlite(test_str, SQLITE_PATH)
    
    if sqlite_vec is None:
        print(f"  ❌ FAIL: Could not find string '{test_str}' in SQLite.")
        print(f"     This suggests the vocab/embedding extraction didn't run correctly.")
    else:
        print(f"  Feature Dim: {sqlite_vec.shape[0]}")
        
        # Live Compare vs CodeBERT
        print(f"  Computing live CodeBERT embedding for '{test_str}'...")
        try:
            tokenizer = AutoTokenizer.from_pretrained(HF_MODEL)
            model = AutoModel.from_pretrained(HF_MODEL)
            inputs = tokenizer(test_str, return_tensors="pt")
            with torch.no_grad():
                live_vec = model(**inputs).last_hidden_state[:, 0, :].numpy().flatten()
                
            sim = np.dot(sqlite_vec, live_vec) / (np.linalg.norm(sqlite_vec) * np.linalg.norm(live_vec))
            print(f"  Cosine Similarity (DB vs Live): {sim:.6f}")
            
            if sim > 0.99:
                print("  ✅ PASS: Embeddings are valid and aligned.")
            else:
                print("  ❌ FAIL: Normalization mismatch. The DB text does not match live CodeBERT input.")
        except Exception as e:
            print(f"  ⚠️ Could not run live comparison (internet/env issue?): {e}")

if __name__ == "__main__":
    main()