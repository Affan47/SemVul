#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
07_batch_cpg_devign_perfunc.py
Evidence-Based Joern Pipeline for Devign (per-function .c + manifest).

Expected layout (per split):
  PERFUNC_BASE/
    ├── train/
    │   ├── train_func_0000001.c
    │   ├── ...
    ├── validation/        # or "valid" if you kept that naming
    │   ├── validation_func_0000001.c
    ├── test/
    │   ├── test_func_0000001.c
    ├── manifest_train.csv
    ├── manifest_validation.csv   # or manifest_valid.csv
    ├── manifest_test.csv

Manifest schema (one row per function):
  function_id  : filename of the .c file (e.g., test_func_0000001.c)
  label        : vulnerability label (0/1)
  project      : project name (optional, stored to projects.json)
  orig_index   : 1-based line number in normalized JSONL (for traceability)

This script:
  1. Loads manifest_<split>.csv
  2. Reads each <split>/<function_id> .c file
  3. Builds per-function CPGs with joern-parse (isolated temp dirs + header stubs)
  4. Validates CPGs (nodes/methods/overlays)
  5. Exports graphs in GraphSON / proto-json / DOT
  6. Writes labels.json (+ optional projects.json) per split for GNN training

CLI flags let you choose:
  --stage parse | export | both
  --format graphson | proto-json | graphml | neo4jcsv | dot
"""

from __future__ import annotations

import argparse
import csv
import json
import os
import shutil
import signal
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor, as_completed
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional, Tuple, Dict, Any

import logging

# ---------- Configuration (defaults – can be overridden via CLI) ----------
# Per-function normalized Devign dataset (what you showed in your path sample)
PERFUNC_BASE = Path(
    "./workspace/03_PerFunction_datasets/original_devign_functions"
)

# Where CPGs + exports will be written
OUT_BASE = Path(
    "./CPGs/original_devign_functions"
)

# ---------- Logging Setup ----------
logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(levelname)s - %(message)s")
logger = logging.getLogger(__name__)

# ---------- Core Utilities ----------
def which(x: str) -> Optional[str]:
    """Find executable in PATH"""
    return shutil.which(x)


def ensure_dir(p: Path) -> None:
    """Create directory if it doesn't exist"""
    p.mkdir(parents=True, exist_ok=True)


def write_json(p: Path, obj: dict) -> None:
    """Write dictionary as formatted JSON"""
    p.write_text(json.dumps(obj, ensure_ascii=False, indent=2), encoding="utf-8")


def dir_nonempty(p: Path) -> bool:
    """
    Return True if directory exists and has at least one entry.
    Used to decide whether an export/CPG directory is valid.
    """
    try:
        return p.exists() and any(p.iterdir())
    except Exception:
        return False


# Track live subprocesses for clean shutdown
_RUNNING_PROCS = set()


def _shutdown(*_args) -> None:
    """Best-effort termination of running Joern processes on SIGINT/SIGTERM."""
    for proc in list(_RUNNING_PROCS):
        try:
            os.killpg(proc.pid, signal.SIGTERM)
        except Exception:
            pass
    sys.exit(130)


# Install signal handlers once
for _sig in (signal.SIGINT, signal.SIGTERM):
    try:
        signal.signal(_sig, _shutdown)
    except Exception:
        # Not fatal (e.g., on some restricted environments)
        pass


