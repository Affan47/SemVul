#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Inspect + deduplicate (CSV or JSON/JSONL) for Reveal schema.

Input CSV columns expected: project, label, functionSource  (hash/size optional/ignored)
Output JSONL rows: {"code", "label", "project"}
"""

from __future__ import annotations
import argparse, json, hashlib, re, sys, csv
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, Iterator, Any
from tqdm import tqdm

# Allow very large CSV fields (e.g., functionSource)
csv.field_size_limit(sys.maxsize)

PREFERRED_KEYS = ["functionSource", "code", "func", "function", "content", "source"]

def normalise(t: str) -> str: return re.sub(r"\s+", " ", t).strip()
def sha(t: str) -> str:       return hashlib.sha256(t.encode("utf-8")).hexdigest()

def stream_json(path: Path) -> Iterator[Dict[str, Any]]:
    with path.open(encoding="utf-8") as fh:
        first = fh.read(1); fh.seek(0)
        if first == "[":
            data = json.load(fh)
            for obj in data:
                if isinstance(obj, dict): yield obj
        else:
            for line in fh:
                line = line.strip()
                if line and line not in ("[", "]", ","):
                    yield json.loads(line.rstrip(","))  # tolerate trailing ','

def _lower_name_map(fieldnames): return {c.lower(): c for c in (fieldnames or [])}

def stream_csv(path: Path) -> Iterator[Dict[str, Any]]:
    with path.open("r", encoding="utf-8", newline="") as fh:
        reader = csv.DictReader(fh)  # add delimiter=";" if needed
        names = _lower_name_map(reader.fieldnames)
        required = ["project", "label", "functionsource"]
        missing = [c for c in required if c not in names]
        if missing:
            raise ValueError(f"Missing required columns {missing} in {path}. Found: {reader.fieldnames}")
        for row in reader: yield row

def coerce_label(val) -> int | None:
    if val is None: return None
    s = str(val).strip().lower()
    if s in {"1","true","yes"}: return 1
    if s in {"0","false","no"}: return 0
    try: return int(s)
    except Exception: return None

def pick_code_key(obj: Dict[str, Any]) -> str | None:
    for k in PREFERRED_KEYS:
        if k in obj and isinstance(obj[k], str) and obj[k].strip(): return k
    return None

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--in",   dest="inp", required=True, help="CSV, JSON array, or JSONL")
    ap.add_argument("--tag",  required=True, help="train | valid | test | all")
    ap.add_argument("--root", default=".", help="project root for outputs")
    args = ap.parse_args()

    root = Path(args.root).expanduser().resolve()
    work = root / "workspace"
    ded  = work / "deduped";  ded.mkdir(parents=True, exist_ok=True)
    rpt  = work / "reports";  rpt.mkdir(parents=True, exist_ok=True)

    src  = Path(args.inp).expanduser().resolve()
    is_csv = src.suffix.lower() == ".csv"
    out_path = ded / f"reveal_{args.tag}_dedup.jsonl"

    buckets: dict[str, list[str]] = defaultdict(list)  # code_sha -> list of row ids
    kept: list[Dict[str, Any]] = []
    skipped_no_code = 0
    key_counter = Counter()
    total_rows = 0

    print(f"\n[{args.tag}] scanning {src.name}  (type: {'CSV' if is_csv else 'JSON'})")

    iterator = stream_csv(src) if is_csv else stream_json(src)

    csv_cols = None
    if is_csv:
        with src.open("r", encoding="utf-8", newline="") as fh:
            reader_names = csv.DictReader(fh)
            csv_cols = _lower_name_map(reader_names.fieldnames)

    def get_csv(obj: Dict[str, Any], name: str) -> Any:
        if not csv_cols: return obj.get(name)
        key = csv_cols.get(name.lower());  return obj.get(key) if key else None

    for row in tqdm(iterator, unit="row"):
        total_rows += 1

        if is_csv:
            key_counter.update([k for k in ["project","label","functionSource"] if get_csv(row,k) is not None])
            code_text = get_csv(row, "functionSource")
            lbl       = coerce_label(get_csv(row, "label"))
            proj      = (get_csv(row, "project") or "").strip() or None
            rid       = f"row_{total_rows}"
        else:
            key       = pick_code_key(row)
            code_text = row.get(key) if key else None
            lbl       = coerce_label(row.get("label"))
            proj      = (row.get("project") or "").strip() or None
            rid       = str(row.get("id", total_rows))

        if not isinstance(code_text, str) or not code_text.strip():
            skipped_no_code += 1
            continue

        code_hash = sha(normalise(code_text))

        if code_hash not in buckets:
            kept.append({
                "code": code_text,                         # original text
                "label": lbl if lbl is not None else 0,    # keep label for training
                "project": proj,
            })
        buckets[code_hash].append(rid)

    if not kept:
        print("⚠️  0 rows kept – falling back to *all* rows so you can inspect them.")
        if is_csv:
            with src.open("r", encoding="utf-8", newline="") as fh:
                reader = csv.DictReader(fh)
                cols = _lower_name_map(reader.fieldnames)
                for r in reader:
                    kept.append({
                        "code": str(r.get(cols.get("functionsource","functionSource"), "")),
                        "label": coerce_label(r.get(cols.get("label","label"))) or 0,
                        "project": (r.get(cols.get("project","project")) or "").strip() or None,
                    })
        else:
            for r in stream_json(src):
                k = pick_code_key(r) or ""
                kept.append({
                    "code": str(r.get(k, "")),
                    "label": coerce_label(r.get("label")) or 0,
                    "project": (r.get("project") or "").strip() or None,
                })

    with out_path.open("w", encoding="utf-8") as fh:
        for row in kept:
            fh.write(json.dumps(row, ensure_ascii=False) + "\n")

    report = {
        "split": args.tag,
        "input_path": str(src),
        "input_type": "csv" if is_csv else "json",
        "rows_total_seen": total_rows,
        "rows_kept_after_dedup": len(kept),
        "rows_no_code_field": skipped_no_code,
        "field_usage_counts": {k: key_counter[k] for k in (PREFERRED_KEYS + ["label","project"]) if k in key_counter},
        "unique_code_buckets": len(buckets),
    }
    rpt_path = rpt / f"feature_report_reveal_{args.tag}.json"
    dup_path = rpt / f"duplicates_reveal_{args.tag}.json"
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
python 04a_inspect_and_deduplicate_reveal.py\
  --in "./datasets/reveal/train_reveal.csv" \
  --tag train

python 04a_inspect_and_deduplicate_reveal.py \
  --in "./datasets/reveal/valid_reveal.csv" \
  --tag valid

python 04a_inspect_and_deduplicate_reveal.py\
  --in "./datasets/reveal/test_reveal.csv" \
  --tag test


"""