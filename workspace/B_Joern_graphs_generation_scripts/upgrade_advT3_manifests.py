#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Upgrade advT* manifests (index,label[,commit],json_path) into a fully enriched schema:

  function_id,label,project,nodes,edges,code_path,graph_json_path

• Uses a mapping CSV (e.g., staging_manifest_<split>.csv) to resolve the true dataset
  project (e.g., "debian", "chrome") and the canonical function_id ("test_func_0000001").
• Falls back sensibly to path-derived hints when mapping is missing.
• Optionally peeks each JSON to fill nodes/edges (heuristic, lightweight).

CLI example:
  python upgrade_advT3_manifests.py \
    --src /.../staging_manifest_test_advT3.csv \
    --out /.../staging_manifest_test_advT3_plus.csv \
    --map /.../staging_manifest_test.csv \
    --json-root /.../Clean_exports/normalized_reveal_graphson/test \
    --compute-sizes
"""

import csv
import json
import re
import sys
from pathlib import Path
from typing import Dict, Optional, Tuple, List, Any, Set

FULL_HEADER = ["function_id", "label", "project", "nodes", "edges", "code_path", "graph_json_path"]


# -------------------------------
# Helpers
# -------------------------------

def _infer_project_from_json_path(json_path: str) -> str:
    """
    Infer a function-folder bucket from a JSON path.

    Handles:
      .../exports/test_func_0000001/export_all/snap_adv1_nocm.json
      .../exports/test_func_0000001/export_all/export.json

    Strategy:
      1) parent folder of 'export_all'
      2) segment right after 'exports'
      3) regex for test_func_<digits>
      4) parent directory name
      5) 'unknown'
    """
    if not json_path:
        return "unknown"

    p = Path(json_path)
    parts = [str(x) for x in p.parts]

    # 1) Use parent folder of 'export_all'
    try:
        idx = len(parts) - 1 - parts[::-1].index("export_all")
        if idx - 1 >= 0:
            cand = parts[idx - 1]
            if cand:
                return cand
    except ValueError:
        pass

    # 2) Segment right after 'exports'
    for i, seg in enumerate(parts):
        if seg == "exports" and i + 1 < len(parts):
            cand = parts[i + 1]
            if cand:
                return cand

    # 3) Regex fallback
    m = re.search(r"(test_func_\d+)", str(p).replace("\\", "/"))
    if m:
        return m.group(1)

    # 4) Parent folder name
    parent = p.parent.name
    if parent:
        return parent

    # 5) Unknown
    return "unknown"


def _load_project_map(csv_with_project: Optional[Path]) -> Tuple[Dict[str, str], Dict[str, str]]:
    """
    Build maps from a staging manifest (with 'function_id' and 'project'):

    Returns:
      proj_map: key -> project
      canon_map: key -> canonical function_id (e.g., "test_func_0000001")

    The same project/canonical func_id can be retrieved by multiple keys:
      - 'function_id' (e.g., "test_func_0000001")
      - numeric suffix (padded): "0000001"
      - numeric suffix (non-padded): "1"
      - function folder derived from graph_json_path: "test_func_0000001"
    """
    proj_map: Dict[str, str] = {}
    canon_map: Dict[str, str] = {}

    if not csv_with_project or not csv_with_project.exists():
        return proj_map, canon_map

    with csv_with_project.open("r", encoding="utf-8") as f:
        r = csv.DictReader(f)
        cols = {c.lower(): c for c in (r.fieldnames or [])}

        k_func  = cols.get("function_id")
        k_proj  = cols.get("project")
        k_gjson = cols.get("graph_json_path")

        if not k_proj:
            return proj_map, canon_map

        for row in r:
            proj = (row.get(k_proj) or "").strip()
            if not proj:
                continue

            func_id_str = (row.get(k_func) or "").strip() if k_func else ""
            if func_id_str:
                # Primary entries
                proj_map[func_id_str] = proj
                canon_map[func_id_str] = func_id_str

                # Numeric variants
                m = re.search(r'(\d+)$', func_id_str)
                if m:
                    padded = m.group(1)                # "0000001"
                    try:
                        non_padded = str(int(padded))  # "1"
                    except Exception:
                        non_padded = None

                    proj_map.setdefault(padded, proj)
                    canon_map.setdefault(padded, func_id_str)

                    if non_padded is not None:
                        proj_map.setdefault(non_padded, proj)
                        canon_map.setdefault(non_padded, func_id_str)

            # Derive function folder from graph_json_path
            if k_gjson and row.get(k_gjson):
                gpath = str(row[k_gjson]).strip().replace('\\', '/')
                m2 = re.search(r'/exports/([^/]+)/export_all/', gpath)
                if m2:
                    func_folder = m2.group(1)  # e.g., "test_func_0000001"
                    proj_map.setdefault(func_folder, proj)
                    # Prefer canonical from function_id; else use folder itself
                    canon_map.setdefault(func_folder, func_id_str or func_folder)

    return proj_map, canon_map


def _peek_nodes_edges(json_root: Optional[Path], rel_json: str) -> Tuple[str, str]:
    """
    Lightweight heuristic to count nodes/edges in a GraphSON file.
    Returns ('','') if disabled/missing/error.
    """
    if not json_root or not rel_json:
        return "", ""
    jp = (json_root / rel_json)
    if not jp.exists():
        return "", ""
    try:
        with jp.open("r", encoding="utf-8") as f:
            obj = json.load(f)

        nodes = 0
        edges = 0

        def walk(o: Any):
            nonlocal nodes, edges
            if isinstance(o, list) and o and isinstance(o[0], dict):
                sample = o[: min(24, len(o))]
                has_src = any(("src" in d or "from" in d or "out" in d or "outV" in d) for d in sample)
                has_dst = any(("dst" in d or "to"   in d or "in"  in d or "inV"  in d) for d in sample)
                has_id  = any(("id"  in d or "_id" in d or "@id" in d)           for d in sample)
                if has_src and has_dst:
                    edges = max(edges, len(o))
                elif has_id:
                    nodes = max(nodes, len(o))
            elif isinstance(o, dict):
                for v in o.values():
                    walk(v)

        walk(obj)
        return (str(nodes) if nodes else "", str(edges) if edges else "")
    except Exception:
        return "", ""


def _find_orig_candidate(json_root: Optional[Path], func_folder: str) -> str:
    """
    Prefer: exports/<func_folder>/export_all/export.json
    Else any 'snap*orig*.json'.
    If json_root is None, return the canonical relative 'export.json' without FS checks.
    """
    rel = f"exports/{func_folder}/export_all/export.json"
    if not json_root:
        return rel
    base = json_root / "exports" / func_folder / "export_all"
    if base.exists():
        p = base / "export.json"
        if p.exists():
            return str(Path("exports") / func_folder / "export_all" / "export.json")
        for cand in base.glob("snap*orig*.json"):
            return str(Path("exports") / func_folder / "export_all" / cand.name)
    return ""


def _looks_like_advT_header(header: List[str]) -> bool:
    """
    Accept either:
      ["index","label","commit","json_path"]  or
      ["index","label","json_path"]
    """
    h = [c.strip().lower() for c in (header or [])]
    return (h == ["index","label","commit","json_path"]) or (h == ["index","label","json_path"])


def resolve_project(fid: str, jrel: str, proj_map: Dict[str, str]) -> str:
    """
    Best-effort dataset project resolver:
      1) mapping by fid ("1", "0000001", "test_func_0000001")
      2) mapping by func-folder from path ("exports/<func>/...")
      3) infer from path (function folder)
      4) 'unknown'
    Mapping always wins over inference.
    """
    # 1) Direct key
    if fid in proj_map:
        return proj_map[fid]

    # 1b) Numeric variants
    try:
        n = int(fid)
        non_padded = str(n)
        padded = f"{n:07d}"  # 7 digits typical of Reveal naming (0000001)
        if non_padded in proj_map:
            return proj_map[non_padded]
        if padded in proj_map:
            return proj_map[padded]
    except Exception:
        pass

    # 2) Function folder from path
    if jrel:
        m = re.search(r'exports/([^/]+)/export_all', jrel.replace('\\', '/'))
        if m:
            func_from_path = m.group(1)
            if func_from_path in proj_map:
                return proj_map[func_from_path]

    # 3) Fallback: infer function-folder; this is NOT the dataset project but better than empty.
    inf = _infer_project_from_json_path(jrel)
    return inf if inf and inf.lower() not in ("unknown", "none", "nan") else "unknown"


def _resolve_canonical_fid(fid: str, paths: List[str], canon_map: Dict[str, str]) -> str:
    """
    Produce the canonical function_id string to write (e.g., "test_func_0000001")
    from the numeric adv manifest fid plus any available path hints or mapping.
    """
    # 1) Direct key
    if fid in canon_map:
        return canon_map[fid]

    # 1b) Numeric variants
    try:
        n = int(fid)
        non_padded = str(n)
        padded = f"{n:07d}"
        if non_padded in canon_map:
            return canon_map[non_padded]
        if padded in canon_map:
            return canon_map[padded]
    except Exception:
        pass

    # 2) Derive from any path: /exports/<func_folder>/export_all/...
    if paths:
        m = re.search(r'exports/([^/]+)/export_all', paths[0].replace('\\', '/'))
        if m:
            func_folder = m.group(1)
            if func_folder in canon_map:
                return canon_map[func_folder]
            return func_folder  # readable fallback

    # 3) Synthesize stable readable fallback from numeric fid
    try:
        return f"test_func_{int(fid):07d}"
    except Exception:
        return fid  # last resort


# -------------------------------
# Main upgrade
# -------------------------------

def upgrade_advT(
    src_csv: Path,
    out_csv: Path,
    mapping_csv: Optional[Path] = None,
    json_root: Optional[Path] = None,
    compute_sizes: bool = False
):
    """
    Convert advT CSV (index,label[,commit],json_path) into FULL_HEADER:
       function_id,label,project,nodes,edges,code_path,graph_json_path

    Behavior:
      • Uses mapping CSV to resolve dataset-level 'project' and canonical 'function_id'
      • Always writes canonical function_id (e.g., "test_func_0000001")
      • For rows with missing 'export.json' in advT, synthesizes an origin row when possible
      • Optionally peeks nodes/edges from JSON (heuristic)
    """
    out_csv.parent.mkdir(parents=True, exist_ok=True)
    proj_map, canon_map = _load_project_map(mapping_csv) if mapping_csv else ({}, {})

    with src_csv.open("r", encoding="utf-8") as f_in:
        r = csv.DictReader(f_in)
        if not _looks_like_advT_header(r.fieldnames or []):
            raise RuntimeError(f"{src_csv} does not look like an adv manifest (index,label,commit?,json_path).")

        cols = {c.lower(): c for c in (r.fieldnames or [])}
        k_idx   = cols.get("index")
        k_label = cols.get("label")
        k_json  = cols.get("json_path")

        rows: List[Dict[str, str]] = list(r)

        # Group rows per numeric 'index' (fid) and collect their json paths
        groups: Dict[str, Dict[str, Any]] = {}
        for row in rows:
            fid = (row.get(k_idx) or "").strip()
            lab = (row.get(k_label) or "").strip()
            jrel = (row.get(k_json) or "").strip()

            g = groups.setdefault(fid, {"label": lab, "paths": [], "blank_rows": 0, "project_hint": None})
            if jrel:
                g["paths"].append(jrel)
                # collect hint from the path (function folder)
                hint = _infer_project_from_json_path(jrel)
                if hint and hint.lower() not in ("unknown", "none", "nan"):
                    g["project_hint"] = g["project_hint"] or hint
            else:
                g["blank_rows"] += 1

        # Resolve project and canonical function_id per fid
        project_by_fid: Dict[str, str] = {}
        canon_fid_by_fid: Dict[str, str] = {}

        for fid, g in groups.items():
            first_path = g["paths"][0] if g["paths"] else ""
            proj = resolve_project(fid, first_path, proj_map)

            # If resolver returns only a func-folder (e.g., test_func_0000001),
            # and we have a better hint, prefer the hint only if mapping was unknown.
            if proj.lower() in ("unknown", "none", "nan"):
                hint = g.get("project_hint")
                if hint and hint.lower() not in ("unknown", "none", "nan"):
                    # NOTE: 'hint' is typically the function folder, *not* dataset project.
                    # Keep as unknown at dataset level; do not override with hint-as-project.
                    pass

            project_by_fid[fid] = proj if proj else "unknown"
            canon_fid_by_fid[fid] = _resolve_canonical_fid(fid, g["paths"], canon_map)

        # Optional debug peek
        # print("[Debug] project_by_fid sample:", list(project_by_fid.items())[:8])
        # print("[Debug] canon_fid_by_fid sample:", list(canon_fid_by_fid.items())[:8])

        # Write output
        seen: Set[Tuple[str, str]] = set()  # (fid, rel_path)
        with out_csv.open("w", encoding="utf-8", newline="") as f_out:
            w = csv.DictWriter(f_out, fieldnames=FULL_HEADER)
            w.writeheader()

            for fid, g in groups.items():
                label = g["label"]
                project = project_by_fid.get(fid, "unknown")
                func_id_out = canon_fid_by_fid.get(fid, fid)

                # Extract function folder to locate export.json for synthesized origin rows
                func_folder = None
                if g["paths"]:
                    m = re.search(r'exports/([^/]+)/export_all', g["paths"][0].replace('\\', '/'))
                    if m:
                        func_folder = m.group(1)

                # (a) If blank origin rows were present, synthesize an origin entry when possible
                if g["blank_rows"] > 0 and func_folder:
                    cand = _find_orig_candidate(json_root, func_folder)
                    if cand and (fid, cand) not in seen:
                        nodes, edges = _peek_nodes_edges(json_root, cand) if compute_sizes else ("", "")
                        w.writerow({
                            "function_id": func_id_out,   # canonical ID
                            "label": label,
                            "project": project,           # dataset project (e.g., debian/chrome)
                            "nodes": nodes,
                            "edges": edges,
                            "code_path": "",
                            "graph_json_path": cand,
                        })
                        seen.add((fid, cand))

                # (b) add all non-empty adv paths; keep dataset project unchanged
                for jrel in g["paths"]:
                    if (fid, jrel) in seen:
                        continue
                    nodes, edges = _peek_nodes_edges(json_root, jrel) if compute_sizes else ("", "")
                    w.writerow({
                        "function_id": func_id_out,   # canonical ID
                        "label": label,
                        "project": project,           # dataset project
                        "nodes": nodes,
                        "edges": edges,
                        "code_path": "",
                        "graph_json_path": jrel,
                    })
                    seen.add((fid, jrel))

    print(f"[OK] Wrote upgraded manifest → {out_csv}")


# -------------------------------
# CLI
# -------------------------------

if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser("Upgrade advT manifests to full schema")
    ap.add_argument("--src", required=True, help="Path to adv manifest CSV (index,label,commit?,json_path)")
    ap.add_argument("--out", required=True, help="Where to write the upgraded CSV")
    ap.add_argument("--map", default=None, help="CSV with 'function_id' and 'project' (e.g., staging_manifest_<split>.csv)")
    ap.add_argument("--json-root", default=None, help="Root where 'exports/<func_folder>/export_all' lives (enables origin discovery and size peek)")
    ap.add_argument("--compute-sizes", action="store_true", help="Peek JSON to fill nodes/edges (slower)")
    args = ap.parse_args()

    src = Path(args.src)
    out = Path(args.out)
    mapping = Path(args.map) if args.map else None
    root = Path(args.json_root) if args.json_root else None

    # Allow any advT manifest name (T3, T6, etc.)
    upgrade_advT(src, out, mapping_csv=mapping, json_root=root, compute_sizes=args.compute_sizes)


"""
python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_reveal_graphson/test/staging_manifest_test_advT3.csv \
  --out ./Clean_exports/normalized_reveal_graphson/test/staging_manifest_test_advT3_plus.csv \
  --map ./Clean_exports/normalized_reveal_graphson/test/staging_manifest_test.csv \
  --json-root ./Clean_exports/normalized_reveal_graphson/test \
  --compute-sizes


