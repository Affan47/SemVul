"""
MPTCN_TTS_Devign.py
SOTA-style, mutant-aware single-file runner for Devign graphs with robust CLI and training stages.

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
from concurrent.futures import ProcessPoolExecutor, as_completed
from concurrent.futures import ThreadPoolExecutor
import random
from torch.utils.data import WeightedRandomSampler
import numpy as np
from tqdm.auto import tqdm
import pickle, hashlib
from tqdm.asyncio import tqdm as _tqdm 
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset
from torch.cuda.amp import autocast, GradScaler

# PyG
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader as GeoDataLoader
from torch_geometric.nn import (
    GCNConv, SAGEConv, GATConv, GINConv,HGTConv, PNAConv, RGCNConv,GlobalAttention,
    global_add_pool, global_mean_pool, global_max_pool, BatchNorm
)
from torch_geometric.nn import AttentionalAggregation
from torch_geometric.utils import to_dense_batch
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
from torch.nn.utils import weight_norm


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
    cache_dir = args.cache_dir or os.path.abspath(os.path.join(root, "..", "cache_devign"))
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
import filelock
class GraphZipCache:
    """
    Single-file cache: packs each parsed PyG graph (pickle) into graph_cache.zip.

    Optimized: keep a per-process ZipFile handle to avoid re-reading the central
    directory on every item. Each DataLoader worker is a separate process, so
    the handle is not shared across processes.
    
    [FIXED] Now uses a .lock file to ensure process-safe writes from
    multiple DataLoader workers.
    """
    def __init__(self, zip_path: Path):
        self.zip_path = Path(zip_path)
        self.zip_path.parent.mkdir(parents=True, exist_ok=True)
        self._names = None     # set of members
        self._local = threading.local()  # per-process ZipFile + pid
        
        # Process-safe file lock
        self._lock = filelock.FileLock(str(self.zip_path) + ".lock", timeout=60)

    def _ensure_index(self):
        if self._names is not None:
            return
        if not self.zip_path.exists():
            self._names = set()
            return
        try:
            with zipfile.ZipFile(self.zip_path, mode="r") as zf:
                self._names = set(zf.namelist())
        except Exception:
            self._names = set()

    def _get_reader(self):
        """Return a ZipFile handle tied to the current process (pid)."""
        zf = getattr(self._local, "zf", None)
        pid = getattr(self._local, "pid", None)
        if zf is None or pid != os.getpid():
            try:
                # Close old handle if PID changed
                if getattr(self._local, "zf", None) is not None:
                    self._local.zf.close()
            except Exception:
                pass
            
            self._local.zf = zipfile.ZipFile(self.zip_path, mode="r")
            self._local.pid = os.getpid()
            zf = self._local.zf
        return zf

    def contains(self, name: str) -> bool:
        self._ensure_index()
        return name in self._names

    def load(self, name: str):
        """Return raw bytes or None."""
        self._ensure_index()
        if name not in self._names:
            return None
        try:
            zf = self._get_reader()
            with zf.open(name, mode="r") as fh:
                return fh.read()
        except Exception:
            return None

    def store(self, name: str, raw_bytes: bytes) -> bool:
        """
        [FIXED] Append a new entry if it doesn't exist using a process-safe file lock.
        """
        try:
            with self._lock:
                # Re-check index AND file contents after acquiring lock
                self._ensure_index()
                if name in self._names:
                    return True # Another process wrote it while we waited

                name_in_zip = False
                if self.zip_path.exists():
                    try:
                        with zipfile.ZipFile(self.zip_path, "r") as zf_read:
                            if name in zf_read.namelist():
                                name_in_zip = True
                    except Exception:
                        pass # File might be empty/corrupt, proceed to write
                
                if name_in_zip:
                    self._names.add(name) # Update in-memory index
                    return True

                # Lock acquired and name is not in zip; proceed with append.
                with zipfile.ZipFile(self.zip_path, mode="a",
                                     compression=zipfile.ZIP_STORED, allowZip64=True) as zf_write:
                    zf_write.writestr(name, raw_bytes)
                
                self._names.add(name)
                return True
        except Exception as e:
            # e.g., FileLock timeout or zip error
            # print(f"[Cache][Store][WARN] Failed to store {name}: {e}") # Optional debug
            return False



# ────────────────────────────────────────────

# ────────────────────────────────────────────
# Sharded ZIP cache (N shards) to avoid single-writer I/O bottleneck
# ────────────────────────────────────────────
class GraphShardedCache:
    """
    Shards the cache into N zip files under a shards dir (optionally a RAM tmpdir):
        <shards_dir>/graph_cache-000.zip, ..., graph_cache-(N-1).zip

    Deterministic shard = md5(member_name) % N.

    NEW: if shards are merged into a base zip and shards are deleted,
    contains()/load() transparently fall back to the base zip.
    
    [FIXED] Now uses .lock files to ensure process-safe writes to each shard.
    """
    def __init__(self, shards_dir: Path, num_shards: int, base_zip: Optional[Path] = None):
        self.shards_dir = Path(shards_dir)
        self.shards_dir.mkdir(parents=True, exist_ok=True)
        self.num_shards = int(max(1, num_shards))
        self.base_zip = Path(base_zip) if base_zip is not None else None
        self._idx = {}          # sid -> set(member_names) for shards
        self._paths = [self.shards_dir / f"graph_cache-{i:03d}.zip" for i in range(self.num_shards)]
        self._base_names = None # set(member_names) for base zip
        self._base_reader = None
        self._base_reader_pid = None
        
        # Process-safe file locks, one per shard
        self._locks = [filelock.FileLock(str(p) + ".lock", timeout=60) for p in self._paths]

    @staticmethod
    def _shard_id(name: str, n: int) -> int:
        h = hashlib.md5(name.encode("utf-8", errors="ignore")).digest()
        return int.from_bytes(h[:4], "little") % n

    def shard_paths(self) -> List[Path]:
        return list(self._paths)

    def _ensure_idx(self, sid: int):
        if sid in self._idx:
            return
        p = self._paths[sid]
        names = set()
        if p.exists():
            try:
                with zipfile.ZipFile(p, mode="r") as zf:
                    names.update(zf.namelist())
            except Exception:
                names = set()
        self._idx[sid] = names

    # NEW: base-zip index & reader
    def _ensure_base_idx(self):
        if self._base_names is not None:
            return
        self._base_names = set()
        if self.base_zip is not None and Path(self.base_zip).exists():
            try:
                with zipfile.ZipFile(self.base_zip, mode="r") as zf:
                    self._base_names = set(zf.namelist())
            except Exception:
                self._base_names = set()

    def _get_base_reader(self):
        if self.base_zip is None or not Path(self.base_zip).exists():
            return None
        if (self._base_reader is None) or (self._base_reader_pid != os.getpid()):
            try:
                # Close old handle if PID changed
                if getattr(self, "_base_reader", None) is not None:
                    self._base_reader.close()
            except Exception:
                pass
            self._base_reader = zipfile.ZipFile(self.base_zip, mode="r")
            self._base_reader_pid = os.getpid()
        return self._base_reader

    def contains(self, name: str) -> bool:
        sid = self._shard_id(name, self.num_shards)
        self._ensure_idx(sid)
        if name in self._idx[sid]:
            return True
        # fallback to base zip
        self._ensure_base_idx()
        return name in (self._base_names or ())

    def load(self, name: str):
        sid = self._shard_id(name, self.num_shards)
        self._ensure_idx(sid)
        if name in self._idx[sid]:
            p = self._paths[sid]
            try:
                # Use a short-lived reader handle for loading
                with zipfile.ZipFile(p, mode="r") as zf:
                    with zf.open(name, mode="r") as fh:
                        return fh.read()
            except Exception:
                return None
        # fallback to base zip
        self._ensure_base_idx()
        if name in (self._base_names or ()):
            try:
                zf = self._get_base_reader()
                if zf is None:
                    return None
                with zf.open(name, mode="r") as fh:
                    return fh.read()
            except Exception:
                return None
        return None

    def store(self, name: str, raw_bytes: bytes) -> bool:
        """
        [FIXED] Append a new entry if it doesn't exist using a process-safe
        file lock specific to this shard.
        """
        sid = self._shard_id(name, self.num_shards)
        p = self._paths[sid]
        lock = self._locks[sid]

        try:
            with lock:
                # Re-check index AND file contents *after* acquiring lock
                self._ensure_idx(sid)
                if name in self._idx[sid]:
                    return True # Another process wrote it while we waited

                name_in_zip = False
                if p.exists():
                    try:
                        with zipfile.ZipFile(p, "r") as zf_read:
                            if name in zf_read.namelist():
                                name_in_zip = True
                    except Exception:
                        pass # File might be empty/corrupt, proceed to write
                
                if name_in_zip:
                    self._idx[sid].add(name) # Update in-memory index
                    return True

                # Lock acquired and name is not in zip; proceed with append.
                with zipfile.ZipFile(p, "a", compression=zipfile.ZIP_STORED, allowZip64=True) as zf_write:
                    zf_write.writestr(name, raw_bytes)
                
                self._idx[sid].add(name)
                # invalidate base index if we’re also keeping a base zip
                self._base_names = None
                return True
        except Exception as e:
            # e.g., FileLock timeout or zip error
            # print(f"[Cache][Store][WARN] Failed to store {name} in shard {sid}: {e}") # Optional debug
            return False

    def merge_to(self, target_zip: Path, delete_after: bool = True):
        target_zip = Path(target_zip)
        target_zip.parent.mkdir(parents=True, exist_ok=True)
        names = set()
        print(f"[Cache][MERGE] merging {len(self._paths)} shards into {target_zip}")
        with zipfile.ZipFile(target_zip, mode="w", compression=zipfile.ZIP_STORED, allowZip64=True) as outzf:
            for p in self._paths:
                if not p.exists():
                    continue
                try:
                    with zipfile.ZipFile(p, mode="r") as inzf:
                        for nm in inzf.namelist():
                            if nm in names:
                                continue
                            outzf.writestr(nm, inzf.read(nm))
                            names.add(nm)
                except Exception as e:
                    print(f"[Cache][MERGE][WARN] skip shard {p}: {e}")
                    continue
        print(f"[Cache][MERGE] done; {len(names)} entries written")
        # refresh base index for fallback
        self._base_names = None

        if delete_after:
            for p in self._paths:
                try:
                    if p.exists():
                        p.unlink()
                        print(f"[Cache][CLEANUP] removed shard {p}")
                        # Also remove the lock file
                        lock_p = Path(str(p) + ".lock")
                        if lock_p.exists():
                            lock_p.unlink()
                except Exception as e:
                    print(f"[Cache][CLEANUP][WARN] failed to remove {p} or its lock: {e}")





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
# Devign-style layout (model/[spatial] and model/[spatial]_[temporal])
# ────────────────────────────────────────────
def _get_devign_layout(args):
    """
    Directories:
      Artifacts (checkpoints, results):
        <script_dir>/MPTCN_TTS_devign/<model>/<spatial>_<temporal>/{checkpoints,results}
        Fallbacks:
          - if temporal missing: <model>/<spatial>/{checkpoints,results}
          - if spatial missing:  <model>/<temporal>/{checkpoints,results}
          - if both missing:     <model>/{checkpoints,results}

      Vocabs (kept per-spatial so they can be reused across temporals):
        <script_dir>/MPTCN_TTS_devign/<model>/<spatial>/vocab
        Fallbacks:
          - if spatial missing: <model>/vocab
    """
    import re
    from pathlib import Path

    root = Path(__file__).resolve().parent
    model_name = str(getattr(args, "model", "model")).lower()

    # sanitize helpers
    def _san(v):
        if v is None:
            return None
        v = str(v).lower()
        v = re.sub(r"[^a-z0-9_\-]+", "", v)
        return v or None

    spat = _san(getattr(args, "spatial", None))
    temp = _san(getattr(args, "temporal", None))

    # ---------- vocab dir (per spatial) ----------
    if spat:
        vocabs_dir = root / "MPTCN_TTS_devign" / model_name / spat / "vocab"
    else:
        vocabs_dir = root / "MPTCN_TTS_devign" / model_name / "vocab"

    # ---------- artifact dir (per spatial+temporal) ----------
    # Prefer "<spatial>_<temporal>" if both present
    if spat and temp:
        art_dir = root / "MPTCN_TTS_devign" / model_name / f"{spat}_{temp}"
    elif spat:
        art_dir = root / "MPTCN_TTS_devign" / model_name / spat
    elif temp:
        art_dir = root / "MPTCN_TTS_devign" / model_name / temp
    else:
        art_dir = root / "MPTCN_TTS_devign" / model_name

    ckpt_dir    = art_dir / "checkpoints"
    results_dir = art_dir / "results"

    for d in (vocabs_dir, ckpt_dir, results_dir):
        d.mkdir(parents=True, exist_ok=True)

    return {
        "model_dir": art_dir,   # main artifact root (spatial+temporal when available)
        "vocab": vocabs_dir,    # shared per-spatial vocab
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
# Parser signature (used to invalidate cache when logic changes)
# -------------------------------------------------------------------
PARSER_SIG = "graphson_v2.1"

# -------------------------------------------------------------------
# Helpers for dynamic GraphSON discovery
# -------------------------------------------------------------------

# include plural 'labels' (take first), and 'category'
_NODE_LABEL_KEYS = (
    "label", "labels", "type", "kind", "nodeLabel", "category", "properties.label"
)

# include common KG terms and labelV
_EDGE_LABEL_KEYS = (
    "label", "edgeLabel", "type", "kind", "rel", "predicate", "relation", "labelV", "properties.label"
)

# broaden endpoints for many exporters
_ENDPOINT_KEYS   = (
    ("src", "dst"),
    ("u", "v"),
    ("in", "out"),
    ("inV", "outV"),
    ("outV", "inV"),
    ("head", "tail"),
    ("source", "target"),
    ("from", "to"),
    ("_outV", "_inV"),
    ("start", "end"),
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
        v = _maybe_dict_get(obj, k) if "." in k else obj.get(k)
        if v is None or v == "":
            continue
        # plural 'labels' → take first non-empty
        if k == "labels" and isinstance(v, (list, tuple)):
            for z in v:
                if z not in (None, ""):
                    return str(z)
            continue
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
    Fast path: try common Devign/Joern keys and short-circuit full-tree scanning.
    Returns:
        (best_node, best_node_key, best_node_score,
         best_edge, best_end_pair, best_edge_label_key, best_edge_score, used_fast)
    If not decisive, returns (None,..., False) so caller can do the slow fallback.
    """
    if not isinstance(g, dict):
        return None, None, 0.0, None, None, None, 0.0, False

    # Typical containers seen in Devign/Joern exports
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
    one_hot=True,
    fallback_feature_dim=64, # Renamed from emb_dim for clarity in parser context
):
    """
    Parses GraphSON format into torch_geometric Data.

    [FIXED] Ensures node_type_ids are always generated and attached.
    [FIXED] In dense mode (--no-one-hot), creates zero features if explicit
            dense features ('feat', 'x', etc.) are not found in the JSON,
            allowing downstream models to use learned embeddings via nn.Embedding.
    """
    import os, json
    import numpy as np

    # Banner print (unchanged)
    global _DENSE_PARSE_BANNER_PRINTED # Assuming this global exists
    if (not one_hot) and ("_DENSE_PARSE_BANNER_PRINTED" not in globals() or not _DENSE_PARSE_BANNER_PRINTED):
        print(f"[Parse] Using DENSE feature mode (fallback_dim={int(fallback_feature_dim)})")
        _DENSE_PARSE_BANNER_PRINTED = True

    # ---- Load JSON (fast path first) ----
    if isinstance(path_or_dict, (str, bytes, os.PathLike, Path)): # Added Path
        try:
            with open(path_or_dict, "rb") as f:
                raw = f.read()
            g = _fast_json_load_bytes(raw)
        except Exception as e1:
            try:
                with open(path_or_dict, "r", encoding="utf-8") as f2:
                    g = json.load(f2)
            except Exception as e2:
                 raise IOError(f"Failed to load JSON from {path_or_dict}. Binary load error: {e1}. Text load error: {e2}")
        src_name = str(path_or_dict)
    elif isinstance(path_or_dict, dict):
        g = path_or_dict
        src_name = "<in-memory>"
    else:
        raise TypeError(f"Input must be a path or dict, got {type(path_or_dict)}")

    node_vocab = node_vocab or {}
    edge_vocab = edge_vocab or {}
    node_vocab_size = max(1, len(node_vocab))
    edge_vocab_get = edge_vocab.get

    # ---- Helpers (extended, unchanged) ----
    _NODE_ID_KEYS = ("id", "@id", "_id", "_key", "_gid", "vertexId")

    def _normalize_graphson_value(x):
        if isinstance(x, dict) and "@value" in x and len(x) <= 2:
            val = x["@value"]
            # Handle nested types like g:Int64
            if isinstance(val, dict) and "@value" in val:
                 return _normalize_graphson_value(val)
            return val
        return x

    def _normalize_id(x):
        x = _normalize_graphson_value(x)
        if isinstance(x, (str, int)): return x
        if isinstance(x, dict):
            # Try common ID keys within the dict itself
            for key in ("id", "@id", "_id", "vertexId"):
                v = x.get(key)
                if v is not None: return _normalize_id(v)
            # Try properties.id if present
            p = x.get("properties")
            if isinstance(p, dict) and "id" in p: return _normalize_id(p["id"])
            # Fallback: stringify
            try: return json.dumps(x, sort_keys=True)
            except Exception: return str(x)
        if isinstance(x, (list, tuple)): return tuple(_normalize_id(e) for e in x)
        return str(x) # Fallback to string

    def _extract_node_id(d: dict):
        for k in _NODE_ID_KEYS:
            v = d.get(k)
            if v is None and "." in k: v = _maybe_dict_get(d, k)
            if v is not None: return _normalize_id(v)
        # Check properties as fallback
        v_prop = _maybe_dict_get(d, "properties.id")
        if v_prop is not None: return _normalize_id(v_prop)
        return None

    def _dense_from_numeric_props(nd: dict, dim: int):
        props = nd.get("properties") if isinstance(nd, dict) else None
        if not isinstance(props, dict): return None
        scalars = []
        for k, v in props.items():
            v_norm = _normalize_graphson_value(v)
            # Allow int/float, ignore lists/dicts within properties for this
            if isinstance(v_norm, (int, float)) and np.isfinite(v_norm):
                scalars.append(float(v_norm))
        if not scalars: return None
        arr = np.asarray(scalars, dtype=np.float32)
        # Simple padding/truncation
        out = np.zeros((dim,), dtype=np.float32)
        length = min(arr.size, dim)
        out[:length] = arr[:length]
        return out.tolist()

    def _extract_dense_feat(nd, dim: int):
        # Prioritize explicit feature keys
        for key in ("feat", "features", "x", "embedding", "vector"):
            v = nd.get(key)
            if v is None and "." in key: v = _maybe_dict_get(nd, key) # Check nested like properties.x
            if isinstance(v, (list, tuple)) and v:
                try:
                    arr = [float(f) for f in v] # Ensure numeric
                    # Pad or truncate
                    current_len = len(arr)
                    if current_len == dim: return arr
                    elif current_len > dim: return arr[:dim]
                    else: return arr + [0.0] * (dim - current_len)
                except (ValueError, TypeError):
                    continue # Skip if not convertible to float

        # Check inside 'properties' dict as fallback
        props = nd.get("properties") if isinstance(nd, dict) else None
        if isinstance(props, dict):
            for key in ("feat", "features", "x", "embedding", "vector"):
                v = props.get(key)
                if isinstance(v, (list, tuple)) and v:
                    try:
                        arr = [float(f) for f in v]
                        current_len = len(arr)
                        if current_len == dim: return arr
                        elif current_len > dim: return arr[:dim]
                        else: return arr + [0.0] * (dim - current_len)
                    except (ValueError, TypeError):
                         continue

        # Last resort: pack numeric properties
        dens = _dense_from_numeric_props(nd, dim)
        if dens is not None:
            return dens

        return None # Indicate no suitable dense feature found


    # ---- Node/Edge Discovery (Fast + Slow Fallback) ----
    # ... (Discovery logic using _score_node_list, _discover_nodes_only, etc. is unchanged) ...
    best_node = None
    best_node_score, best_node_key = 0.0, None
    top_nodes = g.get("nodes") or g.get("Vertices") or (g.get("@value", {}).get("vertices") if isinstance(g, dict) and "@value" in g else None)
    top_edges = g.get("edges") or g.get("Edges") or (g.get("@value", {}).get("edges") if isinstance(g, dict) and "@value" in g else None)

    if isinstance(top_nodes, list) and top_nodes:
        s, lk, _ = _score_node_list(top_nodes, node_vocab)
        if s > best_node_score:
            best_node_score, best_node, best_node_key = s, top_nodes, lk

    best_edge = None
    best_edge_score, best_end_pair, best_edge_label_key = 0.0, None, None
    if isinstance(top_edges, list) and top_edges:
        s, end_pair, lab_key, _ = _score_edge_list(top_edges, edge_vocab)
        if s > best_edge_score:
            best_edge_score, best_edge, best_end_pair, best_edge_label_key = s, top_edges, end_pair, lab_key

    # ... (debug prints unchanged) ...

    # Fill with slow discovery if needed (unchanged logic)
    if best_edge is None or best_end_pair is None:
        slow_edge, slow_end_pair, slow_edge_label_key, slow_edge_score = _discover_edges_only(g, edge_vocab)
        if slow_edge is not None and slow_end_pair is not None:
            best_edge, best_end_pair, best_edge_label_key, best_edge_score = slow_edge, slow_end_pair, slow_edge_label_key, slow_edge_score
            # ... (debug print unchanged) ...

    need_nodes = (best_node is None) or (min_nodes and len(best_node) < int(min_nodes))
    if need_nodes:
        slow_node, slow_node_key, slow_node_score = _discover_nodes_only(g, node_vocab)
        if slow_node is not None and (not min_nodes or len(slow_node) >= int(min_nodes)):
            best_node, best_node_key, best_node_score = slow_node, slow_node_key, slow_node_score
            # ... (debug print unchanged) ...

    # ---- Guard tiny/missing nodes ----
    if not best_node or (min_nodes and len(best_node) < int(min_nodes)):
        msg = f"[{debug_prefix}] No usable nodes found or count < min_nodes={min_nodes} in {src_name}"
        if strict: raise ValueError(msg)
        if debug_prefix: print(msg + " -> Creating fallback graph.")
        # Create a minimal fallback graph
        n = max(8, int(min_nodes)) # Ensure at least min_nodes if specified
        feat_dim = int(fallback_feature_dim)
        x_fallback = torch.zeros(n, feat_dim).float() # Use zeros for fallback dense
        ei_fallback = torch.empty((2, 0), dtype=torch.long) # Empty edges
        idxs_fallback = torch.zeros(n, dtype=torch.long) # Zero index for node type
        data = Data(x=x_fallback, edge_index=ei_fallback, node_type_ids=idxs_fallback)
        data.num_nodes = n # Explicitly set num_nodes
        if debug_prefix: print(f"[{debug_prefix}] Created fallback graph N={data.num_nodes} E=0")
        return data


    # ---- Nodes ----
    node_ids, node_labels = [], []
    node_dense_features = [] # Store extracted/fallback features

    # [FIX] Always parse labels and IDs, attempt dense extraction
    for i, nd in enumerate(best_node):
        # Label and ID extraction (unchanged)
        lab = _best_label_value(nd, _NODE_LABEL_KEYS)
        node_labels.append(lab if lab else "UNKNOWN")
        nid = _extract_node_id(nd)
        node_ids.append(nid if nid is not None else f"idx_{i}") # Use index as fallback ID

        # Attempt to get dense features, fallback to zeros if not found/specified
        feat_dim = int(fallback_feature_dim)
        feat = _extract_dense_feat(nd, feat_dim)
        if feat is None:
            feat = [0.0] * feat_dim # Fallback to zeros
        node_dense_features.append(feat)

    # --- id2idx mapping (unchanged logic, robust normalization) ---
    id2idx = {}
    for i, nid in enumerate(node_ids):
        key = _normalize_id(nid) # Should return str, int, or tuple
        id2idx[key] = i
        # Add common variations for robustness during edge lookup
        try: id2idx[str(key)] = i
        except Exception: pass
        try:
             iv = int(key)
             id2idx[iv] = i
        except (ValueError, TypeError): pass


    N = len(node_labels)
    if N == 0: # Should be caught by min_nodes check, but as safety
        if strict: raise ValueError(f"[{debug_prefix}] Zero nodes after processing in {src_name}")
        # Return fallback graph if zero nodes somehow got here
        n = max(8, int(min_nodes)); feat_dim = int(fallback_feature_dim)
        x_fallback = torch.zeros(n, feat_dim).float(); ei_fallback = torch.empty((2, 0), dtype=torch.long)
        idxs_fallback = torch.zeros(n, dtype=torch.long)
        data = Data(x=x_fallback, edge_index=ei_fallback, node_type_ids=idxs_fallback); data.num_nodes = n
        if debug_prefix: print(f"[{debug_prefix}] Zero nodes processed -> fallback graph N={data.num_nodes}")
        return data


    # --- [FIX] Always create node type IDs ---
    idxs = torch.tensor([_index_or_add(node_vocab, lab, "UNKNOWN") for lab in node_labels], dtype=torch.long)
    # Clamp indices to be valid for vocab size
    idxs = idxs.clamp_(min=0, max=max(0, node_vocab_size - 1))


    # --- Create node features 'x' based on one_hot flag ---
    if one_hot and node_vocab_size > 0:
        # One-hot encoding from node type IDs
        x = F.one_hot(idxs, num_classes=node_vocab_size).to(torch.float32)
    else:
        # Use the extracted/fallback dense features
        x_np = np.asarray(node_dense_features, dtype=np.float32)
        # Safety check: Ensure the array matches the number of nodes
        if x_np.shape[0] != N:
             print(f"[{debug_prefix}][WARN] Mismatch between node count ({N}) and extracted dense features ({x_np.shape[0]}). Using zero fallback.")
             x_np = np.zeros((N, int(fallback_feature_dim)), dtype=np.float32)
        x = torch.from_numpy(x_np).contiguous()


    # ---- Edges ----
    label_keys_try_edges = _EDGE_LABEL_KEYS # Assume this exists
    def _build_edges(edge_list, end_pair):
        rows, cols, elabs, miss = [], [], [], 0
        if not edge_list or not end_pair: return rows, cols, elabs, miss
        a, b = end_pair
        _get = dict.get; _maybe = _maybe_dict_get # Assume _maybe_dict_get handles nested paths

        for e_idx, e in enumerate(edge_list):
            if not isinstance(e, dict): # Skip malformed edge entries
                if debug_prefix and miss < 10: print(f"[{debug_prefix}] Skipping non-dict edge entry at index {e_idx}")
                miss += 1; continue

            u_raw = _get(e, a); u_raw = _normalize_graphson_value(u_raw) if u_raw is not None else _maybe(e, a)
            v_raw = _get(e, b); v_raw = _normalize_graphson_value(v_raw) if v_raw is not None else _maybe(e, b)

            # Extract ID if endpoint is an object
            if isinstance(u_raw, dict): u_raw = u_raw.get("id", _maybe(u_raw, "properties.id"))
            if isinstance(v_raw, dict): v_raw = v_raw.get("id", _maybe(v_raw, "properties.id"))

            if u_raw is None or v_raw is None:
                if debug_prefix and miss < 10: print(f"[{debug_prefix}] Missing endpoint in edge {e_idx}: u={u_raw}, v={v_raw}")
                miss += 1; continue

            # Normalize IDs for lookup
            u_norm = _normalize_id(u_raw)
            v_norm = _normalize_id(v_raw)

            u_i = id2idx.get(u_norm)
            v_i = id2idx.get(v_norm)

            # Fallback: Try string/int conversion if initial lookup failed
            if u_i is None: u_i = id2idx.get(str(u_norm))
            if v_i is None: v_i = id2idx.get(str(v_norm))
            if u_i is None:
                try: u_i = id2idx.get(int(u_norm))
                except (ValueError, TypeError): pass
            if v_i is None:
                try: v_i = id2idx.get(int(v_norm))
                except (ValueError, TypeError): pass

            # Final check if indices were found and are valid
            if u_i is None or v_i is None or not (0 <= u_i < N and 0 <= v_i < N):
                 if debug_prefix and miss < 10: print(f"[{debug_prefix}] Endpoint ID lookup failed or out of bounds for edge {e_idx}: u='{u_norm}'->{u_i}, v='{v_norm}'->{v_i} (N={N})")
                 miss += 1; continue

            rows.append(int(u_i))
            cols.append(int(v_i))
            lab = _best_label_value(e, label_keys_try_edges) or "UNKNOWN" # Use UNKNOWN for missing labels
            elabs.append(edge_vocab_get(lab, edge_vocab_get("UNKNOWN", 0))) # Map to vocab index

        return rows, cols, elabs, miss

    # --- Build edges using the best discovered list ---
    rows, cols, elabs, miss_fast = _build_edges(best_edge, best_end_pair)
    used_slow = False

    # --- Fallback to slow discovery if fast path failed or missed endpoints ---
    if best_edge is not None and (len(rows) == 0 or miss_fast > 0):
        slow_edge2, slow_end2, slow_lab_key2, slow_score2 = _discover_edges_only(g, edge_vocab) # Re-discover
        if slow_edge2 is not None and slow_end2 is not None:
            rows_s, cols_s, elabs_s, miss_slow = _build_edges(slow_edge2, slow_end2)
            # Prefer slow result if it found more edges OR same number with fewer misses
            better = (len(rows_s) > len(rows)) or ((len(rows_s) == len(rows)) and (miss_slow < miss_fast))
            if better:
                if debug_prefix: print(f"[{debug_prefix}] Replacing fast edges (E={len(rows)}, miss={miss_fast}) with slow edges (E={len(rows_s)}, miss={miss_slow})")
                rows, cols, elabs = rows_s, cols_s, elabs_s
                best_edge, best_end_pair, best_edge_label_key = slow_edge2, slow_end2, slow_lab_key2 # Update best refs
                used_slow = True


    # --- Handle case of zero usable edges ---
    if len(rows) == 0:
        if strict: raise ValueError(f"[{debug_prefix}] No usable edges found in {src_name}")
        if debug_prefix: print(f"[{debug_prefix}] No usable edges in {src_name} -> creating empty edge_index")
        edge_index = torch.empty((2, 0), dtype=torch.long)
        edge_attr  = torch.empty((0,), dtype=torch.long)
    else:
        # Convert to tensors
        ei_np = np.asarray([rows, cols], dtype=np.int64)
        et_np = np.asarray(elabs, dtype=np.int64) # Use int64 for edge_attr/type
        edge_index = torch.from_numpy(ei_np).contiguous()
        edge_attr  = torch.from_numpy(et_np).contiguous()


    # ---- Final Data Object Assembly ----
    data = Data(x=x.float(), edge_index=edge_index)
    data.num_nodes = N # Explicitly set node count

    # Attach edge type/attributes if they exist
    if edge_attr.numel() > 0:
        data.edge_attr = edge_attr # Keep original attributes if needed elsewhere
        data.edge_type = edge_attr.clone() # Common alias

    # [FIX] Always attach node_type_ids (as long type)
    data.node_type_ids = idxs.view(-1).long()


    # --- REMOVED PARSE STATS BLOCK ---


    if debug_prefix:
        print(f"[{debug_prefix}] Parsed {src_name} -> N={data.num_nodes}, E={data.edge_index.size(1)} | x={tuple(data.x.shape)}, edge_type={tuple(getattr(data, 'edge_type', torch.tensor([])).shape)}, node_ids={tuple(data.node_type_ids.shape)}")
        if data.num_nodes > 0 and data.edge_index.numel() > 0:
             max_idx = data.edge_index.max().item()
             if max_idx >= data.num_nodes:
                 print(f"[{debug_prefix}][WARN] Edge index max ({max_idx}) >= num_nodes ({data.num_nodes}). Out-of-bounds edges exist.")

    return data




