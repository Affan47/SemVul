#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
make_adv_and_manifests.py · v15 (manifests-first, safe clean → fresh mutants, enhanced resolver)

Order: Build manifests → **Clean old mutants** → Generate fresh mutants → Verify

New:
- --clean-first (enabled by default): removes existing mutants before generation
- --aggressive-clean: remove any snap_adv*.json (ignores suffix)
- Parallel cleaner with tqdm

Python ≥3.7 compatible.
"""

# ---------------- imports ----------------
import csv, json, random, pathlib, os, argparse, sys, time, traceback, re
from concurrent.futures import ProcessPoolExecutor, as_completed
from typing import Any, Dict, Tuple, List, Optional
from tqdm import tqdm

# ---------------- utils ----------------

def log(msg: str, *, v: bool = True):
    if v:
        print(msg, flush=True)

def _open_csv_bom_safe(path: pathlib.Path):
    try:
        return open(path, "r", encoding="utf-8-sig", newline="")
    except Exception:
        return open(path, "r", encoding="utf-8", newline="")

def _sniff_reader(fin):
    sample = fin.read(4096)
    fin.seek(0)
    try:
        dialect = csv.Sniffer().sniff(sample, delimiters=[",", "\t", ";", "|"])
        rd = csv.DictReader(fin, dialect=dialect)
    except Exception:
        rd = csv.DictReader(fin, delimiter=",", skipinitialspace=True)
    fns = rd.fieldnames or []
    if len(fns) == 1 and any(d in fns[0] for d in [",", "\t", ";", "|"]):
        fin.seek(0)
        rd = csv.DictReader(fin, delimiter=",", skipinitialspace=True)
    return rd

def _unwrap(v: Any):
    if isinstance(v, dict) and "@value" in v:
        return _unwrap(v["@value"])
    if isinstance(v, list):
        return [_unwrap(x) for x in v]
    if isinstance(v, dict):
        return {k: _unwrap(val) for k, val in v.items()}
    return v

def _g_int64(x: int) -> Dict[str, Any]:
    return {"@type": "g:Int64", "@value": int(x)}

def _g_edge(id_int: int, outV: int, outVLabel: str, inV: int, inVLabel: str, label: str, props: Optional[Dict[str, Any]] = None) -> Dict[str, Any]:
    return {
        "@type": "g:Edge",
        "id": _g_int64(id_int),
        "label": label,
        "inV": _g_int64(inV),
        "inVLabel": inVLabel,
        "outV": _g_int64(outV),
        "outVLabel": outVLabel,
        "properties": props if props is not None else {}
    }

def _collect(g: Dict[str, Any]):
    gv = g.get("@value", {})
    V = gv.get("vertices", []) or []
    E = gv.get("edges", []) or []
    id2label = {}
    for v in V:
        vid = _unwrap(v.get("id"))
        vlabel = _unwrap(v.get("label"))
        if isinstance(vid, int):
            id2label[vid] = str(vlabel)
    return id2label, E

def _max_edge_id(E: List[Dict[str, Any]]) -> int:
    if not E: return 0
    return max(int(_unwrap(e.get("id"))) for e in E)

def _has_edge(E: List[Dict[str, Any]], outV: int, inV: int, label: str) -> bool:
    for e in E:
        try:
            if int(_unwrap(e.get("outV"))) == outV and int(_unwrap(e.get("inV"))) == inV and str(_unwrap(e.get("label"))) == label:
                return True
        except Exception:
            continue
    return False

# ---------------- GraphSON mutators ----------------

def mut_add_dead_cfg_edge(g: Dict[str, Any], rng: random.Random) -> Dict[str, Any]:
    id2label, E = _collect(g)
    blocks = [vid for vid, lab in id2label.items() if lab == "BLOCK"]
    if len(blocks) >= 2:
        a, b = rng.sample(blocks, 2)
        if a != b and not _has_edge(E, a, b, "CFG"):
            new_id = _max_edge_id(E) + 1
            E.append(_g_edge(new_id, outV=a, outVLabel="BLOCK", inV=b, inVLabel="BLOCK", label="CFG"))
    return g

def mut_swap_ast_children(g: Dict[str, Any], rng: random.Random) -> Dict[str, Any]:
    E = g["@value"]["edges"]
    ast_edges = [e for e in E if str(_unwrap(e.get("label"))) == "AST"]
    if len(ast_edges) >= 2:
        x, y = rng.sample(ast_edges, 2)
        x["inV"], y["inV"] = y["inV"], x["inV"]
        x["inVLabel"], y["inVLabel"] = y["inVLabel"], x["inVLabel"]
    return g

def mut_drop_edge_safe(g: Dict[str, Any], rng: random.Random) -> Dict[str, Any]:
    E = g["@value"]["edges"]
    if len(E) <= 1:
        return g
    SAFE = {"EVAL_TYPE", "DOMINATE", "POST_DOMINATE", "REACHING_DEF", "CDG"}
    cand = [i for i,e in enumerate(E) if str(_unwrap(e.get("label"))) in SAFE]
    if not cand:
        cand = [i for i,e in enumerate(E) if str(_unwrap(e.get("label"))) not in {"SOURCE_FILE"}]
    if cand:
        del E[rng.choice(cand)]
    return g

def mut_duplicate_ref(g: Dict[str, Any], rng: random.Random) -> Dict[str, Any]:
    import copy as _copy
    E = g["@value"]["edges"]
    ref_edges = [e for e in E if str(_unwrap(e.get("label"))) == "REF"
                 and str(_unwrap(e.get("outVLabel"))) == "IDENTIFIER"
                 and str(_unwrap(e.get("inVLabel"))) == "LOCAL"]
    if ref_edges:
        base = _copy.deepcopy(rng.choice(ref_edges))
        base["id"] = _g_int64(_max_edge_id(E) + 1)
        id2label, _ = _collect(g)
        idents = [vid for vid,lab in id2label.items() if lab == "IDENTIFIER"]
        locals_ = [vid for vid,lab in id2label.items() if lab == "LOCAL"]
        if idents and locals_:
            base["outV"] = _g_int64(rng.choice(idents))
            base["inV"]  = _g_int64(rng.choice(locals_))
        E.append(base)
    return g

def mut_tweak_literal_vertex(g: Dict[str, Any], rng: random.Random) -> Dict[str, Any]:
    V = g["@value"]["vertices"]
    for v in V:
        if str(_unwrap(v.get("label"))) == "LITERAL":
            props = v.get("properties", {})
            vp = props.get("CODE")
            if isinstance(vp, dict) and "@value" in vp:
                lst = _unwrap(vp["@value"])
                if isinstance(lst, list) and lst:
                    s = str(lst[0])
                    if s.isdigit() or (s.startswith("-") and s[1:].isdigit()):
                        new_val = str(int(s) + rng.choice([-2,-1,1,2]))
                        props["CODE"] = {"@type":"g:VertexProperty","@value":{"@type":"g:List","@value":[new_val]}}
                        break
    return g

EDGE_MUTS   = [mut_add_dead_cfg_edge, mut_duplicate_ref, mut_drop_edge_safe]
OTHER_MUTS  = [mut_swap_ast_children, mut_tweak_literal_vertex]
ALL_MUTS    = EDGE_MUTS + OTHER_MUTS

# ---------------- manifest parsing ----------------

def _read_source_by_name(src_manifest: pathlib.Path, *, verbose: bool) -> List[Tuple[str,int,int]]:
    """Return (name_stem, orig_index, label)"""
    rows: List[Tuple[str,int,int]] = []
    missing = 0
    with _open_csv_bom_safe(src_manifest) as fin:
        rd = _sniff_reader(fin)
        for r in rd:
            fid = (r.get("function_id") or "").strip()
            lab_raw = (r.get("label") or "0").strip()
            idx_raw = (r.get("orig_index") or "").strip()
            if not fid:
                missing += 1
                continue
            name = pathlib.Path(fid).stem
            try:
                idx = int(idx_raw)
            except Exception:
                idx = int("".join(ch for ch in name if ch.isdigit()) or "0")
            try:
                lab = int(lab_raw)
            except Exception:
                lab = 0
            rows.append((name, idx, lab))
    if verbose:
        log(f"[labels] {src_manifest.name}: rows={len(rows)} missing_function_id={missing}")
    return rows

# ---------------- directory index & resolver ----------------

_digit_tail_re = re.compile(r"(\d+)$")

def _tail_digits(s: str) -> Optional[str]:
    m = _digit_tail_re.search(s)
    return m.group(1) if m else None

class DirIndex:
    """Index split root directories and support fuzzy resolution."""
    def __init__(self, split: str, root: pathlib.Path, verbose: bool):
        self.split = split
        self.root = root
        self.verbose = verbose
        self.by_name: Dict[str, str] = {}
        self.by_stem: Dict[str, str] = {}
        self.by_digits: Dict[str, List[str]] = {}
        self.sample: List[str] = []
        self._build()

    def _build(self):
        if not self.root.exists():
            return
        try:
            dirs = [p for p in self.root.iterdir() if p.is_dir()]
        except Exception:
            dirs = []
        for i, d in enumerate(dirs):
            nm = d.name
            st = pathlib.Path(nm).stem
            self.by_name[nm] = nm
            self.by_stem.setdefault(st, nm)
            td = _tail_digits(nm)
            if td:
                self.by_digits.setdefault(td, []).append(nm)
            if i < 10:
                self.sample.append(nm)
        log(f"[{self.split}] dir-index: {len(dirs)} function dirs (e.g., {', '.join(self.sample[:5])})", v=self.verbose)

    def resolve(self, name_stem: str, orig_index: int) -> Optional[str]:
        """Try: exact stem → stem digits → padded index → any matching digits."""
        # 1) exact stem
        d1 = self.root / name_stem / "export.json"
        if d1.is_file(): return name_stem

        # 2) stem's trailing digits
        sd = _tail_digits(name_stem)
        if sd:
            for cand in self.by_digits.get(sd, []):
                if (self.root / cand / "export.json").is_file():
                    return cand

        # 3) padded orig_index
        pad7 = f"{orig_index:07d}"
        cand3 = f"{self.split}_func_{pad7}"
        if (self.root / cand3 / "export.json").is_file():
            return cand3

        # 4) any dir sharing digits with either stem or index
        for key in dict.fromkeys([sd, pad7]):
            if not key: continue
            for cand in self.by_digits.get(key, []):
                if (self.root / cand / "export.json").is_file():
                    return cand
        return None

# ---------------- Phase A: build manifests ----------------

def build_manifests_first(
    split: str,
    dir_index: DirIndex,
    src_manifest: pathlib.Path,
    rows: List[Tuple[str,int,int]],
    T: int,
    suffix: str,
    verbose: bool,
) -> Tuple[pathlib.Path, pathlib.Path, int]:
    adv_path = src_manifest.with_name(f"{src_manifest.stem}_advT{T}.csv")
    mut_path = src_manifest.with_name(f"{src_manifest.stem}_mutT{T-1}.csv")

    for p in (adv_path, mut_path):
        try: p.unlink(missing_ok=True)
        except Exception: pass

    unresolved = 0
    with open(adv_path, "w", newline="", encoding="utf-8") as fh_all, \
         open(mut_path, "w", newline="", encoding="utf-8") as fh_mut:
        wr_all = csv.writer(fh_all); wr_all.writerow(["index","label","commit","json_path"])
        wr_mut = csv.writer(fh_mut); wr_mut.writerow(["index","label","commit","json_path"])

        it = tqdm(rows, desc=f"[{split}] manifests", unit="idx") if verbose else rows
        for name, idx, lab in it:
            # original row
            wr_all.writerow([idx, lab, "", ""])

            picked = dir_index.resolve(name_stem=pathlib.Path(name).stem, orig_index=idx)
            dirname = picked if picked is not None else pathlib.Path(name).stem
            if picked is None: unresolved += 1

            for step in range(1, T):
                tag = f"adv{step}_{suffix}"
                rel = f"{dirname}/snap_{tag}.json"
                wr_all.writerow([idx, lab, tag, rel])
                wr_mut.writerow([idx, lab, tag, rel])

    if unresolved and verbose:
        log(f"[{split}] WARN: {unresolved} rows unresolved in manifests (placeholders written).", v=True)

    log(f"[{split}] manifests → {adv_path.name}, {mut_path.name}", v=True)
    return adv_path, mut_path, unresolved

# ---------------- Phase B0: CLEAN existing mutants ----------------

def _clean_dir_mutants(args):
    func_dir, T, suffix, aggressive = args
    d = pathlib.Path(func_dir)
    removed = 0
    try:
        if aggressive:
            patterns = ["snap_adv*.json"]
        else:
            patterns = [f"snap_adv{step}_{suffix}.json" for step in range(1, T)]
        for pat in patterns:
            for p in d.glob(pat):
                try:
                    p.unlink()
                    removed += 1
                except Exception:
                    pass
        return (str(d), removed, "")
    except Exception as e:
        return (str(d), removed, f"clean_failed: {e}")
def _any_mutants_exist(root: pathlib.Path, patterns: List[str]) -> bool:
    # quick existence check: stop after the first hit
    for pat in patterns:
        it = root.rglob(pat)
        try:
            next(it)
            return True
        except StopIteration:
            continue
        except Exception:
            continue
    return False

from concurrent.futures import ThreadPoolExecutor  # add at top with imports

def clean_existing_mutants(
    split: str,
    dir_index: DirIndex,
    rows: List[Tuple[str,int,int]],
    T: int,
    suffix: str,
    aggressive: bool,
    max_workers: int,
    verbose: bool,
) -> int:
    # Resolve function dirs once
    dirs = []
    missing = 0
    for name, idx, _lab in rows:
        picked = dir_index.resolve(name_stem=pathlib.Path(name).stem, orig_index=idx)
        if picked is None:
            missing += 1
            continue
        d = dir_index.root / picked
        if d.is_dir():
            dirs.append(str(d))

    # Decide patterns and quick skip if nothing to clean
    if aggressive:
        patterns = ["snap_adv*.json"]
    else:
        patterns = [f"snap_adv{step}_{suffix}.json" for step in range(1, T)]

    # Fast path: if no mutants in the whole split tree, skip
    if not _any_mutants_exist(dir_index.root, patterns):
        log(f"[{split}] clean: no existing mutants found under {dir_index.root}, skip.", v=verbose)
        return 0

    removed_total = 0
    failures = 0

    # Stream submissions with bounded in-flight using a ThreadPool (I/O bound)
    inflight_cap = max(1, max_workers * 8)  # generous but bounded
    pending = []
    it = iter(dirs)

    pbar = tqdm(total=len(dirs), desc=f"[{split}] clean", unit="dir", smoothing=0.05, disable=not verbose)

    def _submit(pool, d):
        return pool.submit(_clean_dir_mutants, (d, T, suffix, aggressive))

    with ThreadPoolExecutor(max_workers=max_workers) as pool:
        # Prime
        while len(pending) < inflight_cap:
            try:
                d = next(it)
            except StopIteration:
                break
            pending.append(_submit(pool, d))

        # Drain/Refill
        while pending:
            done_any = False
            for fu in list(pending):
                if fu.done():
                    done_any = True
                    pending.remove(fu)
                    try:
                        d_ret, removed, err = fu.result()
                        removed_total += int(removed)
                        if err:
                            failures += 1
                            log(f"[{split}] WARN {d_ret}: {err}", v=True)
                    except Exception as e:
                        failures += 1
                        log(f"[{split}] ERROR cleaner: {e}", v=True)
                    if pbar:
                        pbar.update(1)

            # Refill up to cap
            while len(pending) < inflight_cap:
                try:
                    d = next(it)
                except StopIteration:
                    break
                pending.append(_submit(pool, d))

            if not done_any:
                time.sleep(0.01)

    if pbar:
        pbar.close()

    log(f"[{split}] clean: removed {removed_total} mutant files (unresolved={missing}, failures={failures})", v=True)
    return removed_total

# ---------------- Phase B: generate mutants ----------------

def _row_seed_from_index(index: int, seed: int) -> int:
    return seed ^ (index & 0x7FFFFFFF)

def _gen_mutants_for_dir(args):
    func_dir, index, T, seed, suffix, overwrite = args
    base = pathlib.Path(func_dir) / "export.json"
    try:
        with open(base, "r", encoding="utf-8") as f:
            g0 = json.load(f)
    except Exception as e:
        return (str(func_dir), 0, f"read_export_failed: {e}")

    created = 0
    row_seed = _row_seed_from_index(index, seed)

    for step in range(1, T):
        tag = f"adv{step}_{suffix}"
        dest = pathlib.Path(func_dir) / f"snap_{tag}.json"
        if dest.exists() and not overwrite:
            continue

        rng = random.Random(row_seed ^ step)
        import copy as _copy
        g = _copy.deepcopy(g0)

        try:
            chosen = [rng.choice(EDGE_MUTS)]
            pool   = [m for m in ALL_MUTS if m not in chosen]
            extra  = rng.sample(pool, rng.randint(1, 3))

            orig_edges = len(g["@value"]["edges"])
            for m in chosen + extra:
                g = m(g, rng=rng)
            tries = 0
            while len(g["@value"]["edges"]) == orig_edges and tries < 3:
                g = mut_drop_edge_safe(g, rng=rng); tries += 1

            dest.parent.mkdir(parents=True, exist_ok=True)
            with open(dest, "w", encoding="utf-8") as fout:
                json.dump(g, fout)
            created += 1
        except Exception as e:
            return (str(func_dir), created, f"write_mutant_failed: {e}")

    return (str(func_dir), created, "")

def generate_mutants_from_manifests(
    split: str,
    dir_index: DirIndex,
    rows: List[Tuple[str,int,int]],  # (name_stem, orig_index, label)
    T: int,
    seed: int,
    max_workers: int,
    inflight_mult: int,
    overwrite: bool,
    suffix: str,
    verbose: bool,
    dry_run: bool,
) -> int:
    if dry_run:
        log(f"[{split}] DRY-RUN: skipping mutant generation; manifests already written.", v=verbose)
        return 0

    tasks: List[Tuple[str,int]] = []
    missing = 0
    for name, idx, _lab in rows:
        picked = dir_index.resolve(name_stem=pathlib.Path(name).stem, orig_index=idx)
        if picked is None:
            missing += 1
            continue
        d = dir_index.root / picked
        tasks.append((str(d), idx))

    max_inflight = max(1, inflight_mult * max_workers)
    created_total = 0
    failures = 0

    try:
        with ProcessPoolExecutor(max_workers=max_workers) as pool:
            pbar = tqdm(total=len(tasks), desc=f"[{split}] mutants", unit="func", smoothing=0.05) if verbose else None
            in_flight: Dict[Any, Tuple[str,int]] = {}
            it = iter(tasks)

            def _submit(d, idx):
                fu = pool.submit(_gen_mutants_for_dir, (d, idx, T, seed, suffix, overwrite))
                in_flight[fu] = (d, idx)

            while len(in_flight) < max_inflight:
                try:
                    d, idx = next(it)
                except StopIteration:
                    break
                _submit(d, idx)

            while in_flight:
                done_any = False
                for fu in list(in_flight.keys()):
                    if fu.done():
                        done_any = True
                        _d, _idx = in_flight.pop(fu)
                        try:
                            d_ret, created, err = fu.result()
                            created_total += int(created)
                            if err:
                                failures += 1
                                log(f"[{split}] WARN {d_ret}: {err}", v=True)
                        except Exception as e:
                            failures += 1
                            log(f"[{split}] ERROR {_d}: {e}\n{traceback.format_exc()}", v=True)
                        if pbar:
                            pbar.update(1)
                            pbar.set_postfix_str(f"created={created_total},fail={failures},miss={missing}")

                while len(in_flight) < max_inflight:
                    try:
                        d, idx = next(it)
                    except StopIteration:
                        break
                    _submit(d, idx)

                if not done_any:
                    time.sleep(0.01)

            if pbar: pbar.close()
    except Exception as e:
        log(f"[{split}] ProcessPoolExecutor failed: {e}. Falling back to sequential.", v=True)
        log(traceback.format_exc(), v=True)
        for d, idx in tqdm(tasks, desc=f"[{split}] mutants (sequential)", disable=not verbose):
            d_ret, created, err = _gen_mutants_for_dir((d, idx, T, seed, suffix, overwrite))
            created_total += int(created)
            if err:
                failures += 1
                log(f"[{split}] WARN {d_ret}: {err}", v=True)

    log(f"[{split}] mutants created: {created_total} (failures={failures}, source_missing={missing})", v=True)
    return created_total

# ---------------- Phase C: verification ----------------

def _open_manifest_rows(path: pathlib.Path) -> List[Dict[str,str]]:
    with _open_csv_bom_safe(path) as f:
        return list(_sniff_reader(f))

def _rows_for_idx(rows_list, idx):
    s = str(idx)
    return [r for r in rows_list if str(r.get("index","")).strip() == s]

def _read_indices_from_manifest(path: pathlib.Path) -> List[int]:
    out = []
    with _open_csv_bom_safe(path) as f:
        rd = _sniff_reader(f)
        for r in rd:
            try:
                out.append(int(str(r.get("index","")).strip()))
            except Exception:
                pass
    return out

def verify_after_generation(
    split: str,
    dir_index: DirIndex,
    src_manifest: pathlib.Path,
    adv_path: pathlib.Path,
    mut_path: pathlib.Path,
    rows: List[Tuple[str,int,int]],
    T: int,
    suffix: str,
    strict: bool,
    verbose: bool,
) -> bool:
    ok = True
    report_path = src_manifest.with_name(f"{src_manifest.stem}_verify_report.csv")
    try: report_path.unlink(missing_ok=True)
    except Exception: pass

    adv_idxs = set(_read_indices_from_manifest(adv_path))
    mut_idxs = set(_read_indices_from_manifest(mut_path))
    src_idxs = {idx for (_name, idx, _lab) in rows}

    idx_issue = []
    if adv_idxs != src_idxs:
        ok = False; idx_issue.append("adv_index_set_mismatch")
    if mut_idxs != src_idxs:
        ok = False; idx_issue.append("mut_index_set_mismatch")

    by_idx: Dict[int, Tuple[str,int]] = {idx:(name, lab) for (name, idx, lab) in rows}
    adv_rows = _open_manifest_rows(adv_path)
    mut_rows = _open_manifest_rows(mut_path)

    missing_count = 0
    label_mismatch_count = 0
    mutant_missing_total = 0

    with open(report_path, "w", newline="", encoding="utf-8") as fout:
        wr = csv.writer(fout)
        wr.writerow(["index","label_src","func_dir","export_json","mutant_files_ok","label_mismatches","notes"])

        for idx in tqdm(sorted(src_idxs), desc=f"[{split}] verify", unit="idx", disable=not verbose):
            name, label_src = by_idx[idx]
            stem = pathlib.Path(name).stem

            resolved = dir_index.resolve(stem, idx)
            func_dir = dir_index.root / (resolved if resolved is not None else stem)

            base_ok = False
            mutants_ok = True
            label_mismatch = False
            notes = []

            base = func_dir / "export.json"
            if base.is_file():
                base_ok = True
            else:
                wr.writerow([idx, label_src, func_dir.name, "NO", "NO", "N/A", "export_json_missing"])
                missing_count += 1
                ok = False
                continue

            # label consistency across adv/mut manifests
            def _rows_for(rws, idx):
                s = str(idx)
                return [r for r in rws if str(r.get("index","")).strip() == s]
            rows_idx = _rows_for(adv_rows, idx) + _rows_for(mut_rows, idx)
            for r in rows_idx:
                try:
                    lab = int(str(r.get("label","0")).strip())
                except Exception:
                    lab = None
                if lab != label_src:
                    label_mismatch = True
                    break

            for step in range(1, T):
                tag = f"adv{step}_{suffix}"
                dest = func_dir / f"snap_{tag}.json"
                if not dest.is_file():
                    mutants_ok = False
                    notes.append(f"missing:{dest.name}")

            if label_mismatch:
                label_mismatch_count += 1
                ok = False
            if not mutants_ok:
                mutant_missing_total += 1
                ok = False

            wr.writerow([
                idx,
                label_src,
                func_dir.name,
                "YES" if base_ok else "NO",
                "YES" if mutants_ok else "NO",
                "YES" if label_mismatch else "NO",
                ";".join(notes)
            ])

    if idx_issue:
        log(f"[{split}] Index-set issues: {', '.join(idx_issue)}", v=True)
    log(f"[{split}] Verification report → {report_path.name}", v=True)
    log(f"[{split}] Summary: missing_export={missing_count}, label_mismatch={label_mismatch_count}, mutant_sets_missing={mutant_missing_total}", v=True)

    if strict and not ok:
        log(f"[{split}] STRICT mode: verification failed.", v=True)
    return ok or (not strict)

# ---------------- CLI / main ----------------

def parse_args():
    ap = argparse.ArgumentParser(description="Build manifests → Clean mutants → Generate fresh mutants → Verify for each split.")
    ap.add_argument("--json-base", type=str, required=True, help="Base dir with {train,valid,test}_graphson/")
    ap.add_argument("--manifest-train", type=str, required=True, help="Source manifest_train.csv")
    ap.add_argument("--manifest-valid", type=str, required=True, help="Source manifest_valid.csv")
    ap.add_argument("--manifest-test",  type=str, required=True, help="Source manifest_test.csv")
    ap.add_argument("--T", type=int, default=6, help="Temporal window: original + (T-1) mutants.")
    ap.add_argument("--seed", type=int, default=42)
    ap.add_argument("--max-workers", type=int, default=min(64, os.cpu_count() or 1))
    ap.add_argument("--inflight-mult", type=int, default=8, help="Cap for in-flight tasks (x workers).")
    ap.add_argument("--overwrite-mutants", action="store_true", help="Rebuild mutants even if files already exist.")
    ap.add_argument("--clean-first", action="store_true", default=True, help="Remove existing mutants before generation (default on).")
    ap.add_argument("--aggressive-clean", action="store_true", help="Remove ANY snap_adv*.json (ignores suffix).")
    ap.add_argument("--suffix", type=str, default="nocm", help="Filename suffix: snap_adv{i}_<suffix>.json")
    ap.add_argument("--strict", action="store_true", help="Exit non-zero if verification fails for any split.")
    ap.add_argument("--only-split", choices=["train","valid","test"], help="Run only this split.")
    ap.add_argument("--verbose", action="store_true", help="Print progress details.")
    ap.add_argument("--dry-run", action="store_true", help="Do not write mutants; still builds manifests & can verify presence.")
    return ap.parse_args()

def main():
    args = parse_args()

    base = pathlib.Path(args.json_base)
    splits = {
        "train": {"root": base / "train_graphson", "src_manifest": pathlib.Path(args.manifest_train)},
        "valid": {"root": base / "valid_graphson", "src_manifest": pathlib.Path(args.manifest_valid)},
        "test":  {"root": base / "test_graphson",  "src_manifest": pathlib.Path(args.manifest_test)},
    }

    T = int(max(2, args.T))
    all_ok = True

    log(f"[paths] json-base={base}", v=True)
    log(f"[paths] split roots: " + ", ".join(f"{k}={v['root']}" for k,v in splits.items()), v=True)
    log(f"[paths] src manifests: " + ", ".join(f"{k}={v['src_manifest']}" for k,v in splits.items()), v=True)

    for split, cfg in splits.items():
        if args.only_split and split != args.only_split:
            continue

        root = cfg["root"]
        src_manifest = cfg["src_manifest"]

        if not root.exists():
            log(f"[{split}] SKIP: split root missing → {root}", v=True)
            continue
        if not src_manifest.exists():
            log(f"[{split}] SKIP: manifest missing → {src_manifest}", v=True)
            continue

        rows = _read_source_by_name(src_manifest, verbose=args.verbose)
        dir_index = DirIndex(split=split, root=root, verbose=args.verbose)

        # Phase A: Manifests
        adv_path, mut_path, unresolved = build_manifests_first(
            split=split,
            dir_index=dir_index,
            src_manifest=src_manifest,
            rows=rows,
            T=T,
            suffix=args.suffix,
            verbose=args.verbose,
        )

        # Phase B0: Clean existing mutants (default on)
        if args.clean_first and not args.dry_run:
            clean_existing_mutants(
                split=split,
                dir_index=dir_index,
                rows=rows,
                T=T,
                suffix=args.suffix,
                aggressive=bool(args.aggressive_clean),
                max_workers=int(args.max_workers),
                verbose=args.verbose,
            )

        # Phase B: Generate fresh mutants
        generate_mutants_from_manifests(
            split=split,
            dir_index=dir_index,
            rows=rows,
            T=T,
            seed=args.seed,
            max_workers=int(args.max_workers),
            inflight_mult=int(args.inflight_mult),
            overwrite=bool(args.overwrite_mutants),
            suffix=args.suffix,
            verbose=args.verbose,
            dry_run=args.dry_run,
        )

        # Phase C: Verify
        ok = verify_after_generation(
            split=split,
            dir_index=dir_index,
            src_manifest=src_manifest,
            adv_path=adv_path,
            mut_path=mut_path,
            rows=rows,
            T=T,
            suffix=args.suffix,
            strict=bool(args.strict),
            verbose=args.verbose,
        )
        all_ok = all_ok and ok

    if not all_ok and args.strict:
        sys.exit(2)

    print(f"\n✓ Done. Use *_advT{T}.csv for training.", flush=True)

if __name__ == "__main__":
    main()




"""

# Train split only, dry-run (write manifests, skip mutants), verbose
python -u make_adv_windows_all_draper.py \
  --json-base "./Json_exports/normalized_draper_json" \
  --manifest-train "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train.csv" \
  --manifest-valid "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid.csv" \
  --manifest-test  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test.csv" \
  --only-split train \
  --T 3 --max-workers 64 --inflight-mult 8 \
  --clean-first --aggressive-clean --suffix "nocm" \
  --dry-run --verbose


python -u make_adv_windows_all_draper.py \
  --json-base "./Json_exports/normalized_draper_json" \
  --manifest-train "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train.csv" \
  --manifest-valid "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid.csv" \
  --manifest-test  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test.csv" \
  --T 3 --max-workers 64 --inflight-mult 8 \
  --clean-first --aggressive-clean --suffix "nocm" \
  --overwrite-mutants --strict --verbose



  


"""