#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
06_batch_cpg_devign.py
- Stage "parse": source(.c/.cpp) → <split>/<stem>.cpg.bin
- Stage "export": <stem>.cpg.bin → export files (format-aware)
    • graphson/graphml/neo4jcsv/proto-json  -> repr=all (enforced)
    • dot                                    -> repr can be ast,cfg,cdg,ddg,pdg,calls,cfgdom

Outputs layout:
  <out_base>/<split>/
    ├─ *.cpg.bin
    ├─ exports/<stem>/
    │   ├─ cpg.bin  (symlink to the .cpg.bin)
    │   ├─ export_all/         (for all-formats)
    │   └─ export_<repr>/...   (for dot format per repr)
    ├─ logs/*.parse.log
    ├─ logs/*.export_<repr or all>.log
    └─ summary.json

Example:
  PARSE:
    python 06_batch_cpg_devign.py --stage parse --splits train,valid,test --parse-workers 72 --retries 2
  EXPORT (GraphSON full graph):
    python 06_batch_cpg_devign.py --stage export --splits train,valid,test --format graphson --export-workers 72
  EXPORT (DOT per-repr):
    python 06_batch_cpg_devign.py --stage export --splits train --format dot --repr ast,cfg,cdg --export-workers 72
"""

from __future__ import annotations
import argparse, csv, json, os, shutil, signal, subprocess, sys, zipfile
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional, Tuple

# ---------- paths ----------
PERFUNC_BASE = Path("./workspace/03_PerFunction_datasets/normalized_devign_functions")
OUT_BASE     = Path("./CPGs/normalized_devign_functions")

# ---------- utils ----------
def which(x: str) -> Optional[str]:
    return shutil.which(x)

def ensure_dir(p: Path) -> None:
    p.mkdir(parents=True, exist_ok=True)

def dir_nonempty(p: Path) -> bool:
    try:
        return p.exists() and any(p.iterdir())
    except Exception:
        return False

def read_manifest(p: Path) -> List[dict]:
    rows: List[dict] = []
    with p.open(newline="", encoding="utf-8") as fh:
        rows.extend(csv.DictReader(fh))
    return rows

def write_json(p: Path, obj: dict) -> None:
    p.write_text(json.dumps(obj, ensure_ascii=False, indent=2), encoding="utf-8")

_RUNNING = set()
def _shutdown(*_):
    for proc in list(_RUNNING):
        try:
            os.killpg(proc.pid, signal.SIGTERM)
        except Exception:
            pass
    sys.exit(130)
for sig in (signal.SIGINT, signal.SIGTERM):
    signal.signal(sig, _shutdown)

def run_cmd(cmd: List[str], cwd: Path, log_path: Path,
            timeout: Optional[int] = None, keep_log_on_success: bool = False) -> int:
    header = f"$ {' '.join(cmd)}\n\n"
    out, rc = "", -1
    try:
        proc = subprocess.Popen(
            cmd, cwd=str(cwd),
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, start_new_session=True
        )
        _RUNNING.add(proc)
        out, _ = proc.communicate(timeout=timeout)
        rc = proc.returncode
    except subprocess.TimeoutExpired:
        try: proc.kill()
        except Exception: pass
        out2, _ = proc.communicate()
        out = (out2 or "") + "\n[timeout]\n"
        rc = 124
    except Exception as e:
        out = f"[exception] {e}\n"
        rc = 125
    finally:
        _RUNNING.discard(proc)

    if rc != 0 or keep_log_on_success:
        log_path.parent.mkdir(parents=True, exist_ok=True)
        log_path.write_text(header + (out or ""), encoding="utf-8")
    return rc

# ---------- dataclass ----------
@dataclass
class Task:
    split: str
    src: Path
    stem: str
    out_split: Path
    log_dir: Path
    joern_parse: str
    joern_export: str
    # export params
    reprs: List[str]
    fmt: str
    retries: int
    timeout: Optional[int]
    keep_logs: bool
    force: bool

# ---------- stages ----------
def parse_func(t: Task) -> Tuple[str, bool, str]:
    final = t.out_split / f"{t.stem}.cpg.bin"
    if final.exists() and not t.force:
        return (t.stem, True, "cached")

    # infer language from extension for joern-parse (optional)
    lang = None
    ext = t.src.suffix.lower()
    if ext in (".c",): lang = "c"
    elif ext in (".cc", ".cpp", ".cxx", ".hpp", ".hh"): lang = "cpp"

    cmd = [t.joern_parse, str(t.src), "--output", str(final)]
    if lang:
        cmd += ["--language", lang]

    rc = run_cmd(cmd, cwd=t.out_split, log_path=t.log_dir / f"{t.stem}.parse.log",
                 timeout=t.timeout, keep_log_on_success=t.keep_logs)
    return (t.stem, rc == 0 and final.exists(), "parsed" if rc == 0 else "parse_failed")

def export_func(t: Task) -> Tuple[str, bool, str]:
    cpg = t.out_split / f"{t.stem}.cpg.bin"
    if not cpg.exists():
        return (t.stem, False, "no_cpg")

    ebase = t.out_split / "exports" / t.stem
    ensure_dir(ebase)

    # link cpg for convenience
    link = ebase / "cpg.bin"
    if link.exists() or link.is_symlink():
        try: link.unlink()
        except Exception: pass
    try:
        os.symlink(cpg, link)
    except Exception:
        pass

    fmt = (t.fmt or "").lower()
    text_formats_requiring_all = {"graphson", "graphml", "neo4jcsv", "proto-json", "protojson"}
    ok = True

    if fmt in text_formats_requiring_all:
        # one full-graph export into export_all/
        out_dir = ebase / "export_all"
        if out_dir.exists():
            if t.force:
                shutil.rmtree(out_dir, ignore_errors=True)
            elif dir_nonempty(out_dir):
                return (t.stem, True, "export_ok")
            else:
                shutil.rmtree(out_dir, ignore_errors=True)

        cmd = [t.joern_export, "--repr", "all", "--out", str(out_dir)]
        # graphson/graphml/neo4jcsv/proto-json supported for repr=all
        if fmt == "protojson": fmt = "proto-json"
        cmd += ["--format", fmt]
        cmd.append(str(cpg))

        rc = run_cmd(cmd, cwd=ebase, log_path=t.log_dir / f"{t.stem}.export_all.log",
                     timeout=t.timeout, keep_log_on_success=t.keep_logs)
        ok = (rc == 0 and dir_nonempty(out_dir))
        return (t.stem, ok, "export_ok" if ok else "export_failed")

    # DOT: allow multiple reprs side-by-side
    if fmt and fmt != "dot":
        # unknown/unsupported combo, hard fail early
        (t.log_dir / f"{t.stem}.export_unsupported.log").write_text(
            f"format '{t.fmt}' only supported with repr=all; use --format dot for per-repr.",
            encoding="utf-8"
        )
        return (t.stem, False, "export_failed")

    for r in t.reprs:
        out_dir = ebase / f"export_{r}"
        if out_dir.exists():
            if t.force:
                shutil.rmtree(out_dir, ignore_errors=True)
            elif dir_nonempty(out_dir):
                continue
            else:
                shutil.rmtree(out_dir, ignore_errors=True)

        # DOT per-repr
        cmd = [t.joern_export, "--repr", r, "--out", str(out_dir), "--format", "dot", str(cpg)]

        attempt_ok = False
        for _ in range(max(1, t.retries)):
            rc = run_cmd(cmd, cwd=ebase, log_path=t.log_dir / f"{t.stem}.export_{r}.log",
                         timeout=t.timeout, keep_log_on_success=t.keep_logs)
            if rc == 0 and dir_nonempty(out_dir):
                attempt_ok = True
                break
        if not attempt_ok:
            ok = False
    return (t.stem, ok, "export_ok" if ok else "export_partial")

# ---------- plumbing ----------
def build_tasks(split: str, perfunc_base: Path, out_split: Path,
                rows: List[dict], args) -> List[Task]:
    tasks: List[Task] = []
    split_dir = perfunc_base / split
    log_dir = out_split / "logs"
    ensure_dir(log_dir)

    for r in rows:
        fid = (r.get("function_id") or "").strip()
        if not fid:
            continue
        src = split_dir / fid
        if not src.exists():
            continue
        stem = Path(fid).stem

        tasks.append(Task(
            split=split, src=src, stem=stem,
            out_split=out_split, log_dir=log_dir,
            joern_parse=args.joern_parse, joern_export=args.joern_export,
            reprs=[x.strip() for x in (args.repr or "").split(",") if x.strip()],
            fmt=(args.format or "").strip(),
            retries=max(1, args.retries),
            timeout=(args.timeout or None),
            keep_logs=bool(args.log_on_success),
            force=bool(args.force),
        ))
    return tasks

def run_pool(stage: str, tasks: List[Task], workers: int) -> Tuple[int,int,int]:
    ok = partial = failed = 0
    fn = parse_func if stage == "parse" else export_func
    with ThreadPoolExecutor(max_workers=max(1, workers)) as ex:
        futures = {ex.submit(fn, t): t for t in tasks}
        for fut in as_completed(futures):
            try:
                _, success, msg = fut.result()
                if success:
                    if msg == "export_partial": partial += 1
                    else: ok += 1
                else:
                    failed += 1
            except Exception:
                failed += 1
    return ok, partial, failed

# ---------- args ----------
def parse_args():
    ap = argparse.ArgumentParser(description="Batch build + export CPGs for Devign per-function dataset.")
    ap.add_argument("--perfunc-base", default=str(PERFUNC_BASE))
    ap.add_argument("--out-base",     default=str(OUT_BASE))
    ap.add_argument("--splits",       default="train,valid,test",
                    help="comma list (e.g., train,valid,test)")
    ap.add_argument("--stage",        choices=["parse","export","both"], default="both")

    # parse
    ap.add_argument("--parse-workers", type=int, default=60)
    ap.add_argument("--retries",        type=int, default=1)
    ap.add_argument("--timeout",        type=int, default=0)
    ap.add_argument("--force",          action="store_true")
    ap.add_argument("--log-on-success", action="store_true")

    # export
    ap.add_argument("--export-workers", type=int, default=40)
    ap.add_argument("--repr",   default="", help="For DOT only: ast,cfg,cdg,ddg,pdg,calls,cfgdom. Ignored for graphson/graphml/neo4jcsv/proto-json (forced to 'all').")
    ap.add_argument("--format", default="graphson", help="graphson|graphml|neo4jcsv|proto-json|dot")

    # joern
    ap.add_argument("--joern-parse",  default=which("joern-parse")  or "joern-parse")
    ap.add_argument("--joern-export", default=which("joern-export") or "joern-export")
    return ap.parse_args()

def main():
    a = parse_args()
    perfunc_base = Path(a.perfunc_base); out_base = Path(a.out_base)
    ensure_dir(out_base)

    for exe in (a.joern_parse, a.joern_export):
        if not shutil.which(exe):
            print(f"✗ Not on PATH: {exe}"); sys.exit(2)

    splits = [s.strip() for s in a.splits.split(",") if s.strip()]
    for split in splits:
        split_dir = perfunc_base / split
        manifest  = perfunc_base / f"manifest_{split}.csv"
        if not split_dir.exists():  print(f"⚠ missing {split_dir}");  continue
        if not manifest.exists():   print(f"⚠ missing {manifest}");   continue
        rows = read_manifest(manifest)
        if not rows:                print(f"⚠ empty manifest {manifest}"); continue

        out_split = out_base / split
        ensure_dir(out_split)
        (out_split / "logs").mkdir(exist_ok=True)

        tasks = build_tasks(split, perfunc_base, out_split, rows, a)

        print(f"[{split}] functions={len(tasks)} out={out_split}")

        parse_ok = parse_fail = export_ok = export_partial = export_fail = 0

        if a.stage in ("parse","both"):
            ok, _, fail = run_pool("parse", tasks, a.parse_workers)
            parse_ok, parse_fail = ok, fail

        if a.stage in ("export","both"):
            # Enforce repr rules
            fmt = (a.format or "").lower()
            if fmt in {"graphson","graphml","neo4jcsv","proto-json","protojson"}:
                # ignore user-provided repr list; force 'all'
                for t in tasks:
                    t.fmt = "proto-json" if fmt == "protojson" else fmt
                    t.reprs = ["all"]
            elif fmt == "dot":
                # require at least one repr
                if not any((a.repr or "").split(",")):
                    print("• Note: --format dot expects --repr (e.g., --repr ast,cfg).")
            else:
                print(f"✗ Unsupported --format {a.format}")
                sys.exit(2)

            ok, part, fail = run_pool("export", tasks, a.export_workers)
            export_ok, export_partial, export_fail = ok, part, fail

        write_json(out_split / "summary.json", {
            "split": split,
            "stage": a.stage,
            "format": a.format,
            "repr": a.repr or ("all" if (a.format.lower() != "dot") else "(see dot repr)"),
            "parse_ok": parse_ok, "parse_failed": parse_fail,
            "export_ok": export_ok, "export_partial": export_partial, "export_failed": export_fail
        })

    print("✓ Done.")

if __name__ == "__main__":
    main()


"""
export JAVA_TOOL_OPTIONS="-Xms8g -Xmx100g -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:+UseStringDeduplication"
export CPG_TMP=/dev/shm
ulimit -n 1048576
python 01_batch_cpg_devign.py \
  --stage parse \
  --splits train,valid,test \
  --parse-workers 72 \
  --retries 2 \
  --force



export JAVA_TOOL_OPTIONS="-Xms8g -Xmx100g -XX:+UseG1GC -XX:+ParallelRefProcEnabled -XX:+UseStringDeduplication"
export CPG_TMP=/dev/shm
ulimit -n 1048576
python 01_batch_cpg_devign.py \
  --stage export \
  --splits train,valid,test \
  --format graphson \
  --export-workers 72 \
  --retries 1 \
  --force \
  --log-on-success



"""