# ────────────────────────────────────────────
# Dataset (family-aware)
# ────────────────────────────────────────────
# replace _infer_family_id with this:
_FAMILY_RE = re.compile(r"(?:^|/)(?:train|valid|test)_func_(\d+)(?:_|/)", re.IGNORECASE)

def _infer_family_id(pathish: str) -> str:
    """Best-effort family id from a path-ish string like '.../train_func_0000123/...'.
    Falls back to a stable hash-based id."""
    s = (pathish or "").strip().lower()
    m = re.search(r"(?:train_)?func_(\d+)", s)
    if m:
        g = int(m.group(1))
        return f"func_{g:07d}"
    if not s:
        return "func_0000000"
    return f"func_{int(hashlib.md5(s.encode()).hexdigest()[:8],16)%10_000_000:07d}"


def _infer_mut_type(pathish: str) -> str:
    """'orig' if it looks like export.json, else 'snap' if it contains adv/snap hints."""
    s = (pathish or "").strip().lower()
    if not s:
        return "orig"
    if s.endswith("export.json"):
        return "orig"
    if "snap" in s or "adv" in s:
        return "snap"
    return "snap"

class DevignDataset(Dataset):
    def __init__(self,
                 manifest_csv: Optional[str],
                 json_root: Optional[str],
                 feature_dim: int = 64,
                 one_hot: bool = True,
                 cache_dir: Optional[str] = None,
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
                 cache_tmpdir: Optional[str] = None):
        super().__init__()
        self.rows: List[Dict[str, str]] = []
        self.feature_dim = int(feature_dim)
        self.one_hot = bool(one_hot)

        # paths
        self.json_root = Path(json_root) if json_root else None
        self.cache_dir = Path(cache_dir) if cache_dir else None
        self.cache_overwrite = bool(cache_overwrite)
        self.no_progress = bool(no_progress)

        # sharded cache controls
        self.cache_shards = int(max(1, cache_shards))
        self.cache_tmpdir = (Path(cache_tmpdir) if cache_tmpdir else None)

        # controls for parsing
        self.strict_json = bool(strict_json)
        self.fallback_random = bool(fallback_random)
        self.min_nodes = int(min_nodes)
        self.debug_parse = False  # run() may override via args.parse_debug

        # debug/warn counters
        self._missing_warned = 0
        self._report_missing = int(report_missing)

        # global vocabs used by the dynamic parser
        self.node_vocab = node_vocab or {}
        self.edge_vocab = edge_vocab or {}

        self.index_scan_prefixes = (index_scan_prefixes
                                    if index_scan_prefixes is not None
                                    else ["train_func", "valid_func", "test_func", "func"])
        self._dir_cache: Dict[int, Optional[Path]] = {}

        # process-local cache handles (initialized lazily)
        self._zip_cache = None
        self._zip_cache_pid = None

        # -------- load manifest rows --------
        if manifest_csv:
            with open(manifest_csv, "r", encoding="utf-8") as f:
                rd = csv.DictReader(f)
                for r in rd:
                    jp = (r.get("json_path") or r.get("graph_json_path") or "").strip()
                    fam = (r.get("family_id") or "").strip() or _infer_family_id(jp or r.get("function_id", ""))
                    mut = (r.get("mutation_type") or "").strip() or _infer_mut_type(jp)
                    p_eq = r.get("p_eq", 1.0)
                    try:
                        p_eq = float(p_eq)
                    except Exception:
                        p_eq = 1.0
                    r["family_id"] = fam
                    r["mutation_type"] = mut
                    r["p_eq"] = p_eq
                    self.rows.append(r)

    # ---------- make Dataset picklable ----------
    def __getstate__(self):
        """
        Strip non-picklable, process-local handles so DataLoader workers
        can pickle the Dataset. These will be recreated lazily per worker.
        """
        state = self.__dict__.copy()
        state.pop("_zip_cache", None)
        state.pop("_zip_cache_pid", None)
        return state

    def __setstate__(self, state):
        """
        Restore Dataset in worker process; cache handles are rebuilt on demand.
        """
        self.__dict__.update(state)
        self._zip_cache = None
        self._zip_cache_pid = None

    # ---------- robust cache signature ----------
    def _cache_signature(self) -> str:
        """
        Small signature that invalidates cache when featurization/vocabs change.
        """
        import hashlib, json
        payload = {
            "one_hot": bool(getattr(self, "one_hot", True)),
            "feature_dim": int(getattr(self, "feature_dim", 64)),
            "min_nodes": int(getattr(self, "min_nodes", 0)),
            "strict_json": bool(getattr(self, "strict_json", False)),
            "node_vocab": sorted((self.node_vocab or {}).items()),
            "edge_vocab": sorted((self.edge_vocab or {}).items()),
        }
        s = json.dumps(payload, sort_keys=True, ensure_ascii=True)
        return hashlib.md5(s.encode("utf-8")).hexdigest()[:10]

    # ---------- invariants + hygiene for parsed/loaded graphs ----------
    def _validate_graph(self, d: Data, where: str = "") -> Data:
        """
        Ensure PyG Data has the shapes/dtypes GNN layers expect.
        Drop out-of-bounds edges; align edge_type with edge_index; add useful aliases.
        """
        # edge_index existence & dtype
        if not hasattr(d, "edge_index") or d.edge_index is None:
            raise ValueError(f"{where} missing edge_index")
        if d.edge_index.dtype != torch.long:
            d.edge_index = d.edge_index.long()
        if d.edge_index.dim() != 2 or d.edge_index.size(0) != 2:
            raise ValueError(f"{where} bad edge_index shape={tuple(d.edge_index.shape)}")

        # node count
        n = int(getattr(d, "num_nodes", d.x.size(0) if hasattr(d, "x") else 0))
        if n <= 0:
            raise ValueError(f"{where} num_nodes={n}")

        # optional: ensure x is float (dense or one-hot)
        if hasattr(d, "x") and not torch.is_floating_point(d.x):
            d.x = d.x.float()

        # edge_type hygiene if present
        if hasattr(d, "edge_type") and d.edge_type is not None:
            if d.edge_type.dtype != torch.long:
                d.edge_type = d.edge_type.long()
            m = d.edge_index.size(1)
            if d.edge_type.numel() != m:
                # align by truncating to min length
                M = min(m, d.edge_type.numel())
                d.edge_index = d.edge_index[:, :M]
                d.edge_type  = d.edge_type[:M]

        # drop out-of-bounds edges
        src, dst = d.edge_index[0], d.edge_index[1]
        mask = (src >= 0) & (src < n) & (dst >= 0) & (dst < n)
        if not bool(mask.all()):
            keep = mask.nonzero(as_tuple=False).view(-1)
            d.edge_index = d.edge_index[:, keep]
            if hasattr(d, "edge_type") and d.edge_type is not None and d.edge_type.numel() >= keep.numel():
                d.edge_type = d.edge_type[keep]

        # expose node types under a consistent name if present
        if not hasattr(d, "node_type_ids"):
            if hasattr(d, "node_type") and d.node_type is not None:
                d.node_type_ids = d.node_type.long()
            # (optional) infer from one-hot features if obvious
            elif getattr(self, "one_hot", True) and hasattr(d, "x") and d.x.dim() == 2 and d.x.size(1) == max(1, len(self.node_vocab or {})):
                try:
                    d.node_type_ids = d.x.argmax(dim=1).long()
                except Exception:
                    pass

        return d

    # ---------- optional coalesce duplicates ----------
    def _coalesce_edges_(self, d: Data) -> Data:
        """
        Coalesce exact duplicate edges (same src,dst,rel). Safe for sum/mean agg.
        Edge attributes are dropped (not used here).
        """
        try:
            from torch_geometric.utils import coalesce
            if not hasattr(d, "edge_index") or d.edge_index is None or d.edge_index.numel() == 0:
                return d
            # If edge_type present, lift (src,dst) by rel to keep types disjoint
            if hasattr(d, "edge_type") and d.edge_type is not None:
                # pack (src,dst,rel) to a single pair by rel-shift trick
                # Do coalesce on (src,dst), but we need same ordering for type:
                # Workaround: sort by (src,dst,rel), keep first of duplicates.
                ei = d.edge_index
                et = d.edge_type
                key = (ei[0].to(torch.long) << 42) | (ei[1].to(torch.long) << 21) | et.to(torch.long)
                order = torch.argsort(key)
                ei2 = ei[:, order]
                et2 = et[order]
                # now coalesce on (src,dst) will group same tuples contiguously if rel also same
                ei2, _ = coalesce(ei2, None, m=int(d.num_nodes), n=int(d.num_nodes), reduce='add')
                # rebuild mask by unique over key
                uniq, first_idx = torch.unique_consecutive(key[order], return_inverse=False, return_counts=False, return_index=True)
                keep_mask = torch.zeros_like(order, dtype=torch.bool)
                keep_mask[first_idx] = True
                d.edge_index = d.edge_index[:, order][:, keep_mask]
                d.edge_type  = d.edge_type[order][keep_mask]
            else:
                d.edge_index, _ = coalesce(d.edge_index, None, m=int(d.num_nodes), n=int(d.num_nodes), reduce='add')
        except Exception:
            pass
        return d


    # ---------- cache key ----------
    def _graph_cache_key(self, path: Path) -> str:
        """Stable cache key for a single JSON path."""
        try:
            h = hashlib.md5(str(path).encode("utf-8")).hexdigest()[:10]
        except Exception:
            h = hashlib.md5(repr(path).encode("utf-8")).hexdigest()[:10]

        if getattr(self, "one_hot", True):
            feat_tag = f"onehot{max(1, len(getattr(self, 'node_vocab', {}) or {}))}"
        else:
            feat_tag = f"dense{int(getattr(self, 'feature_dim', 64))}"

        user_tag = getattr(self, "cache_tag", "")
        user_tag = (str(user_tag).strip().replace("/", "_").replace(" ", "_")) if user_tag else None

        stem = getattr(path, "stem", None)
        if stem is None:
            stem = os.path.splitext(os.path.basename(str(path)))[0]

        sig = self._cache_signature()  # NEW
        parts = [stem, h, feat_tag, PARSER_SIG, sig]  # NEW: include sig
        if user_tag:
            parts.append(user_tag)
        return "g_" + "-".join(parts) + ".pkl"


    # ---------- cache handle (PID-aware) ----------
    def _get_zip_cache(self):
        """
        Return GraphShardedCache or GraphZipCache (if configured).
        The handle is process-local (PID-aware) to avoid pickling/thread-local issues.
        """
        if self.cache_dir is None:
            return None

        import os
        pid = os.getpid()

        # If we already have a handle but the PID changed, drop it
        if self._zip_cache is not None and self._zip_cache_pid != pid:
            try:
                if hasattr(self._zip_cache, "close"):
                    self._zip_cache.close()
            except Exception:
                pass
            self._zip_cache = None
            self._zip_cache_pid = None

        # Reuse if valid for this PID
        if self._zip_cache is not None:
            return self._zip_cache

        # Build a fresh handle in THIS process
        tag = getattr(self, "cache_tag", "")
        tag_sfx = f"-{tag}" if tag else ""
        split = getattr(self, "split_name", "split")
        enc = "onehot" if getattr(self, "one_hot", True) else f"dense{int(getattr(self, 'feature_dim', 64))}"

        if self.cache_shards > 1:
            shards_dir = self.cache_tmpdir if self.cache_tmpdir else (self.cache_dir / f"shards-{split}-{enc}{tag_sfx}")
            base_zip   = self.cache_dir / f"graph_cache_{split}_{enc}{tag_sfx}.zip"
            self._zip_cache = GraphShardedCache(shards_dir=shards_dir, num_shards=self.cache_shards, base_zip=base_zip)
        else:
            zip_path = self.cache_dir / f"graph_cache_{split}_{enc}{tag_sfx}.zip"
            self._zip_cache = GraphZipCache(zip_path)

        self._zip_cache_pid = pid
        return self._zip_cache

    # ---------- cache warm ----------
    def build_cache_all(self,
                        max_workers: int = 8,
                        max_outstanding: Optional[int] = None,
                        force: bool = False,
                        show_progress: bool = True,
                        parse_strict: Optional[bool] = None,
                        shards: Optional[int] = None,
                        tmpdir: Optional[str] = None):
        """
        Streamed, bounded-thread cache warm. Signature matches run()’s kwargs.
        Uses a synchronous tqdm and advances with update(1) (no __next__()).
        """
        import pickle
        from concurrent.futures import ThreadPoolExecutor, as_completed
        from tqdm import tqdm as _tqdm  # ensure we use the sync version

        # allow per-call overrides for sharded cache settings
        if shards is not None:
            try:
                self.cache_shards = int(max(1, shards))
                # force cache handle to rebuild with new shard config
                self._zip_cache = None
                self._zip_cache_pid = None
            except Exception:
                pass
        if tmpdir is not None:
            try:
                self.cache_tmpdir = Path(tmpdir)
                self._zip_cache = None
                self._zip_cache_pid = None
            except Exception:
                pass

        zc = self._get_zip_cache()
        if zc is None:
            print("[Cache] No cache dir configured; skipping.")
            return {"skipped": True}

        total = len(self.rows)
        print(f"[Cache][BUILD] rows={total} | force={bool(force)} | shards={getattr(self, 'cache_shards', 1)}")

        # Determine which indices to build
        todo: List[int] = []
        for i, r in enumerate(self.rows):
            p = self._first_existing(self._resolve_candidates(r))
            if p is None:
                continue
            key = self._graph_cache_key(p)
            if force or (not zc.contains(key)):
                todo.append(i)

        if not todo:
            print("[Cache] All entries present; nothing to do.")
            return {"built": 0, "skipped": total, "errors": 0, "todo": 0}

        max_outstanding = int(max_outstanding or (8 * max(1, max_workers)))

        def _worker(idx: int):
            r = self.rows[idx]
            p = self._first_existing(self._resolve_candidates(r))
            if p is None:
                # match dataset fallback (tiny random graph)
                n = 12 + (idx % 5)
                d = Data(
                    x=torch.randn(n, self.feature_dim).float(),
                    edge_index=torch.randint(0, n, (2, max(2 * n, 16)))
                )
                key = f"missing-{idx}"
                return idx, key, pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
            else:
                d = _parse_graphson(
                    p,
                    node_vocab=self.node_vocab,
                    edge_vocab=self.edge_vocab,
                    debug_prefix=("Parse" if getattr(self, "debug_parse", False) else ""),
                    strict=(self.strict_json if parse_strict is None else bool(parse_strict)),
                    min_nodes=self.min_nodes,
                    one_hot=self.one_hot,
                    fallback_feature_dim=self.feature_dim,
                )
                if not torch.is_floating_point(d.x):
                    d.x = d.x.float()
                key = self._graph_cache_key(p)
                buf = pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
                return idx, key, buf



        built = 0
        errors = 0

        pbar = _tqdm(total=len(todo), desc="Cache build",
                     disable=(not show_progress), mininterval=0.2)

        with ThreadPoolExecutor(max_workers=max_workers) as ex:
            futures = []
            it = iter(todo)

            # prime the pump
            for _ in range(min(max_outstanding, len(todo))):
                i = next(it, None)
                if i is None:
                    break
                futures.append(ex.submit(_worker, i))

            while futures:
                # pull one completion at a time
                done = []
                for fut in as_completed(futures, timeout=None):
                    done.append(fut)
                    break

                for fut in done:
                    futures.remove(fut)
                    try:
                        idx, key, buf = fut.result()
                        zc.store(key, buf)
                        built += 1
                    except Exception as e:
                        errors += 1
                        if errors <= 10:
                            print(f"[Cache][WARN] idx={idx if 'idx' in locals() else '?'}: {e}")

                    # advance progress bar safely
                    try:
                        pbar.update(1)
                    except Exception:
                        pass

                    # top up queue
                    i = next(it, None)
                    if i is not None:
                        futures.append(ex.submit(_worker, i))

        pbar.close()

        remaining = max(0, len(todo) - built - errors)
        print(f"[Cache] built={built} errors={errors} remaining={remaining}")
        return {"built": built, "errors": errors, "todo": len(todo)}

    def __len__(self) -> int:
        return len(self.rows)

    # ---------- path resolution helpers ----------
    def _find_dir_by_index(self, idx: int) -> Optional[Path]:
        """Map integer index -> directory `<prefix>_{idx:07d}` under json_root (best effort)."""
        if idx in self._dir_cache:
            return self._dir_cache[idx]
        if self.json_root is None:
            self._dir_cache[idx] = None
            return None
        pad = f"{int(idx):07d}"
        # exact first
        for pref in self.index_scan_prefixes:
            cand = self.json_root / f"{pref}_{pad}"
            try:
                if cand.is_dir():
                    self._dir_cache[idx] = cand
                    return cand
            except Exception:
                pass
        # shallow glob fallback
        try:
            for cand in self.json_root.glob(f"*_{pad}"):
                if cand.is_dir():
                    self._dir_cache[idx] = cand
                    return cand
        except Exception:
            pass
        self._dir_cache[idx] = None
        return None

    def _resolve_candidates(self, r: Dict[str, str]) -> List[Path]:
        """Return plausible JSON paths in priority order."""
        cands: List[Path] = []
        jp = (r.get("json_path") or r.get("graph_json_path") or "").strip()
        if jp:
            p = Path(jp)
            if not p.is_absolute() and self.json_root is not None:
                p = self.json_root / p
            cands.append(p)
        # fallback by index for originals
        if self.json_root is not None:
            idx = r.get("index") or r.get("id")
            if idx is not None and str(idx).strip():
                i = int(idx)
                # legacy numeric folder: <root>/<index>/export.json
                cands.append(self.json_root / str(i) / "export.json")
                # common layout: <root>/<prefix>_{index:07d}/export.json
                d = self._find_dir_by_index(i)
                if d is not None:
                    cands.append(d / "export.json")
        # de-dup while preserving order
        seen = set()
        out = []
        for p in cands:
            s = str(p)
            if s in seen:
                continue
            seen.add(s)
            out.append(p)
        return out

    def _first_existing(self, cands: List[Path]) -> Optional[Path]:
        for p in cands:
            try:
                if p.is_file():
                    return p
            except Exception:
                pass
        return None

    # ---------- main fetch ----------
    def __getitem__(self, idx: int) -> Data:
        r = self.rows[idx]

        # 1) Canonicalize manifest row (works for "mix" & "plus")
        try:
            label = int(r.get("label", 0))
        except Exception:
            label = 0

        try:
            p_eq = float(r.get("p_eq", 1.0))
        except Exception:
            p_eq = 1.0

        family_id = (r.get("family_id") or "").strip()
        index_val = r.get("index", None)

        if not family_id:
            fid = (r.get("function_id") or "").strip().lower()
            if fid:
                m = re.search(r"(?:train_)?func_(\d+)", fid)
                if m:
                    g = int(m.group(1))
                    family_id = f"func_{g:07d}"
                    index_val = g

        if not family_id:
            probe = (r.get("json_path") or r.get("graph_json_path") or r.get("code_path") or str(idx)).lower()
            m = re.search(r"(?:train_)?func_(\d+)", probe)
            if m:
                g = int(m.group(1))
                family_id = f"func_{g:07d}"
                index_val = index_val if index_val is not None else g
            else:
                family_id = _infer_family_id(probe)
                index_val = index_val if index_val is not None else idx

        try:
            index_val = int(index_val)
        except Exception:
            index_val = int(idx)

        mut = (r.get("mutation_type") or "").strip().lower()
        t_idx = r.get("t_idx", None)

        jp_raw = (r.get("json_path") or r.get("graph_json_path") or "").strip().lower()

        def _infer_t_and_mut(ps: str):
            if not ps:
                return 0, "orig"
            if ps.endswith("export.json"):
                return 0, "orig"
            m = re.search(r"snap_adv(\d+)", ps)
            if m:
                return int(m.group(1)), "snap"
            m = re.search(r"adv\D*?(\d+)", ps)
            if m:
                return int(m.group(1)), "snap"
            return 1, "snap"

        if not mut or t_idx is None:
            _t, _m = _infer_t_and_mut(jp_raw)
            if not mut:
                mut = _m
            if t_idx is None:
                t_idx = _t
        try:
            t_idx = int(t_idx)
        except Exception:
            t_idx = 0 if mut == "orig" else 1

        is_mut = 0 if (mut == "orig") else 1

        proj_raw = (r.get("project") or "").strip().lower()
        if   proj_raw == "debian": project_label = 0
        elif proj_raw == "chrome": project_label = 1
        else:                      project_label = -1

        # 2) Resolve JSON path (robust)
        cands: List[Path] = []
        jp_exact = (r.get("json_path") or r.get("graph_json_path") or "").strip()
        if jp_exact:
            p = Path(jp_exact)
            if not p.is_absolute() and self.json_root is not None:
                p = (self.json_root / p)
            cands.append(p)
            # if directory, try export_all/export.json
            try:
                if p.is_dir():
                    cands.append(p / "export_all" / "export.json")
            except Exception:
                pass

        # add resolver suggestions
        cands.extend(self._resolve_candidates(r))
        # de-dup
        seen = set(); cands = [p for p in cands if not (str(p) in seen or seen.add(str(p)))]
        p = self._first_existing(cands)

        # 3) Load / parse graph
        if p is None:
            msg = f"[Data][MISS] row={idx} family={family_id} | tried={', '.join(map(str, cands)) or '<none>'}"
            if self.strict_json and not self.fallback_random:
                raise FileNotFoundError(msg)
            if self._missing_warned < self._report_missing:
                print(msg)
                self._missing_warned += 1
            n = 12 + (idx % 5)
            d = Data(
                x=torch.randn(n, self.feature_dim),
                edge_index=torch.randint(0, n, (2, max(2 * n, 16)))
            )
        else:
            zc = self._get_zip_cache()
            loaded_from_cache = False
            entry_name = None

            if zc is not None:
                entry_name = self._graph_cache_key(p)
                if (not self.cache_overwrite) and entry_name and zc.contains(entry_name):
                    raw = zc.load(entry_name)
                    if raw is not None:
                        try:
                            d: Data = pickle.loads(raw)
                            loaded_from_cache = True
                        except Exception:
                            loaded_from_cache = False

            if not loaded_from_cache:
                d = _parse_graphson(
                    p,
                    node_vocab=self.node_vocab,
                    edge_vocab=self.edge_vocab,
                    debug_prefix=("Parse" if getattr(self, "debug_parse", False) else ""),
                    strict=self.strict_json,
                    min_nodes=self.min_nodes,
                    one_hot=self.one_hot,
                    fallback_feature_dim=self.feature_dim,
                )
                if zc is not None and entry_name:
                    try:
                        buf = pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
                        zc.store(entry_name, buf)
                    except Exception:
                        pass

        # 4) Hygiene / warnings
        # 4) Hygiene / warnings
        d = self._validate_graph(d, where=f"[Data][{idx}]")
        d = self._coalesce_edges_(d)

        if (not self.strict_json) and int(d.num_nodes) <= max(8, self.min_nodes):
            ne = int(d.edge_index.size(1)) if hasattr(d, "edge_index") else 0
            if self._missing_warned < self._report_missing:
                print(f"[Data][WARN] Tiny graph from {p or '<none>'} -> nodes={int(d.num_nodes)} edges={ne}")
                self._missing_warned += 1


        # 5) Attach metadata
        d.y = torch.tensor([label], dtype=torch.long)
        d.family_id = family_id
        d.fid = torch.tensor(
            [int(hashlib.md5(family_id.encode()).hexdigest()[:8], 16)],
            dtype=torch.long
        )
        d.mutation_type = mut
        d.t_idx = torch.tensor([int(t_idx)], dtype=torch.long)
        d.is_mutant = torch.tensor([is_mut], dtype=torch.long)   # 0=orig, 1=mutant
        d.p_eq = torch.tensor([p_eq], dtype=torch.float)
        d.sample_index = torch.tensor([index_val], dtype=torch.long)

        d.project = proj_raw
        d.project_label = torch.tensor([project_label], dtype=torch.long)

        return d

    # ---------- summarize (unchanged except imports fixed) ----------
    def summarize_sizes(self,
                        sample: int = 200,
                        use_cache_only: bool = True,
                        bins_nodes = (0, 10, 20, 40, 80, 160, 320, 640, 1_000_000),
                        bins_edges = (0, 20, 40, 80, 160, 320, 640, 1_280, 10_000)):
        from collections import Counter
        import numpy as np

        ns, es = [], []
        node_counts = Counter()
        edge_counts = Counter()
        checked = 0

        node_id2name = {v: k for k, v in (self.node_vocab or {}).items()}
        edge_id2name = {v: k for k, v in (self.edge_vocab or {}).items()}

        zc = self._get_zip_cache()

        for ridx, r in enumerate(self.rows):
            if checked >= int(sample):
                break

            p = self._first_existing(self._resolve_candidates(r))
            if p is None:
                continue

            d = None
            entry = None

            if zc is not None:
                entry = self._graph_cache_key(p)
                if entry and zc.contains(entry):
                    raw = zc.load(entry)
                    if raw is not None:
                        try:
                            d = pickle.loads(raw)
                        except Exception as e:
                            print(f"[Summ][WARN] zip cache load failed for {entry}: {e}")
                            d = None

            if d is None and not use_cache_only:
                try:
                    d = _parse_graphson(
                        p,
                        node_vocab=self.node_vocab,
                        edge_vocab=self.edge_vocab,
                        debug_prefix="SummParse",
                        strict=False,
                        min_nodes=0,
                        one_hot=True,
                        fallback_feature_dim=self.feature_dim,
                    )
                    if zc is not None and entry:
                        try:
                            buf = pickle.dumps(d, protocol=pickle.HIGHEST_PROTOCOL)
                            zc.store(entry, buf)
                        except Exception:
                            pass
                except Exception as e:
                    print(f"[Summ][SKIP] parse failed for {p}: {e}")
                    continue

            if d is None:
                continue

            n = int(getattr(d, "num_nodes", 0))
            e = int(d.edge_index.size(1)) if hasattr(d, "edge_index") else 0
            ns.append(n); es.append(e)

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

        if not ns:
            print("[Summ] No graphs inspected (likely no cache and use_cache_only=True).")
            return

        ns_arr = np.array(ns, dtype=np.int64)
        es_arr = np.array(es, dtype=np.int64)

        def _pct(x): return np.percentile(x, [1, 5, 50, 95, 99]).tolist()

        print("\n========== Dataset size summary ==========")
        print(f"Samples inspected: {checked}")
        print(f"Nodes: mean={ns_arr.mean():.2f}  min={ns_arr.min()}  max={ns_arr.max()}  q01,q05,med,q95,q99={_pct(ns_arr)}")
        print(f"Edges: mean={es_arr.mean():.2f}  min={es_arr.min()}  max={es_arr.max()}  q01,q05,med,q95,q99={_pct(es_arr)}")

        hn, _ = np.histogram(ns_arr, bins=np.asarray(bins_nodes))
        he, _ = np.histogram(es_arr, bins=np.asarray(bins_edges))
        print("\nNode histogram (bins -> count):")
        for i in range(len(hn)):
            lo = bins_nodes[i]; hi = bins_nodes[i+1]
            print(f"  [{lo:>5}, {hi:>5}) : {int(hn[i])}")

        print("\nEdge histogram (bins -> count):")
        for i in range(len(he)):
            lo = bins_edges[i]; hi = bins_edges[i+1]
            print(f"  [{lo:>5}, {hi:>5}) : {int(he[i])}")

        if node_counts:
            print("\nTop node types (by id -> count, name if known):")
            for tid, cnt in node_counts.most_common(15):
                nm = node_id2name.get(tid, "<unk>")
                print(f"  node_type {tid:>2} ({nm:>18}) : {cnt}")
        else:
            print("\nNo node_type tensor found on parsed graphs (skipping node type coverage).")

        if edge_counts:
            print("\nTop edge types (by id -> count, name if known):")
            for tid, cnt in edge_counts.most_common(15):
                nm = edge_id2name.get(tid, "<unk>")
                print(f"  edge_type {tid:>2} ({nm:>18}) : {cnt}")
        else:
            print("\nNo edge_type tensor found on parsed graphs (skipping edge type coverage).")

        print("==========================================\n")


