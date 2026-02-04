#!/usr/bin/env bash
# export_cpg_to_json.sh  –  Convert *per-function* CPGs to JSON (GraphSON / proto-JSON)
# Joern ≥ 4.0

set -euo pipefail
shopt -s nullglob

###############################################################################
# ─── CLI ARGUMENTS ────────────────────────────────────────────────────────────
#   $1  split   : train | valid | test   (mandatory)
#   $2  format  : graphson | proto-json  (optional, default = graphson)
###############################################################################
[[ $# -ge 1 && $# -le 2 ]] ||
  { echo "Usage: $0 {train|valid|test} [graphson|proto-json]" >&2; exit 1; }

SPLIT="$1"
FMT="${2:-graphson}"
[[ "$FMT" =~ ^(graphson|proto-json)$ ]] || { echo "Unsupported format: $FMT"; exit 1; }

###############################################################################
# ─── PATHS – edit here if your folder layout changes ─────────────────────────
###############################################################################
BASE_CPG="./CPGs/normalized_devign_functions"
BASE_OUT="./Json_exports/normalized_devign_json"

###############################################################################
# ─── JOERN auto-detection ────────────────────────────────────────────────────
###############################################################################
JOERN_EXPORT="$(command -v joern-export || true)"
[[ -x "$JOERN_EXPORT" ]] || { echo "FATAL: joern-export not found in \$PATH" >&2; exit 1; }

###############################################################################
# ─── SPLIT-specific dirs ─────────────────────────────────────────────────────
###############################################################################
SRC_DIR="$BASE_CPG/$SPLIT"
OUT_DIR="$BASE_OUT/${SPLIT}_${FMT}"      # one folder per format per split

[[ -d "$SRC_DIR" ]] || { echo "FATAL: split dir not found: $SRC_DIR" >&2; exit 1; }
mkdir -p "$OUT_DIR/logs"
PAR=$(nproc)

###############################################################################
# ─── Colours / timestamp helper ──────────────────────────────────────────────
###############################################################################
if test -t 1; then
  GRN=$'\e[0;32m'; RED=$'\e[0;31m'; CYA=$'\e[0;36m'; NC=$'\e[0m'
else GRN=; RED=; CYA=; NC=; fi
ts(){ printf '%s %s\n' "$(date +'%H:%M:%S')" "$*"; }

###############################################################################
# ─── Banner ──────────────────────────────────────────────────────────────────
###############################################################################
ts "${CYA}Split        : $SPLIT${NC}"
ts "${CYA}Source CPGs  : $SRC_DIR${NC}"
ts "${CYA}Output dir   : $OUT_DIR${NC}"
ts "${CYA}Format       : $FMT${NC}"
ts "${CYA}joern-export : $(basename "$JOERN_EXPORT")${NC}"
ts "${CYA}Parallelism  : $PAR cores${NC}"
echo

###############################################################################
# ─── Worker: one CPG → one JSON folder ──────────────────────────────────────
###############################################################################
export JOERN_EXPORT OUT_DIR FMT GRN RED NC
process_one() {
  local bin="$1" id tmp dir log
  id="${bin##*/}"; id="${id%.cpg.bin}"
  tmp="$OUT_DIR/${id}.tmp"
  dir="$OUT_DIR/$id"
  log="$OUT_DIR/logs/$id.log"

  # skip if we already have a JSON
  [[ -f "$dir/export.json" ]] && { echo "✓ $id" >>"$log"; return; }

  rm -rf "$tmp" "$dir"

  "$JOERN_EXPORT" \
      --repr=all \
      --format="$FMT" \
      --out "$tmp" \
      "$bin" \
      -J-Xmx2G >>"$log" 2>&1 || { echo "${RED}✗ $id${NC}"; rm -rf "$tmp"; return; }

  # Normalise file name to export.json
  case "$FMT" in
    graphson)   mv "$tmp/$id.graphson"   "$tmp/export.json"   2>/dev/null || true ;;
    proto-json) mv "$tmp/$id.proto.json" "$tmp/export.json"   2>/dev/null || true ;;
  esac

  mv "$tmp" "$dir"            # atomic replace → avoids “already exists”
  echo "${GRN}✓  $id${NC}"
}
export -f process_one

###############################################################################
# ─── MAIN: launch workers in parallel ───────────────────────────────────────
###############################################################################
printf '%s\0' "$SRC_DIR"/*.cpg.bin | \
  xargs -0 -I{} -P"$PAR" bash -c 'process_one "$@"' _ {}

###############################################################################
# ─── SUMMARY ────────────────────────────────────────────────────────────────
###############################################################################
total=$(ls "$SRC_DIR"/*.cpg.bin | wc -l)
done=$(find "$OUT_DIR" -name export.json | wc -l)
ts "${GRN}Finished: $done / $total CPGs exported${NC}"
echo "JSON files are under: $OUT_DIR"


####  ./export_cpg_to_json.sh test          # GraphSON (compact)
##    ./export_cpg_to_json.sh test proto-json  # Loss-less protobuf-JSON
