#!/usr/bin/env python3
"""
Step-2 – normalise identifiers for DiverseVul JSONL file
Saves a single JSONL with normalized code (field names preserved), and a manifest CSV.
"""

import argparse, csv, json, re
from itertools import count
from pathlib import Path
from tqdm import tqdm
from tree_sitter import Language, Parser

# ────────────────────────── CLI ──────────────────────────────────────
ap = argparse.ArgumentParser(description="Normalise DiverseVul JSONL (no per-function files, preserve feature names)")
ap.add_argument("--in",      dest="json_in",  required=True, help="*.json or *.jsonl")
ap.add_argument("--out",     dest="json_out", required=True, help="output normalized JSONL path")
ap.add_argument("--manifest", required=True, help="output CSV path")
ap.add_argument("--ts_so",   default="./external/linevul/build/my-languages.so")
ap.add_argument("--ts_c",    default="./external/linevul/tree-sitter-v20/tree-sitter-c")
ap.add_argument("--ts_cpp",  default="./external/linevul/tree-sitter-v20/tree-sitter-cpp")
args = ap.parse_args()

JSON_IN   = Path(args.json_in).expanduser()
JSON_OUT  = Path(args.json_out).expanduser()
MANIFEST  = Path(args.manifest).expanduser()
TS_SO     = Path(args.ts_so).expanduser()
TS_C, TS_CPP = args.ts_c, args.ts_cpp

# ────────── Tree-sitter build / load (once) ─────────────────────────
if not TS_SO.exists():
    print("Compiling Tree-sitter grammars … (first run only)")
    Language.build_library(str(TS_SO), [TS_C, TS_CPP])

try:            C_LANG = Language(str(TS_SO), "c")
except TypeError: C_LANG = Language(str(TS_SO))        # legacy API

parser = Parser(); parser.set_language(C_LANG)

# ────────────────── identifier normaliser ───────────────────────────
def normalise(code: str) -> str:
    tree = parser.parse(code.encode())
    func_name, id_nodes = None, []

    stack = [tree.walk()]
    while stack:
        cur = stack.pop(); node = cur.node
        if node.type in ("function_definition", "function_declarator"):
            for ch in node.children:
                if ch.type == "identifier":
                    func_name = ch.text.decode()
                    break
        elif node.type == "identifier":
            id_nodes.append(node)
        if cur.goto_first_child():
            stack.append(cur.copy())
            while cur.goto_next_sibling():
                stack.append(cur.copy())

    replace = {func_name: "Func0"} if func_name else {}
    counter = count(1)
    for n in id_nodes:
        txt = n.text.decode()
        if txt != func_name and txt not in replace:
            replace[txt] = f"Var{next(counter)}"

    if not replace:
        return code
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, replace)) + r")\b")
    return pattern.sub(lambda m: replace[m.group(0)], code)

# ─────────────────────── main logic ────────────────────────────────
def main():
    rows, idx = [], 0
    norm_records = []

    with JSON_IN.open() as fh:
        first_char = fh.read(1); fh.seek(0)
        records = json.load(fh) if first_char == "[" else (json.loads(l) for l in fh)

        for obj in tqdm(records, unit="func"):
            idx += 1
            # Normalize code and overwrite in-place (no extra fields)
            obj["func"] = normalise(obj["func"])
            norm_records.append(obj)

            rows.append({
                "index": idx,
                "label": obj["target"],
            })

    # Write normalized JSONL
    JSON_OUT.parent.mkdir(parents=True, exist_ok=True)   # <--- add this line
    with JSON_OUT.open("w", encoding="utf-8") as out_f:
        for obj in norm_records:
            out_f.write(json.dumps(obj, ensure_ascii=False) + "\n")


    # Write manifest CSV
    with MANIFEST.open("w", newline="") as csvf:
        w = csv.DictWriter(csvf, fieldnames=rows[0].keys())
        w.writeheader()
        w.writerows(rows)

    print(f"\n✓ Normalised {len(rows)} functions (field names preserved)")
    print(f"✓ Normalized JSONL → {JSON_OUT}")
    print(f"✓ Manifest CSV     → {MANIFEST}")

if __name__ == "__main__":
    main()



"""

for diversevul, run:

python 02_normalise_diversevul.py \
    --in ./workspace/deduped_diversevul/diversevul_all_data_dedup.jsonl \
    --out ./workspace/normalized_diversevul/diversevul_all_data_normalized.jsonl \
    --manifest ./workspace/normalized_diversevul/manifest_diversevul_all.csv



for six_new_datasets, run:

# Train split
python 02_normalise_diversevul.py \
    --in ./workspace/deduped_new_six_datasets/six_new_datasets_train_data_dedup.jsonl \
    --out ./workspace/normalized_new_six_datasets/six_new_datasets_train_data_normalized.jsonl \
    --manifest ./workspace/normalized_new_six_datasets/manifest_train.csv

# Validation split
python 02_normalise_diversevul.py \
    --in ./workspace/deduped_new_six_datasets/six_new_datasets_valid_data_dedup.jsonl \
    --out ./workspace/normalized_new_six_datasets/six_new_datasets_valid_data_normalized.jsonl \
    --manifest ./workspace/normalized_new_six_datasets/manifest_valid.csv

# Test split
python 02_normalise_diversevul.py \
    --in ./workspace/deduped_new_six_datasets/six_new_datasets_test_data_dedup.jsonl \
    --out ./workspace/normalized_new_six_datasets/six_new_datasets_test_data_normalized.jsonl \
    --manifest ./workspace/normalized_new_six_datasets/manifest_test.csv


"""