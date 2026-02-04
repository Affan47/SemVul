#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Inspect + deduplicate (CSV or JSON/JSONL).

Supported schemas:
  • Old Devign CSV: project, label, functionSource
  • New CSV:        id, func, target, project, commit_id

Output JSONL rows: {"code","label","project","id","commit"}
"""

from __future__ import annotations
import argparse, json, hashlib, re, sys, csv
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterator, Any, Optional
from tqdm import tqdm

# Allow very large CSV fields (e.g., function bodies)
csv.field_size_limit(sys.maxsize)

# Prefer keys in this order when scanning JSON objects
PREFERRED_KEYS = ["functionSource", "code", "func", "function", "content", "source"]

def normalise(t: str) -> str:
    return re.sub(r"\s+", " ", t).strip()

def sha(t: str) -> str:
    return hashlib.sha256(t.encode("utf-8")).hexdigest()

def stream_json(path: Path) -> Iterator[Dict[str, Any]]:
    with path.open(encoding="utf-8") as fh:
        first = fh.read(1); fh.seek(0)
        if first == "[":
            data = json.load(fh)
            for obj in data:
                if isinstance(obj, dict):
                    yield obj
        else:
            for line in fh:
                line = line.strip()
                if line and line not in ("[", "]", ","):
                    yield json.loads(line.rstrip(","))  # tolerate trailing ','

def _lower_name_map(fieldnames):
    return {c.lower(): c for c in (fieldnames or [])}

def stream_csv(path: Path) -> Iterator[Dict[str, Any]]:
    with path.open("r", encoding="utf-8", newline="") as fh:
        reader = csv.DictReader(fh)
        # No hard fail here; we validate later to support multiple schemas.
        for row in reader:
            yield row

def coerce_label(val) -> Optional[int]:
    if val is None:
        return None
    s = str(val).strip().lower()
    if s in {"1","true","yes"}: return 1
    if s in {"0","false","no"}: return 0
    try:
        return int(s)
    except Exception:
        return None

def pick_code_key(obj: Dict[str, Any]) -> Optional[str]:
    for k in PREFERRED_KEYS:
        if k in obj and isinstance(obj[k], str) and obj[k].strip():
            return k
    return None

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--in",   dest="inp", required=True, help="CSV, JSON array, or JSONL")
    ap.add_argument("--tag",  required=True, help="train | valid | test | all")
    ap.add_argument("--root", default=".", help="output root")
    args = ap.parse_args()

    root = Path(args.root).expanduser().resolve()
    work = root / "workspace"
    ded  = work / "deduped";  ded.mkdir(parents=True, exist_ok=True)
    rpt  = work / "reports";  rpt.mkdir(parents=True, exist_ok=True)

    src = Path(args.inp).expanduser().resolve()
    is_csv = src.suffix.lower() == ".csv"
    out_path = ded / f"dedup_{args.tag}.jsonl"

    print(f"\n[{args.tag}] scanning {src.name}  (type: {'CSV' if is_csv else 'JSON'})")

    # Discover CSV column names (lower→original) for flexible access
    csv_cols = None
    if is_csv:
        with src.open("r", encoding="utf-8", newline="") as fh:
            peek = csv.DictReader(fh)
            csv_cols = _lower_name_map(peek.fieldnames)

    def get_csv(obj: Dict[str, Any], name: str) -> Any:
        """Case-insensitive column getter for CSV rows."""
        if not csv_cols: return obj.get(name)
        key = csv_cols.get(name.lower())
        return obj.get(key) if key else None

    # Determine which schema we're on (CSV)
    schema = "json"
    if is_csv and csv_cols:
        has_old = all(k in csv_cols for k in ["project", "label", "functionsource"])
        has_new = all(k in csv_cols for k in ["id", "func", "target", "project", "commit_id"])
        if has_old:
            schema = "csv_old"
        elif has_new:
            schema = "csv_new"
        else:
            # Soft guidance
            raise ValueError(
                f"Unrecognized CSV schema. Found columns: {list(csv_cols.values())}\n"
                f"Expected either: ['project','label','functionSource'] or "
                f"['id','func','target','project','commit_id']"
            )

    iterator = stream_csv(src) if is_csv else stream_json(src)

    buckets: dict[str, list[str]] = defaultdict(list)  # code_sha -> list of row ids (for dup report)
    kept: list[Dict[str, Any]] = []
    skipped_no_code = 0
    key_counter = Counter()
    total_rows = 0

    # Field usage tracking set
    tracked_keys = set(PREFERRED_KEYS + ["label","target","project","id","commit_id"])

    for row in tqdm(iterator, unit="row"):
        total_rows += 1

        if is_csv:
            if schema == "csv_old":
                # Old Devign schema
                code_text = get_csv(row, "functionSource")
                lbl       = coerce_label(get_csv(row, "label"))
                proj      = (get_csv(row, "project") or "").strip() or None
                rid       = f"row_{total_rows}"
                rid_out   = rid
                commit    = None
            else:
                # New schema: id, func, target, project, commit_id
                code_text = get_csv(row, "func")
                lbl       = coerce_label(get_csv(row, "target"))
                proj      = (get_csv(row, "project") or "").strip() or None
                rid       = get_csv(row, "id")
                rid_out   = str(rid) if rid is not None else f"row_{total_rows}"
                commit    = (get_csv(row, "commit_id") or "").strip() or None

            # Track usage
            for k in tracked_keys:
                v = get_csv(row, k) if schema == "csv_new" else get_csv(row, k if k!="func" else "functionSource")
                if v is not None:
                    key_counter.update([k])

        else:
            # JSON/JSONL — try to be flexible
            key = pick_code_key(row)
            code_text = row.get(key) if key else None
            # Prefer 'target' if present, else 'label'
            lbl = coerce_label(row.get("target"))
            if lbl is None:
                lbl = coerce_label(row.get("label"))
            proj    = (row.get("project") or "").strip() or None
            rid     = row.get("id")
            rid_out = str(rid) if rid is not None else str(total_rows)
            commit  = (row.get("commit_id") or row.get("commit") or "")
            commit  = commit.strip() or None
            for k in tracked_keys:
                if k in row and row[k] is not None:
                    key_counter.update([k])

        if not isinstance(code_text, str) or not code_text.strip():
            skipped_no_code += 1
            continue

        code_hash = sha(normalise(code_text))

        if code_hash not in buckets:
            kept.append({
                "code": code_text,
                "label": int(lbl) if isinstance(lbl, int) else (1 if lbl == 1 else 0),  # default 0 if missing/invalid
                "project": proj,
                "id": rid_out,
                "commit": commit,
            })
        buckets[code_hash].append(rid_out)

    # Fallback: if nothing kept, dump all rows in a best-effort way so user can inspect
    if not kept:
        print("⚠️  0 rows kept – falling back to *all* rows so you can inspect them.")
        if is_csv:
            with src.open("r", encoding="utf-8", newline="") as fh:
                reader = csv.DictReader(fh)
                cols = _lower_name_map(reader.fieldnames)
                for i, r in enumerate(reader, start=1):
                    # Try new, then old
                    func_col = cols.get("func") or cols.get("functionsource") or "func"
                    lbl_col  = cols.get("target") or cols.get("label") or "target"
                    kept.append({
                        "code": str(r.get(func_col, "")),
                        "label": coerce_label(r.get(lbl_col)) or 0,
                        "project": (r.get(cols.get("project","project")) or "").strip() or None,
                        "id": str(r.get(cols.get("id","id"), i)),
                        "commit": (r.get(cols.get("commit_id","commit_id")) or "").strip() or None,
                    })
        else:
            for i, r in enumerate(stream_json(src), start=1):
                k = pick_code_key(r) or ""
                lbl = coerce_label(r.get("target"))
                if lbl is None:
                    lbl = coerce_label(r.get("label"))
                kept.append({
                    "code": str(r.get(k, "")),
                    "label": lbl or 0,
                    "project": (r.get("project") or "").strip() or None,
                    "id": str(r.get("id", i)),
                    "commit": (r.get("commit_id") or r.get("commit") or "").strip() or None,
                })

    # Write outputs
    with out_path.open("w", encoding="utf-8") as fh:
        for row in kept:
            fh.write(json.dumps(row, ensure_ascii=False) + "\n")

    # Reports
    report = {
        "split": args.tag,
        "input_path": str(src),
        "input_type": "csv" if is_csv else "json",
        "schema_detected": schema,
        "rows_total_seen": total_rows,
        "rows_kept_after_dedup": len(kept),
        "rows_no_code_field": skipped_no_code,
        "field_usage_counts": {k: key_counter[k] for k in sorted(key_counter)},
        "unique_code_buckets": len(buckets),
    }
    rpt_path = rpt / f"feature_report_{args.tag}.json"
    dup_path = rpt / f"duplicates_{args.tag}.json"
    rpt_path.write_text(json.dumps(report, indent=2), encoding="utf-8")
    dup_only = {h: ids for h, ids in buckets.items() if len(ids) > 1}
    dup_path.write_text(json.dumps(dup_only, indent=2), encoding="utf-8")

    print(f"✓ wrote {len(kept)} unique rows  →  {out_path}")
    print(f"✓ report                         →  {rpt_path}")
    print(f"✓ duplicates map                 →  {dup_path}")
    if skipped_no_code:
        print(f"Skipped {skipped_no_code} rows with no non-empty code field")

if __name__ == "__main__":
    main()



"""
python 01a_inspect_and_deduplicate_devign.py\
  --in "./datasets/devign/devign_train.csv" \
  --tag train

python 01a_inspect_and_deduplicate_devign.py \
  --in "./datasets/devign/devign_validation.csv" \
  --tag valid

python 01a_inspect_and_deduplicate_devign.py\
  --in "./datasets/devign/devign_test.csv" \
  --tag test


"""