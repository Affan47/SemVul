#!/usr/bin/env python3
"""
diagnose_cpg_exports.py - Check CPG exports for parsing quality

This script analyzes GraphSON exports to detect:
1. UNKNOWN nodes (parsing failures)
2. Missing critical node types (CALL, IDENTIFIER, etc.)
3. Edge type coverage
4. Normalization quality

Usage:
    # Check single file
    python diagnose_cpg_exports.py --input export.json
    
    # Check directory of exports
    python diagnose_cpg_exports.py --input-dir /path/to/exports --sample 100
"""

import argparse
import json
import os
import random
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List, Set, Tuple


def analyze_export(filepath: Path) -> Dict:
    """Analyze a single GraphSON export file."""
    result = {
        'file': str(filepath),
        'parse_ok': True,
        'issues': [],
        'node_types': Counter(),
        'edge_types': Counter(),
        'has_unknown': False,
        'unknown_code': '',
        'missing_critical': [],
    }
    
    try:
        with open(filepath, 'r') as f:
            data = json.load(f)
    except Exception as e:
        result['parse_ok'] = False
        result['issues'].append(f"JSON parse error: {e}")
        return result
    
    try:
        vertices = data['@value']['vertices']
        edges = data['@value']['edges']
    except KeyError:
        result['parse_ok'] = False
        result['issues'].append("Invalid GraphSON structure")
        return result
    
    # Count node types
    for v in vertices:
        label = v.get('label', 'UNKNOWN')
        result['node_types'][label] += 1
        
        if label == 'UNKNOWN':
            result['has_unknown'] = True
            props = v.get('properties', {})
            code = props.get('CODE', {}).get('@value', {}).get('@value', [''])[0]
            parser_type = props.get('PARSER_TYPE_NAME', {}).get('@value', {}).get('@value', [''])[0]
            result['unknown_code'] = code[:500] if code else ''
            result['issues'].append(f"UNKNOWN node with parser error: {parser_type}")
    
    # Count edge types
    for e in edges:
        label = e.get('label', 'UNKNOWN')
        result['edge_types'][label] += 1
    
    # Check for critical node types
    critical_nodes = {'CALL', 'IDENTIFIER', 'LITERAL', 'LOCAL', 'CONTROL_STRUCTURE'}
    present_nodes = set(result['node_types'].keys())
    missing = critical_nodes - present_nodes
    
    if missing:
        result['missing_critical'] = list(missing)
        result['issues'].append(f"Missing critical nodes: {missing}")
    
    return result


def analyze_directory(input_dir: Path, sample_size: int = 100) -> List[Dict]:
    """Analyze multiple exports from a directory."""
    # Find all export files
    export_files = []
    for pattern in ['*.json', '**/export.json', '**/*.graphson']:
        export_files.extend(input_dir.glob(pattern))
    
    export_files = list(set(export_files))
    print(f"Found {len(export_files)} export files")
    
    if len(export_files) > sample_size:
        random.seed(42)
        export_files = random.sample(export_files, sample_size)
        print(f"Sampling {sample_size} files")
    
    results = []
    for i, f in enumerate(export_files):
        if (i + 1) % 20 == 0:
            print(f"  Analyzed {i+1}/{len(export_files)}...")
        results.append(analyze_export(f))
    
    return results