from torch_geometric.data import Batch, Data
from typing import List

def graph_collate(batch: List[Data]) -> Batch:
    """
    Collate a list of Data objects into a PyG Batch and explicitly record
    the number of graphs. Also flattens common per-graph fields to 1-D when
    they arrive as shape (1,) so downstream code can count graphs reliably.
    """
    b = Batch.from_data_list(batch)

    # Explicitly stamp how many graphs are in this batch.
    # (PyG sometimes sets this; we force it to be robust.)
    b.num_graphs = len(batch)

    # (Optional) Normalize a few common per-graph fields to 1-D
    # so that y.view(-1).numel() == num_graphs, etc.
    def _flat1(x):
        try:
            return x.view(-1) if x is not None else x
        except Exception:
            return x

    for name in ("y", "fid", "t_idx", "is_mutant", "project_label", "p_eq", "sample_index"):
        if hasattr(b, name):
            setattr(b, name, _flat1(getattr(b, name)))

    return b


# ────────────────────────────────────────────
# Vocab builder (from TRAIN split)
# ────────────────────────────────────────────
def _build_vocabs_from_train_ds(train_ds: DevignDataset, disable_progress: bool = True):
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



def ensure_vocabs(args, layout, train_ds: DevignDataset):
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
        x, edge_index = data.x, data.edge_index
        # NOTE: PNAConv does not require edge_attr by default; keep None-safe
        for conv, bn in zip(self.convs, self.bns):
            x = conv(x, edge_index)
            x = F.relu(bn(x), inplace=True)
            x = F.dropout(x, p=self.dropout, training=self.training)

        batch = getattr(data, "batch", None)
        if batch is None:
            g = x.mean(dim=0, keepdim=True)
        else:
            g = _readout(x, batch, self.readout)
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
# TCN Building Blocks (for the "real" TCN)
# ────────────────────────────────────────────

