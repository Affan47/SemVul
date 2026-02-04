#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

# ─── CONFIGURATION ────────────────────────────────────────────────────────────
JOERN_HOME="./external/joern-4.0.386/joern-cli"
FUNC_ROOT="./workspace/03_PerFunction_datasets/normalized_diversevul_functions"
CPG_ROOT="./CPGs/normalized_diversevul_functions"
HEAP_SIZE="4G"
PARALLEL_JOBS=$(nproc)
FRONTEND="joern-parse"
BLACKLIST_FILE="blacklist_ids.txt"

# ─── UTILITIES ────────────────────────────────────────────────────────────────
if test -t 1; then
    GRN=$'\e[0;32m'; RED=$'\e[0;31m'; YLW=$'\e[0;33m'; CYA=$'\e[0;36m'; NC=$'\e[0m'
else
    GRN=''; RED=''; YLW=''; CYA=''; NC=''
fi

timestamp() { printf '[%(%H:%M:%S)T] %s\n' -1 "$1"; }
die() { timestamp "${RED}FATAL: $1${NC}" >&2; exit 1; }

# ─── VALIDATION ───────────────────────────────────────────────────────────────
java -version 2>&1 | grep -qE 'version "(17|18|19|20|21)' || die "Java 17+ required"
[[ -f "$JOERN_HOME/$FRONTEND" ]] || die "Missing $FRONTEND in $JOERN_HOME"
[[ -d "$FUNC_ROOT" ]] || die "Missing functions directory: $FUNC_ROOT"

is_blacklisted() {
    [[ -f "$BLACKLIST_FILE" ]] && grep -qxF "$1" "$BLACKLIST_FILE"
}

is_valid_cpg() {
    unzip -l "$1" 2>/dev/null | grep -q '\.bin$'
}

# Process a single function
process_function() {
    local func_path="$1"
    local func_file
    func_file=$(basename "$func_path")
    local func_id="${func_file%.c}"
    local log_file="$CPG_ROOT/logs/$func_id.log"
    local output_zip="$CPG_ROOT/$func_id.cpg.bin.zip"
    local temp_output="$CPG_ROOT/temp_$func_id"

    mkdir -p "$(dirname "$log_file")" "$CPG_ROOT"

    if is_blacklisted "$func_id"; then
        timestamp "${YLW}Skipping blacklisted: $func_id${NC}" | tee -a "$log_file"
        return 0
    fi

    if [[ -f "$output_zip" ]] && is_valid_cpg "$output_zip"; then
        timestamp "${GRN}Found valid CPG: $func_id${NC}" | tee -a "$log_file"
        return 0
    fi

    rm -rf "$output_zip" "$temp_output"
    timestamp "${CYA}Processing: $func_id${NC}" | tee -a "$log_file"

    if "$JOERN_HOME/$FRONTEND" \
        --language=c \
        --output "$temp_output" \
        "$func_path" \
        -J-Xmx"$HEAP_SIZE" 2>&1 | tee -a "$log_file"
    then
        ls -lhR "$temp_output" 2>/dev/null | tee -a "$log_file"

        if [[ -f "$temp_output" ]]; then
            zip -qj "$output_zip" "$temp_output"
            timestamp "${GRN}Success: $func_id (zipped direct output file)${NC}" | tee -a "$log_file"
        elif [[ -d "$temp_output" ]]; then
            local cpg_file
            cpg_file=$(find "$temp_output" -type f -name '*.bin' -exec du -b {} + | sort -nr | head -n1 | cut -f2-)
            if [[ -f "$cpg_file" ]]; then
                zip -qj "$output_zip" "$cpg_file"
                timestamp "${GRN}Success: $func_id (zipped $(basename "$cpg_file"))${NC}" | tee -a "$log_file"
            else
                timestamp "${RED}No .bin generated: $func_id (no file in workspace)${NC}" | tee -a "$log_file"
                return 1
            fi
        else
            timestamp "${RED}No CPG generated: $func_id (no output file or directory)${NC}" | tee -a "$log_file"
            return 1
        fi
    else
        timestamp "${RED}Joern failed: $func_id${NC}" | tee -a "$log_file"
        return 1
    fi

    rm -rf "$temp_output"
}

# ─── MAIN EXECUTION ───────────────────────────────────────────────────────────
mkdir -p "$CPG_ROOT"
timestamp "${GRN}Starting CPG generation (no split mode)${NC}"
timestamp "Functions: $FUNC_ROOT"
timestamp "CPG Output: $CPG_ROOT"
timestamp "Parallel jobs: $PARALLEL_JOBS"
timestamp "Heap size per job: $HEAP_SIZE"
timestamp "Frontend: $FRONTEND"

overall_status=0

func_files=("$FUNC_ROOT"/*.c)
total_files=${#func_files[@]}
processed=0
failures=0

[[ $total_files -eq 0 ]] && {
    timestamp "${RED}No functions found in $FUNC_ROOT${NC}"
    exit 1
}

mkdir -p "$CPG_ROOT/logs"

for func_path in "${func_files[@]}"; do
    while [[ $(jobs -r -p | wc -l) -ge $PARALLEL_JOBS ]]; do sleep 0.5; done
    process_function "$func_path" &
done

wait

processed=$(find "$CPG_ROOT" -maxdepth 1 -name '*.cpg.bin.zip' 2>/dev/null | wc -l)
failures=$((total_files - processed))

if [[ $failures -eq 0 ]]; then
    timestamp "${GRN}CPG generation completed: $processed/$total_files${NC}"
else
    timestamp "${RED}Some CPGs failed! Failures: $failures${NC}"
    overall_status=1
fi

exit $overall_status


### ./03_batch_cpg.sh ###