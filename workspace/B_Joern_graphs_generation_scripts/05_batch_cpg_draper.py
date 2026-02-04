#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
05_batch_cpg_draper.py — per-function CPGs for Draper (flat files like Devign)

Why this:
- Flat outputs (no nested dirs): <out>/<split>/<STEM>.cpg.bin [+ optional .zip]
- Robust joern-parse: always write to a temp FILE via --output, then move to final.
- Language fallback: try chosen lang, then c<->cpp fallback to avoid None.get crashes.
- Phase 1 (parse-only) is fast and mirrors your Devign flow.
- Phase 2 (export) is optional; it reads the flat cpg.bin and writes exports under <out>/<split>/exports/<STEM>/...
- Logs are only written on failure (use --log-on-success to keep them).
"""

from __future__ import annotations
import argparse, csv, json, os, re, shutil, subprocess, sys, signal, zipfile
from concurrent.futures import ThreadPoolExecutor, as_completed
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from tqdm import tqdm



# ── Paths (adjust if needed) ─────────────────────────────────────────────────
PERFUNC_BASE = Path("./workspace/03_PerFunction_datasets/normalized_draper_functions")
OUT_BASE     = Path("./CPGs/normalized_draper_functions")

import tempfile

def is_trivially_empty(p: Path) -> bool:
    try:
        s = p.read_text(encoding="utf-8", errors="ignore")
        return len(s.strip()) == 0
    except Exception:
        return False

def prepare_src_for_lang(src: Path, lang: Optional[str]) -> Path:
    """
    Ensure the filename suffix matches the language for this attempt.
    If mismatch, copy to a temp file with the appropriate suffix.
    """
    if lang is None:
        return src
    ext = src.suffix.lower()
    want = ".c" if lang == "c" else ".cpp"
    if ext == want:
        return src
    # copy to a temp with right suffix
    tmp = Path(tempfile.mkdtemp(prefix="cpg-src-")) / (src.stem + want)
    shutil.copy2(src, tmp)
    return tmp



def which(x: str) -> Optional[str]: return shutil.which(x)
def ensure_dir(p: Path) -> None: p.mkdir(parents=True, exist_ok=True)

def read_manifest(p: Path) -> List[Dict[str, str]]:
    rows: List[Dict[str, str]] = []
    with p.open(newline="", encoding="utf-8") as fh:
        rows.extend(csv.DictReader(fh))
    return rows

def dir_nonempty(p: Path) -> bool:
    try: return p.exists() and any(p.iterdir())
    except Exception: return False

def write_json(p: Path, obj: dict) -> None:
    p.write_text(json.dumps(obj, ensure_ascii=False, indent=2), encoding="utf-8")

# ── Process control: terminate children cleanly on Ctrl+C ────────────────────
_RUNNING = set()
def _shutdown(*_):
    for proc in list(_RUNNING):
        try: os.killpg(proc.pid, signal.SIGTERM)
        except Exception: pass
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

# ── Language selection with fallback ─────────────────────────────────────────
def pick_lang_from(mode: str, src: Path, manifest_lang: Optional[str]) -> Optional[str]:
    if mode == "manifest" and manifest_lang:
        l = manifest_lang.strip().lower()
        return "cpp" if l.startswith("cpp") else ("c" if l.startswith("c") else None)
    if mode == "ext":
        ext = src.suffix.lower()
        if ext == ".c":  return "c"
        if ext in (".cpp", ".cc", ".cxx", ".hpp", ".hh"): return "cpp"
    return None  # auto

# ── Try to parse into a temp FILE and then move to final ─────────────────────
def try_parse(joern_parse: str, src: Path, out_dir: Path,
              final_file: Path, language: Optional[str],
              timeout: Optional[int], keep_logs: bool, log_dir: Path) -> bool:
    """
    Robust joern-parse:
      1) Force a file output (fast path).
      2) If it fails, retry with a directory output and pick the first *.cpg.bin.
    Also: use a src path whose suffix matches the language for this attempt.
    """
    ensure_dir(out_dir)
    src_for_lang = prepare_src_for_lang(src, language)
    log_path = log_dir / f"{final_file.stem}.parse.log"

    # ---- Path A: output to FILE ----
    tmp_file = out_dir / (final_file.name + ".tmp")
    if tmp_file.exists():
        try: tmp_file.unlink()
        except Exception: pass

    cmd_a = [joern_parse, str(src_for_lang), "--output", str(tmp_file)]
    if language:
        cmd_a += ["--language", language]

    rc_a = run_cmd(cmd_a, cwd=out_dir, log_path=log_path,
                   timeout=timeout, keep_log_on_success=keep_logs)
    if rc_a == 0 and tmp_file.exists():
        if final_file.exists():
            final_file.unlink()
        tmp_file.rename(final_file)
        return final_file.exists()

    # ---- Path B: output to DIR and pick a *.cpg.bin inside ----
    tmp_dir = out_dir / (final_file.name + ".tmpdir")
    if tmp_dir.exists():
        shutil.rmtree(tmp_dir, ignore_errors=True)

    cmd_b = [joern_parse, str(src_for_lang), "--output", str(tmp_dir)]
    if language:
        cmd_b += ["--language", language]

    rc_b = run_cmd(cmd_b, cwd=out_dir, log_path=log_path,
                   timeout=timeout, keep_log_on_success=keep_logs)
    if rc_b == 0 and tmp_dir.exists():
        candidates = list(tmp_dir.rglob("*.cpg.bin")) or list(tmp_dir.rglob("*.bin"))
        if candidates:
            if final_file.exists():
                final_file.unlink()
            shutil.move(str(candidates[0]), str(final_file))
            shutil.rmtree(tmp_dir, ignore_errors=True)
            return final_file.exists()

    # cleanup on failure
    try:
        if tmp_file.exists(): tmp_file.unlink()
        if tmp_dir.exists(): shutil.rmtree(tmp_dir, ignore_errors=True)
    except Exception:
        pass
    return False



# ── Task & stages ────────────────────────────────────────────────────────────
@dataclass
class Task:
    split: str
    src: Path
    stem: str                # e.g., train_func_0000001
    out_split: Path          # e.g., .../CPGs/.../<split>
    log_dir: Path            # e.g., .../CPGs/.../<split>/logs
    joern_parse: str
    joern_export: str
    label: Optional[str]
    lang_m: Optional[str]
    reprs: List[str]
    fmt: Optional[str]
    retries: int
    timeout: Optional[int]
    keep_logs: bool
    force: bool
    lang_mode: str
    compress: str            # "none" | "zip" | "gz"


def parse_func(t: Task) -> Tuple[str, bool, str]:
    final = t.out_split / f"{t.stem}.cpg.bin"

    if final.exists() and not t.force:
        return (t.stem, True, "cached")

    if is_trivially_empty(t.src):
        (t.log_dir / f"{t.stem}.parse.log").write_text(
            "skipped: empty or whitespace-only\n", encoding="utf-8"
        )
        return (t.stem, False, "empty_source")

    # Attempt order:
    first = pick_lang_from(t.lang_mode, t.src, t.lang_m)
    if first == "cpp":
        order = ["c", "cpp"]
    elif first == "c":
        order = ["c", "cpp"]
    else:
        order = ["c", "cpp"]  # default to C first for Draper

    for lang in order:
        for _ in range(max(1, t.retries)):
            if try_parse(t.joern_parse, t.src, t.out_split, final, lang,
                         t.timeout, t.keep_logs, t.log_dir):
                # Optional compression
                if t.compress != "none":
                    try:
                        if t.compress == "zip":
                            z = t.out_split / f"{t.stem}.cpg.bin.zip"
                            with zipfile.ZipFile(z, "w", compression=zipfile.ZIP_DEFLATED) as zf:
                                zf.write(final, arcname=final.name)
                        elif t.compress == "gz":
                            pigz = shutil.which("pigz")
                            if pigz:
                                subprocess.check_call([pigz, "-f", "-k", str(final)])
                            else:
                                import gzip, shutil as sh
                                gz = t.out_split / f"{t.stem}.cpg.bin.gz"
                                with open(final, "rb") as fi, gzip.open(gz, "wb") as fo:
                                    sh.copyfileobj(fi, fo)
                    except Exception:
                        pass
                return (t.stem, True, f"parsed_{lang}")

    return (t.stem, False, "parse_failed_both")



def export_func(t: Task) -> Tuple[str, bool, str]:
    cpg = t.out_split / f"{t.stem}.cpg.bin"
    if not cpg.exists():
        return (t.stem, False, "no_cpg")

    ebase = t.out_split / "exports" / t.stem
    ensure_dir(ebase)

    cpg_link = ebase / "cpg.bin"
    if cpg_link.exists() or cpg_link.is_symlink():
        try: cpg_link.unlink()
        except Exception: pass
    os.symlink(cpg, cpg_link)

    ok = True
    for r in t.reprs:
        out_dir = ebase / f"export_{r}"
        if out_dir.exists():
            if t.force:
                shutil.rmtree(out_dir, ignore_errors=True)
            elif dir_nonempty(out_dir):
                continue
            else:
                shutil.rmtree(out_dir, ignore_errors=True)

        cmd = [t.joern_export, "--repr", r, "--out", str(out_dir)]
        if t.fmt:
            cmd += ["--format", t.fmt]

        rc = run_cmd(cmd, cwd=ebase,
                     log_path=t.log_dir / f"{t.stem}.export_{r}.log",
                     timeout=t.timeout, keep_log_on_success=t.keep_logs)
        if rc != 0 or not dir_nonempty(out_dir):
            ok = False

    return (t.stem, ok, "export_ok" if ok else "export_partial")

# ── Orchestration ────────────────────────────────────────────────────────────
def parse_args():
    ap = argparse.ArgumentParser(description="Draper per-function CPGs (flat files, robust).")
    ap.add_argument("--perfunc-base", default=str(PERFUNC_BASE))
    ap.add_argument("--out-base",     default=str(OUT_BASE))
    ap.add_argument("--splits",       default="train,valid,test")
    ap.add_argument("--stage",        choices=["parse","export","both"], default="both")
    ap.add_argument("--lang-source",  choices=["ext","manifest","auto"], default="ext")

    ap.add_argument("--repr",         default="ast,cfg")
    ap.add_argument("--format",       default="graphson")
    ap.add_argument("--workers",      type=int, default=60)     # good start for -Xmx3g on 80c/250GB
    ap.add_argument("--retries",      type=int, default=1)
    ap.add_argument("--timeout",      type=int, default=0)
    ap.add_argument("--force",        action="store_true")
    ap.add_argument("--log-on-success", action="store_true")

    ap.add_argument("--compress",     choices=["none","zip","gz"], default="none",
                    help="Also write <stem>.cpg.bin.zip (or .gz) like Devign; optional.")
    ap.add_argument("--joern-parse",  default=which("joern-parse") or "joern-parse")
    ap.add_argument("--joern-export", default=which("joern-export") or "joern-export")
    return ap.parse_args()

def build_tasks(split: str, perfunc_base: Path, out_split: Path,
                rows: List[Dict[str,str]], args) -> List[Task]:
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
        lang_m = r.get("lang", None)

        tasks.append(Task(
            split=split, src=src, stem=stem,
            out_split=out_split, log_dir=log_dir,
            joern_parse=args.joern_parse, joern_export=args.joern_export,
            label=r.get("label", None), lang_m=lang_m,
            reprs=[x.strip() for x in args.repr.split(",") if x.strip()],
            fmt=(args.format.strip() or None),
            retries=max(1, args.retries),
            timeout=(args.timeout or None),
            keep_logs=bool(args.log_on_success),
            force=bool(args.force),
            lang_mode=args.lang_source,
            compress=args.compress
        ))
    return tasks


def run_pool(stage: str, tasks: List[Task], workers: int) -> Tuple[int,int,int]:
    ok = partial = failed = 0
    fn = parse_func if stage == "parse" else export_func
    with ThreadPoolExecutor(max_workers=max(1, workers)) as ex:
        futures = {ex.submit(fn, t): t for t in tasks}
        for fut in tqdm(as_completed(futures), total=len(futures), desc=f"{stage} stage"):
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
        print(f"[{split}] functions={len(tasks)} → {out_split} (flat)")

        parse_ok = parse_fail = export_ok = export_partial = export_fail = 0

        if a.stage in ("parse","both"):
            ok, _, fail = run_pool("parse", tasks, a.workers)
            parse_ok, parse_fail = ok, fail

        if a.stage in ("export","both"):
            ok, part, fail = run_pool("export", tasks, a.workers)
            export_ok, export_partial, export_fail = ok, part, fail

        write_json(out_split / "summary.json", {
            "split": split,
            "stage": a.stage,
            "repr": a.repr, "format": a.format,
            "parse_ok": parse_ok, "parse_failed": parse_fail,
            "export_ok": export_ok, "export_partial": export_partial, "export_failed": export_fail
        })

        # Optional: list of produced cpgs (like your Devign folder had)
        with (out_split / "cpg_list.txt").open("w", encoding="utf-8") as fh:
            for p in sorted(out_split.glob("*.cpg.bin")):
                fh.write(str(p.name) + "\n")

    print("✓ Done.")

if __name__ == "__main__":
    main()



'''
Phase 1 — Parse only (fast, like Devign):

export JAVA_TOOL_OPTIONS="-Xms1g -Xmx3g"
ulimit -n 65535

python 05_batch_cpg_draper.py \
  --stage parse \
  --splits train \
  --lang-source ext \
  --workers 60 \
  --retries 1 \
  --compress zip \
  --log-on-success






Phase 2 — Export only (when/where needed):

python 05_batch_cpg_draper.py \
  --stage export \
  --splits train \
  --repr ast,cfg \
  --format graphson \
  --workers 40 \
  --retries 1
1






'''