class TemporalBlock(nn.Module):
    """
    A building block for a Temporal Convolutional Network (TCN).
    Consists of two 1D convolutional layers with causal padding and
    a residual connection.
    """
    def __init__(self, n_inputs, n_outputs, kernel_size, stride, dilation, padding, dropout=0.2):
        super(TemporalBlock, self).__init__()
        
        # [FIX] Set conv padding to 0 and store the causal padding amount
        self.conv1 = weight_norm(nn.Conv1d(n_inputs, n_outputs, kernel_size,
                                           stride=stride, padding=0, dilation=dilation))
        self.padding1 = padding # Store causal padding amount
        self.relu1 = nn.ReLU()
        self.dropout1 = nn.Dropout(dropout)

        # [FIX] Set conv padding to 0 and store the causal padding amount
        self.conv2 = weight_norm(nn.Conv1d(n_outputs, n_outputs, kernel_size,
                                           stride=stride, padding=0, dilation=dilation))
        self.padding2 = padding # Store causal padding amount
        self.relu2 = nn.ReLU()
        self.dropout2 = nn.Dropout(dropout)

        # 1x1 conv for residual connection if dimensions mismatch
        self.downsample = nn.Conv1d(n_inputs, n_outputs, 1) if n_inputs != n_outputs else None
        self.relu = nn.ReLU()
        
        # Initialize weights
        self.init_weights()

    def init_weights(self):
        self.conv1.weight.data.normal_(0, 0.01)
        self.conv2.weight.data.normal_(0, 0.01)
        if self.downsample is not None:
            self.downsample.weight.data.normal_(0, 0.01)

    def forward(self, x):
        # x shape: [Batch, Channels, Length]
        
        # [FIX] Apply manual causal (left) padding
        out = F.pad(x, (self.padding1, 0))
        out = self.conv1(out)
        out = self.relu1(out)
        out = self.dropout1(out)

        # [FIX] Apply manual causal (left) padding
        out = F.pad(out, (self.padding2, 0))
        out = self.conv2(out)
        out = self.relu2(out)
        out = self.dropout2(out)

        res = x if self.downsample is None else self.downsample(x)
        
        # [FIX] Ensure output length matches residual length.
        # This handles any potential off-by-one from conv arithmetic.
        return self.relu(out[..., :res.size(2)] + res)