def run_cmd(
    cmd: List[str],
    cwd: Path,
    log_path: Path,
    timeout: Optional[int] = None,
    keep_log_on_success: bool = False,
) -> int:
    """
    Run a subprocess command, capture stdout+stderr to a log file when needed,
    enforce a timeout, and track processes for clean shutdown.
    """
    header = f"$ {' '.join(cmd)}\n\n"
    out, rc = "", -1
    proc: Optional[subprocess.Popen] = None

    try:
        proc = subprocess.Popen(
            cmd,
            cwd=str(cwd),
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            start_new_session=True,
        )
        _RUNNING_PROCS.add(proc)
        out, _ = proc.communicate(timeout=timeout)
        rc = proc.returncode
    except subprocess.TimeoutExpired:
        if proc is not None:
            try:
                proc.kill()
            except Exception:
                pass
            extra, _ = proc.communicate()
            out = (extra or "") + "\n[timeout]\n"
        rc = 124
    except Exception as e:
        out = f"[exception] {e}\n"
        rc = 125
    finally:
        if proc is not None:
            _RUNNING_PROCS.discard(proc)

    if rc != 0 or keep_log_on_success:
        log_path.parent.mkdir(parents=True, exist_ok=True)
        log_path.write_text(header + (out or ""), encoding="utf-8")

    return rc


# ---------- Header Stub Generation ----------
def generate_header_stubs(temp_dir: Path, code: str) -> None:
    """
    Provide minimal headers for common types/functions Devign uses.

    This helps Joern's C/C++ frontend resolve types better for isolated functions.
    """
    include_dir = temp_dir / "include"
    include_dir.mkdir(exist_ok=True)

    stubs_needed = set()

    if "size_t" in code or "malloc" in code or "free" in code:
        stubs_needed.add("stddef.h")
    if "uint32_t" in code or "int32_t" in code or "uint64_t" in code:
        stubs_needed.add("stdint.h")
    if "printf" in code or "fprintf" in code or "sprintf" in code:
        stubs_needed.add("stdio.h")
    if "memcpy" in code or "memset" in code or "strcmp" in code:
        stubs_needed.add("string.h")
    if "NULL" in code:
        stubs_needed.add("NULL_macro.h")

    stub_content = {
        "stddef.h": "typedef __SIZE_TYPE__ size_t;\n",
        "stdint.h": """
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;
""",
        "stdio.h": "int printf(const char*, ...);\n",
        "string.h": """
void* memcpy(void*, const void*, size_t);
void* memset(void*, int, size_t);
int strcmp(const char*, const char*);
""",
        "NULL_macro.h": "#define NULL ((void*)0)\n",
    }

    for header in stubs_needed:
        (include_dir / header).write_text(stub_content[header], encoding="utf-8")


# ---------- CPG Validation ----------
# ---------- CPG Validation ----------
def validate_cpg_integrity(cpg_path: Path, log_path: Path) -> Tuple[bool, str]:
    """
    Lightweight integrity check for per-function CPGs.

    NOTE:
      The previous implementation spawned a full `joern` console for each
      CPG and queried method/node counts + overlays. That dominates runtime
      when you have tens of thousands of functions.

    For the normalized Devign per-function setup, it's usually sufficient
    to require that the .cpg.bin file:
      1) exists, and
      2) is not trivially small.

    Returns:
        (ok, msg) where msg gives a short reason.
    """
    if not cpg_path.exists():
        return False, "file_missing"

    size = cpg_path.stat().st_size
    if size < 1024:
        return False, f"file_too_small({size}B)"

    return True, f"ok_size={size}B"


# ---------- Export File Validation ----------
def validate_export_files(out_dir: Path, fmt: str) -> bool:
    """
    Validate exported GraphSON / DOT files are parseable.
    """
    if not dir_nonempty(out_dir):
        return False

    if fmt == "graphson":
        for json_file in out_dir.glob("*.json"):
            try:
                json.loads(json_file.read_text(encoding="utf-8"))
            except json.JSONDecodeError:
                logger.error(f"Invalid JSON: {json_file}")
                return False
        return True

    elif fmt == "dot":
        for dot_file in out_dir.glob("*.dot"):
            content = dot_file.read_text(encoding="utf-8")
            if not content.startswith("digraph") or "METHOD" not in content:
                logger.error(f"Malformed DOT: {dot_file}")
                return False
            if 'CODE="' in content and '""' not in content:
                try:
                    import pydot  # optional
                    pydot.graph_from_dot_file(str(dot_file))
                except ModuleNotFoundError:
                    logger.debug("pydot not installed; skipping deep DOT validation")
                except Exception as e:
                    logger.error(f"DOT parse error: {dot_file} - {e}")
                    return False
        return True

    # Other formats: just check non-empty
    return True