python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_reveal_graphson/train/staging_manifest_train_advT3.csv \
  --out ./Clean_exports/normalized_reveal_graphson/train/staging_manifest_train_advT3_plus.csv \
  --map ./Clean_exports/normalized_reveal_graphson/train/staging_manifest_train.csv \
  --json-root ./Clean_exports/normalized_reveal_graphson/train \
  --compute-sizes    


python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_reveal_graphson/valid/staging_manifest_valid_advT3.csv \
  --out ./Clean_exports/normalized_reveal_graphson/valid/staging_manifest_valid_advT3_plus.csv \
  --map ./Clean_exports/normalized_reveal_graphson/valid/staging_manifest_valid.csv \
  --json-root ./Clean_exports/normalized_reveal_graphson/valid \
  --compute-sizes

 ##################################################################################


  python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3.csv \
  --out ./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv \
  --map ./Clean_exports/normalized_devign_graphson/test/staging_manifest_test.csv \
  --json-root ./Clean_exports/normalized_devign_graphson/test \
  --compute-sizes


python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3.csv \
  --out ./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv \
  --map ./Clean_exports/normalized_devign_graphson/train/staging_manifest_train.csv \
  --json-root ./Clean_exports/normalized_devign_graphson/train \
  --compute-sizes    


python upgrade_advT3_manifests.py \
  --src ./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3.csv \
  --out ./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv \
  --map ./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid.csv \
  --json-root ./Clean_exports/normalized_devign_graphson/valid \
  --compute-sizes
"""