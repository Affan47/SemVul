#!/usr/bin/env bash
# 05a_export_cpg_to_json_draper_RAWONLY.sh — Export ONLY raw *.cpg.bin (skip zips)
# Uses absolute paths; safe with joern-export (does NOT pre-create --out dir)
# Requires: joern >= 4.x

set -euo pipefail
shopt -s nullglob

# ───────────────── CLI ─────────────────
SPLIT="${1:-}"; FMT="${2:-graphson}"
[[ -n "$SPLIT" && "$FMT" =~ ^(graphson|proto-json)$ ]] || {
  echo "Usage: $0 {train|valid|test} [graphson|proto-json]" >&2; exit 1; }

# ─────────────── Paths ────────────────
BASE_CPG="./CPGs/normalized_draper_functions/$SPLIT"
BASE_OUT="./Json_exports/normalized_draper_json"
OUT_DIR="$BASE_OUT/${SPLIT}_${FMT}"
[[ -d "$BASE_CPG" ]] || { echo "FATAL: split dir not found: $BASE_CPG" >&2; exit 1; }
mkdir -p "$OUT_DIR" "$OUT_DIR/logs"

# ─────────────── Joern + runtime ────────────────
JOERN_EXPORT="$(command -v joern-export || true)"
[[ -x "$JOERN_EXPORT" ]] || { echo "FATAL: joern-export not in PATH" >&2; exit 1; }

# Neutralize global Java flags so -J-Xmx takes effect
export JAVA_TOOL_OPTIONS=""

# Tunables (override via env): HEAP=4G PAR=16 QUIET=1
HEAP="${HEAP:-16G}"
PAR="${PAR:-16}"
QUIET="${QUIET:-1}"

# ─────────────── Pretty prints ────────────────
if test -t 1; then
  GRN=$'\e[0;32m'; RED=$'\e[0;31m'; CYA=$'\e[0;36m'; YLW=$'\e[0;33m'; NC=$'\e[0m'
else GRN=; RED=; CYA=; YLW=; NC=; fi
ts(){ printf '%s %s\n' "$(date +'%H:%M:%S')" "$*"; }

ts "${CYA}Split        : $SPLIT${NC}"
ts "${CYA}Source CPGs  : $BASE_CPG${NC}"
ts "${CYA}Output dir   : $OUT_DIR${NC}"
ts "${CYA}Format       : $FMT${NC}"
ts "${CYA}joern-export : $(basename "$JOERN_EXPORT")${NC}"
ts "${CYA}Parallelism  : ${PAR} cores${NC}"
ts "${CYA}Java heap    : -Xmx${HEAP}${NC}"
ts "${CYA}Mode         : RAW ONLY (*.cpg.bin)${NC}"
echo

# Clean stale tmp dirs from previous runs
find "$OUT_DIR" -maxdepth 1 -type d -name '*.tmp.*' -print0 | xargs -0r rm -rf

# ─────────────── Worklist from ABSOLUTE PATHS (RAW ONLY) ────────────────
mapfile -t RAW_PATHS < <(find "$BASE_CPG" -maxdepth 1 -type f -name '*.cpg.bin' | sort)
(( ${#RAW_PATHS[@]} > 0 )) || { echo "FATAL: No *.cpg.bin found under $BASE_CPG"; exit 1; }

# Skip already done (by stem derived from basename)
mapfile -t TODO_PATHS < <(
  for p in "${RAW_PATHS[@]}"; do
    b="${p##*/}"; s="${b%.cpg.bin}"
    [[ -f "$OUT_DIR/$s/export.json" ]] || echo "$p"
  done
)

total=${#RAW_PATHS[@]}
todo=${#TODO_PATHS[@]}
ts "RAW *.cpg.bin found: $total"
ts "To export (skip cached): $todo"
printf 'First 10 todo:\n'; for p in "${TODO_PATHS[@]:0:10}"; do echo "  ${p##*/}"; done

export JOERN_EXPORT OUT_DIR FMT GRN RED YLW NC HEAP QUIET

process_one() {
  local bin_path="$1"
  local b="${bin_path##*/}"
  local id="${b%.cpg.bin}"         # e.g., train_func_0006083
  local tmpdir dir rc found logf

  # Sanity: input exists
  [[ -f "$bin_path" ]] || { echo "${YLW}MISS ${id}${NC}"; return 0; }

  # joern-export requirement: --out must NOT exist → mktemp -u (unique non-existent path)
  tmpdir="$(mktemp -u -p "$OUT_DIR" "${id}.tmp.XXXXXXXX")"
  dir="$OUT_DIR/$id"
  logf="$OUT_DIR/logs/${id}.log"

  # Cache hit
  if [[ -f "$dir/export.json" ]]; then return 0; fi

  # Run joern-export (do NOT pre-create tmpdir)
  if [[ "$QUIET" == "1" ]]; then
    "$JOERN_EXPORT" --repr=all --format="$FMT" --out "$tmpdir" "$bin_path" -J-Xmx"${HEAP}" >"$logf" 2>&1 || rc=$?; rc=${rc:-0}
  else
    echo "[joern] $id -> $tmpdir"
    "$JOERN_EXPORT" --repr=all --format="$FMT" --out "$tmpdir" "$bin_path" -J-Xmx"${HEAP}" 2>&1 | tee "$logf" || rc=$?; rc=${rc:-0}
  fi

  # Retry with larger heap if first run failed
  if [[ ${rc:-0} -ne 0 ]]; then
    echo "rc=$rc on $id; retry with bigger heap" >>"$logf"
    "$JOERN_EXPORT" --repr=all --format="$FMT" --out "$tmpdir" "$bin_path" -J-Xmx6G >>"$logf" 2>&1 || rc=$?; rc=${rc:-0}
  fi
  if [[ ${rc:-0} -ne 0 ]]; then
    echo "${RED}✗ $id (joern-export rc=$rc) — see $logf${NC}"
    return 1
  fi

  # Promote produced file to export.json (search recursively to be robust)
  case "$FMT" in
    graphson)   found="$(find "$tmpdir" -type f -name '*.graphson' -o -name '*.json' | head -n1 || true)";;
    proto-json) found="$(find "$tmpdir" -type f -name '*.proto.json' -o -name '*.json' | head -n1 || true)";;
  esac
  [[ -n "$found" ]] && cp -f "$found" "$tmpdir/export.json"

  if [[ -f "$tmpdir/export.json" ]]; then
    rm -rf "$dir"; mv "$tmpdir" "$dir"
    echo "${GRN}✓  $id${NC}"
    return 0
  else
    # keep artifacts for inspection even if no export.json was detected
    rm -rf "$dir"; mv "$tmpdir" "$dir"
    echo "${RED}!  $id (no export.json; kept artifacts in: $dir)${NC}"
    echo "No export.json produced" >>"$logf"
    return 2
  fi
}
export -f process_one

# ─────────────── MAIN (parallel) ────────────────
printf '%s\0' "${TODO_PATHS[@]}" | xargs -0 -n1 -P"$PAR" bash -lc 'process_one "$1"' _

# ─────────────── SUMMARY ────────────────
done_cnt=$(find "$OUT_DIR" -type f -name export.json | wc -l)
ts "${GRN}Finished: $done_cnt / $total with export.json (${todo} processed this run)${NC}"
echo "Artifacts under: $OUT_DIR"
echo "Logs under     : $OUT_DIR/logs"







# Examples:
#   ./05a_export_cpg_draper.sh train
#   ./05a_export_cpg_to_json_draper.sh train proto-json
