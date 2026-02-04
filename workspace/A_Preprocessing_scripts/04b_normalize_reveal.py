#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Normalize all deduplicated reveal splits: train/valid/test.
- Safely strips comments (preserves string/char literals)
- Normalizes basic delimiters/whitespace (newlines, tabs)
- Renames identifiers via tree-sitter (Func0, Var1, …)
- Keeps: code, label, project  (for per-project metrics)
- Writes JSONL + manifest CSV per split, robust to empty input
"""

import csv, json, re
from itertools import count
from pathlib import Path
from tqdm import tqdm
from tree_sitter import Language, Parser

# ==== Tree-sitter setup ====
TS_SO  = "./external/linevul/build/my-languages.so"
TS_C   = "./external/linevul/tree-sitter-v20/tree-sitter-c"
TS_CPP = "./external/linevul/tree-sitter-v20/tree-sitter-cpp"

TS_SO = Path(TS_SO).expanduser()
if not TS_SO.exists():
    print("Compiling Tree-sitter grammars … (first run only)")
    Language.build_library(str(TS_SO), [TS_C, TS_CPP])

try:
    C_LANG = Language(str(TS_SO), "c")
except TypeError:
    C_LANG = Language(str(TS_SO))  # legacy API

parser = Parser()
parser.set_language(C_LANG)

# --------- helpers: comments + whitespace “delimiters” ----------
def strip_comments_c_like(src: str) -> str:
    """
    Remove // and /* */ comments while preserving content inside "strings" and 'chars'.
    Lightweight state machine—good enough prior to parsing / CPG.
    """
    i, n = 0, len(src)
    out = []
    IN_CODE, IN_STR, IN_CHAR, IN_SL_COMMENT, IN_ML_COMMENT = range(5)
    state = IN_CODE
    while i < n:
        ch = src[i]
        nxt = src[i+1] if i+1 < n else ''

        if state == IN_CODE:
            if ch == '"':
                out.append(ch); state = IN_STR; i += 1; continue
            if ch == "'":
                out.append(ch); state = IN_CHAR; i += 1; continue
            if ch == '/' and nxt == '/':
                state = IN_SL_COMMENT; i += 2; continue
            if ch == '/' and nxt == '*':
                state = IN_ML_COMMENT; i += 2; continue
            out.append(ch); i += 1; continue

        if state == IN_STR:
            out.append(ch)
            if ch == '\\' and i+1 < n:
                out.append(src[i+1]); i += 2; continue
            if ch == '"':
                state = IN_CODE
            i += 1; continue

        if state == IN_CHAR:
            out.append(ch)
            if ch == '\\' and i+1 < n:
                out.append(src[i+1]); i += 2; continue
            if ch == "'":
                state = IN_CODE
            i += 1; continue

        if state == IN_SL_COMMENT:
            if ch == '\n':
                out.append('\n'); state = IN_CODE
            i += 1; continue

        if state == IN_ML_COMMENT:
            if ch == '*' and nxt == '/':
                i += 2; state = IN_CODE; continue
            i += 1; continue

    return ''.join(out)

def normalize_delimiters(src: str) -> str:
    """
    Normalize line endings and tabs without being aggressive on spacing:
    - CRLF/CR -> LF
    - tabs -> 4 spaces
    - strip trailing whitespace on lines
    """
    s = src.replace("\r\n", "\n").replace("\r", "\n")
    s = s.replace("\t", "    ")
    # strip trailing spaces but keep internal spacing
    s = "\n".join(line.rstrip() for line in s.split("\n"))
    return s

# --------- identifier renaming via tree-sitter ----------
def normalise_identifiers(code: str) -> str:
    """
    Use tree-sitter to map:
      function name -> Func0
      other identifiers -> Var1, Var2, ...
    """
    try:
        tree = parser.parse(code.encode())
    except Exception:
        # If tree-sitter chokes, return code unchanged
        return code

    func_name, id_nodes = None, []

    stack = [tree.walk()]
    while stack:
        cur = stack.pop()
        node = cur.node
        if node.type in ("function_definition", "function_declarator"):
            for ch in node.children:
                if ch.type == "identifier":
                    try:
                        func_name = ch.text.decode()
                    except Exception:
                        pass
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
        try:
            txt = n.text.decode()
        except Exception:
            continue
        if txt and txt != func_name and txt not in replace:
            replace[txt] = f"Var{next(counter)}"

    if not replace:
        return code
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, replace)) + r")\b")
    return pattern.sub(lambda m: replace[m.group(0)], code)

def normalize_pipeline(code: str) -> str:
    """
    Full normalization pipeline:
      1) strip comments safely
      2) normalize basic delimiters/whitespace
      3) rename identifiers using tree-sitter
    """
    step1 = strip_comments_c_like(code)
    step2 = normalize_delimiters(step1)
    step3 = normalise_identifiers(step2)
    return step3

# ==== Main processing ====
splits = [
    ("train",  "./workspace/02_Deduplicated_datasets/deduped_reveal/reveal_train_dedup.jsonl"),
    ("valid",  "./workspace/02_Deduplicated_datasets/deduped_reveal/reveal_valid_dedup.jsonl"),
    ("test",   "./workspace/02_Deduplicated_datasets/deduped_reveal/reveal_test_dedup.jsonl"),
]

out_base = Path("./workspace/01_Normalized_datasets/05_normalized_reveal")
out_base.mkdir(parents=True, exist_ok=True)

for tag, in_path in splits:
    in_path = Path(in_path)
    out_jsonl = out_base / f"reveal_{tag}_data_normalized.jsonl"
    out_manifest = out_base / f"manifest_{tag}.csv"

    norm_records = []
    rows = []
    bad_lines = 0
    missing_code = 0

    print(f"\nNormalizing {in_path} → {out_jsonl}")
    with in_path.open("r", encoding="utf-8") as f:
        for idx, line in enumerate(tqdm(f, desc=f"{tag} split"), 1):  # 1-based
            line = line.strip()
            if not line:
                continue
            try:
                obj = json.loads(line)
            except Exception:
                bad_lines += 1
                continue

            code = obj.get("code")
            if not isinstance(code, str) or not code.strip():
                missing_code += 1
                continue

            label = obj.get("label", 0)
            project = obj.get("project", "unknown_project")

            # Full normalization pipeline
            code_norm = normalize_pipeline(code)

            norm_records.append({"code": code_norm, "label": label, "project": project})
            rows.append({"index": idx, "label": label, "project": project})

    # Write JSONL
    out_jsonl.parent.mkdir(parents=True, exist_ok=True)
    with out_jsonl.open("w", encoding="utf-8") as out_f:
        for obj in norm_records:
            out_f.write(json.dumps(obj, ensure_ascii=False) + "\n")

    # Write manifest (robust to empty)
    fieldnames = ["index", "label", "project"]
    with out_manifest.open("w", newline="", encoding="utf-8") as csvf:
        w = csv.DictWriter(csvf, fieldnames=fieldnames)
        w.writeheader()
        if rows:
            w.writerows(rows)

    print(f"✓ Normalized {len(rows)} functions: {out_jsonl}")
    print(f"✓ Manifest: {out_manifest}")
    if bad_lines:
        print(f"• Skipped {bad_lines} malformed JSONL line(s).")
    if missing_code:
        print(f"• Skipped {missing_code} row(s) with empty/missing 'code'.")

print("\nAll Reveal splits normalized.")
# Usage: python 04b_normalize_reveal.py
