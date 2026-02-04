"""
MPTCN_TTS_Draper.py
SOTA-style, mutant-aware single-file runner for Draper graphs with robust CLI and training stages.

What's new vs. the base runner:
- Family-aware training: treat each function and its mutants as a "family".
- Loss stack (all optional / tunable):
  * Base CE/Focal (with label smoothing)
  * Symmetric Cross-Entropy (SCE) after warmup (robust to noise)
  * In-family Consistency (same-label mutant pairs → similar logits)
  * Supervised Contrastive over graph embeddings (labels + family as positives)
  * Prototype (EMA class centroids) regularizer on embeddings
  * Optional Delta Head: pairwise "same label" predictor over embedding deltas
- Test-time augmentation (dropedge/feature-noise) for robust ensembling
- Devign-style layout (vocab/checkpoints/results) + coverage audits
- PNA degree-hist caching

Assumptions
- Mutants of benign remain benign; mutants of vulnerable remain vulnerable.
- If manifest lacks family metadata, family_id is inferred from path like train_func_XXXXXXXX.
- If manifest includes 'p_eq' (probability label preserved), it scales the consistency/delta signal (defaults to 1.0).

Manifest columns (flexible):
- Required: index, label, json_path
- Optional: family_id, mutation_type, p_eq
"""

import os, sys, csv, json, math, random, argparse, re
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
# Add this at the top of the file containing GraphZipCache
import time
import numpy as np
from tqdm.auto import tqdm
import pickle, hashlib

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset
from torch.cuda.amp import autocast, GradScaler

# PyG
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader as GeoDataLoader
from torch_geometric.nn import (
    GCNConv, SAGEConv, GATConv, GINConv, PNAConv, RGCNConv,
    global_add_pool, global_mean_pool, global_max_pool, BatchNorm
)

# Optional DeepGCN (GENConv)
try:
    from torch_geometric.nn import DeepGCNLayer, GENConv
    HAS_DEEP = True
except Exception:
    HAS_DEEP = False

# Optional NNConv (MPNN)
try:
    from torch_geometric.nn import NNConv
    HAS_NNCONV = True
except Exception:
    HAS_NNCONV = False

# Metrics + plotting
from sklearn.metrics import accuracy_score, precision_recall_fscore_support, roc_auc_score, confusion_matrix
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt



# ────────────────────────────────────────────
# Parse stats (fast vs slow fallback) — process-local counters
# ────────────────────────────────────────────
from threading import Lock

_PARSE_STATS = {
    "fast_ok": 0,              # fast path used, no fallback
    "slow_fallback": 0,        # slow discovery used (fast had 0 edges or missed endpoints and slow was better)
    "fast_miss_but_equal": 0,  # fast had missed endpoints, slow not strictly better; kept fast
    "empty_edges": 0,          # final build ended with 0 edges (only in relaxed mode)
    "graphs": 0,               # total graphs parsed in this process
}
_PARSE_STATS_LOCK = Lock()

# How often to print [ParseStats] (set via env var if desired)
_PARSE_STATS_EVERY = int(os.environ.get("PARSE_STATS_EVERY", "2000"))



# ────────────────────────────────────────────
# Repro
# ────────────────────────────────────────────
def set_seed(seed: int = 42):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)


# ────────────────────────────────────────────
# tqdm helper
# ────────────────────────────────────────────
def _tqdm(iterable, desc, disable=True, total=None):
    return tqdm(iterable, desc=desc, total=total, leave=False, dynamic_ncols=True, disable=disable)


# ────────────────────────────────────────────
# Cache helpers (generic)
# ────────────────────────────────────────────
def _ensure_cache_dir(args):
    # Default near your JSON export directory:
    root = getattr(args, 'train_json_root', None) or getattr(args, 'json_root', None) or "."
    cache_dir = args.cache_dir or os.path.abspath(os.path.join(root, "..", "cache_draper"))
    os.makedirs(cache_dir, exist_ok=True)
    return cache_dir

def _cache_path(args, name, sig=None):
    cache_dir = _ensure_cache_dir(args)
    fname = f"{name}.pkl" if sig is None else f"{name}-{sig}.pkl"
    return os.path.join(cache_dir, fname)

def _manifest_signature(paths):
    h = hashlib.md5()
    for p in sorted(filter(None, paths)):
        h.update(os.path.basename(p).encode('utf-8', errors='ignore'))
        try:
            h.update(str(os.path.getmtime(p)).encode())
            h.update(str(os.path.getsize(p)).encode())
        except OSError:
            pass
    return h.hexdigest()[:10]



# ────────────────────────────────────────────
# Fast JSON loader shim (tries orjson, safe fallback to stdlib json)
# ────────────────────────────────────────────
# ---- fast JSON loader (orjson if available) ----
try:
    import orjson as _orjson
    def _fast_json_load_bytes(b: bytes):
        return _orjson.loads(b)
except Exception:
    _orjson = None
    def _fast_json_load_bytes(b: bytes):
        import json as _json
        return _json.loads(b.decode("utf-8"))






# ────────────────────────────────────────────
# Single-file ZIP cache for parsed graphs
# ────────────────────────────────────────────
import threading, os, zipfile
from pathlib import Path

import logging
import hashlib
import pickle

logger = logging.getLogger(__name__)

class GraphZipCache:
    """
    Single-file cache implementation for pre-parsed PyTorch Geometric Data objects.
    
    This version handles the case where the cache file doesn't exist yet (new cache).
    """
    def __init__(self, zip_path: Path, cache_version: str = "v2"):
        """
        Initialize the cache with a specific version.
        
        Args:
            zip_path: Path to the ZIP file where cache entries will be stored
            cache_version: Version identifier to ensure cache invalidation
        """
        self.zip_path = Path(zip_path)
        self.zip_path.parent.mkdir(parents=True, exist_ok=True)
        self.cache_version = cache_version
        self._names = None  # Set of cached member names, loaded lazily
        self._lock = threading.Lock()  # Ensures thread safety for index and writes
        self._last_modified = None
        self._index_load_time = 0
        self._max_index_age = 30  # seconds before refreshing index
        
        # Only validate if the cache file already exists
        if self.zip_path.exists():
            self._validate_cache_integrity()
        else:
            # Initialize with empty index for new cache
            self._names = set()
            logger.info(f"Created new cache at {self.zip_path}")
    
    def _validate_cache_integrity(self) -> bool:
        """Verify that the cache ZIP file is not corrupted and has the correct version."""
        try:
            with zipfile.ZipFile(self.zip_path, mode="r") as zf:
                # Check for version marker
                if "cache_version.txt" in zf.namelist():
                    version = zf.read("cache_version.txt").decode().strip()
                    if version != self.cache_version:
                        logger.warning(f"Cache version mismatch: found {version}, expected {self.cache_version}")
                        return False
                
                # Quick check for index validity
                if "index_valid.txt" in zf.namelist():
                    index_valid = zf.read("index_valid.txt").decode().strip()
                    if index_valid != "1":
                        logger.warning("Cache index marked as invalid")
                        return False
                        
                return True
        except Exception as e:
            logger.error(f"Cache validation failed: {e}")
            return False

    def _refresh_index(self):
        """Force a full index refresh, but handle case where cache file doesn't exist."""
        try:
            # Only refresh if the cache file exists
            if not self.zip_path.exists():
                self._names = set()
                return
                
            with zipfile.ZipFile(self.zip_path, mode="r") as zf:
                # Get all entries except metadata
                self._names = set(name for name in zf.namelist() 
                                if name not in ["cache_version.txt", "index_valid.txt"])
            logger.debug(f"Refreshed cache index with {len(self._names)} entries")
        except Exception as e:
            logger.error(f"Failed to refresh cache index: {e}")
            self._names = set()

    def _ensure_index(self, force_refresh: bool = False):
        """Lazily load the list of cached names from the ZIP file."""
        with self._lock:
            current_time = time.time()
            
            # Force refresh if cache is new or index is too old
            if force_refresh or self._names is None or (current_time - self._index_load_time) > self._max_index_age:
                self._refresh_index()
                self._index_load_time = current_time
                return

            # Check if cache file has been modified externally
            try:
                current_mtime = self.zip_path.stat().st_mtime
                if self._last_modified is None or current_mtime != self._last_modified:
                    self._refresh_index()
                    self._last_modified = current_mtime
            except Exception:
                pass

    def contains(self, name: str) -> bool:
        """Check if an entry exists in the cache."""
        self._ensure_index()
        exists = name in self._names
        logger.debug(f"Cache contains '{name}': {exists}")
        return exists

    def load(self, name: str) -> Optional[bytes]:
        """Load raw bytes for a given name from the cache, or return None."""
        self._ensure_index()
        if name not in self._names:
            logger.debug(f"Entry '{name}' not found in cache")
            return None

        try:
            with zipfile.ZipFile(self.zip_path, mode="r") as zf:
                with zf.open(name, mode="r") as fh:
                    return fh.read()
        except Exception as e:
            logger.error(f"Failed to load entry '{name}' from cache: {e}")
            return None

    def store(self, name: str, raw_bytes: bytes) -> bool:
        """
        Store raw bytes into the cache.
        Thread-safe: Uses a lock to prevent concurrent writes and index updates.
        Returns True on success, False otherwise.
        """
        with self._lock:
            try:
                # Ensure we have the latest index
                self._ensure_index(force_refresh=True)
                
                # Check if entry already exists
                if name in self._names:
                    logger.debug(f"Entry '{name}' already exists in cache, skipping write")
                    return True
                
                # Write to cache
                with zipfile.ZipFile(self.zip_path, mode="a", compression=zipfile.ZIP_DEFLATED, allowZip64=True) as zf:
                    zf.writestr(name, raw_bytes)
                
                # Update local index
                self._names.add(name)
                logger.debug(f"Successfully stored entry '{name}' to cache")
                
                # Update cache metadata
                try:
                    with zipfile.ZipFile(self.zip_path, mode="a") as zf:
                        zf.writestr("index_valid.txt", "1")
                        zf.writestr("cache_version.txt", self.cache_version)
                except Exception:
                    pass
                
                return True
            except Exception as e:
                logger.error(f"Failed to store entry '{name}' to cache: {e}")
                return False



    def clean_cache(self, max_age_days: int = 30) -> int:
        """
        Clean up old cache entries based on modification time.
        
        Args:
            max_age_days: Maximum age of cache entries in days
        
        Returns:
            Number of entries removed
        """
        removed = 0
        cutoff = time.time() - (max_age_days * 24 * 3600)
        
        with self._lock:
            try:
                # First get all entries with their modification times
                entries = []
                with zipfile.ZipFile(self.zip_path, "r") as zf:
                    for name in zf.namelist():
                        if name in ["cache_version.txt", "index_valid.txt"]:
                            continue
                        try:
                            info = zf.getinfo(name)
                            entries.append((name, info.date_time))
                        except Exception:
                            continue
                
                # Convert date_time to timestamp
                entries = [(name, time.mktime(datetime(*dt).timetuple())) for name, dt in entries]
                
                # Filter entries to keep
                to_keep = [name for name, mtime in entries if mtime > cutoff]
                to_remove = [name for name, mtime in entries if mtime <= cutoff]
                
                # Create a new ZIP without the old entries
                if to_remove:
                    temp_path = self.zip_path.with_suffix(".tmp")
                    with zipfile.ZipFile(self.zip_path, "r") as zf_in, \
                         zipfile.ZipFile(temp_path, "w", compression=zipfile.ZIP_DEFLATED) as zf_out:
                        
                        # Copy entries to keep
                        for name in to_keep:
                            zf_out.writestr(name, zf_in.read(name))
                        
                        # Copy metadata
                        for meta_name in ["cache_version.txt", "index_valid.txt"]:
                            if meta_name in zf_in.namelist():
                                zf_out.writestr(meta_name, zf_in.read(meta_name))
                    
                    # Replace original with cleaned version
                    self.zip_path.unlink()
                    temp_path.rename(self.zip_path)
                    removed = len(to_remove)
                    logger.info(f"Cleaned {removed} old cache entries")
                
                # Refresh index
                self._refresh_index()
                
            except Exception as e:
                logger.error(f"Cache cleanup failed: {e}")
            
            return removed

# ────────────────────────────────────────────

# ────────────────────────────────────────────
# Sharded ZIP cache (N shards) to avoid single-writer I/O bottleneck
# ────────────────────────────────────────────

logger = logging.getLogger(__name__)

class GraphShardedCache:
    """
    Shards the cache into N zip files under a shards dir (optionally a RAM tmpdir):
        <shards_dir>/graph_cache-000.zip, ..., graph_cache-(N-1).zip

    Deterministic shard = md5(member_name) % N.
    Public API matches GraphZipCache: contains(name), load(name), store(name).
    Also exposes:
        - shard_paths(): list[Path] of shard zip files
        - merge_to(target_zip: Path, delete_after: bool=True): merge shards into one and optionally delete shards
    """
    def __init__(self, shards_dir: Path, num_shards: int, base_zip: Optional[Path] = None):
        self.shards_dir = Path(shards_dir)
        self.shards_dir.mkdir(parents=True, exist_ok=True)
        self.num_shards = int(max(1, num_shards))
        self.base_zip = Path(base_zip) if base_zip is not None else None
        # Dictionary to hold shard-specific locks and indexes
        self._locks = {i: threading.Lock() for i in range(self.num_shards)}
        self._idx: dict[int, Set[str]] = {}  # sid -> set(member_names)
        self._paths = [self.shards_dir / f"graph_cache-{i:03d}.zip" for i in range(self.num_shards)]

    @staticmethod
    def _shard_id(name: str, n: int) -> int:
        h = hashlib.md5(name.encode("utf-8", errors="ignore")).digest()
        return int.from_bytes(h[:4], "little") % n

    def shard_paths(self) -> List[Path]:
        return list(self._paths)

    def _ensure_idx(self, sid: int):
        """Lazily load the index for a specific shard, thread-safe."""
        if sid in self._idx:
            return
        p = self._paths[sid]
        names = set()
        if p.exists():
            try:
                with zipfile.ZipFile(p, mode="r") as zf:
                    names.update(zf.namelist())
                logger.debug(f"Loaded index for shard {sid} ({p}) with {len(names)} entries.")
            except Exception as e:
                logger.error(f"Failed to load index for shard {sid} ({p}): {e}. Initializing empty index.")
                names = set()
        self._idx[sid] = names

    def contains(self, name: str) -> bool:
        """Check if an entry exists in the correct shard."""
        sid = self._shard_id(name, self.num_shards)
        # Use the shard-specific lock for index loading
        with self._locks[sid]:
            self._ensure_idx(sid)
            exists = name in self._idx[sid]
        logger.debug(f"Checked existence of '{name}' (shard {sid}): {exists}")
        return exists

    def load(self, name: str):
        """Load raw bytes for a given name from the correct shard, or return None."""
        sid = self._shard_id(name, self.num_shards)
        # Use the shard-specific lock for index loading
        with self._locks[sid]:
            self._ensure_idx(sid)
            if name not in self._idx[sid]:
                logger.debug(f"Entry '{name}' (shard {sid}) not found in cache.")
                return None

        p = self._paths[sid]
        try:
            with zipfile.ZipFile(p, mode="r") as zf:
                with zf.open(name, mode="r") as fh:
                    data = fh.read()
            logger.debug(f"Successfully loaded entry '{name}' (shard {sid}) from cache.")
            return data
        except Exception as e:
            logger.error(f"Failed to load entry '{name}' (shard {sid}) from {p}: {e}")
            return None

    def store(self, name: str, raw_bytes: bytes) -> bool:
        """
        Store raw bytes into the correct shard.
        Thread-safe for the specific shard.
        Returns True on success, False otherwise.
        """
        sid = self._shard_id(name, self.num_shards)
        # Use the shard-specific lock for writing and index update
        with self._locks[sid]:
            self._ensure_idx(sid)
            if name in self._idx[sid]:
                logger.debug(f"Entry '{name}' (shard {sid}) already exists in cache, skipping write.")
                return True

            p = self._paths[sid]
            try:
                with zipfile.ZipFile(p, mode="a", compression=zipfile.ZIP_STORED, allowZip64=True) as zf:
                    zf.writestr(name, raw_bytes)
                self._idx[sid].add(name) # Update local index for this shard
                logger.debug(f"Successfully stored entry '{name}' (shard {sid}) to cache.")
                return True
            except Exception as e:
                logger.error(f"Failed to store entry '{name}' (shard {sid}) to {p}: {e}")
                return False

    def merge_to(self, target_zip: Path, delete_after: bool = True):
        """
        Merge all shards into one monolithic zip (dedup by name).
        If delete_after=True, delete shard files after successful merge.
        """
        target_zip = Path(target_zip)
        target_zip.parent.mkdir(parents=True, exist_ok=True)
        names = set()
        logger.info(f"[Cache][MERGE] merging {len(self._paths)} shards into {target_zip}")
        
        try:
            with zipfile.ZipFile(target_zip, mode="w", compression=zipfile.ZIP_STORED, allowZip64=True) as outzf:
                for i, p in enumerate(self._paths):
                    if not p.exists():
                        logger.debug(f"Shard {p} does not exist, skipping.")
                        continue
                    try:
                        with zipfile.ZipFile(p, mode="r") as inzf:
                            for nm in inzf.namelist():
                                if nm in names:
                                    logger.warning(f"Duplicate entry '{nm}' found during merge, skipping.")
                                    continue
                                outzf.writestr(nm, inzf.read(nm))
                                names.add(nm)
                    except Exception as e:
                        logger.error(f"[Cache][MERGE][WARN] skip shard {p}: {e}")
                        continue
        except Exception as e:
            logger.error(f"[Cache][MERGE] Failed to create target zip {target_zip}: {e}")
            return # Do not proceed with cleanup if merge failed

        logger.info(f"[Cache][MERGE] done; {len(names)} entries written")

        if delete_after:
            for p in self._paths:
                try:
                    if p.exists():
                        p.unlink()
                        logger.info(f"[Cache][CLEANUP] removed shard {p}")
                except Exception as e:
                    logger.error(f"[Cache][CLEANUP][WARN] failed to remove {p}: {e}")




def load_or_build_cached(args, name, builder_fn, sig=None):
    path = _cache_path(args, name, sig)
    if (not args.cache_overwrite) and os.path.exists(path):
        with open(path, 'rb') as f:
            return pickle.load(f)
    obj = builder_fn()
    with open(path, 'wb') as f:
        pickle.dump(obj, f, protocol=pickle.HIGHEST_PROTOCOL)
    return obj


def _maybe_load_pna_deg_hist(layout):
    """Try to load a cached PNA degree histogram from vocab dir; return Tensor or None."""
    fp = layout["vocab"] / "pna_deg_hist.pkl"
    try:
        with open(fp, "rb") as f:
            obj = pickle.load(f)
        if isinstance(obj, np.ndarray):
            obj = torch.from_numpy(obj).float()
        elif not torch.is_tensor(obj):
            obj = torch.tensor(obj, dtype=torch.float)
        print(f"[PNA] Loaded cached degree histogram from {fp} (len={int(obj.numel())})")
        return obj
    except Exception:
        return None


def compute_pna_degree_hist_from_loader(loader, max_degree: int = 512, args=None):
    hist = torch.zeros(max_degree + 1, dtype=torch.float)
    disable = getattr(args, 'no_progress', False)
    for batch in _tqdm(loader, desc="PNA deg-hist (train)", disable=disable, total=len(loader)):
        ei = batch.edge_index
        num_nodes = int(batch.num_nodes)
        deg_src = torch.bincount(ei[0], minlength=num_nodes)
        deg_dst = torch.bincount(ei[1], minlength=num_nodes)
        deg = (deg_src + deg_dst).clamp_max(max_degree).long()  # undirected degree
        hist.scatter_add_(0, deg, torch.ones_like(deg, dtype=torch.float))
    hist[hist == 0] = 1.0
    return hist


# ────────────────────────────────────────────
# Devign-style layout (model[/spatial])
# ────────────────────────────────────────────
def _get_devign_layout(args):
    """
    Directories:
      <script_dir>/MPTCN_TTS_devign/<model>/<spatial>/{checkpoints,results,vocab}
    Falls back to:
      <script_dir>/MPTCN_TTS_devign/<model>/{checkpoints,results,vocab}
    when --spatial is not provided.
    """
    root = Path(__file__).resolve().parent
    model_name = str(getattr(args, "model", "model")).lower()

    # Use spatial subdir only if present (e.g., rgcn / hgt / cheb / gcn / gat / sage)
    spatial_name = getattr(args, "spatial", None)
    spatial_name = str(spatial_name).lower() if spatial_name else None
    spatial_name = re.sub(r"[^a-z0-9_\-]+", "", spatial_name) if spatial_name else None  # sanitize

    if spatial_name:
        model_dir = root / "MPTCN_TTS_devign" / model_name / spatial_name
    else:
        model_dir = root / "MPTCN_TTS_devign" / model_name

    vocabs_dir  = model_dir / "vocab"
    ckpt_dir    = model_dir / "checkpoints"
    results_dir = model_dir / "results"

    for d in (vocabs_dir, ckpt_dir, results_dir):
        d.mkdir(parents=True, exist_ok=True)

    return {
        "model_dir": model_dir,
        "vocab": vocabs_dir,
        "checkpoints": ckpt_dir,
        "results": results_dir,
    }


# ────────────────────────────────────────────
# GraphSON parsing
# ────────────────────────────────────────────
def _safe_int_map(ids: List[Any]) -> Dict[Any, int]:
    return {k: i for i, k in enumerate(ids)}

import json, sys, math, numpy as np
from collections import Counter
import torch
from torch_geometric.data import Data

# -------------------------------------------------------------------
# Helpers for dynamic GraphSON discovery
# -------------------------------------------------------------------

_NODE_LABEL_KEYS = ("label", "type", "kind", "nodeLabel")
_EDGE_LABEL_KEYS = ("label", "edgeLabel", "type", "kind", "rel")
_ENDPOINT_KEYS   = (
    ("src", "dst"),
    ("u", "v"),
    ("in", "out"),
    ("inV", "outV"),
    ("head", "tail"),
)

def _unwrap_list(x):
    """Unwraps TinkerPop style { '@type':'g:List', '@value': [...] }"""
    if isinstance(x, dict) and "@type" in x and "@value" in x and isinstance(x["@value"], list):
        return x["@value"]
    return x

def _maybe_dict_get(d, dotted):
    """Get nested value by dotted path like 'properties.label'."""
    cur = d
    for k in dotted.split("."):
        if not isinstance(cur, dict) or k not in cur:
            return None
        cur = cur[k]
    return cur

def _best_label_value(obj, label_keys):
    """Try several keys (and properties.label) to extract a label string."""
    for k in label_keys:
        if "." in k:
            v = _maybe_dict_get(obj, k)
        else:
            v = obj.get(k)
        if v is not None and v != "":
            return str(v)
    # Common nested variant
    v = _maybe_dict_get(obj, "properties.label")
    if v not in (None, ""):
        return str(v)
    return None

def _walk_lists(root):
    """Yield all lists found in nested dicts/lists, unwrapped if needed."""
    stack = [root]
    while stack:
        cur = stack.pop()
        if isinstance(cur, dict):
            # unwrap GraphSON style lists first to avoid missing them
            maybe_list = _unwrap_list(cur)
            if maybe_list is not cur:
                stack.append(maybe_list)
            for v in cur.values():
                stack.append(v)
        elif isinstance(cur, list):
            yield _unwrap_list(cur)
            for v in cur:
                stack.append(v)

def _score_node_list(cand_list, node_vocab):
    """
    FAST: set membership + early checks.
    Returns (coverage_score, best_label_key, labels_list) exactly like before.
    """
    if not isinstance(cand_list, list) or not cand_list:
        return 0.0, None, None

    # Quick reject: first few must be dicts (avoids full pass)
    upto = min(8, len(cand_list))
    for i in range(upto):
        if not isinstance(cand_list[i], dict):
            return 0.0, None, None

    vocab_set = set(node_vocab.keys()) if node_vocab else set()
    label_keys_try = _NODE_LABEL_KEYS + ("properties.label",)

    best_cov = 0.0
    best_key = None
    labels = None

    for lk in label_keys_try:
        cnt = 0
        tmp = []
        if vocab_set:
            for d in cand_list:
                lab = _best_label_value(d, (lk,))
                if lab:
                    tmp.append(lab)
                    if lab in vocab_set:
                        cnt += 1
            cov = cnt / float(len(cand_list))
        else:
            # No vocab: treat presence of *any* label as coverage
            for d in cand_list:
                lab = _best_label_value(d, (lk,))
                if lab:
                    tmp.append(lab)
                    cnt += 1
            cov = cnt / float(len(cand_list))
        if cov > best_cov:
            best_cov = cov
            best_key = lk
            labels = tmp

    return best_cov, best_key, labels

def _score_edge_list(cand_list, edge_vocab):
    """
    FAST: one pass per candidate key set with set membership.
    Returns (score, best_end_pair, best_label_key, None) like before.
    """
    if not isinstance(cand_list, list) or not cand_list:
        return 0.0, None, None, None

    upto = min(8, len(cand_list))
    for i in range(upto):
        if not isinstance(cand_list[i], dict):
            return 0.0, None, None, None

    vocab_set = set(edge_vocab.keys()) if edge_vocab else set()

    # Endpoint detection (coverage by key pair)
    best_end_pair, end_cov = None, 0.0
    for a, b in _ENDPOINT_KEYS:
        cnt = 0
        for d in cand_list:
            has_a = (a in d) or (_maybe_dict_get(d, a) is not None)
            if not has_a:
                continue
            has_b = (b in d) or (_maybe_dict_get(d, b) is not None)
            if has_b:
                cnt += 1
        cov = cnt / float(len(cand_list))
        if cov > end_cov:
            end_cov, best_end_pair = cov, (a, b)

    if best_end_pair is None:
        return 0.0, None, None, None

    # Label key detection (coverage by label membership)
    best_label_key, lab_cov = None, 0.0
    label_keys_try = _EDGE_LABEL_KEYS + ("properties.label",)

    if vocab_set:
        for lk in label_keys_try:
            cnt = 0
            for d in cand_list:
                lab = _best_label_value(d, (lk,))
                if lab and (lab in vocab_set):
                    cnt += 1
            cov = cnt / float(len(cand_list))
            if cov > lab_cov:
                lab_cov, best_label_key = cov, lk
    else:
        # No vocab: treat presence of any label as coverage
        for lk in label_keys_try:
            cnt = 0
            for d in cand_list:
                lab = _best_label_value(d, (lk,))
                if lab:
                    cnt += 1
            cov = cnt / float(len(cand_list))
            if cov > lab_cov:
                lab_cov, best_label_key = cov, lk

    if best_label_key is None:
        return 0.0, None, None, None

    score = math.sqrt(max(end_cov, 1e-9) * max(lab_cov, 1e-9))
    return score, best_end_pair, best_label_key, None