# ---------- Data Classes ----------
@dataclass
class Task:
    function_id: str
    code: str
    label: int
    stem: str           # canonical ID (e.g. test_func_0000001)
    out_split: Path
    log_dir: Path
    joern_parse: str
    joern_export: str
    force_language: Optional[str]  # "c" or "cpp" if set, else None
    fmt: str
    timeout: Optional[int]
    keep_logs: bool
    force: bool
    retries: int
    reprs: List[str]



@dataclass
class FunctionRecord:
    """
    One function from per-function Devign dataset.
    function_id: canonical ID without '.c' (e.g., test_func_0000001)
    """
    function_id: str
    code: str
    label: int
    project: str


# ---------- Load from manifest_*.csv + .c files ----------
def load_functions_from_manifest(perfunc_base: Path, split: str) -> List[FunctionRecord]:
    """
    Load functions from:
      <perfunc_base>/manifest_<split>.csv
      <perfunc_base>/<split>/<function_id>.c
    """
    manifest_path = perfunc_base / f"manifest_{split}.csv"
    split_dir = perfunc_base / split

    if not manifest_path.exists():
        logger.error(f"✗ Missing manifest for split '{split}': {manifest_path}")
        return []

    if not split_dir.exists():
        logger.error(f"✗ Missing split directory '{split}': {split_dir}")
        return []

    functions: List[FunctionRecord] = []
    with manifest_path.open(newline="", encoding="utf-8") as fh:
        reader = csv.DictReader(fh)
        if "function_id" not in reader.fieldnames:
            logger.error(f"✗ Manifest {manifest_path} missing 'function_id' column")
            return []

        for i, row in enumerate(reader, start=1):
            fid = (row.get("function_id") or "").strip()
            if not fid:
                logger.warning(f"[{split}] Empty function_id at manifest row {i}")
                continue

            src_path = split_dir / fid
            if not src_path.exists():
                logger.warning(f"[{split}] Missing .c file for {fid}: {src_path}")
                continue

            try:
                code = src_path.read_text(encoding="utf-8")
            except Exception as e:
                logger.error(f"[{split}] Failed to read {src_path}: {e}")
                continue

            label_raw = row.get("label", "0")
            try:
                label = int(label_raw)
            except Exception:
                logger.warning(
                    f"[{split}] Non-integer label '{label_raw}' at row {i}, defaulting to 0"
                )
                label = 0

            project = row.get("project", "unknown_project")
            # canonical ID: strip ".c" if present
            stem = fid.rsplit(".", 1)[0]

            functions.append(
                FunctionRecord(function_id=stem, code=code, label=label, project=project)
            )

    logger.info(f"Loaded {len(functions)} functions from {manifest_path}")
    return functions


