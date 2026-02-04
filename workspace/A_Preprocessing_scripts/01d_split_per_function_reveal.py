#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Split REVEAL CSV splits into per-function .c files plus manifests.

Expected CSV columns:
  - hash, project, size, label, functionSource

Output:
  - <output-base>/<split>/<split>_func_0000001.c
  - <output-base>/manifest_<split>.csv

Usage:
  python 01d_split_per_function_reveal.py
  python 01d_split_per_function_reveal.py --remove-comments --clean-whitespace
  python 01d_split_per_function_reveal.py --overwrite
"""

from __future__ import annotations

import argparse
import csv
import json
import shutil
import sys
from collections import Counter
from dataclasses import dataclass, field
from datetime import datetime
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

try:
    from tqdm import tqdm  # type: ignore
except Exception:  # pragma: no cover - optional dependency
    def tqdm(iterable: Iterable, **_: object) -> Iterable:
        return iterable


DEFAULT_INPUT_DIR = Path("./datasets/reveal")
DEFAULT_OUTPUT_BASE = Path(
    "./workspace/03_PerFunction_datasets/reveal_functions"
)
DEFAULT_SPLITS = ["train", "validation", "test"]


# ---------------------------------------------------------------------------
# Comment removal (no external deps)
# ---------------------------------------------------------------------------
def remove_c_comments(code: str) -> str:
    """Remove C/C++ comments while preserving string and char literals."""
    if not code:
        return code

    result: List[str] = []
    i = 0
    n = len(code)

    while i < n:
        if code[i] == '"':
            result.append(code[i])
            i += 1
            while i < n:
                if code[i] == "\\" and i + 1 < n:
                    result.append(code[i])
                    result.append(code[i + 1])
                    i += 2
                elif code[i] == '"':
                    result.append(code[i])
                    i += 1
                    break
                else:
                    result.append(code[i])
                    i += 1
        elif code[i] == "'":
            result.append(code[i])
            i += 1
            while i < n:
                if code[i] == "\\" and i + 1 < n:
                    result.append(code[i])
                    result.append(code[i + 1])
                    i += 2
                elif code[i] == "'":
                    result.append(code[i])
                    i += 1
                    break
                else:
                    result.append(code[i])
                    i += 1
        elif code[i:i + 2] == "//":
            while i < n and code[i] != "\n":
                i += 1
            if i < n:
                result.append(code[i])
                i += 1
        elif code[i:i + 2] == "/*":
            i += 2
            newlines = 0
            while i < n:
                if code[i:i + 2] == "*/":
                    i += 2
                    break
                if code[i] == "\n":
                    newlines += 1
                i += 1
            if newlines:
                result.append("\n" * newlines)
        else:
            result.append(code[i])
            i += 1

    return "".join(result)


def clean_whitespace(code: str) -> str:
    """Trim trailing whitespace and collapse multiple blank lines."""
    lines = code.split("\n")
    lines = [line.rstrip() for line in lines]
    result: List[str] = []
    blank_count = 0
    for line in lines:
        if not line.strip():
            blank_count += 1
            if blank_count <= 2:
                result.append(line)
        else:
            blank_count = 0
            result.append(line)
    return "\n".join(result)


def normalize_line_endings(code: str) -> str:
    return code.replace("\r\n", "\n").replace("\r", "\n")


def canonical_split_name(name: str) -> str:
    key = name.strip().lower()
    if key in {"val", "valid"}:
        return "validation"
    return key


def resolve_input_path(input_dir: Path, split: str) -> Optional[Path]:
    split = canonical_split_name(split)
    candidates = [
        input_dir / f"{split}_reveal.csv",
        input_dir / f"{split}.csv",
    ]
    if split == "validation":
        candidates.extend([
            input_dir / "valid_reveal.csv",
            input_dir / "val_reveal.csv",
            input_dir / "valid.csv",
            input_dir / "val.csv",
        ])
    for path in candidates:
        if path.exists():
            return path
    return None


def parse_label(value: str) -> Tuple[int, bool]:
    if value is None:
        return 0, False
    try:
        return int(value), True
    except (ValueError, TypeError):
        return 0, False


@dataclass
class SplitStats:
    name: str
    total_rows: int = 0
    written: int = 0
    empty_function: int = 0
    missing_label: int = 0
    bad_label: int = 0
    missing_project: int = 0
    duplicate_hash: int = 0
    label_counts: Counter = field(default_factory=Counter)
    project_counts: Counter = field(default_factory=Counter)
    chars_sum: int = 0
    chars_min: Optional[int] = None
    chars_max: Optional[int] = None
    lines_sum: int = 0
    lines_min: Optional[int] = None
    lines_max: Optional[int] = None

    def update_lengths(self, text: str) -> None:
        char_len = len(text)
        line_len = text.count("\n") + (1 if text else 0)
        self.chars_sum += char_len
        self.lines_sum += line_len
        self.chars_min = char_len if self.chars_min is None else min(self.chars_min, char_len)
        self.chars_max = char_len if self.chars_max is None else max(self.chars_max, char_len)
        self.lines_min = line_len if self.lines_min is None else min(self.lines_min, line_len)
        self.lines_max = line_len if self.lines_max is None else max(self.lines_max, line_len)

    def to_dict(self) -> Dict[str, object]:
        mean_chars = self.chars_sum / self.written if self.written else 0.0
        mean_lines = self.lines_sum / self.written if self.written else 0.0
        return {
            "split": self.name,
            "total_rows": self.total_rows,
            "written": self.written,
            "empty_function": self.empty_function,
            "missing_label": self.missing_label,
            "bad_label": self.bad_label,
            "missing_project": self.missing_project,
            "duplicate_hash": self.duplicate_hash,
            "label_counts": dict(self.label_counts),
            "project_counts": dict(self.project_counts),
            "function_chars": {
                "min": self.chars_min,
                "max": self.chars_max,
                "mean": mean_chars,
            },
            "function_lines": {
                "min": self.lines_min,
                "max": self.lines_max,
                "mean": mean_lines,
            },
        }


def ensure_output_dir(path: Path, overwrite: bool) -> None:
    if path.exists() and any(path.iterdir()):
        if not overwrite:
            raise SystemExit(f"Output directory not empty: {path} (use --overwrite)")
        shutil.rmtree(path)
    path.mkdir(parents=True, exist_ok=True)


def iter_rows(path: Path) -> Iterable[dict]:
    with path.open("r", newline="", encoding="utf-8", errors="replace") as f:
        reader = csv.DictReader(f)
        if reader.fieldnames is None:
            raise ValueError(f"Missing header in {path}")
        for row in reader:
            yield row


def process_split(
    split_name: str,
    input_path: Path,
    output_dir: Path,
    remove_comments: bool,
    clean_ws: bool,
    overwrite: bool,
    max_rows: Optional[int],
) -> Tuple[List[dict], SplitStats]:
    ensure_output_dir(output_dir, overwrite)
    stats = SplitStats(split_name)
    seen_hashes = set()
    manifest_rows: List[dict] = []

    for idx, row in enumerate(tqdm(iter_rows(input_path), desc=split_name), start=1):
        stats.total_rows += 1
        if max_rows is not None and stats.total_rows > max_rows:
            break

        func_src = (row.get("functionSource") or "").strip()
        if not func_src:
            stats.empty_function += 1
            continue

        label_raw = row.get("label", "")
        if label_raw == "":
            stats.missing_label += 1
        label, ok = parse_label(label_raw)
        if not ok and label_raw != "":
            stats.bad_label += 1

        project = (row.get("project") or "").strip()
        if not project:
            stats.missing_project += 1
            project = "unknown_project"

        hash_val = (row.get("hash") or "").strip()
        if hash_val:
            if hash_val in seen_hashes:
                stats.duplicate_hash += 1
            else:
                seen_hashes.add(hash_val)

        size_val = (row.get("size") or "").strip()

        code_out = normalize_line_endings(func_src)
        if remove_comments:
            code_out = remove_c_comments(code_out)
        if clean_ws:
            code_out = clean_whitespace(code_out)
        if not code_out.endswith("\n"):
            code_out += "\n"

        stats.update_lengths(code_out)
        stats.written += 1
        file_id = f"{split_name}_func_{stats.written:07d}.c"
        (output_dir / file_id).write_text(code_out, encoding="utf-8")

        manifest_rows.append(
            {
                "function_id": file_id,
                "label": label,
                "project": project,
                "orig_index": idx,
                "hash": hash_val,
                "size": size_val,
            }
        )

    return manifest_rows, stats


def write_manifest(path: Path, rows: List[dict]) -> None:
    fieldnames = ["function_id", "label", "project", "orig_index", "hash", "size"]
    with path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def write_stats(output_base: Path, stats: List[SplitStats], inputs: Dict[str, str]) -> None:
    payload = {
        "generated_at": datetime.now().isoformat(),
        "output_base": str(output_base),
        "inputs": inputs,
        "splits": [s.to_dict() for s in stats],
    }
    out_json = output_base / "reveal_per_function_stats.json"
    out_txt = output_base / "reveal_per_function_stats.txt"
    out_json.write_text(json.dumps(payload, indent=2), encoding="utf-8")

    lines = [
        "REVEAL Per-Function Split Stats",
        "=" * 72,
        f"Generated: {payload['generated_at']}",
        f"Output base: {payload['output_base']}",
        "",
    ]
    for s in stats:
        d = s.to_dict()
        lines.append(f"Split: {d['split']}")
        lines.append("-" * 72)
        lines.append(f"Rows: {d['total_rows']}  Written: {d['written']}  Empty: {d['empty_function']}")
        lines.append(f"Missing label: {d['missing_label']}  Bad label: {d['bad_label']}")
        lines.append(f"Missing project: {d['missing_project']}  Duplicate hash: {d['duplicate_hash']}")
        lines.append(f"Labels: {d['label_counts']}")
        lines.append(f"Projects: {d['project_counts']}")
        lines.append(f"Function chars: {d['function_chars']}")
        lines.append(f"Function lines: {d['function_lines']}")
        lines.append("")

    out_txt.write_text("\n".join(lines), encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Split REVEAL CSV into per-function files and manifests"
    )
    parser.add_argument("--input-dir", type=Path, default=DEFAULT_INPUT_DIR)
    parser.add_argument("--output-base", type=Path, default=DEFAULT_OUTPUT_BASE)
    parser.add_argument("--splits", nargs="+", default=DEFAULT_SPLITS)
    parser.add_argument("--remove-comments", action="store_true")
    parser.add_argument("--clean-whitespace", action="store_true")
    parser.add_argument("--overwrite", action="store_true")
    parser.add_argument("--max-rows", type=int, default=None)
    args = parser.parse_args()

    try:
        csv.field_size_limit(sys.maxsize)
    except OverflowError:
        csv.field_size_limit(2**31 - 1)

    output_base = args.output_base
    output_base.mkdir(parents=True, exist_ok=True)

    split_stats: List[SplitStats] = []
    input_paths: Dict[str, str] = {}

    for split in args.splits:
        split_name = canonical_split_name(split)
        input_path = resolve_input_path(args.input_dir, split_name)
        if input_path is None:
            print(f"[WARN] No input CSV found for split '{split_name}' in {args.input_dir}")
            continue

        input_paths[split_name] = str(input_path)
        output_dir = output_base / split_name
        rows, stats = process_split(
            split_name=split_name,
            input_path=input_path,
            output_dir=output_dir,
            remove_comments=args.remove_comments,
            clean_ws=args.clean_whitespace,
            overwrite=args.overwrite,
            max_rows=args.max_rows,
        )
        split_stats.append(stats)

        manifest_path = output_base / f"manifest_{split_name}.csv"
        write_manifest(manifest_path, rows)
        print(f"[OK] {split_name}: wrote {stats.written} files, manifest={manifest_path}")

    if split_stats:
        write_stats(output_base, split_stats, input_paths)
        print(f"[OK] Stats: {output_base / 'reveal_per_function_stats.txt'}")


if __name__ == "__main__":
    main()