def _index_or_add(vocab, key, unk_key="UNK"):
    if key in vocab:
        return vocab[key]
    return vocab.get(unk_key, 0)


def _try_fast_containers(g, node_vocab, edge_vocab):
    """
    Fast path: try common Draper/Joern keys and short-circuit full-tree scanning.
    Returns:
        (best_node, best_node_key, best_node_score,
         best_edge, best_end_pair, best_edge_label_key, best_edge_score, used_fast)
    If not decisive, returns (None,..., False) so caller can do the slow fallback.
    """
    if not isinstance(g, dict):
        return None, None, 0.0, None, None, None, 0.0, False

    # Typical containers seen in Draper/Joern exports
    node_cands = []
    for k in ("nodes", "Vertices", "@value"):
        v = g.get(k)
        # Some dumps put nodes under g["@value"]["nodes"]
        if k == "@value" and isinstance(v, dict):
            vv = v.get("nodes")
            if isinstance(vv, list):
                node_cands.append(vv)
        if isinstance(v, list):
            node_cands.append(v)

    edge_cands = []
    for k in ("edges", "Edges", "@value"):
        v = g.get(k)
        if k == "@value" and isinstance(v, dict):
            vv = v.get("edges")
            if isinstance(vv, list):
                edge_cands.append(vv)
        if isinstance(v, list):
            edge_cands.append(v)

    # Score like the slow path but only on these candidates
    best_node, best_node_key, best_node_score = None, None, 0.0
    for lst in node_cands:
        score, lk, _ = _score_node_list(lst, node_vocab)
        if score > best_node_score:
            best_node_score, best_node, best_node_key = score, lst, lk

    best_edge, best_end_pair, best_edge_label_key, best_edge_score = None, None, None, 0.0
    for lst in edge_cands:
        score, end_pair, lab_key, _ = _score_edge_list(lst, edge_vocab)
        if score > best_edge_score:
            best_edge_score, best_edge, best_end_pair, best_edge_label_key = score, lst, end_pair, lab_key

    used_fast = (best_node is not None) or (best_edge is not None)
    return best_node, best_node_key, best_node_score, best_edge, best_end_pair, best_edge_label_key, best_edge_score, used_fast


def _discover_nodes_only(g, node_vocab):
    """Single _walk_lists pass to find the best node list & key."""
    best_node, best_node_key, best_node_score = None, None, 0.0
    for lst in _walk_lists(g):
        s, lk, _ = _score_node_list(lst, node_vocab)
        if s > best_node_score:
            best_node_score, best_node, best_node_key = s, lst, lk
    return best_node, best_node_key, best_node_score

def _discover_edges_only(g, edge_vocab):
    """Single _walk_lists pass to find the best edge list, endpoints and key."""
    best_edge, best_end_pair, best_edge_label_key, best_edge_score = None, None, None, 0.0
    for lst in _walk_lists(g):
        s, end_pair, lab_key, _ = _score_edge_list(lst, edge_vocab)
        if s > best_edge_score:
            best_edge_score, best_edge, best_end_pair, best_edge_label_key = s, lst, end_pair, lab_key
    return best_edge, best_end_pair, best_edge_label_key, best_edge_score




# -------------------------------------------------------------------
# Main parser (REPLACEMENT)
# -------------------------------------------------------------------
def _parse_graphson(
    path_or_dict,
    *,
    node_vocab=None,
    edge_vocab=None,
    debug_prefix="Parse",
    strict=False,
    min_nodes=0,
    one_hot=False,  # This parameter is now ignored - always use dense features
    fallback_feature_dim=64,
    expected_feature_dim=None,  # This is the new parameter
    validate_graph=True,
    max_nodes=None
):
    """
    Parse GraphSON data into a PyTorch Geometric Data object with dense features.
    
    This function implements a multi-pass parsing strategy to handle various JSON structures:
    1. Fast path: Try top-level 'nodes'/'edges' containers (common in Draper/Joern exports)
    2. If nodes missing but edges present: Run NODES-ONLY discovery (no double work)
    3. If edges missing: Run EDGES-ONLY discovery
    4. If fast edges had misses, try slow edges-only discovery and adopt if strictly better
    
    The function now exclusively uses DENSE FEATURES with fixed dimension (fallback_feature_dim)
    to ensure consistent input dimensions for the model.
    
    Args:
        path_or_dict: Path to JSON file or pre-loaded JSON dict
        node_vocab: Vocabulary for node labels (not used for feature dimension)
        edge_vocab: Vocabulary for edge labels (not used for feature dimension)
        debug_prefix: Prefix for debug logs (default: "Parse")
        strict: Whether to raise errors for invalid data (default: False)
        min_nodes: Minimum number of nodes required for a valid graph (default: 0)
        one_hot: This parameter is ignored - dense features are always used
        fallback_feature_dim: Feature dimension for node features (must match model's expected dimension)
        expected_feature_dim: Expected feature dimension (must match model's expected dimension)
        validate_graph: Whether to validate graph structure after parsing (default: True)
        max_nodes: Maximum number of nodes allowed (default: None)
    
    Returns:
        PyTorch Geometric Data object
        
    Raises:
        ValueError: If strict mode is enabled and the graph is invalid
    """
    # ── Input validation ───────────────────────────────────────────────
    if not isinstance(path_or_dict, (str, bytes, os.PathLike, dict)):
        raise TypeError(f"Invalid path_or_dict type: {type(path_or_dict)}")
    
    if node_vocab is None:
        node_vocab = {}
        logger.debug("No node vocabulary provided; using empty vocabulary (not used for dense features)")
    if edge_vocab is None:
        edge_vocab = {}
        logger.debug("No edge vocabulary provided; using empty vocabulary (not used for dense features)")
    
    # ── Load JSON data ───────────────────────────────────────────────
    g = None
    src_name = None
    
    try:
        if isinstance(path_or_dict, (str, bytes, os.PathLike)):
            src_name = str(path_or_dict)
            try:
                with open(path_or_dict, "rb") as f:
                    raw = f.read()
                    g = _fast_json_load_bytes(raw)
                logger.debug(f"Successfully loaded JSON from {src_name}")
            except FileNotFoundError:
                logger.error(f"File not found: {src_name}")
                raise
            except Exception as e:
                logger.error(f"Failed to load JSON from {src_name}: {e}")
                raise
        else:
            g = path_or_dict
            src_name = "<in-memory>"
            logger.debug("Using in-memory JSON data")
        
        if g is None:
            msg = f"Failed to load JSON data from {src_name}"
            logger.error(msg)
            if strict:
                raise ValueError(msg)
            return _create_fallback_graph(
                debug_prefix, 
                fallback_feature_dim, 
                min_nodes, 
                "No data loaded"
            )
    except Exception as e:
        logger.error(f"Critical error loading JSON from {src_name}: {e}")
        if strict:
            raise
        return _create_fallback_graph(
            debug_prefix, 
            fallback_feature_dim, 
            min_nodes, 
            f"Critical load error: {str(e)}"
        )

    # ── Initialize parsing context ───────────────────────────────────
    node_labels = []
    node_ids = []
    rows = []
    cols = []
    elabs = []
    
    # ── Helper functions ─────────────────────────────────────────────
    def _normalize_id(x):
        """Normalize node/edge identifiers for consistent mapping."""
        if isinstance(x, (str, int)):
            return x
        if isinstance(x, dict):
            # Try common identifier patterns
            for key in ("@value", "id", "_id", "vertexId"):
                if key in x and x[key] is not None:
                    return _normalize_id(x[key])
            # Try properties
            props = x.get("properties", {})
            if isinstance(props, dict) and "id" in props:
                return _normalize_id(props["id"])
            # Fallback to string representation
            try:
                return json.dumps(x, sort_keys=True)
            except Exception:
                return str(x)
        if isinstance(x, (list, tuple)):
            return tuple(_normalize_id(e) for e in x)
        return x

    def _extract_node_id(d):
        """Extract a stable identifier from a node dictionary."""
        id_keys = ("id", "@id", "_id", "_key", "_gid", "vertexId")
        for key in id_keys:
            if key in d:
                return _normalize_id(d[key])
        if isinstance(d, dict) and "properties" in d and isinstance(d["properties"], dict):
            if "id" in d["properties"]:
                return _normalize_id(d["properties"]["id"])
        # Fallback to index-based identifier
        return f"node_{len(node_ids)}"

    def _get_label_value(item, key_path):
        """Safely extract label values from nested structures."""
        if not key_path:
            return item
        if not isinstance(key_path, (list, tuple)):
            key_path = (key_path,)
        
        current = item
        for key in key_path:
            if isinstance(current, dict):
                current = current.get(key)
            elif isinstance(current, (list, tuple)) and isinstance(key, int):
                current = current[key] if 0 <= key < len(current) else None
            else:
                return None
            if current is None:
                return None
        return current

    # ── Fast path: try top-level containers ────────────────────────
    best_node = None
    best_edge = None
    best_node_key = None
    best_edge_key = None
    best_node_score = 0.0
    best_edge_score = 0.0
    used_slow = False

    # Try common top-level keys
    node_candidates = [
        g.get("nodes"),
        g.get("Vertices"),
        g.get("@value", {}).get("vertices") if isinstance(g, dict) else None
    ]
    
    edge_candidates = [
        g.get("edges"),
        g.get("Edges"),
        g.get("@value", {}).get("edges") if isinstance(g, dict) else None
    ]

    # Evaluate node candidates
    for candidate in node_candidates:
        if isinstance(candidate, list) and candidate:
            score, key, _ = _score_node_list(candidate, node_vocab)
            if score > best_node_score:
                best_node_score, best_node, best_node_key = score, candidate, key

    # Evaluate edge candidates
    for candidate in edge_candidates:
        if isinstance(candidate, list) and candidate:
            score, end_pair, key, _ = _score_edge_list(candidate, edge_vocab)
            if score > best_edge_score:
                best_edge_score, best_edge, best_end_pair, best_edge_key = score, candidate, end_pair, key

    # ── Debug logging ──────────────────────────────────────────────
    if debug_prefix:
        logger.debug(f"[{debug_prefix}] source={src_name}")
        if best_node is not None:
            logger.debug(f"[{debug_prefix}] nodes_found len={len(best_node)} label_key={best_node_key!r} score={best_node_score:.3f}")
        else:
            logger.debug(f"[{debug_prefix}] nodes_found NONE")
        if best_edge is not None:
            logger.debug(f"[{debug_prefix}] edges_found len={len(best_edge)} endpoints={best_end_pair!r} label_key={best_edge_key!r} score={best_edge_score:.3f}")
        else:
            logger.debug(f"[{debug_prefix}] edges_found NONE")

    # ── Discover missing components ────────────────────────────────
    # If edges are missing or insufficient, try slow edge discovery
    if best_edge is None or best_end_pair is None or len(best_edge) < 2:
        slow_edge, slow_end_pair, slow_edge_key, slow_edge_score = _discover_edges_only(g, edge_vocab)
        if slow_edge is not None and slow_end_pair is not None:
            best_edge, best_end_pair, best_edge_key, best_edge_score = slow_edge, slow_end_pair, slow_edge_key, slow_edge_score
            used_slow = True
            if debug_prefix:
                logger.debug(f"[{debug_prefix}] edges_found (slow) len={len(best_edge)} endpoints={best_end_pair!r} label_key={best_edge_key!r} score={best_edge_score:.3f}")

    # If nodes are missing or insufficient, try slow node discovery
    need_nodes = (best_node is None) or (min_nodes and len(best_node) < min_nodes)
    if need_nodes:
        slow_node, slow_node_key, slow_node_score = _discover_nodes_only(g, node_vocab)
        if slow_node is not None and (not min_nodes or len(slow_node) >= min_nodes):
            best_node, best_node_key, best_node_score = slow_node, slow_node_key, slow_node_score
            if debug_prefix:
                logger.debug(f"[{debug_prefix}] nodes_found (slow) len={len(best_node)} label_key={best_node_key!r} score={best_node_score:.3f}")

    # ── Validate node count ───────────────────────────────────────
    if not best_node or (min_nodes and len(best_node) < min_nodes):
        msg = f"[{debug_prefix}] No usable nodes (min_nodes={min_nodes}) in {src_name}"
        logger.error(msg)
        if strict:
            raise ValueError(msg)
        return _create_fallback_graph(
            debug_prefix,
            fallback_feature_dim,
            min_nodes,
            "Insufficient nodes"
        )

    # ── Process nodes ─────────────────────────────────────────────
    id_to_index = {}
    for nd in best_node:
        nid = _extract_node_id(nd)
        node_id = _normalize_id(nid)
        node_ids.append(node_id)
        
        # Extract node label
        label = None
        for key_path in [
            ("label",), ("type",), ("kind",), ("nodeLabel",), 
            ("properties", "label"), ("properties", "type")
        ]:
            label = _get_label_value(nd, key_path)
            if label:
                break
        node_labels.append(label if label else "UNKNOWN")
        
        # Build mapping
        if node_id not in id_to_index:
            id_to_index[node_id] = len(id_to_index)

    # ── Validate node count again after processing ─────────────────
    N = len(id_to_index)
    if N < max(1, min_nodes):
        msg = f"[{debug_prefix}] Only {N} unique nodes (min_nodes={min_nodes}) in {src_name}"
        logger.error(msg)
        if strict:
            raise ValueError(msg)
        return _create_fallback_graph(
            debug_prefix,
            fallback_feature_dim,
            min_nodes,
            f"Only {N} unique nodes"
        )
    
    # ── Build node features ───────────────────────────────────────
    # DENSE FEATURES: Always create features with fixed dimension
    x = torch.randn(N, fallback_feature_dim).float()

    # ── Process edges ─────────────────────────────────────────────
    def _build_edges(edge_list, end_pair):
        """Build edge index and attributes from edge list and endpoint keys."""
        rows, cols, elabs = [], [], []
        if edge_list and end_pair:
            a, b = end_pair
            for e in edge_list:
                # Extract source and target nodes
                u = _get_label_value(e, (a,))
                v = _get_label_value(e, (b,))
                
                # Normalize and map to indices
                u_id = _normalize_id(u)
                v_id = _normalize_id(v)
                u_idx = id_to_index.get(u_id)
                v_idx = id_to_index.get(v_id)
                
                # Handle missing nodes
                if u_idx is None or v_idx is None:
                    continue
                    
                rows.append(u_idx)
                cols.append(v_idx)
                
                # Extract edge label
                label = None
                for key_path in [
                    ("label",), ("edgeLabel",), ("type",), ("kind",), ("rel",),
                    ("properties", "label"), ("properties", "type")
                ]:
                    label = _get_label_value(e, key_path)
                    if label:
                        break
                elabs.append(edge_vocab.get(label, edge_vocab.get("UNK", 0)))
        return rows, cols, elabs

    # Build edges with current candidates
    rows, cols, elabs = _build_edges(best_edge, best_end_pair)
    
    # If few edges, try slow discovery
    if len(rows) < 2 and best_edge:
        slow_edge2, slow_end2, slow_edge_key2, slow_edge_score2 = _discover_edges_only(g, edge_vocab)
        if slow_edge2 and slow_end2:
            rows_s, cols_s, elabs_s = _build_edges(slow_edge2, slow_end2)
            if len(rows_s) > len(rows):
                rows, cols, elabs = rows_s, cols_s, elabs_s
                used_slow = True
                if debug_prefix:
                    logger.debug(f"[{debug_prefix}] edges_replaced_by_slow (new_count={len(rows)})")

    # ── Create edge index and attributes ──────────────────────────
    if not rows:
        msg = f"[{debug_prefix}] No usable edges in {src_name}"
        logger.warning(msg)
        edge_index = torch.empty((2, 0), dtype=torch.long)
        edge_attr = torch.empty((0,), dtype=torch.long)
    else:
        edge_index = torch.tensor([rows, cols], dtype=torch.long)
        edge_attr = torch.tensor(elabs, dtype=torch.long)

    # ── Create and validate graph data ────────────────────────────
    data = Data(x=x, edge_index=edge_index, edge_attr=edge_attr)
    if edge_attr.numel() > 0:
        data.edge_type = edge_attr.clone()
    
    # Add metadata for debugging
    data.source_path = src_name
    data.node_labels = node_labels
    data.node_ids = node_ids
    
    # ── Validate final graph structure ────────────────────────────
    if validate_graph:
        try:
            # Validate node features dimension
            if data.x.shape[1] != fallback_feature_dim:
                msg = f"Node features have dimension {data.x.shape[1]} but expected {fallback_feature_dim}"
                logger.warning(f"[{debug_prefix}] {msg}")
                # Ensure consistent dimension by adjusting
                data.x = _adjust_feature_dimension(data.x, fallback_feature_dim)
                logger.info(f"[{debug_prefix}] Adjusted node features to dimension {fallback_feature_dim}")
            
            # Validate node count
            if data.num_nodes < min_nodes:
                msg = f"Graph has {data.num_nodes} nodes (min={min_nodes})"
                logger.error(f"[{debug_prefix}] {msg}")
                if strict:
                    raise ValueError(msg)
                return _create_fallback_graph(
                    debug_prefix,
                    fallback_feature_dim,
                    min_nodes,
                    f"Only {data.num_nodes} nodes"
                )
                
            # Validate edge indices
            if data.edge_index.numel() > 0:
                max_index = data.edge_index.max().item()
                if max_index >= data.num_nodes:
                    msg = f"Edge index contains invalid node indices (max={max_index}, num_nodes={data.num_nodes})"
                    logger.error(f"[{debug_prefix}] {msg}")
                    if strict:
                        raise ValueError(msg)
                    # Try to fix by filtering invalid edges
                    valid_mask = (data.edge_index[0] < data.num_nodes) & (data.edge_index[1] < data.num_nodes)
                    data.edge_index = data.edge_index[:, valid_mask]
                    if data.edge_attr.numel() > 0:
                        data.edge_attr = data.edge_attr[valid_mask]
                    logger.warning(f"[{debug_prefix}] Fixed invalid edge indices (new edge count: {data.edge_index.size(1)})")
        except Exception as e:
            logger.error(f"[{debug_prefix}] Graph validation failed: {e}")
            if strict:
                raise
            return _create_fallback_graph(
                debug_prefix,
                fallback_feature_dim,
                min_nodes,
                "Validation failed"
            )

    # ── Record parsing statistics ────────────────────────────────
    with _PARSE_STATS_LOCK:
        _PARSE_STATS["graphs"] += 1
        if used_slow:
            _PARSE_STATS["slow_fallback"] += 1
        else:
            _PARSE_STATS["fast_ok"] += 1
            
        if debug_prefix and _PARSE_STATS_EVERY > 0 and (_PARSE_STATS["graphs"] % _PARSE_STATS_EVERY == 0):
            logger.info(
                f"[ParseStats] fast_ok={_PARSE_STATS['fast_ok']} "
                f"slow_fallback={_PARSE_STATS['slow_fallback']} "
                f"empty_edges={_PARSE_STATS['empty_edges']} "
                f"graphs={_PARSE_STATS['graphs']} (every {_PARSE_STATS_EVERY})"
            )

    # ── Final debug logging ─────────────────────────────────────
    if debug_prefix:
        logger.debug(f"[{debug_prefix}] final_graph N={data.num_nodes} E={data.edge_index.size(1)}")
    
    return data

def _adjust_feature_dimension(x: torch.Tensor, target_dim: int) -> torch.Tensor:
    """
    Adjust node feature dimension to match target dimension.
    
    Args:
        x: Input node feature tensor
        target_dim: Target feature dimension
    
    Returns:
        Node feature tensor with dimension adjusted to target_dim
    """
    N, current_dim = x.shape
    
    # If dimensions match, no adjustment needed
    if current_dim == target_dim:
        return x
    
    # Create a new tensor with the target dimension
    new_x = torch.zeros(N, target_dim, dtype=x.dtype, device=x.device)
    
    # Copy existing features (truncating or padding as needed)
    min_dim = min(current_dim, target_dim)
    new_x[:, :min_dim] = x[:, :min_dim]
    
    return new_x

def _create_fallback_graph(debug_prefix, fallback_feature_dim, min_nodes, reason=""):
    """
    Create a minimal fallback graph when parsing fails.
    
    Args:
        debug_prefix: Prefix for debug logs
        fallback_feature_dim: Feature dimension for the fallback graph
        min_nodes: Minimum number of nodes required
        reason: Reason for fallback graph creation
    
    Returns:
        PyTorch Geometric Data object with random features
    """
    n = max(8, min_nodes)
    logger.warning(f"[{debug_prefix}] No usable graph: {reason} → creating fallback graph with {n} nodes")
    
    # DENSE FEATURES: Always use the fallback dimension
    x = torch.randn(n, fallback_feature_dim).float()
    ei = torch.randint(0, n, (2, max(2 * n, 16)), dtype=torch.long)
    
    # Create Data object with minimal metadata
    data = Data(x=x, edge_index=ei)
    data.source_path = "<fallback>"
    
    # Add debugging information
    if debug_prefix:
        logger.debug(f"[{debug_prefix}] fallback_graph N={n} E={ei.size(1)}")
    
    return data

def _adjust_feature_dimension(x: torch.Tensor, target_dim: int) -> torch.Tensor:
    """
    Adjust node feature dimension to match target dimension.
    
    This is critical for dense features to ensure consistent dimensions.
    
    Args:
        x: Input node feature tensor
        target_dim: Target dimension
        
    Returns:
        Node feature tensor with dimension adjusted to target_dim
    """
    N, current_dim = x.shape
    
    # If dimensions match, no adjustment needed
    if current_dim == target_dim:
        return x
    
    # Create a new tensor with the target dimension
    new_x = torch.zeros(N, target_dim, dtype=x.dtype, device=x.device)
    
    # Copy existing features (truncating or padding as needed)
    min_dim = min(current_dim, target_dim)
    new_x[:, :min_dim] = x[:, :min_dim]
    
    return new_x

def _create_fallback_graph(debug_prefix, fallback_feature_dim, min_nodes, reason=""):
    """
    Create a minimal fallback graph when parsing fails.
    
    Args:
        debug_prefix: Prefix for debug logs
        fallback_feature_dim: Feature dimension for the fallback graph
        min_nodes: Minimum number of nodes required
        reason: Reason for fallback graph creation
    
    Returns:
        PyTorch Geometric Data object with random features
    """
    n = max(8, min_nodes)
    logger.warning(f"[{debug_prefix}] No usable graph: {reason} → creating fallback graph with {n} nodes")
    
    # DENSE FEATURES: Always use the fallback dimension
    x = torch.randn(n, fallback_feature_dim).float()
    ei = torch.randint(0, n, (2, max(2 * n, 16)), dtype=torch.long)
    
    # Create Data object with minimal metadata
    data = Data(x=x, edge_index=ei)
    data.source_path = "<fallback>"
    
    # Add debugging information
    if debug_prefix:
        logger.debug(f"[{debug_prefix}] fallback_graph N={n} E={ei.size(1)}")
    
    return data


# Helper function for creating fallback graphs
def _create_fallback_graph(debug_prefix, fallback_feature_dim, min_nodes, reason=""):
    """
    Create a minimal fallback graph when parsing fails.
    
    Args:
        debug_prefix: Prefix for debug logs
        fallback_feature_dim: Feature dimension for the fallback graph
        min_nodes: Minimum number of nodes required
        reason: Reason for fallback graph creation
    
    Returns:
        PyTorch Geometric Data object with random features
    """
    n = max(8, min_nodes)
    logger.warning(f"[{debug_prefix}] No usable graph: {reason} → creating fallback graph with {n} nodes")
    
    x = torch.randn(n, int(max(1, fallback_feature_dim))).float()
    ei = torch.randint(0, n, (2, max(2 * n, 16)), dtype=torch.long)
    
    # Create Data object with minimal metadata
    data = Data(x=x, edge_index=ei)
    data.source_path = "<fallback>"
    
    # Add debugging information
    if debug_prefix:
        logger.debug(f"[{debug_prefix}] fallback_graph N={n} E={ei.size(1)}")
    
    return data



# ────────────────────────────────────────────
# Dataset (family-aware)
# ────────────────────────────────────────────
# replace _infer_family_id with this:
_FAMILY_RE = re.compile(r"(?:^|/)(?:train|valid|test)_func_(\d+)(?:_|/)", re.IGNORECASE)

def _infer_family_id(path_str: str) -> str:
    s = path_str or ""
    m = _FAMILY_RE.search(s)
    if m:  # group by numeric function id only
        return f"func_{m.group(1)}"
    # fallback: strip mutation suffixes like "_mutXXXX" or "_advT3"
    base = os.path.basename(os.path.dirname(s))
    base = re.sub(r"_(?:mut|adv)\w*$", "", base, flags=re.IGNORECASE)
    return base or "unknown"


def _infer_mut_type(path_str: str) -> str:
    s = (path_str or "").lower()
    if "snap_" in s: return "snap"
    if "adv" in s or "mut" in s or "mutant" in s: return "mut"
    return "orig"