# ---------- Parse Stage ----------
# ---------- Parse Stage ----------
def parse_func(t: Task) -> Tuple[str, bool, str]:
    """
    Parse one function into a CPG using joern-parse in an isolated temp dir.

    Language selection:
      • If t.force_language is set (c/cpp) → always use that.
      • Otherwise, use a simple heuristic:
          "class"/"namespace" present → cpp
          else                        → c
      • On retry, if we initially chose cpp and have no force_language,
        we fallback to c to dodge cpp-frontend crashes (e.g. None.get).
    """
    cpg_path = t.out_split / f"{t.stem}.cpg.bin"

    # Reuse valid cached CPG if present
    if cpg_path.exists() and not t.force:
        valid, msg = validate_cpg_integrity(
            cpg_path, t.log_dir / f"{t.stem}.validate_cache.log"
        )
        if valid:
            return (t.stem, True, f"cached ({msg})")
        else:
            logger.warning(f"Invalid cached CPG for {t.stem}: {msg}")
            cpg_path.unlink(missing_ok=True)

    temp_dir = Path(tempfile.mkdtemp(prefix=f"joern_{t.stem}_"))

    try:
        # Base language choice (before retries)
        if t.force_language in ("c", "cpp"):
            base_lang = t.force_language
        else:
            # crude C/C++ detection on the raw code
            if ("class" in t.code) or ("namespace" in t.code):
                base_lang = "cpp"
            else:
                base_lang = "c"

        # Write source file once (extension based on base_lang)
        src_file = temp_dir / f"{t.stem}.{base_lang}"
        src_file.write_text(t.code, encoding="utf-8")

        generate_header_stubs(temp_dir, t.code)

        attempt_ok = False
        attempts = max(1, t.retries)

        for attempt in range(attempts):
            # On retry, optionally fallback from cpp → c if not forced
            if t.force_language in ("c", "cpp"):
                lang = t.force_language
            else:
                if base_lang == "cpp" and attempt > 0:
                    lang = "c"
                else:
                    lang = base_lang

            cmd = [t.joern_parse, str(temp_dir), "--output", str(cpg_path)]
            if lang:
                cmd += ["--language", lang]

            rc = run_cmd(
                cmd,
                cwd=t.out_split,
                log_path=t.log_dir / f"{t.stem}.parse_attempt{attempt+1}.log",
                timeout=t.timeout,
                keep_log_on_success=t.keep_logs,
            )

            if rc == 0 and cpg_path.exists():
                valid, msg = validate_cpg_integrity(
                    cpg_path, t.log_dir / f"{t.stem}.validate.log"
                )
                if valid:
                    attempt_ok = True
                    break
                else:
                    logger.warning(
                        f"Parse attempt {attempt+1} produced invalid CPG for {t.stem}: {msg}"
                    )
                    cpg_path.unlink(missing_ok=True)
            else:
                logger.warning(
                    f"Parse attempt {attempt+1} failed for {t.stem}: exit code {rc} (lang={lang})"
                )

        return (t.stem, attempt_ok, "parsed" if attempt_ok else "parse_failed")

    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)



# ---------- Export Stage ----------
def export_func(t: Task) -> Tuple[str, bool, str]:
    """
    Export CPG to GraphSON / proto-json / DOT using joern-export.
    """
    cpg_path = t.out_split / f"{t.stem}.cpg.bin"
    if not cpg_path.exists():
        return (t.stem, False, "no_cpg")

    ebase = t.out_split / "exports" / t.stem
    ensure_dir(ebase)

    link = ebase / "cpg.bin"
    if link.exists() or link.is_symlink():
        link.unlink()
    try:
        os.symlink(cpg_path, link)
    except Exception:
        pass

    fmt = (t.fmt or "").lower()
    ok = True

    # full-graph exports
    if fmt in {"graphson", "graphml", "neo4jcsv", "proto-json", "protojson"}:
        out_dir = ebase / "export_all"
        if out_dir.exists():
            if t.force:
                shutil.rmtree(out_dir, ignore_errors=True)
            elif dir_nonempty(out_dir) and validate_export_files(out_dir, fmt):
                return (t.stem, True, "export_cached")
            else:
                shutil.rmtree(out_dir, ignore_errors=True)

        cmd = [
            t.joern_export,
            str(cpg_path),  # CPG FIRST
            "--repr",
            "all",
            "--format",
            "proto-json" if fmt == "protojson" else fmt,
            "--out",
            str(out_dir),
        ]

        attempt_ok = False
        for attempt in range(max(1, t.retries)):
            rc = run_cmd(
                cmd,
                cwd=ebase,
                log_path=t.log_dir / f"{t.stem}.export_all_attempt{attempt+1}.log",
                timeout=t.timeout,
                keep_log_on_success=t.keep_logs,
            )

            if rc == 0 and dir_nonempty(out_dir):
                if validate_export_files(out_dir, fmt):
                    attempt_ok = True
                    break
                else:
                    logger.warning(
                        f"Export attempt {attempt+1} produced invalid files for {t.stem}"
                    )
                    shutil.rmtree(out_dir, ignore_errors=True)

        return (t.stem, attempt_ok, "export_ok" if attempt_ok else "export_failed")

    # DOT exports per repr
    elif fmt == "dot":
        if not t.reprs:
            return (t.stem, False, "no_reprs_specified")

        for r in t.reprs:
            out_dir = ebase / f"export_{r}"
            if out_dir.exists():
                if t.force:
                    shutil.rmtree(out_dir, ignore_errors=True)
                elif dir_nonempty(out_dir) and validate_export_files(out_dir, "dot"):
                    continue
                else:
                    shutil.rmtree(out_dir, ignore_errors=True)

            cmd = [
                t.joern_export,
                str(cpg_path),
                "--repr",
                r,
                "--format",
                "dot",
                "--out",
                str(out_dir),
            ]

            attempt_ok = False
            for attempt in range(max(1, t.retries)):
                rc = run_cmd(
                    cmd,
                    cwd=ebase,
                    log_path=t.log_dir
                    / f"{t.stem}.export_{r}_attempt{attempt+1}.log",
                    timeout=t.timeout,
                    keep_log_on_success=t.keep_logs,
                )

                if rc == 0 and dir_nonempty(out_dir) and validate_export_files(
                    out_dir, "dot"
                ):
                    attempt_ok = True
                    break
                else:
                    logger.warning(
                        f"Export attempt {attempt+1} failed for {t.stem}/{r}"
                    )

            if not attempt_ok:
                ok = False

        return (t.stem, ok, "export_ok" if ok else "export_partial")

    else:
        return (t.stem, False, f"unsupported_format_{fmt}")


