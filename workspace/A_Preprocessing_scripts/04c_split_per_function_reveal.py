#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import json
from pathlib import Path
from tqdm import tqdm
import csv

# === CONFIG ===
splits = [
    ("train",  "./workspace/01_Normalized_datasets/05_normalized_reveal/reveal_train_data_normalized.jsonl"),
    ("valid",  "./workspace/01_Normalized_datasets/05_normalized_reveal/reveal_valid_data_normalized.jsonl"),
    ("test",   "./workspace/01_Normalized_datasets/05_normalized_reveal/reveal_test_data_normalized.jsonl"),
]

out_base = Path("./workspace/03_PerFunction_datasets/normalized_reveal_functions")
out_base.mkdir(parents=True, exist_ok=True)

for split_name, input_jsonl in splits:
    output_dir = out_base / split_name
    output_dir.mkdir(parents=True, exist_ok=True)
    manifest_path = out_base / f"manifest_{split_name}.csv"

    rows = []
    bad_lines = 0
    missing_code = 0

    with open(input_jsonl, 'r', encoding="utf-8") as fin:
        for idx, line in enumerate(tqdm(fin, desc=f"Writing .c files for {split_name} (normalized input)"), start=1):
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

            # Input already normalized: just ensure LF newlines
            code_out = code.replace("\r\n", "\n").replace("\r", "\n")

            file_id = f"{split_name}_func_{idx:07d}.c"  # stable, 1-based, zero-padded
            out_path = output_dir / file_id
            out_path.write_text(code_out, encoding="utf-8")

            rows.append({
                "function_id": file_id,
                "label": label,
                "project": project,
                "orig_index": idx
            })

    # Always write CSV with header (even if no rows)
    fieldnames = ["function_id", "label", "project", "orig_index"]
    with open(manifest_path, "w", newline="", encoding="utf-8") as fout:
        writer = csv.DictWriter(fout, fieldnames=fieldnames)
        writer.writeheader()
        if rows:
            writer.writerows(rows)

    print(f"\n✓ {len(rows)} {split_name} function files written to {output_dir}")
    print(f"✓ Manifest saved to {manifest_path}")
    if bad_lines:
        print(f"• Skipped {bad_lines} malformed JSONL line(s).")
    if missing_code:
        print(f"• Skipped {missing_code} row(s) with empty/missing 'code'.")

print("\nAll splits extracted per-function successfully!")
