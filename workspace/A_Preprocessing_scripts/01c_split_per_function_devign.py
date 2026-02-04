#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
01c_split_per_function_devign_ORIGINAL.py

Split ORIGINAL (non-normalized) Devign JSONL into per-function .c files.
Optionally removes C comments for cleaner CPG generation.

CRITICAL: Use this script instead of the normalized version for vulnerability
detection! The original function names (strcpy, malloc, etc.) are essential
for detecting vulnerability patterns.

Expected JSONL format (ORIGINAL Devign):
    {
      "func": <str>,          # ORIGINAL code (not normalized!)
      "target": <int>,        # vulnerability label (0 or 1)
      "project": <str>,       # project name
      "commit_id": <str>,     # optional
      ...
    }

Output:
  - Per-function .c files: <OUT_BASE>/<split>/<split>_func_0000001.c
  - Manifest CSV: <OUT_BASE>/manifest_<split>.csv

Usage:
    python 01c_split_per_function_devign_ORIGINAL.py
    python 01c_split_per_function_devign_ORIGINAL.py --remove-comments
    python 01c_split_per_function_devign_ORIGINAL.py --remove-comments --clean-whitespace
"""

import csv
import json
import argparse
from pathlib import Path
from typing import Any, Dict, Optional
from tqdm import tqdm


# ═══════════════════════════════════════════════════════════════════
# COMMENT REMOVAL (inline to avoid dependencies)
# ═══════════════════════════════════════════════════════════════════

def remove_c_comments(code: str) -> str:
    """
    Remove C/C++ comments while preserving string literals.
    
    Handles:
    - // single line comments
    - /* multi-line comments */
    - Preserves comments inside string literals
    """
    if not code:
        return code
    
    result = []
    i = 0
    n = len(code)
    
    while i < n:
        # String literal (double quotes)
        if code[i] == '"':
            result.append(code[i])
            i += 1
            while i < n:
                if code[i] == '\\' and i + 1 < n:
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
        
        # Character literal (single quotes)
        elif code[i] == "'":
            result.append(code[i])
            i += 1
            while i < n:
                if code[i] == '\\' and i + 1 < n:
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
        
        # Single-line comment
        elif code[i:i+2] == '//':
            while i < n and code[i] != '\n':
                i += 1
            if i < n:
                result.append(code[i])
                i += 1
        
        # Multi-line comment
        elif code[i:i+2] == '/*':
            i += 2
            newlines = 0
            while i < n:
                if code[i:i+2] == '*/':
                    i += 2
                    break
                if code[i] == '\n':
                    newlines += 1
                i += 1
            result.append('\n' * newlines)
        
        else:
            result.append(code[i])
            i += 1
    
    return ''.join(result)


def clean_whitespace(code: str) -> str:
    """Clean excessive whitespace while preserving structure."""
    lines = code.split('\n')
    lines = [line.rstrip() for line in lines]
    
    result = []
    blank_count = 0
    for line in lines:
        if not line.strip():
            blank_count += 1
            if blank_count <= 2:
                result.append(line)
        else:
            blank_count = 0
            result.append(line)
    
    return '\n'.join(result)

# ═══════════════════════════════════════════════════════════════════
# HELPER FUNCTIONS
# ═══════════════════════════════════════════════════════════════════


def _extract_label(obj: Dict[str, Any]) -> int:
    """Extract vulnerability label (0 or 1)."""
    for key in ("target", "label"):
        if key in obj:
            try:
                return int(obj[key])
            except (ValueError, TypeError):
                pass
    return 0


def _extract_project(obj: Dict[str, Any]) -> str:
    """Extract project name."""
    project = obj.get("project", "")
    if isinstance(project, str) and project.strip():
        return project.strip()
    return "unknown_project"


def _extract_id(obj: Dict[str, Any], fallback: int) -> int:
    """Extract original ID."""
    for key in ("id", "idx", "index"):
        if key in obj:
            try:
                return int(obj[key])
            except (ValueError, TypeError):
                pass
    return fallback


def validate_code_not_normalized(code: str) -> bool:
    """
    Check if code appears to be original (not normalized).
    
    Normalized code typically has patterns like:
    - VAR1, VAR2, FUNC1, FUNC2
    - No actual function names like strcpy, malloc, printf
    
    Returns True if code looks original, False if it looks normalized.
    """
    # Common real function names that should exist in original code
    real_functions = {
        'strcpy', 'strncpy', 'memcpy', 'malloc', 'free', 'printf',
        'sprintf', 'strlen', 'sizeof', 'fopen', 'fclose', 'read',
        'write', 'recv', 'send', 'return', 'if', 'else', 'while', 'for'
    }
    
    # Normalized patterns (generic tokens)
    normalized_patterns = ['VAR1', 'VAR2', 'FUNC1', 'FUNC2', 'LITERAL1']
    
    code_lower = code.lower()
    
    # Check for normalized patterns
    for pattern in normalized_patterns:
        if pattern.lower() in code_lower:
            return False  # Looks normalized
    
    # Check for real function names
    real_found = sum(1 for fn in real_functions if fn in code_lower)
    
    return real_found >= 2  # At least 2 real keywords found


def process_split(split_name: str, input_path: Path, output_dir: Path,
                  remove_comments: bool = False, clean_ws: bool = False) -> Dict[str, Any]:
    """Process a single split."""
    
    output_dir.mkdir(parents=True, exist_ok=True)
    
    rows = []
    stats = {
        "total_lines": 0,
        "valid_functions": 0,
        "bad_json": 0,
        "empty_func": 0,
        "normalized_warning": 0,
        "label_0": 0,
        "label_1": 0,
    }
    
    print(f"\n{'='*60}")
    print(f"Processing {split_name} split")
    print(f"Input: {input_path}")
    print(f"Output: {output_dir}")
    print(f"Remove comments: {remove_comments}")
    print(f"{'='*60}")
    
    with input_path.open("r", encoding="utf-8") as f:
        for line_no, line in enumerate(tqdm(f, desc=f"{split_name}"), start=1):
            stats["total_lines"] += 1
            line = line.strip()
            if not line:
                continue
            
            # Parse JSON
            try:
                obj = json.loads(line)
            except json.JSONDecodeError:
                stats["bad_json"] += 1
                continue
            
            # Extract function code
            func_code = obj.get("func", "")
            if not isinstance(func_code, str) or not func_code.strip():
                stats["empty_func"] += 1
                continue
            
            # Warn if code looks normalized (first 10 only)
            if stats["valid_functions"] < 10:
                if not validate_code_not_normalized(func_code):
                    if stats["normalized_warning"] == 0:
                        print(f"\n⚠️  WARNING: Code appears to be NORMALIZED!")
                        print(f"    First 100 chars: {func_code[:100]}...")
                        print(f"    This will NOT work for vulnerability detection!")
                    stats["normalized_warning"] += 1
            
            # Extract metadata
            label = _extract_label(obj)
            project = _extract_project(obj)
            orig_id = _extract_id(obj, line_no)
            
            # Track label distribution
            if label == 0:
                stats["label_0"] += 1
            else:
                stats["label_1"] += 1
            
            # Process code
            code_out = func_code.replace("\r\n", "\n").replace("\r", "\n")
            
            # Remove comments if requested
            if remove_comments:
                code_out = remove_c_comments(code_out)
            
            # Clean whitespace if requested
            if clean_ws:
                code_out = clean_whitespace(code_out)
            
            # Write .c file
            stats["valid_functions"] += 1
            file_id = f"{split_name}_func_{stats['valid_functions']:07d}.c"
            out_path = output_dir / file_id
            out_path.write_text(code_out, encoding="utf-8")
            
            rows.append({
                "function_id": file_id,
                "label": label,
                "project": project,
                "orig_index": orig_id,
            })
    
    return rows, stats


def main():
    parser = argparse.ArgumentParser(
        description="Split Devign JSONL into per-function .c files"
    )
    parser.add_argument(
        "--input-base", type=Path,
        default=Path("./datasets/devign_full/json"),
        help="Directory containing train.jsonl, test.jsonl, validation.jsonl"
    )
    parser.add_argument(
        "--output-base", type=Path,
        default=Path("./workspace/03_PerFunction_datasets/original_devign_functions"),
        help="Output directory for .c files and manifests"
    )
    parser.add_argument(
        "--remove-comments", action="store_true",
        help="Remove C/C++ comments from code"
    )
    parser.add_argument(
        "--clean-whitespace", action="store_true",
        help="Clean excessive whitespace"
    )
    parser.add_argument(
        "--splits", nargs="+", default=["train", "validation", "test"],
        help="Splits to process"
    )
    
    args = parser.parse_args()
    
    ORIGINAL_BASE = args.input_base
    OUT_BASE = args.output_base
    SPLITS = args.splits
    
    print("\n" + "="*70)
    print("DEVIGN ORIGINAL (NON-NORMALIZED) FUNCTION SPLITTER")
    print("="*70)
    print(f"\nInput base: {ORIGINAL_BASE}")
    print(f"Output base: {OUT_BASE}")
    print(f"Remove comments: {args.remove_comments}")
    print(f"Clean whitespace: {args.clean_whitespace}")
    
    OUT_BASE.mkdir(parents=True, exist_ok=True)
    
    all_stats = {}
    
    for split_name in SPLITS:
        # Try different possible input filenames
        possible_inputs = [
            ORIGINAL_BASE / f"{split_name}.jsonl",
            ORIGINAL_BASE / f"{split_name}.json",
            ORIGINAL_BASE / f"devign_{split_name}.jsonl",
        ]
        
        input_path = None
        for p in possible_inputs:
            if p.exists():
                input_path = p
                break
        
        if input_path is None:
            print(f"\n⚠️  No input found for {split_name} split")
            print(f"   Tried: {[str(p) for p in possible_inputs]}")
            continue
        
        output_dir = OUT_BASE / split_name
        rows, stats = process_split(
            split_name, input_path, output_dir,
            remove_comments=args.remove_comments,
            clean_ws=args.clean_whitespace
        )
        all_stats[split_name] = stats
        
        # Write manifest
        manifest_path = OUT_BASE / f"manifest_{split_name}.csv"
        with manifest_path.open("w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(f, fieldnames=["function_id", "label", "project", "orig_index"])
            writer.writeheader()
            writer.writerows(rows)
        
        print(f"\n✅ {split_name} complete:")
        print(f"   Functions: {stats['valid_functions']}")
        print(f"   Labels: {stats['label_0']} safe, {stats['label_1']} vulnerable")
        print(f"   Manifest: {manifest_path}")
        
        if stats["normalized_warning"] > 0:
            print(f"\n   ⚠️  {stats['normalized_warning']} functions appear NORMALIZED!")
            print(f"      You may need to use the ORIGINAL Devign dataset!")
    
    # Summary
    print("\n" + "="*70)
    print("SUMMARY")
    print("="*70)
    
    total_funcs = sum(s.get("valid_functions", 0) for s in all_stats.values())
    total_vuln = sum(s.get("label_1", 0) for s in all_stats.values())
    total_safe = sum(s.get("label_0", 0) for s in all_stats.values())
    
    print(f"Total functions: {total_funcs}")
    print(f"Vulnerable: {total_vuln} ({100*total_vuln/max(total_funcs,1):.1f}%)")
    print(f"Safe: {total_safe} ({100*total_safe/max(total_funcs,1):.1f}%)")
    print(f"\nOutput: {OUT_BASE}")
    
    # Check for normalization issues
    total_normalized = sum(s.get("normalized_warning", 0) for s in all_stats.values())
    if total_normalized > 0:
        print(f"\n🚨 WARNING: {total_normalized} functions appear to be NORMALIZED!")
        print("   For vulnerability detection, you need ORIGINAL code with:")
        print("   - Real function names (strcpy, malloc, printf, etc.)")
        print("   - Real variable names")
        print("   - Real string literals")
        print("\n   Please check your input JSONL files!")


if __name__ == "__main__":
    main()



"""
python 01c_split_per_function_devign.py \
    --input-base "./datasets/devign_full/json" \
    --output-base "./workspace/03_PerFunction_datasets/original_devign_functions" \
    --remove-comments \
    --clean-whitespace
"""    