class DraperDataset(torch.utils.data.Dataset):
    """
    Dataset class for Draper vulnerability detection dataset.
    
    This class handles loading, parsing, and caching of code property graphs (CPGs) or 
    control flow graphs (CFGs) from JSON files. This version uses DENSE FEATURES by default
    instead of one-hot encoding to ensure consistent feature dimension.
    
    Key changes from original:
    - Default to dense features (one_hot=False)
    - Fixed feature dimension regardless of vocabulary size
    - Enhanced error handling for dimension mismatches
    - Improved cache management for dense features
    """
    
    def __init__(self,
                 manifest_csv: Optional[str],
                 json_root: Optional[str],
                 feature_dim: int = 64,
                 cache_dir: Optional[str] = None,
                 new_cache_dir: Optional[str] = None,  # This is now a valid parameter
                 cache_overwrite: bool = False,
                 no_progress: bool = True,
                 strict_json: bool = False,
                 fallback_random: bool = False,
                 report_missing: int = 20,
                 index_scan_prefixes: Optional[List[str]] = None,
                 node_vocab: Optional[dict] = None,
                 edge_vocab: Optional[dict] = None,
                 min_nodes: int = 0,
                 cache_shards: int = 1,
                 cache_tmpdir: Optional[str] = None,
                 cache_version: str = "v1",
                 validate_graphs: bool = True,
                 cache_clean_after: int = 0,
                 max_cache_size_gb: float = 10.0,
                 cache_timeout: int = 30,
                 one_hot: bool = False):  # CHANGED: Default to False for dense features
        """
        Initialize the DraperDataset.
        
        Args:
            manifest_csv: Path to CSV manifest file containing dataset metadata
            json_root: Root directory containing JSON graph files
            feature_dim: Dimension of node features (for dense features)
            cache_dir: Directory to store cache files
            cache_overwrite: Whether to overwrite existing cache files
            no_progress: Whether to disable progress bars
            strict_json: Whether to raise errors for missing/malformed JSON
            fallback_random: Whether to use random fallback graphs
            report_missing: Maximum number of missing file warnings to report
            index_scan_prefixes: Directory name prefixes for index-based lookup
            node_vocab: Predefined node vocabulary (not used for feature dimension when using dense features)
            edge_vocab: Predefined edge vocabulary
            min_nodes: Minimum number of nodes required for a valid graph
            cache_shards: Number of shards for cache (1 = single file)
            cache_tmpdir: Temporary directory for cache (if different from cache_dir)
            cache_version: Version identifier for cache invalidation
            validate_graphs: Whether to validate graph structure after parsing
            cache_clean_after: Hours after which cache should be cleaned (0 = no cleaning)
            max_cache_size_gb: Maximum cache size in GB (0 = no limit)
            cache_timeout: Maximum time (seconds) to refresh cache index
            one_hot: Whether to use one-hot encoding (default: False - dense features)
        """
        super().__init__()
        
        # Core configuration
        self.rows: List[Dict[str, Any]] = []
        self.feature_dim = int(feature_dim)
        self.json_root = Path(json_root) if json_root else None
        # Handle new cache directory if specified
        if new_cache_dir:
            self.cache_dir = Path(new_cache_dir)
            print(f"[Cache] Using new cache directory: {self.cache_dir}")
            print("  - Old cache remains intact at previous location")
        else:
            self.cache_dir = Path(cache_dir) if cache_dir else None
        self.cache_overwrite = bool(cache_overwrite)
        self.no_progress = bool(no_progress)
        self.cache_shards = int(max(1, cache_shards))
        self.cache_tmpdir = (Path(cache_tmpdir) if cache_tmpdir else None)
        self.cache_version = str(cache_version)
        self.validate_graphs = bool(validate_graphs)
        self.cache_clean_after = int(cache_clean_after)
        self.max_cache_size_gb = float(max_cache_size_gb)
        self.cache_timeout = int(cache_timeout)
        self.one_hot = bool(one_hot)  # CHANGED: Explicit parameter for feature type
        
        # Parsing configuration
        self.strict_json = bool(strict_json)
        self.fallback_random = bool(fallback_random)
        self.min_nodes = int(min_nodes)
        self.debug_parse = False  # Will be set from args.parse_debug later
        
        # Counters and thresholds
        self._missing_warned = 0
        self._report_missing = int(report_missing)
        self._last_cache_clean = 0
        self._cache_initialized = False
        
        # Vocabularies (used for label mapping but NOT for feature dimension when using dense features)
        self.node_vocab = node_vocab or {}
        self.edge_vocab = edge_vocab or {}
        
        # Path resolution settings
        self.index_scan_prefixes = (index_scan_prefixes
                                   if index_scan_prefixes is not None
                                   else ["train_func", "valid_func", "test_func", "func"])
        self._dir_cache: Dict[int, Optional[Path]] = {}
        
        # Load manifest file
        if manifest_csv:
            self._load_manifest(manifest_csv)
        
        # Validate cache configuration
        self._validate_cache_config()

    def _validate_cache_config(self):
        """Validate cache configuration parameters and ensure proper setup."""
        if self.cache_shards < 1:
            logger.warning(f"Invalid cache_shards value: {self.cache_shards}. Setting to 1.")
            self.cache_shards = 1
            
        if self.max_cache_size_gb < 0:
            logger.warning(f"Invalid max_cache_size_gb value: {self.max_cache_size_gb}. Setting to 0 (no limit).")
            self.max_cache_size_gb = 0.0
            
        if self.cache_timeout < 1:
            logger.warning(f"Invalid cache_timeout value: {self.cache_timeout}. Setting to 30 seconds.")
            self.cache_timeout = 30

    def _load_manifest(self, manifest_csv: str):
        """Load and process the manifest CSV file with validation and error handling."""
        try:
            with open(manifest_csv, "r", encoding="utf-8") as f:
                rd = csv.DictReader(f)
                for r in rd:
                    processed = self._process_manifest_row(r)
                    if processed:
                        self.rows.append(processed)
            logger.info(f"Loaded {len(self.rows)} rows from manifest: {manifest_csv}")
        except FileNotFoundError:
            logger.error(f"Manifest file not found: {manifest_csv}")
            raise
        except Exception as e:
            logger.error(f"Error reading manifest {manifest_csv}: {e}")
            raise

    def _process_manifest_row(self, r: Dict[str, str]) -> Optional[Dict[str, Any]]:
        """Process a single manifest row with validation and normalization."""
        # Extract and validate required fields
        label = r.get("label", "0")
        try:
            label = int(label)
        except ValueError:
            logger.warning(f"Invalid label '{label}' for row, defaulting to 0. Row: {r}")
            label = 0

        p_eq_str = r.get("p_eq")
        try:
            p_eq = float(p_eq_str) if p_eq_str is not None else 1.0
        except (ValueError, TypeError):
            logger.warning(f"Invalid p_eq value '{p_eq_str}' for row, defaulting to 1.0. Row: {r}")
            p_eq = 1.0

        # Infer family and mutation type
        jp = (r.get("json_path") or "").strip()
        fam = (r.get("family_id") or "").strip() or _infer_family_id(jp)
        mut = (r.get("mutation_type") or "").strip() or _infer_mut_type(jp)

        return {
            "label": label,
            "p_eq": p_eq,
            "family_id": fam,
            "mutation_type": mut,
            "json_path": jp,
            "index": r.get("index"),
            "id": r.get("id")
        }

    def _graph_cache_key(self, json_path: Path) -> str:
        """
        Build a stable entry name for the graph cache.
        
        The key includes:
        - Hash of the file path
        - Feature dimension (for dense features)
        - Vocabulary signature
        - File modification time
        
        This ensures cache invalidation when any of these parameters change.
        
        Args:
            json_path: Path to the JSON file
            
        Returns:
            Stable cache key string
        """
        try:
            mt = int(json_path.stat().st_mtime)
        except OSError:
            logger.warning(f"Could not stat mtime for {json_path}, using 0.")
            mt = 0
            
        h = hashlib.md5(str(json_path).encode("utf-8")).hexdigest()[:10]
        v = getattr(self, "_vocab_sig", "nosig")
        
        return f"graph-{h}-fd{self.feature_dim}-v{v}-mt{mt}.pkl"

    def _get_zip_cache(self):
            """Get or initialize the cache with versioning and validation."""
            if not self._cache_initialized and self.cache_dir:
                try:
                    # Clean cache if needed
                    self._maybe_clean_cache()
                    
                    # Initialize cache
                    if self.cache_shards > 1:
                        shards_dir = self.cache_tmpdir if self.cache_tmpdir else (self.cache_dir / "shards")
                        base_zip = self.cache_dir / "graph_cache.zip"
                        self._zip_cache = GraphShardedCache(
                            shards_dir=shards_dir,
                            num_shards=self.cache_shards,
                            base_zip=base_zip,
                            cache_version=self.cache_version
                        )
                    else:
                        zip_path = self.cache_dir / "graph_cache.zip"
                        self._zip_cache = GraphZipCache(
                            zip_path=zip_path,
                            cache_version=self.cache_version
                        )
                    
                    self._cache_initialized = True
                    logger.debug(f"Initialized {'sharded' if self.cache_shards > 1 else 'single-file'} cache")
                    
                    # Check cache size
                    self._check_cache_size()
                    
                except Exception as e:
                    logger.error(f"Failed to initialize cache: {e}")
                    self._zip_cache = None
            
            return self._zip_cache

    def _maybe_clean_cache(self):
        """Clean the cache if it exceeds size limits or is too old."""
        if not self.cache_dir or not self.cache_dir.exists():
            return
            
        if self.cache_clean_after > 0 and (time.time() - self._last_cache_clean) > (self.cache_clean_after * 3600):
            logger.info("Performing cache cleanup due to age")
            self._clean_cache()
            self._last_cache_clean = time.time()

    def _check_cache_size(self):
        """Check if cache size exceeds configured limits."""
        if self.max_cache_size_gb > 0:
            cache_size = self._get_cache_size()
            if cache_size > (self.max_cache_size_gb * 1024**3):
                logger.warning(f"Cache size ({cache_size/1024**3:.2f} GB) exceeds limit ({self.max_cache_size_gb} GB)")
                self._clean_cache()

    def _get_cache_size(self) -> float:
        """Calculate total cache size in bytes."""
        total = 0
        if self.cache_dir and self.cache_dir.exists():
            for path in self.cache_dir.rglob("*"):
                if path.is_file():
                    total += path.stat().st_size
        return total

    def _clean_cache(self):
        """Clean the cache based on size and age constraints."""
        cache = self._get_zip_cache()
        if not cache:
            return
            
        if isinstance(cache, GraphZipCache):
            cache.clean_cache()
        elif isinstance(cache, GraphShardedCache):
            # Clean shards
            for i in range(cache.num_shards):
                shard_path = cache._paths[i]
                if shard_path.exists():
                    try:
                        # Basic cleanup - implement more sophisticated logic as needed
                        if shard_path.stat().st_size > (self.max_cache_size_gb / cache.num_shards) * 1024**3:
                            logger.info(f"Shard {i} exceeds size limit, cleaning...")
                            cache._clean_shard(i)
                    except Exception as e:
                        logger.error(f"Failed to clean shard {i}: {e}")

    def __len__(self) -> int:
        """Return the number of items in the dataset."""
        return len(self.rows)

    def _find_dir_by_index(self, idx: int) -> Optional[Path]:
        """
        Map integer index to directory under json_root.
        
        Uses multiple strategies to find the correct directory:
        1. Exact match with known prefixes
        2. Fallback to glob pattern matching
        
        Args:
            idx: Integer index to look up
            
        Returns:
            Path to directory if found, otherwise None
        """
        if idx in self._dir_cache:
            return self._dir_cache[idx]
        if self.json_root is None:
            self._dir_cache[idx] = None
            return None
            
        pad = f"{int(idx):07d}"
        # Try exact matches first
        for pref in self.index_scan_prefixes:
            cand = self.json_root / f"{pref}_{pad}"
            try:
                if cand.is_dir():
                    self._dir_cache[idx] = cand
                    logger.debug(f"Found directory for index {idx}: {cand}")
                    return cand
            except Exception as e:
                logger.warning(f"Error checking directory {cand} for index {idx}: {e}")
                continue
        
        # Try glob pattern matching
        try:
            for cand in self.json_root.glob(f"*_{pad}"):
                if cand.is_dir():
                    self._dir_cache[idx] = cand
                    logger.debug(f"Found directory via glob for index {idx}: {cand}")
                    return cand
        except Exception as e:
            logger.warning(f"Error during glob search for index {idx}: {e}")
            
        # Directory not found
        self._dir_cache[idx] = None
        logger.debug(f"Could not find directory for index {idx}.")
        return None

    def _resolve_candidates(self, r: Dict[str, str]) -> List[Path]:
        """
        Resolve possible JSON file paths for a manifest entry.
        
        Returns paths in priority order:
        1. Explicit path from manifest
        2. Legacy numeric folder structure
        3. Common Draper layout
        
        Args:
            r: Manifest row dictionary
            
        Returns:
            List of candidate paths (in priority order)
        """
        cands: List[Path] = []
        jp = (r.get("json_path") or "").strip()
        
        # Add explicit path if available
        if jp:
            p = Path(jp)
            if not p.is_absolute() and self.json_root is not None:
                p = self.json_root / p
            cands.append(p)
        
        # Add index-based candidates
        if self.json_root is not None:
            idx = r.get("index") or r.get("id")
            if idx is not None and str(idx).strip():
                try:
                    i = int(idx)
                    # Legacy numeric folder format
                    cands.append(self.json_root / str(i) / "export.json")
                    # Common Draper layout
                    d = self._find_dir_by_index(i)
                    if d is not None:
                        cands.append(d / "export.json")
                except ValueError:
                    logger.warning(f"Invalid index '{idx}' in row, skipping index-based lookups. Row: {r}")
        
        return cands

    def _first_existing(self, cands: List[Path]) -> Optional[Path]:
        """
        Find the first existing file among candidate paths.
        
        Args:
            cands: List of candidate paths
            
        Returns:
            First existing path, or None if none exist
        """
        for p in cands:
            try:
                if p.is_file():
                    logger.debug(f"Found existing file: {p}")
                    return p
            except Exception as e:
                logger.warning(f"Error checking file existence for {p}: {e}")
                continue
        logger.debug(f"No existing file found among candidates: {cands}")
        return None

    def __getitem__(self, idx: int) -> Data:
        """Get a single graph by index with improved cache handling for new cache setup."""
        r = self.rows[idx]
        label = int(r.get("label", 0))
        p_eq = float(r.get("p_eq", 1.0))
        family_id = (r.get("family_id") or "unknown")
        mut = (r.get("mutation_type") or "orig")
        is_mut = 0 if (str(mut).lower() == "orig") else 1
        sample_index = idx

        # Resolve graph file path
        cands = self._resolve_candidates(r)
        p = self._first_existing(cands)

        # Load/parse graph
        if p is None:
            msg = f"[Data][MISS] JSON not found for row {idx} | tried={cands} | family={family_id}, mut_type={mut}"
            logger.error(msg)
            if self.strict_json and not self.fallback_random:
                raise FileNotFoundError(msg)
            if self._missing_warned < self._report_missing:
                print(msg)
                self._missing_warned += 1
            # Use random fallback graph
            n = 12 + (idx % 5)
            logger.warning(f"Using random fallback graph for index {idx} (family={family_id}, mut={mut}). Nodes: {n}")
            d = Data(
                x=torch.randn(n, self.feature_dim),
                edge_index=torch.randint(0, n, (2, max(2 * n, 16)))
            )
        else:
            # Load from cache if possible
            zc = self._get_zip_cache()
            loaded_from_cache = False
            entry_name = None

            # Check if we're using a new cache location
            using_new_cache = False
            if zc is not None:
                # Get the cache directory path
                cache_dir = getattr(zc, "cache_dir", None)
                if cache_dir and hasattr(self, "new_cache_dir") and self.new_cache_dir:
                    using_new_cache = True

            if zc is not None:
                entry_name = self._graph_cache_key(p)
                
                # If using new cache, prioritize it over old cache
                if using_new_cache:
                    # Only load from new cache
                    if (not self.cache_overwrite) and entry_name and zc.contains(entry_name):
                        raw = zc.load(entry_name)
                        if raw is not None:
                            try:
                                d: Data = pickle.loads(raw)
                                loaded_from_cache = True
                                logger.debug(f"Loaded graph from NEW cache for {p} (family={family_id}, mut={mut}).")
                            except Exception as e:
                                logger.warning(f"Failed to unpickle cached data from NEW cache for {p}: {e}. Parsing from source.")
                                loaded_from_cache = False
                
                # If not using new cache or new cache failed, try old cache
                if not loaded_from_cache and not using_new_cache:
                    if (not self.cache_overwrite) and entry_name and zc.contains(entry_name):
                        raw = zc.load(entry_name)
                        if raw is not None:
                            try:
                                d: Data = pickle.loads(raw)
                                loaded_from_cache = True
                                logger.debug(f"Loaded graph from OLD cache for {p} (family={family_id}, mut={mut}).")
                            except Exception as e:
                                logger.warning(f"Failed to unpickle cached data from OLD cache for {p}: {e}. Parsing from source.")
                                loaded_from_cache = False

            # Parse from source if not loaded from cache
            if not loaded_from_cache:
                try:
                    d = _parse_graphson(
                        p,
                        node_vocab=self.node_vocab,
                        edge_vocab=self.edge_vocab,
                        debug_prefix=("Parse" if getattr(self, "debug_parse", False) else ""),
                        strict=self.strict_json,
                        min_nodes=self.min_nodes,
                        one_hot=False,  # Always use dense features
                        fallback_feature_dim=self.feature_dim,
                        expected_feature_dim=self.feature_dim
                    )
                    logger.debug(f"Parsed graph from source for {p} (family={family_id}, mut={mut}).")
                except Exception as e:
                    logger.error(f"Failed to parse graph from {p} (family={family_id}, mut={mut}): {e}")
                    raise

                # Store into cache
                if zc is not None and entry_name:
                    try:
                        buf = pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
                        zc.store(entry_name, buf)
                        
                        # Log which cache we're storing to
                        if using_new_cache:
                            logger.debug(f"Stored graph to NEW cache for {p} ({entry_name}, family={family_id}, mut={mut}).")
                        else:
                            logger.debug(f"Stored graph to OLD cache for {p} ({entry_name}, family={family_id}, mut={mut}).")
                    except Exception as e:
                        logger.warning(f"Failed to store graph to cache for {p} ({entry_name}, family={family_id}, mut={mut}): {e}")

        # Validate graph structure if enabled
        if self.validate_graphs:
            self._validate_graph(d, p, idx, family_id, mut)

        # Attach metadata
        d.y = torch.tensor([label], dtype=torch.long)
        d.family_id = family_id
        d.fid = torch.tensor([int(hashlib.md5(family_id.encode()).hexdigest()[:8], 16)], dtype=torch.long)
        d.mutation_type = mut
        d.is_mutant = torch.tensor([is_mut], dtype=torch.long)
        d.p_eq = torch.tensor([p_eq], dtype=torch.float)
        d.sample_index = torch.tensor([sample_index], dtype=torch.long)
        d.source_path = str(p) if p else None
        
        return d

    def _validate_graph(self, d: Data, p: Optional[Path], idx: int, family_id: str, mut: str):
        """
        Validate the structure and integrity of a parsed graph.
        
        This version validates that node features have the expected fixed dimension (self.feature_dim)
        
        Args:
            d: Graph data object to validate
            p: Path to the source JSON file (for logging)
            idx: Dataset index (for logging)
            family_id: Graph family ID (for logging)
            mut: Mutation type (for logging)
        """
        # Check node features
        if not hasattr(d, 'x') or d.x is None:
            msg = f"Graph data for index {idx} (family={family_id}, mut={mut}) has no node features 'x'"
            logger.error(msg)
            raise ValueError(f"Invalid graph data: {msg}")
        
        if not isinstance(d.x, torch.Tensor) or d.x.dim() != 2:
            shape = d.x.shape if hasattr(d, 'x') else 'N/A'
            msg = f"Graph data 'x' has incorrect shape: {shape}. Expected (*, {self.feature_dim})"
            logger.error(f"{msg} | index={idx}, family={family_id}, mut={mut}")
            raise ValueError(f"Invalid graph data: {msg}")
        
        # DENSE FEATURES: Ensure consistent dimension
        if d.x.size(1) != self.feature_dim:
            msg = f"Graph data 'x' has dimension {d.x.size(1)} but expected {self.feature_dim}"
            logger.warning(f"{msg} | index={idx}, family={family_id}, mut={mut}")
            # CHANGED: For dense features, we need to adjust the dimension to match
            # This is critical for consistent training
            d.x = self._adjust_feature_dimension(d.x)
            logger.info(f"Adjusted node feature dimension to {self.feature_dim} | index={idx}, family={family_id}, mut={mut}")

        # Check edge indices
        if not hasattr(d, 'edge_index') or d.edge_index is None:
            logger.warning(f"Graph data for index {idx} (family={family_id}, mut={mut}) has no edges 'edge_index'. Creating empty graph.")
            d.edge_index = torch.empty((2, 0), dtype=torch.long)
        
        if not isinstance(d.edge_index, torch.Tensor) or d.edge_index.dim() != 2 or d.edge_index.size(0) != 2:
            shape = d.edge_index.shape if hasattr(d, 'edge_index') else 'N/A'
            msg = f"Graph data 'edge_index' has incorrect shape: {shape}. Expected (2, *)"
            logger.error(f"{msg} | index={idx}, family={family_id}, mut={mut}")
            raise ValueError(f"Invalid graph data: {msg}")
        
        num_nodes = d.x.size(0)
        if num_nodes > 0 and hasattr(d, 'edge_index') and d.edge_index.size(1) > 0:
            max_index = d.edge_index.max().item()
            if max_index >= num_nodes:
                msg = f"Edge index contains invalid node indices (max={max_index}, num_nodes={num_nodes})"
                logger.error(f"{msg} | index={idx}, family={family_id}, mut={mut}")
                raise ValueError(f"Invalid graph data: {msg}")

        # Check for suspiciously small graphs
        if (not self.strict_json) and int(d.num_nodes) <= max(8, self.min_nodes):
            ne = int(d.edge_index.size(1)) if hasattr(d, "edge_index") else 0
            if self._missing_warned < self._report_missing:
                msg = f"[Data][WARN] Tiny graph from {p or '<none>'} (family={family_id}, mut={mut}) -> nodes={int(d.num_nodes)} edges={ne}"
                print(msg)
                self._missing_warned += 1

    def _adjust_feature_dimension(self, x: torch.Tensor) -> torch.Tensor:
        """
        Adjust node feature dimension to match expected dimension.
        
        This is critical for dense features to ensure consistent dimensions.
        
        Args:
            x: Input node feature tensor
            
        Returns:
            Node feature tensor with dimension adjusted to self.feature_dim
        """
        N, current_dim = x.shape
        
        # If dimensions match, no adjustment needed
        if current_dim == self.feature_dim:
            return x
        
        # Create a new tensor with the expected dimension
        new_x = torch.zeros(N, self.feature_dim, dtype=x.dtype, device=x.device)
        
        # Copy existing features (truncating or padding as needed)
        min_dim = min(current_dim, self.feature_dim)
        new_x[:, :min_dim] = x[:, :min_dim]
        
        return new_x

    def summarize_sizes(self,
                        sample: int = 200,
                        use_cache_only: bool = True,
                        bins_nodes: Tuple[int, ...] = (0, 10, 20, 40, 80, 160, 320, 640, 1_000_000),
                        bins_edges: Tuple[int, ...] = (0, 20, 40, 80, 160, 320, 640, 1_280, 10_000)):
        """
        Generate a summary of graph size statistics.
        
        Args:
            sample: Maximum number of graphs to inspect
            use_cache_only: Whether to only use cached graphs (faster, non-destructive)
            bins_nodes: Bin edges for node count histogram
            bins_edges: Bin edges for edge count histogram
        """
        from collections import Counter
        import numpy as np

        # Validate input parameters
        sample = max(1, min(sample, len(self.rows)))
        bins_nodes = tuple(sorted(bins_nodes))
        bins_edges = tuple(sorted(bins_edges))
        
        ns, es = [], []
        node_counts = Counter()
        edge_counts = Counter()
        checked = 0

        # Prepare vocab mappings for type coverage
        node_id2name = {v: k for k, v in (self.node_vocab or {}).items()}
        edge_id2name = {v: k for k, v in (self.edge_vocab or {}).items()}

        # Get cache instance
        zc = self._get_zip_cache()
        if zc is None and use_cache_only:
            logger.warning("No cache available for summarize_sizes. Cannot proceed with use_cache_only=True.")
            print("[Summ] No cache available and use_cache_only=True. Exiting.")
            return

        # Sample graphs for statistics
        for ridx, r in enumerate(self.rows):
            if checked >= sample:
                break

            p = self._first_existing(self._resolve_candidates(r))
            if p is None:
                logger.debug(f"Skipping row {ridx} as no JSON path found.")
                continue

            d = None
            entry = None

            # Try to load from cache
            if zc is not None:
                entry = self._graph_cache_key(p)
                if entry and zc.contains(entry):
                    raw = zc.load(entry)
                    if raw is not None:
                        try:
                            d = pickle.loads(raw)
                            logger.debug(f"Loaded graph {entry} from cache for stats.")
                        except Exception as e:
                            logger.error(f"[Summ][WARN] zip cache load failed for {entry}: {e}")
                            d = None

            # Parse if not in cache and cache-only is disabled
            if d is None and not use_cache_only:
                try:
                    # CHANGED: Always use dense features (one_hot=False)
                    d = _parse_graphson(
                        p,
                        node_vocab=self.node_vocab,
                        edge_vocab=self.edge_vocab,
                        debug_prefix="SummParse",
                        strict=False,
                        min_nodes=0,
                        one_hot=False,  # CHANGED: Always use dense features
                        fallback_feature_dim=self.feature_dim,
                        expected_feature_dim=self.feature_dim
                    )
                    if zc is not None and entry:
                        try:
                            buf = pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
                            zc.store(entry, buf)
                            logger.debug(f"Stored graph {entry} to cache after stats parsing.")
                        except Exception as e:
                            logger.warning(f"Failed to store graph to cache after stats parsing for {p} ({entry}): {e}")
                except Exception as e:
                    logger.error(f"[Summ][SKIP] parse failed for {p}: {e}")
                    continue

            # Skip if graph could not be loaded
            if d is None:
                logger.debug(f"Skipping row {ridx} as graph could not be loaded/parsed.")
                continue

            # Extract graph statistics
            n = int(getattr(d, "num_nodes", 0))
            e = int(d.edge_index.size(1)) if hasattr(d, "edge_index") else 0
            ns.append(n)
            es.append(e)

            # Count node and edge types
            for attr in ("node_type", "node_type_ids"):
                if hasattr(d, attr):
                    for t in getattr(d, attr).view(-1).tolist():
                        node_counts[t] += 1
                    break

            for attr in ("edge_type", "edge_type_ids"):
                if hasattr(d, attr):
                    for t in getattr(d, attr).view(-1).tolist():
                        edge_counts[t] += 1
                    break

            checked += 1

        # Early exit if no graphs were inspected
        if not ns:
            print("[Summ] No graphs inspected (likely no cache and use_cache_only=True).")
            return

        # Convert to numpy arrays for statistics
        ns_arr = np.array(ns, dtype=np.int64)
        es_arr = np.array(es, dtype=np.int64)

        # Helper function for percentile reporting
        def _pct(x):
            return np.percentile(x, [1, 5, 50, 95, 99]).tolist()

        # Print size statistics
        print("\n========== Dataset size summary ==========")
        print(f"Samples inspected: {checked}")
        print(f"Nodes: mean={ns_arr.mean():.2f}  min={ns_arr.min()}  max={ns_arr.max()}  q01,q05,med,q95,q99={_pct(ns_arr)}")
        print(f"Edges: mean={es_arr.mean():.2f}  min={es_arr.min()}  max={es_arr.max()}  q01,q05,med,q95,q99={_pct(es_arr)}")

        # Generate histograms
        hn, _ = np.histogram(ns_arr, bins=np.asarray(bins_nodes))
        he, _ = np.histogram(es_arr, bins=np.asarray(bins_edges))

        # Print node histogram
        print("\nNode histogram (bins -> count):")
        for i in range(len(hn)):
            lo = bins_nodes[i]
            hi = bins_nodes[i + 1]
            print(f"  [{lo:>5}, {hi:>5}) : {int(hn[i])}")

        # Print edge histogram
        print("\nEdge histogram (bins -> count):")
        for i in range(len(he)):
            lo = bins_edges[i]
            hi = bins_edges[i + 1]
            print(f"  [{lo:>5}, {hi:>5}) : {int(he[i])}")

        # Print node type coverage
        if node_counts:
            print("\nTop node types (by id -> count, name if known):")
            for tid, cnt in node_counts.most_common(15):
                nm = node_id2name.get(tid, "<unk>")
                print(f"  node_type {tid:>2} ({nm:>18}) : {cnt}")
        else:
            print("\nNo node_type tensor found on parsed graphs (skipping node type coverage).")

        # Print edge type coverage
        if edge_counts:
            print("\nTop edge types (by id -> count, name if known):")
            for tid, cnt in edge_counts.most_common(15):
                nm = edge_id2name.get(tid, "<unk>")
                print(f"  edge_type {tid:>2} ({nm:>18}) : {cnt}")
        else:
            print("\nNo edge_type tensor found on parsed graphs (skipping edge type coverage).")

        print("==========================================\n")

    def __str__(self) -> str:
        """Return a string representation of the dataset."""
        return f"DraperDataset(total={len(self)}, feature_dim={self.feature_dim}, cache={'enabled' if self.cache_dir else 'disabled'})"

    def __repr__(self) -> str:
        """Return a detailed string representation of the dataset."""
        return (f"DraperDataset("
                f"manifest_csv={len(self.rows)} rows, "
                f"json_root={self.json_root}, "
                f"feature_dim={self.feature_dim}, "
                f"cache_dir={self.cache_dir}, "
                f"cache_shards={self.cache_shards})")

