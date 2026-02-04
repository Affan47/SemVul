#!/usr/bin/env bash
# 03_batch_cpg_devign.sh  – regenerate per-function CPGs with Joern 4.x
set -euo pipefail
shopt -s nullglob

# ── JOERN auto-detection ────────────────────────────────────────────────────
JOERN="$(command -v joern || true)"
[[ -x "$JOERN" ]] || { echo "FATAL: joern launcher not found in \$PATH" >&2; exit 1; }
JOERN_DIR="$(dirname "$JOERN")"
JOERN_PARSE="$(command -v joern-parse || true)"
[[ -x "$JOERN_PARSE" ]] || JOERN_PARSE="$JOERN_DIR/joern-parse"
[[ -x "$JOERN_PARSE" ]] || { echo "FATAL: joern-parse not found" >&2; exit 1; }

# ── DATASET roots ───────────────────────────────────────────────────────────
BASE_FUNCS="./workspace/03_PerFunction_datasets/normalized_devign_functions"
BASE_CPGS="./CPGs/normalized_devign_functions"

# ── optional split argument ────────────────────────────────────────────────
SPLIT="${1:-all}"
case "$SPLIT" in
  train|valid|test)  FUNC_ROOT="$BASE_FUNCS/$SPLIT"; CPG_ROOT="$BASE_CPGS/$SPLIT" ;;
  all)               FUNC_ROOT="$BASE_FUNCS";         CPG_ROOT="$BASE_CPGS"        ;;
  *) echo "Usage: $0 [train|valid|test|all]" >&2; exit 1 ;;
esac

# ── runtime config ─────────────────────────────────────────────────────────
HEAP="4G"; PAR=$(nproc); BLACK="blacklist_ids.txt"

# ── colours & helpers ──────────────────────────────────────────────────────
if test -t 1; then
  GRN=$'\e[0;32m'; RED=$'\e[0;31m'; YLW=$'\e[0;33m'; CYA=$'\e[0;36m'; NC=$'\e[0m'
else GRN=; RED=; YLW=; CYA=; NC=; fi
ts(){ printf '[%(%H:%M:%S)T] %s\n' -1 "$*"; }
die(){ ts "${RED}FATAL: $*${NC}"; exit 1; }
is_black(){ [[ -f "$BLACK" ]] && grep -qxF "$1" "$BLACK"; }

# ── pre-flight checks ──────────────────────────────────────────────────────
java -version 2>&1 | grep -qE 'version "(17|18|19|20|21)' || die "Java 17+ required"
[[ -d "$FUNC_ROOT" ]] || die "Functions dir missing: $FUNC_ROOT"
mkdir -p "$CPG_ROOT/logs"

# ── parse one function ─────────────────────────────────────────────────────
parse_func() {
  local src="$1"; local id="${src##*/}"; id="${id%.c}"
  local log="$CPG_ROOT/logs/$id.log"
  local out="$CPG_ROOT/$id.cpg.bin"
  local scratch="$CPG_ROOT/tmp_$id"

  if is_black "$id"; then ts "${YLW}Skip $id${NC}"; return; fi
  [[ -f "$out" ]] && { ts "${GRN}OK  $id${NC}"; return; }

  rm -rf "$out" "$scratch"
  ts "${CYA}Parsing $id${NC}"

  if "$JOERN_PARSE" "$src" --language c --output "$scratch" -J-Xmx"$HEAP" >>"$log" 2>&1; then
      local cpg_file

      # Case A – joern-parse wrote a single file (default in Joern 4)
      [[ -f "$scratch" ]] && cpg_file="$scratch"

      # Case B – joern-parse produced a dir: pick first *.cpg.bin or *.bin
      [[ -z ${cpg_file:-} && -d $scratch ]] && \
          cpg_file=$(find "$scratch" -type f \( -name '*.cpg.bin' -o -name '*.bin' \) | head -n1)

      if [[ -f "$cpg_file" ]]; then
          mv "$cpg_file" "$out"
          ts "${GRN}✓  $id${NC}"
      else
          ts "${RED}No CPG file for $id${NC}"
      fi
  else
      ts "${RED}joern-parse failed $id${NC}"
  fi
  rm -rf "$scratch"
}

# ── main parallel loop ─────────────────────────────────────────────────────
ts "${GRN}CPG rebuild – split: $SPLIT${NC}"
mapfile -t FILES < <(find "$FUNC_ROOT" -type f -name '*.c')
total=${#FILES[@]} ; (( total==0 )) && die "No .c files found."

for f in "${FILES[@]}"; do
  while [[ $(jobs -rp | wc -l) -ge $PAR ]]; do sleep 0.15; done
  parse_func "$f" &
done
wait

done_cnt=$(find "$CPG_ROOT" -maxdepth 1 -name '*.cpg.bin' | wc -l)
[[ $done_cnt -eq $total ]] && ts "${GRN}All $done_cnt/$total CPGs ready${NC}" \
                           || ts "${RED}$((total-done_cnt)) failures${NC}"
