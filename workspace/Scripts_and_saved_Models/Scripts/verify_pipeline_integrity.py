#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Pipeline Integrity Smoke Test.

Verifies that:
  • cpg_config.DEVIGN_ORDER
  • vocab_builder artifacts (devign_rel_vocab.json)
  • simple_extractor embedding SQLite DB

are synchronized and structurally consistent BEFORE running cache_manager.py.
"""

import sys
import json
import sqlite3
import argparse
from pathlib import Path


# ────────────────────────────────────────────────────────────
# Helpers: cpg_config loader
# ────────────────────────────────────────────────────────────
def load_cpg_config(scripts_path: Path):
    """
    Temporarily prepend `scripts_path` to sys.path and import cpg_config.

    Fails fast with an explanatory message if import fails.
    """
    scripts_path = str(scripts_path)
    sys.path.insert(0, scripts_path)
    try:
        import cpg_config  # type: ignore
        return cpg_config
    except ImportError as e:
        print(f"❌ Could not import cpg_config from {scripts_path}")
        print(f"   Error: {e}")
        sys.exit(1)
    finally:
        # Remove the path we just injected to avoid leaking into parent env
        try:
            sys.path.remove(scripts_path)
        except ValueError:
            pass


# ────────────────────────────────────────────────────────────
# 1) Vocab sync: devign_rel_vocab.json vs cpg_config.DEVIGN_ORDER
# ────────────────────────────────────────────────────────────
def verify_vocab_sync(vocab_dir: Path, cpg_config) -> bool:
    """
    Ensure that devign_rel_vocab.json:
      • Has exactly the same key set as cpg_config.DEVIGN_ORDER
      • Uses indices 0..N-1 in exactly that order
    """
    print("\n[1/2] Verifying Vocab Sync...")
    rel_vocab_path = vocab_dir / "devign_rel_vocab.json"

    if not rel_vocab_path.exists():
        print(f"❌ Missing devign_rel_vocab.json at {rel_vocab_path}")
        return False

    try:
        with rel_vocab_path.open("r", encoding="utf-8") as f:
            vocab = json.load(f)
    except Exception as e:
        print(f"❌ Failed to read {rel_vocab_path}: {e}")
        return False

    if not isinstance(vocab, dict):
        print(f"❌ devign_rel_vocab.json is not a JSON object (dict). Got: {type(vocab)}")
        return False

    vocab_keys = set(vocab.keys())
    config_keys = set(cpg_config.DEVIGN_ORDER)

    # Check 1: Set Equality
    if vocab_keys != config_keys:
        print("❌ Mismatch between JSON and cpg_config.DEVIGN_ORDER!")
        missing = config_keys - vocab_keys
        extra = vocab_keys - config_keys
        print(f"   Missing in JSON: {missing}" if missing else "   Missing in JSON: ∅")
        print(f"   Extra in JSON:   {extra}"   if extra else "   Extra in JSON:   ∅")
        return False

    # Check 2: Order / Index Equality (vocab[name] == idx)
    for idx, name in enumerate(cpg_config.DEVIGN_ORDER):
        if name not in vocab:
            print(f"❌ '{name}' missing from devign_rel_vocab.json (unexpected after set check).")
            return False
        if vocab[name] != idx:
            print(f"❌ Index mismatch for '{name}': Config={idx}, JSON={vocab[name]}")
            return False

    num_classes = len(cpg_config.DEVIGN_ORDER)
    print(f"✅ Vocab consistent with cpg_config (Devign, {num_classes} classes).")
    return True


# ────────────────────────────────────────────────────────────
# 2) Embedding DB integrity: dimension checks
# ────────────────────────────────────────────────────────────
def verify_embedding_integrity(db_path: Path) -> bool:
    """
    Verify that the embedding SQLite DB is internally consistent.

    Rules:
      • DB file must exist.
      • If an 'embeddings' table exists and has a 'dim' column, we read one row
        to infer `actual_dim`.
      • If an 'emb_config' table exists with key='dim', we read `conf_dim`.
      • If both are present, they must match.
      • If exactly one is present, we accept it as the dimension source.
      • If neither source exists, we treat this as a failure.
    """
    print("\n[2/2] Verifying Embedding DB Integrity...")
    if not db_path.exists():
        print(f"❌ DB not found: {db_path}")
        return False

    conn = None
    try:
        conn = sqlite3.connect(f"file:{db_path}?mode=ro", uri=True)
        cursor = conn.cursor()

        # -------------------------------
        # 1) Try to infer dim from 'embeddings'
        # -------------------------------
        actual_dim = None
        has_dim_col = False

        # Check that 'embeddings' table exists and inspect its columns
        try:
            cursor.execute("PRAGMA table_info(embeddings)")
            cols_info = cursor.fetchall()
            if cols_info:
                col_names = [r[1] for r in cols_info]  # r[1] is column name
                has_dim_col = ("dim" in col_names)
        except sqlite3.OperationalError:
            # 'embeddings' table may not exist at all in some legacy DBs
            cols_info = []

        if has_dim_col:
            try:
                cursor.execute("SELECT dim FROM embeddings LIMIT 1")
                row = cursor.fetchone()
                if not row:
                    print("⚠️  'embeddings' table is empty. Cannot verify dimension.")
                    # Empty DB is not considered an integrity failure; user may be mid-build.
                    return True
                actual_dim = int(row[0])
            except sqlite3.OperationalError as e:
                print(f"⚠️  Failed to read 'dim' from 'embeddings': {e}")

        # -------------------------------
        # 2) Try to read dim from emb_config
        # -------------------------------
        conf_dim = None
        try:
            cursor.execute("SELECT value FROM emb_config WHERE key='dim'")
            conf_row = cursor.fetchone()
            if conf_row is not None:
                # value is stored as TEXT; cast to int
                conf_dim = int(conf_row[0])
        except sqlite3.OperationalError:
            # 'emb_config' may not exist in older DBs
            conf_row = None

        # -------------------------------
        # 3) Consistency logic
        # -------------------------------
        if (actual_dim is not None) and (conf_dim is not None):
            # Both sources present: they MUST match
            if actual_dim != conf_dim:
                print(f"❌ INTEGRITY ERROR: Row dim ({actual_dim}) != Config dim ({conf_dim})")
                print("   This DB is likely corrupted or mixes different embedding models.")
                return False
            print(f"✅ Dimensions match: {actual_dim} (Source: embeddings.row & emb_config)")
            return True

        if (actual_dim is not None) and (conf_dim is None):
            # Only row-based source available
            print(f"⚠️  Dimensions: {actual_dim} (Source: embeddings row only - legacy DB, no emb_config)")
            return True

        if (actual_dim is None) and (conf_dim is not None):
            # Only config-based source available
            print(f"⚠️  Dimensions: {conf_dim} (Source: emb_config only - no 'dim' column on embeddings)")
            return True

        # If we reach here, we have neither row nor config dimension
        print("❌ Could not determine embedding dimension from DB.")
        print("   No 'dim' column in 'embeddings' and no 'dim' entry in 'emb_config'.")
        return False

    except Exception as e:
        print(f"❌ SQLite Error while checking {db_path}: {e}")
        return False
    finally:
        if conn is not None:
            conn.close()


# ────────────────────────────────────────────────────────────
# Main entry point
# ────────────────────────────────────────────────────────────
def main():
    parser = argparse.ArgumentParser(
        description="Pipeline Integrity Smoke Test: cpg_config + vocab_builder + embeddings DB",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "--vocab-dir",
        type=Path,
        required=True,
        help="Directory containing devign_rel_vocab.json (from vocab_builder.py).",
    )
    parser.add_argument(
        "--scripts-dir",
        type=Path,
        required=True,
        help="Directory where cpg_config.py lives (usually your Scripts dir).",
    )
    parser.add_argument(
        "--sqlite-db",
        type=Path,
        required=True,
        help="Path to the CodeBERT embeddings SQLite DB (from simple_extractor.py).",
    )
    args = parser.parse_args()

    print("=== PIPELINE INTEGRITY SMOKE TEST ===")

    # 1. Load Config
    cfg = load_cpg_config(args.scripts_dir)

    # 2. Verify Vocab
    vocab_ok = verify_vocab_sync(args.vocab_dir, cfg)

    # 3. Verify DB
    db_ok = verify_embedding_integrity(args.sqlite_db)

    if vocab_ok and db_ok:
        print("\n✅✅ SYSTEM READY FOR CACHE BUILD ✅✅")
        sys.exit(0)
    else:
        print("\n❌❌ SYSTEM INTEGRITY CHECK FAILED ❌❌")
        sys.exit(1)


if __name__ == "__main__":
    main()


"""
python verify_pipeline_integrity.py \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  --scripts-dir "./workspace/Scripts_and_saved_Models/Scripts" \
  --sqlite-db "./Clean_exports/cache_devign_v2/codebert_v2.sqlite"

"""