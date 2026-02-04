#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
remove_c_comments.py - Intelligently remove C/C++ comments

Handles:
- Single-line comments: // comment
- Multi-line comments: /* comment */
- Nested edge cases
- String literals (doesn't remove // or /* inside strings)
- Preserves line structure for accurate line numbers

Usage:
    # Process a single file
    python remove_c_comments.py --input file.c --output file_clean.c
    
    # Process entire directory
    python remove_c_comments.py --input-dir /path/to/functions --output-dir /path/to/clean
    
    # Process JSONL and output clean JSONL
    python remove_c_comments.py --input-jsonl data.jsonl --output-jsonl data_clean.jsonl
"""

import re
import json
import argparse
from pathlib import Path
from typing import Optional
from tqdm import tqdm


def remove_c_comments(code: str) -> str:
    """
    Remove C/C++ comments while preserving string literals and code structure.
    
    Handles:
    - // single line comments
    - /* multi-line comments */
    - Comments inside strings are preserved (not removed)
    - Preserves newlines to maintain line numbers
    """
    if not code:
        return code
    
    result = []
    i = 0
    n = len(code)
    
    while i < n:
        # Check for string literal (double quotes)
        if code[i] == '"':
            # Copy entire string literal including contents
            result.append(code[i])
            i += 1
            while i < n:
                if code[i] == '\\' and i + 1 < n:
                    # Escape sequence - copy both chars
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
        
        # Check for character literal (single quotes)
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
        
        # Check for single-line comment
        elif code[i:i+2] == '//':
            # Skip until end of line, but keep the newline
            while i < n and code[i] != '\n':
                i += 1
            # Keep the newline
            if i < n:
                result.append(code[i])
                i += 1
        
        # Check for multi-line comment
        elif code[i:i+2] == '/*':
            i += 2
            # Count newlines to preserve line structure
            newlines = 0
            while i < n:
                if code[i:i+2] == '*/':
                    i += 2
                    break
                if code[i] == '\n':
                    newlines += 1
                i += 1
            # Preserve newlines to maintain line numbers
            result.append('\n' * newlines)
        
        # Regular character
        else:
            result.append(code[i])
            i += 1
    
    return ''.join(result)


def clean_whitespace(code: str) -> str:
    """
    Clean up excessive whitespace while preserving structure.
    
    - Removes trailing whitespace on each line
    - Collapses multiple blank lines into max 2
    - Preserves indentation
    """
    lines = code.split('\n')
    
    # Remove trailing whitespace
    lines = [line.rstrip() for line in lines]
    
    # Collapse multiple blank lines
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


def process_code(code: str, remove_comments: bool = True, clean_ws: bool = True) -> str:
    """Process code with optional comment removal and whitespace cleaning."""
    if remove_comments:
        code = remove_c_comments(code)
    if clean_ws:
        code = clean_whitespace(code)
    return code


def process_file(input_path: Path, output_path: Path) -> bool:
    """Process a single .c file."""
    try:
        code = input_path.read_text(encoding='utf-8', errors='replace')
        clean_code = process_code(code)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(clean_code, encoding='utf-8')
        return True
    except Exception as e:
        print(f"Error processing {input_path}: {e}")
        return False


def process_directory(input_dir: Path, output_dir: Path) -> dict:
    """Process all .c files in a directory."""
    stats = {"success": 0, "failed": 0}
    
    c_files = list(input_dir.rglob("*.c"))
    print(f"Found {len(c_files)} .c files")
    
    for c_file in tqdm(c_files, desc="Processing"):
        rel_path = c_file.relative_to(input_dir)
        out_path = output_dir / rel_path
        
        if process_file(c_file, out_path):
            stats["success"] += 1
        else:
            stats["failed"] += 1
    
    return stats


def process_jsonl(input_path: Path, output_path: Path) -> dict:
    """Process JSONL file, cleaning the 'func' field."""
    stats = {"total": 0, "success": 0, "failed": 0}
    
    with input_path.open('r', encoding='utf-8') as fin, \
         output_path.open('w', encoding='utf-8') as fout:
        
        for line in tqdm(fin, desc="Processing JSONL"):
            stats["total"] += 1
            line = line.strip()
            if not line:
                continue
            
            try:
                obj = json.loads(line)
                if 'func' in obj and isinstance(obj['func'], str):
                    obj['func'] = process_code(obj['func'])
                fout.write(json.dumps(obj, ensure_ascii=False) + '\n')
                stats["success"] += 1
            except Exception as e:
                stats["failed"] += 1
                # Write original line on failure
                fout.write(line + '\n')
    
    return stats


def test_comment_removal():
    """Test the comment removal function."""
    
    test_cases = [
        # Basic single-line comment
        (
            'int x = 5; // this is a comment\nint y = 6;',
            'int x = 5; \nint y = 6;'
        ),
        # Multi-line comment
        (
            'int x = 5; /* comment */ int y = 6;',
            'int x = 5;  int y = 6;'
        ),
        # Multi-line spanning lines
        (
            'int x = 5;\n/* line 1\nline 2 */\nint y = 6;',
            'int x = 5;\n\n\nint y = 6;'
        ),
        # Comment-like content in string
        (
            'char *s = "// not a comment";',
            'char *s = "// not a comment";'
        ),
        # Comment-like content in string 2
        (
            'char *s = "/* also not */";',
            'char *s = "/* also not */";'
        ),
        # Escaped quote in string
        (
            'char *s = "say \\"hi\\""; // comment',
            'char *s = "say \\"hi\\""; \n'
        ),
    ]
    
    print("Testing comment removal...")
    all_passed = True
    
    for i, (input_code, expected) in enumerate(test_cases):
        result = remove_c_comments(input_code)
        # Normalize for comparison
        result_norm = result.rstrip()
        expected_norm = expected.rstrip()
        
        if result_norm == expected_norm:
            print(f"  Test {i+1}: ✅ PASS")
        else:
            print(f"  Test {i+1}: ❌ FAIL")
            print(f"    Input:    {repr(input_code)}")
            print(f"    Expected: {repr(expected)}")
            print(f"    Got:      {repr(result)}")
            all_passed = False
    
    return all_passed


def main():
    parser = argparse.ArgumentParser(description="Remove C/C++ comments from code")
    
    parser.add_argument("--input", type=Path, help="Input .c file")
    parser.add_argument("--output", type=Path, help="Output .c file")
    parser.add_argument("--input-dir", type=Path, help="Input directory with .c files")
    parser.add_argument("--output-dir", type=Path, help="Output directory")
    parser.add_argument("--input-jsonl", type=Path, help="Input JSONL file")
    parser.add_argument("--output-jsonl", type=Path, help="Output JSONL file")
    parser.add_argument("--test", action="store_true", help="Run tests")
    
    args = parser.parse_args()
    
    if args.test:
        success = test_comment_removal()
        print("\n" + ("All tests passed! ✅" if success else "Some tests failed! ❌"))
        return
    
    if args.input and args.output:
        print(f"Processing {args.input} -> {args.output}")
        if process_file(args.input, args.output):
            print("✅ Done")
        else:
            print("❌ Failed")
    
    elif args.input_dir and args.output_dir:
        print(f"Processing directory {args.input_dir} -> {args.output_dir}")
        stats = process_directory(args.input_dir, args.output_dir)
        print(f"✅ Success: {stats['success']}, Failed: {stats['failed']}")
    
    elif args.input_jsonl and args.output_jsonl:
        print(f"Processing JSONL {args.input_jsonl} -> {args.output_jsonl}")
        stats = process_jsonl(args.input_jsonl, args.output_jsonl)
        print(f"✅ Total: {stats['total']}, Success: {stats['success']}, Failed: {stats['failed']}")
    
    else:
        parser.print_help()
        print("\nExample usage:")
        print("  python remove_c_comments.py --test")
        print("  python remove_c_comments.py --input code.c --output clean.c")
        print("  python remove_c_comments.py --input-dir ./functions --output-dir ./clean")
        print("  python remove_c_comments.py --input-jsonl train.jsonl --output-jsonl train_clean.jsonl")


if __name__ == "__main__":
    main()


  