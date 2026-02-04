#!/usr/bin/env python3
"""
Robust Step-1  –  inspect Diversevul JSON + drop exact-duplicate code strings.

Example:
    python 01_inspect_and_deduplicate_diversevul.py --in diversevul_20230702.json --tag all
"""

from __future__ import annotations
import argparse, json, hashlib, re, sys
from collections import Counter, defaultdict
from pathlib import Path
from tqdm import tqdm

# Ordered preference list for where the C/C++ text lives
PREFERRED_KEYS = ["code", "func", "function", "content", "source"]

def normalise(t: str) -> str:  return re.sub(r"\s+", " ", t).strip()
def sha(t: str) -> str:        return hashlib.sha256(t.encode()).hexdigest()

def stream(path: Path):
    """Yield JSON objects from JSON-array or JSONL file."""
    with path.open(encoding="utf-8") as fh:
        first = fh.read(1); fh.seek(0)
        if first == "[":
            for obj in json.load(fh):
                yield obj
        else:
            for line in fh:
                line = line.strip()
                if line and line not in ("[", "]", ","):
                    yield json.loads(line.rstrip(","))   # tolerate trailing ','

def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--in",   dest="json_in", required=True)
    ap.add_argument("--tag",  required=True, help="all | train | valid | test")
    ap.add_argument("--root", default=".",   help="project root")
    args = ap.parse_args()

    root  = Path(args.root).expanduser().resolve()
    work  = root / "workspace"
    ded   = work / "deduped";   ded.mkdir(parents=True, exist_ok=True)
    rpt   = work / "reports";   rpt.mkdir(parents=True, exist_ok=True)

    src   = Path(args.json_in).expanduser().resolve()
    out   = ded / f"diversevul_{args.tag}_data_dedup.jsonl"

    buckets: dict[str,list[str]] = defaultdict(list)
    kept, skipped_no_code = [], 0
    key_counter = Counter()

    print(f"\n[{args.tag}] scanning {src.name}")
    for obj in tqdm(stream(src), unit="func"):
        key_counter.update(obj.keys())

        key = next((k for k in PREFERRED_KEYS if k in obj and isinstance(obj[k], str) and obj[k].strip()), None)
        if key is None:
            skipped_no_code += 1
            continue

        h = sha(normalise(obj[key]))
        if h not in buckets:
            kept.append(obj)             # keep first occurrence
        buckets[h].append(str(obj.get("id", len(buckets[h]))))

    if not kept:
        print("⚠️  0 rows kept – falling back to *all* rows so you can inspect them.")
        kept = list(stream(src))         # dump everything, no dedup

    # write deduped JSONL
    with out.open("w", encoding="utf-8") as fh:
        for row in kept:
            fh.write(json.dumps(row, ensure_ascii=False) + "\n")

    # reports
    total = skipped_no_code + len(kept)
    report = {
        "split"   : args.tag,
        "rows_total" : total,
        "rows_kept"  : len(kept),
        "rows_no_code_field" : skipped_no_code,
        "field_usage_counts" : {k: key_counter[k] for k in PREFERRED_KEYS if k in key_counter},
    }
    (rpt / f"feature_report_diversevul_{args.tag}.json").write_text(json.dumps(report, indent=2))
    dup_only = {h: ids for h,ids in buckets.items() if len(ids) > 1}
    (rpt / f"duplicates_diversevul_{args.tag}.json").write_text(json.dumps(dup_only, indent=2))

    print(f"✓ wrote {len(kept)} unique rows  →  {out}")
    print("Key-field usage:", report["field_usage_counts"])
    if skipped_no_code:
        print(f"Skipped {skipped_no_code} rows with no non-empty code field")

if __name__ == "__main__":
    main()





"""


python 01_inspect_and_deduplicate_diversevul.py \
    --in ./datasets/Diversevul/diversevul_20230702.json \
    --tag all


"""