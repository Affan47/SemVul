#!/usr/bin/env python3
"""
make_manifest_T6.py  ·  dual-CSV edition
────────────────────────────────────────
For every Devign split it writes **two** manifests:

1. manifest_<split>_advT6.csv   ← rows 0-5  (original + 5 mutants)   ✅ use for training
2. manifest_<split>_mutT5.csv   ← rows 1-5  (mutants only)           optional / ablation

Rows are streamed — memory-safe, CPU-friendly, progress-bar included.
"""

import argparse, csv, pathlib, concurrent.futures as cf
from functools import partial
from tqdm import tqdm

# ─── paths (same layout you showed) ─────────────────────────────────────────
GRAPH_ROOT   = pathlib.Path(
    "./Json_exports/normalized_devign_json"
)
MANIFEST_DIR = pathlib.Path(
    "./workspace/01_Normalized_datasets/03_normalized_devign"
)

SNAP_NAMES = ["export.json"] + [f"snap_adv{i}_nocm.json" for i in range(1, 6)]

# ─── helpers ───────────────────────────────────────────────────────────────
def load_label_map(old_manifest: pathlib.Path) -> dict[int, int]:
    """{function_id: label}  – only a few MB."""
    import pandas as pd
    df = pd.read_csv(old_manifest, usecols=["index", "label"])
    return dict(df.groupby("index")["label"].first())

def is_complete(fid_dir: pathlib.Path) -> bool:
    return all((fid_dir / n).is_file() for n in SNAP_NAMES)

def rows_for(fid_dir: pathlib.Path, label: int) -> list[list]:
    """Return 6 rows (orig+5) or [] if any file missing."""
    if not is_complete(fid_dir):
        return []
    fid   = int(fid_dir.name[1:])                           # F000123 → 123
    rows  = []
    for name in SNAP_NAMES:
        commit = "" if name == "export.json" else pathlib.Path(name).stem
        rows.append([fid, label, commit, f"{fid_dir.name}/{name}"])
    return rows

# ─── main ───────────────────────────────────────────────────────────────────
def build_manifests(split: str, max_workers: int):
    graph_dir     = GRAPH_ROOT / f"{split}_graphson"
    old_manifest  = MANIFEST_DIR / f"manifest_{split}.csv"
    out_advT6     = MANIFEST_DIR / f"manifest_{split}_advT6.csv"   # rows 0-5  ✅
    out_mutT5     = MANIFEST_DIR / f"manifest_{split}_mutT5.csv"   # rows 1-5  (optional)

    label_map = load_label_map(old_manifest)
    rows_advT6, rows_mutT5 = 0, 0                                  # counters

    # CSV writers (open both files once)
    with open(out_advT6, "w", newline="") as fh_all, \
         open(out_mutT5, "w", newline="") as fh_mut, \
         tqdm(unit="func", desc=f"[{split}] scanning") as pbar:

        wr_all = csv.writer(fh_all); wr_all.writerow(["index","label","commit","json_path"])
        wr_mut = csv.writer(fh_mut); wr_mut.writerow(["index","label","commit","json_path"])

        func_dirs = [d for d in graph_dir.iterdir()
                     if d.is_dir() and d.name.startswith("F")]

        # pool over I/O-bound existence checks
        max_workers = max(1, min(max_workers, 16))
        it = func_dirs if max_workers == 1 else \
             cf.ThreadPoolExecutor(max_workers=max_workers).map(lambda d: d, func_dirs)

        for fid_dir in it:
            fid = int(fid_dir.name[1:])
            six_rows = rows_for(fid_dir, label_map.get(fid, 0))
            if not six_rows:                                        # incomplete → skip
                pbar.update(1); continue

            wr_all.writerows(six_rows)                              # 0-5
            wr_mut.writerows(six_rows[1:])                          # 1-5 only

            rows_advT6 += len(six_rows)
            rows_mutT5 += len(six_rows) - 1
            pbar.update(1)

    print(f"[{split}] wrote {rows_advT6} rows  → {out_advT6}")
    print(f"[{split}] wrote {rows_mutT5} rows  → {out_mutT5}")

# ─── CLI ────────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("split", choices=["train", "valid", "test"],
                    help="Dataset split to process")
    ap.add_argument("--workers", type=int, default=16,
                    help="Max parallel threads (default 16)")
    args = ap.parse_args()

    build_manifests(args.split, args.workers)
