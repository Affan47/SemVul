#!/usr/bin/env bash
# Export per-repr from *.cpg.bin, then MERGE to one JSON per function.
# - Exports AST/CFG/DDG/... into separate folders, then merges into export.json (single file per function)
# - Preserves edge labels; prefixes node/edge endpoints with repr (e.g., ast:, cfg:) to avoid ID collisions
# - Logs export and merge per item under <OUT_DIR>/logs/
# - Parallel, cached, resumable (skips done items)
# Requires: joern >= 4.x, python3

set -euo pipefail
shopt -s nullglob

# ─────────────── CLI ────────────────
SPLIT="${1:-}"; FMT="${2:-graphson}"
if [[ -z "${SPLIT}" || ! "${FMT}" =~ ^(graphson|proto-json)$ ]]; then
  echo "Usage: $0 {train|valid|test} [graphson|proto-json]" >&2
  exit 1
fi

# ─────────────── Paths (Reveal) ────────────────
BASE_CPG="./CPGs/normalized_reveal_functions/${SPLIT}"
BASE_OUT="./Json_exports/normalized_reveal_json"
OUT_DIR="${BASE_OUT}/${SPLIT}_${FMT}"
[[ -d "$BASE_CPG" ]] || { echo "FATAL: split dir not found: $BASE_CPG" >&2; exit 1; }
mkdir -p "$OUT_DIR/logs"

# ─────────────── Joern + runtime ────────────────
JOERN_EXPORT="$(command -v joern-export || true)"
[[ -x "$JOERN_EXPORT" ]] || { echo "FATAL: joern-export not in PATH" >&2; exit 1; }
"$JOERN_EXPORT" --help | grep -q -- '--repr' || { echo "FATAL: joern-export missing --repr option" >&2; exit 1; }

# Neutralize global Java flags so -J-Xmx takes effect
export JAVA_TOOL_OPTIONS=""

# Tunables (override via env): HEAP=6G PAR=40 QUIET=1 REPRS="ast,cfg,ddg,cdg,calls"
HEAP="${HEAP:-6G}"
PAR="${PAR:-40}"
QUIET="${QUIET:-1}"
REPRS="${REPRS:-ast,cfg,ddg}"

# ─────────────── Pretty prints ────────────────
if test -t 1; then
  GRN=$'\e[0;32m'; RED=$'\e[0;31m'; CYA=$'\e[0;36m'; YLW=$'\e[0;33m'; NC=$'\e[0m'
else GRN=; RED=; CYA=; YLW=; NC=; fi
ts(){ printf '%s %s\n' "$(date +'%H:%M:%S')" "$*"; }

ts "${CYA}Split        : ${SPLIT}${NC}"
ts "${CYA}Source CPGs  : ${BASE_CPG}${NC}"
ts "${CYA}Output dir   : ${OUT_DIR}${NC}"
ts "${CYA}Format       : ${FMT}${NC}"
ts "${CYA}Representations: ${REPRS}${NC}"
ts "${CYA}joern-export : $(basename "$JOERN_EXPORT")${NC}"
ts "${CYA}Parallelism  : ${PAR} cores${NC}"
ts "${CYA}Java heap    : -Xmx${HEAP}${NC}"
echo

# Clean stale tmp parent dirs from previous runs
find "$OUT_DIR" -maxdepth 1 -type d -name '*.tmp.*' -print0 | xargs -0r rm -rf