def graph_collate(batch: List[Data]) -> Batch:
    """Collate function for DataLoader that preserves graph structure."""
    return Batch.from_data_list(batch)

# ────────────────────────────────────────────
# Vocab builder (from TRAIN split)
# ────────────────────────────────────────────
def _build_vocabs_from_train_ds(train_ds: DraperDataset, disable_progress: bool = True):
    node_set, edge_set = set(), set()
    total = len(train_ds.rows)
    for r in _tqdm(train_ds.rows, desc="Build vocabs (train)", disable=disable_progress, total=total):
        p = train_ds._first_existing(train_ds._resolve_candidates(r))
        if p is None:
            continue
        try:
            with open(p, "r", encoding="utf-8") as f:
                g = json.load(f)
            nodes = g.get("nodes") or g.get("Vertices") or []
            edges = g.get("edges") or g.get("Edges") or g.get("@value", {}).get("edges") or []
            for n in nodes:
                lab = n.get("label", "")
                if lab: node_set.add(str(lab))
            for e in edges:
                inv = e.get("inVLabel"); outv = e.get("outVLabel")
                if inv:  node_set.add(str(inv))
                if outv: node_set.add(str(outv))
                elab = e.get("label") or e.get("edgeLabel") or e.get("type") or e.get("rel")
                if elab: edge_set.add(str(elab))
        except Exception:
            continue
    node_vocab = {lab: i for i, lab in enumerate(sorted(node_set))}
    edge_vocab = {"UNK": 0}
    for lab in sorted(edge_set):
        if lab != "UNK":
            edge_vocab[lab] = len(edge_vocab)
    return {"node_vocab": node_vocab, "edge_vocab": edge_vocab}


def _vocab_signature(node_vocab: dict, edge_vocab: dict) -> str:
    import hashlib, json
    # stable, order-independent hash
    ns = json.dumps(sorted(node_vocab.items()), separators=(",", ":"), ensure_ascii=True)
    es = json.dumps(sorted(edge_vocab.items()), separators=(",", ":"), ensure_ascii=True)
    h = hashlib.md5()
    h.update(ns.encode("utf-8")); h.update(b"|"); h.update(es.encode("utf-8"))
    return h.hexdigest()[:8]



def ensure_vocabs(args, layout, train_ds: DraperDataset):
    vocab_dir = layout["vocab"]
    node_json = vocab_dir / "node_vocab.json"
    edge_json = vocab_dir / "edge_vocab.json"
    node_pkl  = vocab_dir / "node_vocab.pkl"
    edge_pkl  = vocab_dir / "edge_vocab.pkl"

    if not getattr(args, "rebuild_vocabs", False):
        if node_pkl.exists() and edge_pkl.exists():
            with open(node_pkl, "rb") as f: node_vocab = pickle.load(f)
            with open(edge_pkl, "rb") as f: edge_vocab = pickle.load(f)
            print(f"[Vocab] Loaded (PKL) node={len(node_vocab)} edge={len(edge_vocab)} from {vocab_dir}")
            if (len(node_vocab) == 0 or len(edge_vocab) == 0) and not getattr(args, "allow_empty_vocabs", False):
                print("[Vocab][WARN] Empty vocabs → rebuilding")
            else:
                return {"node_vocab": node_vocab, "edge_vocab": edge_vocab}
        if node_json.exists() and edge_json.exists():
            with open(node_json, "r", encoding="utf-8") as f: node_vocab = json.load(f)
            with open(edge_json, "r", encoding="utf-8") as f: edge_vocab = json.load(f)
            print(f"[Vocab] Loaded (JSON) node={len(node_vocab)} edge={len(edge_vocab)} from {vocab_dir}")
            if (len(node_vocab) == 0 or len(edge_vocab) == 0) and not getattr(args, "allow_empty_vocabs", False):
                print("[Vocab][WARN] Empty vocabs → rebuilding")
            else:
                with open(node_pkl, "wb") as f: pickle.dump(node_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
                with open(edge_pkl, "wb") as f: pickle.dump(edge_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
                return {"node_vocab": node_vocab, "edge_vocab": edge_vocab}

    print("[Vocab] Building from TRAIN")
    vocabs = _build_vocabs_from_train_ds(train_ds, disable_progress=getattr(args, "no_progress", False))
    node_vocab = vocabs.get("node_vocab", {})
    edge_vocab = vocabs.get("edge_vocab", {})
    try:
        with open(node_json, "w", encoding="utf-8") as f: json.dump(node_vocab, f)
        with open(edge_json, "w", encoding="utf-8") as f: json.dump(edge_vocab, f)
        with open(node_pkl, "wb") as f: pickle.dump(node_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
        with open(edge_pkl, "wb") as f: pickle.dump(edge_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
        print(f"[Vocab] Saved to {vocab_dir}")
    except Exception as e:
        print(f"[Vocab][WARN] Save error: {e}")
    return {"node_vocab": node_vocab, "edge_vocab": edge_vocab}


# Add this function to handle cache migration
def migrate_cache(old_cache_dir: Path, new_cache_dir: Path):
    """Migrate cache from old location to new location without deleting old cache."""
    if not old_cache_dir.exists():
        logger.info(f"Old cache directory not found: {old_cache_dir}")
        return
    
    logger.info(f"Starting cache migration from {old_cache_dir} to {new_cache_dir}")
    
    # Create new cache directory if needed
    new_cache_dir.mkdir(parents=True, exist_ok=True)
    
    # Copy all cache files
    try:
        # If using sharded cache
        old_shards = list(old_cache_dir.glob("shards/*.zip"))
        if old_shards:
            new_shards_dir = new_cache_dir / "shards"
            new_shards_dir.mkdir(parents=True, exist_ok=True)
            
            for shard in old_shards:
                shutil.copy2(shard, new_shards_dir)
            logger.info(f"  - Copied {len(old_shards)} shard files")
        
        # If using single file cache
        old_cache = old_cache_dir / "graph_cache.zip"
        if old_cache.exists():
            shutil.copy2(old_cache, new_cache_dir)
            logger.info("  - Copied single cache file")
        
        # Copy cache metadata
        for meta_file in ["cache_version.txt", "index_valid.txt"]:
            meta_path = old_cache_dir / meta_file
            if meta_path.exists():
                shutil.copy2(meta_path, new_cache_dir)
        
        logger.info(f"Cache migration complete. Old cache remains at {old_cache_dir}")
        logger.info(f"New cache is now at {new_cache_dir}")
    except Exception as e:
        logger.error(f"Cache migration failed: {e}")
        logger.info("Proceeding with fresh cache in new location")

# ────────────────────────────────────────────
# Models (Baselines + Wrapped) → return dict(logits, emb)
# ────────────────────────────────────────────
def _readout(x, batch, how="mean"):
    if how == "mean": return global_mean_pool(x, batch)
    if how == "max":  return global_max_pool(x, batch)
    return global_add_pool(x, batch)

class GCNBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, layers=3, readout="mean", dropout=0.1):
        super().__init__()
        self.layers = nn.ModuleList([GCNConv(in_dim, hidden_dim)] + [GCNConv(hidden_dim, hidden_dim) for _ in range(layers-1)])
        self.bns = nn.ModuleList([BatchNorm(hidden_dim) for _ in range(layers)])
        self.dropout = dropout; self.readout = readout
        self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))
    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        for c, bn in zip(self.layers, self.bns):
            x = F.relu(bn(c(x, ei)))
            x = F.dropout(x, p=self.dropout, training=self.training)
        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class GATBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, heads=2, layers=3, readout="mean", dropout=0.1):
        super().__init__()
        self.layers = nn.ModuleList()
        self.layers.append(GATConv(in_dim, hidden_dim//heads, heads=heads, concat=True))
        for _ in range(layers-1):
            self.layers.append(GATConv(hidden_dim, hidden_dim//heads, heads=heads, concat=True))
        self.bns = nn.ModuleList([BatchNorm(hidden_dim) for _ in range(layers)])
        self.dropout = dropout; self.readout = readout
        self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))
    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        for c, bn in zip(self.layers, self.bns):
            x = F.elu(bn(c(x, ei)))
            x = F.dropout(x, p=self.dropout, training=self.training)
        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class SAGEBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, layers=3, readout="mean", dropout=0.1):
        super().__init__()
        self.layers = nn.ModuleList([SAGEConv(in_dim, hidden_dim)] + [SAGEConv(hidden_dim, hidden_dim) for _ in range(layers-1)])
        self.bns = nn.ModuleList([BatchNorm(hidden_dim) for _ in range(layers)])
        self.dropout = dropout; self.readout = readout
        self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))
    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        for c, bn in zip(self.layers, self.bns):
            x = F.relu(bn(c(x, ei)))
            x = F.dropout(x, p=self.dropout, training=self.training)
        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class GINBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, layers=4, readout="mean", dropout=0.1):
        super().__init__()
        def mlp(i,o): return nn.Sequential(nn.Linear(i,o), nn.ReLU(), nn.Linear(o,o))
        self.layers = nn.ModuleList([GINConv(mlp(in_dim, hidden_dim))] + [GINConv(mlp(hidden_dim, hidden_dim)) for _ in range(layers-1)])
        self.bns = nn.ModuleList([BatchNorm(hidden_dim) for _ in range(layers)])
        self.dropout = dropout; self.readout = readout
        self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))
    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        for c, bn in zip(self.layers, self.bns):
            x = F.relu(bn(c(x, ei)))
            x = F.dropout(x, p=self.dropout, training=self.training)
        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class PNABaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, layers=4, readout="mean", dropout=0.1, deg_hist: Optional[torch.Tensor]=None):
        super().__init__()
        assert layers >= 1, "PNABaseline: layers must be >= 1"

        aggregators = ["mean", "min", "max", "std"]
        scalers = ["identity", "amplification", "attenuation"]

        self.convs = nn.ModuleList()
        self.bns   = nn.ModuleList()

        if deg_hist is None:
            deg_hist = torch.tensor([1.0], dtype=torch.float)

        self.convs.append(
            PNAConv(
                in_dim,
                hidden_dim,
                aggregators=aggregators,
                scalers=scalers,
                deg=deg_hist
            )
        )
        self.bns.append(BatchNorm(hidden_dim))

        for _ in range(layers - 1):
            self.convs.append(
                PNAConv(
                    hidden_dim,
                    hidden_dim,
                    aggregators=aggregators,
                    scalers=scalers,
                    deg=deg_hist
                )
            )
            self.bns.append(BatchNorm(hidden_dim))

        self.dropout = float(dropout)
        self.readout = readout
        self.head = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Dropout(self.dropout),
            nn.Linear(hidden_dim, out_dim)
        )

    # --- ADD this helper inside the class ---
    def forward_features(self, data):
        # 1) run your existing message-passing stack to get node embeddings
        x = data.x
        edge_index = data.edge_index
        edge_attr = getattr(data, "edge_attr", None)
        # (Use your own layers; the following line(s) are placeholders.)
        for layer in self.gnn_layers:
            # adapt the call signature to your layer type (PNA/GIN/etc.)
            x = layer(x, edge_index, edge_attr) if edge_attr is not None else layer(x, edge_index)

        # 2) pool to a graph-level vector (match your current readout)
        batch = getattr(data, "batch", None)
        if batch is None:
            # single-graph fallback
            g = x.mean(dim=0, keepdim=True)
        else:
            from torch_geometric.nn import global_mean_pool
            if getattr(self, "readout", "mean") == "sum":
                from torch_geometric.nn import global_add_pool
                g = global_add_pool(x, batch)
            else:
                g = global_mean_pool(x, batch)
        return g

    # --- REPLACE your existing forward() with this one ---
    def forward(self, data):
        g = self.forward_features(data)                     # graph embedding
        # your existing classifier head (keep exactly as you had)
        logits = self.head(F.dropout(g, p=self.dropout, training=self.training))
        return {"logits": logits, "emb": g}


class DeeperGCNBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, layers=8, readout="mean", dropout=0.1, norm_type="batch"):
        super().__init__()
        if not HAS_DEEP:
            raise RuntimeError("GENConv/DeepGCN not available in this torch-geometric version.")
        self.input = nn.Linear(in_dim, hidden_dim)
        self.layers = nn.ModuleList()
        for _ in range(layers):
            conv = GENConv(hidden_dim, hidden_dim, aggr="softmax", t=1.0, learn_t=True, num_layers=2)
            norm = nn.BatchNorm1d(hidden_dim) if norm_type == "batch" else nn.LayerNorm(hidden_dim)
            act = nn.ReLU(inplace=True)
            self.layers.append(DeepGCNLayer(conv, norm, act, block="res", dropout=dropout))
        self.dropout = dropout; self.readout = readout
        self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))
    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        x = self.input(x)
        for layer in self.layers:
            x = layer(x, ei)
        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class MPNNBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, edge_dim=8, layers=3,
                 readout="mean", dropout=0.1, num_relations: int = 0):
        super().__init__()
        if not HAS_NNCONV:
            raise RuntimeError("NNConv not available; please upgrade torch-geometric.")
        self.edge_dim = int(edge_dim)
        self.readout = readout
        self.dropout = float(dropout)
        self.edge_emb = nn.Embedding(int(num_relations), self.edge_dim) if int(num_relations) > 0 else None

        self.proj_in = nn.Linear(in_dim, hidden_dim)
        self.convs = nn.ModuleList()
        self.nn_edges = nn.ModuleList()
        for _ in range(layers):
            self.nn_edges.append(nn.Sequential(
                nn.Linear(self.edge_dim, hidden_dim * hidden_dim)
            ))
            self.convs.append(NNConv(hidden_dim, hidden_dim, self.nn_edges[-1], aggr='mean'))

        self.act = nn.ReLU(inplace=True)
        self.read = global_mean_pool if readout == "mean" else global_add_pool
        self.head = nn.Sequential(
            nn.Dropout(self.dropout),
            nn.Linear(hidden_dim, out_dim)
        )

    def forward(self, data):
        x, ei = data.x, data.edge_index
        rel = getattr(data, "edge_type", None)
        eattr = getattr(data, "edge_attr", None)
        if eattr is None:
            if self.edge_emb is not None and rel is not None:
                eattr = self.edge_emb(rel.clamp_min(0))
            else:
                eattr = x.new_zeros((ei.size(1), self.edge_dim))

        h = self.proj_in(x)
        for conv in self.convs:
            h = self.act(conv(h, ei, eattr))
        g = self.read(h, data.batch)
        logits = self.head(g)

        return {"logits": logits, "emb": g}




class RGcnBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=128, out_dim=2, num_relations: int = 1, layers=3, readout="mean", dropout=0.1):
        super().__init__()
        self.num_relations = max(1, int(num_relations))
        self.layers = nn.ModuleList(
            [RGCNConv(in_dim, hidden_dim, num_relations=self.num_relations)] +
            [RGCNConv(hidden_dim, hidden_dim, num_relations=self.num_relations) for _ in range(layers-1)]
        )
        self.bns = nn.ModuleList([BatchNorm(hidden_dim) for _ in range(layers)])
        self.dropout = float(dropout)
        self.readout = readout
        self.head = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(inplace=True),
            nn.Dropout(self.dropout),
            nn.Linear(hidden_dim, out_dim)
        )

    def forward(self, data: Data):
        x, ei, ba = data.x, data.edge_index, data.batch
        rel = getattr(data, "edge_type", None)
        if rel is None:
            rel = torch.zeros(ei.size(1), dtype=torch.long, device=ei.device)
        rel = rel.clamp_(0, self.num_relations - 1)

        for c, bn in zip(self.layers, self.bns):
            x = c(x, ei, rel)
            x = bn(x)
            x = F.relu(x, inplace=True)
            x = F.dropout(x, p=self.dropout, training=self.training)

        g = _readout(x, ba, self.readout)
        return {"logits": self.head(g), "emb": g}

DGCNNBaseline = DeeperGCNBaseline  # alias


# Advanced (optional) layers
from torch_geometric.nn import ChebConv
try:
    from torch_geometric.nn import HANConv
    HAS_HAN = True
except Exception:
    HAS_HAN = False

try:
    from torch_geometric.nn import HGTConv
    HAS_HGT = True
except Exception:
    HAS_HGT = False


# ────────────────────────────────────────────
# MPTCN-TTS (aligned, homogeneous) → returns (logits, emb)
# ────────────────────────────────────────────
class MPTCN_TTS(nn.Module):
    def __init__(
        self,
        in_dim,
        hidden_dim=256,
        out_dim=2,
        spatial="gcn",
        Ls=2,
        Lt=2,
        heads=2,
        bases=4,           # <- will be set to num_relations by run(args) for RGCN
        dropout=0.3,
        readout="mean",
        temporal="tcn",    # <- accept temporal kind flag (e.g., "gru")
    ):
        super().__init__()
        self.spatial = str(spatial).lower()
        self.temporal_kind = str(temporal).lower()
        self.readout = readout
        self.dropout = float(dropout)
        self.Ls = int(Ls)
        self.Lt = int(Lt)
        self.heads = int(heads)
        self.bases = int(max(1, bases))  # interpreted as num_relations when spatial="rgcn"

        # ---- Spatial stack ----
        self.s_layers = nn.ModuleList()
        self.s_bns = nn.ModuleList()
        dim_in, dim_h = int(in_dim), int(hidden_dim)

        for li in range(self.Ls):
            in_ch = dim_in if li == 0 else dim_h
            if self.spatial == "gcn":
                conv = GCNConv(in_ch, dim_h)
            elif self.spatial == "gat":
                conv = GATConv(in_ch, dim_h // self.heads, heads=self.heads, concat=True)
            elif self.spatial == "sage":
                conv = SAGEConv(in_ch, dim_h)
            elif self.spatial == "cheb":
                conv = ChebConv(in_ch, dim_h, K=3)
            elif self.spatial == "rgcn":
                # Use bases as num_relations; runner sets bases=num_relations
                conv = RGCNConv(in_ch, dim_h, num_relations=self.bases)
            else:
                conv = GCNConv(in_ch, dim_h)
            self.s_layers.append(conv)
            self.s_bns.append(BatchNorm(dim_h))

        # ---- Temporal stack ----
        self.temporal = nn.ModuleList()
        if self.temporal_kind == "gru":
            # Lightweight GRU blocks over the per-graph embedding
            for _ in range(self.Lt):
                self.temporal.append(nn.GRU(input_size=dim_h, hidden_size=dim_h, batch_first=True))
        else:
            # Default: residual MLP blocks ("tcn"-like head)
            for _ in range(self.Lt):
                self.temporal.append(nn.Sequential(
                    nn.Linear(dim_h, dim_h),
                    nn.ReLU(inplace=True),
                    nn.Dropout(self.dropout),
                    nn.Linear(dim_h, dim_h),
                ))

        # ---- Classifier head ----
        self.head = nn.Sequential(
            nn.Linear(dim_h, dim_h),
            nn.ReLU(inplace=True),
            nn.Dropout(self.dropout),
            nn.Linear(dim_h, out_dim),
        )

    def forward(self, data: Data):
        x, ei = data.x, data.edge_index
        # default a batch vector if missing (single-graph fallback)
        ba = getattr(data, "batch", torch.zeros(x.size(0), dtype=torch.long, device=x.device))
        rel = getattr(data, "edge_type", None)

        # ── Spatial message passing ───────────────────────────────────────
        for conv, bn in zip(self.s_layers, self.s_bns):
            if isinstance(conv, RGCNConv):
                # ensure we have a relation tensor
                if rel is None:
                    rel = torch.zeros(ei.size(1), dtype=torch.long, device=ei.device)

                # SAFETY 1: keep edge_type length in sync with edge_index
                if rel.numel() != ei.size(1):
                    M = min(rel.numel(), ei.size(1))
                    ei = ei[:, :M]
                    rel = rel[:M]

                # SAFETY 2: clamp relation ids into valid range [0, bases-1]
                rel = rel.clamp_(0, max(1, self.bases) - 1)

                x = conv(x, ei, rel)
            else:
                x = conv(x, ei)

            x = F.relu(bn(x), inplace=True)
            x = F.dropout(x, p=self.dropout, training=self.training)

        # ── Graph readout ────────────────────────────────────────────────
        g = _readout(x, ba, self.readout)

        # ── Temporal mixing ──────────────────────────────────────────────
        for block in self.temporal:
            if isinstance(block, nn.GRU):
                # Treat per-graph embedding as a length-1 sequence
                z, _ = block(g.unsqueeze(1))   # (B, 1, D)
                z = z.squeeze(1)               # (B, D)
            else:
                z = block(g)
            g = F.relu(g + z, inplace=True)
            g = F.dropout(g, p=self.dropout, training=self.training)

        logits = self.head(g)
        return {"logits": logits, "emb": g}


# HGT & HAN wrappers
class HGTBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=256, out_dim=2, layers=2, heads=1, dropout=0.3, readout="mean"):
        super().__init__()
        self.readout = readout; self.dropout = dropout; self.use_fallback = not HAS_HGT
        if self.use_fallback:
            self.fallback = GATBaseline(in_dim, hidden_dim, out_dim, heads=heads, layers=max(2,layers), readout=readout, dropout=dropout)
        else:
            self.inp = nn.Linear(in_dim, hidden_dim)
            self.convs = nn.ModuleList(); self.norms = nn.ModuleList()
            for _ in range(layers):
                self.convs.append(HGTConv(in_channels=hidden_dim, out_channels=hidden_dim,
                                          metadata=(['n'], [('n','e','n')]), heads=heads))
                self.norms.append(nn.LayerNorm(hidden_dim))
            self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))

    def forward(self, data: Data):
        if self.use_fallback:
            return self.fallback(data)
        x, ei = data.x, data.edge_index
        ba = getattr(data, "batch", torch.zeros(x.size(0), dtype=torch.long, device=x.device))
        x = self.inp(x)
        x_dict = {'n': x}; ei_dict = {('n','e','n'): ei}
        for conv, ln in zip(self.convs, self.norms):
            x_dict = conv(x_dict, ei_dict)
            h = x_dict['n']; h = F.relu(ln(h)); h = F.dropout(h, p=self.dropout, training=self.training)
            x_dict['n'] = h
        g = _readout(x_dict['n'], ba, self.readout)
        return {"logits": self.head(g), "emb": g}

class HANBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=256, out_dim=2, layers=2, heads=2, dropout=0.3, readout="mean"):
        super().__init__()
        self.readout = readout; self.dropout = dropout; self.use_fallback = not HAS_HAN
        if self.use_fallback:
            self.fallback = GATBaseline(in_dim, hidden_dim, out_dim, heads=heads, layers=max(2,layers), readout=readout, dropout=dropout)
        else:
            self.inp = nn.Linear(in_dim, hidden_dim)
            self.hans = nn.ModuleList(); metapaths = [[('n','e','n')]]
            for _ in range(layers):
                self.hans.append(HANConv(in_channels=hidden_dim, out_channels=hidden_dim, metapaths=metapaths, heads=heads))
            self.head = nn.Sequential(nn.Linear(hidden_dim, hidden_dim), nn.ReLU(), nn.Dropout(dropout), nn.Linear(hidden_dim, out_dim))

    def forward(self, data: Data):
        if self.use_fallback:
            return self.fallback(data)
        x, ei = data.x, data.edge_index
        ba = getattr(data, "batch", torch.zeros(x.size(0), dtype=torch.long, device=x.device))
        h = self.inp(x)
        x_dict = {'n': h}; ei_dict = {('n','e','n'): ei}
        for han in self.hans:
            x_dict = han(x_dict, ei_dict)
            h = x_dict['n']; h = F.relu(h); h = F.dropout(h, p=self.dropout, training=self.training)
            x_dict['n'] = h
        g = _readout(x_dict['n'], ba, self.readout)
        return {"logits": self.head(g), "emb": g}