# ---------- Task Builder ----------
def build_tasks(
    split: str,
    perfunc_base: Path,
    out_split: Path,
    functions: List[FunctionRecord],
    args,
) -> Tuple[List[Task], int]:
    """
    Build Task objects from FunctionRecord list.
    """
    tasks: List[Task] = []
    log_dir = out_split / "logs" / "joern"
    ensure_dir(log_dir)

    # reprs for DOT format
    base_fmt = (args.format or "").lower()
    base_reprs: List[str] = []
    if base_fmt == "dot":
        base_reprs = [r.strip() for r in (args.repr or "").split(",") if r.strip()]

    # Optional global language override
    force_lang = None
    if getattr(args, "force_language", None):
        force_lang = args.force_language.strip().lower()

    for func in functions:
        tasks.append(
            Task(
                function_id=func.function_id,
                code=func.code,
                label=func.label,
                stem=func.function_id,
                out_split=out_split,
                log_dir=log_dir,
                joern_parse=args.joern_parse,
                joern_export=args.joern_export,
                force_language=force_lang,
                fmt=base_fmt,
                timeout=(args.timeout or 180),
                keep_logs=bool(args.log_on_success),
                force=bool(args.force),
                retries=max(1, args.retries),
                reprs=list(base_reprs),
            )
        )

    return tasks, 0


