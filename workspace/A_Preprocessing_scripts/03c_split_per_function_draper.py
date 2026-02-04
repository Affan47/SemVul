#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
03c_per_function_export_draper.py

Export per-function source files for each Draper split from the normalized JSONL:
  INPUT (per split):  JSONL lines like {"code": "<normalized>", "label": "<label | optional>"}
  OUTPUT:
    - Per-function files under: <out_base>/<split>/<split>_func_<7-digit>.(c|cpp)
    - Manifest CSV per split:   <out_base>/manifest_<split>.csv with columns:
        function_id, label, orig_index, lang

Notes:
  • This script expects you've already run the normalization step that removes comments safely (AST-based).
  • File extension is selected via Tree-sitter: parse with C and C++; we pick the language with fewer ERROR nodes.
"""

from __future__ import annotations
import csv
import json
from pathlib import Path
from typing import Tuple

from tqdm import tqdm
from tree_sitter import Language, Parser

# ─────────────────────────────────────────────────────────────────────────────
# CONFIG
# ─────────────────────────────────────────────────────────────────────────────
# Normalized Draper JSONL inputs from your previous step:
SPLITS = [
    ("train", "./workspace/01_Normalized_datasets/04_normalized_draper/draper_train_data_normalized.jsonl"),
    ("valid", "./workspace/01_Normalized_datasets/04_normalized_draper/draper_valid_data_normalized.jsonl"),
    ("test",  "./workspace/01_Normalized_datasets/04_normalized_draper/draper_test_data_normalized.jsonl"),
]

# Output base directory
OUT_BASE = Path("./workspace/03_PerFunction_datasets/normalized_draper_functions")
OUT_BASE.mkdir(parents=True, exist_ok=True)

# Tree-sitter paths (same layout you used in normalization)
TS_ROOT = Path("./external/linevul")
TS_SO   = TS_ROOT / "build/my-languages.so"
TS_C    = TS_ROOT / "tree-sitter-v20/tree-sitter-c"
TS_CPP  = TS_ROOT / "tree-sitter-v20/tree-sitter-cpp"

# ─────────────────────────────────────────────────────────────────────────────
# Tree-sitter setup
# ─────────────────────────────────────────────────────────────────────────────
TS_SO = TS_SO.expanduser()
if not TS_SO.exists():
    print("Compiling Tree-sitter grammars … (first run only)")
    Language.build_library(str(TS_SO), [str(TS_C), str(TS_CPP)])

try:
    C_LANG   = Language(str(TS_SO), "c")
    CPP_LANG = Language(str(TS_SO), "cpp")
except TypeError:
    # legacy API fallback
    C_LANG   = Language(str(TS_SO))
    CPP_LANG = Language(str(TS_SO))

PARSER_C   = Parser();  PARSER_C.set_language(C_LANG)
PARSER_CPP = Parser();  PARSER_CPP.set_language(CPP_LANG)

def _count_error_nodes(node) -> int:
    cnt = 1 if node.has_error else 0
    cur = node.walk()
    if cur.goto_first_child():
        while True:
            cnt += _count_error_nodes(cur.node)
            if not cur.goto_next_sibling():
                break
    return cnt

def _best_lang(code_bytes: bytes) -> Tuple[str, int, int]:
    """
    Return ('c'|'cpp', err_c, err_cpp) selecting the language with fewer ERROR nodes.
    """
    t_c   = PARSER_C.parse(code_bytes)
    t_cpp = PARSER_CPP.parse(code_bytes)
    e_c   = _count_error_nodes(t_c.root_node)
    e_cpp = _count_error_nodes(t_cpp.root_node)
    return (("cpp", e_c, e_cpp) if e_cpp < e_c else ("c", e_c, e_cpp))

# ─────────────────────────────────────────────────────────────────────────────
# Main export logic
# ─────────────────────────────────────────────────────────────────────────────
def process_split(split_name: str, input_jsonl: str) -> None:
    input_path = Path(input_jsonl)
    if not input_path.exists():
        print(f"⚠️  Missing split file: {input_path}")
        return

    output_dir    = OUT_BASE / split_name
    manifest_path = OUT_BASE / f"manifest_{split_name}.csv"
    output_dir.mkdir(parents=True, exist_ok=True)

    rows = []
    with input_path.open("r", encoding="utf-8") as fin:
        for idx, line in enumerate(tqdm(fin, desc=f"Writing {split_name} functions (.c/.cpp)"), 1):
            obj = json.loads(line)
            code  = obj.get("code", "")
            label = obj.get("label", None)

            # Decide file extension by best parse
            lang, err_c, err_cpp = _best_lang(code.encode("utf-8", errors="ignore"))
            ext = ".cpp" if lang == "cpp" else ".c"

            file_id = f"{split_name}_func_{idx:07d}{ext}"
            out_path = output_dir / file_id
            out_path.write_text(code, encoding="utf-8")

            rows.append({
                "function_id": file_id,
                "label": label,
                "orig_index": idx,   # 1-based to align with normalization manifest
                "lang": lang,
            })

    # Write manifest (even if empty, emit header)
    with manifest_path.open("w", newline="", encoding="utf-8") as fout:
        if rows:
            writer = csv.DictWriter(fout, fieldnames=rows[0].keys())
            writer.writeheader()
            writer.writerows(rows)
        else:
            writer = csv.writer(fout)
            writer.writerow(["function_id", "label", "orig_index", "lang"])

    print(f"\n✓ {len(rows)} {split_name} function files written to {output_dir}")
    print(f"✓ Manifest saved to {manifest_path}")

def main():
    for split_name, input_jsonl in SPLITS:
        process_split(split_name, input_jsonl)
    print("\nAll splits extracted per-function successfully!")

if __name__ == "__main__":
    main()
# Usage: python 03c_per_function_export_draper.py