# ────────────────────────────────────────────
# Probabilities / Calibration / Temperature
# ────────────────────────────────────────────
def _delta_from_logits(logits: torch.Tensor) -> torch.Tensor:
    if logits.size(-1) == 1: return logits.view(-1)
    return (logits[:,1] - logits[:,0]).view(-1)

def _probs_from_logits_binary(logits: torch.Tensor, T: float = 1.0) -> torch.Tensor:
    """
    Convert logits to binary probabilities with temperature scaling.
    
    Args:
        logits: Raw model outputs (can be 1D or 2D)
        T: Temperature for scaling (T > 0)
    
    Returns:
        Probabilities in [0, 1]
    """
    # Ensure temperature is valid
    T = max(1e-3, T)
    
    # Handle different shapes of logits
    if logits.dim() == 1:
        # Binary classification with single logit
        probs = torch.sigmoid(logits / T)
    elif logits.dim() == 2 and logits.size(1) == 1:
        # Binary classification with 2D tensor
        probs = torch.sigmoid(logits[:, 0] / T)
    elif logits.dim() == 2 and logits.size(1) == 2:
        # Binary classification with two logits
        probs = torch.softmax(logits / T, dim=1)[:, 1]
    else:
        raise ValueError(f"Unexpected logits shape: {logits.shape}")
    
    # Add numerical stability
    probs = torch.clamp(probs, 1e-7, 1 - 1e-7)
    
    return probs

def _fit_temperature(y_true: np.ndarray, y_prob: np.ndarray, beta: float = 0.6) -> float:
    """
    Fit temperature scaling to maximize F1 score.
    
    Args:
        y_true: True binary labels
        y_prob: Predicted probabilities
        beta: Beta parameter for F1 score
    
    Returns:
        Optimized temperature value
    """
    # Skip fitting if probabilities are already binary or constant
    if np.unique(y_prob).size <= 2 or np.std(y_prob) < 1e-6:
        return 1.0
    
    # Define temperature search space
    T_candidates = np.logspace(-1, 1, 21)  # 0.1 to 10.0
    best_T = 1.0
    best_f1 = 0.0
    
    # Find optimal temperature
    for T in T_candidates:
        # Apply temperature scaling
        z = np.log(y_prob) - np.log(1 - y_prob)
        z_scaled = z / T
        y_pred = 1.0 / (1.0 + np.exp(-z_scaled))
        y_pred_binary = (y_pred >= 0.5).astype(int)
        
        # Calculate F1 score
        p, r, f1 = _prf(y_true, y_pred_binary, beta)
        
        if f1 > best_f1:
            best_f1 = f1
            best_T = T
    
    # Ensure temperature is within reasonable bounds
    best_T = max(0.1, min(10.0, best_T))
    
    if best_T != 1.0:
        logger.info(f"Fitted temperature T={best_T:.3f} (F1={best_f1:.4f})")
    
    return best_T

def transform_threshold_preT_to_postT(thr_preT: float, T: float) -> float:
    """
    Transform a threshold from pre-temperature space to post-temperature space.
    
    Args:
        thr_preT: Threshold in pre-temperature space
        T: Temperature used for scaling
    
    Returns:
        Equivalent threshold in post-temperature space
    """
    thr_preT = float(np.clip(thr_preT, 1e-6, 1 - 1e-6))
    z_pre = float(np.log(thr_preT) - np.log(1 - thr_preT))
    z_post = z_pre / float(max(1e-3, T))
    thr_post = 1.0 / (1.0 + math.exp(-z_post))
    return float(np.clip(thr_post, 1e-6, 1 - 1e-6))

def clamp01_np(x: np.ndarray) -> np.ndarray:
    return np.minimum(1.0, np.maximum(0.0, x))

def decide_from_prob(y_prob: np.ndarray, thr: float) -> np.ndarray:
    return (y_prob >= float(thr)).astype(np.int64)

class TemperatureScaler(nn.Module):
    def __init__(self, init_T: float = 1.0):
        super().__init__()
        self.log_T = nn.Parameter(torch.tensor(math.log(max(1e-3, init_T)), dtype=torch.float))
    @property
    def T(self) -> torch.Tensor:
        return torch.exp(self.log_T)
    def forward(self, logits: torch.Tensor) -> torch.Tensor:
        return logits / self.T

@torch.no_grad()
def fit_temperature(model: nn.Module, loader: GeoDataLoader, device: torch.device, max_iter: int = 200, lr: float = 1e-2) -> float:
    scaler = TemperatureScaler(1.0).to(device)
    opt = torch.optim.LBFGS(scaler.parameters(), lr=lr, max_iter=max_iter, line_search_fn="strong_wolfe")
    nll = nn.BCEWithLogitsLoss(reduction="mean")

    model.eval()
    Ls, Ys = [], []
    for batch in loader:
        b = batch.to(device, non_blocking=True)
        out = model(b)
        logits = out["logits"] if isinstance(out, dict) else out
        gap = _delta_from_logits(logits).unsqueeze(-1)
        gap = torch.nan_to_num(gap, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-30, 30)
        Ls.append(gap)
        Ys.append(b.y.float().view(-1,1))
    if not Ls:
        return 1.0
    L = torch.cat(Ls, dim=0); Y = torch.cat(Ys, dim=0)

    def closure():
        opt.zero_grad(set_to_none=True)
        logits_scaled = scaler(L)
        loss = nll(logits_scaled, Y)
        if not torch.isfinite(loss):
            # return a small finite loss to keep LBFGS stable
            return torch.tensor(0.0, device=device, requires_grad=True)
        loss.backward()
        return loss

    try:
        opt.step(closure)
        T = float(torch.clamp(scaler.T.detach(), 0.1, 10.0).item())
        tqdm.write(f"[Temp] Fitted temperature T={T:.3f}")
        return T
    except Exception:
        return 1.0




def transform_threshold_preT_to_postT(thr_preT: float, T: float) -> float:
    thr_preT = float(np.clip(thr_preT, 1e-6, 1 - 1e-6))
    z_pre = float(np.log(thr_preT) - np.log(1 - thr_preT))
    z_post = z_pre / float(max(1e-3, T))
    thr_post = 1.0 / (1.0 + math.exp(-z_post))
    return float(np.clip(thr_post, 1e-6, 1 - 1e-6))

@dataclass
class CalibConfig:
    beta: float = 1.0
    min_precision: Optional[float] = None
    max_pos_rate_over_base: float = 3.0
    min_pos_frac: float = 0.02
    ema_alpha: float = 0.6

def _prf(y_true: np.ndarray, y_pred: np.ndarray, beta: float) -> Tuple[float,float,float]:
    tp = int(((y_true == 1) & (y_pred == 1)).sum())
    fp = int(((y_true == 0) & (y_pred == 1)).sum())
    fn = int(((y_true == 1) & (y_pred == 0)).sum())
    p = tp / (tp + fp) if (tp + fp) > 0 else 0.0
    r = tp / (tp + fn) if (tp + fn) > 0 else 0.0
    if p == 0.0 and r == 0.0:
        f = 0.0
    else:
        b2 = beta * beta
        f = (1 + b2) * p * r / (b2 * p + r + 1e-12)
    return p, r, f

def _pr_sweep(y_true: np.ndarray, y_prob: np.ndarray, beta: float,
              min_precision: Optional[float], min_recall: Optional[float] = None) -> Tuple[float, Dict[str, float]]:
    y_true = y_true.astype(np.int64)
    y_prob = clamp01_np(y_prob.astype(np.float64))
    if y_prob.size == 0:
        return 0.5, {"f":0.0, "p":0.0, "r":0.0, "thr":0.5}

    uniq = np.unique(y_prob)
    qgrid = np.linspace(0.0, 1.0, num=min(201, max(21, len(uniq)*2)))
    cand = np.unique(np.concatenate([
        uniq,
        np.quantile(y_prob, qgrid, method="linear"),
        np.array([1e-6, 0.5, 1-1e-6], dtype=np.float64)
    ]))

    best = {"f": -1.0, "p": 0.0, "r": 0.0, "thr": 0.5}
    best_any = {"f": -1.0, "p": 0.0, "r": 0.0, "thr": 0.5}
    for thr in cand:
        y_pred = (y_prob >= thr).astype(np.int64)
        p, r, f = _prf(y_true, y_pred, beta)
        if f > best_any["f"]:
            best_any.update({"f":float(f),"p":float(p),"r":float(r),"thr":float(thr)})
        if (min_precision is not None) and (p < min_precision):
            continue
        if (min_recall is not None) and (r < min_recall):
            continue
        if f > best["f"]:
            best.update({"f":float(f),"p":float(p),"r":float(r),"thr":float(thr)})

    return (best_any if best["f"] < 0 else best)["thr"], (best_any if best["f"] < 0 else best)



def calibrate_threshold(y_true: np.ndarray, y_prob: np.ndarray, cfg: CalibConfig, base_rate: Optional[float] = None) -> Tuple[float, Dict[str, float]]:
    y_true = y_true.astype(np.int64)
    y_prob = clamp01_np(y_prob.astype(np.float64))
    base = float(base_rate) if base_rate is not None else float((y_true == 1).mean() if len(y_true) else 0.5)
    thr_raw, stats = _pr_sweep(y_true, y_prob, cfg.beta, cfg.min_precision, getattr(cfg, "min_recall", None))


    pos_rate = float((y_prob >= thr_raw).mean()) if len(y_prob) else 0.5
    max_pos = float(min(1.0, cfg.max_pos_rate_over_base * max(1e-6, base)))
    min_pos = float(max(0.0, cfg.min_pos_frac))

    thr = float(thr_raw)
    if pos_rate > max_pos:
        thr = float(np.quantile(y_prob, 1.0 - max_pos))
    elif pos_rate < min_pos:
        thr = float(np.quantile(y_prob, 1.0 - min_pos))

    thr = float(np.clip(thr, 1e-6, 1 - 1e-6))
    print(f"[Calib] raw_thr={thr_raw:.6f} pos_rate={pos_rate:.4f} base={base:.4f} "
      f"max_pos={(cfg.max_pos_rate_over_base*base):.4f} min_pos={cfg.min_pos_frac:.4f} -> adj_thr={thr:.6f}")

    return thr, {"thr_raw": thr_raw, "thr": thr, "pos_rate": pos_rate, "base": base, **stats}


# ────────────────────────────────────────────
# Contrastive / Prototype utilities
# ────────────────────────────────────────────
def cosine_sim(a, b):
    a = F.normalize(a, dim=-1); b = F.normalize(b, dim=-1)
    return torch.mm(a, b.t())

def supervised_contrastive(
    z: torch.Tensor,
    y: torch.Tensor,
    fid: Optional[torch.Tensor] = None,
    tau: float = 0.1,
    mode: str = "label+family",
):
    """
    z: [N, D], y: [N], fid: [N] (optional)
    Positives: same label (+ same family if mode includes it).
    Numerically-stable, no in-place ops, no 'no positives' rows.
    """
    N = z.size(0)
    if N <= 1:
        return z.new_tensor(0.0)

    # Cosine similarity in fp32, temperature scale (no in-place)
    z = F.normalize(z.float(), dim=-1, eps=1e-5)  # Added eps for zero-norm safety
    sim = torch.matmul(z, z.T) / float(max(1e-6, tau))  # [N, N]

    # Masks
    eye = torch.eye(N, dtype=torch.bool, device=z.device)
    y = y.view(-1)
    mask_label = (y.unsqueeze(0) == y.unsqueeze(1))
    if fid is not None and "family" in mode:
        fmask = (fid.view(-1, 1) == fid.view(1, -1))
        pos_mask = mask_label & fmask
    else:
        pos_mask = mask_label
    pos_mask = pos_mask & (~eye)  # exclude self

    # Rows that actually have ≥1 positive
    valid = pos_mask.any(dim=1)
    if not valid.any():
        return z.new_tensor(0.0)

    # Numerically stable NT-Xent:
    # loss_i = -log( sum_{p in P(i)} exp(s_{i,p}) / sum_{a != i} exp(s_{i,a}) )
    # = -( logsumexp(pos) - logsumexp(all_except_self) )
    neg_inf = torch.finfo(sim.dtype).min
    pos_logits = sim.masked_fill(~pos_mask, neg_inf)     # keep only positives
    all_except_self = sim.masked_fill(eye, neg_inf)      # exclude diagonal

    num = torch.logsumexp(pos_logits, dim=1)             # log Σ exp over positives
    den = torch.logsumexp(all_except_self, dim=1)        # log Σ exp over all except self

    loss_vec = -(num - den)
    loss_vec = loss_vec[valid]                           # keep only valid rows
    return loss_vec.mean()

class PrototypeBank(nn.Module):
    def __init__(self, dim: int, num_classes: int, ema_momentum: float = 0.9):
        super().__init__()
        self.register_buffer("centroids", torch.zeros(num_classes, dim))
        self.register_buffer("counts", torch.zeros(num_classes))
        self.m = float(ema_momentum)
    @torch.no_grad()
    def update(self, z: torch.Tensor, y: torch.Tensor):
        for c in torch.unique(y):
            idx = (y == c).nonzero(as_tuple=False).view(-1)
            if idx.numel() == 0: continue
            mean = z[idx].mean(dim=0)
            self.centroids[c] = self.m * self.centroids[c] + (1 - self.m) * mean
            self.counts[c] = self.counts[c] + float(idx.numel())
    def reg_loss(self, z: torch.Tensor, y: torch.Tensor, weight: float=1.0):
        c = self.centroids[y]  # [N, D]
        return weight * F.mse_loss(z, c, reduction="mean")


# ────────────────────────────────────────────
# Auxiliary Delta Head (pairwise "same label")
# ────────────────────────────────────────────
class DeltaHead(nn.Module):
    def __init__(self, dim: int, hidden: int = 128):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(2*dim, hidden),
            nn.ReLU(inplace=True),
            nn.Linear(hidden, 1)
        )
    def forward(self, z1: torch.Tensor, z2: torch.Tensor):
        # Features: |z1-z2| and z1*z2 concatenated
        feat = torch.cat([torch.abs(z1 - z2), z1 * z2], dim=-1)
        return self.net(feat).view(-1)

# ──────────────────────────────────────────────────────────────
# Gradient Reversal & Domain Adapter
# ──────────────────────────────────────────────────────────────
class _GradReverse(torch.autograd.Function):
    @staticmethod
    def forward(ctx, x, lambd: float):
        ctx.lambd = float(lambd)
        return x.view_as(x)
    @staticmethod
    def backward(ctx, grad):
        return -ctx.lambd * grad, None

def grad_reverse(x, lambd: float = 1.0):
    return _GradReverse.apply(x, float(lambd))

class DomainAdapter(nn.Module):
    def __init__(self, in_dim: int, hidden: int = 128):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(in_dim, hidden),
            nn.ReLU(inplace=True),
            nn.Linear(hidden, 1)  # binary domain logits
        )
    def forward(self, z, lambd: float = 1.0):
        return self.net(grad_reverse(z, lambd=lambd)).view(-1)

# ────────────────────────────────────────────
# Losses
# ────────────────────────────────────────────
def focal_loss(
    logits: torch.Tensor,
    target: torch.Tensor,
    gamma: float = 0.0,
    smoothing: float = 0.0,
    class_weight: Optional[torch.Tensor] = None,
    pos_weight: Optional[float] = None,
):
    # Single-logit binary path
    if logits.size(-1) == 1:
        tgt = target.float().view(-1, 1) if target.dim() == 1 else target.float()
        if smoothing > 0.0:
            # smooth toward 0.5
            tgt = tgt * (1.0 - smoothing) + 0.5 * smoothing
        pw = None
        if pos_weight is not None:
            pw = torch.tensor(float(pos_weight), device=logits.device, dtype=logits.dtype)
        bce = F.binary_cross_entropy_with_logits(logits, tgt, reduction="none", pos_weight=pw)
        if gamma > 0.0:
            p = torch.sigmoid(logits).detach()
            pt = p * tgt + (1 - p) * (1 - tgt)
            loss = (1.0 - pt).pow(gamma) * bce
        else:
            loss = bce
        return loss.mean()

    # Two-logit path (softmax)
    y = target.long().view(-1)
    if smoothing > 0.0:
        C = logits.size(-1)
        on = (1.0 - smoothing); off = smoothing / max(1, C - 1)
        y_onehot = F.one_hot(y, num_classes=C).to(logits.dtype)
        y_smooth = y_onehot * on + (1.0 - y_onehot) * off
        logp = F.log_softmax(logits, dim=-1)
        ce = -(y_smooth * logp).sum(dim=1)
        if class_weight is not None:
            w = class_weight[y]
            ce = ce * w
    else:
        ce = F.cross_entropy(logits, y, weight=class_weight, reduction="none")

    if gamma > 0.0:
        p = torch.exp(-ce).detach()
        ce = (1.0 - p).pow(gamma) * ce
    return ce.mean()



def symmetric_cross_entropy(logits: torch.Tensor, target: torch.Tensor, alpha: float=0.5, beta: float=0.5, eps: float=0.1):
    """
    SCE ≈ alpha * CE + beta * RCE. We implement a numerically safe RCE using smoothed one-hot.
    """
    C = logits.size(-1)
    y = target.long().view(-1)
    ce = F.cross_entropy(logits, y, reduction="mean")
    with torch.no_grad():
        onehot = torch.zeros_like(logits).scatter_(1, y.view(-1,1), 1.0)
        smooth = onehot * eps + (1.0 - onehot) * ((1.0 - eps) / max(1, C-1))
        smooth = torch.clamp(smooth, 1e-6, 1.0)
    probs = F.softmax(logits, dim=-1)
    rce = - torch.mean(torch.sum(probs * torch.log(smooth), dim=1))
    return alpha * ce + beta * rce

def consistency_loss_same_family(deltas: torch.Tensor, y: torch.Tensor, fid: torch.Tensor, p_eq: torch.Tensor):
    """
    Encourage same-label items within a family to have similar delta logits.
    deltas: [N], y: [N], fid:[N], p_eq:[N] in [0,1]
    """
    N = deltas.numel()
    if N <= 1: return deltas.new_tensor(0.0)
    same_fam = (fid.view(-1,1) == fid.view(1,-1))
    same_lab = (y.view(-1,1) == y.view(1,-1))
    mask = same_fam & same_lab
    mask.fill_diagonal_(False)
    if not mask.any():
        return deltas.new_tensor(0.0)
    w = (p_eq.view(-1,1) * p_eq.view(1,-1))
    diffs = (deltas.view(-1,1) - deltas.view(1,-1))**2
    loss = (diffs * mask.float() * w).sum() / (mask.float() * w + 1e-12).sum()
    return loss


def _compute_class_stats_from_manifest_rows(rows: List[Dict[str, Any]]) -> Tuple[int, int, float]:
    n_pos, n_neg = 0, 0
    for r in rows:
        try:
            lab = int(r.get("label", 0))
        except Exception:
            lab = 0
        if lab == 1:
            n_pos += 1
        else:
            n_neg += 1
    total = max(1, n_pos + n_neg)
    base_rate = float(n_pos) / float(total)
    return n_pos, n_neg, base_rate


# ────────────────────────────────────────────
# Evaluate & collectors (with optional TTA)
# ────────────────────────────────────────────
def _augment_batch_for_eval(b: Batch, dropedge_p: float = 0.0, feat_noise_std: float = 0.0):
    b = b.clone()
    if dropedge_p > 0.0 and b.edge_index is not None and b.edge_index.numel() > 0:
        E = b.edge_index.size(1)
        keep = torch.rand(E, device=b.edge_index.device) > dropedge_p
        if keep.sum() >= 1:
            b.edge_index = b.edge_index[:, keep]
            if getattr(b, "edge_attr", None) is not None:
                b.edge_attr = b.edge_attr[keep]
            if getattr(b, "edge_type", None) is not None:
                b.edge_type = b.edge_type[keep]

    # numerical feature noise (unchanged)
    if feat_noise_std > 0.0:
        noise = torch.randn_like(b.x) * feat_noise_std
        b.x = b.x + noise

    # --- final safety: keep lengths consistent if anything upstream misbehaves
    if getattr(b, "edge_type", None) is not None and b.edge_index is not None:
        E = b.edge_index.size(1)
        if b.edge_type.numel() != E:
            # clamp to the minimum to avoid runtime errors
            M = min(E, int(b.edge_type.numel()))
            b.edge_index = b.edge_index[:, :M]
            if getattr(b, "edge_attr", None) is not None and b.edge_attr.size(0) != M:
                b.edge_attr = b.edge_attr[:M]
            b.edge_type = b.edge_type[:M]
    return b


@torch.inference_mode()
def collect_probs_with_T(model, loader, device, T: float = 1.0, tta: int = 0, tta_dropedge_p: float=0.0, tta_feat_noise_std: float=0.0):
    model.eval()
    ys, probs = [], []
    T = float(max(0.1, min(10.0, T)))
    disable = getattr(loader, "_no_progress", True)
    for batch in _tqdm(loader, desc="Eval/prob collect", disable=disable, total=len(loader)):
        b = batch.to(device, non_blocking=True)
        if tta and tta > 0:
            acc = 0.0
            for _ in range(tta):
                bb = _augment_batch_for_eval(b, tta_dropedge_p, tta_feat_noise_std)
                out = model(bb)
                logits = out["logits"] if isinstance(out, dict) else out
                logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                p1 = _probs_from_logits_binary(logits, T=T)
                acc += p1.detach().cpu()
            p1 = (acc / float(tta))
        else:
            out = model(b)
            logits = out["logits"] if isinstance(out, dict) else out
            logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
            p1 = _probs_from_logits_binary(logits, T=T).detach().cpu()
        ys.extend(b.y.detach().cpu().tolist())
        probs.extend(p1.tolist())
    return np.asarray(ys, dtype=np.int64), np.asarray(probs, dtype=np.float32)

@torch.inference_mode()
def evaluate(model: nn.Module, loader: GeoDataLoader, device: torch.device, threshold: float = 0.5, temperature: Optional[float] = None,
             tta: int = 0, tta_dropedge_p: float=0.0, tta_feat_noise_std: float=0.0) -> Dict[str, Any]:
    model.eval()
    y_true, prob_list = [], []
    T = float(temperature) if (temperature is not None and np.isfinite(temperature) and temperature > 0.0) else 1.0
    T = max(0.1, min(10.0, T))
    disable = getattr(loader, "_no_progress", True)
    for batch in _tqdm(loader, desc="Evaluate", disable=disable, total=len(loader)):
        b = batch.to(device, non_blocking=True)
        if tta and tta > 0:
            acc = 0.0
            for _ in range(tta):
                bb = _augment_batch_for_eval(b, tta_dropedge_p, tta_feat_noise_std)
                out = model(bb)
                logits = out["logits"] if isinstance(out, dict) else out
                logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                p1 = _probs_from_logits_binary(logits, T=T)
                acc += p1.detach().cpu()
            p1 = (acc / float(tta))
        else:
            out = model(b)
            logits = out["logits"] if isinstance(out, dict) else out
            logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
            p1 = _probs_from_logits_binary(logits, T=T).detach().cpu()
        prob_list.append(p1)
        y_true.extend(b.y.detach().cpu().tolist())
    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = (np.asarray(torch.cat(prob_list).numpy(), dtype=np.float32) if prob_list else np.empty((0,), dtype=np.float32))
    y_prob = clamp01_np(y_prob)
    y_pred = decide_from_prob(y_prob, threshold)
    acc = accuracy_score(y_true, y_pred) if len(y_true) else 0.0
    prec, rec, f1, _ = precision_recall_fscore_support(y_true, y_pred, average="binary", zero_division=0)
    try:
        auc = roc_auc_score(y_true, y_prob) if len(np.unique(y_true)) > 1 else float("nan")
    except Exception:
        auc = float("nan")
    cm = confusion_matrix(y_true, y_pred) if len(y_true) else np.zeros((2,2), dtype=int)
    return {"acc": float(acc), "prec": float(prec), "rec": float(rec), "f1": float(f1),
            "auc": float(auc) if np.isfinite(auc) else float("nan"),
            "cm": cm, "thr": float(threshold), "T": float(T)}


# ────────────────────────────────────────────
# Model factory
# ────────────────────────────────────────────
def make_model(args, in_dim: int, pna_deg_hist: Optional[torch.Tensor]=None) -> nn.Module:
    name = args.model.lower()
    if name == "gcn":      return GCNBaseline(in_dim, args.hidden_dim, args.num_classes, args.layers, args.readout, args.dropout)
    if name == "gat":      return GATBaseline(in_dim, args.hidden_dim, args.num_classes, args.heads, args.layers, args.readout, args.dropout)
    if name == "sage":     return SAGEBaseline(in_dim, args.hidden_dim, args.num_classes, args.layers, args.readout, args.dropout)
    if name == "gin":      return GINBaseline(in_dim, args.hidden_dim, args.num_classes, args.layers, args.readout, args.dropout)
    if name == "pna":
        return PNABaseline(in_dim, args.hidden_dim, args.num_classes, args.layers, args.readout, args.dropout, deg_hist=pna_deg_hist)
    if name in ("deepgcn","deepergcn","dgcnn"):
        return DeeperGCNBaseline(in_dim, args.hidden_dim, args.num_classes, args.layers, args.readout, args.dropout)
    if name == "mpnn":
        return MPNNBaseline(
            in_dim, hidden_dim=args.hidden_dim, out_dim=args.num_classes,
            edge_dim=args.edge_emb_dim, layers=args.layers, readout=args.readout,
            dropout=args.dropout, num_relations=getattr(args, "num_relations", 0)
        )

    if name == "rgcn":     return RGcnBaseline(in_dim, args.hidden_dim, args.num_classes, num_relations=getattr(args, "num_relations", 1), layers=args.layers, readout=args.readout, dropout=args.dropout)
    if name == "mptcn_tts":
        return MPTCN_TTS(in_dim, hidden_dim=args.hidden_dim, out_dim=args.num_classes,
                         spatial=args.spatial, Ls=args.Ls, Lt=args.Lt, heads=args.heads, bases=args.bases,
                         dropout=args.dropout, readout=args.readout,temporal=args.temporal,)   # <-- pass it through)
    if name == "han":
        return HANBaseline(in_dim, hidden_dim=args.hidden_dim, out_dim=args.num_classes,
                           layers=args.layers, heads=args.heads, dropout=args.dropout, readout=args.readout)
    if name == "hgt":
        return HGTBaseline(in_dim, hidden_dim=args.hidden_dim, out_dim=args.num_classes,
                           layers=args.layers, heads=args.hgt_heads, dropout=args.dropout, readout=args.readout)
    raise ValueError(f"Unknown model: {args.model}")


