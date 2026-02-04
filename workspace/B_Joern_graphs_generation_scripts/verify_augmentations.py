#!/usr/bin/env python3
"""
verify_all_augments.py  ·  Devign augmentation checker (T = 6)

Designed for big iron (88 cores, 250 GB RAM):
• Loads / validates graphs in parallel (ProcessPoolExecutor)
• tqdm progress bar per split
• Hard-coded paths for train & valid
• Exit status 0 → everything OK, 1 → critical errors
"""

import csv, json, os, sys
from pathlib import Path
from collections import defaultdict, Counter
from concurrent.futures import ProcessPoolExecutor, as_completed
from functools import partial
from tqdm import tqdm

# ───────── CONFIG ─────────
T            = 6
EDGE_DIFF    = True           # warn if edge count never changes
MAX_WORKERS  = min(40, os.cpu_count() or 1)   # keep disk happy

SPLITS = {
    "train": {
        "manifest": Path("./"
                         "workspace/01_Normalized_datasets/03_normalized_devign/"
                         "manifest_train_advT6.csv"),
        "json_root": Path("./"
                          "Json_exports/normalized_devign_json/train_graphson"),
    },
    "valid": {
        "manifest": Path("./"
                         "workspace/01_Normalized_datasets/03_normalized_devign/"
                         "manifest_valid_advT6.csv"),
        "json_root": Path("./"
                          "Json_exports/normalized_devign_json/valid_graphson"),
    },
}
# ──────────────────────────

# tiny ANSI helper
def c(code, txt): return f"\033[{code}m{txt}\033[0m" if sys.stdout.isatty() else txt
RED  = lambda t: c("31;1", t)
YLW  = lambda t: c("33;1", t)
GRN  = lambda t: c("32;1", t)

def resolve_json_path(row: dict, root: Path) -> Path:
    jp = (row.get("json_path") or "").strip()
    return root / jp if jp else root / f"F{int(row['index']):06d}" / "export.json"

# ---------- worker ----------
def check_one(index, rows, root, edge_diff):
    """Return Counter of anomalies for this function index."""
    ctr = Counter()              # keys: mismatch, missing, ident, edge_static, checked
    # row-count already guaranteed by caller
    paths = [resolve_json_path(r, root) for r in rows]

    graphs = []
    for p in paths:
        if not p.is_file():
            ctr["missing"] += 1
            return ctr
        try:
            graphs.append(json.load(p.open()))
        except Exception:
            ctr["missing"] += 1
            return ctr

    ctr["checked"] = 1
    base = graphs[0]
    if all(g == base for g in graphs[1:]):
        ctr["ident"] += 1
    if edge_diff:
        be = len(base["@value"]["edges"])
        if all(len(g["@value"]["edges"]) == be for g in graphs[1:]):
            ctr["edge_static"] += 1
    return ctr

# ---------- split verifier ----------
def verify_split(name, manifest: Path, json_root: Path):
    assert manifest.is_file(), f"manifest missing: {manifest}"
    assert json_root.is_dir(), f"json_root missing: {json_root}"

    # group rows by index
    groups = defaultdict(list)
    with manifest.open() as fh:
        for r in csv.DictReader(fh):
            groups[r["index"]].append(r)

    # first pass: detect wrong row-counts (cheap)
    anomalies = Counter()
    jobs = {}
    for idx, rows in groups.items():
        if len(rows) != T:
            anomalies["mismatch"] += 1
            continue   # skip heavy check
        jobs[idx] = rows

    print(f"\n── {name.upper()} split  ({len(jobs)} functions to scan) ──")

    # parallel heavy check
    with ProcessPoolExecutor(max_workers=MAX_WORKERS) as pool, \
         tqdm(total=len(jobs), unit="func") as bar:
        fut_to_idx = {pool.submit(check_one, idx, rows, json_root, EDGE_DIFF): idx
                      for idx, rows in jobs.items()}
        for fut in as_completed(fut_to_idx):
            ctr = fut.result()
            anomalies.update(ctr)
            bar.update()

    # summary
    print(GRN("✔ done"))
    print(f"  functions checked       : {anomalies['checked']}")
    print(f"  wrong row-count (≠{T})  : {anomalies['mismatch']}")
    print(f"  missing / unreadable    : {anomalies['missing']}")
    print(f"  identical augmentations : {anomalies['ident']}")
    if EDGE_DIFF:
        print(f"  edge-count unchanged     : {anomalies['edge_static']}")

    critical = anomalies["mismatch"] + anomalies["missing"]
    return critical == 0  # True → OK

# ---------- run both splits ----------
all_ok = True
for s, cfg in SPLITS.items():
    all_ok &= verify_split(s, cfg["manifest"], cfg["json_root"])

sys.exit(0 if all_ok else 1)


"""python verify_augmentations.py  """