# Worklist
mapfile -t RAW_PATHS < <(find "$BASE_CPG" -maxdepth 1 -type f -name '*.cpg.bin' | sort)
(( ${#RAW_PATHS[@]} > 0 )) || { echo "FATAL: No *.cpg.bin found under $BASE_CPG"; exit 1; }

# Skip items that already have a merged export.json
mapfile -t TODO_PATHS < <(
  for p in "${RAW_PATHS[@]}"; do
    b="${p##*/}"; s="${b%.cpg.bin}"
    [[ -f "$OUT_DIR/$s/export.json" ]] || echo "$p"
  done
)

total=${#RAW_PATHS[@]}
todo=${#TODO_PATHS[@]}
ts "RAW *.cpg.bin found: $total"
ts "To process (skip cached): $todo"
printf 'First 10 todo:\n'; for p in "${TODO_PATHS[@]:0:10}"; do echo "  ${p##*/}"; done

export JOERN_EXPORT OUT_DIR FMT GRN RED YLW NC HEAP QUIET REPRS

# ─────────────── Python merger (embedded) ────────────────
merge_one_python='
import json, sys
from pathlib import Path

base = Path(sys.argv[1])   # OUT_DIR/<id>
fmt  = sys.argv[2]
reprs = sys.argv[3].split(",")

log = base.parent / "logs" / (base.name + ".merge.log")
def logw(msg):
    log.parent.mkdir(parents=True, exist_ok=True)
    with log.open("a", encoding="utf-8") as fh:
        fh.write(str(msg) + "\n")

def read_json_any(p: Path):
    try:
        s = p.read_text(encoding="utf-8")
    except Exception as e:
        logw(f"[readfail] {p}: {e}")
        return []
    s = s.strip()
    if not s:
        return []
    if s[0] == "[":
        try: return json.loads(s)
        except Exception as e:
            logw(f"[json-array-parse-error] {p}: {e}"); return []
    out = []
    for line in s.splitlines():
        line=line.strip()
        if not line: continue
        try: out.append(json.loads(line))
        except Exception as e:
            logw(f"[ndjson-parse-error] {p}: {e}")
    return out

def prefix_id(val, rep):
    return f"{rep}:{val}"

def merge(base: Path, fmt: str, reprs: list[str]):
    nodes = []
    edges = []
    for rep in reprs:
        rep_dir = base / f"export_{rep}"
        if not rep_dir.exists():
            logw(f"[missing-repr] {rep_dir}")
            continue
        nodir = rep_dir / "nodes"
        egdir = rep_dir / "edges"
        n = e = 0
        if nodir.exists():
            files = list(nodir.rglob("*.json")) + list(nodir.rglob("*.graphson")) + list(nodir.rglob("*.proto.json"))
            for f in sorted(files):
                for it in read_json_any(f):
                    if "id" in it: it["id"] = prefix_id(it["id"], rep)
                    it["repr"] = rep
                    nodes.append(it); n += 1
        if egdir.exists():
            files = list(egdir.rglob("*.json")) + list(egdir.rglob("*.graphson")) + list(egdir.rglob("*.proto.json"))
            for f in sorted(files):
                for it in read_json_any(f):
                    if "outV" in it: it["outV"] = prefix_id(it["outV"], rep)
                    if "inV"  in it: it["inV"]  = prefix_id(it["inV"],  rep)
                    if "src"  in it: it["src"]  = prefix_id(it["src"],  rep)
                    if "dst"  in it: it["dst"]  = prefix_id(it["dst"],  rep)
                    it["repr"] = rep
                    edges.append(it); e += 1
        logw(f"[repr {rep}] nodes={n} edges={e}")

    header = {
        "schemaVersion": "reveal-merged-v1",
        "format": fmt,
        "reps": reprs,
        "functionId": base.name,
    }
    merged = {"header": header, "nodes": nodes, "edges": edges}
    outp = base / "export.json"
    try:
        outp.write_text(json.dumps(merged, ensure_ascii=False), encoding="utf-8")
        logw(f"[merged] nodes={len(nodes)} edges={len(edges)} -> {outp}")
        return 0
    except Exception as e:
        logw(f"[merge-write-error] {e}")
        return 1

sys.exit( merge(base, fmt, reprs) )
'

process_one() {
  local bin_path="$1"
  local b="${bin_path##*/}"
  local id="${b%.cpg.bin}"         # e.g., train_func_0006083
  local parent tmpdir dir rc logf

  [[ -f "$bin_path" ]] || { echo "${YLW}MISS ${id}${NC}"; return 0; }

  dir="$OUT_DIR/$id"
  logf="$OUT_DIR/logs/${id}.export.log"

  # Cache hit
  if [[ -f "$dir/export.json" ]]; then
    [[ "$QUIET" == "1" ]] || echo "skip ${id} (cached)"
    return 0
  fi

  # Create unique parent for tmp; Joern requires parent to exist
  parent="$(mktemp -d -p "$OUT_DIR" "${id}.tmp.XXXXXXXX")"
  tmpdir="$parent/out"
  mkdir -p "$tmpdir"   # <<< FIX: ensure parent out/ exists so Joern can create export_<repr> under it

  # Run per-repr exports
  IFS=',' read -ra REPR_ARR <<< "$REPRS"
  for R in "${REPR_ARR[@]}"; do
    rc=0
    if [[ "$QUIET" == "1" ]]; then
      "$JOERN_EXPORT" --repr="$R" --format="$FMT" --out "$tmpdir/export_$R" "$bin_path" -J-Xmx"${HEAP}" >"$logf" 2>&1 || rc=$?
    else
      echo "[joern] $id :: $R"
      "$JOERN_EXPORT" --repr="$R" --format="$FMT" --out "$tmpdir/export_$R" "$bin_path" -J-Xmx"${HEAP}" 2>&1 | tee -a "$logf" || rc=$?
    fi
    if [[ ${rc:-0} -ne 0 ]]; then
      echo "rc=$rc on $id:$R; retry with bigger heap" >>"$logf"
      "$JOERN_EXPORT" --repr="$R" --format="$FMT" --out "$tmpdir/export_$R" "$bin_path" -J-Xmx8G >>"$logf" 2>&1 || rc=$?
      if [[ ${rc:-0} -ne 0 ]]; then
        echo "${RED}✗ ${id}:${R} (joern-export rc=$rc) — see $logf${NC}"
        rc=0  # keep going; merger will log missing repr
      fi
    fi
  done

  # Promote tmpdir to final dir, then merge
  if [[ -d "$dir" ]]; then rm -rf "$dir"; fi
  mv "$tmpdir" "$dir"      # move only the out/ (now contains export_* dirs)
  rm -rf "$parent" || true

  # Merge all reprs into one JSON (export.json)
  if [[ "$QUIET" != "1" ]]; then echo "[merge] $id"; fi
  python3 - "$dir" "$FMT" "$REPRS" <<'PY'
'"$merge_one_python"'
PY

  if [[ -f "$dir/export.json" ]]; then
    echo "${GRN}✓  ${id}${NC}"
    return 0
  else
    echo "${RED}!  ${id} (no export.json; kept artifacts in: $dir)${NC}"
    echo "No export.json produced" >>"$logf"
    return 2
  fi
}
export -f process_one
export merge_one_python

# ─────────────── MAIN (parallel) ────────────────
printf '%s\0' "${TODO_PATHS[@]}" | xargs -0 -n1 -P"$PAR" bash -lc 'process_one "$1"' _

# ─────────────── SUMMARY ────────────────
done_cnt=$(find "$OUT_DIR" -type f -name export.json | wc -l | awk "{print \$1}")
ts "${GRN}Finished: ${done_cnt} / ${total} with export.json (${todo} processed this run)${NC}"
echo "Artifacts under: $OUT_DIR"
echo "Logs under     : $OUT_DIR/logs"



#
# export HEAP=8G PAR=56 REPRS="ast,cfg,cdg,calls" QUIET=1
#  ./06a_export_cpg_reveal.sh valid graphson

./06a_export_cpg_reveal.sh valid graphson  
#./06a_export_cpg_reveal.sh test graphson
