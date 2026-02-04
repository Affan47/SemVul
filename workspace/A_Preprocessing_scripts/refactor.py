import os
import subprocess
import sys
import time
from concurrent.futures import ProcessPoolExecutor, as_completed

# --- Configuration ---
SINGLE_FILE = "./workspace/03_PerFunction_datasets/original_devign_functions/test/test_func_0000001.c"

SPLIT_DIRS = [
    "./workspace/03_PerFunction_datasets/original_devign_functions/train", 
    "./workspace/03_PerFunction_datasets/original_devign_functions/test", 
    "./workspace/03_PerFunction_datasets/original_devign_functions/validation"
]

# Strict formatting style
STYLE_CONFIG = "-style={BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 120, AlignConsecutiveAssignments: true, KeepEmptyLinesAtTheStartOfBlocks: false}"

def remove_blank_lines(file_path):
    """
    Reads the file and removes all lines that are empty or just whitespace.
    This effectively 'compacts' the code before formatting.
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        
        # Filter out lines that are just whitespace
        non_empty_lines = [line for line in lines if line.strip() != ""]
        
        with open(file_path, 'w', encoding='utf-8') as f:
            f.writelines(non_empty_lines)
        return True
    except Exception as e:
        print(f"[-] Error cleaning {file_path}: {e}")
        return False

def run_formatter(file_path):
    """
    Worker function to Clean AND Format a single file.
    """
    try:
        # Step 1: Remove all existing ugly blank lines
        if not remove_blank_lines(file_path):
            return False

        # Step 2: Apply clang-format to add back *correct* spacing
        cmd = ["clang-format", "-i", STYLE_CONFIG, file_path]
        subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        return True
    except Exception:
        return False

def get_all_c_files(folders):
    """
    Scans folders and returns a list of all .c files.
    """
    c_files = []
    print("[*] Scanning directories for files...")
    for folder in folders:
        if not os.path.exists(folder):
            print(f"[-] Directory '{folder}' not found. Skipping.")
            continue
            
        for root, dirs, files in os.walk(folder):
            for file in files:
                if file.endswith(".c"):
                    c_files.append(os.path.join(root, file))
    return c_files

def process_in_parallel(all_files):
    """
    Uses all CPU cores to process files simultaneously.
    """
    total_files = len(all_files)
    print(f"[*] Found {total_files} files. Starting parallel processing...")
    
    max_workers = os.cpu_count() or 4
    print(f"[*] Using {max_workers} CPU cores.")

    processed_count = 0
    start_time = time.time()

    with ProcessPoolExecutor(max_workers=max_workers) as executor:
        futures = {executor.submit(run_formatter, f): f for f in all_files}
        
        for future in as_completed(futures):
            processed_count += 1
            if processed_count % 100 == 0:
                elapsed = time.time() - start_time
                print(f"    Progress: {processed_count}/{total_files} files cleaned... ({elapsed:.2f}s)")

    print(f"\n[+] Processing Complete! {processed_count} files processed.")

def main():
    # 1. Check the single file first
    print(f"--- Checking Single File: {SINGLE_FILE} ---")
    if os.path.exists(SINGLE_FILE):
        success = run_formatter(SINGLE_FILE)
        if success:
            print("[+] Single file check passed.")
        else:
            print("[!] Single file check failed.")
            return
    else:
        print(f"[-] Test file not found: {SINGLE_FILE}")
    
    # 2. Gather all files
    all_files = get_all_c_files(SPLIT_DIRS)
    
    if not all_files:
        print("[-] No files found to process.")
        return

    # 3. Process
    process_in_parallel(all_files)

if __name__ == "__main__":
    main()