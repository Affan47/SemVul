#!/usr/bin/env python3
"""
make_adv_windows_all.py · v3  (robust-vocab edition)

Creates (T-1) synthetic snapshots per real Devign function.
  • Always 1 edge-level mutator  (adds / drops / wraps an edge)
  • Plus 1-3 extra mutators      (literal tweak, control-flow swap, etc.)
  • Identifier-renaming was **removed** – keeps vocabulary size stable.

Outputs manifest_<split>_advT{T}.csv for every split configured in SPLITS.
"""

import csv, json, random, copy, pathlib, os
from hashlib import md5
from concurrent.futures import ProcessPoolExecutor, as_completed
from tqdm import tqdm

# ───────── USER CONFIG ──────────
SPLITS = {
    "train": {
        "json_root": "./"
                     "Json_exports/normalized_devign_json/train_graphson",
        "manifest_in": "./"
                       "workspace/01_Normalized_datasets/03_normalized_devign/"
                       "manifest_train.csv",
    },
    "valid": {
        "json_root": "./"
                     "Json_exports/normalized_devign_json/valid_graphson",
        "manifest_in": "./"
                       "workspace/01_Normalized_datasets/03_normalized_devign/"
                       "manifest_valid.csv",
    },
        "test": {
        "json_root": "./"
                     "Json_exports/normalized_devign_json/test_graphson",
        "manifest_in": "./"
                       "workspace/01_Normalized_datasets/03_normalized_devign/"
                       "manifest_test.csv",
    },
}
T               = 6                      # snapshots per temporal window
SEED            = 42
MAX_WORKERS     = min(40, os.cpu_count() or 1)
MIN_MUTS, MAX_MUTS = 3, 5               # per synthetic snapshot
random.seed(SEED)

# ──────── mutators ────────
def mut_dead_edge(j):
    """Clone an existing BLOCK–BLOCK edge to create dead control-flow."""
    edges = j["@value"]["edges"]
    blk   = [e["inV"]["@value"] for e in edges if e["inVLabel"] == "BLOCK"]
    if len(blk) >= 2:
        a, b = random.sample(blk, 2)
        n    = copy.deepcopy(edges[-1])
        n["inV"]["@value"], n["outV"]["@value"] = a, b
        edges.append(n)
    return j

def mut_literal(j):
    """Perturb small integer literals inside edge labels."""
    for e in j["@value"]["edges"]:
        if e["inVLabel"].isdigit():
            val = int(e["inVLabel"]) + random.choice([-2, -1, 1, 2])
            e["inVLabel"] = str(val)
    return j

def mut_cf_swap(j):
    """Swap the heads of two AST edges → mild control-flow shuffle."""
    ast = [e for e in j["@value"]["edges"] if e["label"] == "AST"]
    if len(ast) >= 2:
        x, y = random.sample(ast, 2)
        x["inV"]["@value"], y["inV"]["@value"] = y["inV"]["@value"], x["inV"]["@value"]
    return j

def mut_call_wrap(j):
    """Wrap a random CALL edge in an ARGUMENT edge (simulates extra param)."""
    calls = [e for e in j["@value"]["edges"] if e["inVLabel"] == "CALL"]
    if calls:
        base  = random.choice(calls)
        new   = copy.deepcopy(base)
        new["id"]["@value"] = max(e["id"]["@value"] for e in j["@value"]["edges"]) + 1
        new["inVLabel"] = "ARGUMENT"
        j["@value"]["edges"].append(new)
    return j

def mut_drop_edge(j):
    """Delete a random edge (structural sparsification)."""
    edges = j["@value"]["edges"]
    if len(edges) > 1:
        edges.pop(random.randrange(len(edges)))
    return j

# --- mutator pools (renaming removed) ---
EDGE_MUTS   = [mut_dead_edge, mut_call_wrap, mut_drop_edge]   # guarantee one
OTHER_MUTS  = [mut_literal, mut_cf_swap]                      # optional extras
ALL_MUTS    = EDGE_MUTS + OTHER_MUTS

# ─────── helper ───────
def augment_one(row, json_root):
    """Return original + (T-1) augmented manifest rows for one function."""
    base_path = json_root / row.get("json_path",
                                    f"F{int(row['index']):06d}/export.json")
    try:
        g0 = json.load(open(base_path))
    except FileNotFoundError:
        return [row]

    out_rows = [row]
    for step in range(1, T):
        tag  = f"adv{step}_{row.get('commit','nocm')}"
        dest = base_path.parent / f"snap_{tag}.json"
        if not dest.exists():
            rng = random.Random(SEED ^ (int(row["index"]) << 4) ^ step)
            g = copy.deepcopy(g0)

            # ---- pick mutators ----
            chosen = [rng.choice(EDGE_MUTS)]                    # always edge mut
            pool   = [m for m in ALL_MUTS if m not in chosen]
            extra  = rng.sample(pool, rng.randint(MIN_MUTS-1, MAX_MUTS-1))

            orig_edges = len(g["@value"]["edges"])
            for m in chosen + extra:
                g = m(g)

            # fail-safe: ensure edge count changed
            while len(g["@value"]["edges"]) == orig_edges:
                g = mut_drop_edge(g)

            dest.parent.mkdir(parents=True, exist_ok=True)
            json.dump(g, dest.open("w"))

        new_row = dict(row)
        new_row["commit"]    = tag
        new_row["json_path"] = str(dest.relative_to(json_root))
        out_rows.append(new_row)
    return out_rows

# ─────── main ───────
for split, cfg in SPLITS.items():
    json_root     = pathlib.Path(cfg["json_root"])
    manifest_in   = pathlib.Path(cfg["manifest_in"])
    manifest_out  = manifest_in.with_name(f"{manifest_in.stem}_advT{T}.csv")

    print(f"\n=== {split.upper()} split ===")

    # 1. purge old synthetic files
    n_del = 0
    for func_dir in tqdm(json_root.glob("F*"), desc="Cleaning", unit="dir"):
        for f in func_dir.iterdir():
            if f.name.startswith(("snap_aug", "snap_adv")):
                f.unlink(missing_ok=True); n_del += 1
    print(f"  deleted {n_del} old synthetic files.")

    # 2. load manifest, keep only real rows
    rows_real = []
    with manifest_in.open() as fin:
        reader = csv.DictReader(fin)
        for row in reader:
            if row.get("commit", "").startswith(("aug", "adv")):
                continue
            rows_real.append(row)
    print("  real rows:", len(rows_real))

    # allow regeneration by deleting the old out-file
    manifest_out.unlink(missing_ok=True)

    # 3. augment in parallel
    fieldnames = list(rows_real[0].keys())
    for col in ("commit", "json_path"):
        fieldnames.append(col) if col not in fieldnames else None

    created = 0
    with manifest_out.open("w", newline="") as fout, \
         ProcessPoolExecutor(max_workers=MAX_WORKERS) as pool:
        writer = csv.DictWriter(fout, fieldnames=fieldnames)
        writer.writeheader()

        futs = [pool.submit(augment_one, r, json_root) for r in rows_real]
        for fu in tqdm(as_completed(futs), total=len(futs),
                       desc=f"Augmenting {split}", unit="func"):
            rows = fu.result()
            created += len(rows) - 1
            writer.writerows(rows)

    print(f"  → wrote {manifest_out}  (+{created} new snapshots)")

print("\n✓ All splits processed.  Point your training script at *_advT6.csv")