# ────────────────────────────────────────────
# Train (mutant-aware)
# ────────────────────────────────────────────
# ──────────────────────────────────────────────────────────────
# TRAIN EPOCH (mutant-aware) — REWRITTEN
# Paste over your existing definition
# ──────────────────────────────────────────────────────────────
# ──────────────────────────────────────────────────────────────
# TRAIN EPOCH (mutant-aware) — memory-safe + warning throttle
# ──────────────────────────────────────────────────────────────
def train_epoch_mutant_aware(
    model,
    loader,
    device,
    optimizer,
    scaler,
    amp: bool,
    args,
    dom_head=None,
    delta_head: Optional[DeltaHead] = None,
    proto_bank: Optional[PrototypeBank] = None,
    global_step: int = 0,
    scheduler=None, 
):
    model.train()
    if delta_head is not None:
        delta_head.train()

    total_loss_accum = 0.0
    seen_graphs = 0

    disable_bar = getattr(loader, "_no_progress", False) if hasattr(loader, "_no_progress") else False
    pbar = _tqdm(loader, desc="Train (batches)", disable=disable_bar, total=len(loader))

    optimizer.zero_grad(set_to_none=True)
    accum_steps = max(1, int(getattr(args, "accum_steps", 1)))

    # limit very noisy collapse warnings per epoch
    collapse_warn_budget = int(getattr(args, "warn_collapse_budget", 6))
    collapse_warn_printed = 0

    for batch in pbar:
        b = batch.to(device, non_blocking=True)
        seen_graphs += int(getattr(b, "num_graphs", 0))

        # Stochastic regularization during training (DropEdge + optional feature noise)
        if getattr(args, "dropedge_p", 0.0) > 0.0 or getattr(args, "train_feat_noise_std", 0.0) > 0.0:
            b = _augment_batch_for_eval(
                b,
                dropedge_p=float(getattr(args, "dropedge_p", 0.0)),
                feat_noise_std=float(getattr(args, "train_feat_noise_std", 0.0)),
            )

        with autocast(enabled=amp):
            out = model(b)
            logits = out["logits"] if isinstance(out, dict) else out
            emb = out.get("emb", None) if isinstance(out, dict) else None
            y = b.y.view(-1).long()

            # Guard against NaN/Inf / explosions
            logits = torch.nan_to_num(logits, nan=0.0, posinf=30.0, neginf=-30.0).clamp_(-30, 30)

            # Δ-logit collapse monitor (rate-limited & throttled)
            if not getattr(args, "no_progress", False):
                if (global_step % 50) == 0 and collapse_warn_printed < collapse_warn_budget:
                    with torch.no_grad():
                        z = logits.view(-1) if logits.size(-1) == 1 else (logits[:, 1] - logits[:, 0])
                        z = torch.tanh(z)
                        if torch.isfinite(z).any():
                            zstd = float(z.std().detach().cpu().item())
                            if zstd < 1e-3:
                                tqdm.write("[Warn] Δlogit ~ constant this step; watch for probability collapse.")
                                collapse_warn_printed += 1

            # Light-weight batch/graph stats every ~200 steps
            if (global_step % 200) == 0 and not getattr(args, "no_progress", False):
                with torch.no_grad():
                    y_np = b.y.view(-1).detach().cpu().numpy()
                    y_pos = int((y_np == 1).sum())
                    p = float((y_np == 1).mean())
                    n_nodes = int(b.x.size(0))
                    n_graphs = int(getattr(b, "num_graphs", 0))
                    n_edges = int(b.edge_index.size(1)) if getattr(b, "edge_index", None) is not None else 0

                    # show the weighting that actually applies to the current head shape
                    if logits.size(-1) > 1:
                        weight_str = (f"class_weight=[1.0,{getattr(args,'pos_weight',1.0):.4f}]")
                    else:
                        weight_str = (f"pos_weight={getattr(args,'pos_weight',1.0):.4f}")

                    tqdm.write(
                        f"[BatchMix] y_pos={y_pos}/{n_graphs} ({p:.4f}) | nodes={n_nodes} edges={n_edges} "
                        f"| {weight_str} | gamma={getattr(args,'focal_gamma',0.0)} "
                        f"smoothing={getattr(args,'label_smoothing',0.0)}"
                    )

                with torch.no_grad():
                    d = _delta_from_logits(logits).detach().float()
                    d = torch.nan_to_num(d, nan=0.0, posinf=30.0, neginf=-30.0)
                    tqdm.write(f"[Diag] Δlogit std={d.std().item():.6e} (batch={n_graphs})")

            # ── Base loss (SCE after warmup or focal/CE) — CORRECT weighting split
            use_sce = bool(getattr(args, "use_sce", False)) and (global_step >= int(getattr(args, "sce_after", 0)))
            cw = None  # ensure visible for logging below

            if use_sce:
                base = symmetric_cross_entropy(
                    logits, y,
                    alpha=float(getattr(args, "sce_alpha", 0.1)),
                    beta=float(getattr(args, "sce_beta", 1.0)),
                    eps=float(getattr(args, "sce_epsilon", 1e-4)),
                )
            else:
                if logits.size(-1) > 1:
                    # 2-logit (softmax): use class_weight ONLY (no pos_weight)
                    if getattr(args, "pos_weight", None) is not None:
                        cw = torch.tensor([1.0, float(args.pos_weight)], device=logits.device, dtype=logits.dtype)
                    base = focal_loss(
                        logits, y,
                        gamma=float(getattr(args, "focal_gamma", 0.0)),
                        smoothing=float(getattr(args, "label_smoothing", 0.0)),
                        class_weight=cw,
                        pos_weight=None,
                    )
                else:
                    # 1-logit (BCE): use pos_weight ONLY (no class_weight)
                    base = focal_loss(
                        logits, y,
                        gamma=float(getattr(args, "focal_gamma", 0.0)),
                        smoothing=float(getattr(args, "label_smoothing", 0.0)),
                        class_weight=None,
                        pos_weight=(float(getattr(args, "pos_weight")) if getattr(args, "pos_weight", None) is not None else None),
                    )

            loss = base

            # One-time loss wiring print (first step of epoch)
            if (global_step == 0) and (not getattr(args, "no_progress", False)):
                path = ("SCE" if use_sce else "Focal/CE")
                out_dim = int(logits.size(-1))
                used_cw = (cw.detach().cpu().tolist() if (cw is not None and out_dim > 1) else None)
                used_pw = (float(args.pos_weight) if (out_dim == 1 and getattr(args, "pos_weight", None) is not None) else None)
                tqdm.write(
                    f"[LossWire] branch={path} | logits_out_dim={out_dim} | "
                    f"class_weight={used_cw} | pos_weight={used_pw} | "
                    f"gamma={float(getattr(args,'focal_gamma',0.0))} | "
                    f"smoothing={float(getattr(args,'label_smoothing',0.0))}"
                )

            # Family consistency
            if float(getattr(args, "consistency_w", 0.0)) > 0.0:
                deltas = _delta_from_logits(logits)
                fid = getattr(b, "fid", torch.zeros_like(y))
                p_eq = getattr(b, "p_eq", torch.ones_like(deltas))
                cons = consistency_loss_same_family(deltas, y, fid.view(-1), p_eq.view(-1))
                loss = loss + float(args.consistency_w) * cons

            # Supervised Contrastive
            if emb is not None and float(getattr(args, "supcon_w", 0.0)) > 0.0:
                fid = getattr(b, "fid", None)
                fid = fid.view(-1) if fid is not None else None
                scon = supervised_contrastive(
                    emb, y, fid=fid,
                    tau=float(getattr(args, "supcon_tau", 0.1)),
                    mode=str(getattr(args, "supcon_mode", "label+family")),
                )
                loss = loss + float(args.supcon_w) * scon

            # Prototype
            if emb is not None and (proto_bank is not None) and float(getattr(args, "proto_w", 0.0)) > 0.0:
                loss = loss + proto_bank.reg_loss(emb, y, weight=float(args.proto_w))

            # Delta head (within-family)
            if (delta_head is not None) and (emb is not None) and float(getattr(args, "delta_w", 0.0)) > 0.0:
                K = int(getattr(args, "delta_pairs_per_family", 2))
                fid = getattr(b, "fid", None)
                if fid is not None:
                    y_cpu = y.detach().cpu()
                    fid_cpu = fid.view(-1).detach().cpu().tolist()
                    by_f: Dict[int, List[int]] = {}
                    for i, f in enumerate(fid_cpu):
                        by_f.setdefault(int(f), []).append(i)

                    dz_loss = emb.new_tensor(0.0)
                    pair_groups = 0
                    for _, idxs in by_f.items():
                        if len(idxs) < 2:
                            continue
                        idxs_pos = [i for i in idxs if int(y_cpu[i]) == 1]
                        idxs_neg = [i for i in idxs if int(y_cpu[i]) == 0]

                        def take_pairs(pool):
                            if len(pool) < 2: return []
                            random.shuffle(pool)
                            return [(pool[i], pool[i + 1]) for i in range(0, min(len(pool) - 1, 2 * K), 2)]

                        pairs = take_pairs(idxs_pos) + take_pairs(idxs_neg)
                        if not pairs:
                            continue
                        z1 = emb[[i for i, _ in pairs]]
                        z2 = emb[[j for _, j in pairs]]
                        pred = delta_head(z1, z2).view(-1)
                        target = torch.ones_like(pred)
                        dz_loss = dz_loss + F.binary_cross_entropy_with_logits(pred, target, reduction="mean")
                        pair_groups += 1

                    if pair_groups > 0:
                        dz_loss = dz_loss / float(pair_groups)
                        loss = loss + float(args.delta_w) * dz_loss

            # Domain Adapter (GRL)
            if (dom_head is not None) and (emb is not None) and float(getattr(args, "lambda_dom", 0.0)) > 0.0:
                dom_logits = dom_head(emb, lambd=float(args.lambda_dom))
                dom_y = getattr(b, "is_mutant", None)
                if dom_y is not None:
                    dom_y = dom_y.view(-1).float()
                    dom_loss = F.binary_cross_entropy_with_logits(dom_logits, dom_y, reduction="mean")
                    loss = loss + float(args.lambda_dom) * dom_loss

            # Optional logit L2
            if float(getattr(args, "logit_l2", 0.0)) > 0.0:
                if logits.size(-1) == 1:
                    z = logits.view(-1)
                else:
                    z = logits[:, 1] - logits[:, 0]
                loss = loss + float(args.logit_l2) * torch.mean(z * z)

        # Grad accumulation
        loss_scaled = loss / float(accum_steps)
        if amp:
            scaler.scale(loss_scaled).backward()
        else:
            loss_scaled.backward()

        # Grad norm snapshot (rate-limited)
        if (global_step % (50 * accum_steps) == 0):
            try:
                total_gn = 0.0; cnt = 0
                for p in model.parameters():
                    if (p.grad is not None) and torch.isfinite(p.grad).all():
                        total_gn += float(p.grad.detach().norm().item()); cnt += 1
                if cnt > 0 and (not getattr(args, "no_progress", False)):
                    tqdm.write(f"[Grad] avg_param_grad_norm≈{total_gn/max(1,cnt):.4e}")
            except Exception:
                pass

        if ((global_step + 1) % accum_steps) == 0:
            # Grad clipping for stability
            if amp:
                scaler.unscale_(optimizer)
            torch.nn.utils.clip_grad_norm_(list(model.parameters()), max_norm=1.0)

            if amp:
                scaler.step(optimizer); scaler.update()
            else:
                optimizer.step()
            if scheduler is not None:
                try:
                    scheduler.step()
                except Exception:
                    pass
            optimizer.zero_grad(set_to_none=True)


            # Show effective LR / accum info occasionally
            if (global_step % 200) == 0 and not getattr(args, "no_progress", False):
                lr_show = optimizer.param_groups[0].get('lr', float(getattr(args, 'lr', 0.0)))
                tqdm.write(f"[Opt] lr={lr_show} | accum_steps={accum_steps}")

        # Update prototype bank
        if emb is not None and proto_bank is not None:
            with torch.no_grad():
                proto_bank.update(emb.detach(), y.detach())

        total_loss_accum += float(loss_scaled.detach().cpu().item()) * float(accum_steps)
        global_step += 1

    if not getattr(args, "no_progress", False):
        tqdm.write(f"[Debug] TRAIN epoch graphs seen = {seen_graphs}")

    mean_loss = total_loss_accum / max(1, len(loader))
    return mean_loss, global_step




# ────────────────────────────────────────────
# Audit helpers
# ────────────────────────────────────────────
def _audit_dataset_jsons(ds: DraperDataset, name: str = "SPLIT"):
    total = len(ds.rows)
    found = 0
    auto_resolved = 0
    misses = []
    for i, r in enumerate(ds.rows):
        cands = ds._resolve_candidates(r)
        p = ds._first_existing(cands)
        if p is None:
            if len(misses) < 10:
                jp = (r.get("json_path") or "").strip()
                idx = r.get("index") or r.get("id")
                misses.append(f"row={i} json_path='{jp}' index='{idx}'")
        else:
            found += 1
            jp = (r.get("json_path") or "").strip()
            if not jp and p.name == "export.json":
                auto_resolved += 1
    cov = (found / total) if total else 0.0
    print(f"[Audit][{name}] JSON coverage: {found}/{total} = {cov*100:.2f}%")
    if auto_resolved > 0:
        print(f"[Audit][{name}] originals auto-resolved to export.json: {auto_resolved}")
    if misses:
        print(f"[Audit][{name}] sample misses:\n  " + "\n  ".join(misses))
    return cov


# Put this near the top of the file or at the start of run(), BEFORE it's called.
def _quick_graph_stats(ds, name):
    import numpy as np
    ns, es = [], []
    n_check = min(2000, len(ds))
    miss = 0
    hard_miss = 0
    for i in range(n_check):
        try:
            d = ds[i]
        except FileNotFoundError as e:
            if hard_miss < 10:
                print(f"[Stats][{name}][MISS] {str(e)}")
            hard_miss += 1
            continue
        except Exception as e:
            if hard_miss < 10:
                print(f"[Stats][{name}][MISS] row={i}: {e}")
            hard_miss += 1
            continue

        n = int(getattr(d, "num_nodes", 0))
        e = int(d.edge_index.size(1)) if hasattr(d, "edge_index") else int(getattr(d, "num_edges", 0))
        ns.append(n); es.append(e)
        if n == 8 and e in (0, 16):
            miss += 1

    total_seen = len(ns)
    if total_seen == 0:
        print(f"[Stats][{name}] no graphs inspected (hard_miss={hard_miss}).")
        return

    print(f"[Stats][{name}] seen={total_seen}/{n_check} hard_miss={hard_miss} "
          f"nodes(mean/med/p95)=({np.mean(ns):.1f}/{np.median(ns):.1f}/{np.quantile(ns,0.95):.1f}) "
          f"edges(mean/med/p95)=({np.mean(es):.1f}/{np.median(es):.1f}/{np.quantile(es,0.95):.1f}) "
          f"fallback_like={miss}/{total_seen} ({100*miss/max(1,total_seen):.1f}%)")

# Place this ABOVE its first use in run()
def _apply_collapse_policy(ds, policy: str, K: int = 2, seed: int = 123):
    """
    TRAIN-ONLY policy that reduces rows per family:
      all    : keep all rows
      latest : keep single latest snapshot per family (best-effort by t_idx; else lexicographic)
      orig   : keep original (export.json or mutation_type=='orig') if present; else latest
      orig+k : keep original (if present) + K random non-orig snapshots per family
    """
    import re, random
    from typing import Dict, List, Any

    policy = (policy or "all").lower()
    if policy == "all":
        print("[Collapse][train] policy=all → using all rows")
        return

    # group by family
    by_fam: Dict[str, List[dict]] = {}
    for r in ds.rows:
        fam = str(r.get("family_id", "unknown"))
        by_fam.setdefault(fam, []).append(r)

    rng = random.Random(seed)

    def is_orig(row: dict) -> bool:
        mut = str(row.get("mutation_type", "")).lower()
        jp  = (row.get("json_path") or "").strip().lower()
        return (mut == "orig") or (jp == "") or jp.endswith("/export.json") or jp.endswith("\\export.json")

    def time_idx(row: dict) -> int:
        t_raw = row.get("t_idx", None)
        if t_raw is None:
            jp = str(row.get("json_path", ""))
            m = re.search(r"(?:adv|mut)\D*?(\d+)", jp)
            if m:
                return int(m.group(1))
            return int(hash(jp) & 0xffff)
        try:
            return int(t_raw)
        except Exception:
            return 0

    kept: List[dict] = []
    fam_cnt_before = 0
    for fam, rows in by_fam.items():
        fam_cnt_before += len(rows)
        orig_rows = [r for r in rows if is_orig(r)]
        snap_rows = [r for r in rows if r not in orig_rows]

        if policy == "latest":
            kept.append(max(rows, key=time_idx))
            continue

        if policy == "orig":
            kept.append(orig_rows[0] if orig_rows else max(rows, key=time_idx))
            continue

        if policy == "orig+k":
            sel = []
            if orig_rows:
                sel.append(orig_rows[0])
            rng.shuffle(snap_rows)
            sel.extend(snap_rows[:max(0, int(K))])
            if not sel:  # no orig and k==0
                sel = [max(rows, key=time_idx)]
            kept.extend(sel)
            continue

        # unknown → fallback = all
        kept.extend(rows)

    ds.rows = kept
    if hasattr(ds, "indices"):
        ds.indices = list(range(len(ds.rows)))
    if hasattr(ds, "len"):
        try:
            ds.len = len(ds.rows)
        except Exception:
            pass

    print(f"[Collapse][train] policy={policy} K={K} → kept {len(ds.rows)} rows from {len(by_fam)} families (was {fam_cnt_before})")