def print_summary(results: List[Dict]):
    """Print analysis summary."""
    print("\n" + "=" * 70)
    print("CPG EXPORT ANALYSIS SUMMARY")
    print("=" * 70)
    
    total = len(results)
    unknown_count = sum(1 for r in results if r['has_unknown'])
    missing_critical = sum(1 for r in results if r['missing_critical'])
    parse_errors = sum(1 for r in results if not r['parse_ok'])
    
    print(f"\n📊 OVERALL STATISTICS:")
    print(f"  Total files analyzed: {total}")
    print(f"  JSON parse errors: {parse_errors} ({100*parse_errors/total:.1f}%)")
    print(f"  Files with UNKNOWN nodes: {unknown_count} ({100*unknown_count/total:.1f}%)")
    print(f"  Files missing critical nodes: {missing_critical} ({100*missing_critical/total:.1f}%)")
    
    # Aggregate node types
    all_node_types = Counter()
    all_edge_types = Counter()
    for r in results:
        all_node_types.update(r['node_types'])
        all_edge_types.update(r['edge_types'])
    
    print(f"\n🏷️ NODE TYPES ACROSS ALL FILES:")
    for node_type, count in all_node_types.most_common():
        print(f"  {node_type}: {count}")
    
    print(f"\n🔗 EDGE TYPES ACROSS ALL FILES:")
    for edge_type, count in all_edge_types.most_common():
        print(f"  {edge_type}: {count}")
    
    # Check for new/unusual types
    known_edges = {'AST', 'CFG', 'CDG', 'PDG', 'DDG', 'REACHING_DEF', 'CONTAINS', 
                   'REF', 'CALL', 'ARGUMENT', 'RECEIVER', 'CONDITION', 'BINDS',
                   'BINDS_TO', 'PARAMETER_LINK', 'SOURCE_FILE', 'DOMINATE', 
                   'POST_DOMINATE', 'CAPTURED_BY', 'INHERITS_FROM', 'ALIAS_OF',
                   'EVAL_TYPE', 'CDG'}
    
    new_edges = set(all_edge_types.keys()) - known_edges
    if new_edges:
        print(f"\n🆕 NEW/UNUSUAL EDGE TYPES: {new_edges}")
    
    # Issues summary
    all_issues = Counter()
    for r in results:
        for issue in r['issues']:
            # Truncate long issues
            short_issue = issue[:80]
            all_issues[short_issue] += 1
    
    if all_issues:
        print(f"\n⚠️ TOP ISSUES:")
        for issue, count in all_issues.most_common(10):
            print(f"  [{count}x] {issue}")
    
    # Sample problematic files
    problematic = [r for r in results if r['has_unknown'] or r['missing_critical']]
    if problematic:
        print(f"\n📝 SAMPLE PROBLEMATIC FILES:")
        for r in problematic[:5]:
            print(f"\n  File: {r['file']}")
            for issue in r['issues'][:3]:
                print(f"    • {issue}")
    
    # Quality assessment
    print("\n" + "=" * 70)
    print("QUALITY ASSESSMENT")
    print("=" * 70)
    
    if unknown_count > total * 0.1:
        print(f"\n🔴 CRITICAL: {100*unknown_count/total:.0f}% of files have parsing errors!")
        print("   The CPGs are incomplete. GNN training will suffer.")
        print("   Possible causes:")
        print("   - Missing header stubs")
        print("   - Syntax errors in normalized code")
        print("   - Joern version issues")
    elif unknown_count > 0:
        print(f"\n⚠️ WARNING: {unknown_count} files have parsing errors")
    else:
        print("\n✅ All files parsed successfully!")
    
    if missing_critical > total * 0.5:
        print(f"\n🔴 CRITICAL: {100*missing_critical/total:.0f}% missing critical nodes!")
    
    # Recommendations
    print("\n📋 RECOMMENDATIONS:")
    if 'EVAL_TYPE' in all_edge_types:
        print("  ✅ EVAL_TYPE edge found - add to edge vocabulary!")
    if unknown_count > 0:
        print("  • Check header stubs for undefined types")
        print("  • Review normalization script for syntax issues")
        print("  • Consider using Joern's fuzzy parser mode")


def main():
    parser = argparse.ArgumentParser(description="Diagnose CPG export quality")
    parser.add_argument("--input", type=str, help="Single export file to analyze")
    parser.add_argument("--input-dir", type=str, help="Directory of exports")
    parser.add_argument("--sample", type=int, default=100, help="Max files to sample")
    
    args = parser.parse_args()
    
    if args.input:
        results = [analyze_export(Path(args.input))]
    elif args.input_dir:
        results = analyze_directory(Path(args.input_dir), args.sample)
    else:
        parser.error("Either --input or --input-dir required")
    
    print_summary(results)


if __name__ == "__main__":
    main()


"""
python diagnose_cpg_exports.py \
    --input-dir ./CPGs/normalized_devign_functions/train \
    --sample 200

"""    