class TemporalConvNet(nn.Module):
    """
    A stack of TemporalBlocks to form a TCN.
    """
    def __init__(self, num_inputs, num_channels, kernel_size=2, dropout=0.2):
        super(TemporalConvNet, self).__init__()
        layers = []
        num_levels = len(num_channels)
        for i in range(num_levels):
            dilation_size = 2 ** i
            in_channels = num_inputs if i == 0 else num_channels[i-1]
            out_channels = num_channels[i]
            
            # Note: The padding is (kernel_size-1) * dilation_size for causal convs
            # Here we use standard padding to keep length roughly the same
            padding = (kernel_size-1) * dilation_size
            
            layers.append(TemporalBlock(in_channels, out_channels, kernel_size, stride=1, dilation=dilation_size,
                                        padding=padding, dropout=dropout))

        self.network = nn.Sequential(*layers)

    def forward(self, x):
        # x shape: [Batch, Channels, Length]
        return self.network(x)


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
        Lt=2,               # Now controls # of TCN/GRU layers
        heads=2,
        bases=4,            # for RGCN: forward relation count
        dropout=0.3,
        readout="mean",
        temporal="tcn",     # [FIXED] "tcn" (real TCN) or "gru"
        Ks=3,               # GNN kernel size (e.g., Cheb)
        Kt=3,               # TCN kernel size
        add_reverse_rel=False,   # controls forward+reverse relations
        rgcn_num_bases=None,
    ):
    
        super().__init__()
        print("[Build][MPTCN_TTS] Initializing REAL TCN/GRU-on-nodes architecture.") # <-- ADDED/MODIFIED PRINT
        self.spatial = str(spatial).lower()
        self.temporal_kind = str(temporal).lower()
        self.readout = str(readout).lower()

        # Readout gate (attention)
        self.readout_gate = None
        self.readout_aggr = None
        if self.readout == "attn":
            self.readout_gate = nn.Sequential(
                nn.Linear(int(hidden_dim), max(32, int(hidden_dim)//2)),
                nn.ReLU(inplace=True),
                nn.Linear(max(32, int(hidden_dim)//2), 1),
            )
            self.readout_aggr = AttentionalAggregation(self.readout_gate)
            print("[Build][Readout] mode=attn")

        self.dropout = float(dropout)
        self.Ls = int(Ls)
        self.Lt = int(Lt) # Num temporal layers
        self.heads = int(heads)
        self.bases = int(max(1, bases))   # forward relation count
        self.Ks = int(Ks) # GNN kernel
        self.Kt = int(Kt) # TCN kernel

        # Embedding fusion state (populated by attach_input_embedding)
        self.input_emb: Optional[nn.Embedding] = None
        self.embed_mode: str = "none"   # "none" | "concat" | "replace"
        self.emb_dim: int = 0

        # Debug/trace flags (bound in run(args))
        self._dev_printed = False
        self._ids_warned = False
        self.add_reverse_rel = bool(add_reverse_rel)
        self.debug_rgcn_io = False
        self._debug_hdr_once = False

        # Stability/memory toggles (can be set after construction)
        self.use_row_norm = False
        self.use_ckpt = False

        # Store requested RGCN basis count
        self.rgcn_num_bases = int(rgcn_num_bases) if rgcn_num_bases is not None else max(4, self.bases // 2)
        self.rgcn_num_bases = max(1, self.rgcn_num_bases)

        # Project (raw_x_width) -> hidden_dim so spatial stack is fixed-width
        self.input_proj = nn.LazyLinear(hidden_dim)

        # ---- Spatial stack (hidden_dim -> hidden_dim) ----
        self.s_layers = nn.ModuleList()
        self.s_bns = nn.ModuleList()
        dim_h = int(hidden_dim)

        for li in range(self.Ls):
            in_ch = dim_h
            out_ch = dim_h

            if self.spatial == "gcn":
                conv = GCNConv(in_ch, out_ch)

            elif self.spatial == "gat":
                # out_ch must be divisible by heads when concat=True
                conv = GATConv(in_ch, out_ch // self.heads, heads=self.heads, concat=True)

            elif self.spatial == "sage":
                conv = SAGEConv(in_ch, out_ch)

            elif self.spatial == "cheb":
                conv = ChebConv(in_ch, out_ch, K=self.Ks)

            elif self.spatial == "rgcn":
                # forward relations (optionally doubled by reverse)
                num_rel = int(self.bases) * (2 if self.add_reverse_rel else 1)
                # clamp requested bases to valid range [1, num_rel]
                num_bases = max(1, min(int(self.rgcn_num_bases), num_rel))
                conv = RGCNConv(
                    in_ch, out_ch,
                    num_relations=num_rel,
                    num_bases=num_bases,
                    aggr='add'
                )
                if self.add_reverse_rel:
                    print(f"[Build][RGCN] bases={self.bases} | num_bases={num_bases} | add_reverse_rel=ON | layer.num_relations={num_rel}")
                else:
                    print(f"[Build][RGCN] bases={self.bases} | num_bases={num_bases} | add_reverse_rel=OFF | layer.num_relations={num_rel}")

            elif self.spatial == "hgt":
                # Record that we run a single-node-type hetero graph
                # with `bases` forward relations, optionally doubled by reverse ones.
                self.hgt_has_rev = bool(self.add_reverse_rel)
                self.hgt_rel_names = [str(r) for r in range(self.bases)]

                # Build metadata once; each HGTConv gets the same schema.
                if self.hgt_has_rev:
                    rels = [('N', rn, 'N') for rn in self.hgt_rel_names] + \
                        [('N', f'{rn}_rev', 'N') for rn in self.hgt_rel_names]
                else:
                    rels = [('N', rn, 'N') for rn in self.hgt_rel_names]
                metadata = (['N'], rels)

                conv = HGTConv(
                    in_channels=in_ch,
                    out_channels=out_ch,
                    metadata=metadata,
                    heads=self.heads,          # keep heads configurable
                    # group='sum',             # (optional) default is 'sum'; leave default unless you need 'mean'
                )

                # One-time, helpful build log
                if self.hgt_has_rev:
                    print(f"[Build][HGT] bases={self.bases} | add_reverse_rel=ON | "
                        f"edge_types={len(rels)} (fwd={self.bases}, rev={self.bases}) | heads={self.heads}")
                else:
                    print(f"[Build][HGT] bases={self.bases} | add_reverse_rel=OFF | "
                        f"edge_types={len(rels)} (fwd only) | heads={self.heads}")

            else:
                # default fallback
                conv = GCNConv(in_ch, out_ch)

            self.s_layers.append(conv)
            self.s_bns.append(BatchNorm(out_ch))


        # --- JK attention gate (content-aware, per-node, per-layer) ---
        self.jk_gate = nn.Sequential(
            nn.Linear(dim_h, max(32, dim_h // 2)),
            nn.ReLU(inplace=True),
            nn.Linear(max(32, dim_h // 2), 1),
        )


        # ---- [FIX] Temporal stack (operates on node sequences) ----
        # This module will receive a padded tensor [B, L_max, D]
        # GRU expects: [B, L, D] (batch_first=True)
        # TCN expects: [B, D, L] (channels_first)
        self.temporal_module = None
        if self.temporal_kind == "gru":
            print(f"[Build][Temporal] Using GRU(layers={self.Lt}) on node sequences.")
            self.temporal_module = nn.GRU(
                input_size=dim_h, 
                hidden_size=dim_h, 
                num_layers=self.Lt, 
                batch_first=True, # [B, L, D]
                dropout=self.dropout if self.Lt > 1 else 0.0
            )
        elif self.temporal_kind == "tcn":
            print(f"[Build][Temporal] Using TCN(layers={self.Lt}, K={self.Kt}) on node sequences.")
            # TCN needs channels_first: [B, D, L]
            # We create Lt layers, each with hidden_dim channels
            tcn_channels = [dim_h] * self.Lt
            self.temporal_module = TemporalConvNet(
                num_inputs=dim_h, # Input channels = hidden_dim
                num_channels=tcn_channels,
                kernel_size=self.Kt,
                dropout=self.dropout
            )
        else:
            print(f"[Build][Temporal] WARNING: Unknown temporal kind '{self.temporal_kind}'. No temporal module will be used.")

        # ---- Classifier head ----
        self.head = nn.Sequential(
            nn.Linear(dim_h, dim_h),
            nn.ReLU(inplace=True),
            nn.Dropout(self.dropout),
            nn.Linear(dim_h, out_dim),
        )

        # NEW: optional auxiliary head for project (debian/chrome)
        self.proj_head = nn.Sequential(
            nn.Linear(dim_h, max(64, dim_h // 2)),
            nn.ReLU(inplace=True),
            nn.Linear(max(64, dim_h // 2), 2),  # 2 classes: debian/chrome
        )

    def forward(self, data: Data):
        # ---- Edge index and (optional) relation types ----
        ei  = data.edge_index
        rel = getattr(data, "edge_type", None)

        # Choose device from edge_index
        dev = ei.device

        # Batch vector fallback for single-graph cases
        if getattr(data, "batch", None) is None:
            ba = torch.zeros(data.x.size(0), dtype=torch.long, device=dev)
        else:
            ba = data.batch.to(dev, non_blocking=True)

        # ---- Input encoding & fusion ----
        x_dense = data.x.float().to(dev, non_blocking=True)

        # cheap structural signal → log in/out degree (2 dims)
        N = x_dense.size(0)
        deg_in  = torch.bincount(ei[1], minlength=N).float()
        deg_out = torch.bincount(ei[0], minlength=N).float()
        feat_deg = torch.stack([torch.log1p(deg_in), torch.log1p(deg_out)], dim=-1).to(x_dense.device)

        # combine dense + degree
        x_dense_plus = torch.cat([x_dense, feat_deg], dim=-1)

        need_ids = (self.embed_mode in ("concat", "replace")) and (self.input_emb is not None)
        have_ids = (getattr(data, "node_type_ids", None) is not None)

        if need_ids and not have_ids and not self._ids_warned:
            print("[Warn] embed_mode!=none but node_type_ids missing on Data. "
                "Rebuild cache in dense mode (--no-one-hot) with a fresh --cache-tag.")
            self._ids_warned = True

        if have_ids and (self.input_emb is not None):
            idx = data.node_type_ids
            if not torch.is_tensor(idx):
                idx = torch.as_tensor(idx, dtype=torch.long)
            idx = idx.to(self.input_emb.weight.device, non_blocking=True)
            e = self.input_emb(idx)  # [N, emb_dim]

            # one-time device debug
            if not self._dev_printed:
                print(f"[Debug] input_emb.device={self.input_emb.weight.device} | idx.device={idx.device}")
                self._dev_printed = True

            if self.embed_mode == "replace":
                if e.device != x_dense_plus.device:
                    e = e.to(x_dense_plus.device, non_blocking=True)
                x_raw = torch.cat([e, feat_deg], dim=-1)
            elif self.embed_mode == "concat":
                if e.device != x_dense_plus.device:
                    e = e.to(x_dense_plus.device, non_blocking=True)
                x_raw = torch.cat([x_dense_plus, e], dim=-1)
            else:
                x_raw = x_dense_plus
        else:
            x_raw = x_dense_plus

        # Project raw features to hidden_dim before spatial message passing
        x = self.input_proj(x_raw)  # LazyLinear infers width on first call
        dev = x.device  # trust feature device after projection

        # ---- Prepare relation types for spatial stack ----
        rel_work = (
            torch.zeros(ei.size(1), dtype=torch.long, device=dev)
            if rel is None
            else (rel.to(dev, non_blocking=True) if rel.device != dev else rel)
        )

        # derive forward relation count (bases)
        max_rel = int(rel_work.max().item() + 1) if rel_work.numel() > 0 else 1
        bases   = int(getattr(self, "bases", 0)) or max_rel
        max_rel = max(1, max_rel, bases)
        rel_work = rel_work.clamp_(0, max_rel - 1)

        if getattr(self, "debug_rgcn_io", False) and not getattr(self, "_debug_hdr_once", False):
            ur = torch.unique(rel_work).tolist()
            print(f"[RGCN][DBG] ei={tuple(ei.size())} rel={tuple(rel_work.size())} "
                f"unique_rels={len(ur)} sample={ur[:10]} bases={bases} "
                f"add_reverse={getattr(self,'add_reverse_rel',False)}")
            self._debug_hdr_once = True

        # ---------- Build HGT edge_index_dict ONCE per forward (speed) ----------
        use_hgt = any(isinstance(c, HGTConv) for c in self.s_layers)
        edge_index_dict_all = None
        if use_hgt:
            # Pull metadata from the first HGT layer
            meta_edge_types = None
            for c in self.s_layers:
                if isinstance(c, HGTConv):
                    meta_edge_types = getattr(c, "metadata", (['N'], []))[1]
                    break
            meta_edge_types = set(meta_edge_types) if meta_edge_types is not None else None

            edge_index_dict_all = {}
            empty = ei.new_empty(2, 0)
            total_edges_used = 0

            for rid in range(max_rel):
                mask = (rel_work == rid)
                eidx = ei[:, mask] if mask.any() else empty
                if eidx.numel() > 0:
                    total_edges_used += eidx.size(1)
                k_fwd = ('N', f'{rid}', 'N')
                if (meta_edge_types is None) or (k_fwd in meta_edge_types):
                    edge_index_dict_all[k_fwd] = eidx
                if getattr(self, "add_reverse_rel", False):
                    k_rev = ('N', f'{rid}_rev', 'N')
                    if (meta_edge_types is None) or (k_rev in meta_edge_types):
                        edge_index_dict_all[k_rev] = (eidx[[1, 0], :] if eidx.numel() > 0 else empty)

            # If NO edges exist for any relation in this batch, we will bypass HGT layers below.
            if getattr(self, "debug_rgcn_io", False) and not getattr(self, "_debug_hgt_once", False):
                nkeys = 0 if edge_index_dict_all is None else sum(int(v.numel() > 0) for v in edge_index_dict_all.values())
                decl = max_rel * (2 if getattr(self, "add_reverse_rel", False) else 1)
                print(f"[HGT][DBG] total_edges_used={total_edges_used} | non_empty_keys={nkeys} / declared={decl}")
                self._debug_hgt_once = True
        # -----------------------------------------------------------------------

        # ---- Spatial stack with residuals + optional row-norm + JK capture ----
        x_layers = []

        from torch.utils.checkpoint import checkpoint as _ckpt
        def _rgcn_call(conv, xx, eidx, rty):
            return conv(xx, eidx, rty)

        for conv, bn in zip(self.s_layers, self.s_bns):
            # --- message passing (per layer) ---
            if isinstance(conv, RGCNConv):
                use_rev = bool(getattr(self, "add_reverse_rel", False))
                nr = int(getattr(conv, "num_relations", 0) or 0)

                if use_rev and nr >= 2 * max_rel:
                    ei_use  = torch.cat([ei, ei[[1, 0], :]], dim=1)
                    rel_use = torch.cat([rel_work, rel_work + max_rel], dim=0).clamp_(0, nr - 1)

                    if getattr(self, "debug_rgcn_io", False) and not getattr(self, "_debug_io_once", False):
                        print(f"[RGCN][FWD+REV] nr={nr} | bases={bases} | "
                            f"E_fwd={ei.size(1)} E_rev={ei.size(1)} E_total={ei_use.size(1)}")
                        self._debug_io_once = True  # print once
                    if getattr(self, "use_ckpt", False):
                        # Wrap conv in a closure so checkpoint sees only Tensor args
                        fn = lambda _x, _ei, _rel: conv(_x, _ei, _rel)
                        try:
                            x_mp = _ckpt(fn, x, ei_use, rel_use, use_reentrant=False, preserve_rng_state=False)
                        except TypeError:
                            x_mp = _ckpt(fn, x, ei_use, rel_use)
                    else:
                        x_mp = conv(x, ei_use, rel_use)

                else:
                    if use_rev and nr < 2 * max_rel and getattr(self, "debug_rgcn_io", False):
                        print(f"[RGCN][FWD-ONLY] add_reverse=True but nr={nr} < 2*bases={2*bases}")
                    if getattr(self, "use_ckpt", False):
                        fn = lambda _x, _ei, _rel: conv(_x, _ei, _rel)
                        try:
                            x_mp = _ckpt(fn, x, ei, rel_work, use_reentrant=False, preserve_rng_state=False)
                        except TypeError:
                            x_mp = _ckpt(fn, x, ei, rel_work)
                    else:
                        x_mp = conv(x, ei, rel_work)

            elif isinstance(conv, HGTConv):
                # Speed priority: do NOT checkpoint HGT (recompute is very costly).
                # If no edges present for any relation in this batch → bypass.
                if (edge_index_dict_all is None) or all(v.numel() == 0 for v in edge_index_dict_all.values()):
                    # no message passing possible
                    x_mp = x
                else:
                    x_dict = {'N': x}
                    out_dict = conv(x_dict, edge_index_dict_all)
                    x_mp = out_dict['N']

            else:
                # standard convs (GCN/GAT/SAGE/Cheb, etc.)
                x_mp = conv(x, ei)

            # --- residual pre-activation + optional row-norm ---
            x_res = x
            x = bn(x_mp)
            if getattr(self, "use_row_norm", False):
                x = F.normalize(x, p=2, dim=-1)
            x = F.relu(x, inplace=True)
            x = x + x_res

            # JK: collect after residual, before dropout
            x_layers.append(x)

            # dropout
            x = F.dropout(x, p=self.dropout, training=self.training)

        # --- JK aggregation (fast) ---
        if len(x_layers) > 0:
            x = torch.stack(x_layers, dim=0).max(dim=0).values  # JK-max

        
        # ---- [FIX] Temporal mixing (on node embeddings) ----
        # x is [N, D] (all nodes in batch)
        # ba is [N] (batch index for each node)
        
        if self.temporal_module is not None:
            # 1. Convert [N, D] -> [B, L_max, D]
            # x_padded is [B, L_max, D], mask is [B, L_max]
            # We must use fill_value=0.0 as padding for TCN/GRU
            x_padded, mask = to_dense_batch(x, ba, fill_value=0.0)
            
            if self.temporal_kind == "gru":
                # Input: [B, L_max, D]
                # We need to pack the sequence to handle padding
                lengths = mask.sum(dim=1).cpu().to(torch.int64) # Get actual lengths
                
                # Ensure lengths are valid (pack_padded_sequence needs > 0)
                if (lengths > 0).all():
                    x_packed = nn.utils.rnn.pack_padded_sequence(
                        x_padded, lengths, batch_first=True, enforce_sorted=False
                    )
                    # out_packed is [B, L, D]
                    out_packed, _ = self.temporal_module(x_packed)
                    
                    # Unpack -> [B, L_max, D]
                    x_padded, _ = nn.utils.rnn.pad_packed_sequence(
                        out_packed, batch_first=True, total_length=x_padded.size(1)
                    )
                else:
                    # A graph was empty, skip GRU
                    pass # x_padded remains as is (mostly zeros)
            
            elif self.temporal_kind == "tcn":
                # Input: [B, L_max, D] -> TCN needs [B, D, L_max]
                x_padded_tcn = x_padded.permute(0, 2, 1)
                
                # out_tcn is [B, D, L_max]
                out_tcn = self.temporal_module(x_padded_tcn)
                
                # Convert back -> [B, L_max, D]
                x_padded = out_tcn.permute(0, 2, 1)

            # 2. Convert [B, L_max, D] -> [N, D]
            # Use the mask to select only the valid nodes
            x = x_padded[mask] # Shape [N, D]

        
        # ---- Graph readout (NOW runs on temporally-processed nodes) ----
        if self.readout == "attn" and (self.readout_aggr is not None):
            g = self.readout_aggr(x, index=ba)
        else:
            g = _readout(x, ba, self.readout)
        
        # ---- Head ----
        logits = self.head(g)
        proj_logits = self.proj_head(g)  # always compute; loss uses only labeled rows
        return {"logits": logits, "proj_logits": proj_logits, "emb": g}




# HGT & HAN wrappers
class HGTBaseline(nn.Module):
    def __init__(self, in_dim, hidden_dim=256, out_dim=2, layers=2, heads=1, dropout=0.3, readout="mean",
                 num_relations: int = 1, add_reverse_rel: bool = False):
        super().__init__()
        self.readout = readout
        self.dropout = dropout
        self.use_fallback = not HAS_HGT
        self.num_relations = max(1, int(num_relations))
        self.add_reverse_rel = bool(add_reverse_rel)

        if self.use_fallback:
            print("[HGTBaseline][WARN] HGTConv not found. Falling back to GATBaseline.")
            self.fallback = GATBaseline(in_dim, hidden_dim, out_dim, heads=heads, layers=max(2,layers), readout=readout, dropout=dropout)
        else:
            self.fallback = None
            self.inp = nn.Linear(in_dim, hidden_dim) # This is now wrapped, so in_dim=hidden_dim
            
            # --- [FIX] Build correct HGT metadata ---
            self.hgt_rel_names = [str(r) for r in range(self.num_relations)]
            if self.add_reverse_rel:
                rels = [('N', rn, 'N') for rn in self.hgt_rel_names] + \
                       [('N', f'{rn}_rev', 'N') for rn in self.hgt_rel_names]
            else:
                rels = [('N', rn, 'N') for rn in self.hgt_rel_names]
            
            self.metadata = (['N'], rels)
            num_edge_types = len(rels)
            
            self.convs = nn.ModuleList()
            self.norms = nn.ModuleList()
            for _ in range(layers):
                self.convs.append(HGTConv(
                    in_channels=hidden_dim, 
                    out_channels=hidden_dim,
                    metadata=self.metadata, 
                    heads=heads
                ))
                self.norms.append(nn.LayerNorm(hidden_dim))
            
            self.head = nn.Sequential(
                nn.Linear(hidden_dim, hidden_dim), 
                nn.ReLU(), 
                nn.Dropout(dropout), 
                nn.Linear(hidden_dim, out_dim)
            )
            print(f"[Build][HGTBaseline] OK | num_relations={self.num_relations} rev={self.add_reverse_rel} | "
                  f"Total edge types={num_edge_types} | heads={heads}")

    def forward(self, data: Data):
        if self.use_fallback:
            return self.fallback(data)
            
        x, ei = data.x, data.edge_index
        rel = getattr(data, "edge_type", None)
        ba = getattr(data, "batch", torch.zeros(x.size(0), dtype=torch.long, device=x.device))
        
        # x is already [N, hidden_dim] from the NodeFeatureWrapper
        # self.inp(x) is no longer needed if in_dim=hidden_dim, but we keep it
        # for consistency with the wrapper's design (it's now hidden->hidden)
        x = self.inp(x) 

        # --- [FIX] Build heterogeneous edge_index_dict ---
        if rel is None:
            rel = torch.zeros(ei.size(1), dtype=torch.long, device=ei.device)
        rel = rel.clamp_(0, self.num_relations - 1)
        
        edge_index_dict = {}
        empty = ei.new_empty(2, 0)
        
        for rid in range(self.num_relations):
            mask = (rel == rid)
            eidx = ei[:, mask] if mask.any() else empty
            
            k_fwd = ('N', f'{rid}', 'N')
            edge_index_dict[k_fwd] = eidx
            
            if self.add_reverse_rel:
                k_rev = ('N', f'{rid}_rev', 'N')
                edge_index_dict[k_rev] = (eidx[[1, 0], :] if eidx.numel() > 0 else empty)
        
        # Run HGT layers
        x_dict = {'N': x}
        for conv, ln in zip(self.convs, self.norms):
            # Bypass layer if no edges are present at all
            if all(v.numel() == 0 for v in edge_index_dict.values()):
                x_dict['N'] = x_dict['N'] # No-op
            else:
                x_dict = conv(x_dict, edge_index_dict)
            
            h = x_dict['N']
            h = F.relu(ln(h))
            h = F.dropout(h, p=self.dropout, training=self.training)
            x_dict['N'] = h
            
        g = _readout(x_dict['N'], ba, self.readout)
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
    if logits.dim() == 1:
        delta = logits.float() / float(T)
    elif logits.size(-1) == 1:
        delta = logits.squeeze(-1).float() / float(T)
    else:
        delta = (logits[..., 1] - logits[..., 0]).float() / float(T)
    delta = torch.nan_to_num(delta, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
    return torch.sigmoid(delta)

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

      # IMPORTANT: do NOT let stats['thr'] (sweep thr) overwrite our adjusted thr;
      # expose both explicitly and return the adjusted thr.
    stats_out = {**stats,
                 "thr_raw": float(thr_raw),       # from PR sweep
                 "thr_used": float(thr),          # after pos-rate clamps
                 "pos_rate_raw": float(pos_rate), # pos-rate at raw_thr (pre-clamp)
                 "base": float(base)}
    return float(thr), stats_out


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
    # [FIX] Add epsilon to F.normalize AND to the norm calculation itself
    # to prevent nan from 0-vector inputs
    z_norm = torch.norm(z.float(), p=2, dim=-1, keepdim=True).clamp_min(1e-12)
    z = z.float() / z_norm
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

class ProjectAux(nn.Module):
    """
    Wraps a base model that returns {'logits', 'emb'} and adds 'proj_logits' from the same embedding.
    """
    def __init__(self, base: nn.Module, hidden_dim: int, num_proj_classes: int = 2, dropout: float = 0.1):
        super().__init__()
        self.base = base
        self.proj_head = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(inplace=True),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, num_proj_classes)
        )

    def forward(self, data: Data):
        out = self.base(data)
        emb = out.get("emb", None)
        if emb is not None:
            out["proj_logits"] = self.proj_head(emb)
        return out



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


def _sweep_threshold(y, p, beta=1.0, min_prec=None, min_rec=None, grid=None):
    if grid is None:
        grid = np.linspace(0.05, 0.95, 19)
    y = np.asarray(y).astype(np.int64)
    p = np.asarray(p).astype(np.float32)
    best_thr, best_f = 0.5, -1.0
    beta2 = beta * beta
    for t in grid:
        pred = (p >= t).astype(np.int64)
        tp = int(((pred == 1) & (y == 1)).sum())
        fp = int(((pred == 1) & (y == 0)).sum())
        fn = int(((pred == 0) & (y == 1)).sum())
        prec = tp / max(1, tp + fp)
        rec  = tp / max(1, tp + fn)
        if (min_prec is not None) and (prec < min_prec): continue
        if (min_rec  is not None) and (rec  < min_rec):  continue
        f = (1 + beta2) * (prec * rec) / max(1e-9, (beta2 * prec + rec))
        if f > best_f:
            best_f, best_thr = f, t
    return float(best_thr)

def calibrate_thr_per_project(y, p, proj, beta=1.0, min_prec=None, min_rec=None):
    y = np.asarray(y).astype(np.int64)
    p = np.asarray(p).astype(np.float32)
    proj = np.asarray(proj).astype(np.int64) if proj is not None else None
    out = {}
    if proj is None:
        return out
    for pid in np.unique(proj):
        if int(pid) < 0:    # skip unknown
            continue
        m = (proj == pid)
        if m.sum() == 0: 
            continue
        out[int(pid)] = _sweep_threshold(
            y[m], p[m], beta=beta, min_prec=min_prec, min_rec=min_rec
        )
    return out



# ────────────────────────────────────────────
# Evaluate & collectors (with optional TTA)
# ────────────────────────────────────────────
def _augment_batch_for_eval(
    b: Batch,
    dropedge_p: float = 0.0,
    feat_noise_std: float = 0.0,
    add_reverse_edges: bool = False,  # NEW
):
    b = b.clone()

    # A3.0) Add reverse edges first (reuse same relation id → safe for all spatial backends)
    if add_reverse_edges and getattr(b, "edge_index", None) is not None and b.edge_index.numel() > 0:
        ei     = b.edge_index
        ei_rev = torch.stack([ei[1], ei[0]], dim=0)

        if getattr(b, "edge_type", None) is not None:
            et     = b.edge_type
            et_rev = et  # reuse relation ids for reverse direction
            b.edge_type = torch.cat([et, et_rev], dim=0)

        if getattr(b, "edge_attr", None) is not None:
            ea     = b.edge_attr
            b.edge_attr = torch.cat([ea, ea], dim=0)

        b.edge_index = torch.cat([ei, ei_rev], dim=1)

    # A3.1) DropEdge
    if dropedge_p > 0.0 and getattr(b, "edge_index", None) is not None and b.edge_index.numel() > 0:
        E    = b.edge_index.size(1)
        keep = torch.rand(E, device=b.edge_index.device) > float(dropedge_p)
        if keep.sum() >= 1:
            b.edge_index = b.edge_index[:, keep]
            if getattr(b, "edge_attr", None) is not None:
                b.edge_attr = b.edge_attr[keep]
            if getattr(b, "edge_type", None) is not None:
                b.edge_type = b.edge_type[keep]

    # A3.2) Feature noise
    if feat_noise_std > 0.0 and getattr(b, "x", None) is not None:
        if not torch.is_floating_point(b.x):
            b.x = b.x.float()
        noise = torch.randn_like(b.x) * float(feat_noise_std)
        b.x = b.x + noise

    # safety: keep lengths consistent
    if getattr(b, "edge_type", None) is not None and getattr(b, "edge_index", None) is not None:
        E = b.edge_index.size(1)
        if b.edge_type.numel() != E:
            M = min(E, int(b.edge_type.numel()))
            b.edge_index = b.edge_index[:, :M]
            if getattr(b, "edge_attr", None) is not None and b.edge_attr.size(0) != M:
                b.edge_attr = b.edge_attr[:M]
            b.edge_type = b.edge_type[:M]

    return b

def _relation_dropout_inplace(b: Batch, p: float = 0.0) -> Batch:
    """Randomly drop a fraction of edges uniformly (by masking edge_index and edge_type).
    Safe no-op if p<=0 or if edge_type is missing.
    """
    p = float(p)
    if p <= 0.0:
        return b
    if not hasattr(b, "edge_index"): 
        return b
    ei = b.edge_index
    et = getattr(b, "edge_type", None)
    m = ei.size(1)
    if m == 0:
        return b
    mask = (torch.rand(m, device=ei.device) > p)
    if mask.sum().item() == m:
        return b  # keep all
    b.edge_index = ei[:, mask]
    if et is not None and torch.is_tensor(et) and et.numel() == m:
        b.edge_type = et[mask]
    ea = getattr(b, "edge_attr", None)
    if ea is not None and torch.is_tensor(ea) and ea.size(0) == m:
        b.edge_attr = ea[mask]
    return b


@torch.inference_mode()
def collect_probs_with_T(model, loader, device, T: float = 1.0,
                         tta: int = 0, tta_dropedge_p: float = 0.0, tta_feat_noise_std: float = 0.0):
    model.eval()
    y_all, p_all, proj_all = [], [], []
    no_prog = getattr(loader, "_no_progress", False)
    for b in _tqdm(loader, desc="Collect", disable=no_prog, total=len(loader)):
        b = b.to(device, non_blocking=True)
        with torch.no_grad():
            # TTA loop (unchanged)
            logits_acc = None
            views = max(1, int(tta))
            for _ in range(views):
                bb = _augment_batch_for_eval(b,
                        dropedge_p=float(tta_dropedge_p),
                        feat_noise_std=float(tta_feat_noise_std))
                out = model(bb)
                logits = out["logits"] if isinstance(out, dict) else out
                logits = logits / max(1e-6, float(T))
                logits = torch.nan_to_num(logits, nan=0.0, posinf=30.0, neginf=-30.0).clamp_(-30, 30)
                probs = F.softmax(logits, dim=-1)[:, 1] if logits.size(-1) > 1 else torch.sigmoid(logits.view(-1))
                logits_acc = probs if logits_acc is None else (logits_acc + probs)
            probs = (logits_acc / float(views)).detach().cpu()

            y_all.append(b.y.view(-1).detach().cpu().numpy())
            p_all.append(probs.numpy())

            # NEW: collect project IDs (label or id; -1 fallback)
            if hasattr(b, "project_label") and b.project_label is not None:
                proj = b.project_label.view(-1).detach().cpu().numpy()
            elif hasattr(b, "project_id") and b.project_id is not None:
                proj = b.project_id.view(-1).detach().cpu().numpy()
            else:
                proj = np.full_like(b.y.view(-1).detach().cpu().numpy(), fill_value=-1)
            proj_all.append(proj)

    y_all = np.concatenate(y_all, axis=0) if len(y_all) else np.array([])
    p_all = np.concatenate(p_all, axis=0) if len(p_all) else np.array([])
    proj_all = np.concatenate(proj_all, axis=0) if len(proj_all) else None
    return y_all, p_all, proj_all


@torch.inference_mode()
def evaluate(
    model: nn.Module,
    loader: GeoDataLoader,
    device: torch.device,
    threshold: float = 0.5,
    temperature: Optional[float] = None,
    tta: int = 0,
    tta_dropedge_p: float = 0.0,
    tta_feat_noise_std: float = 0.0,
    threshold_map: dict | None = None,   # NEW: per-project {project_id -> thr}
) -> Dict[str, Any]:
    """
    Evaluates the main binary task and (optionally) the project-aux head.

    Expects batches to possibly have:
      - y (main labels)                    : [B]
      - project_label (0=debian,1=chrome) : [B] or -1 if unknown/missing

    If the model returns:
      - out["logits"]        : main task logits (required)
      - out["proj_logits"]   : project head logits (optional; 2-class)
      - or out["proj_prob"]  : project head probs for class-1 (float in [0,1])
    we will evaluate the project head as well (when ground-truth provided).
    """
    model.eval()

    # ---------- collectors ----------
    y_true: List[int] = []
    prob_list: List[torch.Tensor] = []

    # project collectors (labels per-sample; -1 → unknown)
    proj_labels_all: List[int] = []

    # optional project head probabilities (class-1 = chrome) if model provides it
    proj_prob_list: List[torch.Tensor] = []

    # ---------- config ----------
    T = float(temperature) if (temperature is not None and np.isfinite(temperature) and temperature > 0.0) else 1.0
    T = max(0.1, min(10.0, T))
    disable = getattr(loader, "_no_progress", True)

    # ---------- loop ----------
    for batch in _tqdm(loader, desc="Evaluate", disable=disable, total=len(loader)):
        b = batch.to(device, non_blocking=True)

        # ---- TTA averaging for main (and aux if available) ----
        if tta and tta > 0:
            acc_main = 0.0
            acc_proj = 0.0
            have_proj = False

            for _ in range(int(tta)):
                bb = _augment_batch_for_eval(b, tta_dropedge_p, tta_feat_noise_std)
                out = model(bb)

                # main
                logits = out["logits"] if isinstance(out, dict) else out
                logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                p1 = _probs_from_logits_binary(logits, T=T)  # prob for class-1
                acc_main += p1.detach().cpu()

                # aux project head (optional)
                if isinstance(out, dict) and ("proj_logits" in out or "proj_prob" in out):
                    have_proj = True
                    if "proj_prob" in out:
                        pp = out["proj_prob"]
                        if torch.is_tensor(pp) and pp.dim() >= 1:
                            pp = pp.view(-1)
                        pp = torch.nan_to_num(pp, nan=0.5).clamp_(0.0, 1.0)
                        acc_proj += pp.detach().cpu()
                    else:
                        plog = out["proj_logits"]
                        # 2-class softmax → prob of class-1 (chrome)
                        plog = torch.nan_to_num(plog, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                        psoft = F.softmax(plog, dim=-1)
                        pp = psoft[..., 1]
                        acc_proj += pp.detach().cpu()

            p1 = (acc_main / float(tta))
            prob_list.append(p1)

            if have_proj:
                proj_prob_list.append(acc_proj / float(tta))

        else:
            out = model(b)

            # main
            logits = out["logits"] if isinstance(out, dict) else out
            logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
            p1 = _probs_from_logits_binary(logits, T=T).detach().cpu()
            prob_list.append(p1)

            # aux project head (optional)
            if isinstance(out, dict) and ("proj_logits" in out or "proj_prob" in out):
                if "proj_prob" in out:
                    pp = out["proj_prob"]
                    if torch.is_tensor(pp) and pp.dim() >= 1:
                        pp = pp.view(-1)
                    pp = torch.nan_to_num(pp, nan=0.5).clamp_(0.0, 1.0)
                    proj_prob_list.append(pp.detach().cpu())
                else:
                    plog = out["proj_logits"]
                    plog = torch.nan_to_num(plog, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                    psoft = F.softmax(plog, dim=-1)
                    proj_prob_list.append(psoft[..., 1].detach().cpu())

        # collect labels
        y_true.extend(b.y.view(-1).detach().cpu().tolist())

        # collect project labels if present; else fill as unknown (-1)
        pl = getattr(b, "project_label", None)
        if pl is None:  # backward-compatibility if dataset used 'project_id'
            pl = getattr(b, "project_id", None)
        if pl is not None:
            proj_labels_all.extend(pl.view(-1).detach().cpu().tolist())
        else:
            proj_labels_all.extend([-1] * p1.numel())

    # ---------- main task metrics (overall) ----------
    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = (np.asarray(torch.cat(prob_list).numpy(), dtype=np.float32) if prob_list else np.empty((0,), dtype=np.float32))
    y_prob = clamp01_np(y_prob)

    # ---- NEW: per-sample binarization using threshold_map when provided ----
    proj_labels_all = np.asarray(proj_labels_all, dtype=np.int64)
    if threshold_map and proj_labels_all.size == y_prob.size:
        thr_vec = np.full_like(y_prob, fill_value=float(threshold), dtype=np.float32)
        # apply project-specific thresholds where known
        for pid, thr in threshold_map.items():
            mask = (proj_labels_all == int(pid))
            if mask.any():
                thr_vec[mask] = float(thr)
        y_pred = (y_prob >= thr_vec).astype(np.int64)
    else:
        # global threshold fallback (original behavior)
        y_pred = (y_prob >= float(threshold)).astype(np.int64)

    acc = accuracy_score(y_true, y_pred) if len(y_true) else 0.0
    prec, rec, f1, _ = precision_recall_fscore_support(y_true, y_pred, average="binary", zero_division=0)
    try:
        auc = roc_auc_score(y_true, y_prob) if len(np.unique(y_true)) > 1 else float("nan")
    except Exception:
        auc = float("nan")
    cm_overall = confusion_matrix(y_true, y_pred, labels=[0, 1]) if len(y_true) else np.zeros((2, 2), dtype=int)

    result: Dict[str, Any] = {
        "acc": float(acc),
        "prec": float(prec),
        "rec": float(rec),
        "f1": float(f1),
        "auc": float(auc) if np.isfinite(auc) else float("nan"),
        "cm": cm_overall,
        "thr": float(threshold),
        "T": float(T),
    }
    if threshold_map:
        result["thr_map"] = {int(k): float(v) for k, v in threshold_map.items()}

    # ---------- per-project breakdown (main task) ----------
    # 0=debian, 1=chrome, -1=unknown
    per_proj: Dict[str, Dict[str, Any]] = {}

    def _slice_and_metrics(mask: np.ndarray) -> Dict[str, Any]:
        if not mask.any():
            return {"count": 0}
        yt = y_true[mask]
        yp = y_pred[mask]
        ypb = y_prob[mask]
        m_prec, m_rec, m_f1, _ = precision_recall_fscore_support(yt, yp, average="binary", zero_division=0)
        try:
            m_auc = roc_auc_score(yt, ypb) if len(np.unique(yt)) > 1 else float("nan")
        except Exception:
            m_auc = float("nan")
        return {
            "count": int(yt.size),
            "acc": float(accuracy_score(yt, yp)),
            "prec": float(m_prec),
            "rec":  float(m_rec),
            "f1":   float(m_f1),
            "auc":  float(m_auc),
            "cm":   confusion_matrix(yt, yp, labels=[0, 1]),
        }

    mask_deb = (proj_labels_all == 0)
    mask_chr = (proj_labels_all == 1)
    mask_unk = (proj_labels_all < 0)

    per_proj["debian"]  = _slice_and_metrics(mask_deb)
    per_proj["chrome"]  = _slice_and_metrics(mask_chr)
    per_proj["unknown"] = _slice_and_metrics(mask_unk)

    result["per_project"] = per_proj

    # ---------- project-aux head metrics (optional) ----------
    if len(proj_prob_list) > 0:
        proj_prob = np.asarray(torch.cat(proj_prob_list).numpy(), dtype=np.float32)
        # evaluate only on rows with known ground-truth project label (0/1)
        known = proj_labels_all >= 0
        proj_metrics: Dict[str, Any] = {"count": int(known.sum())}

        if known.any():
            pt = proj_labels_all[known].astype(np.int64)
            pp = clamp01_np(proj_prob[known])
            # default threshold 0.5 for project 1 (chrome)
            ppred = (pp >= 0.5).astype(np.int64)

            p_prec, p_rec, p_f1, _ = precision_recall_fscore_support(pt, ppred, average="binary", zero_division=0)
            try:
                p_auc = roc_auc_score(pt, pp) if len(np.unique(pt)) > 1 else float("nan")
            except Exception:
                p_auc = float("nan")

            proj_metrics.update({
                "acc": float(accuracy_score(pt, ppred)),
                "prec": float(p_prec),
                "rec":  float(p_rec),
                "f1":   float(p_f1),
                "auc":  float(p_auc),
                "cm":   confusion_matrix(pt, ppred, labels=[0, 1]),
            })
        result["project_aux"] = proj_metrics

    return result


from torch.utils.data.sampler import Sampler

from torch.utils.data.sampler import Sampler

class FamilyAwareSampler(Sampler):
    """
    [FIX] A Sampler that yields batches grouped by "family_id".
    
    This is critical for mutant-aware losses (consistency, supcon, delta)
    which require multiple members of the same family in a single batch.
    
    It builds a batch by:
    1. Randomly selecting `num_families_per_batch` families.
    2. For each family, sampling `num_members_per_family` items (with replacement).
    
    This replaces the WeightedRandomSampler, as class balancing will be
    handled by the loss function's `pos_weight`.
    
    [FIXED-V2] Removed invalid 'replacement' kwarg from torch.randint and
               added safety check for zero families/members.
    """
    def __init__(self,
                 manifest_rows: List[Dict[str, Any]],
                 batch_size: int,
                 num_members_per_family: int,
                 seed: int = 42):
        
        self.rows = manifest_rows
        self.batch_size = int(batch_size)
        self.k = int(max(1, num_members_per_family))
        self.num_families_per_batch = int(max(1, self.batch_size // self.k))
        self.total_families = 0
        self.num_samples = len(self.rows)
        self.g = torch.Generator()
        self.g.manual_seed(seed)
        
        print(f"[Sampler] FamilyAwareSampler enabled: k={self.k} families_per_batch={self.num_families_per_batch}")
        
        # Group row indices by family_id
        self.by_family: Dict[str, List[int]] = {}
        for i, r in enumerate(self.rows):
            fam_id = r.get("family_id", f"__unknown_{i}__")
            self.by_family.setdefault(fam_id, []).append(i)
        
        self.family_ids = list(self.by_family.keys())
        self.total_families = len(self.family_ids)
        
        if self.total_families == 0 and self.num_samples > 0:
             print("[Sampler][ERROR] No families found, but num_samples > 0. Check 'family_id' in manifest.")
        elif self.total_families < self.num_families_per_batch:
            print(f"[Sampler][WARN] total_families ({self.total_families}) < num_families_per_batch ({self.num_families_per_batch}). Sampling families with replacement.")
        
        print(f"[Sampler] Found {self.total_families} unique families for {self.num_samples} samples.")

    def __iter__(self):
        # Determine number of batches needed to cover num_samples
        num_batches = (self.num_samples + self.batch_size - 1) // self.batch_size
        
        if self.total_families == 0:
            if self.num_samples > 0:
                 print("[Sampler][iter][ERROR] No families to sample from. Yielding no batches.")
            yield from [] # Yield nothing
            return

        for _ in range(num_batches):
            batch_indices = []
            
            # 1. Sample families for this batch
            # This samples *with replacement* by default.
            fam_indices = torch.randint(
                low=0, 
                high=self.total_families, 
                size=(self.num_families_per_batch,), 
                generator=self.g
            ).tolist()
            
            # 2. For each family, sample K members
            for fam_idx in fam_indices:
                fam_id = self.family_ids[fam_idx]
                member_indices = self.by_family[fam_id]
                
                # [FIX] Safety check for empty family list
                if not member_indices:
                    continue

                # [FIX] Removed invalid 'replacement=True' argument.
                # This call also samples with replacement by default.
                sample_indices = torch.randint(
                    low=0, 
                    high=len(member_indices), # high is exclusive
                    size=(self.k,), 
                    generator=self.g
                ).tolist()
                
                batch_indices.extend([member_indices[i] for i in sample_indices])
            
            # 3. Yield indices for this batch
            if not batch_indices:
                continue # Skip empty batches
                
            final_batch = [batch_indices[i] for i in torch.randperm(len(batch_indices), generator=self.g)]
            yield from final_batch[:self.batch_size]

    def __len__(self) -> int:
        return self.num_samples
class NodeFeatureWrapper(nn.Module):
    """
    [FIX] A wrapper to apply the complex MPTCN-TTS input feature logic
    (dense + degree + learned embedding) to any standard GNN baseline.
    
    This wrapper ensures that --no-one-hot with --embed-mode works for all models.
    """
    def __init__(self, 
                 base_model: nn.Module, 
                 raw_feature_dim: int, 
                 num_tokens: int,
                 args: argparse.Namespace):
        super().__init__()
        self.base_model = base_model
        self.hidden_dim = int(args.hidden_dim)
        self.embed_mode = str(getattr(args, "embed_mode", "none")).lower()
        self.emb_dim = int(getattr(args, "emb_dim", 64))
        
        # 1. Embedding layer for node type IDs
        self.input_emb: Optional[nn.Embedding] = None
        if self.embed_mode in ("concat", "replace"):
            self.input_emb = nn.Embedding(int(num_tokens), self.emb_dim)
            print(f"[Wrapper][{base_model.__class__.__name__}] Attached nn.Embedding (mode={self.embed_mode})")

        # 2. Projector from raw features -> hidden_dim
        # We use LazyLinear to automatically handle the input dimension,
        # which changes based on the embedding mode.
        self.input_proj = nn.LazyLinear(self.hidden_dim)
        
        self._dev_printed = False
        self._ids_warned = False

    def forward(self, data: Data):
        dev = data.x.device
        
        # ---- 1. Get raw dense features (from parser) ----
        x_dense = data.x.float() # [N, raw_feature_dim] (potentially all zeros)
        
        # ---- 2. Get degree features ----
        N = x_dense.size(0)
        ei = data.edge_index
        deg_in  = torch.bincount(ei[1], minlength=N).float()
        deg_out = torch.bincount(ei[0], minlength=N).float()
        feat_deg = torch.stack([torch.log1p(deg_in), torch.log1p(deg_out)], dim=-1).to(dev)
        
        # Combine dense + degree
        x_dense_plus = torch.cat([x_dense, feat_deg], dim=-1)

        # ---- 3. Get learned embeddings ----
        need_ids = (self.embed_mode in ("concat", "replace")) and (self.input_emb is not None)
        have_ids = (getattr(data, "node_type_ids", None) is not None)

        if need_ids and not have_ids and not self._ids_warned:
            print(f"[Wrapper][{self.base_model.__class__.__name__}][WARN] embed_mode!=none but node_type_ids missing on Data.")
            self._ids_warned = True

        if have_ids and (self.input_emb is not None):
            idx = data.node_type_ids.to(self.input_emb.weight.device)
            e = self.input_emb(idx)  # [N, emb_dim]

            if not self._dev_printed:
                print(f"[Wrapper][{self.base_model.__class__.__name__}][Debug] input_emb.device={self.input_emb.weight.device} | idx.device={idx.device}")
                self._dev_printed = True

            if self.embed_mode == "replace":
                x_raw = torch.cat([e, feat_deg], dim=-1)
            elif self.embed_mode == "concat":
                x_raw = torch.cat([x_dense_plus, e], dim=-1)
            else: # embed_mode == "none"
                x_raw = x_dense_plus
        else:
            x_raw = x_dense_plus

        # ---- 4. Project to hidden_dim and replace data.x ----
        data.x = self.input_proj(x_raw) # [N, hidden_dim]
        
        # ---- 5. Call the base model ----
        return self.base_model(data)

# ────────────────────────────────────────────
# Model factory
# ────────────────────────────────────────────
def make_model(args, 
                 raw_feature_dim: int, 
                 num_node_tokens: int,
                 pna_deg_hist: Optional[torch.Tensor]=None) -> nn.Module:
    """
    [FIXED] Model factory.
    - Wraps all baselines in NodeFeatureWrapper to handle dense/embedding logic.
    - Passes hidden_dim as in_dim to baselines (since wrapper projects to hidden_dim).
    - Passes correct num_relations to MPNN.
    - Builds MPTCN_TTS directly as it handles its own features.
    """
    name = args.model.lower()
    hidden_dim = int(args.hidden_dim)
    out_dim = int(args.num_classes)
    layers = int(args.layers)
    dropout = float(args.dropout)
    readout = str(args.readout)
    
    # Special case: MPTCN-TTS handles its own feature fusion
    if name == "mptcn_tts":
        return MPTCN_TTS(
            in_dim=raw_feature_dim, # It uses LazyLinear, so this is just a placeholder
            hidden_dim=hidden_dim,
            out_dim=out_dim,
            spatial=args.spatial,
            Ls=args.Ls,
            Lt=args.Lt,
            heads=args.heads,
            bases=args.bases,
            dropout=dropout,
            readout=readout,
            temporal=args.temporal,
            Ks=args.Ks,
            Kt=args.Kt,
            add_reverse_rel=getattr(args, "rgcn_add_reverse_rel", False),
            rgcn_num_bases=getattr(args, "rgcn_num_bases", None),
        )

    # All other models are baselines and need the feature wrapper
    base_model = None
    
    # --- Define the base model (note: in_dim is NOW hidden_dim) ---
    if name == "gcn":
        base_model = GCNBaseline(hidden_dim, hidden_dim, out_dim, layers, readout, dropout)
    elif name == "gat":
        base_model = GATBaseline(hidden_dim, hidden_dim, out_dim, args.heads, layers, readout, dropout)
    elif name == "sage":
        base_model = SAGEBaseline(hidden_dim, hidden_dim, out_dim, layers, readout, dropout)
    elif name == "gin":
        base_model = GINBaseline(hidden_dim, hidden_dim, out_dim, layers, readout, dropout)
    elif name == "pna":
        base_model = PNABaseline(hidden_dim, hidden_dim, out_dim, layers, readout, dropout, deg_hist=pna_deg_hist)
    elif name in ("deepgcn","deepergcn","dgcnn"):
        base_model = DeeperGCNBaseline(hidden_dim, hidden_dim, out_dim, layers, readout, dropout)
    elif name == "mpnn":
        base_model = MPNNBaseline(
            hidden_dim, hidden_dim=hidden_dim, out_dim=out_dim,
            edge_dim=args.edge_emb_dim, layers=layers, readout=readout,
            dropout=dropout, 
            num_relations=int(getattr(args, "num_relations", 0)) # [FIX] Pass correct num_relations
        )
    elif name == "rgcn":
        base_model = RGcnBaseline(
            hidden_dim, hidden_dim, out_dim, 
            num_relations=int(getattr(args, "num_relations", 1)), 
            layers=layers, readout=readout, dropout=dropout
        )
    elif name == "han":
        base_model = HANBaseline(hidden_dim, hidden_dim, out_dim, layers, args.heads, dropout, readout)
    elif name == "hgt":
        # HGTBaseline is fixed in Step 2, but we still wrap it
        base_model = HGTBaseline(
            hidden_dim, hidden_dim, out_dim, 
            layers=layers, heads=args.hgt_heads, dropout=dropout, readout=readout,
            num_relations=int(getattr(args, "num_relations", 1)), # Pass num_relations
            add_reverse_rel=getattr(args, "rgcn_add_reverse_rel", False) # Pass reverse flag
        )
    else:
        raise ValueError(f"Unknown model: {args.model}")

    # --- Wrap the baseline model ---
    # The wrapper will handle:
    # 1. Fusing data.x (raw dense) + degree features
    # 2. Fusing node_type_ids embeddings (if embed_mode != none)
    # 3. Projecting the final raw vector -> hidden_dim
    # 4. Replacing data.x with this projected vector
    # 5. Calling base_model(data)
    
    model = NodeFeatureWrapper(
        base_model=base_model,
        raw_feature_dim=raw_feature_dim, # The dim of data.x from the parser
        num_tokens=num_node_tokens,
        args=args
    )
    
    return model

def _graphs_in_batch(b) -> int:
    # 1) direct property if valid
    try:
        ng = getattr(b, "num_graphs", None)
        if isinstance(ng, int) and ng > 0:
            return ng
    except Exception:
        pass
    # 2) batch vector
    try:
        if hasattr(b, "batch") and b.batch is not None:
            return int(b.batch.max().item()) + 1
    except Exception:
        pass
    # 3) graph-level labels length
    try:
        if hasattr(b, "y") and b.y is not None:
            return int(b.y.view(-1).size(0))
    except Exception:
        pass
    # 4) last ditch — treat as 1
    return 1



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
    first_probe_done: bool = False # Add parameter with default
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

        # ---- Count graphs this step (robust) & one-time probe ----
        graphs_this_step = _graphs_in_batch(b)
        seen_graphs += graphs_this_step

        if (not first_probe_done) and (not getattr(args, "no_progress", False)):
            try:
                by_attr  = getattr(b, "num_graphs", None)
                by_y     = int(b.y.view(-1).size(0)) if hasattr(b, "y") and b.y is not None else None
                by_batch = (int(b.batch.max().item()) + 1) if hasattr(b, "batch") and b.batch is not None else None
                tqdm.write(f"[Probe] graphs_in_batch: guess={graphs_this_step} | attr={by_attr} | by_y={by_y} | by_batch={by_batch}")
            except Exception:
                pass
            # Also dump a single edge debug line
            try:
                et = getattr(b, "edge_type", None)
                et_shape = (et.size() if (isinstance(et, torch.Tensor)) else None)
                unique_et = (int(torch.unique(et).numel()) if (isinstance(et, torch.Tensor) and et.numel() > 0) else 0)
                print("[Debug] edge_index:", b.edge_index.size(),
                      "| edge_type:", et_shape,
                      "| unique edge types:", unique_et)
            except Exception:
                pass

            # Check node_type_ids presence if we’re using embeddings
            need_ids = (str(getattr(model, 'embed_mode', 'none')).lower() in ('concat', 'replace')) \
                       and (getattr(model, 'input_emb', None) is not None)
            has_ids  = hasattr(b, "node_type_ids")
            if need_ids and not has_ids:
                raise RuntimeError(
                    "[BatchCheck] node_type_ids MISSING on first batch but embed_mode!=none. "
                    "Rebuild cache with --no-one-hot (dense) and a fresh --cache-tag."
                )
            elif has_ids:
                nid = b.node_type_ids
                print(f"[BatchCheck] node_type_ids OK | dtype={getattr(nid,'dtype',type(nid))} "
                      f"| len={int(nid.numel() if torch.is_tensor(nid) else len(nid))}")
            first_probe_done = True

        # Stochastic regularization during training (DropEdge + optional feature noise)
        if getattr(args, "dropedge_p", 0.0) > 0.0 or getattr(args, "train_feat_noise_std", 0.0) > 0.0:
            b = _augment_batch_for_eval(
                b,
                dropedge_p=float(getattr(args, "dropedge_p", 0.0)),
                feat_noise_std=float(getattr(args, "train_feat_noise_std", 0.0)),
                add_reverse_edges=False,   # <— NEW
            )
        # Drop a fraction of relations (edge types) as additional regularization
        if float(getattr(args, "rel_dropout_p", 0.0)) > 0.0:
            b = _relation_dropout_inplace(b, float(args.rel_dropout_p))


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
                    n_graphs = graphs_this_step
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

            # --- Project aux loss (binary softmax)
            # --- Project aux loss (binary softmax)
            if float(getattr(args, "project_w", 0.0)) > 0.0:
                proj_logits = out.get("proj_logits", None) if isinstance(out, dict) else None
                if proj_logits is not None:
                    # DO NOT use "or" between tensors; check None explicitly
                    p = getattr(b, "project_label", None)
                    if p is None:
                        p = getattr(b, "project_id", None)

                    if p is not None:
                        if not torch.is_tensor(p):
                            p = torch.as_tensor(p)

                        # move to the same device as logits and ensure shape/type
                        p = p.to(logits.device, non_blocking=True).view(-1).long()

                        # only keep rows with valid project targets (>=0)
                        valid = (p >= 0)
                        if valid.any():
                            loss_proj = F.cross_entropy(proj_logits[valid], p[valid], reduction="mean")
                            loss = loss + float(getattr(args, "project_w", 0.0)) * loss_proj


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
            torch.nn.utils.clip_grad_norm_(list(model.parameters()),                                   
                                            max_norm=float(getattr(args, "clip_grad", 1.0)))


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
        if seen_graphs <= 0:
            tqdm.write("[Debug][WARN] TRAIN epoch graphs counter was 0 — falling back to probe logic next epoch.")
        else:
            tqdm.write(f"[Debug] TRAIN epoch graphs seen = {seen_graphs}")

    mean_loss = total_loss_accum / max(1, len(loader))
    return mean_loss, global_step





# ────────────────────────────────────────────
# Audit helpers
# ────────────────────────────────────────────
def _audit_dataset_jsons(ds: DevignDataset, name: str = "SPLIT"):
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

# Put this at module scope (outside run), near other helpers
@torch.inference_mode()
def evaluate_project(model: nn.Module, loader: GeoDataLoader, device: torch.device,
                     threshold: float = 0.5) -> Dict[str, Any]:
    model.eval()
    y_true, y_prob = [], []
    disable = getattr(loader, "_no_progress", True)
    for batch in _tqdm(loader, desc="Evaluate(project)", disable=disable, total=len(loader)):
        b = batch.to(device, non_blocking=True)
        out = model(b)
        proj_logits = out["proj_logits"] if isinstance(out, dict) else None
        if proj_logits is None:
            continue

        logit = torch.nan_to_num(proj_logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
        if logit.size(-1) == 1:
            p1 = torch.sigmoid(logit.view(-1)).detach().cpu()
        else:
            p1 = F.softmax(logit, dim=-1)[:, 1].detach().cpu()

        # STANDARDIZE on 'project_label' (see #2 below)
        pt = getattr(b, "project_label", None)
        if pt is None:  # fallback if your dataset used 'project_id'
            pt = getattr(b, "project_id", None)
        if pt is None:
            continue

        pt = pt.view(-1).detach().cpu()
        mask = (pt >= 0)
        if not mask.any():
            continue
        y_true.extend(pt[mask].tolist())
        y_prob.extend(p1[mask].tolist())

    if not y_true:
        return {"acc": 0.0, "prec": 0.0, "rec": 0.0, "f1": 0.0, "auc": float("nan"),
                "cm": np.zeros((2,2), dtype=int), "thr": float(threshold)}

    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = clamp01_np(np.asarray(y_prob, dtype=np.float32))
    y_pred = (y_prob >= float(threshold)).astype(np.int64)

    acc = accuracy_score(y_true, y_pred)
    prec, rec, f1, _ = precision_recall_fscore_support(y_true, y_pred, average="binary", zero_division=0)
    try:
        auc = roc_auc_score(y_true, y_prob) if len(np.unique(y_true)) > 1 else float("nan")
    except Exception:
        auc = float("nan")
    cm = confusion_matrix(y_true, y_pred, labels=[0,1])
    return {"acc": float(acc), "prec": float(prec), "rec": float(rec), "f1": float(f1),
            "auc": float(auc) if np.isfinite(auc) else float("nan"),
            "cm": cm, "thr": float(threshold)}



def _as_int(val, default):
    return default if val is None else int(val)

# ────────────────────────────────────────────
# Run  — memory-safer DataLoader setup (no sharding/merge)
# ────────────────────────────────────────────
def run(args):
    torch.autograd.set_detect_anomaly(True) # <--- ADD THIS LINE
    from types import SimpleNamespace

    # ── seed & device
    set_seed(args.seed)
    device = torch.device("cuda" if torch.cuda.is_available() and not args.no_cuda else "cpu")
    if device.type == "cuda":
        props = torch.cuda.get_device_properties(0)
        print(f"[Device] CUDA available → {props.name} | cc {props.major}.{props.minor} | {props.total_memory/1e9:.1f} GB")
    else:
        print("[Device] CPU (CUDA not available or --no-cuda set)")

    # Avoid BLAS/OpenMP oversubscription during JSON parse + zip write
    import os
    os.environ.setdefault("OMP_NUM_THREADS", "1")
    os.environ.setdefault("MKL_NUM_THREADS", "1")
    os.environ.setdefault("OPENBLAS_NUM_THREADS", "1")
    os.environ.setdefault("NUMEXPR_NUM_THREADS", "1")
    torch.set_num_threads(1)



    # ── roots
    train_root = args.train_json_root or args.json_root
    val_root   = args.val_json_root   or args.json_root
    test_root  = args.test_json_root  or args.json_root

    # ── layout & cache
    layout    = _get_devign_layout(args)
    cache_dir = _ensure_cache_dir(args)

    # ── datasets (vocabs injected later)
    train_ds = DevignDataset(
        manifest_csv=args.train_manifest, json_root=train_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )
    val_ds = DevignDataset(
        manifest_csv=args.val_manifest, json_root=val_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )
    test_ds = DevignDataset(
        manifest_csv=args.test_manifest, json_root=test_root, feature_dim=args.feature_dim,
        cache_dir=cache_dir, cache_overwrite=bool(getattr(args, "cache_overwrite", False)),
        no_progress=bool(getattr(args, "no_progress", False)), strict_json=bool(getattr(args, "strict_json", True)),
        fallback_random=bool(getattr(args, "fallback_random", False)), report_missing=20,
        index_scan_prefixes=["train_func","valid_func","test_func","func"],
        node_vocab=None, edge_vocab=None
    )
    # wire debug flag for parsing / cache paths
    train_ds.debug_parse = bool(getattr(args, "parse_debug", False))
    val_ds.debug_parse   = bool(getattr(args, "parse_debug", False))
    test_ds.debug_parse  = bool(getattr(args, "parse_debug", False))
    
    # after you construct train_ds / val_ds / test_ds:
    train_ds.split_name = "train"
    val_ds.split_name   = "val"
    test_ds.split_name  = "test"


    # --- BEGIN: quick class breakdown per mutation_type (pre-filter) ---
    from collections import Counter, defaultdict

    def _label_counts(rows):
        by_mut = defaultdict(lambda: Counter({0: 0, 1: 0}))
        for r in rows:
            mt = str(r.get("mutation_type", "")).lower() or "unknown"
            y  = int(r.get("label", 0))
            by_mut[mt][y] += 1
        return by_mut

    for name, ds in [("TRAIN", train_ds), ("VAL", val_ds), ("TEST", test_ds)]:
        by_mut = _label_counts(ds.rows)
        total  = sum(sum(c.values()) for c in by_mut.values())
        pos    = sum(c[1] for c in by_mut.values())
        neg    = sum(c[0] for c in by_mut.values())
        print(f"[ClassBreakdown][{name}][pre-filter] total={total} pos={pos} neg={neg} pos_frac={pos/(total+1e-9):.4f}")
        for mt, c in by_mut.items():
            t = c[0] + c[1]
            print(f"  - {mt:8s}: n={t:6d}  pos={c[1]:6d}  neg={c[0]:6d}  pos_frac={c[1]/(t+1e-9):.4f}")
# --- END: quick class breakdown per mutation_type (pre-filter) ---

    
    # after creating train_ds / val_ds / test_ds, but BEFORE calling any cache init/reconfigure hooks:
    for ds in (train_ds, val_ds, test_ds):
        ds.one_hot = bool(getattr(args, "one_hot", True))
        if not ds.one_hot:
            ds.feature_dim = int(getattr(args, "emb_dim", 64))  # <-- set to 128 for --no-one-hot --emb-dim 128
        ds.cache_tag = getattr(args, "cache_tag", "")

        # now it’s safe to (re)configure caches, they’ll use the correct feature_dim
        try:
            for hook in ("_ensure_graph_cache", "_reset_graph_cache", "_init_graph_cache"):
                if hasattr(ds, hook):
                    try:
                        getattr(ds, hook)(shards=getattr(ds, "cache_shards", 1),
                                        tmpdir=getattr(ds, "cache_tmpdir", ""))
                    except TypeError:
                        getattr(ds, hook)()
                    break
            else:
                zc = getattr(ds, "_get_zip_cache", lambda: None)()
                if zc and hasattr(zc, "reconfigure"):
                    try:
                        zc.reconfigure(num_shards=getattr(ds, "cache_shards", 1),
                                    tmpdir=getattr(ds, "cache_tmpdir", ""))
                    except TypeError:
                        zc.reconfigure()
        except Exception:
            pass


        # Optional: faster IO if supported by your cache writer
        for attr, val in [
            ("cache_compression", "stored"),   # no compression: fastest
            ("cache_store_mode", "append"),    # append/incremental if supported
            ("cache_flush_every", 4096),       # buffer more entries before flushing
        ]:
            if hasattr(ds, attr):
                try:
                    setattr(ds, attr, val)
                except Exception:
                    pass

    # If dense mode, make the dataset feature_dim match emb_dim so the parser uses it
    if not getattr(args, "one_hot", True):
        emb_dim = int(getattr(args, "emb_dim", 64))
        for ds in (train_ds, val_ds, test_ds):
            ds.feature_dim = emb_dim
        print(f"[FeatWire] Dense mode → dataset.feature_dim set to emb_dim={emb_dim}")

    # ---- Optional: VAL/TEST on originals only ----
    def _is_orig_row(r: dict) -> bool:
        mut = str(r.get("mutation_type", "")).lower()
        jp  = (r.get("json_path") or r.get("graph_json_path") or "").strip().lower()
        return (mut == "orig") or (jp.endswith("/export.json") or jp.endswith("\\export.json"))

    if bool(getattr(args, "val_original_only", False)):
        _before = len(val_ds.rows)
        val_ds.rows = [r for r in val_ds.rows if _is_orig_row(r)]
        print(f"[SplitFilter][VAL] kept originals {len(val_ds.rows)}/{_before}")

    if bool(getattr(args, "test_original_only", False)):
        _before = len(test_ds.rows)
        test_ds.rows = [r for r in test_ds.rows if _is_orig_row(r)]
        print(f"[SplitFilter][TEST] kept originals {len(test_ds.rows)}/{_before}")

    # --- BEGIN: quick class breakdown per mutation_type (post-filter) ---
    for name, ds in [("TRAIN", train_ds), ("VAL", val_ds), ("TEST", test_ds)]:
        by_mut = _label_counts(ds.rows)
        total  = sum(sum(c.values()) for c in by_mut.values())
        pos    = sum(c[1] for c in by_mut.values())
        neg    = sum(c[0] for c in by_mut.values())
        print(f"[ClassBreakdown][{name}][post-filter] total={total} pos={pos} neg={neg} pos_frac={pos/(total+1e-9):.4f}")
        for mt, c in by_mut.items():
            t = c[0] + c[1]
            print(f"  - {mt:8s}: n={t:6d}  pos={c[1]:6d}  neg={c[0]:6d}  pos_frac={c[1]/(t+1e-9):.4f}")
    # --- END: quick class breakdown per mutation_type (post-filter) ---
        


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
    if args.model.lower() == "mptcn_tts" and args.spatial.lower() in ("rgcn", "hgt"):
        args.bases = int(args.num_relations)  # num_relations = len(edge_vocab)
        print(f"[FeatWire][MPTCN_TTS][RGCN] bases set to num_relations={args.bases}")



    v_sig = _vocab_signature(node_vocab, edge_vocab)
    train_ds._vocab_sig = v_sig
    val_ds._vocab_sig   = v_sig
    test_ds._vocab_sig  = v_sig

    # ---- sanity probe: confirm node_type_ids BEFORE any cache work ----
    try:
        _probe = train_ds[0]
        has_nid = hasattr(_probe, "node_type_ids")
        n_nodes = int(getattr(_probe, "num_nodes", _probe.x.size(0)))
        if has_nid:
            nid = _probe.node_type_ids
            print(f"[Probe] node_type_ids present | dtype={getattr(nid,'dtype',type(nid))} "
                f"| len={int(nid.numel() if torch.is_tensor(nid) else len(nid))} "
                f"| num_nodes={n_nodes} | unique={int(torch.unique(nid).numel()) if torch.is_tensor(nid) else 'n/a'}")
            if torch.is_tensor(nid):
                assert nid.dtype == torch.long, "[Probe][ERR] node_type_ids must be torch.long"
                assert nid.numel() == n_nodes,  "[Probe][ERR] len(node_type_ids) != num_nodes"
        else:
            print("[Probe][WARN] node_type_ids MISSING on train_ds[0]. If using embed_mode=concat/replace, your cache is likely stale.")
    except Exception as e:
        print(f"[Probe][INFO] Could not inspect train_ds[0]: {e}")


    if int(getattr(args, "dry_run", 0)) > 0:
        k = min(int(args.dry_run), len(train_ds))
        print(f"[DryRun] Parsing {k} graphs from TRAIN then exiting…")
        for i in range(k):
            _ = train_ds[i]
            if (i + 1) % 10 == 0 or (i + 1) == k:
                print(f"[DryRun] {i+1}/{k} parsed")
        print("[DryRun] OK")
        return


    def _as_int(val, default):
        return default if val is None else int(val)





    import inspect

    if getattr(args, "warm_cache", False):
        hw = os.cpu_count() or 1

        # >>> TUNED FOR YOUR 80-CORE MACHINE <<<
        # Go back up: this was faster in your earlier run.
        # Keep a safety margin (leave ~8 cores idle for OS/other tasks).
        default_workers = max(8, min(72, hw - 8))  # earlier you saw ~72 give ~11.5 it/s
        builder_workers = int(os.environ.get("DEVIGN_CACHE_WORKERS", default_workers))

        # Make the producer queue deeper; avoids starvation
        default_max_outstanding = builder_workers * 64
        max_outstanding = int(os.environ.get("DEVIGN_MAX_OUTSTANDING", default_max_outstanding))

        print(f"[Cache] Targeting {builder_workers} workers | max_outstanding={max_outstanding} (on {hw}-core system)")

        for ds_, tag in [(train_ds, "TRAIN"), (val_ds, "VAL"), (test_ds, "TEST")]:
            # If your method supports a 'shards' kw, pass it; else it will use ds_.cache_shards set above
            sig = inspect.signature(ds_.build_cache_all)
            supported = sig.parameters
            bc_kwargs = {}

            # High-level toggles (only if supported)
            if "max_workers" in supported:
                bc_kwargs["max_workers"] = builder_workers
            if "max_outstanding" in supported:
                bc_kwargs["max_outstanding"] = max_outstanding
            if "force" in supported:
                bc_kwargs["force"] = bool(getattr(args, "cache_overwrite", False))
            if "show_progress" in supported:
                bc_kwargs["show_progress"] = (not getattr(args, "no_progress", False))
            if "parse_strict" in supported:
                # >>> LOOSEN STRICTNESS FOR SPEED (skips heavy exception paths)
                bc_kwargs["parse_strict"] = False

            # Try passing shards if the API supports it; otherwise the ds_.cache_shards we set above will apply.
            if "shards" in supported:
                bc_kwargs["shards"] = int(getattr(args, "cache_shards", 1))
            if "tmpdir" in supported:
                bc_kwargs["tmpdir"] = getattr(args, "cache_tmpdir", "") or None

            stats = ds_.build_cache_all(**bc_kwargs)
            print(f"[Cache][{tag}] stats: {stats}")

            # Merge shards if applicable
            zc_ = ds_._get_zip_cache()
            if isinstance(zc_, GraphShardedCache) and bool(getattr(args, "merge_shards", True)):
                base_zip = zc_.base_zip or (ds_.cache_dir / f"graph_cache_{ds_.split_name}.zip")
                zc_.merge_to(base_zip, delete_after=bool(getattr(args, "delete_shards_after_merge", True)))
                print(f"[Cache][{tag}] merged shards → {base_zip}")
    else:
        print("[Cache] warm_cache=False → skipping upfront cache build.")

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
# ── DataLoaders (robust: never int(None); prefetch only when workers > 0)
    def _as_int(val, default):
        return default if val is None else int(val)

    print(f"[Manifest] TRAIN={len(train_ds)}  VAL={len(val_ds)}  TEST={len(test_ds)}")
    print("[Stage] Building DataLoaders…")

    pin = (device.type == "cuda")

    # ---- [FIX] Family-Aware Sampler for TRAIN ----
    # This replaces the WeightedRandomSampler to ensure mutant-aware
    # losses receive batches grouped by family.
    # Class balancing is now handled by the `pos_weight` in the loss function.
    
    train_sampler = FamilyAwareSampler(
        manifest_rows=train_ds.rows,
        batch_size=_as_int(getattr(args, "train_batch_size", None),
                           _as_int(getattr(args, "batch_size", None), 128)),
        num_members_per_family=int(getattr(args, "family_members_k", 4)),
        seed=int(getattr(args, "seed", 42))
    )

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
        train_ds,
        batch_size=train_bs,
        sampler=train_sampler,      # ← [FIX] use the new family-aware sampler
        shuffle=False,              # ← must be False when sampler is set
        num_workers=num_workers_train,
        **dl_kwargs_train,
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
    num_node_tokens = len(node_vocab)
    if getattr(args, "one_hot", True):
        raw_feature_dim = num_node_tokens
        print(f"[FeatWire] Using ONE-HOT features → raw_in_dim={raw_feature_dim}")
    else:
        # This is the --emb-dim arg, which controls the parser's output dim
        raw_feature_dim = int(getattr(args, "emb_dim", 64)) 
        print(f"[FeatWire] Using DENSE features → raw_in_dim={raw_feature_dim}")
        if getattr(args, "embed_mode", "none") == "none":
            print(f"[FeatWire][WARN] --no-one-hot is set but --embed-mode=none. "
                  f"Model will ONLY use dense features from parser (potentially zeros).")
        else:
             print(f"[FeatWire] Learned embeddings will be used (mode={args.embed_mode}).")


    # ... (probe code) ...

    # ── model
    model = make_model(
        args, 
        raw_feature_dim=raw_feature_dim, 
        num_node_tokens=num_node_tokens, 
        pna_deg_hist=pna_deg_hist
    )

    # record flags on the module
    model.debug_rgcn_io = bool(getattr(args, "debug_rgcn_io", False))
    model.use_row_norm   = bool(getattr(args, "row_norm", False))
    model.use_ckpt       = True  # turn on for deep stacks to save memory


    # If using dense features (--no-one-hot) and user asked for embeddings,
    # attach the embedding table and set fusion mode.
    if (not getattr(args, "one_hot", True)) and hasattr(model, "attach_input_embedding"):
        if str(getattr(args, "embed_mode", "none")).lower() in ("concat", "replace"):
            model.attach_input_embedding(
                num_tokens=len(node_vocab),
                emb_dim=int(getattr(args, "emb_dim", in_dim)),
                mode=str(getattr(args, "embed_mode", "concat"))
            )

    model = model.to(device)
    # Enable per-batch RGCN prints when requested
    try:
        model.debug_rgcn_io = bool(getattr(args, "debug_rgcn_io", False))
    except Exception:
        pass

    # Check if a baseline is used with incompatible dense feature settings
    is_baseline = args.model.lower() not in ("mptcn_tts",) # Add other complex models if they get embedding support
    use_embed = not getattr(args, "one_hot", True) and str(getattr(args, "embed_mode", "none")).lower() != "none"
    
    if is_baseline and use_embed:
        print(f"[WARN] Baseline model '{args.model}' selected with --no-one-hot and --embed-mode={args.embed_mode}. "
              f"Baselines currently do not use learned embeddings from node_type_ids. "
              f"They will only use the basic dense features from the parser (potentially zeros). "
              f"Performance may be significantly degraded. Consider using MPTCN_TTS or --one-hot.")

    # If using dense features (--no-one-hot) and user asked for embeddings,
    # attach the embedding table and set fusion mode FOR MPTCN_TTS.
    if args.model.lower() == "mptcn_tts" and (not getattr(args, "one_hot", True)) and hasattr(model, "attach_input_embedding"):
        if str(getattr(args, "embed_mode", "none")).lower() in ("concat", "replace"):
            print(f"[FeatWire] Attaching nn.Embedding to MPTCN_TTS (mode={args.embed_mode}, size={len(node_vocab)}, dim={args.emb_dim})")
            model.attach_input_embedding(
                num_tokens=len(node_vocab),
                emb_dim=int(getattr(args, "emb_dim", in_dim)), # Use emb_dim for embedding width
                mode=str(getattr(args, "embed_mode", "concat"))
            )
            
    model = model.to(device)

    # NEW: project aux head
    if bool(getattr(args, "project_aux", False)):
        model = ProjectAux(model, hidden_dim=int(getattr(args, "hidden_dim", 256)),
                        num_proj_classes=2, dropout=float(getattr(args, "dropout", 0.3))).to(device)



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
        warmup_min = float(getattr(args, "warmup_min_factor", 0.05))
        if step_idx < warmup_steps:
            return max(warmup_min, float(step_idx + 1) / float(max(1, warmup_steps)))
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
    best_f1 = -float('inf')
    best_state = None
    best_delta = None
    best_epoch = -1

    # NEW: per-project threshold maps (VAL-most-recent and best-so-far)
    thr_map = None
    best_thr_map = None

    best_thr_map = {}   # <-- add this line
    delta = args.calib_max_pos_delta if args.calib_max_pos_delta is not None else 2.0
    calib_cfg = CalibConfig(
        beta=float(getattr(args, "calib_beta", 1.0)),
        min_precision=(None if args.min_precision is None else float(args.min_precision)),
        max_pos_rate_over_base=1.0 + float(delta),
        min_pos_frac=float(getattr(args, "calib_min_pos_frac", 0.02)),
        ema_alpha=float(getattr(args, "thr_ema_alpha", 0.6)),
    )
    setattr(calib_cfg, "min_recall", (None if args.min_recall is None else float(args.min_recall)))

    # ensure optional recall constraint is wired
    setattr(calib_cfg, "min_recall", (None if getattr(args, "min_recall", None) is None else float(args.min_recall)))

    thr_ema = None
    global_step = 0
    first_probe_done = False # <--- PASTE THE LINE HERE

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
            global_step=global_step, scheduler=scheduler, # <--- FIX: Was scheduler=None
            first_probe_done=first_probe_done # Pass the current value
        )

        if not args.no_progress:
            _lr = optimizer.param_groups[0].get("lr", float(getattr(args, "lr", 0.0)))
            print(f"[Opt] lr={_lr:.6g}")

        # collect VAL probabilities (T=1.0, optional TTA)
        # collect VAL probabilities (T=1.0, optional TTA)  — NOW RETURNS projv ALSO
        yv, pv, projv = collect_probs_with_T(
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
            pv_np = np.asarray(pv, dtype=np.float64)
            pos_rate_used = float((pv_np >= thr_calib).mean()) if pv_np.size else float('nan')

            # Metrics at USED threshold (post clamp/EMA)
            from sklearn.metrics import precision_recall_fscore_support
            y_pred_used = (pv_np >= thr_calib).astype(np.int64)
            p_u, r_u, f_u, _ = precision_recall_fscore_support(yv, y_pred_used, average="binary", zero_division=0)

            print(
                f"[Calib] raw_thr={_stats.get('thr_raw', float('nan')):.6f} "
                f"adj_thr={_stats.get('thr_used', thr_calib):.6f} "
                f"| pos_rate_raw={_stats.get('pos_rate_raw', float('nan')):.4f} "
                f"pos_rate_used={pos_rate_used:.4f} base={train_base_rate:.4f} "
                f"| RAW(F/P/R)={_stats.get('f', float('nan')):.4f}/{_stats.get('p', float('nan')):.4f}/{_stats.get('r', float('nan')):.4f} "
                f"USED(F/P/R)={f_u:.4f}/{p_u:.4f}/{r_u:.4f}"
            )
            # Inversion sanity: if probs are inverted relative to labels, AUC on (1-p) will be high
            try:
                from sklearn.metrics import roc_auc_score
                auc_inv = roc_auc_score(yv, 1.0 - np.asarray(pv, dtype=np.float64))
                print(f"[Calib][sanity] AUC={_stats.get('auc', float('nan')):.6f} | AUC_inv={auc_inv:.6f}")
            except Exception:
                pass

       
        # NEW: per-project thresholds on VAL (guarded)
        thr_map = None
        try:
            # use projv (the one returned by collect_probs_with_T)
            thr_map = calibrate_thr_per_project(
                y=yv, p=pv, proj=projv,
                beta=calib_cfg.beta,
                min_prec=calib_cfg.min_precision,
                min_rec=getattr(calib_cfg, "min_recall", None),
            )
        except Exception:
            thr_map = None  # function missing or inputs invalid → fall back to global threshold

        if not args.no_progress and thr_map:
            print(f"[Calib][per-project] VAL thresholds: {thr_map}")




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
        # track & save best checkpoint
        if val_m["f1"] > best_f1:
            best_f1 = float(val_m["f1"])
            best_state = {k: v.detach().cpu() for k, v in model.state_dict().items()}
            best_delta = ({k: v.detach().cpu() for k, v in delta_head.state_dict().items()} if delta_head is not None else None)
            best_epoch = int(ep)
            best_thr_map = (dict(thr_map) if thr_map is not None else None)  # guard: thr_map may be None



            best_ckpt = {
                "state_dict": best_state,
                "delta_head": best_delta,
                "args": vars(args),
                "val_metrics": val_m,
                "epoch": best_epoch,
                "thr_ema": float(thr_ema),
                "thr_per_project": best_thr_map,   # NEW: persist
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

    # ---- A7.2 transform per-project thresholds by T (if temp. scaling enabled)
    thr_post_map = {}
    if 'best_thr_map' in locals() and isinstance(best_thr_map, dict):
        if bool(getattr(args, "do_temperature", False)):
            thr_post_map = {pid: transform_threshold_preT_to_postT(th, float(T_val))
                            for pid, th in best_thr_map.items()}
        else:
            thr_post_map = dict(best_thr_map)


    # ── final test
    test_m = evaluate(
         model, test_loader, device, threshold=thr_post, temperature=float(getattr(args, "T_test", 1.0)),
        tta=int(getattr(args, "tta", False)),
        tta_dropedge_p=float(getattr(args, "tta_dropedge_p", 0.0)),
        tta_feat_noise_std=float(getattr(args, "tta_feat_noise_std", 0.0)),
        threshold_map=(best_thr_map if best_thr_map is not None else thr_map)
    )

    # ── write results
    out_dir = layout["results"] if args.output_dir == "./results_devign" else Path(args.output_dir)
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

    # --- NEW: project eval (only if aux enabled) ---
    proj_test_m = None
    if bool(getattr(args, "project_aux", False)):
        proj_test_m = evaluate_project(model, test_loader, device, threshold=0.5)
        with open(out_dir / "test_metrics_project.json", "w", encoding="utf-8") as f:
            json.dump(_jsonify(proj_test_m), f, indent=2)
        try:
            cm_p = proj_test_m.get("cm", None)
            if cm_p is not None:
                fig = plt.figure(figsize=(4, 4))
                plt.imshow(cm_p, interpolation="nearest"); plt.title("Confusion Matrix (Project)"); plt.colorbar()
                tick = np.arange(2); plt.xticks(tick, ["debian","chrome"]); plt.yticks(tick, ["debian","chrome"])
                for i in range(2):
                    for j in range(2):
                        plt.text(j, i, format(cm_p[i, j], 'd'), ha="center", va="center")
                plt.ylabel("True"); plt.xlabel("Predicted"); plt.tight_layout()
                fig.savefig(out_dir / "confusion_matrix_project.png", dpi=160); plt.close(fig)
        except Exception:
            pass

    print(f"[TEST] F1={test_m['f1']:.4f} P={test_m['prec']:.4f} R={test_m['rec']:.4f} AUC={test_m['auc']} thr_post={thr_post:.4f} T={T_val:.3f}")
    if proj_test_m is not None:
        print(f"[TEST][Project] F1={proj_test_m['f1']:.4f} P={proj_test_m['prec']:.4f} R={proj_test_m['rec']:.4f} AUC={proj_test_m['auc']}")
    return test_m






# ────────────────────────────────────────────
# CLI  [COMPLETED]
# ────────────────────────────────────────────
def build_parser():
    parser = argparse.ArgumentParser(
        description="MPTCN-TTS Devign mutant-aware runner",
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
                        choices=["mean", "sum", "max", "attn"],
                        help=("Global readout: 'mean'/'sum'/'max' via PyG global_*_pool, "
                            "or 'attn' (GlobalAttention with a 1-layer gate)."))

    parser.add_argument("--feature-dim", type=int, default=64, dest="feature_dim",
                        help="Default node feature width used for dataset fallbacks and/or simple featurizers.")

    # Input feature wiring
    parser.add_argument("--one-hot", dest="one_hot", action="store_true", default=True,
                        help="Assume parser emits one-hot node features (width=len(node_vocab)).")
    parser.add_argument("--no-one-hot", dest="one_hot", action="store_false",
                        help="(Advanced) You changed the parser to emit dense features.")



    # Data IO
    parser.add_argument("--train-manifest", type=str, required=True)
    parser.add_argument("--val-manifest",   type=str, required=True)
    parser.add_argument("--test-manifest",  type=str, required=True)

    parser.add_argument("--json-root", type=str, default=None, help="Fallback root if per-split roots not provided")
    parser.add_argument("--train-json-root", type=str, default=None)
    parser.add_argument("--val-json-root",   type=str, default=None)
    parser.add_argument("--test-json-root",  type=str, default=None)

    parser.add_argument("--cache-dir", type=str, default=None,
                        help="Directory to save/load cached graphs & precomputations (defaults to <json_root>/../cache_devign)")
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



    # Embedding fusion mode (for --no-one-hot only)
    parser.add_argument("--embed-mode", type=str, default="none",
                        choices=["none", "concat", "replace"],
                        help="How to use nn.Embedding when dense features are used: "
                             "'none' (disable), 'concat' (dense ⊕ embedding), or 'replace' (embedding only).")


    parser.add_argument("--project-aux", action="store_true",
                    help="Enable auxiliary project classification head (debian vs chrome).")
    parser.add_argument("--project-w", type=float, default=0.2,
                    help="Loss weight for the project aux head.")

    parser.add_argument("--family-members-k", type=int, default=4,
                    help="For FamilyAwareSampler, the number of members (K) to sample per family for a batch.")

    # --- NEW: graph relation & stability controls ---
    parser.add_argument(
        "--rgcn-add-reverse-rel", action="store_true",
        help="Duplicate edges in reverse direction for RGCN/HGT (RGCN layers must be constructed with 2*bases relations)."
    )
    parser.add_argument(
        "--rel-dropout-p", type=float, default=0.0,
        help="During TRAIN, randomly replace an edge_type with UNK (id=0) with probability p."
    )
    parser.add_argument(
        "--clip-grad", type=float, default=0.0,
        help="If >0, clip global grad-norm to this value before optimizer.step(). (train loop already clips at 1.0; this overrides it if set.)"
    )



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

    parser.add_argument("--val-original-only",  action="store_true",
                    help="If set, keep only original (non-mutated) graphs in VAL.")
    parser.add_argument("--test-original-only", action="store_true",
                        help="If set, keep only original (non-mutated) graphs in TEST.")

    # Debugging / tracing
    parser.add_argument("--debug-rgcn-io", action="store_true",
                        help="Print per-layer/batch edge sizes & relation counts in RGCN path.")
    parser.add_argument("--debug-parser", action="store_true",
                        help="Print parser/cache decisions and first-graph stats when parsing.")

    parser.add_argument("--warmup-min-factor", type=float, default=0.05,
                        help="Minimum LR multiplier during warmup (was 1e-3).")

    parser.add_argument('--rgcn-num-bases', type=int, default=None,
                        help='Basis count for RGCN (<= forward bases). Defaults to bases//2.')


    # Temps / architecture knobs
    parser.add_argument("--T", type=float, default=1.0)
    parser.add_argument("--T-test", type=float, default=1.0, dest="T_test")
    parser.add_argument("--Lt", type=int, default=2)
    parser.add_argument("--Ls", type=int, default=2)
    parser.add_argument("--Kt", type=int, default=3, help="Kernel size for TCN temporal module")
    parser.add_argument("--Ks", type=int, default=3, help="Kernel size for GNN spatial module (e.g., ChebConv)")
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
    parser.add_argument("--no-progress", action="store_true")
    parser.add_argument("--label-smoothing", type=float, default=0.02)
    parser.add_argument("--head-warmup-steps", type=int, default=500)

    # AMP/Device
    parser.add_argument("--no-amp", action="store_true")
    parser.add_argument("--no-cuda", action="store_true")
    parser.add_argument("--num-workers", type=int, default=0)

    # Pretrain controls
    parser.add_argument("--do-contrastive", action="store_true")
    parser.add_argument("--pre-epochs", type=int, default=0)
    parser.add_argument("--tau", type=float, default=0.1)

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
    parser.add_argument("--cache-tag", type=str, default="",
    help="Optional suffix for cache zip/shards (e.g., 'dense', 'oh').")


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
    parser.add_argument("--calib-max-pos-delta", type=float, default=2.0, dest="calib_max_pos_delta")
    parser.add_argument("--calib-min-pos-frac", type=float, default=0.02, dest="calib_min_pos_frac")
    parser.add_argument("--do-temperature", action="store_true")
    parser.add_argument(
        "--reg-warmup-epochs",
        dest="reg_warmup_epochs",
        type=int,
        default=3,
        help="Warm up regularizers (consistency/supcon/proto/delta) linearly over the first N epochs."
    )


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
    parser.add_argument("--output-dir", type=str, default="./results_devign")

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

A (mptcn_tts • cheb • tcn)

Pretrain

python 01_MPTCN_TTS_Devign.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"


Fine-tune

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"


Both

python 01_MPTCN_TTS_Devign.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"

B (mptcn_tts • cheb • tcn)

Pretrain

python 01_MPTCN_TTS_Devign.py \
  --stage pretrain \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"


Fine-tune

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"


Both

python 01_MPTCN_TTS_Devign.py \
  --stage both \
  --model mptcn_tts \
  --spatial cheb \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"

C (mptcn_tts • cheb • gru)

Pretrain

python 01_MPTCN_TTS_Devign.py \
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
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json" \
  --val-json-root   "./Json_exports/normalized_devign_json" \
  --test-json-root  "./Json_exports/normalized_devign_json"


Fine-tune


python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial cheb \
  --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 192 \
  --epochs 30 \
  --hidden-dim 256 \
  --emb-dim 128 \
  --no-one-hot \
  --family-members-k 4 \
  --cache-tag dense_cheb_gru_v1 \
  --lr 2e-4 \
  --dropout 0.25 \
  --label-smoothing 0.0 \
  --focal-gamma 0.8 \
  --max-pos-weight 4.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.05 \
  --consistency-w 0.02 \
  --supcon-w 0.02 --supcon-tau 0.07 \
  --proto-w 0.01 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --warm-cache \
  --do-temperature \
  --calib-beta 1.5 \
  --min-recall 0.50 \
  --min-precision 0.30 \
  --calib-max-pos-delta 0.60 \
  --calib-min-pos-frac 0.04 \
  --thr-ema-alpha 0.80 \
  --val-interval 1 \
  --num-workers 64 \
  --eval-num-workers 64 \
  --prefetch-factor 2 \
  --eval-prefetch-factor 2 \
  --persistent-workers \
  --eval-persistent-workers \
  --mp-context forkserver \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_devign_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_devign_json/test_graphson" \
  --cache-dir "./Json_exports/cache_devign" \
  --cache-shards 16\
  --cache-tmpdir /dev/shm \
  --merge-shards \
  --delete-shards-after-merge


AAAAAAAAAAAAAAAAAAAAAAAAAA
python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial cheb --temporal gru \
  --Ls 2 --Lt 2 --Kt 3 \
  --batch-size 256 --epochs 60 \
  --no-amp \
  --hidden-dim 256 --emb-dim 128 --no-one-hot \
  --family-members-k 4 \
  --cache-tag dense_cheb_gru_v1 \
  --weight-decay 0.01 \
  --lr 1.5e-4 --dropout 0.25 \
  --label-smoothing 0.02 --focal-gamma 0 \
  --max-pos-weight 12 --lambda-dom 0.0 \
  --train-feat-noise-std 0 --dropedge-p 0 \
  --consistency-w 0.05 --proto-w 0.01 \
  --supcon-w 0.03 --supcon-tau 0.07 \
  --delta-head --delta-w 0 --delta-pairs-per-family 2 \
  --tta 2 --thr-ema-alpha 0.7  --T 1 --T-test 1 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --no-audit \
  --num-workers 8 --eval-num-workers 8 \
  --min-precision 0.30 --min-recall 0.50 \
  --calib-beta 1.5 \
  --calib-max-pos-delta 1.0 \
  --do-temperature \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_train_mix_advT3.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_valid_advT3.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/manifest_test_advT3.csv" \
  --train-json-root "./Json_exports/normalized_devign_json/train_graphson" \
  --val-json-root   "./Json_exports/normalized_devign_json/valid_graphson" \
  --test-json-root  "./Json_exports/normalized_devign_json/test_graphson" \
  --cache-dir "./Json_exports/cache_devign" \
  --no-warm-cache

BBBBBBBBBBBBBBBBBBBBBBBBBBB
for building cache only


###########################################################
#### Command for BUILDING CACHE ONLY ######################
###########################################################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --epochs 0 \
  --model mptcn_tts --spatial cheb --temporal gru \
  --hidden-dim 256 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --cache-tag dense_cheb_gru_v1_catNID \
  --num-workers 64 \
  --eval-num-workers 64 \
  --mp-context forkserver \
  --warm-cache \
  --cache-overwrite \
  --cache-shards 16 \
  --cache-tmpdir /dev/shm \
  --merge-shards \
  --delete-shards-after-merge \
  --no-audit \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"



for training only

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial cheb --temporal gru \
  --Ls 2 --Lt 3 --Kt 3 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --cache-tag dense_cheb_gru_v1_catNID \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.45 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"







###### for training only with TCN ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial cheb --temporal tcn \
  --Ls 2 --Lt 3 --Kt 3 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --cache-tag dense_cheb_tcn_v1_catNID\
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.45 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"


#### For training only with GCN x GRU ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial gcn --temporal gru \
  --Ls 2 --Lt 5 --Kt 3 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.0 \
  --min-precision 0.25 --min-recall 0.40 \
  --calib-max-pos-delta 0.25 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"


#### For training only with GCN x TCN ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts  --spatial gcn --temporal tcn \
  --Ls 3 --Lt 5 --Kt 5 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.45 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"



#### For training only with sage × gru ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts  --spatial sage --temporal gru \
  --Ls 7 --Lt 9 --Kt 9 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.40 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"


#### For training only with sage × tcn ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts  --spatial sage --temporal tcn \
  --Ls 9 --Lt 9 --Kt 9 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.45 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"



#### For training only with gat × gru ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts  --spatial gat --temporal gru \
  --heads 8 \
  --Ls 9 --Lt 9 --Kt 9 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 520 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.20 --min-recall 0.30 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"

#### For training only with gat × tcn ############################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts  --spatial gat --temporal tcn \
  --heads 8 \
  --Ls 4 --Lt 3 --Kt 3 \
  --batch-size 192 --epochs 100 \
  --hidden-dim 512 --emb-dim 128 --no-one-hot \
  --embed-mode concat \
  --family-members-k 4 \
  --lr 1.5e-4 --weight-decay 0.01 \
  --dropout 0.25 --label-smoothing 0.02 --focal-gamma 0.8 \
  --max-pos-weight 8.0 --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.05 \
  --consistency-w 0.03 --supcon-w 0.05 --supcon-tau 0.07 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.01 --delta-pairs-per-family 2 \
  --tta 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.8 \
  --do-temperature --calib-beta 1.5 \
  --min-precision 0.30 --min-recall 0.37 \
  --calib-max-pos-delta 0.40 --calib-min-pos-frac 0.03 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --project-w 0.2 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"



###########################################################
#### Training: rgcn × gru #################################
###########################################################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial rgcn --temporal gru \
  --rgcn-add-reverse-rel \
  --readout attn \
  --Ls 3 --Lt 2 \
  --batch-size 192 --epochs 80 \
  --hidden-dim 256 --emb-dim 128 --no-one-hot --embed-mode concat \
  --family-members-k 4 \
  --lr 3e-4 --weight-decay 0.01 \
  --dropout 0.15 --rel-dropout-p 0.10 --label-smoothing 0.02 --focal-gamma 0.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.03 \
  --consistency-w 0.02 --supcon-w 0.05 --supcon-tau 0.08 --supcon-mode label+family \
  --proto-w 0.02 --proto-ema-m 0.995 \
  --delta-head --delta-w 0.00 --delta-pairs-per-family 2 \
  --reg-warmup-epochs 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.7 \
  --do-temperature --calib-beta 1.0 \
  --min-precision 0.50 --min-recall 0.50 \
  --calib-max-pos-delta 0.30 --calib-min-pos-frac 0.05 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --seed 42 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"




##################################################################
#### Training: rgcn × tcn (Both Stages, 3-Member Families) #####
##################################################################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts \
  --spatial rgcn \
  --temporal tcn \
  --rgcn-add-reverse-rel \
  --rgcn-num-bases 32 \
  --readout attn \
  --row-norm \
  --Ls 8 \
  --Lt 3 \
  --hidden-dim 480 \
  --emb-dim 128 \
  --batch-size 64 \
  --accum-steps 8 \
  --epochs 80 \
  --no-one-hot \
  --embed-mode concat \
  --family-members-k 3 \
  --lr 5e-5 \
  --weight-decay 0.01 \
  --dropout 0.20 \
  --rel-dropout-p 0.10 \
  --label-smoothing 0.02 \
  --focal-gamma 0.0 \
  --train-feat-noise-std 0.01 \
  --dropedge-p 0.03 \
  --clip-grad 1.0 \
  --lambda-dom 0.0 \
  --consistency-w 0.02 \
  --supcon-w 0.08 \
  --supcon-tau 0.10 \
  --supcon-mode label+family \
  --proto-w 0.03 \
  --proto-ema-m 0.99 \
  --delta-head \
  --delta-w 0.00 \
  --delta-pairs-per-family 2 \
  --reg-warmup-epochs 2 \
  --do-temperature \
  --T 1 \
  --T-test 1 \
  --thr-ema-alpha 0.7 \
  --min-precision 0.50 \
  --min-recall 0.50 \
  --calib-max-pos-delta 0.25 \
  --calib-min-pos-frac 0.05 \
  --val-interval 1 \
  --num-workers 32 \
  --eval-num-workers 32 \
  --prefetch-factor 2 \
  --persistent-workers \
  --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --seed 42 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"


###########################################################
#### Training: rgcn × tcn (minimum) #######################
###########################################################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial rgcn --temporal tcn \
  --rgcn-add-reverse-rel \
  --Ls 4 --Lt 2 \
  --batch-size 92 --epochs 60 \
  --hidden-dim 512 --emb-dim 128 --no-one-hot --embed-mode concat \
  --family-members-k 4 \
  --lr 2e-4 --weight-decay 0.01 \
  --dropout 0.22 --rel-dropout-p 0.10 --label-smoothing 0.02 --focal-gamma 0.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.02 \
  --consistency-w 0.02 --supcon-w 0.08 --supcon-tau 0.10 --supcon-mode label+family \
  --proto-w 0.03 --proto-ema-m 0.99 \
  --delta-head --delta-w 0.00 --delta-pairs-per-family 2 \
  --reg-warmup-epochs 2 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.7 \
  --min-precision 0.50 --min-recall 0.50 \
  --calib-max-pos-delta 0.25 --calib-min-pos-frac 0.05 \
  --readout attn --clip-grad 2.0 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --seed 42 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"
_____________________________________________________________________________________

###########################################################
#### Training: hgt × gru ##################################
###########################################################

python 01_MPTCN_TTS_Devign.py \
  --stage fine-tune \
  --model mptcn_tts --spatial hgt --temporal gru \
  --Ls 2 --Lt 3 --heads 4 \
  --batch-size 192 --epochs 80 \
  --hidden-dim 512 --emb-dim 128 --no-one-hot --embed-mode concat \
  --family-members-k 4 \
  --lr 2e-4 --weight-decay 0.01 \
  --dropout 0.22 --label-smoothing 0.02 --focal-gamma 0.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.03 \
  --consistency-w 0.02 --supcon-w 0.05 --supcon-tau 0.08 \
  --proto-w 0.02 \
  --delta-head --delta-w 0.00 --delta-pairs-per-family 2 \
  --reg-warmup-epochs 4 \
  --tta 0 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.7 \
  --do-temperature --calib-beta 1.0 \
  --min-precision 0.50 --min-recall 0.50 \
  --calib-max-pos-delta 0.25 --calib-min-pos-frac 0.05 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --seed 42 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"



###########################################################
#### Training: hgt × tcn (maximum) ########################
###########################################################

python 01_MPTCN_TTS_Devign.py \
  --stage both \
  --do-contrastive \
  --pre-epochs 60 \
  --model mptcn_tts --spatial hgt --temporal tcn \
  --Ls 12 --Lt 1 --heads 4 \
  --batch-size 6 --accum-steps 8 --epochs 80 \
  --hidden-dim 768 --emb-dim 128 --no-one-hot --embed-mode concat \
  --family-members-k 4 \
  --lr 3e-4 --weight-decay 0.01 \
  --dropout 0.20 --label-smoothing 0.02 --focal-gamma 0.0 \
  --lambda-dom 0.0 \
  --train-feat-noise-std 0.01 --dropedge-p 0.03 \
  --consistency-w 0.02 --supcon-w 0.08 --supcon-tau 0.10 --supcon-mode label+family \
  --proto-w 0.03 --proto-ema-m 0.99 \
  --delta-head --delta-w 0.00 --delta-pairs-per-family 2 \
  --reg-warmup-epochs 3 \
  --T 1 --T-test 1 \
  --thr-ema-alpha 0.7 \
  --min-precision 0.50 --min-recall 0.50 \
  --calib-max-pos-delta 0.25 --calib-min-pos-frac 0.05 \
  --readout attn --row-norm --clip-grad 2.0 \
  --val-interval 1 \
  --num-workers 64 --eval-num-workers 64 \
  --prefetch-factor 2 --eval-prefetch-factor 2 \
  --persistent-workers --eval-persistent-workers \
  --mp-context forkserver \
  --no-audit \
  --seed 42 \
  --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
  --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
  --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
  --train-json-root "./Clean_exports/normalized_devign_graphson/train" \
  --val-json-root   "./Clean_exports/normalized_devign_graphson/valid" \
  --test-json-root  "./Clean_exports/normalized_devign_graphson/test" \
  --cache-dir "./Clean_exports/cache_devign"





------------------------------------------------------------------------------------------------------------------------



"""