# ────────────────────────────────────────────
# Run  — memory-safer DataLoader setup (no sharding/merge)
# ────────────────────────────────────────────
def run(args):
    from types import SimpleNamespace

    # ── seed & device
    set_seed(args.seed)
    device = torch.device("cuda" if torch.cuda.is_available() and not args.no_cuda else "cpu")
    if device.type == "cuda":
        props = torch.cuda.get_device_properties(0)
        print(f"[Device] CUDA available → {props.name} | cc {props.major}.{props.minor} | {props.total_memory/1e9:.1f} GB")
    else:
        print("[Device] CPU (CUDA not available or --no-cuda set)")

    # ── roots
    train_root = args.train_json_root or args.json_root
    val_root   = args.val_json_root   or args.json_root
    test_root  = args.test_json_root  or args.json_root

    # ── layout & cache
    layout    = _get_devign_layout(args)
    cache_dir = _ensure_cache_dir(args)

    # If --new-cache-dir is specified, use that instead
    if args.new_cache_dir:
        cache_dir = Path(args.new_cache_dir)
        cache_dir.mkdir(parents=True, exist_ok=True)
        print(f"[Cache] Using NEW cache directory: {cache_dir}")
        print(f"  - Old cache remains at: {args.cache_dir}")
        print("  - New cache will be built in this location")

    # ── datasets (vocabs injected later)
    train_ds = DraperDataset(
        manifest_csv=args.train_manifest, json_root=train_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        new_cache_dir=args.new_cache_dir,  # Pass the new cache directory
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )
    val_ds = DraperDataset(
        manifest_csv=args.val_manifest, json_root=val_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )
    test_ds = DraperDataset(
        manifest_csv=args.test_manifest, json_root=test_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )

    # ── vocabs
    vocabs = ensure_vocabs(args, layout, train_ds)
    node_vocab, edge_vocab = vocabs["node_vocab"], vocabs["edge_vocab"]
    train_ds.node_vocab = node_vocab; train_ds.edge_vocab = edge_vocab
    val_ds.node_vocab   = node_vocab; val_ds.edge_vocab   = edge_vocab
    test_ds.node_vocab  = node_vocab; test_ds.edge_vocab  = edge_vocab

    # --- Ensure relational baselines see all relations ---
    args.num_relations = max(1, len(edge_vocab))
    print(f"[FeatWire] num_relations set from edge_vocab: {args.num_relations}")

    # Ensure MPTCN_TTS RGCN sees the full relation set
    if args.model.lower() == "mptcn_tts" and args.spatial.lower() == "rgcn":
        args.bases = int(args.num_relations)  # num_relations = len(edge_vocab)
        print(f"[FeatWire][MPTCN_TTS][RGCN] bases set to num_relations={args.bases}")



    v_sig = _vocab_signature(node_vocab, edge_vocab)
    train_ds._vocab_sig = v_sig
    val_ds._vocab_sig   = v_sig
    test_ds._vocab_sig  = v_sig

    if int(getattr(args, "dry_run", 0)) > 0:
        k = min(int(args.dry_run), len(train_ds))
        print(f"[DryRun] Parsing {k} graphs from TRAIN then exiting…")
        for i in range(k):
            _ = train_ds[i]
            if (i + 1) % 10 == 0 or (i + 1) == k:
                print(f"[DryRun] {i+1}/{k} parsed")
        print("[DryRun] OK")
        return

    # ── warm single-zip cache (no sharding/merge paths)
    def _ensure_zip_cache_filled(ds: DraperDataset, name: str):
        zc = ds._get_zip_cache()
        if zc is None:
            print(f"[Cache][{name}] no cache dir; skipping fill")
            return
        missing = []
        for i, r in enumerate(ds.rows):
            p = ds._first_existing(ds._resolve_candidates(r))
            if p is None:
                continue
            entry = ds._graph_cache_key(p)
            if entry and (not zc.contains(entry)):
                missing.append(i)
        if not missing:
            print(f"[Cache][{name}] zip is already complete ({len(ds)} entries).")
            return
        print(f"[Cache][{name}] warming {len(missing)} graphs into graph_cache.zip …")
        for i in _tqdm(missing, desc=f"Cache {name}", disable=args.no_progress, total=len(missing)):
            try:
                _ = ds[i]
            except Exception as e:
                if not args.no_progress:
                    tqdm.write(f"[Cache][{name}][WARN] row={i}: {e}")
        print(f"[Cache][{name}] warm complete.")

    from concurrent.futures import ProcessPoolExecutor, as_completed
    def _warm_cache_sequentially(ds: DraperDataset, name: str, progress=True):
        """
        Warm the cache by loading all graphs sequentially (no parallel workers).
        
        This is the correct approach that was used in the previous implementation.
        """
        zc = ds._get_zip_cache()
        if zc is None:
            print(f"[Cache][{name}] no cache dir; skipping fill")
            return
        
        # Find missing entries
        missing = []
        for i, r in enumerate(ds.rows):
            p = ds._first_existing(ds._resolve_candidates(r))
            if p is None:
                continue
            entry = ds._graph_cache_key(p)
            if entry and (not zc.contains(entry)):
                missing.append(i)
        
        if not missing:
            print(f"[Cache][{name}] zip is already complete ({len(ds)} entries).")
            return
        
        # Process sequentially to avoid pickling issues
        print(f"[Cache][{name}] warming {len(missing)} graphs into graph_cache.zip …")
        pbar = _tqdm(missing, desc=f"Cache {name}", disable=not progress, total=len(missing))
        
        for i in pbar:
            try:
                # Directly process the graph without DataLoader parallelism
                # This avoids all pickling issues with thread locks
                ds.__getitem__(i)
            except Exception as e:
                if progress:
                    pbar.write(f"[Cache][{name}][WARN] row={i}: {e}")
        
        print(f"[Cache][{name}] warm complete.")

    def _parallel_warm_cache(ds: DraperDataset, name: str, num_workers: int = 4):
        """
        Warm cache with controlled number of workers to avoid I/O contention.
        
        Args:
            ds: Dataset to warm cache for
            name: Name for the dataset (for logging)
            num_workers: Number of workers to use (4 is optimal for most systems)
        """
        zc = ds._get_zip_cache()
        if zc is None:
            print(f"[Cache][{name}] no cache dir; skipping fill")
            return
        
        # Find missing entries
        missing = []
        for i, r in enumerate(ds.rows):
            p = ds._first_existing(ds._resolve_candidates(r))
            if p is None:
                continue
            entry = ds._graph_cache_key(p)
            if entry and (not zc.contains(entry)):
                missing.append(i)
        
        if not missing:
            print(f"[Cache][{name}] zip is already complete ({len(ds)} entries).")
            return
        
        print(f"[Cache][{name}] warming {len(missing)} graphs into graph_cache.zip …")
        
        # Use a process pool to warm the cache in parallel
        with ProcessPoolExecutor(max_workers=num_workers) as executor:
            # Create a progress bar
            with tqdm(total=len(missing), desc=f"Cache {name}", disable=args.no_progress) as pbar:
                # Submit tasks
                futures = {executor.submit(ds.__getitem__, i): i for i in missing}
                
                # Process results
                for future in as_completed(futures):
                    i = futures[future]
                    try:
                        future.result()
                        pbar.update(1)
                    except Exception as e:
                        if not args.no_progress:
                            tqdm.write(f"[Cache][{name}][WARN] row={i}: {e}")
        
        print(f"[Cache][{name}] warm complete.")

    if getattr(args, "warm_cache", False):
        print(f"[Cache] Warming cache with {args.cache_workers} workers to avoid I/O contention")
        _warm_cache_sequentially(train_ds, "TRAIN", progress=not args.no_progress)
        _warm_cache_sequentially(val_ds, "VAL", progress=not args.no_progress)
        _warm_cache_sequentially(test_ds, "TEST", progress=not args.no_progress)
            # --- Optionally merge shards into a single zip and clean up ---
        for ds, tag in [(train_ds, "TRAIN"), (val_ds, "VAL"), (test_ds, "TEST")]:
            zc = ds._get_zip_cache()
            if isinstance(zc, GraphShardedCache) and bool(getattr(args, "merge_shards", True)):
                base_zip = zc.base_zip or (ds.cache_dir / "graph_cache.zip")
                zc.merge_to(base_zip, delete_after=bool(getattr(args, "delete_shards_after_merge", True)))
                print(f"[Cache][{tag}] merged shards → {base_zip}")
    else:
        print("[Cache] warm_cache=False → skipping upfront cache fill.")


    # ── quick stats (helpers must be defined elsewhere in file)
    if getattr(args, "quick_stats", False):
        _quick_graph_stats(train_ds, "TRAIN")
        _quick_graph_stats(val_ds,   "VAL")
        _quick_graph_stats(test_ds,  "TEST")
    else:
        print("[Stats] quick_stats=False → skipping dataset size scan.")

    # ── collapse policy on TRAIN
    _apply_collapse_policy(
        train_ds,
        policy=getattr(args, "collapse_policy", "all"),
        K=int(getattr(args, "collapse_k", 2)),
        seed=int(getattr(args, "seed", 42))
    )

    # ── class stats → pos_weight
    def _class_stats(rows: List[Dict[str, Any]]) -> Tuple[int, int, float]:
        n_pos = n_neg = 0
        for r in rows:
            try:
                lab = int(r.get("label", 0))
            except Exception:
                lab = 0
            if lab == 1: n_pos += 1
            else:        n_neg += 1
        total = max(1, n_pos + n_neg)
        return n_pos, n_neg, float(n_pos) / float(total)

    n_pos, n_neg, train_base_rate = _class_stats(train_ds.rows)
    pos_weight = (float(n_neg) / float(max(1, n_pos))) if n_pos > 0 else 1.0
    print(f"[ClassStats][TRAIN] pos={n_pos} neg={n_neg} → pos_weight={pos_weight:.3f}")
    args.pos_weight = float(pos_weight)


    # prevent extreme weights from destabilizing early training
    max_pw = float(getattr(args, "max_pos_weight", 8.0))
    args.pos_weight = float(min(max_pw, args.pos_weight))
    print(f"[ClassStats][TRAIN] capped pos_weight={args.pos_weight:.3f} (max_pos_weight={max_pw})")

    # gentle regularization defaults if user didn’t set them
    if getattr(args, "label_smoothing", None) is None:
        args.label_smoothing = 0.10
    if getattr(args, "logit_l2", None) is None:
        args.logit_l2 = 1e-4


    # ── coverage audit
    if getattr(args, "do_audit", True):
        tr_cov = _audit_dataset_jsons(train_ds, "TRAIN")
        if tr_cov < float(args.min_json_coverage):
            raise RuntimeError(f"[Audit][TRAIN] Coverage {tr_cov*100:.2f}% < min-json-coverage {args.min_json_coverage*100:.2f}% → fix paths/manifests.")
        _audit_dataset_jsons(val_ds, "VAL")
        _audit_dataset_jsons(test_ds, "TEST")
    else:
        print("[Audit] do_audit=False → skipping coverage audit.")


    # ── DataLoaders (robust: never int(None); prefetch only when workers > 0)
    # ── DataLoaders (robust: never int(None); prefetch only when workers > 0)
    def _as_int(val, default):
        return default if val is None else int(val)

    print(f"[Manifest] TRAIN={len(train_ds)}  VAL={len(val_ds)}  TEST={len(test_ds)}")
    print("[Stage] Building DataLoaders…")

    pin = (device.type == "cuda")

    num_workers_train = _as_int(getattr(args, "num_workers", None), 0)
    num_workers_eval  = _as_int(getattr(args, "eval_num_workers", None), num_workers_train)

    train_bs = _as_int(getattr(args, "train_batch_size", None),
                    _as_int(getattr(args, "batch_size", None), 128))
    eval_bs  = _as_int(getattr(args, "eval_batch_size", None),
                    _as_int(getattr(args, "batch_size", None), 128))

    pref_train = _as_int(getattr(args, "prefetch_factor", None), 2)
    pref_eval  = _as_int(getattr(args, "eval_prefetch_factor", None), pref_train)

    # Optional custom mp context (fixes hangs on some systems)
    mp_ctx = None
    if getattr(args, "mp_context", None):
        import torch.multiprocessing as mp
        mp_ctx = mp.get_context(args.mp_context)

    dl_kwargs_train = dict(
        collate_fn=graph_collate,
        pin_memory=pin,
        persistent_workers=(num_workers_train > 0 and bool(getattr(args, "persistent_workers", False))),
        timeout=int(getattr(args, "loader_timeout", 0)) or 0,
    )
    dl_kwargs_eval = dict(
        collate_fn=graph_collate,
        pin_memory=pin,
        persistent_workers=(num_workers_eval > 0 and bool(getattr(args, "eval_persistent_workers", False))),
        timeout=int(getattr(args, "loader_timeout", 0)) or 0,
    )

    # Only attach prefetch when workers > 0 (PyTorch requirement)
    if num_workers_train > 0:
        dl_kwargs_train["prefetch_factor"] = pref_train
    if num_workers_eval > 0:
        dl_kwargs_eval["prefetch_factor"] = pref_eval

    # Attach context if requested
    if mp_ctx is not None:
        dl_kwargs_train["multiprocessing_context"] = mp_ctx
        dl_kwargs_eval["multiprocessing_context"] = mp_ctx

    # propagate parse debug choice to datasets
    train_ds.debug_parse = bool(getattr(args, "parse_debug", False))
    val_ds.debug_parse   = bool(getattr(args, "parse_debug", False))
    test_ds.debug_parse  = bool(getattr(args, "parse_debug", False))

    train_loader = GeoDataLoader(
        train_ds, batch_size=train_bs, shuffle=True,
        num_workers=num_workers_train, **dl_kwargs_train,
    )
    val_loader = GeoDataLoader(
        val_ds, batch_size=eval_bs, shuffle=False,
        num_workers=num_workers_eval, **dl_kwargs_eval,
    )
    test_loader = GeoDataLoader(
        test_ds, batch_size=eval_bs, shuffle=False,
        num_workers=num_workers_eval, **dl_kwargs_eval,
    )

    print("[Stage] DataLoaders ready.")

    train_loader._no_progress = getattr(args, "no_progress", False)
    val_loader._no_progress   = getattr(args, "no_progress", False)
    test_loader._no_progress  = getattr(args, "no_progress", False)

    print(f"[Sizes] train_ds={len(train_ds)} val_ds={len(val_ds)} test_ds={len(test_ds)}")
    print(f"[Batches/Epoch] train={len(train_loader)} val={len(val_loader)} test={len(test_loader)} | "
          f"train_batch={train_bs} | eval_batch={eval_bs} | "
          f"num_workers(train/eval)={num_workers_train}/{num_workers_eval} | "
          f"prefetch(train/eval)={dl_kwargs_train.get('prefetch_factor','-')}/"
          f"{dl_kwargs_eval.get('prefetch_factor','-')}")


    # ---------- LR SCHEDULER MUST BE BUILT AFTER THE OPTIMIZER ----------
    # (and after train_loader exists so we can compute steps/epoch correctly)

    # ── PNA degree histogram (use cached if available; else build once)
    pna_deg_hist = None
    if args.model.lower() == "pna":
        pkl_path = layout["vocab"] / "pna_deg_hist.pkl"
        if pkl_path.exists():
            try:
                with open(pkl_path, "rb") as f:
                    pna_deg_hist = pickle.load(f)
                _len = len(pna_deg_hist) if hasattr(pna_deg_hist, "__len__") else "?"
                print(f"[PNA] Loaded cached degree histogram from {pkl_path} (len={_len})")
            except Exception:
                pna_deg_hist = None
        if pna_deg_hist is None:
            _sig = _manifest_signature([args.train_manifest])
            print("[PNA] Building degree histogram over TRAIN loader (one pass)…")
            pna_deg_hist = load_or_build_cached(
                args, "pna_deg_hist",
                lambda: compute_pna_degree_hist_from_loader(train_loader, args=args),
                sig=_sig
            )
            try:
                with open(pkl_path, "wb") as f:
                    pickle.dump(pna_deg_hist.cpu() if torch.is_tensor(pna_deg_hist) else pna_deg_hist,
                                f, protocol=pickle.HIGHEST_PROTOCOL)
                print(f"[PNA] Saved degree histogram → {pkl_path}")
            except Exception:
                pass

    # ── feature wiring
    # ── feature wiring
    if getattr(args, "one_hot", False):
        in_dim = len(node_vocab)
        print(f"[FeatWire] Using ONE-HOT features → in_dim=len(node_vocab)={in_dim}")
    else:
        in_dim = int(args.emb_dim)
        print(f"[FeatWire] Using DENSE features → in_dim=--emb-dim={in_dim}")

    try:
        _probe = train_ds[0]
        got = int(_probe.x.size(1))
        if got != in_dim:
            # For dense features, we can adjust the dimension
            if not getattr(args, "one_hot", False):
                print(f"[FeatWire][INFO] Adjusting feature dimension from {got} to {in_dim}")
                # This will be handled in the dataset's __getitem__
            else:
                print(f"[FeatWire][WARN] train_ds[0].x.size(1)={got} != in_dim={in_dim} → overriding in_dim to {got}")
                in_dim = got
    except Exception as _e:
        print(f"[FeatWire][INFO] Skipping early feature check: {_e}")

    # ── model
    model = make_model(args, in_dim=in_dim, pna_deg_hist=pna_deg_hist).to(device)

    # init classifier bias to base-rate prior
    try:
        prior_logit = math.log(max(1e-6, train_base_rate) / max(1e-6, 1.0 - train_base_rate))
        head = None
        if hasattr(model, "head") and isinstance(model.head, nn.Sequential):
            for m in reversed(model.head):
                if isinstance(m, nn.Linear) and m.out_features in (1, 2):
                    head = m
                    break
        if head is not None and head.bias is not None:
            with torch.no_grad():
                if head.out_features == 1:
                    head.bias.fill_(prior_logit)
                else:
                    b = torch.zeros_like(head.bias)
                    if b.numel() == 2:
                        b[1] = +0.5 * prior_logit
                        b[0] = -0.5 * prior_logit
                        head.bias.copy_(b)
            print(f"[Init] Classifier bias set from base-rate={train_base_rate:.6f} → prior_logit={prior_logit:.4f} (out_dim={head.out_features})")
    except Exception as e:
        print(f"[Init][WARN] Bias prior init skipped: {e}")

    # aux heads / banks
    dom_head = None
    if float(getattr(args, "lambda_dom", 0.0)) > 0.0:
        dom_head = DomainAdapter(in_dim=args.hidden_dim, hidden=max(64, args.hidden_dim // 2)).to(device)
    delta_head = DeltaHead(args.hidden_dim, hidden=max(64, args.hidden_dim // 2)).to(device) \
                if bool(getattr(args, "delta_head", False)) else None
    proto_bank = PrototypeBank(args.hidden_dim, args.num_classes,
                            ema_momentum=float(getattr(args, "proto_ema_m", 0.999))).to(device) \
                if float(getattr(args, "proto_w", 0.0)) > 0.0 else None

    print(f"[STAGE] {str(args.stage).upper()} | model={args.model} | T={args.T} T-test={args.T_test}")

    # optimizer (include heads) — build BEFORE scheduler
    decay, no_decay = [], []
    def _bucket(named_params):
        for n, p in named_params:
            if not p.requires_grad:
                continue
            if n.endswith(".bias") or "norm" in n.lower() or "bn" in n.lower() or "layernorm" in n.lower():
                no_decay.append(p)
            else:
                decay.append(p)

    _bucket(model.named_parameters())
    if delta_head is not None: _bucket(delta_head.named_parameters())
    if dom_head is not None:   _bucket(dom_head.named_parameters())

    optimizer = torch.optim.AdamW(
        [
            {"params": decay,    "weight_decay": min(0.01, float(getattr(args, "weight_decay", 0.01)))},
            {"params": no_decay, "weight_decay": 0.0},
        ],
        lr=float(getattr(args, "lr", 1e-4)),
    )
    scaler = GradScaler(enabled=(not bool(getattr(args, "no_amp", False))))

    # ---- LR warmup scheduler (per-step) ----
    # Linear warmup → then flat LR (no decay), computed in UPDATE-steps (after grad accumulation)
    accum_steps = max(1, int(getattr(args, "accum_steps", 1)))
    steps_per_epoch = max(1, math.ceil(len(train_loader) / accum_steps))
    epochs = int(getattr(args, "epochs", 0))
    total_updates = max(1, steps_per_epoch * max(0, epochs))

    warmup_frac  = float(getattr(args, "warmup_frac", 0.1))
    warmup_steps_cfg = int(getattr(args, "warmup_steps", 0))
    warmup_steps = warmup_steps_cfg if warmup_steps_cfg > 0 else int(warmup_frac * total_updates)

    from torch.optim.lr_scheduler import LambdaLR
    def _lr_lambda(step_idx: int):
        # step_idx counts optimizer.update() calls
        if warmup_steps <= 0:
            return 1.0
        if step_idx < warmup_steps:
            return max(1e-3, float(step_idx + 1) / float(max(1, warmup_steps)))
        return 1.0

    scheduler = LambdaLR(optimizer, lr_lambda=_lr_lambda)


    # ─────────────────────────────────────────────
    # Optional contrastive pretrain (projector head) — with graph-level augmentations
    # ─────────────────────────────────────────────
    if args.stage in ("pretrain", "both") and bool(getattr(args, "do_contrastive", False)) and int(getattr(args, "pre_epochs", 0)) > 0:
        projector = nn.Sequential(
            nn.Linear(args.hidden_dim, args.hidden_dim),
            nn.ReLU(inplace=True),
            nn.Linear(args.hidden_dim, max(64, args.hidden_dim // 2))
        ).to(device)

        opt_pre = torch.optim.AdamW(
            list(model.parameters()) + list(projector.parameters()),
            lr=float(getattr(args, "pre_lr", 3e-4)),
            weight_decay=min(0.01, float(getattr(args, "weight_decay", 0.01)))
        )
        scaler_pre = GradScaler(enabled=(not bool(getattr(args, "no_amp", False))))

        # graph-level augmentation strengths for pretrain (fallback to train-time flags if pre_* not provided)
        pre_dropedge_p      = float(getattr(args, "pre_dropedge_p", getattr(args, "dropedge_p", 0.0)))
        pre_feat_noise_std  = float(getattr(args, "pre_feat_noise_std", getattr(args, "train_feat_noise_std", 0.0)))
        tau = max(1e-6, float(getattr(args, "tau", 0.1)))  # temperature for NT-Xent

        for ep in _tqdm(range(1, int(args.pre_epochs) + 1), desc="Pretrain epochs", disable=args.no_progress, total=int(args.pre_epochs)):
            model.train(); projector.train()
            total_pre = 0.0

            for batch in _tqdm(train_loader, desc="Pretrain (batches)", disable=args.no_progress, total=len(train_loader)):
                b = batch.to(device, non_blocking=True)
                opt_pre.zero_grad(set_to_none=True)

                # build TWO graph views with mild, independent augmentations
                b1 = _augment_batch_for_eval(b, dropedge_p=pre_dropedge_p,     feat_noise_std=pre_feat_noise_std)
                b2 = _augment_batch_for_eval(b, dropedge_p=pre_dropedge_p,     feat_noise_std=pre_feat_noise_std)

                with autocast(enabled=(not bool(getattr(args, "no_amp", False)))):
                    # forward both views through the GNN encoder
                    out1 = model(b1)
                    out2 = model(b2)
                    emb1 = out1["emb"] if isinstance(out1, dict) else None
                    emb2 = out2["emb"] if isinstance(out2, dict) else None

                    # safe fallbacks in case model does not expose "emb"
                    if emb1 is None or emb2 is None:
                        if getattr(b1, "batch", None) is not None:
                            from torch_geometric.nn import global_mean_pool
                            emb1 = global_mean_pool(b1.x, b1.batch)
                            emb2 = global_mean_pool(b2.x, b2.batch)
                        else:
                            emb1 = torch.mean(b1.x, dim=0, keepdim=True).repeat(b1.num_graphs, 1)
                            emb2 = torch.mean(b2.x, dim=0, keepdim=True).repeat(b2.num_graphs, 1)

                    # numerical safety
                    emb1 = torch.nan_to_num(emb1, nan=0.0, posinf=1e6, neginf=-1e-6)
                    emb2 = torch.nan_to_num(emb2, nan=0.0, posinf=1e6, neginf=-1e-6)

                    # projector + dropout on embeddings
                    z1 = projector(F.dropout(emb1, p=0.2, training=True))
                    z2 = projector(F.dropout(emb2, p=0.2, training=True))

                    # normalize and build similarity matrices
                    z1n = F.normalize(z1.float(), dim=-1, eps=1e-12)
                    z2n = F.normalize(z2.float(), dim=-1, eps=1e-12)
                    logits_12 = (z1n @ z2n.t()) / tau
                    logits_21 = (z2n @ z1n.t()) / tau
                    logits_12 = torch.nan_to_num(logits_12, nan=0.0).clamp_(-30, 30)
                    logits_21 = torch.nan_to_num(logits_21, nan=0.0).clamp_(-30, 30)

                    # InfoNCE / NT-Xent with identity positives
                    target = torch.arange(z1.size(0), device=z1.device)
                    loss_pre = 0.5 * (F.cross_entropy(logits_12, target) + F.cross_entropy(logits_21, target))

                scaler_pre.scale(loss_pre).backward()
                scaler_pre.unscale_(opt_pre)
                torch.nn.utils.clip_grad_norm_(list(model.parameters()) + list(projector.parameters()), max_norm=1.0)
                scaler_pre.step(opt_pre)
                scaler_pre.update()

                lp = float(loss_pre.detach().cpu().item())
                if not (math.isnan(lp) or math.isinf(lp)):
                    total_pre += lp

            if not args.no_progress:
                tqdm.write(f"[Pretrain] epoch {ep:03d}/{int(args.pre_epochs)} loss={total_pre/max(1,len(train_loader)):.4f}")

        if args.stage == "pretrain":
            return {"pretrain_loss_last": float(total_pre / max(1, len(train_loader)))}

    # ─────────────────────────────────────────────
    # Supervised training (fine-tune/both)
    # ─────────────────────────────────────────────
    best_f1, best_state, best_epoch, best_delta = -1.0, None, -1, None
    calib_cfg = CalibConfig(
        beta=float(getattr(args, "calib_beta", 0.8)),
        min_precision=(None if getattr(args, "min_precision", None) is None else float(args.min_precision)),
        max_pos_rate_over_base=1.0 + float(getattr(args, "calib_max_pos_delta", 0.0)),
        min_pos_frac=float(getattr(args, "calib_min_pos_frac", 0.0)),
        ema_alpha=float(getattr(args, "thr_ema_alpha", 0.6)),
    )
    # ensure optional recall constraint is wired
    setattr(calib_cfg, "min_recall", (None if getattr(args, "min_recall", None) is None else float(args.min_recall)))

    thr_ema = None
    global_step = 0

    reg_warmup_epochs = int(getattr(args, "reg_warmup_epochs", 3))
    def _reg_scale(ep: int) -> float:
        if reg_warmup_epochs <= 0:
            return 1.0
        return float(min(1.0, ep / float(reg_warmup_epochs)))

    epoch_iter = range(1, int(getattr(args, "epochs", 0)) + 1) \
        if args.stage in ("fine-tune", "both") and int(getattr(args, "epochs", 0)) > 0 else []

    for ep in _tqdm(epoch_iter, desc="Train epochs", disable=args.no_progress, total=int(getattr(args, "epochs", 0))):
        # scale regularizers with warmup
        s = _reg_scale(ep)
        args_train = SimpleNamespace(**vars(args))
        args_train.consistency_w = float(getattr(args, "consistency_w", 0.0)) * s
        args_train.supcon_w     = float(getattr(args, "supcon_w", 0.0)) * s
        args_train.proto_w      = float(getattr(args, "proto_w", 0.0)) * s
        args_train.delta_w      = float(getattr(args, "delta_w", 0.0)) * s

        # one epoch of training
        tr_loss, global_step = train_epoch_mutant_aware(
            model=model, loader=train_loader, device=device,
            optimizer=optimizer, scaler=scaler, amp=(not bool(getattr(args, "no_amp", False))),
            args=args_train, dom_head=dom_head, delta_head=delta_head, proto_bank=proto_bank,
            global_step=global_step, scheduler=scheduler
        )

        if not args.no_progress:
            _lr = optimizer.param_groups[0].get("lr", float(getattr(args, "lr", 0.0)))
            print(f"[Opt] lr={_lr:.6g}")

        # collect VAL probabilities (T=1.0, optional TTA)
        yv, pv = collect_probs_with_T(
            model, val_loader, device, T=float(getattr(args, "T", 1.0)),
            tta=int(getattr(args, "tta", 0)),
            tta_dropedge_p=float(getattr(args, "tta_dropedge_p", 0.0)),
            tta_feat_noise_std=float(getattr(args, "tta_feat_noise_std", 0.0))
        )

        # quick clamp-check eval at base-rate quantile
        thr_base = float(np.quantile(pv, 1.0 - train_base_rate)) if len(pv) else 0.5
        val_m_base = evaluate(
            model, val_loader, device, threshold=thr_base, temperature=1.0,
            tta=int(getattr(args, "tta", 0)),
            tta_dropedge_p=float(getattr(args, "tta_dropedge_p", 0.0)),
            tta_feat_noise_std=float(getattr(args, "tta_feat_noise_std", 0.0))
        )
        print(
            f"[ClampCheck] thr@base={thr_base:.4f} (base_rate={train_base_rate:.4f}) "
            f"→ VAL: F1={val_m_base['f1']:.4f} P={val_m_base['prec']:.4f} "
            f"R={val_m_base['rec']:.4f} AUC={val_m_base['auc']}"
        )

        if not args.no_progress and len(pv):
            pv_np = np.asarray(pv, dtype=np.float64)
            q = np.quantile(pv_np, [0.01, 0.05, 0.5, 0.95, 0.99])
            print(
                f"[ValProbs] N={pv_np.size} mean={pv_np.mean():.4f} std={pv_np.std():.6f} "
                f"min={pv_np.min():.4f} q01={q[0]:.4f} q05={q[1]:.4f} med={q[2]:.4f} "
                f"q95={q[3]:.4f} q99={q[4]:.4f} max={pv_np.max():.4f}"
            )

        # calibrate threshold on VAL (robust sweep)
        thr_calib, _stats = calibrate_threshold(yv, pv, cfg=calib_cfg, base_rate=train_base_rate)
        if not args.no_progress:
            print(
                f"[Calib] raw_thr={_stats.get('thr_raw', thr_calib):.6f} adj_thr={_stats.get('thr', thr_calib):.6f} "
                f"| pos_rate={_stats.get('pos_rate', float('nan')):.4f} base={train_base_rate:.4f} "
                f"| F={_stats.get('f', float('nan')):.4f} P={_stats.get('p', float('nan')):.4f} R={_stats.get('r', float('nan')):.4f}"
            )

        # EMA of threshold with flat-output fallback
        if ep == 1 or thr_ema is None or not np.isfinite(thr_ema):
            thr_ema = float(thr_calib)
        else:
            thr_ema = float(calib_cfg.ema_alpha * thr_calib + (1.0 - calib_cfg.ema_alpha) * thr_ema)

        if len(pv):
            pv_np = np.asarray(pv, dtype=np.float64)
            if float(pv_np.std()) < 1e-6 or float(pv_np.max() - pv_np.min()) < 1e-6:
                q = min(1.0 - 1e-6, max(1e-6, 1.0 - train_base_rate))
                thr_ema = float(np.quantile(pv_np, q))
        else:
            thr_ema = 0.5

        # evaluate VAL with smoothed threshold
        val_m = evaluate(
            model, val_loader, device, threshold=thr_ema, temperature=float(getattr(args, "T", 1.0)),
            tta=int(getattr(args, "tta", 0)),
            tta_dropedge_p=float(getattr(args, "tta_dropedge_p", 0.0)),
            tta_feat_noise_std=float(getattr(args, "tta_feat_noise_std", 0.0))
        )

        # track & save best checkpoint
        if val_m["f1"] > best_f1:
            best_f1 = float(val_m["f1"])
            best_state = {k: v.detach().cpu() for k, v in model.state_dict().items()}
            best_delta = ({k: v.detach().cpu() for k, v in delta_head.state_dict().items()} if delta_head is not None else None)
            best_epoch = int(ep)
            best_ckpt = {
                "state_dict": best_state,
                "delta_head": best_delta,
                "args": vars(args),
                "val_metrics": val_m,
                "epoch": best_epoch,
                "thr_ema": float(thr_ema),
            }
            torch.save(best_ckpt, layout["checkpoints"] / "best.pt")

        if not args.no_progress:
            print(
                f"[Train] ep {ep:03d}/{int(getattr(args,'epochs',0))} "
                f"loss={tr_loss:.4f} | thr_ema={thr_ema:.4f} | "
                f"Val: F1={val_m['f1']:.4f} P={val_m['prec']:.4f} R={val_m['rec']:.4f} AUC={val_m['auc']}"
            )


    # ── load best (if any)
    if best_state is not None:
        model.load_state_dict(best_state)
        if best_delta is not None and delta_head is not None:
            delta_head.load_state_dict(best_delta)

    # ── optional temperature scaling on VAL
    T_val = fit_temperature(model, val_loader, device) if bool(getattr(args, "do_temperature", False)) else 1.0
    thr_post = transform_threshold_preT_to_postT(float(thr_ema if thr_ema is not None else 0.5), float(T_val)) \
               if bool(getattr(args, "do_temperature", False)) else float(thr_ema if thr_ema is not None else 0.5)

    # ── final test
    test_m = evaluate(
         model, test_loader, device, threshold=thr_post, temperature=float(getattr(args, "T_test", 1.0)),
        tta=int(getattr(args, "tta", False)),
        tta_dropedge_p=float(getattr(args, "tta_dropedge_p", 0.0)),
        tta_feat_noise_std=float(getattr(args, "tta_feat_noise_std", 0.0))
    )

    # ── write results
    out_dir = layout["results"] if args.output_dir == "./results_draper" else Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    def _jsonify(o):
        import numpy as _np
        if isinstance(o, _np.ndarray): return o.tolist()
        if isinstance(o, (_np.floating, _np.integer, _np.bool_)): return o.item()
        if isinstance(o, dict):  return {k: _jsonify(v) for k, v in o.items()}
        if isinstance(o, (list, tuple)): return [_jsonify(v) for v in o]
        return o

    with open(out_dir / "test_metrics.json", "w", encoding="utf-8") as f:
        json.dump(_jsonify(test_m), f, indent=2)

    try:
        with open(layout["checkpoints"] / "best_summary.json", "w", encoding="utf-8") as f:
            json.dump({"best_val_f1": best_f1, "best_epoch": best_epoch, "thr_ema": float(thr_ema if thr_ema is not None else 0.5)}, f, indent=2)
    except Exception:
        pass

    # Optional confusion matrix image
    try:
        cm = test_m.get("cm", None)
        if cm is not None:
            fig = plt.figure(figsize=(4, 4))
            plt.imshow(cm, interpolation="nearest"); plt.title("Confusion Matrix"); plt.colorbar()
            tick = np.arange(2); plt.xticks(tick, ["0","1"]); plt.yticks(tick, ["0","1"])
            for i in range(2):
                for j in range(2):
                    plt.text(j, i, format(cm[i, j], 'd'), ha="center", va="center")
            plt.ylabel("True"); plt.xlabel("Predicted"); plt.tight_layout()
            fig.savefig(out_dir / "confusion_matrix.png", dpi=160); plt.close(fig)
    except Exception:
        pass

    print(f"[TEST] F1={test_m['f1']:.4f} P={test_m['prec']:.4f} R={test_m['rec']:.4f} AUC={test_m['auc']} thr_post={thr_post:.4f} T={T_val:.3f}")
    return test_m




# ────────────────────────────────────────────
# CLI  [COMPLETED]
# ────────────────────────────────────────────
def build_parser():
    parser = argparse.ArgumentParser(
        description="MPTCN-TTS Draper mutant-aware runner",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        allow_abbrev=False,
    )

    # Core model/data
    parser.add_argument("--model", type=str, default="deepergcn",
                        choices=["mptcn_tts","gin","gat","gcn","sage","mpnn","rgcn","han","dgcnn","pna","deepergcn"])
    parser.add_argument("--spatial", type=str, default="gcn")
    parser.add_argument("--temporal", type=str, default="tcn", choices=["tcn","gru"])
    parser.add_argument("--num-classes", type=int, default=2, dest="num_classes")
    parser.add_argument("--emb-dim", type=int, default=64, dest="emb_dim")
    parser.add_argument("--hidden-dim", type=int, default=256, dest="hidden_dim")
    parser.add_argument("--layers", type=int, default=6)
    parser.add_argument("--heads", type=int, default=2)
    parser.add_argument("--bases", type=int, default=4, help="num_relations for RGCN")
    parser.add_argument("--hgt-heads", type=int, default=1, dest="hgt_heads")
    parser.add_argument("--hgt-max-rel", type=int, default=800, dest="hgt_max_rel")

    parser.add_argument("--lambda-dom", type=float, default=0.0,
                        help="Weight for domain adaptation loss (GRL).")
    parser.add_argument("--dropedge-p", type=float, default=0.0,
                        help="Probability to drop edges (train/eval augmentation).")
    parser.add_argument("--train-feat-noise-std", type=float, default=0.0,
                        help="Std dev of Gaussian noise added to node features during training.")
    parser.add_argument("--edge-emb-dim", type=int, default=16,
                        help="Edge embedding dim for MPNN/NNConv.")
    parser.add_argument("--readout", type=str, default="mean",
                        choices=["mean", "sum"], help="Global readout.")
    parser.add_argument("--feature-dim", type=int, default=64, dest="feature_dim",
                        help="Default node feature width used for dataset fallbacks and/or simple featurizers.")

    # Input feature wiring

    # Data IO
    parser.add_argument("--train-manifest", type=str, required=True)
    parser.add_argument("--val-manifest",   type=str, required=True)
    parser.add_argument("--test-manifest",  type=str, required=True)

    parser.add_argument("--json-root", type=str, default=None, help="Fallback root if per-split roots not provided")
    parser.add_argument("--train-json-root", type=str, default=None)
    parser.add_argument("--val-json-root",   type=str, default=None)
    parser.add_argument("--test-json-root",  type=str, default=None)

    parser.add_argument("--cache-dir", type=str, default=None,
                        help="Directory to save/load cached graphs & precomputations (defaults to <json_root>/../cache_draper)")
    parser.add_argument("--cache-overwrite", action="store_true",
                        help="Overwrite existing caches instead of loading them")

    # Vocab lifecycle
    parser.add_argument("--rebuild-vocabs", action="store_true",
                        help="Force rebuilding node/edge vocabs from TRAIN and overwrite saved ones")
    parser.add_argument("--allow-empty-vocabs", action="store_true",
                        help="Do not auto-rebuild even if loaded vocabs are empty (not recommended)")

    # JSON handling & audit
    parser.add_argument("--strict-json", action="store_true",
                        help="Error if a JSON is missing/malformed (recommended only when auditing)")
    parser.add_argument("--min-json-coverage", type=float, default=0.80,
                        help="Abort if TRAIN JSON coverage below this fraction")
    parser.add_argument("--report-missing", type=int, default=20,
                        help="How many missing-path messages to print per split")

    # Family sampling / collapse (TRAIN ONLY)
    parser.add_argument("--collapse-policy", type=str, default="all",
                        choices=["all","latest","orig","orig+k"],
                        help="How to subsample snapshots per family for TRAIN.")
    parser.add_argument("--collapse-k", type=int, default=2,
                        help="K for 'orig+k' policy (ignored otherwise).")



    # Cache sharding / tmp & merge
    parser.add_argument("--cache-shards", type=int, default=1,
                        help="If >1, use sharded ZIP cache (N shards) to avoid single-writer I/O bottleneck.")
    parser.add_argument("--cache-tmpdir", type=str, default="",
                        help="Optional fast tmp dir for shard ZIPs (e.g., /dev/shm). If empty, use <cache_dir>/shards.")
    # default = merge & delete shards after warm (space-safe). Allow user to disable if needed.
    parser.add_argument("--merge-shards", dest="merge_shards", action="store_true",
                        help="Merge shards into a single graph_cache.zip after cache warm.")
    parser.add_argument("--no-merge-shards", dest="merge_shards", action="store_false",
                        help="Do not merge shards after warm.")
    parser.set_defaults(merge_shards=True)

    parser.add_argument("--delete-shards-after-merge", dest="delete_shards_after_merge", action="store_true",
                        help="Delete shard ZIPs after a successful merge.")
    parser.add_argument("--keep-shards-after-merge", dest="delete_shards_after_merge", action="store_false",
                        help="Keep shard ZIPs after merge (not recommended with limited disk).")
    parser.set_defaults(delete_shards_after_merge=True)


    parser.add_argument("--prefetch-factor", type=int, default=1)
    parser.add_argument("--eval-prefetch-factor", type=int, default=None)  # falls back to prefetch-factor
    parser.add_argument("--persistent-workers", action="store_true")
    parser.add_argument("--eval-persistent-workers", action="store_true")
    parser.add_argument("--eval-num-workers", type=int, default=None)
    parser.add_argument("--warn-collapse-budget", type=int, default=6)



    # Temps / architecture knobs
    parser.add_argument("--T", type=float, default=1.0)
    parser.add_argument("--T-test", type=float, default=1.0, dest="T_test")
    parser.add_argument("--Lt", type=int, default=2)
    parser.add_argument("--Ls", type=int, default=2)
    parser.add_argument("--Kt", type=int, default=3)
    parser.add_argument("--Ks", type=int, default=3)

    # Regularization
    parser.add_argument("--dropout", type=float, default=0.3)
    parser.add_argument("--row-norm", action="store_true")
    parser.add_argument("--mixup-alpha", type=float, default=0.0)
    parser.add_argument("--temporal-jitter", type=float, default=0.0)
    parser.add_argument("--logit-l2", type=float, default=0.0)
    parser.add_argument("--focal-gamma", type=float, default=0.0, dest="focal_gamma")

    # Train
    parser.add_argument("--stage", choices=["both","pretrain","fine-tune"], default="both")
    parser.add_argument("--epochs", type=int, default=25)
    parser.add_argument("--batch-size", type=int, default=64)
    parser.add_argument("--train-batch-size", type=int, default=None)
    parser.add_argument("--eval-batch-size", type=int, default=128)
    parser.add_argument("--accum-steps", type=int, default=1)
    parser.add_argument("--lr", type=float, default=1e-4)
    parser.add_argument("--pre-lr", type=float, default=1e-3, dest="pre_lr")
    parser.add_argument("--weight-decay", type=float, default=0.05)
    parser.add_argument("--early-stop", type=int, default=0)
    parser.add_argument("--val-interval", type=int, default=1)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--no-progress", action="store_true", help="Disable tqdm progress bars" ,default=False)
    parser.add_argument("--label-smoothing", type=float, default=0.02)
    parser.add_argument("--head-warmup-steps", type=int, default=500)
    # Add this line near the other DataLoader-related arguments
    parser.add_argument("--cache-workers", type=int, default=4,
                    help="Number of workers for cache warming (default: 4). Use a low value like 4 to avoid I/O contention.")

    # AMP/Device
    parser.add_argument("--no-amp", action="store_true")
    parser.add_argument("--no-cuda", action="store_true")
    parser.add_argument("--num-workers", type=int, default=0)

    # Pretrain controls
    parser.add_argument("--do-contrastive", action="store_true")
    parser.add_argument("--pre-epochs", type=int, default=0)
    parser.add_argument("--tau", type=float, default=0.1)

    # Add this to your argument parser
    parser.add_argument("--new-cache-dir", type=str, default=None,
                        help="Directory for new cache (leaves old cache intact). If specified, will create new cache in this location.")

    # Mutant-aware heads & losses
    parser.add_argument("--consistency-w", type=float, default=0.0, help="Weight for in-family consistency loss")
    parser.add_argument("--supcon-w", type=float, default=0.0, help="Weight for supervised contrastive loss")
    parser.add_argument("--supcon-tau", type=float, default=0.07, help="Temperature for SupCon")
    parser.add_argument("--supcon-mode", type=str, default="label+family", choices=["label","label+family"])

    parser.add_argument("--proto-w", type=float, default=0.0, help="Weight for prototype regularizer")
    parser.add_argument("--proto-ema-m", type=float, default=0.9, help="EMA for prototype bank")

    parser.add_argument("--delta-head", action="store_true", help="Enable auxiliary delta head")
    parser.add_argument("--delta-w", type=float, default=0.0, help="Weight for delta head BCE loss")
    parser.add_argument("--delta-pairs-per-family", type=int, default=2, help="Max sampled pairs per family per batch")

    # Symmetric CE
    parser.add_argument("--use-sce", action="store_true")
    parser.add_argument("--sce-after", type=int, default=5, help="Use SCE after this many steps")
    parser.add_argument("--sce-alpha", type=float, default=0.5)
    parser.add_argument("--sce-beta", type=float, default=0.5)
    parser.add_argument("--sce-epsilon", type=float, default=0.1)

    # Calibration / Temperature
    parser.add_argument("--min-precision", type=float, default=None)
    parser.add_argument("--min-recall", type=float, default=None)
    parser.add_argument("--calib-beta", type=float, default=1.0)
    parser.add_argument("--thr-ema-alpha", type=float, default=0.6, dest="thr_ema_alpha")
    parser.add_argument("--calib-max-pos-delta", type=float, default=None, dest="calib_max_pos_delta")
    parser.add_argument("--calib-min-pos-frac", type=float, default=0.02, dest="calib_min_pos_frac")
    parser.add_argument("--do-temperature", action="store_true")

    # In the argument parser section (around line 1200)
    parser.add_argument("--one-hot", dest="one_hot", action="store_true", default=False,
                        help="Assume parser emits one-hot node features (width=len(node_vocab)).")
    parser.add_argument("--no-one-hot", dest="one_hot", action="store_false",
                        help="Use dense features instead of one-hot encoding (default).")
    # ---- Startup toggles / safety ----
    parser.add_argument("--warm-cache", dest="warm_cache", action="store_true",
                        help="Pre-fill graph zip cache before training/eval (OFF by default)")
    parser.add_argument("--no-warm-cache", dest="warm_cache", action="store_false")
    parser.set_defaults(warm_cache=False)

    parser.add_argument("--quick-stats", dest="quick_stats", action="store_true",
                        help="Scan a sample of graphs and print size histograms (OFF by default)")
    parser.add_argument("--no-quick-stats", dest="quick_stats", action="store_false")
    parser.set_defaults(quick_stats=False)

    parser.add_argument("--audit", dest="do_audit", action="store_true",
                        help="Audit JSON path coverage (ON by default)")
    parser.add_argument("--no-audit", dest="do_audit", action="store_false")
    parser.set_defaults(do_audit=True)

    parser.add_argument("--parse-debug", action="store_true",
                        help="Verbose parse prints for each JSON (very slow)")

    parser.add_argument("--loader-timeout", type=int, default=0,
                        help="Timeout (sec) for DataLoader workers; 0 disables")

    parser.add_argument("--mp-context", choices=["fork", "forkserver", "spawn"], default=None,
                        help="Multiprocessing start method for DataLoader workers")

    parser.add_argument("--dry-run", type=int, default=0,
                        help="If >0, parse N graphs from TRAIN then exit (debug parsing/hangs)")

    # You reference this later; define it so CLI accepts it
    parser.add_argument("--max-pos-weight", type=float, default=8.0,
                        help="Cap on computed pos_weight to avoid instability")



    # Test-time augmentation
    parser.add_argument("--tta", type=int, default=0, help="# augmented eval passes to average")
    parser.add_argument("--tta-dropedge-p", type=float, default=0.0)
    parser.add_argument("--tta-feat-noise-std", type=float, default=0.0)

    # Output
    parser.add_argument("--output-dir", type=str, default="./results_draper")

    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)

    # Stage normalization
    if args.stage == "pretrain":
        args.do_contrastive = True
        args.epochs = 0
    elif args.stage == "fine-tune":
        args.do_contrastive = False
        args.pre_epochs = 0

    run(args)


if __name__ == "__main__":
    main()


# ────────────────────────────────────────────
# Preset command combos (T=3)
# ────────────────────────────────────────────
"""
A (mptcn_tts • cheb • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 1 \
  --Kt 5 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 1e-4 \
  --dropout 0.5 \
  --focal-gamma 1 \
  --row-norm \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.09 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 1 \
  --Kt 5 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.5 \
  --focal-gamma 1 \
  --row-norm \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 1 \
  --Kt 5 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.5 \
  --focal-gamma 1 \
  --row-norm \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.09 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

B (mptcn_tts • cheb • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --row-norm \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 3e-4 \
  --dropout 0.2 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.1 \
  --supcon-lambda 0.1 \
  --supcon-tau 0.07 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --row-norm \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 3e-4 \
  --dropout 0.2 \
  --supcon-lambda 0.1 \
  --supcon-tau 0.07 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --row-norm \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 3e-4 \
  --dropout 0.2 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.1 \
  --supcon-lambda 0.1 \
  --supcon-tau 0.07 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

C (mptcn_tts • cheb • gru)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 5e-4 \
  --dropout 0.3 \
  --focal-gamma 1 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 192 \
  --epochs 30 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.25 \
  --label-smoothing 0.0 \
  --focal-gamma 0.8 \
  --max-pos-weight 4.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.05 \
  --supcon-w 0.02 --supcon-tau 0.07 \
  --proto-w 0.01 \
  --tta 2 \
  --T 1 --T-test 1 \
  --do-temperature \
  --calib-beta 1.5 \
  --min-recall 0.35 \
  --min-precision 0.30 \
  --calib-max-pos-delta 0.60 \
  --calib-min-pos-frac 0.04 \
  --thr-ema-alpha 0.80 \
  --val-interval 1 \
  --num-workers 32 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --cache-dir "./Json_exports/cache_draper"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 5e-4 \
  --dropout 0.3 \
  --focal-gamma 1 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

D (mptcn_tts • rgcn • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 3e-4 \
  --dropout 0.3 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.15 \
  --supcon-lambda 0.1 \
  --supcon-tau 0.07 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 192 \
  --epochs 30 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.25 \
  --label-smoothing 0.0 \
  --focal-gamma 0.8 \
  --max-pos-weight 4.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.05 \
  --supcon-w 0.02 --supcon-tau 0.07 \
  --proto-w 0.01 \
  --tta 2 \
  --T 1 --T-test 1 \
  --do-temperature \
  --calib-beta 1.5 \
  --min-recall 0.35 \
  --min-precision 0.30 \
  --calib-max-pos-delta 0.60 \
  --calib-min-pos-frac 0.04 \
  --thr-ema-alpha 0.80 \
  --val-interval 1 \
  --num-workers 32 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --cache-dir "./Json_exports/cache_draper"




Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 3e-4 \
  --dropout 0.3 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.15 \
  --supcon-lambda 0.1 \
  --supcon-tau 0.07 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

E (mptcn_tts • hgt • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 64 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 1e-4 \
  --dropout 0.3 \
  --early-stop 8 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.1 \
  --lambda-dom 0.03 \
  --supcon-lambda 0.05 \
  --supcon-tau 0.07 \
  --hgt-max-rel 800 \
  --hgt-heads 1 \
  --cache-after-pretrain \
  --cache-head-epochs 10 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 64 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.3 \
  --early-stop 8 \
  --lambda-dom 0.03 \
  --supcon-lambda 0.05 \
  --supcon-tau 0.07 \
  --hgt-max-rel 800 \
  --hgt-heads 1 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 64 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.3 \
  --early-stop 8 \
  --do-contrastive \
  --pre-epochs 60 \
  --tau 0.1 \
  --lambda-dom 0.03 \
  --supcon-lambda 0.05 \
  --supcon-tau 0.07 \
  --hgt-max-rel 800 \
  --hgt-heads 1 \
  --cache-after-pretrain \
  --cache-head-epochs 10 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

F (mptcn_tts • cheb • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 3e-4 \
  --dropout 0.3 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 3e-4 \
  --dropout 0.3 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --Ks 3 \
  --batch-size 256 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 3e-4 \
  --dropout 0.3 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"

G (mptcn_tts • rgcn • gru)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal gru \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 192 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.25 \
  --lambda-dom 0.02 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal gru \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 192 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 30 \
  --lr 2e-4 \
  --dropout 0.25 \
  --lambda-dom 0.02 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal gru \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 192 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 30 \
  --lr 2e-4 \
  --dropout 0.25 \
  --lambda-dom 0.02 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


H (mptcn_tts • hgt • tcn)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 1e-4 \
  --dropout 0.4 \
  --supcon-lambda 0.2 \
  --supcon-tau 0.07 \
  --lambda-dom 0.05 \
  --hgt-heads 2 \
  --hgt-max-rel 800 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.4 \
  --supcon-lambda 0.2 \
  --supcon-tau 0.07 \
  --lambda-dom 0.05 \
  --hgt-heads 2 \
  --hgt-max-rel 800 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 3 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 1e-4 \
  --dropout 0.4 \
  --supcon-w 0.2 \
  --supcon-tau 0.07 \
  --lambda-dom 0.05 \
  --hgt-heads 2 \
  --hgt-max-rel 800 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


I1 (pna • tcn • Ls=2)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model pna \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 16 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.2 \
  --row-norm \
  --focal-gamma 0.0 \
  --supcon-lambda 0.02 \
  --supcon-tau 0.07 \
  --lambda-dom 0.0 \
  --dropedge-p 0.0 \
  --temporal-jitter 0.0 \
  --accum-steps 2 \
  --min-precision 0.70 \
  --min-recall 0.10 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model pna \
  --layers 4 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --readout mean \
  --dropout 0.2 \
  --batch-size 128 \
  --accum-steps 2 \
  --epochs 25 \
  --lr 3e-4 \
  --weight-decay 1e-4 \
  --focal-gamma 0 \
  --consistency-w 0 \
  --supcon-w 0 \
  --proto-w 0 \
  --lambda-dom 0 \
  --dropedge-p 0.0 \
  --train-feat-noise-std 0.01 \
  --T 3 --T-test 3 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --pre-epochs 0 \
  --feature-dim 64 \
  --one-hot \
  --min-json-coverage 0.80 \
  --num-workers 16 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --cache-overwrite \
  --cache-dir "./Json_exports/cache_draper"



Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --do-contrastive \
  --pre-epochs 60 \
  --model pna \
  --layers 4 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --readout mean \
  --dropout 0.2 \
  --batch-size 128 \
  --accum-steps 2 \
  --epochs 25 \
  --lr 3e-4 \
  --weight-decay 1e-4 \
  --focal-gamma 1.5 \
  --consistency-w 0 \
  --supcon-w 0.05 --supcon-tau 0.07 --supcon-mode label+family \
  --proto-w 0.05 --proto-ema-m 0.99 \
  --lambda-dom 0 \
  --dropedge-p 0.05 \
  --train-feat-noise-std 0.01 \
  --tta 4 \
  --tta-dropedge-p 0.05 \
  --tta-feat-noise-std 0.005 \
  --T 3 --T-test 3 \
  --calib-beta 1.5 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --feature-dim 64 \
  --one-hot \
  --min-json-coverage 0.80 \
  --num-workers 16 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --cache-dir "./Json_exports/cache_draper"


I2 (pna • tcn • Ls=4)

Pretrain

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model pna \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 4 \
  --Kt 3 \
  --batch-size 16 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 3e-4 \
  --dropout 0.25 \
  --row-norm \
  --focal-gamma 0.0 \
  --supcon-lambda 0.05 \
  --supcon-tau 0.10 \
  --lambda-dom 0.0 \
  --dropedge-p 0.05 \
  --temporal-jitter 0.05 \
  --mixup-alpha 0.10 \
  --accum-steps 1 \
  --calib-beta 0.7 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.08 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --logit-l2 2e-6 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"


Fine-tune

python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model pna \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 6 \
  --Kt 3 \
  --batch-size 128 \
  --accum-steps 2 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 0 \
  --lr 1e-3 \
  --weight-decay 1e-4 \
  --dropout 0.2 \
  --readout sum \
  --focal-gamma 0.0 \
  --supcon-w 0.02 \
  --supcon-tau 0.07 \
  --consistency-w 0.10 \
  --proto-w 0.05 \
  --delta-head --delta-w 0.02 \
  --dropedge-p 0.0 \
  --train-feat-noise-std 0.01 \
  --temporal-jitter 0.0 \
  --lambda-dom 0.03 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --do-contrastive \
  --pre-epochs 20 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json




Both

python MPTCN_TTS_Draper.py \
  --stage both \
  --model pna \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 6 \
  --Kt 3 \
  --batch-size 128 \
  --accum-steps 2 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
  --lr 2e-4 \
  --dropout 0.2 \
  --focal-gamma 0.0 \
  --supcon-w 0.02 \
  --supcon-tau 0.07 \
  --consistency-w 0.10 \
  --proto-w 0.05 \
  --delta-head --delta-w 0.02 \
  --dropedge-p 0.0 \
  --train-feat-noise-std 0.01 \
  --temporal-jitter 0.0 \
  --lambda-dom 0.03 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --do-contrastive \
  --pre-epochs 20 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json



J (deepergcn • gcn • tcn)

python MPTCN_TTS_Draper.py \
  --stage pretrain \
  --model deepergcn \
  --spatial gcn \
  --temporal tcn \
  --T 3 \
  --T-test 3 \
  --Lt 2 \
  --Ls 6 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.2 \
  --focal-gamma 0.0 \
  --supcon-lambda 0.02 \
  --supcon-tau 0.07 \
  --lambda-dom 0.0 \
  --dropedge-p 0.0 \
  --temporal-jitter 0.0 \
  --accum-steps 2 \
  --min-precision 0.70 \
  --min-recall 0.10 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --do-contrastive \
  --pre-epochs 60 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json" \
  --val-json-root   "./Json_exports/normalized_draper_json" \
  --test-json-root  "./Json_exports/normalized_draper_json"
```

**Fine-tune**

```bash
python MPTCN_TTS_Draper.py \
  --stage fine-tune \
  --model deepergcn \
  --layers 4 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --readout mean \
  --dropout 0.2 \
  --batch-size 128 \
  --accum-steps 2 \
  --epochs 25 \
  --lr 3e-4 \
  --weight-decay 1e-4 \
  --focal-gamma 0 \
  --consistency-w 0 \
  --supcon-w 0 \
  --proto-w 0 \
  --lambda-dom 0 \
  --dropedge-p 0.0 \
  --train-feat-noise-std 0.01 \
  --T 3 --T-test 3 \
  --calib-beta 0.6 \
  --thr-ema-alpha 0.10 \
  --calib-max-pos-delta 0.05 \
  --calib-min-pos-frac 0.02 \
  --val-interval 1 \
  --pre-epochs 0 \
  --feature-dim 64 \
  --one-hot \
  --min-json-coverage 0.80 \
  --num-workers 16 \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --cache-dir "./Json_exports/cache_draper"

```

**Both**

```bash
python MPTCN_TTS_Draper_2.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 192 \
  --epochs 30 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.25 \
  --label-smoothing 0.0 \
  --focal-gamma 0.8 \
  --max-pos-weight 4.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.05 \
  --supcon-w 0.02 --supcon-tau 0.07 \
  --proto-w 0.01 \
  --tta 2 \
  --T 1 --T-test 1 \
  --do-temperature \
  --calib-beta 1.5 \
  --min-recall 0.35 \
  --min-precision 0.30 \
  --calib-max-pos-delta 0.60 \
  --calib-min-pos-frac 0.04 \
  --thr-ema-alpha 0.80 \
  --val-interval 1 \
  --num-workers 4\
  --cache-workers 4 \
  --warm-cache \
  --new-cache-dir "./Json_exports/cache_draper_v2" \
  --cache-dir "./Json_exports/cache_draper" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json \
  --no-one-hot



```




python MPTCN_TTS_Draper_2.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 192 \
  --epochs 30 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --lr 2e-4 \
  --dropout 0.25 \
  --label-smoothing 0.0 \
  --focal-gamma 0.8 \
  --max-pos-weight 4.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.05 \
  --supcon-w 0.02 \
  --supcon-tau 0.07 \
  --proto-w 0.01 \
  --tta 2 \
  --T 1 \
  --T-test 1 \
  --do-temperature \
  --calib-beta 1.5 \
  --min-recall 0.35 \
  --min-precision 0.30 \
  --calib-max-pos-delta 0.60 \
  --calib-min-pos-frac 0.04 \
  --thr-ema-alpha 0.80 \
  --val-interval 1 \
  --num-workers 32 \
  --warm-cache \
  --no-one-hot \
  --new-cache-dir "./Json_exports/cache_draper_v2" \
  --cache-dir "./Json_exports/cache_draper" \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_train_mix_advT3.csv" \
  --val-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_valid_advT3.csv" \
  --test-manifest "./workspace/03_PerFunction_datasets/normalized_draper_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_draper_json/train_graphson" \
  --val-json-root "./Json_exports/normalized_draper_json/valid_graphson" \
  --test-json-root "./Json_exports/normalized_draper_json/test_graphson" \
  --strict-json

"""