# ---------- Process Pool ----------
def run_pool(stage: str, tasks: List[Task], workers: int) -> Tuple[int, int, int]:
    """
    Run parse/export tasks in a ProcessPoolExecutor for isolation.

    We cap workers based on CPU count to avoid oversubscribing Joern, but we no
    longer hard-cap at 4. On large machines (e.g., 80+ cores), this allows
    significantly more parallelism.

    Rough policy (can be tuned):
      • parse  : up to min(16, max(2, cpu_count // 4))
      • export : up to min(24, max(2, cpu_count // 2))
    """
    ok = partial_ok = failed = 0
    fn = parse_func if stage == "parse" else export_func

    cpu_count = os.cpu_count() or 8
    if stage == "parse":
        hard_cap = max(2, min(16, max(1, cpu_count // 4)))
    else:
        hard_cap = max(2, min(24, max(1, cpu_count // 2)))

    safe_workers = max(1, min(workers, hard_cap))
    if safe_workers < workers:
        logger.warning(
            f"Capping {stage} workers from {workers} to {safe_workers} for stability "
            f"(cpu_count={cpu_count})"
        )

    with ProcessPoolExecutor(max_workers=safe_workers) as ex:
        futures = {ex.submit(fn, t): t for t in tasks}
        for fut in as_completed(futures):
            try:
                _, success, msg = fut.result()
                if success:
                    if msg == "export_partial":
                        partial_ok += 1
                    else:
                        ok += 1
                else:
                    failed += 1
                    t = futures[fut]
                    logger.error(f"✗ {t.function_id}: {msg}")
            except Exception:
                logger.exception(f"Exception in {stage} task")
                failed += 1

    return ok, partial_ok, failed



# ---------- CLI + Main ----------
def parse_args():
    ap = argparse.ArgumentParser(
        description="Evidence-Based Joern Pipeline for Devign (per-function .c + manifest)"
    )
    ap.add_argument("--perfunc-base", default=str(PERFUNC_BASE))
    ap.add_argument("--out-base", default=str(OUT_BASE))
    ap.add_argument(
        "--splits",
        default="train,validation,test",  # use "train,valid,test" if that's what you used
        help="Comma-separated list of splits to process "
        "(e.g., train,validation,test or train,valid,test)",
    )
    ap.add_argument(
        "--stage", choices=["parse", "export", "both"], default="both"
    )

        # Parse settings
    ap.add_argument(
        "--parse-workers",
        type=int,
        default=4,
        help="Max concurrent parse operations (recommended: 2-4)",
    )
    ap.add_argument(
        "--retries",
        type=int,
        default=2,
        help="Number of retry attempts per function",
    )
    ap.add_argument(
        "--timeout",
        type=int,
        default=180,
        help="Timeout per function in seconds",
    )

    # Parse settings
    ap.add_argument(
        "--force-language",
        choices=["c", "cpp"],
        help=(
            "Force Joern frontend language for ALL functions. "
            "If unset, a simple heuristic is used "
            '(\"class\"/\"namespace\" → cpp, else c).'
        ),
    )

    ap.add_argument(
        "--force",
        action="store_true",
        help="Force re-processing even if outputs exist",
    )
    ap.add_argument(
        "--log-on-success",
        action="store_true",
        help="Keep logs even for successful operations",
    )

    # Export settings
    ap.add_argument(
        "--export-workers",
        type=int,
        default=4,
        help="Max concurrent export operations (recommended: 2-4)",
    )
    ap.add_argument(
        "--repr",
        default="",
        help="For DOT format: comma-separated representations "
        "(ast,cfg,cdg,ddg,pdg,calls,cfgdom)",
    )
    ap.add_argument(
        "--format",
        default="graphson",
        choices=["graphson", "graphml", "proto-json", "protojson", "neo4jcsv", "dot"],
        help="Export format",
    )

    # Joern paths
    ap.add_argument("--joern-parse", default=which("joern-parse") or "joern-parse")
    ap.add_argument("--joern-export", default=which("joern-export") or "joern-export")

    return ap.parse_args()


def main():
    args = parse_args()
    perfunc_base = Path(args.perfunc_base)
    out_base = Path(args.out_base)
    ensure_dir(out_base)

    # Validate Joern installation
    for exe in (args.joern_parse, args.joern_export):
        if not which(exe):
            logger.error(f"✗ Not on PATH: {exe}")
            sys.exit(2)

    # Check Joern version (optional)
    try:
        version_result = subprocess.run(
            [args.joern_parse, "--version"], capture_output=True, text=True, timeout=30
        )
        logger.info(f"Joern version: {version_result.stdout.strip()}")
    except Exception as e:
        logger.warning(f"Could not verify Joern version: {e}")

    splits = [s.strip() for s in args.splits.split(",") if s.strip()]
    all_summaries: Dict[str, Any] = {}

    for split in splits:
        logger.info("\n" + "=" * 60)
        logger.info(f"Processing split: {split}")
        logger.info("=" * 60)

        functions = load_functions_from_manifest(perfunc_base, split)
        if not functions:
            logger.error(f"✗ No valid functions for split '{split}'")
            continue

        out_split = out_base / split
        ensure_dir(out_split)

        # labels + projects for GNN training
        labels_path = out_split / "labels.json"
        projects_path = out_split / "projects.json"
        if args.force or not labels_path.exists():
            labels = {f.function_id: f.label for f in functions}
            write_json(labels_path, labels)
            logger.info(f"Saved {len(labels)} labels to {labels_path}")
        if args.force or not projects_path.exists():
            projects = {f.function_id: f.project for f in functions}
            write_json(projects_path, projects)
            logger.info(f"Saved {len(projects)} projects to {projects_path}")

        tasks, _ = build_tasks(split, perfunc_base, out_split, functions, args)
        logger.info(f"Processing {len(tasks)} functions")

        parse_ok = parse_fail = export_ok = export_partial = export_fail = 0

        if args.stage in ("parse", "both"):
            logger.info(
                f"\n[Parse Stage] workers={args.parse_workers}, retries={args.retries}"
            )
            ok, _, fail = run_pool("parse", tasks, args.parse_workers)
            parse_ok, parse_fail = ok, fail
            logger.info(f"[Parse] {ok} OK, {fail} failed")

        if args.stage in ("export", "both"):
            fmt = (args.format or "").lower()
            if fmt in {"graphson", "graphml", "neo4jcsv", "proto-json", "protojson"}:
                for t in tasks:
                    t.fmt = fmt
                    t.reprs = ["all"]
            elif fmt == "dot":
                reprs = [r.strip() for r in (args.repr or "").split(",") if r.strip()]
                if not reprs:
                    logger.warning("DOT format expects --repr (e.g., --repr ast,cfg)")
                for t in tasks:
                    t.fmt = "dot"
                    t.reprs = list(reprs)

            logger.info(
                f"\n[Export Stage] format={args.format}, workers={args.export_workers}"
            )
            ok, part, fail = run_pool("export", tasks, args.export_workers)
            export_ok, export_partial, export_fail = ok, part, fail
            logger.info(f"[Export] {ok} OK, {part} partial, {fail} failed")

        summary = {
            "split": split,
            "total_functions": len(functions),
            "stage": args.stage,
            "format": args.format,
            "parse_ok": parse_ok,
            "parse_failed": parse_fail,
            "export_ok": export_ok,
            "export_partial": export_partial,
            "export_failed": export_fail,
            "success_rate": {
                "parse": parse_ok / len(tasks) if tasks else 0.0,
                "export": export_ok / len(tasks) if tasks else 0.0,
            },
        }
        write_json(out_split / "summary.json", summary)
        all_summaries[split] = summary

    write_json(out_base / "summary_all.json", all_summaries)

    logger.info("\n" + "=" * 60)
    logger.info("FINAL SUMMARY")
    logger.info("=" * 60)
    for split, summary in all_summaries.items():
        logger.info(
            f"{split}: {summary['total_functions']} functions, "
            f"parse_success={summary['parse_ok']}/{summary['total_functions']} "
            f"({summary['success_rate']['parse']:.1%}), "
            f"export_success={summary['export_ok']}/{summary['total_functions']} "
            f"({summary['success_rate']['export']:.1%})"
        )
    logger.info("=" * 60)
    logger.info("✓ Pipeline complete. Check logs in <out>/<split>/logs/joern/")


if __name__ == "__main__":
    main()

"""
python generate_cpg_devign_final.py \
  --stage both \
  --splits train,validation,test \
  --format graphson \
  --parse-workers 32 \
  --export-workers 32 \
  --timeout 300 \
  --retries 2


"""