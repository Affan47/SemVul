import json
from pathlib import Path
from tqdm import tqdm
import csv
import re

# === CONFIG ===
input_jsonl = "./workspace/01_Normalized_datasets/01_normalized_diversevul/diversevul_all_data_normalized.jsonl"
output_dir = "./workspace/02_PerFunction_datasets/normalized_diversevul_functions"
manifest_path = "./workspace/02_PerFunction_datasets/manifest_diversevul_functions.csv"

def remove_comments(code: str) -> str:
    # Remove /* ... */ comments (multiline)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    # Remove // ... comments (single-line)
    code = re.sub(r'//.*', '', code)
    return code

Path(output_dir).mkdir(parents=True, exist_ok=True)
rows = []

with open(input_jsonl, 'r') as fin:
    for idx, line in enumerate(tqdm(fin, desc="Writing .c files (no comments)")):
        obj = json.loads(line)
        # Support both 'func' or 'code' as code field
        code = obj["func"] if "func" in obj else obj["code"]
        code_no_comments = remove_comments(code)
        file_id = f"Func_{idx:07d}.c"
        out_path = Path(output_dir) / file_id
        out_path.write_text(code_no_comments, encoding="utf-8")
        rows.append({
            "function_id": file_id,
            "label": obj.get("target", obj.get("label", "")),
            "orig_index": idx
        })

# Save manifest
with open(manifest_path, "w", newline="") as fout:
    writer = csv.DictWriter(fout, fieldnames=rows[0].keys())
    writer.writeheader()
    writer.writerows(rows)

print(f"\n✓ {len(rows)} function files written (comments removed) to {output_dir}")
print(f"✓ Manifest saved to {manifest_path}")
