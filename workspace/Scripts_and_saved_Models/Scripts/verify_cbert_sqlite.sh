#!/usr/bin/env bash
set -Eeuo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 /path/to/codebert.sqlite [expected_dim=768] [probe_sha]"
  exit 2
fi

DB="$1"
EXPECTED_DIM="${2:-768}"
PROBE_SHA="${3:-}"

if ! command -v sqlite3 >/dev/null 2>&1; then
  echo "ERROR: sqlite3 CLI not found"; exit 127
fi
[[ -f "$DB" ]] || { echo "ERROR: DB not found: $DB"; exit 1; }

echo "== CodeBERT SQLite schema check =="
echo "DB: $DB"
echo "Expected embedding dim: $EXPECTED_DIM (bytes ≈ $((EXPECTED_DIM*4)))"

# helper: pipe-delimited output
q() { sqlite3 -noheader -separator '|' "$DB" "$1"; }

# 1) Table existence
HAS_EMB_TABLE="$(q "SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND lower(name)='embeddings';")"
if [[ "$HAS_EMB_TABLE" != "1" ]]; then
  echo "FAIL: table 'embeddings' not found."; sqlite3 "$DB" ".tables"; exit 1
fi
echo "OK: table 'embeddings' exists."

# 2) Columns
HAS_SHA256="$(q "SELECT COUNT(*) FROM pragma_table_info('embeddings') WHERE lower(name)='sha256';")"
HAS_VEC="$(q "SELECT COUNT(*) FROM pragma_table_info('embeddings') WHERE lower(name)='vec';")"
[[ "$HAS_SHA256" == "1" && "$HAS_VEC" == "1" ]] || {
  echo "FAIL: required columns 'sha256' and/or 'vec' missing."; sqlite3 "$DB" ".schema embeddings"; exit 1; }
echo "OK: required columns present: sha256, vec"

# 3) Row count + vector byte lengths (parse with '|' IFS)
IFS='|' read -r ROWS MINB AVGB MAXB <<<"$(q "SELECT COUNT(*), IFNULL(MIN(length(vec)),0), IFNULL(ROUND(AVG(length(vec)),2),0), IFNULL(MAX(length(vec)),0) FROM embeddings;")"
echo "Rows: $ROWS"
echo "vec length (bytes): min=$MINB avg=$AVGB max=$MAXB"

if (( ROWS > 0 )); then
  EXPECTED_BYTES=$((EXPECTED_DIM*4))
  # avg may be decimal → use Python to compute avg dim safely
  AVG_DIM=$(python3 - <<PY
try:
    print(int(round(float("$AVGB")/4.0)))
except Exception:
    print(0)
PY
)
  MIN_DIM=$(( MINB/4 ))
  MAX_DIM=$(( MAXB/4 ))
  echo "vec derived dims (≈bytes/4): min≈$MIN_DIM avg≈$AVG_DIM max≈$MAX_DIM"
  if (( MINB == EXPECTED_BYTES && MAXB == EXPECTED_BYTES )); then
    echo "OK: Vector sizes match expected ${EXPECTED_DIM} dims (${EXPECTED_BYTES} bytes)."
  else
    echo "WARN: Vector byte lengths differ from expected ${EXPECTED_BYTES}."
  fi
else
  echo "WARN: No rows in embeddings; cannot validate vector size."
fi

# 4) Cross-check the 'dim' column
IFS='|' read -r MIND DMAXD NDIST <<<"$(q "SELECT MIN(dim), MAX(dim), COUNT(DISTINCT dim) FROM embeddings;")"
echo "dim column: min=$MIND max=$DMAXD distinct=$NDIST"

# 5) Index on sha256 (account for PRIMARY KEY auto-index)
IDX_LIST="$(q "PRAGMA index_list('embeddings');")"
if [[ -z "$IDX_LIST" ]]; then
  echo "WARN: No index reported by PRAGMA (unexpected for a PRIMARY KEY)."
else
  IDX_NAMES="$(awk -F'|' '{print $2}' <<<"$IDX_LIST" | paste -sd, -)"
  echo "OK: Index(es) present: $IDX_NAMES"
fi

# 6) Optional probe
if [[ -n "$PROBE_SHA" ]]; then
  HITS="$(q "SELECT COUNT(*) FROM embeddings WHERE sha256='$PROBE_SHA';")"
  echo "Probe sha256=$PROBE_SHA → hits=$HITS"
fi

# 7) Sample rows
echo "Sample rows (sha256, length(vec)):"
sqlite3 "$DB" -noheader -separator '|' "SELECT sha256, length(vec) FROM embeddings LIMIT 5;"

# 8) Final schema echo (compact)
echo "Schema:"
sqlite3 "$DB" ".schema embeddings"

echo "== Done =="


#### ./verify_cbert_sqlite.sh "./Clean_exports/cache_devign/codebert_v2.sqlite"