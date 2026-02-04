"""
02_MPTCN_TTS_Devign.py

Cache-consumer runner for Devign-style vulnerability detection.
Loads pre-built PyG graphs from cache_manager.py output.

Key Features:
- Consumes pre-built cache (no GraphSON parsing)
- Supports cache-fused features (one-hot + embeddings)
- Family-aware mutant sampling
- Robust training with calibration

Prerequisites:
1. Run cache_manager.py to build cache first
2. Have vocabularies in place
3. Know your cache signature (16-hex)
"""

from __future__ import annotations

# ──────────────────────────────────────────────────────────────────────────────
# STANDARD LIBRARY
# ──────────────────────────────────────────────────────────────────────────────
import os
import sys
import hashlib
import csv
import json
import math
import time
import pickle
from datetime import datetime  # ← ADD THIS
import random
import warnings
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple
from collections import Counter, defaultdict
from dataclasses import dataclass
from types import SimpleNamespace
from tqdm import tqdm
import time

# ──────────────────────────────────────────────────────────────────────────────
# NUMPY & SCIPY
# ──────────────────────────────────────────────────────────────────────────────
import numpy as np

# ──────────────────────────────────────────────────────────────────────────────
# PYTORCH CORE
# ──────────────────────────────────────────────────────────────────────────────
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset as TorchDataset
from torch_geometric.utils import degree
# ──────────────────────────────────────────────────────────────────────────────
# PYTORCH GEOMETRIC
# ──────────────────────────────────────────────────────────────────────────────
from torch_geometric.data import Data, Batch
from torch_geometric.loader import DataLoader as GeoDataLoader
from torch_geometric.nn import (
    GCNConv,
    SAGEConv,
    GATConv,
    GINConv,
    PNAConv,
    RGCNConv,
    global_add_pool,
    global_max_pool,
    global_mean_pool,
)
from torch_geometric.nn.norm import BatchNorm


# Optional PyG modules (graceful degradation)
try:
    from torch_geometric.nn import GENConv, DeepGCNLayer
    HAS_DEEP = True
except ImportError:
    HAS_DEEP = False

try:
    from torch_geometric.nn import HGTConv
    HAS_HGT = True
except ImportError:
    HAS_HGT = False

try:
    from torch_geometric.nn import NNConv
    HAS_NNCONV = True
except ImportError:
    HAS_NNCONV = False

# ──────────────────────────────────────────────────────────────────────────────
# SKLEARN (metrics only)
# ──────────────────────────────────────────────────────────────────────────────
from sklearn.metrics import (
    accuracy_score,
    precision_recall_fscore_support,
    roc_auc_score,
    confusion_matrix,
)
print("[DevignDebug] Loaded 02_MPTCN_TTS_Devign.py (GGNN debug build v1)", flush=True)

# ──────────────────────────────────────────────────────────────────────────────
# PROGRESS BARS
# ──────────────────────────────────────────────────────────────────────────────
from tqdm import tqdm

# ──────────────────────────────────────────────────────────────────────────────
# AMP (AUTOMATIC MIXED PRECISION)
# ──────────────────────────────────────────────────────────────────────────────
from contextlib import nullcontext, contextmanager

try:
    from torch.cuda.amp import GradScaler as _CudaGradScaler, autocast as _cuda_autocast
except ImportError:
    _CudaGradScaler, _cuda_autocast = None, None

try:
    from torch import autocast as _torch_autocast
except ImportError:
    _torch_autocast = None

GradScaler = _CudaGradScaler

@contextmanager
def autocast_ctx(enabled: bool):
    """Unified autocast context for training."""
    if not enabled:
        yield
        return
    if _torch_autocast is not None:
        with _torch_autocast("cuda", enabled=True):
            yield
    elif _cuda_autocast is not None:
        with _cuda_autocast(enabled=True):
            yield
    else:
        yield



# ──────────────────────────────────────────────────────────────────────────────
# ENVIRONMENT SETUP
# ──────────────────────────────────────────────────────────────────────────────
os.environ.setdefault("PYTORCH_NVML_BASED_CUDA_CHECK", "0")
os.environ.setdefault("OMP_NUM_THREADS", "1")
os.environ.setdefault("MKL_NUM_THREADS", "1")
warnings.filterwarnings("ignore", message="Can't initialize NVML")

# ──────────────────────────────────────────────────────────────────────────────
# REPRODUCIBILITY
# ──────────────────────────────────────────────────────────────────────────────
def set_seed(seed: int = 42):
    """Set random seeds for reproducibility."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    try:
        torch.backends.cudnn.deterministic = True
        torch.backends.cudnn.benchmark = False
    except:
        pass



# ──────────────────────────────────────────────────────────────────────────────
# NOTES ON REMOVED IMPORTS
# ──────────────────────────────────────────────────────────────────────────────
"""
REMOVED (not needed for cache-consumer mode):
- from cache_manager import CacheConfig, CacheManager, CacheSignatureBuilder
  → Cache is pre-built, we only load .pt files directly
  
- sqlite3, hashlib (for CodeBERT)
  → Cache already has embedded features, no runtime embedding lookup
  
- from shared_text_norm import normalize_for_embedding, sha256_normalized
  → Not needed for consuming pre-built cache
  
- zipfile, filelock
  → Cache manager already handled these during build
  
- Complex GraphSON parsing utilities
  → Cache contains PyG Data objects, no parsing needed

KEPT:
- torch, torch_geometric (core ML)
- sklearn (metrics)
- json, csv (reading manifests and signatures)
- pathlib (file operations)
- numpy (numerical operations)
"""





# ──────────────────────────────────────────────────────────────────────────────
# DEBUG UTILITIES
# ──────────────────────────────────────────────────────────────────────────────

DEBUG_VERBOSE = True  # Set to False to silence debug

def _debug_classwise_probs(probs: np.ndarray, labels: np.ndarray, prefix: str = "VAL") -> None:
    """
    Print separate statistics for P(y=1) over positive and negative examples.

    This tells us whether the model actually ranks positives higher than negatives.
    """
    import numpy as np

    probs = np.asarray(probs, dtype=float)
    labels = np.asarray(labels, dtype=int)

    pos = probs[labels == 1]
    neg = probs[labels == 0]

    def _summ(name: str, arr: np.ndarray) -> str:
        if arr.size == 0:
            return f"{name}: N=0"
        return (
            f"{name}: N={arr.size} "
            f"mean={arr.mean():.6f} std={arr.std():.6f} "
            f"min={arr.min():.6f} max={arr.max():.6f}"
        )

    print(f"[{prefix}DBG] Class-wise probability stats")
    print(f"[{prefix}DBG] " + _summ("NEG (y=0)", neg))
    print(f"[{prefix}DBG] " + _summ("POS (y=1)", pos))


def _dbg(msg: str):
    """Debug print (can be disabled globally)."""
    if DEBUG_VERBOSE:
        print(msg, flush=True)

def _tstat(name: str, t: torch.Tensor):
    """Print tensor statistics."""
    try:
        t = t.detach()
        finite = torch.isfinite(t)
        print(f"[TSTAT][{name}] shape={tuple(t.shape)} "
              f"mean={float(t[finite].mean()):.6f} std={float(t[finite].std()):.6f} "
              f"min={float(t[finite].min()):.6f} max={float(t[finite].max()):.6f} "
              f"nonfinite={int((~finite).sum())}", flush=True)
    except Exception as e:
        print(f"[TSTAT][{name}] <stats failed: {e}>", flush=True)

def _npstat(name: str, a: np.ndarray):
    """Print numpy array statistics."""
    if a is None or a.size == 0:
        print(f"[NPSTAT][{name}] empty", flush=True)
        return
    a = a.astype(np.float64)
    print(f"[NPSTAT][{name}] N={a.size} mean={a.mean():.6f} std={a.std():.6f} "
          f"min={a.min():.6f} q50={np.quantile(a,0.50):.6f} max={a.max():.6f}", flush=True)

def clamp01_np(arr: np.ndarray) -> np.ndarray:
    """Clamp numpy array to [0, 1]."""
    return np.clip(arr.astype(np.float64), 0.0, 1.0)

def _dropedge_and_align_batch_(batch: Batch, p: float):
    """
    Drop edges with probability p and ensure all edge attributes stay aligned.
    Modifies batch in-place.
    """
    if p <= 0.0 or not hasattr(batch, "edge_index"):
        return
    
    ei = batch.edge_index
    if ei.size(1) == 0:
        return
    
    # Create mask
    device = ei.device
    mask = torch.rand(ei.size(1), device=device) >= float(p)
    
    # Apply to edge_index
    batch.edge_index = ei[:, mask]
    
    # Apply to all edge attributes
    for attr_name in ["edge_type", "edge_type_devign", "edge_attr"]:
        if hasattr(batch, attr_name):
            attr = getattr(batch, attr_name)
            if torch.is_tensor(attr) and attr.size(0) == mask.size(0):
                setattr(batch, attr_name, attr[mask])

def _ensure_aligned_ei_attrs(
    edge_index: torch.Tensor,
    edge_type: Optional[torch.Tensor] = None,
    edge_attr: Optional[torch.Tensor] = None
) -> Tuple[torch.Tensor, Optional[torch.Tensor], Optional[torch.Tensor]]:
    """
    Ensure edge_index, edge_type, and edge_attr have consistent sizes.
    Returns aligned versions.
    """
    if edge_index is None or edge_index.numel() == 0:
        return (
            torch.empty((2, 0), dtype=torch.long),
            None,
            None
        )
    
    num_edges = edge_index.size(1)
    
    # Align edge_type
    if edge_type is not None and torch.is_tensor(edge_type):
        if edge_type.size(0) != num_edges:
            _dbg(f"[WARN] edge_type size {edge_type.size(0)} != num_edges {num_edges}, truncating")
            edge_type = edge_type[:num_edges] if edge_type.size(0) > num_edges else None
    
    # Align edge_attr
    if edge_attr is not None and torch.is_tensor(edge_attr):
        if edge_attr.size(0) != num_edges:
            _dbg(f"[WARN] edge_attr size {edge_attr.size(0)} != num_edges {num_edges}, truncating")
            edge_attr = edge_attr[:num_edges] if edge_attr.size(0) > num_edges else None
    
    return edge_index, edge_type, edge_attr

# ────────────────────────────────────────────
# Devign layout helper (dirs) - ENHANCED
# ────────────────────────────────────────────
def _get_devign_layout(args):
    """
    Artifacts layout logic:
    1. If --output-dir is specified, use that EXACT path.
    2. If not, auto-generate a path based on model config + seed to prevent overwrites.
       Format: <script_dir>/MPTCN_TTS_devign/<model>_<dim>dim_<layers>L_seed<seed>/
    """
    import re
    from pathlib import Path
    
    # 1. Check for explicit output directory (Best for Ensembling/Experiments)
    explicit_out = getattr(args, "output_dir", None)
    
    if explicit_out:
        art_dir = Path(explicit_out).resolve()
    else:
        # 2. Auto-generate descriptive path
        root = Path(__file__).resolve().parent
        model_name = str(getattr(args, "model", "model")).lower()
        
        # Extract unique identifying features
        hidden = getattr(args, "hidden_dim", "X")
        layers = getattr(args, "layers", "X")
        seed   = getattr(args, "seed", "42")
        
        # Construct unique run ID: e.g., "devign_512dim_8L_seed100"
        run_id = f"{model_name}_{hidden}dim_{layers}L_seed{seed}"

        # Append legacy spatial tags if they exist
        def _san(v):
            if v is None: return ""
            v = str(v).lower()
            v = re.sub(r"[^a-z0-9_\-]+", "", v)
            return v
            
        spat = _san(getattr(args, "spatial", None))
        if spat: run_id += f"_{spat}"
        
        art_dir = root / "MPTCN_TTS_devign" / run_id

    # Define Subdirectories
    vocabs_dir  = art_dir / "vocab"
    ckpt_dir    = art_dir / "checkpoints"
    results_dir = art_dir / "results"

    # Create them
    for d in (vocabs_dir, ckpt_dir, results_dir):
        d.mkdir(parents=True, exist_ok=True)

    # Logging for verification
    print(f"[Layout] Artifacts directory: {art_dir}")

    return {
        "model_dir": art_dir,
        "vocab": vocabs_dir,
        "checkpoints": ckpt_dir,
        "results": results_dir,
    }
# ─────────────────────────────────────────────────────────────────────────────
# Fallback AttentionalAggregation if external flag is set (kept as-is)
# ─────────────────────────────────────────────────────────────────────────────
if 'HAS_ATT_AGGR' in globals() and not HAS_ATT_AGGR:
    class AttentionalAggregation(nn.Module):
        """Minimal fallback if torch_geometric.nn.aggr.AttentionalAggregation is unavailable."""
        def __init__(self, gate_nn: nn.Module):
            super().__init__()
            self.gate_nn = gate_nn
        def forward(self, x: torch.Tensor, index: torch.Tensor) -> torch.Tensor:
            device = x.device
            gate = self.gate_nn(x).squeeze(-1)
            gate = torch.nan_to_num(gate, nan=0.0)
            gate = gate - gate.max()
            w = torch.exp(gate)
            num_graphs = int(index.max().item()) + 1 if index.numel() else 1
            s = x.new_zeros(num_graphs, x.size(-1))
            z = x.new_zeros(num_graphs)
            s.index_add_(0, index, x * w.unsqueeze(-1))
            z.index_add_(0, index, w)
            z = z.clamp_min(1e-12).unsqueeze(-1)
            return s / z

# ─────────────────────────────────────────────────────────────────────────────
# PNA helpers
# ─────────────────────────────────────────────────────────────────────────────
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
    for batch in tqdm(loader, desc="PNA deg-hist (train)", disable=disable, total=len(loader)):
        ei = batch.edge_index
        num_nodes = int(batch.num_nodes)
        deg_src = torch.bincount(ei[0], minlength=num_nodes)
        deg_dst = torch.bincount(ei[1], minlength=num_nodes)
        deg = (deg_src + deg_dst).clamp_max(max_degree).long()  # undirected degree
        hist.scatter_add_(0, deg, torch.ones_like(deg, dtype=torch.float))
    hist[hist == 0] = 1.0
    return hist



def anti_collapse_loss(delta: torch.Tensor, target_std: float = 0.25) -> torch.Tensor:
    """
    Penalize batches where the std of delta logits is too low.
    delta: [N] tensor of (logit_1 - logit_0) or single-logit equivalents.
    """
    if delta is None or delta.numel() < 2:
        # zero loss if not enough samples
        return delta.new_tensor(0.0) if isinstance(delta, torch.Tensor) else torch.tensor(0.0)

    delta = delta.float()
    std = delta.std()
    # If std >= target_std → loss = 0; if std < target → positive penalty
    return F.relu(target_std - std)



def _debug_probs_classwise(tag: str, y: np.ndarray, p: np.ndarray):
    y = np.asarray(y, dtype=np.int64).ravel()
    p = np.asarray(p, dtype=np.float64).ravel()
    if y.size == 0 or p.size == 0 or y.size != p.size:
        return
    _dbg(f"[{tag}] Class-wise probability stats")
    for lab, name in [(0, "NEG"), (1, "POS")]:
        mask = (y == lab)
        if mask.any():
            v = p[mask]
            _dbg(
                f"[{tag}] {name} (y={lab}): N={v.size} "
                f"mean={float(v.mean()):.6f} std={float(v.std()):.6f} "
                f"min={float(v.min()):.6f} max={float(v.max()):.6f}"
            )


# ────────────────────────────────────────────
# Debug: inspect fused features from cache
# ────────────────────────────────────────────
def debug_fusion_snapshot(dataset, args, max_nodes: int = 3):
    """
    Print a small, human-readable view of fused features x = [type_onehot | code_emb].

    Assumes:
      • args._node_vocab_for_check is set (run() already does this)
      • dataset[i] returns a Data with .x and .y
    """
    import math
    import torch

    node_vocab = getattr(args, "_node_vocab_for_check", None)
    if node_vocab is None:
        print("[FusionDBG] args._node_vocab_for_check missing; cannot infer type_dim.")
        return

    type_dim = len(node_vocab)
    print("\n" + "=" * 70)
    print("[FusionDBG] Snapshot of fused features from CachedDataset")
    print("=" * 70)

    # Pick a couple of samples: first positive and first negative if possible
    pos_idx = None
    neg_idx = None
    for i, row in enumerate(dataset.rows):
        try:
            y = int(row.get("label", row.get("y", 0)))
        except Exception:
            y = 0
        if y == 1 and pos_idx is None:
            pos_idx = i
        if y == 0 and neg_idx is None:
            neg_idx = i
        if pos_idx is not None and neg_idx is not None:
            break

    indices = []
    if pos_idx is not None:
        indices.append(("POS", pos_idx))
    if neg_idx is not None and neg_idx != pos_idx:
        indices.append(("NEG", neg_idx))
    if not indices:
        indices.append(("ANY", 0))

    for tag, idx in indices:
        data = dataset[idx]
        x = getattr(data, "x", None)
        y = getattr(data, "y", None)
        if x is None:
            print(f"[FusionDBG] Sample {tag} idx={idx}: no .x found")
            continue

        if not torch.is_tensor(x):
            x = torch.as_tensor(x)

        x = x.float().cpu()
        N, D = x.size()
        code_dim = D - type_dim

        print(f"\n[FusionDBG] Sample {tag} idx={idx}")
        print(f"  label        : {int(y.item()) if isinstance(y, torch.Tensor) else y}")
        print(f"  x.shape      : {tuple(x.shape)} (N_nodes={N}, D={D})")
        print(f"  type_dim     : {type_dim}")
        print(f"  code_dim     : {code_dim}  (D - type_dim)")

        if code_dim <= 0:
            print("  [WARN] code_dim <= 0 → fusion may be misconfigured.")
            continue

        x_type = x[:, :type_dim]
        x_code = x[:, type_dim:]

        # Global stats
        def _stats(t, name):
            t_flat = t.reshape(-1)
            print(
                f"  [{name}] mean={t_flat.mean():.4f} "
                f"std={t_flat.std():.4f} "
                f"min={t_flat.min():.4f} "
                f"max={t_flat.max():.4f}"
            )

        _stats(x, "x_all")
        _stats(x_type, "x_type(0:V)")
        _stats(x_code, "x_code(V:)")

        # Finite checks
        if not torch.isfinite(x).all():
            print("  [FusionDBG][CRIT] x contains NaN/Inf!")
        else:
            print("  [FusionDBG] x is finite (no NaN/Inf detected).")

        # Print a few nodes (first K)
        K = min(max_nodes, N)
        print(f"  Showing first {K} nodes (shortened):")
        for n in range(K):
            xt = x_type[n]
            xc = x_code[n]
            typ_nz = (xt > 0).nonzero(as_tuple=False).view(-1)
            # Just first few dims from code part
            code_slice = xc[: min(8, code_dim)]
            print(f"    Node {n}:")
            print(f"      type_nonzero_indices  : {typ_nz.tolist()}")
            print(f"      code_first_dims (8max): [{', '.join(f'{v:.3f}' for v in code_slice.tolist())}]")

    print("=" * 70 + "\n")




# ────────────────────────────────────────────
# Debug: per-epoch parameter norm summary
# ────────────────────────────────────────────
def debug_param_norms(model, top_k: int = 5):
    """
    Print the top-k parameters by L2 norm.
    """
    import torch
    norms = []
    with torch.no_grad():
        for name, p in model.named_parameters():
            if p is None or p.data is None:
                continue
            n = p.data.norm().item()
            norms.append((n, name))
    if not norms:
        print("[ParamDBG] No parameters found.")
        return
    norms.sort(reverse=True, key=lambda x: x[0])
    print("\n[ParamDBG] Top parameter norms:")
    for n, name in norms[:top_k]:
        print(f"  {name:40s} | norm={n:.4f}")
    print()




class SoftF1Loss(nn.Module):
    """
    Soft F1 for *binary* classification, using the same binary-probability
    mapping as `_probs_from_logits_binary`.

    Handles logits of shape [B], [B,1] or [B,2].
    """
    def __init__(self, epsilon: float = 1e-7):
        super().__init__()
        self.epsilon = epsilon

    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        # targets: [B] or [B,1] → flatten to [B]
        targets = targets.float().view(-1)
        # shared helper (already defined later in the file)
        probs = _probs_from_logits_binary(logits).view(-1)

        # clip to [0,1] just in case of numerical noise
        probs = torch.clamp(probs, 0.0, 1.0)

        # Soft confusion-matrix components
        tp = (probs * targets).sum()
        fp = (probs * (1.0 - targets)).sum()
        fn = ((1.0 - probs) * targets).sum()

        precision = tp / (tp + fp + self.epsilon)
        recall    = tp / (tp + fn + self.epsilon)

        f1 = 2.0 * precision * recall / (precision + recall + self.epsilon)

        # Single scalar – optimizer minimizes 1 - F1
        return 1.0 - f1


import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import RGCNConv, global_sort_pool




# ─────────────────────────────────────────────────────────────────────────────
# Robust Devign-style architecture (EnhancedDevignNet)
# ─────────────────────────────────────────────────────────────────────────────

class RobustGatedFusion(nn.Module):
    """
    Gated fusion of [one-hot | code-embedding] with a small residual path.
    This assumes the first `one_hot_dim` features in x are type/one-hot,
    and the remaining are code embeddings.
    """
    def __init__(self, total_dim: int, hidden_dim: int, one_hot_dim: int):
        super().__init__()
        if total_dim < one_hot_dim:
            raise ValueError(f"total_dim={total_dim} < one_hot_dim={one_hot_dim}")
        self.one_hot_dim = int(one_hot_dim)
        self.emb_dim = int(total_dim - one_hot_dim)
        self.hidden_dim = int(hidden_dim)

        # Layer normalization for code embeddings
        self.code_norm = nn.LayerNorm(self.emb_dim)

        # Type (one-hot) projection
        self.proj_type = nn.Sequential(
            nn.Linear(self.one_hot_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
        )

        # Code embedding projection
        self.proj_code = nn.Sequential(
            nn.Linear(self.emb_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
        )

        # Gating network over [h_type | h_code]
        self.gate_net = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.GELU(),
            nn.Dropout(0.1),
            nn.Linear(hidden_dim, 1),
            nn.Sigmoid(),
        )

        # Residual projection on the *original* concatenated input [type|code]
        self.residual_proj = nn.Linear(total_dim, hidden_dim)

        # Debug flags (can be toggled from outside)
        self.debug_gate: bool = False
        self.debug_sleep: float = 0.0

        # Epoch-level alpha stats (aggregated over batches)
        self._alpha_stat_batches: int = 0
        self._alpha_stat_mean_sum: float = 0.0
        self._alpha_stat_std_sum: float = 0.0
        self._alpha_stat_min: float = float("inf")
        self._alpha_stat_max: float = 0.0

        self._init_weights()

    def _init_weights(self):
        # He init for linear layers; gate bias → 0 (i.e., sigmoid(0)=0.5)
        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.kaiming_normal_(m.weight, mode="fan_out", nonlinearity="relu")
                if m.bias is not None:
                    nn.init.constant_(m.bias, 0.0)

        last_linear = None
        for m in self.gate_net.modules():
            if isinstance(m, nn.Linear):
                last_linear = m
        if last_linear is not None and last_linear.bias is not None:
            with torch.no_grad():
                last_linear.bias.fill_(0.0)

    # -------- Epoch-level alpha stats API ---------------------------------
    def reset_epoch_alpha_stats(self):
        """Reset accumulated alpha stats (call at start of each epoch)."""
        self._alpha_stat_batches = 0
        self._alpha_stat_mean_sum = 0.0
        self._alpha_stat_std_sum = 0.0
        self._alpha_stat_min = float("inf")
        self._alpha_stat_max = 0.0

    def get_epoch_alpha_stats(self):
        """
        Return aggregated alpha stats for the current epoch, or None if
        no batches were seen.
        """
        if self._alpha_stat_batches == 0:
            return None
        mean = self._alpha_stat_mean_sum / self._alpha_stat_batches
        std = self._alpha_stat_std_sum / self._alpha_stat_batches
        return {
            "mean": float(mean),
            "std": float(std),
            "min": float(self._alpha_stat_min),
            "max": float(self._alpha_stat_max),
            "batches": int(self._alpha_stat_batches),
        }

    # ----------------------------------------------------------------------
    def forward(self, x: torch.Tensor, return_alpha: bool = False):
        """
        Forward pass.

        If return_alpha=True, returns (out, alpha) where:
          • out   = fused representation [N, hidden_dim]
          • alpha = gate values per node [N, 1]
        Otherwise returns out only.
        """
        expected_dim = self.one_hot_dim + self.emb_dim
        if x.size(1) != expected_dim:
            raise RuntimeError(
                f"RobustGatedFusion: expected dim {expected_dim}, got {x.size(1)}"
            )

        # Split features
        x_type = x[:, :self.one_hot_dim]
        x_code = x[:, self.one_hot_dim:]

        if torch.isnan(x).any() or torch.isinf(x).any():
            print("[GatedFusion] NaN/Inf in input!")
            raise ValueError("Invalid input to RobustGatedFusion")

        # Normalize code embeddings and project both streams
        x_code = self.code_norm(x_code)
        h_type = self.proj_type(x_type)
        h_code = self.proj_code(x_code)

        # Gate in [0,1]
        gate_input = torch.cat([h_type, h_code], dim=1)
        alpha = self.gate_net(gate_input)  # [N,1]

        # ---- accumulate epoch-level stats (train mode only) ---------------
        if self.training:
            with torch.no_grad():
                a = alpha.view(-1)
                m = a.mean().item()
                s = a.std().item()
                amin = a.min().item()
                amax = a.max().item()
                self._alpha_stat_batches += 1
                self._alpha_stat_mean_sum += m
                self._alpha_stat_std_sum += s
                self._alpha_stat_min = min(self._alpha_stat_min, amin)
                self._alpha_stat_max = max(self._alpha_stat_max, amax)

        # ── Gate debug (on-demand, for this batch) ─────────────────────────
        if getattr(self, "debug_gate", False):
            with torch.no_grad():
                a = alpha.view(-1)
                mean = a.mean().item()
                std = a.std().item()
                amin = a.min().item()
                amax = a.max().item()
                print(
                    f"[GatedFusionDBG] alpha: mean={mean:.4f} std={std:.4f} "
                    f"min={amin:.4f} max={amax:.4f} N={a.numel()}"
                )
                k = min(8, a.numel())
                vals = ", ".join(f"{v:.3f}" for v in a[:k].tolist())
                print(f"[GatedFusionDBG] alpha first {k}: [{vals}]")
                if float(getattr(self, "debug_sleep", 0.0) or 0.0) > 0.0:
                    import time
                    time.sleep(float(getattr(self, "debug_sleep", 0.0)))

        # Fused output + residual
        fused = alpha * h_code + (1.0 - alpha) * h_type
        residual = self.residual_proj(x)
        out = fused + 0.1 * residual  # small residual for gradient preservation

        # Occasional random debug of gate statistics
        if self.training and torch.rand(1).item() < 0.01:
            alpha_mean = alpha.mean().item()
            alpha_std = alpha.std().item()
            print(f"[GatedFusion] alpha mean={alpha_mean:.4f}, std={alpha_std:.4f}")
            if alpha_std < 1e-2:
                print("[GatedFusion] WARNING: gate is collapsing toward a constant.")

        if return_alpha:
            return out, alpha
        return out

    # ----------------------------------------------------------------------
    def gate_reg_loss(
        self,
        alpha: torch.Tensor,
        target_mean: float,
        min_std: float,
    ) -> torch.Tensor:
        """
        Numerically safe gate regularizer.

        • Encourages mean(alpha) ≈ target_mean (e.g. 0.4–0.5).
        • Encourages std(alpha) >= min_std (to avoid collapse).

        All NaNs/Infs are clamped away so this term can never poison
        the main loss with non-finite values.
        """
        # Flatten and ensure float32
        a = alpha.view(-1).float()
        if a.numel() == 0:
            return alpha.new_tensor(0.0)

        # Replace any NaNs/Infs in alpha itself
        a = torch.nan_to_num(a, nan=0.5, posinf=1.0, neginf=0.0)

        # Mean
        m = a.mean()

        # Variance with clamp to avoid negative / tiny values
        var = torch.mean((a - m) ** 2)
        var = torch.nan_to_num(var, nan=0.0, posinf=1.0, neginf=0.0)
        var = torch.clamp(var, min=1e-8, max=1e4)

        std = torch.sqrt(var)

        # Targets as floats (no grad through them)
        tm = float(target_mean)
        ms = float(min_std)

        # Mean penalty
        mean_term = (m - tm) ** 2

        # Std penalty only if std < ms
        std_gap = torch.relu(ms - std)
        std_term = std_gap * std_gap

        loss = mean_term + std_term
        loss = torch.nan_to_num(loss, nan=0.0, posinf=0.0, neginf=0.0)
        return loss



class RobustResRGCNLayer(nn.Module):
    """
    Residual RGCN layer:
      • LayerNorm pre-norm
      • GELU activation
      • Dropout
      • Learnable residual weight
    """
    def __init__(self, hidden_dim: int, num_relations: int, dropout: float = 0.2):
        super().__init__()
        self.conv = RGCNConv(
            hidden_dim,
            hidden_dim,
            num_relations=num_relations,
            aggr="mean",
            bias=True,
        )
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
        self.residual_weight = nn.Parameter(torch.tensor(0.5))

    def forward(self, x, edge_index, edge_type):
        # Pre-norm
        x_norm = self.norm(x)
        h = self.conv(x_norm, edge_index, edge_type)
        h = F.gelu(h)
        h = self.dropout(h)

        # Learnable residual mixing
        alpha = torch.sigmoid(self.residual_weight)
        out = alpha * x + (1.0 - alpha) * h

        # Occasional layer variance debug
        if self.training and torch.rand(1).item() < 0.005:
            h_std = h.std(dim=0, unbiased=False).mean().item()
            if h_std < 1e-4:
                print(f"[ResRGCN] WARNING: layer output variance very small: std={h_std:.6f}")
        return out


class EnhancedDevignNet(nn.Module):
    """
    Robust Devign-style model with:
      • [x | degree] input, where x = cache features (one-hot+code)
      • RobustGatedFusion over [one-hot | rest]
      • Stack of RobustResRGCNLayer
      • Learned layer-attention
      • mean+max pooling → MLP classifier
      • contrastive projection head ('proj') for SupCon
    """
    def __init__(
        self,
        input_dim: int,
        hidden_dim: int,
        num_layers: int = 6,
        num_relations: int = 5,
        num_node_tokens: int = 28,
        dropout: float = 0.2,
        num_classes: int = 2,
        max_degree: int = 100,
    ):
        super().__init__()

        self.hidden_dim = int(hidden_dim)
        self.num_layers = int(num_layers)
        self.num_relations = int(num_relations)
        self.dropout_p = float(dropout)
        self.num_classes = int(num_classes)
        self.max_degree = int(max_degree)
        self.num_node_tokens = int(num_node_tokens)

        # 3 degree features: in, out, total
        self.degree_dim = 3

        # Input: we take cache features of width `input_dim` and append 3-degree features
        self.input_proj = RobustGatedFusion(
            total_dim=int(input_dim) + self.degree_dim,
            hidden_dim=self.hidden_dim,
            one_hot_dim=self.num_node_tokens,
        )

        # Deep ResRGCN backbone
        self.layers = nn.ModuleList(
            [
                RobustResRGCNLayer(
                    hidden_dim=self.hidden_dim,
                    num_relations=self.num_relations,
                    dropout=self.dropout_p,
                )
                for _ in range(self.num_layers)
            ]
        )

        # Learnable layer-attention over per-layer outputs
        self.layer_attention = nn.Parameter(
            torch.ones(self.num_layers) / float(self.num_layers)
        )

        # Pre-transform before pooling
        self.pool_transform = nn.Linear(self.hidden_dim, self.hidden_dim)

        # Classifier head (2×hidden_dim because we concat mean+max)
        self.classifier = nn.Sequential(
            nn.Linear(self.hidden_dim * 2, 512),
            nn.LayerNorm(512),
            nn.GELU(),
            nn.Dropout(self.dropout_p),
            nn.Linear(512, 256),
            nn.LayerNorm(256),
            nn.GELU(),
            nn.Dropout(self.dropout_p),
            nn.Linear(256, self.num_classes),
        )

        # Contrastive projection head
        self.contrastive_head = nn.Sequential(
            nn.Linear(self.hidden_dim * 2, 256),
            nn.GELU(),
            nn.Linear(256, 128),
        )

        # Standard init for Linear + LayerNorm
        self.apply(self._init_weights)

    def _init_weights(self, module):
        if isinstance(module, nn.Linear):
            nn.init.xavier_uniform_(module.weight)
            if module.bias is not None:
                nn.init.constant_(module.bias, 0.0)
        elif isinstance(module, nn.LayerNorm):
            nn.init.constant_(module.bias, 0.0)
            nn.init.constant_(module.weight, 1.0)

    def compute_degree_features(self, edge_index: torch.Tensor, num_nodes: int) -> torch.Tensor:
        """
        Normalized degree features:
          • in_degree, out_degree, total_degree
          • log1p + clamp + scaling to [0,1]
        """
        device = edge_index.device

        # Handle no-edge graphs gracefully
        if edge_index.numel() == 0:
            return torch.zeros(num_nodes, self.degree_dim, device=device)

        row, col = edge_index

        # Uses torch_geometric.utils.degree imported at top
        out_degree = degree(row, num_nodes, dtype=torch.float32)
        in_degree = degree(col, num_nodes, dtype=torch.float32)
        total_degree = in_degree + out_degree

        max_deg = float(self.max_degree)

        # log1p + clamp, then normalize to [0,1]
        log_max = math.log1p(max_deg)
        log_max_total = math.log1p(2.0 * max_deg)

        out_degree = torch.log1p(out_degree).clamp(max=log_max) / log_max
        in_degree = torch.log1p(in_degree).clamp(max=log_max) / log_max
        total_degree = torch.log1p(total_degree).clamp(max=log_max_total) / log_max_total

        deg_features = torch.stack([in_degree, out_degree, total_degree], dim=1)
        return deg_features


    def forward(self, data):
        x = data.x.float()
        edge_index = data.edge_index
        edge_type = getattr(data, "edge_type", None)
        batch = getattr(data, "batch", None)

        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)

        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        else:
            edge_type = edge_type.long()
            if edge_type.max() >= self.num_relations:
                print(
                    f"[EnhancedDevignNet] edge_type.max()={int(edge_type.max())} "
                    f">= num_relations={self.num_relations} — clamping."
                )
                edge_type = edge_type.clamp(0, self.num_relations - 1)

        num_nodes = x.size(0)
        deg = self.compute_degree_features(edge_index, num_nodes)
        x_cat = torch.cat([x, deg], dim=1)

        if self.training and torch.rand(1).item() < 0.01:
            std_all = x_cat.std().item()
            std_deg = deg.std().item()
            print(f"[EnhancedDevignNet/Input] std_all={std_all:.4f}, std_deg={std_deg:.4f}")

        # 1) Input projection (get fused features AND alpha for regularizer)
        h, alpha = self.input_proj(x_cat, return_alpha=True)  # <-- CHANGED

        # 2) ResRGCN stack
        layer_outputs = []
        for i, layer in enumerate(self.layers):
            h = layer(h, edge_index, edge_type)
            layer_outputs.append(h)
            if self.training and torch.rand(1).item() < 0.005:
                m = h.mean().item()
                s = h.std(unbiased=False).item()
                print(f"[EnhancedDevignNet/Layer {i}] mean={m:.4f}, std={s:.4f}")

        # 3) Attention over layer outputs
        attn = F.softmax(self.layer_attention, dim=0)
        h_comb = torch.zeros_like(layer_outputs[0])
        for w, out_i in zip(attn, layer_outputs):
            h_comb = h_comb + w * out_i

        # 4) Graph pooling (mean + max)
        h_tr = self.pool_transform(h_comb)
        g_max = global_max_pool(h_tr, batch)
        g_mean = global_mean_pool(h_tr, batch)
        g = torch.cat([g_max, g_mean], dim=1)

        if self.training and torch.rand(1).item() < 0.01:
            gm = g.mean().item()
            gs = g.std(unbiased=False).item()
            print(f"[EnhancedDevignNet/Pool] mean={gm:.4f}, std={gs:.4f}")

        # 5) Classifier & contrastive head
        logits = self.classifier(g)
        proj = F.normalize(self.contrastive_head(g), dim=1)

        # match existing train loop interface: logits, emb, proj
        # NEW: also return alpha so train loop can regularize it
        return {"logits": logits, "emb": g, "proj": proj, "alpha": alpha}

class GradientMonitor:
    """
    Simple gradient monitor. Attach as `model.grad_monitor = GradientMonitor(model)`.
    """
    def __init__(self, model: nn.Module):
        self.model = model
        self.gradients = {}
        self.hooks = []
        for name, p in model.named_parameters():
            if p.requires_grad:
                handle = p.register_hook(lambda grad, n=name: self._save_grad(n, grad))
                self.hooks.append(handle)

    def _save_grad(self, name, grad):
        if grad is None:
            return
        self.gradients[name] = {
            "mean": float(grad.mean().item()),
            "std": float(grad.std().item()),
            "max": float(grad.max().item()),
            "min": float(grad.min().item()),
            "norm": float(grad.norm().item()),
        }

    def print_stats(self, top_k: int = 5):
        if not self.gradients:
            print("[GradMonitor] No gradients recorded yet.")
            return
        items = sorted(self.gradients.items(), key=lambda kv: kv[1]["norm"], reverse=True)
        print("=" * 60)
        print("[GradMonitor] Top gradient norms")
        for i, (name, stats) in enumerate(items[:top_k]):
            print(
                f"{i+1}. {name}: "
                f"norm={stats['norm']:.4f}, mean={stats['mean']:.4f}, std={stats['std']:.4f}"
            )
        vanishing = [n for n, s in self.gradients.items() if s["norm"] < 1e-7]
        exploding = [n for n, s in self.gradients.items() if s["norm"] > 100.0]
        if vanishing:
            print(f"[GradMonitor] Vanishing grads in {len(vanishing)} params (e.g., {vanishing[:5]})")
        if exploding:
            print(f"[GradMonitor] Exploding grads in {len(exploding)} params (e.g., {exploding[:5]})")
        print("=" * 60)

    def cleanup(self):
        for h in self.hooks:
            h.remove()
        self.hooks.clear()



# ─────────────────────────────────────────────────────────────────────────────
# DevignDataset — clean, cache-managed, SQLite CodeBERT attach (RAW-SHA)
# ─────────────────────────────────────────────────────────────────────────────

from torch.utils.data import Dataset
from torch_geometric.data import Data
from pathlib import Path
import csv
import re
from hashlib import sha256
from typing import Dict, Any, Optional

class DevignDataset(Dataset):
    """
    Thin wrapper around CacheManager - delegates all parsing to cache_manager.
    
    This dataset just:
    1. Reads manifest rows
    2. Calls cache_manager.get_or_build()
    3. Returns PyG Data objects
    
    NO duplicate parsing, NO duplicate feature building, NO duplicate embedding attachment.
    """
    def __init__(
        self,
        manifest_csv: str,
        json_root: str,
        cache_manager,  # CacheManager instance
        split_name: str = "train",
        transform=None,
    ):
        super().__init__()
        
        self.json_root = Path(json_root)
        self.cache_manager = cache_manager
        self.split_name = split_name
        self.transform = transform
        
        # Load manifest
        self.rows = []
        with open(manifest_csv, "r", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            for row in reader:
                self.rows.append(row)
        
        print(f"[{split_name}] Loaded {len(self.rows)} samples from {manifest_csv}")
    
    def __len__(self) -> int:
        return len(self.rows)
    
    def _generate_row_key(self, row: Dict[str, Any], graphson_path: Path) -> str:
        """
        Generate row key EXACTLY matching cache_manager.build_from_manifest logic.

        Pattern:
            func_id__snapshot__<sha8>

        In the current dataset:
            • snapshot = "export" for every graph (only export.json, no mutants).
        """
        # Try to reconstruct the same "rel" string cache_manager uses
        try:
            rel = graphson_path.relative_to(self.json_root).as_posix()
        except Exception:
            rel = graphson_path.as_posix()

        # 1) Identify function_id: prefer manifest, else derive from path
        func_id = (row.get("function_id") or row.get("func_id") or row.get("fid") or "").strip()
        if not func_id:
            # cache_manager regex: r"/([A-Za-z]*_?func_\d{6,})/"
            m = re.search(r"/([A-Za-z]*_?func_\d{6,})/", "/" + rel)
            if m:
                func_id = m.group(1)
            else:
                # final fallback: parent dir name
                func_id = graphson_path.parent.name or "func"

        # 2) Snapshot name from file stem
        #    In your current dataset (only export.json): snapshot == "export"
        snapshot = graphson_path.stem

        # 3) Compose collision-safe key and add short hash tail
        raw_key = f"{func_id}__{snapshot}"
        safe_key = re.sub(r"[^A-Za-z0-9_.-]+", "_", raw_key)
        hash_tail = sha256(raw_key.encode("utf-8")).hexdigest()[:8]
        row_key = f"{safe_key}__{hash_tail}"

        return row_key

    
    def __getitem__(self, idx: int) -> Data:
        row = self.rows[idx]
        
        # Resolve GraphSON path
        rel_path = (row.get("graph_json_path") or row.get("json_path", "")).strip().lstrip("/")
        if not rel_path.endswith(".json"):
            rel_path += ".json"
        
        graphson_path = self.json_root / rel_path
        
        if not graphson_path.exists():
            raise FileNotFoundError(f"GraphSON not found: {graphson_path}")
        
        # Generate row key (must match cache_manager logic exactly)
        row_key = self._generate_row_key(row, graphson_path)
        
        # Get label
        label = None
        label_str = row.get("label", row.get("target", ""))
        if label_str:
            try:
                label = int(label_str)
            except:
                pass
        
        # Get or build from cache (SINGLE SOURCE OF TRUTH)
        data = self.cache_manager.get_or_build(
            row_key=row_key,
            graphson_path=graphson_path,
            label=label,
            metadata={"split": self.split_name, "idx": idx}
        )
        
        if data is None:
            raise RuntimeError(f"Failed to build graph for {graphson_path}")
        
        # Apply transform if provided
        if self.transform is not None:
            data = self.transform(data)
        
        return data
    
    def get_statistics(self) -> Dict[str, Any]:
        """Get cache statistics."""
        return self.cache_manager.get_statistics()
# ─────────────────────────────────────────────────────────────────────────────
# Collate
# ─────────────────────────────────────────────────────────────────────────────
def graph_collate(batch: List[Data]) -> Batch:
    b = Batch.from_data_list(batch)
    b.num_graphs = len(batch)

    def _flat1(x):
        try: return x.view(-1) if x is not None else x
        except: return x

    for name in ("y","fid","t_idx","is_mutant","project_label","p_eq","sample_index"):
        if hasattr(b, name):
            setattr(b, name, _flat1(getattr(b, name)))

    if hasattr(b, "code_embeddings") and isinstance(b.code_embeddings, torch.Tensor):
        b.code_embeddings = b.code_embeddings.to(torch.float32)
    if hasattr(b, "code_embedding_mask") and isinstance(b.code_embedding_mask, torch.Tensor):
        b.code_embedding_mask = b.code_embedding_mask.to(torch.bool)
    return b


def ensure_vocabs(args, layout, train_ds=None):
    """
    Load vocabs produced by vocab_builder.py, with robust source resolution.

    Resolution priority for vocab_dir:
      1) args.vocab_dir (CLI override, e.g. /.../devign_vocab_normfunc_v2)
      2) layout['vocab'] (usual experiment-local copy)
      3) $DEVIGN_VOCAB_DIR env var (optional)

    Accepts both:
      • node_vocab.json / edge_vocab.json
      • node_type_vocab.json / edge_type_vocab.json   (older naming)
    """
    import os
    import json
    import pickle
    from pathlib import Path

    # 1) Resolve vocab_dir root
    cli_vocab_dir = getattr(args, "vocab_dir", "") or ""
    if cli_vocab_dir:
        vocab_dir = Path(cli_vocab_dir).expanduser().resolve()
    else:
        vocab_dir = Path(layout["vocab"]).expanduser().resolve()

    # Optional env override if the chosen dir is empty / missing
    if (not vocab_dir.exists()) or (not any(vocab_dir.glob("devign_rel_vocab.*"))):
        env_dir = os.environ.get("DEVIGN_VOCAB_DIR")
        if env_dir:
            candidate = Path(env_dir).expanduser().resolve()
            if candidate.exists():
                vocab_dir = candidate

    vocab_dir.mkdir(parents=True, exist_ok=True)

    # --- File names (with alias support) ---
    node_json = vocab_dir / "node_vocab.json"
    edge_json = vocab_dir / "edge_vocab.json"
    dev_json  = vocab_dir / "devign_rel_vocab.json"

    node_pkl  = vocab_dir / "node_vocab.pkl"
    edge_pkl  = vocab_dir / "edge_vocab.pkl"
    dev_pkl   = vocab_dir / "devign_rel_vocab.pkl"

    # Allow older names: node_type_vocab.json / edge_type_vocab.json
    def _alias(path: Path, aliases):
        if path.exists():
            return path
        for name in aliases:
            alt = path.with_name(name)
            if alt.exists():
                return alt
        return path  # fall back (may not exist)

    node_json = _alias(node_json, ["node_type_vocab.json"])
    edge_json = _alias(edge_json, ["edge_type_vocab.json"])

    def _ok(nv, ev, dv):
        if getattr(args, "allow_empty_vocabs", False):
            return True
        return (
            isinstance(nv, dict) and len(nv) > 0
            and isinstance(ev, dict) and len(ev) > 0
            and isinstance(dv, dict)
            and set(dv.keys()) >= {"AST", "CFG", "DFG_READ", "DFG_WRITE", "NCS"}
        )

    # --- Prefer PKL if present ---
    if node_pkl.exists() and edge_pkl.exists() and dev_pkl.exists():
        with open(node_pkl, "rb") as f:
            node_vocab = pickle.load(f)
        with open(edge_pkl, "rb") as f:
            edge_vocab = pickle.load(f)
        with open(dev_pkl, "rb") as f:
            devign_rel_vocab = pickle.load(f)

        if _ok(node_vocab, edge_vocab, devign_rel_vocab):
            print(
                f"[Vocab] Loaded (PKL) node={len(node_vocab)} "
                f"edge={len(edge_vocab)} devign_keys={sorted(devign_rel_vocab.keys())}"
            )
            return {
                "vocab_dir": vocab_dir,
                "node_vocab": node_vocab,
                "edge_vocab": edge_vocab,
                "devign_rel_vocab": devign_rel_vocab,
            }
        else:
            raise RuntimeError(
                "[Vocab] Invalid PKL vocabs — please regenerate with vocab_builder.py"
            )

    # --- Fallback to JSON ---
    if node_json.exists() and edge_json.exists() and dev_json.exists():
        with open(node_json, "r", encoding="utf-8") as f:
            node_vocab = json.load(f)
        with open(edge_json, "r", encoding="utf-8") as f:
            edge_vocab = json.load(f)
        with open(dev_json, "r", encoding="utf-8") as f:
            devign_rel_vocab = json.load(f)

        if _ok(node_vocab, edge_vocab, devign_rel_vocab):
            # persist PKL for faster reloads
            with open(node_pkl, "wb") as f:
                pickle.dump(node_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
            with open(edge_pkl, "wb") as f:
                pickle.dump(edge_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)
            with open(dev_pkl, "wb") as f:
                pickle.dump(devign_rel_vocab, f, protocol=pickle.HIGHEST_PROTOCOL)

            print(
                f"[Vocab] Loaded (JSON) node={len(node_vocab)} "
                f"edge={len(edge_vocab)} devign_keys={sorted(devign_rel_vocab.keys())}"
            )
            return {
                "vocab_dir": vocab_dir,
                "node_vocab": node_vocab,
                "edge_vocab": edge_vocab,
                "devign_rel_vocab": devign_rel_vocab,
            }
        else:
            raise RuntimeError(
                "[Vocab] Invalid JSON vocabs — please regenerate with vocab_builder.py"
            )

    # --- Nothing found ---
    raise FileNotFoundError(
        f"[Vocab] Missing vocabulary files in {vocab_dir}. "
        f"Run vocab_builder.py to create node_vocab.* / edge_vocab.* / devign_rel_vocab.* "
        f"or pass --vocab-dir pointing to the correct directory."
    )


# ─────────────────────────────────────────────────────────────────────────────
# Small helpers (used above, keep same signatures you already had)
# ─────────────────────────────────────────────────────────────────────────────
def _infer_family_id(s: str) -> str:
    s = (s or "").lower()
    m = re.search(r"(?:train_)?func_(\d+)", s)
    if m:
        g = int(m.group(1)); return f"func_{g:07d}"
    # fallback hash
    return f"func_{hashlib.md5(s.encode()).hexdigest()[:7]}"

def _infer_mut_type(s: str) -> str:
    s = (s or "").lower()
    if not s: return "orig"
    if s.endswith("export.json"): return "orig"
    return "snap"



# # ────────────────────────────────────────────
# # Probabilities / Calibration / Temperature
# # ────────────────────────────────────────────


def _probs_from_logits_binary(logits: torch.Tensor, T: float = 1.0) -> torch.Tensor:
    """
    FIXED VERSION: Convert logits to probabilities with validation.
    
    Critical fixes:
    1. Validates temperature > 0
    2. Checks for NaN/Inf
    3. Better handling of edge cases
    """
    # Validate temperature
    if T <= 0:
        print(f"⚠️ [probs_from_logits] Invalid temperature {T}, using 1.0")
        T = 1.0
    
    # Clamp temperature to reasonable range
    T = max(0.1, min(10.0, float(T)))
    
    # Check for NaN/Inf in input
    if torch.isnan(logits).any() or torch.isinf(logits).any():
        print("⚠️ [probs_from_logits] NaN/Inf in logits, cleaning...")
        logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0)
    
    # Handle different logit shapes
    if logits.dim() == 2 and logits.size(1) == 2:
        # Two-class output: use softmax
        # Apply temperature scaling
        scaled_logits = logits / T
        # Clamp to prevent overflow
        scaled_logits = scaled_logits.clamp(-50, 50)
        # Get probability of positive class
        p = F.softmax(scaled_logits, dim=1)[:, 1]
    elif logits.dim() == 2 and logits.size(1) == 1:
        # Single logit output: use sigmoid
        logits_flat = logits.view(-1)
        scaled_logits = logits_flat / T
        scaled_logits = scaled_logits.clamp(-50, 50)
        p = torch.sigmoid(scaled_logits)
    else:
        # Assume single logit per sample
        logits_flat = logits.view(-1)
        scaled_logits = logits_flat / T
        scaled_logits = scaled_logits.clamp(-50, 50)
        p = torch.sigmoid(scaled_logits)
    
    # Final validation
    p = p.view(-1)
    
    if torch.isnan(p).any():
        print("⚠️ [probs_from_logits] NaN in output probabilities!")
        p = torch.nan_to_num(p, nan=0.5)
    
    # Clamp to valid probability range
    p = p.clamp(1e-7, 1 - 1e-7)
    
    return p

def _pr_sweep(
    y_true: np.ndarray,
    y_prob: np.ndarray,
    beta: float,
    min_precision: Optional[float],
    min_recall: Optional[float] = None
) -> Tuple[float, Dict[str, float]]:
    """
    Helper function for threshold sweep - unchanged but included for completeness.
    """
    def _prf(y_true: np.ndarray, y_pred: np.ndarray, beta: float) -> Tuple[float, float, float]:
        """Calculate precision, recall, F-beta score."""
        from sklearn.metrics import precision_recall_fscore_support
        p, r, f, _ = precision_recall_fscore_support(
            y_true, y_pred, average="binary", beta=beta, zero_division=0
        )
        return float(p), float(r), float(f)
    
    y_true = y_true.astype(np.int64)
    y_prob = np.clip(y_prob.astype(np.float64), 0.0, 1.0)
    
    if y_prob.size == 0:
        return 0.5, {"f": 0.0, "p": 0.0, "r": 0.0, "thr": 0.5}
    
    # Create candidate thresholds
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
            best_any.update({"f": float(f), "p": float(p), "r": float(r), "thr": float(thr)})
        
        if (min_precision is not None) and (p < min_precision):
            continue
        if (min_recall is not None) and (r < min_recall):
            continue
        
        if f > best["f"]:
            best.update({"f": float(f), "p": float(p), "r": float(r), "thr": float(thr)})
    
    return (best_any if best["f"] < 0 else best)["thr"], (best_any if best["f"] < 0 else best)







from dataclasses import dataclass
from typing import Optional

@dataclass
class CalibConfig:
    """Configuration for threshold calibration."""
    beta: float = 1.0
    min_precision: Optional[float] = None
    min_recall: Optional[float] = None
    max_pos_rate_over_base: float = 3.0
    min_pos_frac: float = 0.01
    min_prob_std: float = 1e-3


def calibrate_threshold(
    y_true: np.ndarray,
    y_prob: np.ndarray,
    cfg: CalibConfig,
    base_rate: Optional[float] = None
) -> Tuple[float, Dict[str, float]]:
    """
    FIXED VERSION: Calibrate threshold with LOUD failure detection.
    
    Critical fix: Explicitly warns when model outputs are flat (not learning).
    """
    try:
        # Input validation
        y_true = np.asarray(y_true, dtype=np.int64)
        y_prob = np.asarray(y_prob, dtype=np.float64)
        
        if y_true.size == 0 or y_prob.size == 0:
            print("[Calib] Empty arrays, returning defaults")
            return 0.5, {"f": 0.0, "p": 0.0, "r": 0.0, "thr": 0.5, "base": 0.5}
        
        if y_true.size != y_prob.size:
            print(f"[Calib] Size mismatch: y_true={y_true.size}, y_prob={y_prob.size}")
            return 0.5, {"f": 0.0, "p": 0.0, "r": 0.0, "thr": 0.5, "base": 0.5}
        
        # Clean probabilities
        y_prob = np.clip(y_prob, 0.0, 1.0)
        
        # Compute base rate
        base = float(base_rate) if base_rate is not None else float((y_true == 1).mean())
        if not np.isfinite(base):
            base = 0.5
        base = float(np.clip(base, 0.001, 0.999))
        
        # CRITICAL FIX: Loud failure for flat probabilities
        prob_std = float(y_prob.std())
        min_prob_std = float(getattr(cfg, "min_prob_std", 1e-3))
        
        if prob_std < min_prob_std:
            print("=" * 80)
            print("🚨🚨🚨 [CRITICAL] MODEL COLLAPSE DETECTED! 🚨🚨🚨")
            print("=" * 80)
            print(f"Probability standard deviation: {prob_std:.6g}")
            print(f"Minimum acceptable: {min_prob_std:.6g}")
            print("")
            print("DIAGNOSIS:")
            print("  - The model is outputting nearly identical probabilities for all samples")
            print("  - This means the model is NOT learning")
            print("")
            print("LIKELY CAUSES:")
            print("  1. Learning rate too high (gradient explosion)")
            print("  2. Learning rate too low (no learning)")
            print("  3. Poor weight initialization")
            print("  4. Feature preprocessing issues (all features identical)")
            print("  5. Loss function bug")
            print("  6. Gradient vanishing in deep layers")
            print("")
            print("IMMEDIATE ACTIONS:")
            print("  1. Check if loss is decreasing")
            print("  2. Check gradient norms")
            print("  3. Verify input features have variation")
            print("  4. Try different learning rates (e.g., 1e-3, 1e-4, 1e-5)")
            print("  5. Check weight initialization")
            print("=" * 80)
            
            # Print some debug info
            print(f"\nDebug info:")
            print(f"  - Probability mean: {y_prob.mean():.6f}")
            print(f"  - Probability min: {y_prob.min():.6f}")
            print(f"  - Probability max: {y_prob.max():.6f}")
            print(f"  - Unique values: {len(np.unique(y_prob))}")
            print(f"  - Base rate: {base:.4f}")
            
            stats = {
                "f": 0.0,
                "p": 0.0,
                "r": 0.0,
                "thr": 0.5,
                "base": base,
                "prob_std": prob_std,
                "thr_raw": 0.5,
                "thr_used": 0.5,
                "pos_rate_raw": float((y_prob >= 0.5).mean()),
                "pos_rate_used": float((y_prob >= 0.5).mean()),
                "WARNING": "MODEL_COLLAPSED"
            }
            
            # Still return 0.5 to keep script running, but user is now aware
            print("\nReturning default threshold 0.5, but training has likely failed!")
            print("=" * 80)
            return 0.5, stats
        
        # Normal calibration continues...
        print(f"\n[Calib] Starting threshold calibration:")
        print(f"  - N samples: {y_prob.size}")
        print(f"  - Base rate: {base:.4f}")
        print(f"  - Prob mean: {y_prob.mean():.6f}")
        print(f"  - Prob std: {prob_std:.6f}")
        print(f"  - Prob range: [{y_prob.min():.6f}, {y_prob.max():.6f}]")
        
        # Sweep for best threshold
        try:
            result = _pr_sweep(
                y_true, y_prob, cfg.beta,
                cfg.min_precision,
                getattr(cfg, "min_recall", None)
            )
            
            if result is None or not isinstance(result, tuple) or len(result) != 2:
                raise ValueError(f"_pr_sweep returned invalid result: {result}")
            
            thr_raw, stats = result
            
            if not isinstance(thr_raw, (int, float)) or not np.isfinite(thr_raw):
                raise ValueError(f"Invalid threshold from _pr_sweep: {thr_raw}")
            
        except Exception as e:
            print(f"[Calib] _pr_sweep failed: {e}, using base-rate quantile")
            thr_raw = float(np.quantile(y_prob, 1.0 - base))
            stats = {"f": 0.0, "p": 0.0, "r": 0.0, "thr": thr_raw}
        
        # Apply constraints
        pos_rate_raw = float((y_prob >= thr_raw).mean())
        max_pos = float(min(1.0, cfg.max_pos_rate_over_base * max(1e-6, base)))
        min_pos = float(max(0.0, cfg.min_pos_frac))
        
        print(f"  - Raw threshold: {thr_raw:.6f}")
        print(f"  - Raw positive rate: {pos_rate_raw:.4f}")
        print(f"  - Max allowed pos rate: {max_pos:.4f}")
        print(f"  - Min required pos rate: {min_pos:.4f}")
        
        # Adjust threshold based on constraints
        thr = float(thr_raw)
        
        if pos_rate_raw > max_pos:
            try:
                thr = float(np.quantile(y_prob, 1.0 - max_pos))
                print(f"  - Adjusted to cap positive rate: {thr:.6f}")
            except Exception:
                thr = thr_raw
        elif pos_rate_raw < min_pos:
            try:
                thr = float(np.quantile(y_prob, 1.0 - min_pos))
                print(f"  - Adjusted to ensure minimum positives: {thr:.6f}")
            except Exception:
                thr = thr_raw
        
        # Final clamp
        thr = float(np.clip(thr, 1e-6, 1.0 - 1e-6))
        if not np.isfinite(thr):
            print("[Calib] Non-finite threshold after constraints, using 0.5")
            thr = 0.5
        
        # Final positive rate
        pos_rate_used = float((y_prob >= thr).mean())
        
        # Build output
        stats_out = {
            **stats,
            "thr_raw": float(thr_raw),
            "thr_used": float(thr),
            "pos_rate_raw": float(pos_rate_raw),
            "pos_rate_used": float(pos_rate_used),
            "base": float(base),
            "prob_std": prob_std,
        }
        
        print(f"\n[Calib] Final calibration results:")
        print(f"  - Raw threshold: {thr_raw:.6f}")
        print(f"  - Used threshold: {thr:.6f}")
        print(f"  - Positive rate (raw): {pos_rate_raw:.4f}")
        print(f"  - Positive rate (used): {pos_rate_used:.4f}")
        print(f"  - Base rate: {base:.4f}")
        
        # Warnings for extreme thresholds
        if thr >= 0.95:
            print(f"⚠️ [Calib] Very high threshold ({thr:.4f}) - may predict almost no positives")
        elif thr <= 0.05:
            print(f"⚠️ [Calib] Very low threshold ({thr:.4f}) - may predict almost all positives")
        
        return float(thr), stats_out
    
    except Exception as e:
        # Ultimate fallback
        print(f"[Calib][FATAL] Exception: {e}")
        import traceback
        traceback.print_exc()
        return 0.5, {"f": 0.0, "p": 0.0, "r": 0.0, "thr": 0.5, "base": 0.5, "error": str(e)}

# ────────────────────────────────────────────
# Losses
# ────────────────────────────────────────────
def focal_loss(
    logits: torch.Tensor,
    target: torch.Tensor,
    gamma: float = 2.0,
    pos_weight: float = 1.0,
    eps: float = 1e-6,
) -> torch.Tensor:
    """
    Numerically stable binary focal loss.

    Parameters
    ----------
    logits : Tensor
        Raw logits for P(y=1). Shape [N] or [N, 1].
    target : Tensor
        Binary labels {0,1}, shape [N].
    gamma : float
        Focusing parameter. gamma=0 => plain weighted BCE.
    pos_weight : float
        Positive-class weight, same semantics as BCEWithLogitsLoss(pos_weight).
    eps : float
        Numerical clamp for probabilities.
    """
    logits = logits.float()
    target = target.float()

    if logits.dim() > 1:
        logits = logits.squeeze(-1)

    # Sigmoid + clamp
    prob = torch.sigmoid(logits)
    prob = prob.clamp(min=eps, max=1.0 - eps)

    # Weighted BCE per-sample
    #   loss_i = - [ w * y log(p) + (1-y) log(1-p) ]
    loss_pos = -pos_weight * target * torch.log(prob)
    loss_neg = -(1.0 - target) * torch.log(1.0 - prob)
    bce = loss_pos + loss_neg  # [N]

    # Focal weight on p_t
    pt = prob * target + (1.0 - prob) * (1.0 - target)  # [N]
    focal_factor = (1.0 - pt).pow(gamma)

    loss = focal_factor * bce
    return loss.mean()


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
def _augment_batch_for_eval(
    b: Batch,
    dropedge_p: float = 0.0,
    feat_noise_std: float = 0.0,
    add_reverse_edges: bool = False,
    rev_rel_offset: int = 0,
):
    """
    FIXED VERSION: Augment batch for evaluation (TTA).
    
    Critical fix: Works on a clone to avoid corrupting the original batch.
    
    NOTE: Caller should pass b.clone() for TTA to avoid progressive corruption.
    This function will also validate parameters.
    """
    # Parameter validation
    if dropedge_p < 0.0 or dropedge_p > 1.0:
        raise ValueError(f"dropedge_p must be in [0,1], got {dropedge_p}")
    if feat_noise_std < 0.0:
        print(f"⚠️ Warning: feat_noise_std should be >= 0, got {feat_noise_std}")
    
    # Early return if no augmentation
    if dropedge_p == 0.0 and feat_noise_std == 0.0 and not add_reverse_edges:
        return b
    
    # Get edge index
    ei = b.edge_index
    if ei is None or ei.numel() == 0:
        # No edges, only apply feature noise if requested
        if feat_noise_std > 0.0 and torch.is_tensor(b.x):
            x = b.x.float() + torch.randn_like(b.x.float()) * float(feat_noise_std)
            b.x = x
        return b
    
    device = ei.device
    
    # Handle reverse edges
    if add_reverse_edges and ei.numel() > 0:
        ei_rev = torch.stack([ei[1], ei[0]], dim=0)
        ei = torch.cat([ei, ei_rev], dim=1)
        
        # Handle edge types - maintain consistency
        if hasattr(b, "edge_type") and torch.is_tensor(b.edge_type):
            et = b.edge_type.view(-1)
            et_rev = et + int(rev_rel_offset) if int(rev_rel_offset) > 0 else et
            et = torch.cat([et, et_rev], dim=0)
        else:
            et = None
        
        if hasattr(b, "edge_type_devign") and torch.is_tensor(b.edge_type_devign):
            etd = b.edge_type_devign.view(-1)
            etd_rev = etd + int(rev_rel_offset) if int(rev_rel_offset) > 0 else etd
            etd = torch.cat([etd, etd_rev], dim=0)
        else:
            etd = None
        
        if hasattr(b, "edge_attr") and torch.is_tensor(b.edge_attr):
            ea = torch.cat([b.edge_attr, b.edge_attr], dim=0)
        else:
            ea = None
    else:
        et = getattr(b, "edge_type", None)
        etd = getattr(b, "edge_type_devign", None)
        ea = getattr(b, "edge_attr", None)
    
    # Apply DropEdge
    if dropedge_p > 0.0 and ei.size(1) > 0:
        # Create mask for edges to keep
        mask = torch.rand(ei.size(1), device=device) >= float(dropedge_p)
        edges_before = ei.size(1)
        
        # Apply mask to all edge attributes
        ei = ei[:, mask]
        if et is not None:
            et = et[mask]
        if etd is not None:
            etd = etd[mask]
        if ea is not None:
            ea = ea[mask]
        
        edges_after = ei.size(1)
        # Debug: track edge dropping
        # print(f"[DropEdge] Kept {edges_after}/{edges_before} edges ({100*edges_after/edges_before:.1f}%)")
    
    # Apply feature noise
    x = b.x
    if feat_noise_std > 0.0 and torch.is_tensor(x):
        if not torch.is_floating_point(x):
            x = x.float()
        
        noise = torch.randn_like(x) * float(feat_noise_std)
        x = x + noise
        
        # Debug: track noise magnitude
        # noise_ratio = noise.abs().mean() / (x.abs().mean() + 1e-8)
        # print(f"[FeatNoise] Added noise with relative magnitude {noise_ratio:.4f}")
    
    # Update batch attributes
    # Note: This modifies the batch, so caller should pass a clone for safety
    b.edge_index = ei
    if et is not None:
        b.edge_type = et
    if etd is not None:
        b.edge_type_devign = etd
    if ea is not None:
        b.edge_attr = ea
    b.x = x
    
    return b


def _relation_dropout_inplace(b: Batch, p: float = 0.0) -> Batch:
    """
    Randomly drop a fraction of edges uniformly.
    Applies the SAME mask to edge_index, edge_attr, edge_type, and edge_type_devign.
    """
    if not hasattr(b, "edge_index") or not torch.is_tensor(b.edge_index):
        return b
    _dropedge_and_align_batch_(b, float(p))
    return b

# ────────────────────────────────────────────
# Threshold calibration via PR / F1 sweep
# ────────────────────────────────────────────
def _find_best_f1_threshold(y_true, p_pred, min_pos_frac: float = 0.01):
    """
    Given arrays of labels (0/1) and probabilities, sweep thresholds derived
    from the predicted scores and return the threshold that maximizes F1.

    min_pos_frac prevents degenerate thresholds that predict almost all
    examples as negative (very low pos_rate).
    """
    import numpy as np

    y = np.asarray(y_true, dtype=np.float32).ravel()
    p = np.asarray(p_pred, dtype=np.float32).ravel()
    if y.shape != p.shape:
        raise ValueError(f"Shape mismatch: y.shape={y.shape}, p.shape={p.shape}")

    n = y.shape[0]
    if n == 0:
        return 0.5, {"thr": 0.5, "f1": 0.0, "prec": 0.0, "rec": 0.0, "pos_rate": 0.0}

    # sort by descending probability
    order = np.argsort(-p)
    y_sorted = y[order]
    p_sorted = p[order]

    total_pos = float(y_sorted.sum())
    if total_pos <= 0.0:
        # no positives: F1 is always 0, any threshold equivalent → use 0.5
        return 0.5, {"thr": 0.5, "f1": 0.0, "prec": 0.0, "rec": 0.0, "pos_rate": 0.0}

    cumsum_pos = np.cumsum(y_sorted)
    idx = np.arange(1, n + 1, dtype=np.float32)

    tp = cumsum_pos
    fp = idx - tp
    fn = total_pos - tp

    prec = tp / np.maximum(tp + fp, 1e-9)
    rec  = tp / np.maximum(total_pos, 1e-9)
    f1   = 2.0 * prec * rec / np.maximum(prec + rec, 1e-9)
    pos_rate = idx / float(n)

    # avoid thresholds that predict almost nothing as positive
    mask = pos_rate >= float(min_pos_frac)
    if not np.any(mask):
        mask = slice(None)

    f1_masked = f1[mask]
    best_rel = int(np.argmax(f1_masked))

    if isinstance(mask, slice):
        best_idx = best_rel
    else:
        valid_indices = np.nonzero(mask)[0]
        best_idx = int(valid_indices[best_rel])

    best_thr = float(p_sorted[best_idx])

    stats = {
        "thr": best_thr,
        "f1": float(f1[best_idx]),
        "prec": float(prec[best_idx]),
        "rec": float(rec[best_idx]),
        "pos_rate": float(pos_rate[best_idx]),
    }
    return best_thr, stats

@torch.inference_mode()
def collect_probs_with_T(
    model,
    loader,
    device,
    T: float = 1.0,
    tta: int = 0,
    tta_dropedge_p: float = 0.0,
    tta_feat_noise_std: float = 0.0,
    args=None,
):
    """
    FIXED VERSION: Collect probabilities with temperature / TTA.
    
    Critical fixes:
    1. Renamed logits_acc to probs_acc for clarity
    2. Accumulate raw probabilities, divide once at end
    3. Added NaN validation
    4. Better debug output
    """
    import time
    
    model.eval()
    
    # Better debug output
    print(f"\n[COLLECT] Starting probability collection:")
    print(f"  - Temperature: {T}")
    print(f"  - TTA views: {int(tta)}")
    print(f"  - DropEdge p: {tta_dropedge_p}")
    print(f"  - Feature noise std: {tta_feat_noise_std}")
    
    y_all, p_all, proj_all = [], [], []
    no_prog = getattr(loader, "_no_progress", False)
    
    # Optional debug sleep
    debug_sleep = 0.0
    if args is not None:
        try:
            debug_sleep = float(getattr(args, "debug_sleep", 0.0) or 0.0)
        except Exception:
            debug_sleep = 0.0
    
    first_batch = True
    batch_count = 0
    
    for b in tqdm(loader, desc="Collect", disable=no_prog, total=len(loader)):
        batch_count += 1
        b = b.to(device, non_blocking=True)
        
        with torch.no_grad():
            # FIX: Better variable naming
            probs_acc = None  # Changed from logits_acc
            views = max(1, int(tta))
            
            for vi in range(views):
                # FIX: Clone batch for augmentation to avoid corruption
                bb = _augment_batch_for_eval(
                    b.clone() if tta > 0 else b,  # Clone for TTA
                    dropedge_p=float(tta_dropedge_p),
                    feat_noise_std=float(tta_feat_noise_std)
                )
                
                out = model(bb)
                logits = out["logits"] if isinstance(out, dict) else out
                
                # Clamp and convert to probabilities
                logits = torch.nan_to_num(
                    logits, nan=0.0, posinf=50.0, neginf=-50.0
                ).clamp_(-60, 60)
                
                probs = _probs_from_logits_binary(logits, T=float(T)).view(-1)
                
                # Debug on first view of first batch
                if first_batch and vi == 0:
                    print(f"[CollectDBG] Batch 1, View 1 stats:")
                    print(f"  - Logits shape: {tuple(logits.shape)}")
                    print(f"  - Probs mean: {float(probs.mean()):.6f}")
                    print(f"  - Probs std: {float(probs.std()):.6f}")
                    print(f"  - Probs range: [{float(probs.min()):.6f}, {float(probs.max()):.6f}]")
                
                # FIX: Accumulate raw probabilities (not pre-divided)
                if probs_acc is None:
                    probs_acc = probs.clone()  # Clone to avoid reference issues
                else:
                    probs_acc = probs_acc + probs  # Simple addition
            
            # FIX: Divide once at the end
            if views > 1:
                probs_final = probs_acc / float(views)
            else:
                probs_final = probs_acc
            
            probs_final = probs_final.detach().cpu()
            
            # Validation check
            if torch.isnan(probs_final).any():
                print(f"⚠️ [COLLECT] NaN detected in batch {batch_count}!")
                # Continue but track this
            
            # First batch comprehensive stats
            if first_batch:
                print(f"\n[COLLECT] First batch final stats:")
                print(f"  - N: {probs_final.numel()}")
                print(f"  - Mean: {float(probs_final.mean()):.6f}")
                print(f"  - Std: {float(probs_final.std()):.6f}")
                print(f"  - Min: {float(probs_final.min()):.6f}")
                print(f"  - Max: {float(probs_final.max()):.6f}")
                print(f"  - Unique values: {len(torch.unique(probs_final))}")
                
                # Critical check for flat probabilities
                if probs_final.std() < 1e-3:
                    print("🚨 [COLLECT] WARNING: Probabilities are nearly flat!")
                    print("    This indicates the model may not be learning.")
                
                if debug_sleep > 0.0:
                    print(f"[CollectDBG] Sleeping for {debug_sleep:.1f} seconds for inspection")
                    time.sleep(debug_sleep)
                
                first_batch = False
            
            # Collect labels
            y_all.append(b.y.view(-1).detach().cpu().numpy())
            p_all.append(probs_final.numpy())
            
            # Collect project IDs
            if hasattr(b, "project_label") and b.project_label is not None:
                proj = b.project_label.view(-1).detach().cpu().numpy()
            elif hasattr(b, "project_id") and b.project_id is not None:
                proj = b.project_id.view(-1).detach().cpu().numpy()
            else:
                proj = np.full_like(b.y.view(-1).detach().cpu().numpy(), fill_value=-1)
            proj_all.append(proj)
    
    # Concatenate all batches
    y_all = np.concatenate(y_all, axis=0) if len(y_all) else np.array([])
    p_all = np.concatenate(p_all, axis=0) if len(p_all) else np.array([])
    proj_all = np.concatenate(proj_all, axis=0) if len(proj_all) else None
    
    # Global statistics
    if p_all.size:
        print(f"\n[COLLECT] Global probability statistics:")
        print(f"  - Total samples: {p_all.size}")
        print(f"  - Mean: {float(p_all.mean()):.6f}")
        print(f"  - Std: {float(p_all.std()):.6f}")
        print(f"  - Range: [{float(p_all.min()):.6f}, {float(p_all.max()):.6f}]")
        
        # CRITICAL: Flatness check
        if p_all.std() < 1e-3:
            print("🚨🚨🚨 [COLLECT] CRITICAL: Model outputs are flat!")
            print(f"    Std deviation: {float(p_all.std()):.6g}")
            print("    The model is NOT learning properly!")
    
    if y_all.size:
        print(f"  - Positive rate in labels: {float((y_all == 1).mean()):.4f}")
    
    # Class-wise debug
    if y_all.size and p_all.size:
        try:
            neg_mask = (y_all == 0)
            pos_mask = (y_all == 1)
            
            if neg_mask.any():
                print(f"\n[COLLECT] Class 0 (negative) probabilities:")
                print(f"  - N: {int(neg_mask.sum())}")
                print(f"  - Mean: {float(p_all[neg_mask].mean()):.6f}")
                print(f"  - Std: {float(p_all[neg_mask].std()):.6f}")
                print(f"  - Range: [{float(p_all[neg_mask].min()):.6f}, {float(p_all[neg_mask].max()):.6f}]")
            
            if pos_mask.any():
                print(f"[COLLECT] Class 1 (positive) probabilities:")
                print(f"  - N: {int(pos_mask.sum())}")
                print(f"  - Mean: {float(p_all[pos_mask].mean()):.6f}")
                print(f"  - Std: {float(p_all[pos_mask].std()):.6f}")
                print(f"  - Range: [{float(p_all[pos_mask].min()):.6f}, {float(p_all[pos_mask].max()):.6f}]")
            
            # Check if positive class has higher average probability (good sign)
            if neg_mask.any() and pos_mask.any():
                pos_mean = float(p_all[pos_mask].mean())
                neg_mean = float(p_all[neg_mask].mean())
                if pos_mean > neg_mean:
                    print(f"✅ Good: Positive class has higher avg probability ({pos_mean:.4f} > {neg_mean:.4f})")
                else:
                    print(f"⚠️ Warning: Negative class has higher avg probability ({neg_mean:.4f} >= {pos_mean:.4f})")
        except Exception as e:
            print(f"[COLLECT] Could not compute class-wise stats: {e}")
    
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
    threshold_map: dict | None = None,
    epoch: Optional[int] = None,  # ✅ NEW: For probability monitoring
) -> Dict[str, Any]:
    """
    Evaluates the binary head consistently using _probs_from_logits_binary.
    FIXED: Removed boolean tensor crash and dead project-head logic.
    ADDED: Real-time probability distribution monitoring.
    """
    model.eval()

    # ---------- config ----------
    T = float(temperature) if (temperature is not None and np.isfinite(temperature) and temperature > 0.0) else 1.0
    T = max(0.1, min(10.0, T))
    disable = getattr(loader, "_no_progress", True)
    _dbg(f"[EVAL] T={T} thr={float(threshold):.6f} thr_map={'yes' if threshold_map else 'no'} tta={int(tta)}")

    # ---------- collectors ----------
    y_true: List[int] = []
    prob_list: List[torch.Tensor] = []
    proj_labels_all: List[int] = []
    
    first_batch = True

    # ---------- loop ----------
    for batch in tqdm(loader, desc="Evaluate", disable=disable, total=len(loader)):
        b = batch.to(device, non_blocking=True)

        if tta and tta > 0:
            acc_main = 0.0
            
            for vi in range(int(tta)):
                bb = _augment_batch_for_eval(b, tta_dropedge_p, tta_feat_noise_std)
                out = model(bb)

                # main head
                logits = out["logits"] if isinstance(out, dict) else out
                logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                p1 = _probs_from_logits_binary(logits, T=T).view(-1)
                acc_main += p1.detach().cpu()

                if first_batch and vi == 0:
                    _dbg(f"[EvalDBG] logits.shape={tuple(logits.shape)} → "
                         f"p.mean={float(p1.mean()):.6f} std={float(p1.std()):.6f}")

            p1 = (acc_main / float(tta))
            prob_list.append(p1)

        else:
            out = model(b)
            logits = out["logits"] if isinstance(out, dict) else out
            logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
            p1 = _probs_from_logits_binary(logits, T=T).detach().cpu().view(-1)
            prob_list.append(p1)

            if first_batch:
                _dbg(
                    f"[EvalDBG] logits.shape={tuple(logits.shape)} → "
                    f"p.mean={float(p1.mean()):.6f} std={float(p1.std()):.6f} "
                    f"min={float(p1.min()):.6f} max={float(p1.max()):.6f}"
                )
                first_batch = False

        # labels
        y_true.extend(b.y.view(-1).detach().cpu().tolist())

        # --- CRITICAL FIX: Safe Project Label Retrieval ---
        pl = getattr(b, "project_label", None)
        if pl is None:
            pl = getattr(b, "project_id", None)
            
        if pl is not None:
            proj_labels_all.extend(pl.view(-1).detach().cpu().tolist())
        else:
            proj_labels_all.extend([-1] * p1.numel())

    # ---------- main task metrics ----------
    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = (np.asarray(torch.cat(prob_list).numpy(), dtype=np.float32) if prob_list else np.empty((0,), dtype=np.float32))
    y_prob = clamp01_np(y_prob)

    # ---------- NEW: Real-time probability monitoring ----------
    if epoch is not None and y_true.size > 0 and y_prob.size > 0:
        pos_mask = y_true == 1
        neg_mask = y_true == 0
        if pos_mask.any() and neg_mask.any():
            mean_prob = y_prob.mean()
            pos_prob = y_prob[pos_mask].mean()
            neg_prob = y_prob[neg_mask].mean()
            gap = pos_prob - neg_prob
            print(f"\n[Epoch {epoch}] Val Mean Prob: {mean_prob:.3f} | Pos-Prob: {pos_prob:.3f} | Neg-Prob: {neg_prob:.3f} | Gap: {gap:.3f}\n")

    # ---------- debug ----------
    if y_true.size and y_prob.size:
        try:
            _debug_classwise_probs(y_prob, y_true, prefix="EVAL")
        except Exception as e:
            _dbg(f"[EvalDBG] class-wise prob debug failed: {e}")

    # ---------- binarize with optional per-project thresholds ----------
    proj_labels_all = np.asarray(proj_labels_all, dtype=np.int64)
    
    if threshold_map and proj_labels_all.size == y_prob.size:
        thr_vec = np.full_like(y_prob, fill_value=float(threshold), dtype=np.float32)

        for pid, thr in threshold_map.items():
            mask = (proj_labels_all == int(pid))
            if mask.any():
                thr_vec[mask] = float(thr)
        y_pred = (y_prob >= thr_vec).astype(np.int64)
    else:
        y_pred = (y_prob >= float(threshold)).astype(np.int64)

    # ---------- compute metrics ----------
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

    # ---------- per-project breakdown ----------
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

    return result




from torch.utils.data import BatchSampler
import torch

class FamilyBatchSampler(BatchSampler):
    """
    Yields batches where each batch consists of `num_families_per_batch` families,
    with `num_members_per_family` samples per family (sampled with replacement).
    Ensures balanced family representation while maintaining reproducibility.
    """
    def __init__(self, manifest_rows, batch_size: int, num_members_per_family: int, seed: int = 42, drop_last: bool = False):
        self.rows = manifest_rows
        self.batch_size = int(batch_size)
        self.k = int(max(1, num_members_per_family))
        self.families_per_batch = max(1, self.batch_size // self.k)
        self.drop_last = bool(drop_last)
        self.g = torch.Generator().manual_seed(int(seed))

        # Build family index map
        self.by_family = {}
        for i, r in enumerate(self.rows):
            fam = r.get("family_id", f"__unknown_{i}__")
            self.by_family.setdefault(fam, []).append(i)
        
        self.family_ids = list(self.by_family.keys())
        
        # Calculate batches per epoch
        n = len(self.rows)
        self.num_batches = (n // self.batch_size) if drop_last else ((n + self.batch_size - 1) // self.batch_size)
        
        print(f"[BatchSampler] families={len(self.family_ids)} | k={self.k} | families_per_batch={self.families_per_batch} | batches/epoch={self.num_batches}")

    def __iter__(self):
        if not self.family_ids:
            return
        
        for _ in range(self.num_batches):
            # Sample families uniformly
            fam_idx = torch.randint(0, len(self.family_ids), (self.families_per_batch,), generator=self.g).tolist()
            batch = []
            
            # Sample K members from each family (with replacement)
            for fi in fam_idx:
                members = self.by_family[self.family_ids[fi]]
                if not members: 
                    continue
                pick = torch.randint(0, len(members), (self.k,), generator=self.g).tolist()
                batch.extend(members[i] for i in pick)
            
            # Trim or pad to exact batch size
            if len(batch) >= self.batch_size:
                yield batch[:self.batch_size]
            elif not self.drop_last and len(batch) > 0:
                # Pad with random samples from entire dataset
                remain = self.batch_size - len(batch)
                extra = torch.randint(0, len(self.rows), (remain,), generator=self.g).tolist()
                batch.extend(extra)
                yield batch

    def __len__(self):
        return self.num_batches

# ─────────────────────────────────────────────────────────────
# Self-paced / curriculum family batch sampler (static easy→hard)
# ─────────────────────────────────────────────────────────────
class SelfPacedFamilyBatchSampler(torch.utils.data.Sampler):
    """
    Self-paced sampler over families.

    • Groups rows by family_id (fid / family_id / function_id).
    • Assigns each family a 'difficulty' (by nodes/edges if present, else 1).
    • At epoch 0 uses start_frac of easiest families; linearly increases to
      end_frac by final epoch.
    """

    def __init__(
        self,
        rows,
        batch_size: int,
        num_members_per_family: int = 1,
        num_epochs: int = 1,
        start_frac: float = 0.3,
        end_frac: float = 1.0,
        seed: int = 42,
        drop_last: bool = True,
    ):
        super().__init__(None)
        self.rows = list(rows)
        self.batch_size = int(batch_size)
        self.k = int(num_members_per_family)
        self.num_epochs = max(1, int(num_epochs))
        self.start_frac = float(start_frac)
        self.end_frac = float(end_frac)
        self.drop_last = bool(drop_last)

        self.current_epoch = 0
        self._rng = random.Random(seed)

        # Build families
        fam_to_indices: Dict[Any, List[int]] = {}
        fam_to_difficulty: Dict[Any, float] = {}

        for idx, row in enumerate(self.rows):
            fam_id = self._get_family_id(row, idx)
            diff = self._get_difficulty(row)

            fam_to_indices.setdefault(fam_id, []).append(idx)
            # accumulate difficulty (we'll average later)
            fam_to_difficulty[fam_id] = fam_to_difficulty.get(fam_id, 0.0) + float(diff)

        # Average difficulty per family
        families = []
        for fam_id, indices in fam_to_indices.items():
            mean_diff = fam_to_difficulty[fam_id] / max(1, len(indices))
            families.append((fam_id, indices, mean_diff))

        # Sort by difficulty: easiest → hardest
        families.sort(key=lambda t: t[2])
        self._families = families

    @staticmethod
    def _get_family_id(row, idx: int):
        # Try dict-style first
        if isinstance(row, dict):
            for key in ("family_id", "fid", "function_id", "index"):
                if key in row:
                    return row[key]
            return idx
        # Then attribute-style
        for attr in ("family_id", "fid", "function_id", "index"):
            if hasattr(row, attr):
                return getattr(row, attr)
        return idx

    @staticmethod
    def _get_difficulty(row):
        """
        Heuristic difficulty: prefer nodes/edges if present,
        otherwise constant (degenerates to uniform sampling).
        """
        if isinstance(row, dict):
            n = row.get("nodes", None)
            e = row.get("edges", None)
        else:
            n = getattr(row, "nodes", None)
            e = getattr(row, "edges", None)

        if n is not None and e is not None:
            return float(n) + 0.1 * float(e)
        if n is not None:
            return float(n)
        if e is not None:
            return float(e)
        return 1.0

    def set_epoch(self, epoch: int):
        self.current_epoch = max(0, int(epoch))

    def __len__(self) -> int:
        # approximate batches per epoch
        total_graphs = sum(len(f[1]) for f in self._families)
        return max(1, total_graphs // max(1, self.batch_size))

    def __iter__(self):
        # fraction of families to use at this epoch
        t = min(1.0, self.current_epoch / max(1, self.num_epochs - 1))
        frac = self.start_frac + t * (self.end_frac - self.start_frac)
        frac = float(min(1.0, max(0.0, frac)))

        num_families = len(self._families)
        num_active = max(1, int(round(frac * num_families)))

        active_families = self._families[:num_active]
        fam_indices = list(range(len(active_families)))
        self._rng.shuffle(fam_indices)

        batch: List[int] = []

        for fam_idx in fam_indices:
            _, idxs, _ = active_families[fam_idx]
            # sample up to k members from this family (with replacement if needed)
            if len(idxs) >= self.k:
                chosen = self._rng.sample(idxs, self.k)
            else:
                chosen = [self._rng.choice(idxs) for _ in range(self.k)]
            batch.extend(chosen)

            if len(batch) >= self.batch_size:
                yield batch[: self.batch_size]
                batch = []

        if batch and not self.drop_last:
            yield batch



def _ensure_aligned_ei_attrs(ei: torch.Tensor,
                             *attrs: Optional[torch.Tensor]) -> tuple[torch.Tensor, ...]:
    """
    Returns a tuple (ei, *aligned_attrs) where each attr is truncated to the same
    number of edges as edge_index. Non-tensor attrs are passed through.

    SAFETY: if lengths mismatch, we warn once; set ENV DEVIGN_STRICT_EALIGN=1 to raise.
    """
    import os
    if not (torch.is_tensor(ei) and ei.dim() == 2):
        return (ei, *attrs)
    E = int(ei.size(1))
    out = [ei]
    for a in attrs:
        if torch.is_tensor(a):
            a = a.view(-1)
            if int(a.numel()) != E:
                # warn once
                if not getattr(_ensure_aligned_ei_attrs, "_warned", False):
                    print(f"[Align][WARN] edge_index has {E} edges but an attr has {int(a.numel())}; truncating to match. "
                          f"Set DEVIGN_STRICT_EALIGN=1 to raise.", flush=True)
                    _ensure_aligned_ei_attrs._warned = True
                if os.environ.get("DEVIGN_STRICT_EALIGN", "0") == "1":
                    raise RuntimeError(f"Edge attribute length {int(a.numel())} != E={E}")
                a = a[:E]
        out.append(a)
    return tuple(out)


def _dropedge_and_align_batch_(b, p: float) -> None:
    """
    In-place DropEdge that applies the SAME mask to:
      - edge_index
      - edge_attr (if present)
      - edge_type (if present)
      - edge_type_devign (if present)
    Then hard-aligns lengths.
    """
    p = float(p)
    if p <= 0.0 or not hasattr(b, "edge_index") or not torch.is_tensor(b.edge_index) or b.edge_index.numel() == 0:
        # still enforce alignment if something came in mismatched
        if hasattr(b, "edge_index"):
            b.edge_index, b.edge_type, b.edge_attr = _ensure_aligned_ei_attrs(
                b.edge_index, getattr(b, "edge_type", None), getattr(b, "edge_attr", None)
            )
            # align devign separately (it may exist without edge_type)
            _, et_dev = _ensure_aligned_ei_attrs(b.edge_index, getattr(b, "edge_type_devign", None))
            if torch.is_tensor(et_dev):
                b.edge_type_devign = et_dev
        return

    ei = b.edge_index
    E = int(ei.size(1))
    keep = (torch.rand(E, device=ei.device) >= p)
    if keep.sum().item() == E:
        # no edges dropped but still align all attrs
        b.edge_index, b.edge_type, b.edge_attr = _ensure_aligned_ei_attrs(
            b.edge_index, getattr(b, "edge_type", None), getattr(b, "edge_attr", None)
        )
        _, et_dev = _ensure_aligned_ei_attrs(b.edge_index, getattr(b, "edge_type_devign", None))
        if torch.is_tensor(et_dev):
            b.edge_type_devign = et_dev
        return

    b.edge_index = ei[:, keep]
    if hasattr(b, "edge_attr") and torch.is_tensor(b.edge_attr) and b.edge_attr.size(0) == E:
        b.edge_attr = b.edge_attr[keep]
    if hasattr(b, "edge_type") and torch.is_tensor(b.edge_type) and b.edge_type.numel() == E:
        b.edge_type = b.edge_type[keep]
    if hasattr(b, "edge_type_devign") and torch.is_tensor(b.edge_type_devign) and b.edge_type_devign.numel() == E:
        b.edge_type_devign = b.edge_type_devign[keep]

    # final hard alignment
    b.edge_index, b.edge_type, b.edge_attr = _ensure_aligned_ei_attrs(
        b.edge_index, getattr(b, "edge_type", None), getattr(b, "edge_attr", None)
    )
    _, et_dev = _ensure_aligned_ei_attrs(b.edge_index, getattr(b, "edge_type_devign", None))
    if torch.is_tensor(et_dev):
        b.edge_type_devign = et_dev


# ────────────────────────────────────────────────────────────────────────────────
# NodeFeatureWrapper - FIXED VERSION
#   • Correctly builds per-node features without silent dropping
#   • Robust feature fusion: x_dense + log1p(in/out) [+ Code(text)] [+ TypeEmbedding(type)]
#   • Projects to hidden_dim and delegates to base GNN model
#   • Handles batched PyG lists and partial/missing fields safely
# ────────────────────────────────────────────────────────────────────────────────
class NodeFeatureWrapper(nn.Module):
    _PRINT_ONCE_FLAGS: Dict[str, bool] = {}

    def __init__(
        self,
        base_model: nn.Module,
        raw_feature_dim: int,
        num_tokens: int,
        args,
    ):
        super().__init__()
        self.base_model = base_model
        self._base_name = type(base_model).__name__

        # ---- config
        self.hidden_dim = int(getattr(args, "hidden_dim", 256))
        # Code embedding fusion mode (for precomputed embeddings on Data)
        # none|concat|replace
        self.code_mode = str(getattr(args, "code_mode", "none")).lower()

        # Type embedding (optional)
        self.embed_mode = str(getattr(args, "embed_mode", "none")).lower()  # none|concat|replace
        self.emb_dim    = int(getattr(args, "emb_dim", 64))
        self.input_emb: Optional[nn.Embedding] = None
        if self.embed_mode in ("concat", "replace"):
            self.input_emb = nn.Embedding(int(num_tokens), self.emb_dim)
            print(f"[Wrapper][{self._base_name}] Attached nn.Embedding (mode={self.embed_mode})")

        # Projection to the base model's working width
        self.input_proj = nn.LazyLinear(self.hidden_dim)

        # Debug
        self._dbg_embed       = bool(getattr(args, "debug_embed", False))
        self._dbg_emit_every  = 0  # 0 => print only once
        self._dbg_seen        = 0
        self._ids_warned_once = False

    # ---------- small helper to canonicalize mixed text payloads ----------
    @staticmethod
    def _canon_text(x: Any) -> str:
        if x is None:
            return ""
        if isinstance(x, (list, tuple)):
            flat: List[str] = []
            stack = list(x)
            while stack:
                y = stack.pop(0)
                if isinstance(y, (list, tuple)):
                    stack[:0] = list(y)
                elif y is not None:
                    s = str(y).strip()
                    if s:
                        flat.append(s)
            return " ".join(flat)
        if isinstance(x, dict):
            try:
                import json
                return json.dumps(x, sort_keys=True)
            except Exception:
                return str(x)
        return str(x).strip()

    @classmethod
    def _print_once(cls, key: str, msg: str):
        if not cls._PRINT_ONCE_FLAGS.get(key, False):
            print(msg, flush=True)
            cls._PRINT_ONCE_FLAGS[key] = True

   # ------------------------------- forward ------------------------------------
    def forward(self, data: Data):
        """
        CACHE-AWARE FEATURE HANDLING:
        - If cache_manager already fused features → just project to hidden_dim
        - Otherwise → rebuild features (legacy path for non-cached data)
        """
        dev = data.x.device
        x_input = data.x.float().to(dev, non_blocking=True)
        N = x_input.size(0)

        # ✅ CHECK: Did cache_manager already fuse features?
        already_fused = bool(getattr(data, "_cache_fused", False))
        
        if already_fused:
            # Cache-fused path: features are ALREADY complete
            # Just project to hidden_dim for model compatibility
            if not getattr(self, "_printed_cache_fused_once", False):
                print(f"[Wrapper] Cache-fused input detected: x.shape={tuple(x_input.shape)} → hidden_dim={self.hidden_dim}", flush=True)
                self._printed_cache_fused_once = True
            
            # Simple projection - no feature reconstruction
            data.x = self.input_proj(x_input)
            return self.base_model(data)

        # ─────────────────────────────────────────────────────────
        # LEGACY PATH: Non-cached data (rebuild features)
        # ─────────────────────────────────────────────────────────
        
        # 1) Dense from parser (raw)
        x_dense = x_input
        
        # 2) Degree features
        ei = getattr(data, "edge_index", None)
        if ei is None or ei.numel() == 0:
            deg_in = torch.zeros(N, device=dev)
            deg_out = torch.zeros(N, device=dev)
        else:
            ei0 = ei[0].to(dev, non_blocking=True).long()
            ei1 = ei[1].to(dev, non_blocking=True).long()
            deg_in = torch.bincount(ei1, minlength=N).float()
            deg_out = torch.bincount(ei0, minlength=N).float()
        feat_deg = torch.stack([torch.log1p(deg_in), torch.log1p(deg_out)], dim=-1)
        
        # 3) Base features
        base_feat = x_dense
        features = [base_feat]
        
        type_dim_dbg = 0
        code_dim_dbg = 0
        
        # 4) Type embedding (if enabled)
        if (self.input_emb is not None) and hasattr(data, "node_type_ids"):
            try:
                idx = data.node_type_ids.to(dev, non_blocking=True).long()
                type_vecs = self.input_emb(idx)
                type_dim_dbg = int(type_vecs.size(1))
                
                if str(self.embed_mode).lower() == "replace":
                    base_feat = type_vecs
                    features[0] = base_feat
                elif str(self.embed_mode).lower() == "concat":
                    features.append(type_vecs)
            except Exception as e:
                if not getattr(self, "_ids_warned_once", False):
                    print(f"[Wrapper][WARN] type embedding failed: {e}", flush=True)
                    self._ids_warned_once = True
        
        # 5) Code embedding (if available)
        code_vecs = getattr(data, "code_embeddings", None)
        if code_vecs is not None:
            code_vecs = code_vecs.to(dev, dtype=x_dense.dtype, non_blocking=True)
            
            # Align to N
            if code_vecs.size(0) != N:
                if code_vecs.size(0) > N:
                    code_vecs = code_vecs[:N]
                else:
                    pad = code_vecs.new_zeros(N - code_vecs.size(0), code_vecs.size(1))
                    code_vecs = torch.cat([code_vecs, pad], dim=0)
            
            code_dim_dbg = int(code_vecs.size(1))
            
            if str(self.code_mode).lower() == "replace":
                base_feat = code_vecs
                features[0] = base_feat
            elif str(self.code_mode).lower() == "concat":
                features.append(code_vecs)
        
        # 6) Always add degree features
        features.append(feat_deg)
        
        # 7) Assemble and project
        x_raw = torch.cat(features, dim=-1)
        
        # Debug (first forward only in legacy path)
        if getattr(self, "_dbg_embed", False) and not getattr(self, "_legacy_warned", False):
            base_dim = int(base_feat.size(1))
            base_name = "dense"
            if str(self.embed_mode).lower() == "replace" and type_dim_dbg > 0:
                base_name = "type(replace)"
            if str(self.code_mode).lower() == "replace" and code_dim_dbg > 0:
                base_name = "code(replace)"
            
            print(f"[Wrapper][LEGACY] Non-cached: base({base_name})={base_dim} + deg=2"
                f"{f' + code={code_dim_dbg}' if str(self.code_mode).lower()=='concat' and code_dim_dbg>0 else ''}"
                f"{f' + type={type_dim_dbg}' if str(self.embed_mode).lower()=='concat' and type_dim_dbg>0 else ''}"
                f" → {x_raw.size(1)} → hidden_dim={self.hidden_dim}", flush=True)
            self._legacy_warned = True
        
        data.x = self.input_proj(x_raw)
        return self.base_model(data)


class DevignNetWithProjection(nn.Module):
    """
    Wrapper that projects input features to DevignNet's expected dimension.
    Used when cache features don't match DevignNet's internal expectations.
    """
    def __init__(self, devign_core: nn.Module, in_dim: int, out_dim: int):
        super().__init__()
        self.projection = nn.Linear(in_dim, out_dim)
        self.core = devign_core
        
    def forward(self, data):
        # Project features
        data.x = self.projection(data.x)
        # Pass to DevignNet
        return self.core(data)
# ────────────────────────────────────────────
# Model factory
# ────────────────────────────────────────────
from typing import Optional
import argparse

# Assuming these classes are defined elsewhere:
# MPTCN_TTS, GCNBaseline, GATBaseline, SAGEBaseline, GINBaseline, PNABaseline,
# DeeperGCNBaseline, MPNNBaseline, RGcnBaseline, HANBaseline, HGTBaseline,
# NodeFeatureWrapper
def make_model(
    args,
    raw_feature_dim: int,
    num_node_tokens: int,
    cache_fused: bool = False,
) -> nn.Module:
    """
    Model factory for the cache-only Devign runner.

    This version ALWAYS builds EnhancedDevignNet (robust ResRGCN backbone)
    and ignores the older DevignSortPoolNet / DevignAttentionNet variants.
    """
    name = str(getattr(args, "model", "devign")).lower()
    if name != "devign":
        raise ValueError(f"[make_model] This runner only supports --model devign, got: {name}")

    hidden_dim = int(getattr(args, "hidden_dim", 256))
    out_dim = int(getattr(args, "num_classes", 2))
    steps = int(getattr(args, "devign_steps", getattr(args, "layers", 6)))
    dropout = float(getattr(args, "dropout", 0.2))

    if hidden_dim <= 0:
        raise ValueError(f"hidden_dim must be > 0, got {hidden_dim}")
    if raw_feature_dim <= 0:
        raise ValueError(f"raw_feature_dim must be > 0, got {raw_feature_dim}")

    # Infer number of Devign relations from vocab if available
    devign_rel_vocab = getattr(args, "devign_rel_vocab", None)
    if isinstance(devign_rel_vocab, dict) and len(devign_rel_vocab) > 0:
        num_relations = max(int(v) for v in devign_rel_vocab.values()) + 1
    else:
        # Devign default: 5 relation types (AST, CFG, DFG_READ, DFG_WRITE, NCS)
        num_relations = 5

    input_dim = int(raw_feature_dim)
    max_deg = int(getattr(args, "max_degree", 100))

    print("=" * 70)
    print("[make_model] EnhancedDevignNet configuration")
    print("=" * 70)
    print(f"  raw_feature_dim = {input_dim}")
    print(f"  hidden_dim      = {hidden_dim}")
    print(f"  layers          = {steps}")
    print(f"  num_relations   = {num_relations}")
    print(f"  num_node_tokens = {num_node_tokens}")
    print(f"  dropout         = {dropout}")
    print(f"  max_degree      = {max_deg}")
    print(f"  cache_fused     = {cache_fused}")
    print("=" * 70)

    model = EnhancedDevignNet(
        input_dim=input_dim,
        hidden_dim=hidden_dim,
        num_layers=steps,
        num_relations=num_relations,
        num_node_tokens=int(num_node_tokens),
        dropout=dropout,
        num_classes=out_dim,
        max_degree=max_deg,
    )

    # Optional gradient monitor (if you add --debug-gradients to argparse)
    if bool(getattr(args, "debug_gradients", False)):
        print("[make_model] Enabling GradientMonitor on EnhancedDevignNet")
        model.grad_monitor = GradientMonitor(model)

    return model


# ────────────────────────────────────────────
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

# def validate_cache_signature(dataset, args):
#     """
#     Validate that cache signature matches training configuration.
#     Prevents silent mismatches that cause poor performance.
#     """
#     try:
#         sample = dataset[0]
#         cache_sig = getattr(sample, "_cache_signature", None)
#         cache_fused = bool(getattr(sample, "_cache_fused", False))
        
#         if cache_sig is None:
#             print("[CacheValidation] ⚠️  WARNING: No cache signature found - using non-cached data?")
#             return
        
#         print(f"[CacheValidation] Cache signature: {cache_sig}")
#         print(f"[CacheValidation] Cache fused: {cache_fused}")
#         print(f"[CacheValidation] Feature dim: {sample.x.shape}")
        
#         # Check fusion mode consistency
#         model_fusion = str(getattr(args, "fusion", "none")).lower()
        
#         if cache_fused and model_fusion != "none":
#             print(f"[CacheValidation] ⚠️  WARNING: Cache already fused but model fusion='{model_fusion}'")
#             print(f"[CacheValidation]            Guards should prevent double fusion, but verify behavior!")
        
#         if not cache_fused and model_fusion == "none":
#             print(f"[CacheValidation] ℹ️  INFO: Neither cache nor model will fuse")
#             print(f"[CacheValidation]         Features are: {sample.x.shape}")
        
#         print("[CacheValidation] ✅ Validation complete\n")
        
#     except Exception as e:
#         print(f"[CacheValidation] ⚠️  Could not validate cache: {e}")


# ────────────────────────────────────────────
# INTELLIGENT DEBUGGING TOOLS
# ────────────────────────────────────────────
def register_grad_debug_hooks(model):
    """
    Registers hooks to print gradient norms for every layer.
    This helps identify EXACTLY which layer causes the explosion.
    """
    for name, param in model.named_parameters():
        if param.requires_grad:
            def make_hook(name):
                def hook(grad):
                    # Only print if things look scary (norm > 1.0)
                    norm = grad.norm().item()
                    if norm > 1.0 or torch.isnan(grad).any():
                        print(f"[GradAnalysis] {name} | Norm: {norm:.4f} | NaN: {torch.isnan(grad).any()}")
                return hook
            param.register_hook(make_hook(name))






import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.cuda.amp import autocast as autocast_ctx
from tqdm import tqdm
import time

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.cuda.amp import autocast as autocast_ctx
from tqdm import tqdm
import time

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.cuda.amp import autocast as autocast_ctx
from tqdm import tqdm
import time

def train_epoch_mutant_aware(
    model,
    loader,
    device,
    optimizer,
    scaler,
    amp: bool,
    args,
    dom_head=None,
    delta_head=None,
    proto_bank=None,
    global_step: int = 0,
    scheduler=None,
    first_probe_done: bool = False,
):
    """Robust training loop with BCE + SoftF1 + anti-collapse and NaN protection."""
    import time
    _tw = getattr(tqdm, "write", print)


    # ---------- Safe loss adder (nested helper) ---------------------------
    def _safe_add_loss(total, term, weight: float, name: str):
        """
        Add `weight * term` to `total` only if `term` is finite.
        Returns the new total.
        """
        if term is None or weight == 0.0:
            return total
        # Clean NaNs/Infs in the term itself
        term = torch.nan_to_num(term, nan=0.0, posinf=0.0, neginf=0.0)
        if not torch.isfinite(term):
            try:
                val = float(term.detach().item())
            except Exception:
                val = float("nan")
            _tw(f"[LossGuard] Skipping non-finite {name} loss: {val:.4e}")
            return total
        return total + weight * term
    # ---------------------------------------------------------------------

    if amp and scaler is None:
        raise RuntimeError("AMP is enabled but 'scaler' is None.")

    model.train()
    if delta_head is not None:
        delta_head.train()
    if dom_head is not None:
        dom_head.train()

    # Hyperparameters
    accum_steps   = max(1, int(getattr(args, "accum_steps", 1)))
    clip_grad     = float(getattr(args, "clip_grad", 1.0))
    dropedge_p    = float(getattr(args, "dropedge_p", 0.0))
    feat_noise    = float(getattr(args, "train_feat_noise_std", 0.0))
    rel_drop_p    = float(getattr(args, "rel_dropout_p", 0.0))

    pos_weight_v      = float(getattr(args, "pos_weight", 1.0))
    logit_l2_w        = float(getattr(args, "logit_l2", 0.0))
    consistency_w     = float(getattr(args, "consistency_w", 0.0))
    supcon_w          = float(getattr(args, "supcon_w", 0.0))
    anti_collapse_w   = float(getattr(args, "anti_collapse_w", 0.0))
    anti_collapse_tgt = float(getattr(args, "anti_collapse_target", 0.25))
    supcon_tau        = float(getattr(args, "supcon_tau", 0.1))
    focal_gamma       = float(getattr(args, "focal_gamma", 0.0))

    # NEW: gate regularizer weight

    debug_train_probs = bool(getattr(args, "debug_train_probs", False))
    debug_sleep       = float(getattr(args, "debug_sleep", 0.0) or 0.0)


    # Tracking
    micro_batches_processed = 0
    total_loss_accum        = 0.0   # total weighted loss (what we differentiate)
    cls_loss_accum          = 0.0   # classification (BCE+SoftF1) component
    supcon_loss_accum       = 0.0   # weighted SupCon contribution (supcon_w * sc_loss)
    gate_reg_loss_accum     = 0.0   # NEW: gate regularizer contribution (for logging)
    # NEW: gate regularizer weight
    gate_reg_w        = float(getattr(args, "gate_reg_w", 0.0) or 0.0)
    gate_target_mean  = float(getattr(args, "gate_target_mean", 0.4))
    gate_min_std      = float(getattr(args, "gate_min_std", 0.05))


    # delta_std epoch stats
    delta_std_sum    = 0.0
    delta_std_sq_sum = 0.0
    delta_std_min    = float("inf")
    delta_std_max    = 0.0
    delta_std_count  = 0

    # Loss functions
    bce_loss_fn = nn.BCEWithLogitsLoss(pos_weight=torch.tensor([pos_weight_v], device=device))
    f1_loss_fn  = SoftF1Loss().to(device)

    disable_bar = bool(getattr(loader, "_no_progress", False)) if hasattr(loader, "_no_progress") else False
    try:
        total_batches = len(loader)
    except Exception:
        total_batches = None

    pbar = tqdm(loader, desc="Train", disable=disable_bar, total=total_batches)
    optimizer.zero_grad(set_to_none=True)
    optimizer_steps_this_epoch = 0
    train_delta_debug_done     = False
    grad_debug_done            = False

    # counts micro-batches since last optimizer step (for debugging)
    accum_counter = 0

    for batch_idx, batch in enumerate(pbar):
        emb = None
        b   = batch.to(device, non_blocking=True)

        # Edge-type validation
        if hasattr(b, "edge_type") and hasattr(model, "num_relations"):
            if b.edge_type.max() >= model.num_relations:
                raise RuntimeError(
                    f"Training data edge_type {b.edge_type.max()} >= model.num_relations {model.num_relations}."
                )

        # One-time probe
        if not first_probe_done:
            try:
                graphs_this_step = b.batch.max().item() + 1
                _tw(f"[Probe] graphs in batch: {graphs_this_step}")
                if debug_sleep > 0.0:
                    time.sleep(debug_sleep)
            except Exception:
                pass
            first_probe_done = True

        # Augmentations
        if dropedge_p > 0.0 or feat_noise > 0.0:
            b = _augment_batch_for_eval(b, dropedge_p=dropedge_p, feat_noise_std=feat_noise)
        if rel_drop_p > 0.0:
            b = _relation_dropout_inplace(b, rel_drop_p)

        # ---------- Forward + Loss ----------
        with autocast_ctx(amp):
            out = model(b)

            alpha = None
            if isinstance(out, dict):
                logits_raw = out["logits"]
                emb = out.get("emb", None)
                alpha = out.get("alpha", None)
            else:
                logits_raw = out
                emb = None
                alpha = None


            # Sanitize logits but KEEP gradient for loss
            logits_raw = torch.nan_to_num(logits_raw, nan=0.0, posinf=50.0, neginf=-50.0)
            logits_clamped = logits_raw.clamp(-60.0, 60.0)  # no .detach()

            # Normalize logits shape
            if logits_clamped.dim() == 1:
                logits = logits_clamped.view(-1, 1)
            elif logits_clamped.dim() == 2:
                logits = logits_clamped
            else:
                raise RuntimeError(f"Unexpected logits shape {tuple(logits_clamped.shape)}")

            y = b.y.view(-1).float()
            m = min(logits.size(0), y.size(0))
            logits = logits[:m]
            y      = y[:m]

            # Binary margin delta
            if logits.size(-1) == 1:
                delta = logits.squeeze(-1)
            elif logits.size(-1) == 2:
                delta = logits[:, 1] - logits[:, 0]
            else:
                raise RuntimeError(f"Unexpected logits last-dim {logits.size(-1)}")

            # --- Classification Loss (Focal/BCE + Soft-F1) ---
            if focal_gamma > 0.0:
                cls_loss_main = focal_loss(delta, y, gamma=focal_gamma, pos_weight=pos_weight_v)
            else:
                cls_loss_main = bce_loss_fn(delta, y)

            cls_loss_f1 = f1_loss_fn(delta, y)
            cls_loss    = 0.6 * cls_loss_main + 0.4 * cls_loss_f1

            # delta std (for anti-collapse + stats)
            delta_std = delta.std()
            delta_std_val = float(delta_std.detach().item())
            delta_std_sum    += delta_std_val
            delta_std_sq_sum += delta_std_val * delta_std_val
            delta_std_min     = min(delta_std_min, delta_std_val)
            delta_std_max     = max(delta_std_max, delta_std_val)
            delta_std_count  += 1

            # One-time debug of logits/probs
            if not train_delta_debug_done:
                with torch.no_grad():
                    d_cpu = delta.detach().cpu()
                    p_cpu = torch.sigmoid(d_cpu)
                    _tw(f"[TrainDBG] delta stats: mean={d_cpu.mean():.4f} std={d_cpu.std():.4f}")
                    if debug_train_probs:
                        _tw(f"[TrainDBG] prob stats: mean={p_cpu.mean():.4f} std={p_cpu.std():.4f}")
                        y_cpu = y.detach().cpu()
                        for lab in [0, 1]:
                            mask = (y_cpu == lab)
                            if mask.any():
                                v = p_cpu[mask]
                                _tw(f"[TrainDBG] class {lab}: N={int(mask.sum())} mean={v.mean():.4f}")
                if debug_sleep > 0.0:
                    time.sleep(debug_sleep)
                train_delta_debug_done = True

            loss = cls_loss
            delta_std_for_reg = delta_std  # keep grad

            # ---------- SupCon (optional) ----------
            if supcon_w > 0.0 and isinstance(out, dict) and "proj" in out:
                z = F.normalize(out["proj"], dim=1)
                labels_v = y.view(-1)

                sim_matrix = torch.matmul(z, z.T) / supcon_tau
                sim_max, _ = sim_matrix.max(dim=1, keepdim=True)
                sim_matrix = sim_matrix - sim_max
                exp_sim = torch.exp(sim_matrix)

                mask = torch.eq(labels_v.unsqueeze(1), labels_v.unsqueeze(0)).float()
                mask_eye = torch.eye(z.shape[0], device=device, dtype=torch.float32)
                mask = mask - mask_eye

                sum_exp_sim = (exp_sim * (1 - mask_eye)).sum(dim=1, keepdim=True)
                log_prob = sim_matrix - torch.log(sum_exp_sim + 1e-8)

                pos_pairs = mask.sum(dim=1)
                has_pos = pos_pairs > 0
                if has_pos.sum() > 0:
                    mean_log_prob_pos = (mask * log_prob).sum(dim=1) / pos_pairs.clamp(min=1)
                    sc_loss = -mean_log_prob_pos[has_pos].mean()
                    supcon_contrib = supcon_w * sc_loss
                    loss = loss + supcon_contrib
                    supcon_loss_accum += float(supcon_contrib.item() * accum_steps)

            # ---------- Anti-collapse (fixed direction) ----------
            if anti_collapse_w > 0.0:
                gap = torch.relu(anti_collapse_tgt - delta_std_for_reg)
                ac_loss = gap.pow(2)
                loss = loss + anti_collapse_w * ac_loss

            # ---------- Logit L2 ----------
            if logit_l2_w > 0.0:
                loss = loss + logit_l2_w * delta.pow(2).mean()

            # ---------- Consistency (family) ----------
            if consistency_w > 0.0 and hasattr(b, "fid"):
                fid = b.fid.view(-1)
                with torch.no_grad():
                    p_eq = torch.ones_like(y)
                c_loss = consistency_loss_same_family(delta, y, fid, p_eq)
                loss = loss + consistency_w * c_loss

            # ---------- Gate regularizer (NEW, safe) ----------
            if gate_reg_w > 0.0 and alpha is not None and hasattr(model, "input_proj"):
                gate_mod = getattr(model, "input_proj", None)
                if isinstance(gate_mod, RobustGatedFusion):
                    gate_loss = gate_mod.gate_reg_loss(
                        alpha=alpha,
                        target_mean=gate_target_mean,
                        min_std=gate_min_std,
                    )
                    # Add safely to main loss
                    loss = _safe_add_loss(loss, gate_loss, gate_reg_w, "gate")
                    # For logging, we still track its magnitude
                    gate_reg_loss_accum += float(
                        (gate_reg_w * gate_loss.detach()).item() * accum_steps
                    )


            if loss is None:
                _tw(f"[WARN] No loss computed for batch {batch_idx}, skipping.")
                continue

            # Gradient accumulation scaling
            loss = loss / float(accum_steps)

            if not torch.isfinite(loss):
                _tw(f"[WARN] Loss NaN/Inf at batch {batch_idx}: {loss.item()}. Skipping this micro-batch.")
                if debug_sleep > 0.0:
                    time.sleep(debug_sleep)
                continue

        if not loss.requires_grad:
            _tw(f"[WARN] Loss doesn't require grad at batch {batch_idx}, skipping.")
            if debug_sleep > 0.0:
                time.sleep(debug_sleep)
            continue

        # ---------- Backward ----------
        if amp and scaler is not None:
            scaler.scale(loss).backward()
        else:
            loss.backward()

        # Tracking (use unscaled metrics)
        total_loss_accum += float(loss.detach().item() * accum_steps)
        cls_loss_accum   += float(cls_loss.item() * accum_steps)
        micro_batches_processed += 1
        accum_counter += 1

        # ---------- Optimizer step (with accumulation) ----------
        is_accum_boundary = (
            ((batch_idx + 1) % accum_steps == 0)
            or (total_batches is not None and (batch_idx + 1 == total_batches))
        )

        if is_accum_boundary:
            nan_grad = False
            grad_norm = None

            # 1) Unscale once per optimizer update window (AMP only)
            if amp and scaler is not None:
                try:
                    scaler.unscale_(optimizer)
                except RuntimeError as e:
                    _tw(f"[GradDBG][ERROR] unscale_ failed at batch {batch_idx}: {e}")
                    optimizer.zero_grad(set_to_none=True)
                    accum_counter = 0
                    if debug_sleep > 0.0:
                        time.sleep(debug_sleep)
                    # skip this step and continue training
                    continue

            # 2) Clip gradients + detect NaN/Inf
            if clip_grad > 0.0:
                grad_norm = torch.nn.utils.clip_grad_norm_(model.parameters(), clip_grad)

                if not grad_debug_done and not getattr(args, "no_progress", False):
                    _tw(f"[GradDBG] batch={batch_idx} grad_norm={float(grad_norm):.4e}")
                    if debug_sleep > 0.0:
                        time.sleep(debug_sleep)
                    grad_debug_done = True

                if hasattr(model, "grad_monitor"):
                    try:
                        if (batch_idx % int(getattr(args, "grad_debug_interval", 100) or 100)) == 0:
                            model.grad_monitor.print_stats(top_k=3)
                    except Exception as e:
                        _tw(f"[GradDBG] grad_monitor error: {e}")

                if torch.isnan(grad_norm) or torch.isinf(grad_norm):
                    nan_grad = True
                    _tw(
                        f"[CRIT] Gradient explosion at global_step={global_step}: "
                        f"grad_norm={grad_norm}. Skipping optimizer step."
                    )
                    if debug_sleep > 0.0:
                        time.sleep(debug_sleep)

            # 3) Step (maybe) + always update scaler if AMP
            did_step = False
            if not nan_grad and accum_counter > 0:
                if amp and scaler is not None:
                    scaler.step(optimizer)
                else:
                    optimizer.step()
                did_step = True
            else:
                _tw(
                    f"[StepDBG] Skipping optimizer.step at batch {batch_idx} "
                    f"(nan_grad={nan_grad}, accum_counter={accum_counter})"
                )

            if amp and scaler is not None:
                scaler.update()

            # 4) Clear grads & scheduler
            optimizer.zero_grad(set_to_none=True)

            if did_step:
                optimizer_steps_this_epoch += 1
                global_step += 1
                if scheduler is not None:
                    try:
                        scheduler.step()
                    except Exception as e:
                        _tw(f"[Scheduler][WARN] {e}")

            # reset accumulation counter
            accum_counter = 0

    # ---------- Epoch-level stats ----------
    avg_loss         = total_loss_accum / max(1, micro_batches_processed)
    avg_cls_loss     = cls_loss_accum   / max(1, micro_batches_processed)
    avg_supcon_loss  = supcon_loss_accum / max(1, micro_batches_processed)
    avg_gate_reg_loss = gate_reg_loss_accum / max(1, micro_batches_processed)

    if delta_std_count > 0 and not getattr(args, "no_progress", False):
        mean_delta_std = delta_std_sum / delta_std_count
        var_delta_std  = max(0.0, delta_std_sq_sum / delta_std_count - mean_delta_std * mean_delta_std)
        std_delta_std  = var_delta_std ** 0.5
        _tw(
            f"[EpochTrainDBG] delta_std: "
            f"mean={mean_delta_std:.4f} std={std_delta_std:.4f} "
            f"min={delta_std_min:.4f} max={delta_std_max:.4f}"
        )

    avg_delta_std = delta_std_sum / max(1, delta_std_count)

    if not getattr(args, "no_progress", False):
        _tw(
            f"[EpochTrain] steps={optimizer_steps_this_epoch} "
            f"| cls={avg_cls_loss:.4f} supcon={avg_supcon_loss:.4f} "
            f"gate={avg_gate_reg_loss:.4f} "
            f"total={avg_loss:.4f} delta_std={avg_delta_std:.4f}"
        )

    return total_loss_accum, global_step, first_probe_done


    
def _as_int(val, default):
    return default if val is None else int(val)

# ----- datasets (with cache manager + final vocabs) -----
# ----- datasets (load from pre-built cache) -----
from torch.utils.data import Dataset as TorchDataset

    
class CachedDataset(TorchDataset):
    """
    Loads pre-built PyG Data objects from cache directory.
    Uses index.csv to map entries to cached .pt files.
    """
    
    def __init__(self, cache_dir: Path, manifest_path: Optional[Path] = None):
        self.cache_dir = Path(cache_dir)
        self.manifest_path = manifest_path
        
        # 1. Load index.csv (Source of Truth for Files)
        index_csv = self.cache_dir / "meta" / "index.csv"
        if not index_csv.exists():
            raise RuntimeError(f"Index CSV not found: {index_csv}")
        
        self.index_entries = []
        with open(index_csv, "r") as f:
            reader = csv.DictReader(f)
            self.index_entries = list(reader)
        
        if not self.index_entries:
            raise RuntimeError(f"Index CSV is empty: {index_csv}")
        
        print(f"[Dataset] Loaded {len(self.index_entries)} entries from index.csv")
        
        # 2. Build Fast Paths Lookup
        self.pt_paths = []
        for entry in self.index_entries:
            rel_path = entry.get("rel_path", "")
            if not rel_path:
                raise RuntimeError(f"Index entry missing rel_path: {entry}")
            
            abs_path = self.cache_dir / rel_path
            if not abs_path.exists():
                raise RuntimeError(f"Cached file not found: {abs_path}")
            
            self.pt_paths.append(abs_path)
        
        # 3. Load Manifest (Source of Truth for Labels/Metadata)
        raw_rows = []
        if manifest_path and Path(manifest_path).exists():
            with open(manifest_path, "r") as f:
                raw_rows = list(csv.DictReader(f))
            print(f"[Dataset] Loaded {len(raw_rows)} manifest rows")
        
        # 4. ALIGN MANIFEST ROWS TO INDEX ORDER
        # We must match rows to index_entries via 'row_key' or 'function_id'
        if raw_rows:
            row_map = {}
            for r in raw_rows:
                # Try keys in order of reliability
                if r.get("row_key"): row_map[str(r["row_key"])] = r
                elif r.get("function_id"): row_map[str(r["function_id"])] = r
                elif r.get("fid"): row_map[str(r["fid"])] = r
            
            aligned_rows = []
            matches = 0
            for entry in self.index_entries:
                # Try exact match first
                k = str(entry.get("row_key", ""))
                match = row_map.get(k)
                
                # Try function ID fallback
                if not match:
                    fid = str(entry.get("function_id", ""))
                    match = row_map.get(fid)
                
                if match:
                    matches += 1
                    aligned_rows.append(match)
                else:
                    # Fallback to index info if manifest row missing
                    aligned_rows.append({"label": entry.get("label", 0)})
            
            print(f"[Dataset] Aligned {matches}/{len(self.index_entries)} rows from manifest.")
            self.rows = aligned_rows
        else:
            # No manifest provided, rely entirely on index.csv
            self.rows = [{"label": entry.get("label", 0)} for entry in self.index_entries]
        
        print(f"[Dataset] Ready: {len(self)} samples")
    
    def __len__(self):
        return len(self.index_entries)
    
    def __getitem__(self, idx):
        if idx >= len(self.pt_paths):
            raise IndexError(f"Index {idx} out of range (dataset has {len(self.pt_paths)} samples)")
        
        pt_file = self.pt_paths[idx]
        
        try:
            data = torch.load(pt_file, map_location="cpu")

            # Attach row metadata if available, but DO NOT override cached label
            if idx < len(self.rows):
                row = self.rows[idx]
                # Keep manifest row for debugging / project info / stats
                setattr(data, "manifest_row", row)

            return data
        except Exception as e:
            print(f"[Dataset] Error loading {pt_file}: {e}")
            raise



def debug_cached_features(dataset, num_graphs: int = 5):
    import math
    print(f"\n[DebugX] Inspecting first {num_graphs} graphs from cache_dir={dataset.cache_dir}")
    means = []
    stds = []
    for i in range(min(num_graphs, len(dataset))):
        d = dataset[i]
        x = d.x.float()
        m = float(x.mean())
        s = float(x.std())
        means.append(m)
        stds.append(s)
        print(f"[DebugX] idx={i:4d} x.shape={tuple(x.shape)} mean={m:.4e} std={s:.4e}")
    if len(means) >= 2:
        print(f"[DebugX] per-graph mean range: {min(means):.4e} → {max(means):.4e}")
        print(f"[DebugX] per-graph std  range: {min(stds):.4e} → {max(stds):.4e}")



# ──────────────────────────────────────────────────────────
# Collapse policy helper (orig/snap/K-per-family/none/all)
# ──────────────────────────────────────────────────────────
def _apply_collapse_policy(
    dataset,
    policy: str = "all",
    K: int = 2,
    seed: int = 42,
    verbose: bool = True
) -> Dict[str, Any]:
    """
    Robust runtime collapse that filters CachedDataset based on family membership.
    
    CRITICAL: Works with CachedDataset that loads from index.csv by filtering
    both index_entries (source of truth) and pt_paths (actual file references).
    
    Args:
        dataset: CachedDataset instance with index_entries and pt_paths
        policy: Collapse strategy
            - "all" or "none": Keep everything (no-op)
            - "orig": Keep only originals (export snapshots)
            - "snap": Keep only mutants (exclude originals)
            - "k" or "k-per-family": Keep up to K members per family
                (prefer 1 original + K-1 random mutants)
        K: Maximum members per family (for k-per-family policy)
        seed: Random seed for deterministic mutant selection
        verbose: Print detailed statistics
    
    Returns:
        Dict with collapse statistics for logging
    
    Modifies:
        dataset.index_entries (filtered list)
        dataset.pt_paths (filtered list, synchronized with index_entries)
        dataset.rows (filtered if present, for metadata compatibility)
    
    Example row_key formats (from index.csv):
        - test_func_0000001__export__b7f172bd          (original)
        - test_func_0000001__snap_adv1_nocm__28ba3f95  (mutant)
        - test_func_0000002__snap_adv2_nocm__a3e9ce46  (mutant)
    
    Family extraction: "test_func_0000001__export__b7f172bd" → "test_func_0000001"
    """
    import re
    from collections import defaultdict
    import random
    
    # ═══════════════════════════════════════════════════════════════════════════
    # INPUT VALIDATION
    # ═══════════════════════════════════════════════════════════════════════════
    
    if not hasattr(dataset, 'index_entries'):
        raise TypeError(
            f"Dataset must have 'index_entries' attribute (CachedDataset). "
            f"Got type: {type(dataset).__name__}"
        )
    
    entries = dataset.index_entries
    if not isinstance(entries, list) or len(entries) == 0:
        if verbose:
            print(f"[Collapse] Dataset empty, skipping (policy={policy})")
        return {"status": "skipped", "reason": "empty_dataset"}
    
    original_count = len(entries)
    
    # Validate cache_dir
    if not hasattr(dataset, 'cache_dir'):
        raise AttributeError("Dataset missing 'cache_dir' attribute")
    
    # Normalize policy
    policy = (policy or "all").strip().lower()
    K = max(1, int(K))
    seed = int(seed)
    
    if verbose:
        print(f"\n{'='*70}")
        print(f"COLLAPSE POLICY: {policy.upper()}")
        print(f"{'='*70}")
        print(f"Policy: {policy}")
        if policy in ("k", "k-per-family", "k_per_family", "kperfamily"):
            print(f"K (max per family): {K}")
        print(f"Seed: {seed}")
        print(f"Original size: {original_count} samples")
    
    # No-op policies
    if policy in ("all", "none"):
        if verbose:
            print(f"[Collapse] Policy '{policy}' → no filtering")
            print(f"{'='*70}\n")
        return {
            "status": "no_change",
            "policy": policy,
            "original_count": original_count,
            "final_count": original_count,
        }
    
    # Initialize RNG
    rng = random.Random(seed)
    
    # ═══════════════════════════════════════════════════════════════════════════
    # HELPER FUNCTIONS
    # ═══════════════════════════════════════════════════════════════════════════
    
    def _is_original(entry: dict) -> bool:
        """
        Detect if entry is an original (non-mutant) from row_key.
        
        Detection rules:
        1. Contains "__export__" → ORIGINAL
        2. Contains "__snap_" or "__adv" or "__mutant" → MUTANT
        3. Has mutation_type field == "orig" → ORIGINAL
        4. Default: Assume ORIGINAL (conservative)
        
        Examples:
            test_func_0000001__export__b7f172bd         → True
            test_func_0000001__snap_adv1_nocm__28ba3f95 → False
        """
        row_key = str(entry.get("row_key", ""))
        
        # Rule 1: Explicit original marker
        if "__export__" in row_key:
            return True
        
        # Rule 2: Explicit mutant markers
        mutant_markers = ["__snap_", "__adv", "__mutant", "_nocm", "_cm"]
        if any(marker in row_key for marker in mutant_markers):
            return False
        
        # Rule 3: Check metadata if present
        if "mutation_type" in entry:
            return str(entry.get("mutation_type", "")).lower() == "orig"
        
        # Rule 4: Default (conservative - assume original if ambiguous)
        return True
    
    def _extract_function_id(entry: dict) -> str:
        """
        Extract function ID from row_key.
        
        Expected format: {function_id}__{snapshot}__{hash8}
        
        Examples:
            test_func_0000001__export__b7f172bd         → test_func_0000001
            test_func_0000001__snap_adv1_nocm__28ba3f95 → test_func_0000001
            train_func_0012345__snap_adv2_nocm__abc123  → train_func_0012345
        
        Fallback: If pattern doesn't match, use first part before "__"
        """
        row_key = str(entry.get("row_key", ""))
        
        if not row_key:
            return "unknown"
        
        # Primary pattern: split on "__" and take first part
        parts = row_key.split("__")
        if len(parts) >= 2:
            func_id = parts[0]
            
            # Validate it looks like a function ID
            # Expected: {prefix}_func_{digits} or func_{digits}
            if re.match(r'^[A-Za-z0-9]*_?func_\d+$', func_id, re.IGNORECASE):
                return func_id.lower()
            
            # If not standard format, still use it but warn
            if verbose and len(parts) >= 3:
                # Only warn once per unique pattern
                if not hasattr(_extract_function_id, '_warned'):
                    _extract_function_id._warned = set()
                if func_id not in _extract_function_id._warned:
                    print(f"[Collapse][WARN] Non-standard function ID format: {func_id}")
                    _extract_function_id._warned.add(func_id)
            
            return func_id.lower()
        
        # Fallback: use entire row_key as family
        return row_key.lower()
    
    def _entry_sort_key(entry: dict) -> str:
        """Deterministic sort key for entries."""
        return str(entry.get("row_key", ""))
    
    # ═══════════════════════════════════════════════════════════════════════════
    # BUILD FAMILIES
    # ═══════════════════════════════════════════════════════════════════════════
    
    families = defaultdict(list)
    family_stats = {"originals": 0, "mutants": 0}
    
    for entry in entries:
        func_id = _extract_function_id(entry)
        families[func_id].append(entry)
        
        if _is_original(entry):
            family_stats["originals"] += 1
        else:
            family_stats["mutants"] += 1
    
    # Sort members within each family (deterministic ordering)
    for func_id in families:
        families[func_id].sort(key=_entry_sort_key)
    
    num_families = len(families)
    avg_family_size = original_count / max(1, num_families)
    
    if verbose:
        print(f"\n[Families]")
        print(f"  Total families: {num_families}")
        print(f"  Avg family size: {avg_family_size:.2f}")
        print(f"  Originals: {family_stats['originals']} ({100*family_stats['originals']/original_count:.1f}%)")
        print(f"  Mutants: {family_stats['mutants']} ({100*family_stats['mutants']/original_count:.1f}%)")
        
        # Show family size distribution
        family_sizes = [len(members) for members in families.values()]
        print(f"  Family size: min={min(family_sizes)}, max={max(family_sizes)}, "
              f"median={sorted(family_sizes)[len(family_sizes)//2]}")
    
    # ═══════════════════════════════════════════════════════════════════════════
    # APPLY POLICY
    # ═══════════════════════════════════════════════════════════════════════════
    
    kept_entries = []
    policy_stats = {
        "families_processed": 0,
        "families_kept": 0,
        "originals_kept": 0,
        "mutants_kept": 0,
    }
    
    if policy == "orig":
        # Keep only originals
        for func_id, members in families.items():
            policy_stats["families_processed"] += 1
            
            originals = [e for e in members if _is_original(e)]
            if originals:
                policy_stats["families_kept"] += 1
                policy_stats["originals_kept"] += len(originals)
                kept_entries.extend(originals)
    
    elif policy == "snap":
        # Keep only mutants (exclude originals)
        for func_id, members in families.items():
            policy_stats["families_processed"] += 1
            
            mutants = [e for e in members if not _is_original(e)]
            if mutants:
                policy_stats["families_kept"] += 1
                policy_stats["mutants_kept"] += len(mutants)
                kept_entries.extend(mutants)
    
    elif policy in ("k", "k-per-family", "k_per_family", "kperfamily"):
        # Keep up to K members per family (prefer 1 original + K-1 mutants)
        for func_id, members in families.items():
            policy_stats["families_processed"] += 1
            
            if len(members) <= K:
                # Family has ≤K members, keep all
                kept_entries.extend(members)
                policy_stats["families_kept"] += 1
                policy_stats["originals_kept"] += sum(1 for e in members if _is_original(e))
                policy_stats["mutants_kept"] += sum(1 for e in members if not _is_original(e))
            else:
                # Family has >K members, select K
                originals = [e for e in members if _is_original(e)]
                mutants = [e for e in members if not _is_original(e)]
                
                chosen = []
                
                # Step 1: Pick 1 original (deterministic: first in sorted order)
                if originals:
                    chosen.append(originals[0])
                    policy_stats["originals_kept"] += 1
                
                # Step 2: Pick K-1 random mutants (or as many as available)
                need = K - len(chosen)
                if need > 0 and mutants:
                    # Random selection (seeded for reproducibility)
                    selected_mutants = rng.sample(mutants, k=min(need, len(mutants)))
                    chosen.extend(selected_mutants)
                    policy_stats["mutants_kept"] += len(selected_mutants)
                
                # Step 3: If still short (no mutants), pad with remaining originals
                if len(chosen) < K and len(originals) > 1:
                    remaining_origs = [e for e in originals if e not in chosen]
                    need = K - len(chosen)
                    chosen.extend(remaining_origs[:need])
                    policy_stats["originals_kept"] += min(need, len(remaining_origs))
                
                kept_entries.extend(chosen)
                policy_stats["families_kept"] += 1
    
    else:
        raise ValueError(f"Unknown collapse policy: {policy!r}. "
                        f"Valid: all, none, orig, snap, k-per-family")
    
    final_count = len(kept_entries)
    
    # ═══════════════════════════════════════════════════════════════════════════
    # VALIDATION
    # ═══════════════════════════════════════════════════════════════════════════
    
    if final_count == 0:
        raise RuntimeError(
            f"Collapse policy '{policy}' resulted in ZERO samples! "
            f"Original: {original_count}, Policy: {policy}, K: {K}"
        )
    
    # Validate K constraint for k-per-family
    if policy in ("k", "k-per-family", "k_per_family", "kperfamily"):
        kept_families = defaultdict(list)
        for entry in kept_entries:
            func_id = _extract_function_id(entry)
            kept_families[func_id].append(entry)
        
        max_family_size = max(len(members) for members in kept_families.values())
        if max_family_size > K:
            raise RuntimeError(
                f"VALIDATION FAILED: Found family with {max_family_size} members "
                f"after K={K} collapse. This is a bug!"
            )
    
    # ═══════════════════════════════════════════════════════════════════════════
    # UPDATE DATASET (CRITICAL: Synchronize index_entries and pt_paths)
    # ═══════════════════════════════════════════════════════════════════════════
    
    # Update index_entries
    dataset.index_entries = kept_entries
    
    # Rebuild pt_paths to match filtered index_entries
    new_pt_paths = []
    missing_files = []
    
    for entry in kept_entries:
        rel_path = entry.get("rel_path", "")
        if not rel_path:
            raise RuntimeError(f"Entry missing 'rel_path' field: {entry}")
        
        abs_path = dataset.cache_dir / rel_path
        if not abs_path.exists():
            missing_files.append(str(abs_path))
        else:
            new_pt_paths.append(abs_path)
    
    if missing_files:
        # Show first few missing files
        examples = missing_files[:5]
        raise RuntimeError(
            f"CRITICAL: {len(missing_files)} cached files not found after collapse!\n"
            f"Examples:\n" + "\n".join(f"  - {p}" for p in examples) +
            f"\n\nThis indicates cache corruption or path resolution bug."
        )
    
    dataset.pt_paths = new_pt_paths
    
    # Also update rows if present (for metadata compatibility)
    if hasattr(dataset, 'rows') and isinstance(dataset.rows, list):
        if len(dataset.rows) == original_count:
            # Rows were aligned with original entries - filter by index
            original_indices = {i: entry for i, entry in enumerate(entries)}
            kept_indices = {i for i, entry in enumerate(entries) if entry in kept_entries}
            dataset.rows = [dataset.rows[i] for i in sorted(kept_indices) if i < len(dataset.rows)]
        else:
            # Rows and entries don't align - try to match by row_key
            if verbose:
                print(f"[Collapse][WARN] Rows ({len(dataset.rows)}) != entries ({original_count})")
            
            # Build mapping from row_key to row
            if all("row_key" in e for e in kept_entries):
                kept_keys = {e["row_key"] for e in kept_entries}
                # Filter rows by matching keys if possible
                if all(isinstance(r, dict) and "row_key" in r for r in dataset.rows):
                    dataset.rows = [r for r in dataset.rows if r.get("row_key") in kept_keys]
                # Otherwise keep all rows (metadata may not align perfectly)
    
    # Verify synchronization
    assert len(dataset.index_entries) == len(dataset.pt_paths), \
        f"CRITICAL BUG: index_entries ({len(dataset.index_entries)}) != " \
        f"pt_paths ({len(dataset.pt_paths)}) after collapse"
    
    # ═══════════════════════════════════════════════════════════════════════════
    # STATISTICS & LOGGING
    # ═══════════════════════════════════════════════════════════════════════════
    
    reduction_pct = 100 * (1 - final_count / original_count)
    
    stats = {
        "status": "success",
        "policy": policy,
        "K": K if policy in ("k", "k-per-family", "k_per_family", "kperfamily") else None,
        "seed": seed,
        "original_count": original_count,
        "final_count": final_count,
        "reduction_pct": reduction_pct,
        "families_total": num_families,
        "families_kept": policy_stats["families_kept"],
        "originals_kept": policy_stats["originals_kept"],
        "mutants_kept": policy_stats["mutants_kept"],
        "avg_members_per_family": final_count / max(1, policy_stats["families_kept"]),
    }
    
    if verbose:
        print(f"\n[Results]")
        print(f"  Kept: {final_count}/{original_count} samples ({reduction_pct:.1f}% reduction)")
        print(f"  Families kept: {policy_stats['families_kept']}/{num_families}")
        print(f"  Originals kept: {policy_stats['originals_kept']}")
        print(f"  Mutants kept: {policy_stats['mutants_kept']}")
        print(f"  Avg members/family: {stats['avg_members_per_family']:.2f}")
        print(f"\n✅ Collapse successful")
        print(f"  index_entries: {len(dataset.index_entries)} entries")
        print(f"  pt_paths: {len(dataset.pt_paths)} paths")
        print(f"  dataset.__len__(): {len(dataset)} samples")
        print(f"{'='*70}\n")
    
    return stats


# ═══════════════════════════════════════════════════════════════════════════
# VALIDATION HELPER (Call after collapse to verify correctness)
# ═══════════════════════════════════════════════════════════════════════════

def validate_collapsed_dataset(dataset, policy: str, K: int = 2, verbose: bool = True):
    """
    Validate that collapse was applied correctly.
    Raises exceptions if invariants are violated.
    """
    if not hasattr(dataset, 'index_entries'):
        raise TypeError("Dataset must have 'index_entries' attribute")
    
    entries = dataset.index_entries
    n = len(entries)
    
    if n == 0:
        raise ValueError("Dataset is empty after collapse!")
    
    # Check 1: Synchronization
    assert len(dataset.pt_paths) == n, \
        f"pt_paths ({len(dataset.pt_paths)}) != index_entries ({n})"
    
    # Check 2: All files exist
    missing = [p for p in dataset.pt_paths if not p.exists()]
    if missing:
        raise RuntimeError(f"{len(missing)} files missing: {missing[:3]}")
    
    # Check 3: Policy-specific validation
    from collections import defaultdict
    
    def _extract_func_id(e):
        return str(e.get("row_key", "")).split("__")[0] if "__" in e.get("row_key", "") else "unknown"
    
    def _is_orig(e):
        return "__export__" in str(e.get("row_key", ""))
    
    families = defaultdict(list)
    for entry in entries:
        func_id = _extract_func_id(entry)
        families[func_id].append(entry)
    
    if policy == "orig":
        # Should have only originals
        non_origs = [e for e in entries if not _is_orig(e)]
        if non_origs:
            raise ValueError(f"Found {len(non_origs)} non-originals in orig-only dataset")
    
    elif policy == "snap":
        # Should have no originals
        origs = [e for e in entries if _is_orig(e)]
        if origs:
            raise ValueError(f"Found {len(origs)} originals in mutants-only dataset")
    
    elif policy in ("k", "k-per-family", "k_per_family", "kperfamily"):
        # No family should have >K members
        oversized = [(fid, len(members)) for fid, members in families.items() if len(members) > K]
        if oversized:
            raise ValueError(
                f"Found {len(oversized)} families with >{K} members: {oversized[:5]}"
            )
    
    if verbose:
        print(f"✅ Validation passed: {n} samples, {len(families)} families")
    
    return True

def _len_ds(ds) -> int:
    try:
        return len(ds)
    except TypeError:
        return len(getattr(ds, "rows", []))



def validate_cache_signature(dataset, model, args, split_name="TRAIN"):
    """
    Validate that cache signature matches model/training configuration.
    
    Prevents silent mismatches that cause:
    - Double fusion (cache + model both fusing)
    - Dimension errors (wrong feature widths)
    - Poor performance (incompatible features)
    
    Args:
        dataset: DevignDataset instance
        model: Model instance (can be None for early validation)
        args: Training arguments
        split_name: Name of split for logging
    """
 
    
    print(f"\n{'='*70}")
    print(f"CACHE VALIDATION: {split_name}")
    print(f"{'='*70}")
    
    try:
        # Get first sample
        if len(dataset) == 0:
            print(f"⚠️  [{split_name}] Dataset is empty - skipping validation")
            return
        
        sample = dataset[0]
        
        # Extract cache metadata
        cache_sig = getattr(sample, "_cache_signature", None)
        cache_fused = bool(getattr(sample, "_cache_fused", False))
        x_shape = tuple(sample.x.shape) if hasattr(sample, "x") else None
        
        # Basic metadata check
        if cache_sig is None:
            print(f"⚠️  [{split_name}] No cache signature found")
            print(f"    This might be non-cached data or old cache format")
        else:
            print(f"✅ [{split_name}] Cache signature: {cache_sig}")
        
        print(f"✅ [{split_name}] Cache fused: {cache_fused}")
        print(f"✅ [{split_name}] Feature shape: {x_shape}")
        
        # Check for code embeddings
        has_code_emb = hasattr(sample, "code_embeddings") and sample.code_embeddings is not None
        if has_code_emb:
            code_shape = tuple(sample.code_embeddings.shape)
            code_nnz = (sample.code_embeddings.abs().sum(dim=1) > 0).sum().item()
            print(f"✅ [{split_name}] Code embeddings: {code_shape} ({code_nnz}/{code_shape[0]} non-zero)")
        else:
            print(f"ℹ️  [{split_name}] Code embeddings: None")
        
        # Check edge types
        has_edge_type = hasattr(sample, "edge_type") and sample.edge_type is not None
        has_edge_type_devign = hasattr(sample, "edge_type_devign") and sample.edge_type_devign is not None
        
        if has_edge_type:
            print(f"✅ [{split_name}] edge_type present: {sample.edge_type.shape}")
        if has_edge_type_devign:
            print(f"✅ [{split_name}] edge_type_devign present: {sample.edge_type_devign.shape}")
        if not has_edge_type and not has_edge_type_devign:
            print(f"⚠️  [{split_name}] No edge type attributes found")
        
        # ═══════════════════════════════════════════════════════════════
        # CRITICAL CHECKS: Fusion mode consistency
        # ═══════════════════════════════════════════════════════════════
        
        model_fusion = str(getattr(args, "fusion", "none")).lower()
        
        print(f"\n{'─'*70}")
        print(f"FUSION CONFIGURATION CHECK")
        print(f"{'─'*70}")
        
        print(f"Model fusion mode: {model_fusion}")
        print(f"Cache fused: {cache_fused}")
        
        # Check 1: Double fusion risk
        if cache_fused and model_fusion != "none":
            print(f"\n🚨 [CRITICAL WARNING] DOUBLE FUSION RISK DETECTED!")
            print(f"   Cache already fused: {cache_fused}")
            print(f"   Model fusion mode: {model_fusion}")
            print(f"   ")
            print(f"   This will cause dimension errors or poor performance!")
            print(f"   ")
            print(f"   SOLUTION: Set --fusion none when using cache-fused data")
            print(f"   OR: Rebuild cache with fusion_mode='none'")
        
        # Check 2: Incomplete features
        if not cache_fused and model_fusion == "none":
            print(f"\n⚠️  [WARNING] No fusion from cache OR model")
            print(f"   Cache fused: {cache_fused}")
            print(f"   Model fusion: {model_fusion}")
            print(f"   ")
            print(f"   Features may be incomplete!")
            print(f"   ")
            print(f"   If you want code embeddings:")
            print(f"   - Option A: Rebuild cache with fusion_mode='early_concat'")
            print(f"   - Option B: Set --fusion early (model-side fusion)")
        
        # Check 3: Expected dimensions
        if x_shape:
            expected_dim = None
            
            if bool(getattr(args, "one_hot", True)):
                vocab_size = len(getattr(args, "_node_vocab_for_check", {}))
                if vocab_size > 0:
                    if cache_fused and has_code_emb:
                        expected_dim = vocab_size + 768  # one-hot + CodeBERT
                    else:
                        expected_dim = vocab_size
            
            if expected_dim and x_shape[1] != expected_dim:
                print(f"\n⚠️  [WARNING] Feature dimension mismatch")
                print(f"   Expected: {expected_dim}")
                print(f"   Actual: {x_shape[1]}")
        
        # Check 4: Model compatibility (if model provided)
        if model is not None:
            print(f"\n{'─'*70}")
            print(f"MODEL COMPATIBILITY CHECK")
            print(f"{'─'*70}")
            
            # Test forward pass
            try:
                model.eval()
                device = next(model.parameters()).device
                sample_dev = sample.to(device)
                
                with torch.no_grad():
                    output = model(sample_dev)
                
                logits_shape = output["logits"].shape if isinstance(output, dict) else output.shape
                print(f"✅ [{split_name}] Model forward pass successful")
                print(f"   Output shape: {logits_shape}")
                
            except RuntimeError as e:
                if "size mismatch" in str(e) or "dimension" in str(e).lower():
                    print(f"\n🚨 [CRITICAL ERROR] Model forward pass failed!")
                    print(f"   Error: {e}")
                    print(f"   ")
                    print(f"   This indicates dimension mismatch (likely double fusion)")
                    raise
                else:
                    print(f"⚠️  [{split_name}] Model forward pass failed: {e}")
            except Exception as e:
                print(f"⚠️  [{split_name}] Could not test model forward: {e}")
        
        print(f"\n{'='*70}")
        print(f"✅ [{split_name}] Validation Complete")
        print(f"{'='*70}\n")
        
    except Exception as e:
        print(f"\n⚠️  [{split_name}] Validation error: {e}")
        import traceback
        traceback.print_exc()


def _jsonify(o):
    """Safe JSON converter for numpy / torch objects."""
    import numpy as np
    import torch

    if isinstance(o, (np.bool_, bool)):
        return bool(o)
    if isinstance(o, (np.integer,)):
        return int(o)
    if isinstance(o, (np.floating,)):
        return float(o)
    if isinstance(o, np.ndarray):
        return o.tolist()
    if isinstance(o, torch.Tensor):
        if o.dim() == 0:
            return float(o.item())
        return o.detach().cpu().tolist()
    # fallback
    try:
        return o.item()  # torch scalar or similar
    except Exception:
        return str(o)



from pathlib import Path


def _infer_index_path_from_args_for_split(args, split: str) -> Optional[Path]:
    """
    Infer index.csv path for a given split ("train", "val", "test") using:
      • <split>_cache_zip (preferred)
      • or cache_dir + dataset_name + cache_signature layout.
    """
    split = split.lower()

    # Map split → argument name for cache_zip flags
    split_to_zip_attr = {
        "train": "train_cache_zip",
        "val": "val_cache_zip",
        "valid": "val_cache_zip",
        "test": "test_cache_zip",
    }
    cache_zip_attr = split_to_zip_attr.get(split)
    idx_path: Optional[Path] = None

    # 1) Preferred: derive from --*-cache-zip
    if cache_zip_attr is not None:
        cache_zip = getattr(args, cache_zip_attr, None)
        if cache_zip:
            cache_zip = Path(cache_zip)
            candidate = cache_zip.parent / "meta" / "index.csv"
            if candidate.exists():
                return candidate

    # 2) Fallback: cache_dir / dataset_name / split / cache_signature / meta/index.csv
    cache_dir = getattr(args, "cache_dir", None)
    cache_sig = getattr(args, "cache_signature", None)
    dataset_name = getattr(args, "dataset_name", "devign")

    if cache_dir and cache_sig:
        cache_dir = Path(cache_dir)

        # cache_manager.py uses "train", "valid", "test" as split folders
        split_name_for_dir = {
            "train": "train",
            "val": "valid",
            "valid": "valid",
            "test": "test",
        }.get(split, split)

        candidate = cache_dir / dataset_name / split_name_for_dir / cache_sig / "meta" / "index.csv"
        if candidate.exists():
            return candidate

    return None


def _compute_label_stats_from_manifest(manifest_path: Path) -> Optional[Dict[str, Any]]:
    """
    Read manifest CSV and compute global + per-project label stats.
    Expects a 'label' column (or 'target' as fallback) and optional 'project'.
    """
    import csv
    from collections import Counter

    labels: List[int] = []
    projects: List[Tuple[str, int]] = []

    if not manifest_path.exists():
        print(f"[SplitCheck] manifest not found: {manifest_path}")
        return None

    with manifest_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            lbl_str = row.get("label", row.get("target", ""))
            if lbl_str in ("", None):
                continue
            try:
                lbl = int(lbl_str)
            except ValueError:
                continue
            labels.append(lbl)

            proj = (row.get("project") or "").strip()
            if proj:
                projects.append((proj, lbl))

    if not labels:
        return None

    n = len(labels)
    pos = sum(1 for x in labels if x == 1)
    neg = n - pos
    pos_frac = pos / float(n)

    stats: Dict[str, Any] = {
        "N": n,
        "pos": pos,
        "neg": neg,
        "pos_frac": pos_frac,
    }

    if projects:
        proj_total = Counter(p for p, _ in projects)
        proj_pos = Counter(p for p, lbl in projects if lbl == 1)
        stats["projects"] = {
            proj: {
                "total": proj_total[proj],
                "pos": proj_pos.get(proj, 0),
                "pos_frac": proj_pos.get(proj, 0) / float(proj_total[proj]),
            }
            for proj in proj_total.keys()
        }

    return stats

def _compute_label_stats_from_index(index_path: Path) -> Optional[Dict[str, Any]]:
    """
    Read cache index.csv and compute global + per-project label stats.
    Requires that 'label' and (optionally) 'project' columns were added in CacheManager.put().
    """
    import csv
    from collections import Counter

    labels: List[int] = []
    projects: List[Tuple[str, int]] = []

    if not index_path.exists():
        print(f"[SplitCheck] index.csv not found: {index_path}")
        return None

    with index_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            lbl_str = row.get("label", "")
            if lbl_str in ("", None):
                continue
            try:
                lbl = int(lbl_str)
            except ValueError:
                continue
            labels.append(lbl)

            proj = (row.get("project") or "").strip()
            if proj:
                projects.append((proj, lbl))

    if not labels:
        return None

    n = len(labels)
    pos = sum(1 for x in labels if x == 1)
    neg = n - pos
    pos_frac = pos / float(n)

    stats: Dict[str, Any] = {
        "N": n,
        "pos": pos,
        "neg": neg,
        "pos_frac": pos_frac,
    }

    if projects:
        proj_total = Counter(p for p, _ in projects)
        proj_pos = Counter(p for p, lbl in projects if lbl == 1)
        stats["projects"] = {
            proj: {
                "total": proj_total[proj],
                "pos": proj_pos.get(proj, 0),
                "pos_frac": proj_pos.get(proj, 0) / float(proj_total[proj]),
            }
            for proj in proj_total.keys()
        }

    return stats



def _print_manifest_cache_label_alignment(
    split: str,
    manifest_path: Optional[Path],
    index_path: Optional[Path],
) -> None:
    """
    Print global + per-project label stats for:
      • manifest (function_id,label,project,...)
      • cache index.csv (row_key,label,function_id,project,...)
    and show simple diffs.
    """
    print(f"\n[SplitCheck] ===== split={split} =====")

    # --- Manifest stats ---
    m_stats = None
    if manifest_path is None:
        print("[SplitCheck] manifest: not provided")
    else:
        m_stats = _compute_label_stats_from_manifest(manifest_path)
        if m_stats is None:
            print(f"[SplitCheck] manifest: {manifest_path} → no usable labels")
        else:
            print(
                f"[SplitCheck] manifest: "
                f"N={m_stats['N']} "
                f"pos={m_stats['pos']} "
                f"neg={m_stats['neg']} "
                f"pos_frac={m_stats['pos_frac']:.4f}"
            )

    # --- Cache index stats ---
    i_stats = None
    if index_path is None:
        print("[SplitCheck] cache index: no index path available")
    else:
        i_stats = _compute_label_stats_from_index(index_path)
        if i_stats is None:
            print(f"[SplitCheck] cache index: {index_path} → no usable labels")
        else:
            print(
                f"[SplitCheck] cache index: "
                f"N={i_stats['N']} "
                f"pos={i_stats['pos']} "
                f"neg={i_stats['neg']} "
                f"pos_frac={i_stats['pos_frac']:.4f}"
            )

    # --- Diff summary ---
    if m_stats and i_stats:
        diff_N = i_stats["N"] - m_stats["N"]
        diff_pos = i_stats["pos"] - m_stats["pos"]
        print(
            f"[SplitCheck] diff (cache - manifest): "
            f"N={diff_N:+d}, pos={diff_pos:+d}"
        )

        # Optional: per-project comparison if both sides have it
        if "projects" in m_stats and "projects" in i_stats:
            print("[SplitCheck] per-project pos_frac (manifest → cache):")
            all_projects = sorted(
                set(m_stats["projects"].keys()) | set(i_stats["projects"].keys())
            )
            for proj in all_projects:
                m_p = m_stats["projects"].get(proj)
                i_p = i_stats["projects"].get(proj)
                if not m_p and not i_p:
                    continue

                def _fmt(p):
                    if not p:
                        return "N/A"
                    return f"{p['pos']}/{p['total']} ({p['pos_frac']:.4f})"

                print(
                    f"  {proj:20s}: "
                    f"manifest={_fmt(m_p)} | "
                    f"cache={_fmt(i_p)}"
                )

def _probe_loader_label_stats(loader, split: str, max_batches: int = 16) -> None:
    """
    Probe a DataLoader and print label stats (and per-project stats if available).

    • Looks at batch.y (graph labels).
    • Tries to read project info from:
        - batch.project  (if present, per-graph)
        - batch.manifest_row (list of dicts with 'project' key)
    • Stops after `max_batches` batches to avoid scanning the whole split.
    """
    from collections import Counter
    import math

    if loader is None:
        print(f"[LoaderCheck] split={split}: loader is None")
        return

    all_labels: list[int] = []
    proj_pairs: list[tuple[str, int]] = []

    n_batches = 0

    for b_idx, batch in enumerate(loader):
        n_batches += 1

        # --- labels (required) ---
        y = getattr(batch, "y", None)
        if y is None:
            continue

        y_list = y.detach().cpu().view(-1).tolist()
        all_labels.extend(y_list)

        # --- try direct batch.project ---
        proj_attr = getattr(batch, "project", None)
        if proj_attr is not None:
            # Often collated as list/tuple of length == num_graphs
            if isinstance(proj_attr, (list, tuple)):
                if len(proj_attr) == len(y_list):
                    for lbl, proj in zip(y_list, proj_attr):
                        proj_str = str(proj).strip()
                        if proj_str:
                            proj_pairs.append((proj_str, int(lbl)))
                else:
                    # If shape mismatch, just ignore project here
                    pass
            else:
                # Single project for the whole batch
                proj_str = str(proj_attr).strip()
                if proj_str:
                    for lbl in y_list:
                        proj_pairs.append((proj_str, int(lbl)))

        else:
            # --- fallback: batch.manifest_row (list of dicts) ---
            mrows = getattr(batch, "manifest_row", None)
            if isinstance(mrows, (list, tuple)) and len(mrows) == len(y_list):
                for lbl, row in zip(y_list, mrows):
                    proj_str = ""
                    try:
                        proj_str = str(row.get("project") or "").strip()
                    except Exception:
                        proj_str = ""
                    if proj_str:
                        proj_pairs.append((proj_str, int(lbl)))

        if b_idx + 1 >= max_batches:
            break

    if not all_labels:
        print(f"[LoaderCheck] split={split}: no labels found in first {n_batches} batches")
        return

    N = len(all_labels)
    pos = sum(1 for x in all_labels if x == 1)
    neg = N - pos
    pos_frac = pos / float(N) if N > 0 else math.nan

    print(
        f"\n[LoaderCheck] split={split}: "
        f"batches_scanned={n_batches} "
        f"N={N} pos={pos} neg={neg} pos_frac={pos_frac:.4f}"
    )

    if proj_pairs:
        proj_total = Counter(p for p, _ in proj_pairs)
        proj_pos = Counter(p for p, lbl in proj_pairs if lbl == 1)

        print(f"[LoaderCheck] split={split}: per-project pos_frac (approx, first {N} graphs):")
        for proj in sorted(proj_total.keys()):
            t = proj_total[proj]
            p = proj_pos.get(proj, 0)
            frac = p / float(t) if t > 0 else 0.0
            print(f"  {proj:20s}: {p}/{t} ({frac:.4f})")
    else:
        print(f"[LoaderCheck] split={split}: no project info on batches (project/manifest_row missing)")


# ────────────────────────────────────────────
# Self-paced curriculum helpers (SPLVD-style)
# ────────────────────────────────────────────
# ────────────────────────────────────────────
# Self-paced curriculum helpers (SPLVD-style)
# ────────────────────────────────────────────
def compute_family_difficulty(
    model,
    dataset,
    rows,
    device,
    T: float = 1.0,
    batch_size: Optional[int] = None,
    num_workers: Optional[int] = None,
    max_batches: Optional[int] = None,
    debug_sleep: float = 0.0,
):
    """
    Compute per-family difficulty scores for self-paced curriculum.

    Current Devign normfunc setup (no mutants yet):

      • One function_id == one family.
      • `rows` is the manifest row list (e.g. train_ds.rows).
      • family_id is defined as _coerce_index_label(function_id).

    Difficulty for a family is:
        diff = 1.0 - min(1.0, 2 * |mean_p - 0.5|)
    so families with p ~ 0.5 are "hard", and with p near 0 or 1 are "easy".
    """
    from collections import defaultdict
    import time

    # ---- Safety checks on dataset/rows ----
    if dataset is None:
        print("[Curriculum][WARN] compute_family_difficulty: dataset is None; returning empty difficulty map.")
        return {}

    if rows is None:
        print("[Curriculum][WARN] compute_family_difficulty: rows is None; returning empty difficulty map.")
        return {}

    num_samples = len(rows)
    if num_samples == 0:
        print("[Curriculum][WARN] compute_family_difficulty: rows is empty; returning empty difficulty map.")
        return {}

    # Helper: extract a stable family ID from a manifest row
    # CURRENT PROJECT: family_id ≡ function_id (normalized by _coerce_index_label).
    def _row_to_family_id(row, idx: int):
        """
        row: manifest row (dict-like or object)
        idx: fallback numeric index
        """
        func_id = None

        # Manifest rows look like: function_id,label,project,orig_index
        try:
            if isinstance(row, dict):
                func_id = row.get("function_id", None)
            else:
                # pandas / SimpleNamespace style
                if hasattr(row, "function_id"):
                    func_id = getattr(row, "function_id")
                elif hasattr(row, "get"):
                    func_id = row.get("function_id", None)
        except Exception:
            func_id = None

        if not func_id:
            func_id = idx  # very last fallback

        # Same normalization as collapse/cached family utilities
        try:
            fam_norm = _coerce_index_label(str(func_id))
        except Exception:
            fam_norm = str(func_id)

        return fam_norm

    # ---- Build a simple sequential loader to align indices ↔ rows ----
    from torch_geometric.loader import DataLoader as GeoDataLoader

    # Batch size: prefer explicit argument, otherwise default
    if batch_size is not None and batch_size > 0:
        base_bs = int(batch_size)
    else:
        base_bs = 256

    # Num workers: prefer explicit num_workers; default to 0 for deterministic scan
    if num_workers is None:
        num_workers = 0
    else:
        num_workers = int(num_workers)

    simple_loader = GeoDataLoader(
        dataset,
        batch_size=base_bs,
        shuffle=False,
        num_workers=num_workers,
        collate_fn=graph_collate,
    )

    # ---- Run model over all train graphs and collect per-family probs ----
    model.eval()
    family_to_probs: Dict[Any, List[float]] = defaultdict(list)

    with torch.no_grad(), autocast_ctx(False):
        global_idx = 0  # index into rows / dataset

        for batch_idx, batch in enumerate(simple_loader):
            b = batch.to(device, non_blocking=True)

            out = model(b)
            logits = out["logits"] if isinstance(out, dict) else out
            probs = _probs_from_logits_binary(logits, T=T).detach().cpu().view(-1)

            batch_n = int(probs.shape[0])
            for j in range(batch_n):
                if global_idx >= num_samples:
                    break

                row = rows[global_idx]
                fam_id = _row_to_family_id(row, global_idx)
                family_to_probs[fam_id].append(float(probs[j]))
                global_idx += 1

            if max_batches is not None and (batch_idx + 1) >= max_batches:
                break

    # ---- Convert family→probs into family→difficulty ----
    family_difficulty: Dict[Any, float] = {}
    for fid, plist in family_to_probs.items():
        if not plist:
            continue

        m = float(sum(plist) / float(len(plist)))
        # difficulty ∈ [0,1], max when m ≈ 0.5
        diff = 1.0 - min(1.0, abs(m - 0.5) * 2.0)
        family_difficulty[fid] = diff

    if debug_sleep > 0.0:
        time.sleep(debug_sleep)

    return family_difficulty


# ────────────────────────────────────────────
# Run — cache-only Devign runner
# ────────────────────────────────────────────
# ────────────────────────────────────────────
# Run — cache-only Devign runner + self-paced curriculum
# ────────────────────────────────────────────
def run(args):
    """
    End-to-end runner using ONLY pre-built cache_manager output.
    """
    # ----- imports kept local to avoid polluting global namespace -----
    import os
    import math
    import json
    import time
    import numpy as np
    from pathlib import Path
    from collections import defaultdict as _dd
    from torch.optim import AdamW
    from torch.utils.data import SubsetRandomSampler, Dataset, RandomSampler
    from torch_geometric.loader import DataLoader as GeoDataLoader

    # ─────────────────────────────────────────────
    # Quick manifest → cache index label alignment
    # ─────────────────────────────────────────────
    try:
        split_to_manifest = {
            "train": Path(args.train_manifest) if getattr(args, "train_manifest", None) else None,
            "val":   Path(args.val_manifest)   if getattr(args, "val_manifest", None)   else None,
            "test":  Path(args.test_manifest)  if getattr(args, "test_manifest", None)  else None,
        }

        for split, manifest_path in split_to_manifest.items():
            if manifest_path is None:
                continue

            index_path = _infer_index_path_from_args_for_split(args, split)
            _print_manifest_cache_label_alignment(split, manifest_path, index_path)
    except Exception as e:
        print(f"[SplitCheck] Warning: label alignment check failed: {e}")

    # ----- small logger helper (tqdm-safe) -----
    LOG_LEVEL = str(getattr(args, "log_level", "info")).lower()

    def log(*a, lvl="info"):
        order = {"error": 0, "warn": 1, "info": 2, "debug": 3}
        if order.get(lvl, 2) <= order.get(LOG_LEVEL, 2):
            try:
                print(*a)
            except Exception:
                pass

    debug_sleep = float(getattr(args, "debug_sleep", 0.0) or 0.0)

    # ---------------- SEED + DEVICE + AMP ----------------
    set_seed(int(getattr(args, "seed", 42)))

    use_cuda = (not bool(getattr(args, "no_cuda", False))) and torch.cuda.is_available()
    device = torch.device("cuda" if use_cuda else "cpu")

    if device.type == "cuda":
        props = torch.cuda.get_device_properties(0)
        log(f"[Device] {props.name} | cc {props.major}.{props.minor} | {props.total_memory/1e9:.1f} GB")
        try:
            torch.backends.cudnn.benchmark = True
            torch.backends.cuda.matmul.allow_tf32 = True
            try:
                torch.set_float32_matmul_precision("high")
            except Exception:
                pass
        except Exception:
            pass
    else:
        log("[Device] CPU")

    amp = (not bool(getattr(args, "no_amp", False))) and (device.type == "cuda")

    # AMP context
    try:
        from torch.cuda.amp import GradScaler as _CudaGradScaler, autocast as _cuda_autocast
    except Exception:
        _CudaGradScaler, _cuda_autocast = None, None
    try:
        from torch import autocast as _torch_autocast
    except Exception:
        _torch_autocast = None

    GradScaler = _CudaGradScaler
    scaler = GradScaler(enabled=amp) if GradScaler is not None else None

    if "autocast_ctx" not in globals():
        from contextlib import contextmanager

        @contextmanager
        def autocast_ctx(enabled: bool):
            if not enabled:
                yield
                return
            if _torch_autocast is not None:
                with _torch_autocast("cuda", enabled=True):
                    yield
            elif _cuda_autocast is not None:
                with _cuda_autocast(enabled=True):
                    yield
            else:
                yield

        globals()["autocast_ctx"] = autocast_ctx

    # keep thread oversubscription down
    os.environ.setdefault("OMP_NUM_THREADS", "1")
    os.environ.setdefault("MKL_NUM_THREADS", "1")
    try:
        torch.set_num_threads(1)
    except Exception:
        pass

    # ----- basic train hyperparams defaults -----
    if not hasattr(args, "clip_grad"):
        args.clip_grad = 1.0
    if not hasattr(args, "lr"):
        args.lr = 1e-4
    if not hasattr(args, "weight_decay"):
        args.weight_decay = 0.01
    if not hasattr(args, "warmup_steps"):
        args.warmup_steps = 0
    if not hasattr(args, "epochs"):
        args.epochs = 40
    if not hasattr(args, "accum_steps"):
        args.accum_steps = 1

    # ---------------- LAYOUT + CACHE RESOLUTION ----------------
    layout = _get_devign_layout(args)

    # Setup file logging
    log_file = layout["model_dir"] / "train.log"
    import logging
    for handler in logging.root.handlers[:]:
        logging.root.removeHandler(handler)
    logging.basicConfig(filename=str(log_file), level=logging.INFO, format="%(asctime)s %(message)s")

    log(f"[Setup] Output Directory: {layout['model_dir']}")

    cache_root = (
        Path(args.cache_dir)
        if getattr(args, "cache_dir", None)
        else Path(os.path.join(getattr(args, "train_json_root", "."), "..", "cache_devign"))
    ).resolve()

    dataset_name = str(getattr(args, "dataset_name", "devign"))
    cache_signature = str(getattr(args, "cache_signature", "")).strip()
    if not cache_signature:
        raise RuntimeError("args.cache_signature is required.")

    def _split_dir(split: str) -> Path:
        return cache_root / dataset_name / split / cache_signature

    train_cache_dir = _split_dir("train")
    val_cache_dir   = _split_dir("valid")
    test_cache_dir  = _split_dir("test")

    for d in (train_cache_dir, val_cache_dir, test_cache_dir):
        if not d.exists():
            if "valid" in str(d):
                alt = _split_dir("validation")
                if alt.exists():
                    val_cache_dir = alt
                    continue
            raise RuntimeError(f"Cache split directory not found: {d}")

    log(f"[CACHE] root={cache_root}")
    log(f"[CACHE] dataset={dataset_name} signature={cache_signature}")

    # ---------------- LOAD CACHE SIGNATURE & RESOLVE VOCAB ----------------
    sig_path = train_cache_dir / "meta" / "signature.json"
    if not sig_path.exists():
        raise RuntimeError(f"Cache signature file not found: {sig_path}")

    with open(sig_path, "r") as f:
        cache_sig_data = json.load(f)

    # ---------------- RESOLVE VOCAB DIR ----------------
    sig_vocab_dir = cache_sig_data.get("vocab_dir", "") or ""
    if not getattr(args, "vocab_dir", "") and sig_vocab_dir:
        args.vocab_dir = sig_vocab_dir

    vocab_info = ensure_vocabs(args, layout, train_ds=None)
    node_vocab = vocab_info["node_vocab"]
    devign_rel_vocab = vocab_info["devign_rel_vocab"]
    num_node_tokens = len(node_vocab)

    args._node_vocab_for_check = node_vocab
    args.devign_rel_vocab = devign_rel_vocab

    log(
        f"[Setup] Vocab loaded from {vocab_info['vocab_dir']}: "
        f"node_types={num_node_tokens} devign_keys={sorted(devign_rel_vocab.keys())}"
    )

    # ---------------- FEATURE DIM FROM CACHE SIGNATURE ----------------
    features_cfg = cache_sig_data.get("features", {}) or {}
    final_x_dim = int(features_cfg.get("final_x_dim") or 0)
    if final_x_dim <= 0:
        final_x_dim = num_node_tokens
        log(
            f"[CACHE] WARNING: 'final_x_dim' missing in signature.json; "
            f"falling back to final_x_dim={final_x_dim}"
        )

    cache_fusion_mode = str(features_cfg.get("fusion_mode", "none")).lower()
    cache_fused = bool(features_cfg.get("fused", cache_fusion_mode.startswith("early")))

    log(f"[CACHE] fusion_mode={cache_fusion_mode} | fused={cache_fused}")
    log(f"[CACHE] final_x_dim={final_x_dim} | node_vocab_size={num_node_tokens}")

    # ---------------- DATASETS (CachedDataset) ----------------
    train_ds = CachedDataset(train_cache_dir, manifest_path=getattr(args, "train_manifest", None))
    val_ds   = CachedDataset(val_cache_dir,   manifest_path=getattr(args, "val_manifest", None))
    test_ds  = CachedDataset(test_cache_dir,  manifest_path=getattr(args, "test_manifest", None))

    # Optional fusion debug snapshot (one-time)
    if bool(getattr(args, "debug_fusion", False)):
        try:
            debug_fusion_snapshot(train_ds, args, max_nodes=3)
            # small pause so you can see this block clearly in logs
            if float(getattr(args, "debug_sleep", 0.0) or 0.0) > 0.0:
                import time
                time.sleep(float(getattr(args, "debug_sleep", 0.0)))
        except Exception as e:
            print(f"[FusionDBG] Error while inspecting fused features: {e}")

    if getattr(args, "do_audit", False):
        debug_cached_features(train_ds, num_graphs=5)
        debug_cached_features(val_ds,   num_graphs=5)

    # ---------------- APPLY COLLAPSE POLICIES ----------------
    print("\n" + "=" * 70)
    print("DATASET COLLAPSE POLICY")
    print("=" * 70)

    collapse_policy = getattr(args, "collapse_policy", "all")
    collapse_K      = int(getattr(args, "collapse_K", 2))
    collapse_seed   = int(getattr(args, "seed", 42))

    print("Collapse configuration:")
    print(f"  Policy: {collapse_policy}")
    print(f"  K (for k-per-family): {collapse_K}")
    print(f"  Seed: {collapse_seed}")

    # TRAIN
    print(f"\n[TRAIN SPLIT] before collapse: {len(train_ds)}")
    train_collapse_stats = _apply_collapse_policy(
        train_ds, policy=collapse_policy, K=collapse_K, seed=collapse_seed, verbose=True
    )
    validate_collapsed_dataset(train_ds, policy=collapse_policy, K=collapse_K, verbose=False)
    print(f"After collapse: {len(train_ds)}")

    # VAL
    val_collapse_policy = getattr(args, "val_collapse_policy", "all")
    print(f"\n[VAL SPLIT] before collapse: {len(val_ds)}")
    val_collapse_stats = _apply_collapse_policy(
        val_ds, policy=val_collapse_policy, K=collapse_K, seed=collapse_seed, verbose=True
    )
    validate_collapsed_dataset(val_ds, policy=val_collapse_policy, K=collapse_K, verbose=False)
    print(f"After collapse: {len(val_ds)}")

    # TEST
    test_collapse_policy = getattr(args, "test_collapse_policy", "all")
    print(f"\n[TEST SPLIT] before collapse: {len(test_ds)}")
    test_collapse_stats = _apply_collapse_policy(
        test_ds, policy=test_collapse_policy, K=collapse_K, seed=collapse_seed, verbose=True
    )
    validate_collapsed_dataset(test_ds, policy=test_collapse_policy, K=collapse_K, verbose=False)
    print(f"After collapse: {len(test_ds)}")

    args._collapse_metadata = {"train": train_collapse_stats, "val": val_collapse_stats, "test": test_collapse_stats}

    # ---------------- CLASS STATS / BASE RATE ----------------
    n_pos, n_neg, base_rate = _compute_class_stats_from_manifest_rows(train_ds.rows)
    log(f"[ClassStats][TRAIN] n_pos={n_pos} n_neg={n_neg} base_rate={base_rate:.4f} (≈{n_pos}/{n_pos+n_neg})")

    if not hasattr(args, "pos_weight") or float(args.pos_weight) <= 0.0:
        if n_pos > 0:
            args.pos_weight = max(1.0, float(n_neg) / float(n_pos))
        else:
            args.pos_weight = 1.0
    log(f"[LossConfig] pos_weight={float(args.pos_weight):.4f}")

    # ---------------- DYNAMIC FAMILY & CURRICULUM DETECTION ----------------
    # Automatically scan for mutants. If none found, disable complexity.
    
    family_index = _dd(list)
    row_fids = []
    has_families = False
    
    # Helper to extract ID safely
    def _get_fid(row, i):
        fid = row.get("fid") or row.get("family_id") or row.get("function_id") or row.get("orig_index")
        if fid is None: fid = i
        return str(fid)

    # Build family map
    for idx, row in enumerate(train_ds.rows):
        fid = _get_fid(row, idx)
        # Normalize to int hash for stability
        try:
            fid_int = int(fid)
        except:
            fid_int = int(hash(str(fid)) & 0x7FFFFFFF)
        
        row_fids.append(fid_int)
        family_index[fid_int].append(idx)

    family_ids = sorted(family_index.keys())
    
    # Analyze structure
    max_family_size = max(len(v) for v in family_index.values()) if family_index else 0
    num_multi_member = sum(1 for v in family_index.values() if len(v) > 1)
    has_mutants = num_multi_member > 0
    has_families = len(family_ids) > 0
    # Auto-Configure Sampler
    requested_k = int(getattr(args, "family_members_k", 1))
    use_curriculum = str(getattr(args, "curriculum", "none")).lower() == "selfpaced"
    
    if has_mutants:
        print(f"[AutoDetect] Found {num_multi_member} families with mutants (Max size: {max_family_size}).")
        if requested_k <= 1:
            print(f"[AutoDetect] Upgrading family_members_k to 2 (Contrastive Learning Enabled).")
            family_k = 2
        else:
            family_k = requested_k
        use_family_sampler = True
        print(f"[Config] Using FamilyBatchSampler with k={family_k}")
    else:
        print(f"[AutoDetect] No mutants found (Max family size: {max_family_size}). Originals only.")
        if requested_k > 1:
            print(f"[AutoDetect] Downgrading family_members_k to 1 (no mutants available).")
        family_k = 1
        use_family_sampler = False
        # IMPORTANT: If no mutants, force curriculum OFF because curriculum assumes families.
        if use_curriculum:
             print(f"[Config] Disabling Curriculum because dataset has no families/mutants.")
             use_curriculum = False
        print(f"[Config] Using Standard Shuffle Sampler (Faster)")

    # Curriculum Setup (if enabled)
    start_frac = float(getattr(args, "curriculum_start_frac", 0.3))
    end_frac   = float(getattr(args, "curriculum_end_frac", 1.0))
    family_difficulty = {}
    
    if use_curriculum:
        family_difficulty = {fid: 0.0 for fid in family_ids}
        print(f"[Curriculum] Self-Paced Learning Enabled (Start: {start_frac:.2f}, End: {end_frac:.2f})")
    else:
        print("[Curriculum] Disabled.")

    # ---------------- DATALOADERS ----------------
    num_workers      = int(getattr(args, "num_workers", 4))
    eval_num_workers = int(getattr(args, "eval_num_workers", num_workers))
    batch_size       = int(getattr(args, "batch_size", 64))
    train_batch_size = getattr(args, "train_batch_size", None)
    if train_batch_size is not None and int(train_batch_size) > 0:
        bs_train = int(train_batch_size)
    else:
        bs_train = batch_size
    eval_batch_size  = int(getattr(args, "eval_batch_size", batch_size))
    pin_mem = device.type == "cuda"

    base_train_loader = None
    train_loader = None

    # Tiny wrapper dataset for curriculum subsets
    class _SubsetCachedDataset(Dataset):
        def __init__(self, base_ds, indices):
            self.base_ds = base_ds
            self.indices = list(indices)
            self.rows = [base_ds.rows[i] for i in self.indices]
        def __len__(self):
            return len(self.indices)
        def __getitem__(self, idx):
            return self.base_ds[self.indices[idx]]

    # LOGIC BRANCHING FOR LOADER TYPE
    if use_family_sampler and not use_curriculum:
        # Case A: Mutants exist, No Curriculum -> Static Family Sampler
        train_sampler = FamilyBatchSampler(
            train_ds.rows,
            batch_size=bs_train,
            num_members_per_family=family_k,
            seed=int(getattr(args, "seed", 42)),
            drop_last=True,
        )
        train_loader = GeoDataLoader(
            train_ds,
            batch_sampler=train_sampler,
            num_workers=num_workers,
            collate_fn=graph_collate,
            pin_memory=pin_mem,
        )
        base_train_loader = train_loader

    elif use_family_sampler and use_curriculum:
        # Case B: Mutants exist + Curriculum -> Epoch-specific loader (built inside loop)
        train_loader = None
        base_train_loader = None # Will probe later manually
        
    elif not use_family_sampler and use_curriculum:
        # Case C: No Mutants + Curriculum -> Epoch-specific subset sampler (built inside loop)
        # We need a dummy base loader for probing
        train_loader = None
        base_train_loader = None

    else:
        # Case D: No Mutants, No Curriculum (Standard Baseline) -> Plain Shuffle
        train_loader = GeoDataLoader(
            train_ds,
            batch_size=bs_train,
            shuffle=True,
            num_workers=num_workers,
            collate_fn=graph_collate,
            pin_memory=pin_mem,
        )
        base_train_loader = train_loader

    # Probe a base batch (Safe Check)
    if base_train_loader is not None:
        try:
            first_batch = next(iter(base_train_loader))
            print("[DEBUG] first_batch.x.shape", first_batch.x.shape)
            print("[DEBUG] first_batch.y.shape", first_batch.y.shape)
        except Exception as e:
            print(f"[DEBUG] Failed to probe first batch: {e}")
    elif use_curriculum:
        # If curriculum, base_loader is None, so probe manually
        try:
            dummy_loader = GeoDataLoader(train_ds, batch_size=2, shuffle=True, collate_fn=graph_collate)
            first_batch = next(iter(dummy_loader))
            print("[DEBUG] (Curriculum Probe) first_batch.x.shape", first_batch.x.shape)
        except Exception:
            pass

    val_loader = GeoDataLoader(
        val_ds,
        batch_size=eval_batch_size,
        shuffle=False,
        num_workers=eval_num_workers,
        collate_fn=graph_collate,
        pin_memory=pin_mem,
    )
    test_loader = GeoDataLoader(
        test_ds,
        batch_size=eval_batch_size,
        shuffle=False,
        num_workers=eval_num_workers,
        collate_fn=graph_collate,
        pin_memory=pin_mem,
    )

    try:
        if base_train_loader: _probe_loader_label_stats(base_train_loader, "train", max_batches=16)
    except Exception:
        pass
    try:
        _probe_loader_label_stats(val_loader, "val", max_batches=16)
    except Exception:
        pass
    try:
        _probe_loader_label_stats(test_loader, "test", max_batches=16)
    except Exception:
        pass

    # ... after train_loader is created, before training loop

    # Fusion debugging: inspect a single batch and optionally exit
    if getattr(args, "debug_fusion", False):
        try:
            print("\n[FusionDBG] debug_fusion=True → inspecting fused features from train_loader")
            _debug_fusion_on_batch(
                loader=train_loader,
                node_vocab=node_vocab,
                final_x_dim=final_x_dim,
                device=device,
                max_nodes=8,
                max_dims=8,
            )
        except Exception as e:
            print(f"[FusionDBG] Error while inspecting fusion: {e}")

        # # Option A: exit after debugging (safer first pass)
        # print("[FusionDBG] Exiting after fusion debug as requested.")
        # return

        print("[FusionDBG] Continuing training after fusion debug.")

    # ---------------- EXPERIMENT CONFIG ----------------
    experiment_config = {
        "timestamp": datetime.now().isoformat(timespec="seconds"),
        "model": str(getattr(args, "model", "devign")),
        "backbone": str(getattr(args, "backbone", "transformer")),
        "hidden_dim": int(getattr(args, "hidden_dim", 256)),
        "layers": int(getattr(args, "layers", 8)),
        "dropout": float(getattr(args, "dropout", 0.2)),
        "batch_size": bs_train,
        "lr": float(getattr(args, "lr", 1e-4)),
        "seed": int(getattr(args, "seed", 42)),
        "cache_signature": cache_signature,
        "curriculum": str(getattr(args, "curriculum", "none")),
        "curriculum_start_frac": float(getattr(args, "curriculum_start_frac", 0.3)),
        "curriculum_end_frac": float(getattr(args, "curriculum_end_frac", 1.0)),
    }
    args._experiment_config = experiment_config
    log(f"[Experiment] {experiment_config}", lvl="debug")

    # ---------------- MODEL BUILD ----------------
    raw_in = final_x_dim
    print("\n" + "=" * 70)
    print("MODEL INITIALIZATION")
    print("=" * 70)
    print(f"Cache feature dim: {raw_in}")
    print(f"Model will receive: {raw_in}-dim inputs")
    print("=" * 70 + "\n")

    model = make_model(
        args,
        raw_feature_dim=raw_in,
        num_node_tokens=max(1, num_node_tokens),
        cache_fused=cache_fused,
    ).to(device)


    print("[Debug] Registering per-layer gradient hooks...")
    register_grad_debug_hooks(model)

    if debug_sleep > 0.0:
        time.sleep(debug_sleep)
    else:
        time.sleep(7.0)
    print(f"✅ Model initialized: {args.model}")

    # ─────────────────────────────────────────────
    # Enable gated fusion debug if requested (--debug-gate)
    # ─────────────────────────────────────────────
    try:
        if bool(getattr(args, "debug_gate", False)):
            gate_sleep = float(getattr(args, "debug_gate_sleep", 0.0) or 0.0)

            # For Devign, the gated fusion lives in model.input_proj
            if hasattr(model, "input_proj") and isinstance(model.input_proj, RobustGatedFusion):
                model.input_proj.debug_gate = True
                model.input_proj.debug_sleep = gate_sleep
                print(
                    f"[GatedFusionDBG] Enabled gate debugging on model.input_proj "
                    f"(debug_gate=True, debug_sleep={gate_sleep:.2f}s)"
                )
            else:
                print(
                    "[GatedFusionDBG] debug_gate=True, but model.input_proj is missing "
                    "or not a RobustGatedFusion instance."
                )
    except Exception as e:
        print(f"[GatedFusionDBG] Failed to enable gate debug: {e}")


    # ─────────────────────────────────────────────
    # Enable gate regularizer if requested
    # ─────────────────────────────────────────────
    try:
        gate_reg_w = float(getattr(args, "gate_reg_w", 0.0) or 0.0)
        gate_target_mean = float(getattr(args, "gate_target_mean", 0.4))
        gate_min_std = float(getattr(args, "gate_min_std", 0.05))

        if gate_reg_w > 0.0 and hasattr(model, "input_proj") and isinstance(model.input_proj, RobustGatedFusion):
            model.input_proj.configure_gate_regularizer(
                enabled=True,
                target_mean=gate_target_mean,
                min_std=gate_min_std,
            )
            print(
                f"[GateReg] Enabled gate regularizer on model.input_proj: "
                f"w={gate_reg_w:.4f}, target_mean={gate_target_mean:.4f}, "
                f"min_std={gate_min_std:.4f}"
            )
        elif gate_reg_w > 0.0:
            print(
                "[GateReg] gate_reg_w > 0 but model.input_proj is missing "
                "or not a RobustGatedFusion instance. Gate regularizer disabled."
            )
    except Exception as e:
        print(f"[GateReg] Failed to configure gate regularizer: {e}")


    # Validation of model
    try:
        probe_loader = GeoDataLoader(
            train_ds,
            batch_size=2,
            shuffle=False,
            num_workers=0,
            collate_fn=graph_collate,
        )
        probe_batch = next(iter(probe_loader)).to(device, non_blocking=True)
        with torch.no_grad():
            _ = model(probe_batch)
        print("✅ [InitProbe] Lazy modules initialized successfully")
    except Exception as e:
        print(f"⚠️ [InitProbe] Init failed (non-fatal): {e}")

    # ---------------- OPTIMIZER + SCHEDULER (OneCycle) ----------------
    optimizer = AdamW(model.parameters(), lr=float(args.lr), weight_decay=float(args.weight_decay))

    accum_steps = max(1, int(getattr(args, "accum_steps", 1)))
    epochs = int(getattr(args, "epochs", 40))

    # For baseline stability: disable OneCycleLR and use constant LR
    scheduler = None
    print(f"[Scheduler] Disabled for baseline run. Using constant LR={float(args.lr):.2e}")


    # ---------------- OUTPUT DIRS ----------------
    ckpt_dir = layout["checkpoints"]
    results_dir = layout["results"]
    ckpt_dir.mkdir(parents=True, exist_ok=True)
    results_dir.mkdir(parents=True, exist_ok=True)

    # ---------------- TRAIN LOOP ----------------
    global_step = 0
    first_probe_done = False
    best_val_f1 = -1.0
    best_state = None
    best_thr = 0.5

    if getattr(args, "no_calibration", False):
        best_thr = float(getattr(args, "fixed_threshold", 0.5))
        print(f"[Config] Using Fixed Threshold: {best_thr}")

    print("\n" + "=" * 70)
    print("TRAINING")
    print("=" * 70)

    for epoch in range(epochs):
        print(f"\n----- Epoch {epoch+1}/{epochs} -----")

        # Reset gate stats at start of each epoch (if RobustGatedFusion present)
        try:
            if hasattr(model, "input_proj") and hasattr(model.input_proj, "reset_epoch_alpha_stats"):
                model.input_proj.reset_epoch_alpha_stats()
        except Exception as e:
            print(f"[GateEpochDBG] Failed to reset alpha stats: {e}")

        # ----- Build epoch-specific train loader (curriculum) -----
        if use_curriculum:
            if len(family_ids) == 0:
                raise RuntimeError("[Curriculum] No families found in train_ds.rows.")
    
            if epochs <= 1:
                frac = end_frac
            else:
                t = epoch / max(1, epochs - 1)
                frac = start_frac + (end_frac - start_frac) * t
            frac = max(0.0, min(1.0, frac))

            num_families = len(family_ids)
            num_active = max(1, int(round(frac * num_families)))

            # sort families by difficulty (lower = easier)
            sorted_fids = sorted(family_ids, key=lambda fid: family_difficulty.get(fid, 0.0))
            active_fids = set(sorted_fids[:num_active])

            print(
                f"[Curriculum] Epoch {epoch+1}: frac={frac:.3f} → "
                f"using {num_active}/{num_families} families"
            )

            if use_family_sampler:
                # Case B: Mutants + Curriculum
                active_rows = [
                    row for row, fid in zip(train_ds.rows, row_fids) if fid in active_fids
                ]
                epoch_sampler = FamilyBatchSampler(
                    active_rows,
                    batch_size=bs_train,
                    num_members_per_family=family_k,
                    seed=int(getattr(args, "seed", 42)),
                    drop_last=True,
                )
                epoch_train_loader = GeoDataLoader(
                    train_ds,
                    batch_sampler=epoch_sampler,
                    num_workers=num_workers,
                    collate_fn=graph_collate,
                    pin_memory=pin_mem,
                )
            else:
                # Case C: No Mutants + Curriculum (Subset Random)
                active_indices = []
                for fid in active_fids:
                    active_indices.extend(family_index.get(fid, []))
                if not active_indices:
                    active_indices = list(range(len(train_ds)))
                
                sampler = SubsetRandomSampler(active_indices)
                epoch_train_loader = GeoDataLoader(
                    train_ds,
                    batch_size=bs_train,
                    sampler=sampler,
                    num_workers=num_workers,
                    collate_fn=graph_collate,
                    pin_memory=pin_mem,
                )
        else:
            # Standard Shuffle (Case D or A)
            epoch_train_loader = base_train_loader

        # ----- Train epoch -----
        epoch_loss, global_step, first_probe_done = train_epoch_mutant_aware(
            model,
            epoch_train_loader,
            device,
            optimizer,
            scaler,
            amp,
            args,
            global_step=global_step,
            scheduler=scheduler,
            first_probe_done=first_probe_done,
        )


        print(f"[Epoch {epoch+1}] train_loss_total={epoch_loss:.4f}")

        # ----- Gate α epoch-level summary (train) -----
        try:
            if hasattr(model, "input_proj") and hasattr(model.input_proj, "get_epoch_alpha_stats"):
                gate_stats = model.input_proj.get_epoch_alpha_stats()
            else:
                gate_stats = None
        except Exception as e:
            print(f"[GateEpochDBG] Failed to read alpha stats: {e}")
            gate_stats = None

        if gate_stats is not None:
            print(
                "[GateEpochDBG] alpha (train): "
                f"mean={gate_stats['mean']:.4f} std={gate_stats['std']:.4f} "
                f"min={gate_stats['min']:.4f} max={gate_stats['max']:.4f} "
                f"batches={gate_stats['batches']}"
            )
            # Optional: reset ready for next epoch (or rely on reset at start)
            try:
                model.input_proj.reset_epoch_alpha_stats()
            except Exception as e:
                print(f"[GateEpochDBG] Failed to reset alpha stats after epoch: {e}")


        # Optional: per-epoch parameter norm summary
        if bool(getattr(args, "debug_param_norms", False)):
            try:
                debug_param_norms(model, top_k=8)
                if float(getattr(args, "debug_sleep", 0.0) or 0.0) > 0.0:
                    import time
                    time.sleep(float(getattr(args, "debug_sleep", 0.0)))
            except Exception as e:
                print(f"[ParamDBG] Error while computing param norms: {e}")


        # -------- VAL PROBABILITIES --------
        y_val, p_val, _ = collect_probs_with_T(
            model,
            val_loader,
            device,
            T=1.0,
            tta=0,
            tta_dropedge_p=0.0,
            tta_feat_noise_std=0.0,
        )

        try:
            if getattr(args, "debug_probs", False) and y_val.size and p_val.size:
                _dbg(
                    f"[VALCOLLECT] N={y_val.size} "
                    f"mean_p={float(p_val.mean()):.4f} std_p={float(p_val.std()):.4f}"
                )
        except Exception:
            pass

         # -------- Threshold logic --------
        no_calibration = bool(getattr(args, "no_calibration", False))

        if no_calibration:
            thr_epoch = float(getattr(args, "fixed_threshold", 0.5))
            print(f"[Calib] Using fixed threshold: {thr_epoch:.4f}")

        elif y_val.size == 0:
            print("[Calib] No validation data; reusing previous/best threshold.")
            thr_epoch = best_thr if best_thr is not None else float(getattr(args, "fixed_threshold", 0.5))

        elif getattr(args, "skip_calibration", False):
            thr_epoch = best_thr if best_thr is not None else float(getattr(args, "fixed_threshold", 0.5))
            print(f"[Calib] Skipping calibration; reusing thr={thr_epoch:.4f}")

        else:
            use_cfg = bool(getattr(args, "use_calib_config", False))
            if use_cfg:
                # Use the richer CalibConfig + calibrate_threshold path
                cfg = CalibConfig(
                    beta=float(getattr(args, "calib_beta", 1.0)),
                    min_precision=(
                        None
                        if float(getattr(args, "min_precision", 0.0)) <= 0.0
                        else float(getattr(args, "min_precision"))
                    ),
                    min_recall=(
                        None
                        if float(getattr(args, "min_recall", 0.0)) <= 0.0
                        else float(getattr(args, "min_recall"))
                    ),
                    max_pos_rate_over_base=float(getattr(args, "calib_max_pos_delta", 3.0)),
                    min_pos_frac=float(getattr(args, "calib_min_pos_frac", 0.0)),
                    min_prob_std=1e-3,
                )

                thr_epoch, calib_stats = calibrate_threshold(
                    y_true=y_val,
                    y_prob=p_val,
                    cfg=cfg,
                    base_rate=base_rate,
                )
            else:
                # Original simple F1 sweep
                thr_epoch, calib_stats = _find_best_f1_threshold(
                    y_val,
                    p_val,
                    min_pos_frac=float(getattr(args, "calib_min_pos_frac", 0.0)),
                )
                print(
                    f"[Calib] F1-sweep: thr={thr_epoch:.4f} f1={calib_stats['f1']:.4f} "
                    f"prec={calib_stats['prec']:.4f} rec={calib_stats['rec']:.4f}"
                )

            if debug_sleep > 0.0:
                time.sleep(debug_sleep)

        # -------- VAL METRICS --------
        val_metrics = evaluate(model, val_loader, device, threshold=thr_epoch, temperature=1.0)
        print(
            f"[VAL] epoch={epoch+1} "
            f"f1={val_metrics['f1']:.4f} "
            f"prec={val_metrics['prec']:.4f} "
            f"rec={val_metrics['rec']:.4f} "
            f"auc={val_metrics['auc']:.4f}"
        )
        if debug_sleep > 0.0:
            time.sleep(debug_sleep)

        # -------- Curriculum difficulty update --------
        if use_curriculum and has_families:
            print(f"[Curriculum] Recomputing family difficulty after epoch {epoch+1}...")
            family_difficulty = compute_family_difficulty(
                model=model,
                dataset=train_ds,
                rows=train_ds.rows,
                device=device,
                T=float(getattr(args, "T", 1.0)),
                batch_size=eval_batch_size,
                num_workers=eval_num_workers,
                debug_sleep=debug_sleep,
            )

        # -------- CHECKPOINT --------
        if val_metrics["f1"] > best_val_f1:
            best_val_f1 = val_metrics["f1"]
            best_state = {
                "epoch": epoch,
                "model_state": model.state_dict(),
                "thr_best": float(thr_epoch),
                "val_metrics": val_metrics,
                "config": experiment_config,
            }
            if not getattr(args, "no_calibration", False):
                best_thr = float(thr_epoch)

            torch.save(best_state, ckpt_dir / "best.pt")
            print(f"[Checkpoint] Updated best.pt (F1={best_val_f1:.4f}, thr={best_thr:.4f})")

    # ---------------- FINAL TEST ----------------
    if best_state:
        model.load_state_dict(best_state["model_state"])
        best_thr = float(best_state["thr_best"])

    test_metrics = evaluate(model, test_loader, device, threshold=best_thr)
    print(
        f"\n[TEST] F1={test_metrics['f1']:.4f} "
        f"Prec={test_metrics['prec']:.4f} "
        f"Rec={test_metrics['rec']:.4f} "
        f"AUC={test_metrics['auc']:.4f} (thr={best_thr:.4f})"
    )

    # Save Summary
    summary = {
        "experiment": experiment_config,
        "best_val": best_state["val_metrics"] if best_state else {},
        "test": test_metrics,
        "best_thr": best_thr,
    }

    def _json_numpy_serializer(o):
        if isinstance(o, (np.int64, np.int32)):
            return int(o)
        if isinstance(o, (np.float32, np.float64)):
            return float(o)
        if isinstance(o, np.ndarray):
            return o.tolist()
        raise TypeError(f"Type {type(o)} not serializable")

    with open(results_dir / "test_metrics.json", "w") as f:
        json.dump(summary, f, indent=2, default=_json_numpy_serializer)

    print(f"[Results] Saved summary → {results_dir}/test_metrics.json")
# ────────────────────────────────────────────
# CLI — Minimal, Devign-focused (cache-consumer only)
# ────────────────────────────────────────────
import argparse

def build_parser():
    """
    Argument parser for the baseline Devign runner that CONSUMES a ready cache.

    What remains:
      • Model core/dims
      • Loader & training hyperparams
      • Calibration / temperature / TTA
      • Cache discovery (root + signature) OR explicit ZIPs
      • (Optional) manifests for family-aware sampling/metadata
      • Collapse policy (train-side row selection)

    Removed:
      • All GraphSON/vocab/SQLite/fusion/build-cache flags
      • Any text/CodeBERT fusion args (these are decided at cache build time)
    """
    parser = argparse.ArgumentParser(
        description="Devign runner (baseline) — trains from prebuilt cache (no GraphSON/SQLite here)",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        allow_abbrev=False,
    )

    # -------------------------------
    # Core model / dims (Devign only)
    # -------------------------------
    parser.add_argument("--model", type=str, default="devign", choices=["devign"])
    parser.add_argument("--num-classes", type=int, default=2, dest="num_classes")
    parser.add_argument("--hidden-dim",   type=int, default=384, dest="hidden_dim",
                        help="Backbone hidden size and readout width.")
    parser.add_argument("--layers",       type=int, default=8,
                        help="Number of Devign (message-passing) layers.")
    parser.add_argument("--dropout", type=float, default=0.20,
                        help="Dropout used in Devign layers / heads.")

    # -------------------------------
    # Cache consumption (pick ONE mode)
    # -------------------------------
    # Mode A: signature discovery (preferred when using standard layout)
    parser.add_argument("--cache-dir", type=str, required=False, default=None,
                        help="Cache root produced by cache_manager.py (e.g., .../cache_devign_v1).")
    parser.add_argument("--dataset-name", type=str, default="devign",
                        help="Dataset name used by cache_manager folder layout.")
    parser.add_argument("--cache-signature", type=str, default="",
                        help="16-hex signature folder (e.g., 4110578353421322). If empty, will auto-discover when unambiguous.")

    # Mode B (override): explicit ZIP paths per split
    parser.add_argument("--train-cache-zip", type=str, default="",
                        help="Override: full path to cache_train.zip.")
    parser.add_argument("--val-cache-zip",   type=str, default="",
                        help="Override: full path to cache_valid.zip.")
    parser.add_argument("--test-cache-zip",  type=str, default="",
                        help="Override: full path to cache_test.zip.")

    parser.add_argument(
    "--debug-fusion",
    action="store_true",
    help="Print a small sample of fused features (one-hot + CodeBERT) from the train cache and exit after debugging."
    )

    parser.add_argument(
        "--debug-gate",
        action="store_true",
        help="Enable RobustGatedFusion gate alpha debug prints."
    )

    parser.add_argument(
        "--debug-gate-sleep",
        type=float,
        default=0.0,
        help="Optional sleep (seconds) after each gate debug print to inspect output."
    )
    # -------------------------------
    # (Optional) manifests for sampler/metadata
    # -------------------------------
    parser.add_argument("--train-manifest", type=str, default="",
                        help="Optional manifest CSV to drive family-aware sampling / metadata.")
    parser.add_argument("--val-manifest",   type=str, default="")
    parser.add_argument("--test-manifest",  type=str, default="")

    # -------------------------------
    # Mutant-aware sampling
    # -------------------------------
    parser.add_argument("--family-members-k", type=int, default=1,
                        help="Members per family sampled into a batch (if family-aware sampler is enabled).")







    parser.add_argument("--max_nodes", type=int, default=512, help="Max nodes for dense batching (95th percentile)")


    # -------------------------------
    # Dataset collapse policy (training-time row selection)
    # -------------------------------
    parser.add_argument(
        "--collapse-policy", type=str, default="all",  # ← CHANGED: default to "all"
        choices=["all","none","orig","snap","k","k-per-family","k_per_family","kperfamily"],
        help="Row selection for TRAIN split (default: all = no filtering)."
    )
    parser.add_argument(
        "--collapse-K", type=int, default=1, dest="collapse_K",
        help="Max members per family for k-per-family policy."
    )
    parser.add_argument(
        "--val-collapse-policy", type=str, default="all",
        choices=["all","none","orig","snap","k","k-per-family"],
        help="Row selection for VAL split (default: all)."
    )
    parser.add_argument(
        "--test-collapse-policy", type=str, default="all",
        choices=["all","none","orig","snap","k","k-per-family"],
        help="Row selection for TEST split (default: all)."
    )
    # ... inside build_parser, near --supcon-w or --anti-collapse-w ...

    parser.add_argument(
        "--consistency-w",
        type=float,
        default=0.0,
        help="Weight for consistency loss across family members (0 = disabled).",
    )
    
    parser.add_argument(
        "--proto-w",
        type=float,
        default=0.0,
        help="Weight for prototype clustering loss (0 = disabled).",
    )



    # Curriculum / self-paced sampler
    parser.add_argument(
        "--curriculum",
        type=str,
        default="none",
        choices=["none", "selfpaced"],
        help="Self-paced/curriculum mode for family batching. 'none' = original sampler; 'selfpaced' = easy-to-hard families.",
    )
    parser.add_argument(
        "--curriculum-start-frac",
        type=float,
        default=0.3,
        help="Fraction of easiest families to use at epoch 0 when curriculum='selfpaced'.",
    )
    parser.add_argument(
        "--curriculum-end-frac",
        type=float,
        default=1.0,
        help="Final fraction of families (usually 1.0) by last epoch when curriculum='selfpaced'.",
    )



    parser.add_argument(
        "--sortpool-k", 
        type=int, 
        default=64,
        help="Number of top nodes to keep in SortPooling (k). Critical for avoiding tunnel vision."
    )

    # -------------------------------
    # Loader / workers
    # -------------------------------
    parser.add_argument("--batch-size",       type=int, default=192)
    parser.add_argument("--eval-batch-size",  type=int, default=256)
    parser.add_argument("--train-batch-size", type=int, default=None,
                        help="If set, overrides --batch-size for training only.")
    parser.add_argument("--num-workers",         type=int, default=32)
    parser.add_argument("--eval-num-workers",    type=int, default=32)
    parser.add_argument("--prefetch-factor",     type=int, default=2)
    parser.add_argument("--eval-prefetch-factor",type=int, default=2)
    parser.add_argument("--persistent-workers",        action="store_true")
    parser.add_argument("--eval-persistent-workers",   action="store_true")
    parser.add_argument("--loader-timeout", type=int, default=0)
    parser.add_argument("--mp-context", choices=["fork","forkserver","spawn"], default="forkserver")

    # -------------------------------
    # Train / schedules
    # -------------------------------
    parser.add_argument("--epochs", type=int, default=80)
    parser.add_argument("--accum-steps", type=int, default=1)
    parser.add_argument("--lr", type=float, default=5e-4)
    parser.add_argument("--weight-decay", type=float, default=0.01)
    parser.add_argument("--early-stop", type=int, default=0,
                        help="Stop after N epochs without val improvement (0=disabled).")
    parser.add_argument("--val-interval", type=int, default=1,
                        help="Validate every N epochs.")
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--no-progress", action="store_true",
                        help="Disable tqdm progress bars.")
    

    parser.add_argument(
        "--vocab-dir",
        type=str,
        default="",
        help=(
            "Directory containing node_vocab.* / edge_vocab.* / devign_rel_vocab.* "
            "produced by vocab_builder.py. "
            "If empty, the runner will fall back to the cache signature or DEVIGN_VOCAB_DIR."
        ),
    )


    # -------------------------------
    # Loss shaping (simple & safe)
    # -------------------------------
    # ---------- Loss / optimization ----------
    parser.add_argument(
        "--label-smoothing",
        type=float,
        default=0.0,
        help="Label smoothing for CE/BCE (0 = disabled).",
    )
    # +++ ADD THIS BLOCK +++
    parser.add_argument(
        "--pos-weight",
        type=float,
        default=0.0, 
        help="Manual positive class weight for BCE (0 = auto-calculate).",
    )
    # ++++++++++++++++++++++
    parser.add_argument(
        "--focal-gamma",
        type=float,
        default=0.0,
        help="Focal loss gamma (0 = disabled).",
    )
    parser.add_argument(
        "--max-pos-weight",
        type=float,
        default=1.0,
        help="Upper bound for positive-class weight in BCEWithLogits.",
    )

    # L2 penalty on delta logits (already used in train_epoch_mutant_aware via args.logit_l2)
    parser.add_argument(
        "--logit-l2",
        type=float,
        default=0.0,
        help="L2 penalty weight on delta logits (0 = disabled).",
    )

    # NEW: anti-collapse regularizer on delta.std()
    parser.add_argument(
        "--anti-collapse-w",
        type=float,
        default=0.0,
        help="Weight for anti-collapse penalty on delta.std() (0 = disabled).",
    )
    parser.add_argument(
        "--anti-collapse-target",
        type=float,
        default=0.5,
        help="Target std for delta in the anti-collapse penalty.",
    )

    parser.add_argument(
        "--supcon-w",
        type=float,
        default=0.0,
        help="Weight for Supervised Contrastive Loss (0 = disabled).",
    )
    parser.add_argument("--debug-train-probs", action="store_true")
    parser.add_argument("--debug-sleep", type=float, default=6.0)

    # -------------------------------
    # Gate regularizer (for RobustGatedFusion)
    # -------------------------------
    parser.add_argument(
        "--gate-reg-w",
        type=float,
        default=0.0,
        help="Weight for gate regularizer; 0.0 disables gate regularization."
    )
    parser.add_argument(
        "--gate-target-mean",
        type=float,
        default=0.4,
        help="Target mean of gate alpha for gate regularizer (e.g., 0.4)."
    )
    parser.add_argument(
        "--gate-min-std",
        type=float,
        default=0.05,
        help="Minimum std of gate alpha for gate regularizer (encourages non-collapsed gates)."
    )



    # -------------------------------
    # Warmup / stability
    # -------------------------------
    parser.add_argument("--warmup-frac", type=float, default=0.1,
                        help="Fraction of total steps to use for warmup (if --warmup-steps not set).")
    parser.add_argument("--warmup-steps", type=int, default=0,
                        help="Number of warmup steps (overrides --warmup-frac if > 0).")
    parser.add_argument("--clip-grad", type=float, default=1.0)

    # Small regularization during training
    parser.add_argument("--train-feat-noise-std", type=float, default=0.01,
                        help="Gaussian noise std on node features during TRAIN.")
    parser.add_argument("--dropedge-p", type=float, default=0.03,
                        help="Edge-drop prob during TRAIN (also used for TTA if set).")


    

    # -------------------------------
    # Calibration / temperature / TTA
    # -------------------------------
    parser.add_argument("--T", type=float, default=1.0,
                        help="Temperature used during training-time eval (if enabled).")
    parser.add_argument("--T-test", type=float, default=1.0, dest="T_test",
                        help="Temperature used during test-time evaluation.")
    parser.add_argument("--do-temperature", action="store_true",
                        help="Fit temperature on VAL before TEST.")
    parser.add_argument("--calib-beta", type=float, default=1.0, dest="calib_beta",
                        help="F-beta used in PR sweep during threshold calibration.")
    parser.add_argument("--thr-ema-alpha", type=float, default=0.8, dest="thr_ema_alpha",
                        help="EMA factor for running decision threshold (optional).")
    parser.add_argument("--min-precision", type=float, default=0.30,
                        help="Precision floor for threshold selection (if set).")
    parser.add_argument("--min-recall",    type=float, default=0.45,
                        help="Recall floor for threshold selection (if set).")
    parser.add_argument("--calib-max-pos-delta", type=float, default=0.40, dest="calib_max_pos_delta",
                        help="Clamp on positive rate vs. base during calibration.")
    parser.add_argument("--calib-min-pos-frac",  type=float, default=0.03,  dest="calib_min_pos_frac",
                        help="Minimum positive fraction allowed by calibrated threshold.")
    parser.add_argument(
        "--use-calib-config",
        action="store_true",
        help="Use CalibConfig + calibrate_threshold for VAL threshold selection "
             "instead of simple F1 sweep.",
    )


    # NEW: simple vanilla threshold mode
    parser.add_argument("--no-calibration", action="store_true",
                        help="Disable PR-based threshold calibration; use a fixed global threshold.")
    parser.add_argument("--fixed-threshold", type=float, default=0.5,
                        help="Decision threshold used when --no-calibration is set (vanilla ML style).")


    parser.add_argument("--tta", type=int, default=2,
                        help="# of stochastic TTA views to average at eval.")
    parser.add_argument("--tta-dropedge-p", type=float, default=0.0,
                        help="DropEdge probability for TTA.")
    parser.add_argument("--tta-feat-noise-std", type=float, default=0.0,
                        help="Feature-noise std for TTA.")



    # Backbone choice for Devign
    parser.add_argument(
        "--backbone",
        type=str,
        default="transformer",
        choices=["transformer", "resrgcn","sortpool","attention"],
        help="Backbone inside Devign: 'transformer' (UniMP-style) or 'resrgcn' (residual R-GCN) or 'sortpool' (SOTA).",
    )
    # -------------------------------
    # Device / misc
    # -------------------------------
    parser.add_argument("--no-amp", action="store_true",
                        help="Disable AMP even on CUDA.")
    parser.add_argument("--no-cuda", action="store_true",
                        help="Force CPU even if CUDA is available.")
    parser.add_argument("--output-dir", type=str, default="./results_devign")
    parser.add_argument("--quick-stats", dest="quick_stats", action="store_true",
                        help="Shorter eval prints.")
    parser.add_argument("--no-quick-stats", dest="quick_stats", action="store_false")
    parser.set_defaults(quick_stats=False)
    parser.add_argument("--audit", dest="do_audit", action="store_true",
                        help="Run additional coverage/consistency checks.")
    parser.add_argument("--no-audit", dest="do_audit", action="store_false")
    parser.set_defaults(do_audit=False)
    parser.add_argument("--detect-anomaly", action="store_true",
                        help="Enable torch.autograd anomaly detection (slow).")

    return parser


def main(argv=None):
    parser = build_parser()
    args = parser.parse_args(argv)

    # Devign is T=1 by design (no temporal); keep temps for eval logic.
    if args.T is None:      args.T = 1.0
    if args.T_test is None: args.T_test = 1.0

    # Hand off to runner (expects only cache-consumption fields).
    run(args)


if __name__ == "__main__":
    main()



"""
python 02_MPTCN_TTS_Devign.py \
    --model devign \
    --layers 8 \
    --hidden-dim 384 \
    --dropout 0.20 \
    --epochs 80 \
    --batch-size 64 \
    --num-workers 32 \
    --eval-num-workers 32 \
    --cache-dir "./Clean_exports/cache_devign_v2" \
    --dataset-name devign \
    --cache-signature "4110578353421322" \
    --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
    --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
    --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
    --persistent-workers \
    --eval-persistent-workers \
    --prefetch-factor 2 \
    --eval-prefetch-factor 2 \
    --dropedge-p 0.03 \
    --train-feat-noise-std 0.01 \
    --do-temperature \
    --calib-beta 1.5 \
    --no-calibration \
    --fixed-threshold 0.5 \
    --thr-ema-alpha 0.8 \
    --min-precision 0.30 \
    --min-recall 0.45 \
    --collapse-policy orig \
    --val-collapse-policy all \
    --test-collapse-policy all \
    --output-dir "./results_devign_originals_only"


python 02_MPTCN_TTS_Devign.py \
    --model devign \
    --layers 8 \
    --hidden-dim 768 \
    --dropout 0.20 \
    --cache-dir "./Clean_exports/cache_devign_v1" \
    --dataset-name devign \
    --cache-signature "4110578353421322" \
    --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
    --val-manifest "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
    --test-manifest "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
    --epochs 50 \
    --batch-size 32 \
    --lr 1e-4 \
    --warmup-steps 200 \
    --clip-grad 1.0 \
    --num-workers 8 \
    --eval-num-workers 8 \
    --persistent-workers \
    --eval-persistent-workers \
    --prefetch-factor 2 \
    --eval-prefetch-factor 2 \
    --dropedge-p 0.03 \
    --train-feat-noise-std 0.01 \
    --do-temperature \
    --calib-beta 1.5 \
    --thr-ema-alpha 0.8 \
    --min-precision 0.30 \
    --min-recall 0.45 \
    --output-dir "./results_devign_cache_v1" \
    --seed 42


python 02_MPTCN_TTS_Devign.py \
    --model devign \
    --layers 8 \
    --hidden-dim 384 \
    --dropout 0.20 \
    --epochs 80 \
    --batch-size 64 \
    --num-workers 32 \
    --eval-num-workers 32 \
    --train-cache-zip "./Clean_exports/cache_devign_v1/devign/train/4110578353421322/cache_train.zip" \
    --val-cache-zip   "./Clean_exports/cache_devign_v1/devign/valid/4110578353421322/cache_valid.zip" \
    --test-cache-zip  "./Clean_exports/cache_devign_v1/devign/test/4110578353421322/cache_test.zip" \
    --train-manifest "./Clean_exports/normalized_devign_graphson/train/staging_manifest_train_advT3_plus.csv" \
    --val-manifest   "./Clean_exports/normalized_devign_graphson/valid/staging_manifest_valid_advT3_plus.csv" \
    --test-manifest  "./Clean_exports/normalized_devign_graphson/test/staging_manifest_test_advT3_plus.csv" \
    --persistent-workers \
    --eval-persistent-workers \
    --prefetch-factor 2 \
    --eval-prefetch-factor 2 \
    --dropedge-p 0.03 \
    --train-feat-noise-std 0.01 \
    --do-temperature \
    --calib-beta 1.5 \
    --thr-ema-alpha 0.8 \
    --min-precision 0.30 \
    --min-recall 0.45 \
    --output-dir "./results_devign"



#######################################################

python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 16 \
  --hidden-dim 512 \
  --epochs 80 \
  --batch-size 32 \
  --eval-batch-size 32 \
  --num-workers 32 \
  --eval-num-workers 32 \
  --prefetch-factor 2 \
  --eval-prefetch-factor 2 \
  --persistent-workers \
  --eval-persistent-workers \
  --anti-collapse-w 0.1 --anti-collapse-target 0.5 \
  --max-pos-weight 8 \
  --min-precision 0.60 \
  \
  --cache-dir "./Clean_exports/cache_devign_v1" \
  --dataset-name "devign_normfunc" \
  --cache-signature "ed3362cdb12e0185" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy all \
  --val-collapse-policy all \
  --test-collapse-policy all \
  \
  --dropedge-p 0.00 \
  --train-feat-noise-std 0.00 \
  --output-dir "./results_devign_originals_only"



python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 6 \
  --hidden-dim 512 \
  --dropout 0.1 \
  --epochs 30 \
  --batch-size 32 \
  --lr 0.0001 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v1" \
  --dataset-name "devign_normfunc" \
  --cache-signature "ed3362cdb12e0185" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --focal-gamma 0.0 \
  --no-calibration \
  --fixed-threshold 0.5 \
  \
  --num-workers 8 \
  --persistent-workers \
  --prefetch-factor 2 \
  --clip-grad 0.5 \
  --no-amp \
  --output-dir "./results_devign_fix_v2"



python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 8 \
  --hidden-dim 768 \
  --dropout 0.2 \
  --epochs 50 \
  --batch-size 64 \
  --lr 0.0005 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v4" \
  --dataset-name "devign_normfunc" \
  --cache-signature "ed3362cdb12e0185" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --focal-gamma 2.0 \
  --pos-weight 1.0 \
  --min-recall 0.50 \
  --min-precision 0.50 \
  \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_sage_balanced_final"



python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 16 \
  --hidden-dim 256 \
  --dropout 0.2 \
  --epochs 60 \
  --batch-size 92 \
  --lr 0.0005 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v4" \
  --dataset-name "devign_normfunc" \
  --cache-signature "7033bf97f7eb49f0" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.0 \
  --supcon-w 0.2 \
  --min-precision 0.50 \
  \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_resgcn_supcon_v1"




Model A




python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 8 \
  --hidden-dim 256 \
  --dropout 0.2 \
  --epochs 60 \
  --batch-size 256 \
  --lr 0.0005 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v4" \
  --dataset-name "devign_normfunc" \
  --cache-signature "7033bf97f7eb49f0" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.0 \
  --supcon-w 0.2 \
  --min-precision 0.55 \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  \
  --seed 42 \
  --output-dir "./results_ensemble_A"


python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 4 \
  --hidden-dim 256 \
  --dropout 0.2 \
  --epochs 60 \
  --batch-size 32 \
  --accum-steps 2 \
  --lr 0.0005 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "52c1749e0da6a379" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.0 \
  --supcon-w 0.0 \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_transformer_v2"




python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --backbone resrgcn \
  --curriculum selfpaced \
  --curriculum-start-frac 0.3 \
  --curriculum-end-frac 1.0 \
  --layers 4 \
  --hidden-dim 256 \
  --dropout 0.2 \
  --epochs 60 \
  --batch-size 32 \
  --accum-steps 2 \
  --lr 5e-4 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "52c1749e0da6a379" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.0 \
  --supcon-w 0.1 \
  --anti-collapse-w 0.5 \
  --anti-collapse-target 0.2 \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_resrgcn_selfpaced_v1"





python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --backbone resrgcn \
  --curriculum selfpaced \
  --curriculum-start-frac 0.5 \
  --curriculum-end-frac 1.0 \
  \
  --layers 6 \
  --hidden-dim 512 \
  --dropout 0.2 \
  \
  --epochs 60 \
  --batch-size 32 \
  --accum-steps 2 \
  --lr 5e-4 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "52c1749e0da6a379" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.5 \
  --supcon-w 0.5 \
  --anti-collapse-w 0.1 \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_devign_scaled_512_v1"



python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --backbone sortpool \
  --curriculum selfpaced \
  --curriculum-start-frac 0.5 \
  --curriculum-end-frac 1.0 \
  \
  --layers 6 \
  --hidden-dim 512 \
  --dropout 0.2 \
  \
  --epochs 60 \
  --batch-size 16 \
  --accum-steps 4 \
  --lr 5e-4 \
  --weight-decay 1e-4 \
  \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "52c1749e0da6a379" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  --pos-weight 1.5 \
  --supcon-w 0.5 \
  --anti-collapse-w 0.1 \
  --num-workers 8 \
  --persistent-workers \
  --clip-grad 1.0 \
  --output-dir "./results_devign_SOTA_sortpool_v1"




python 02_MPTCN_TTS_Devign.py \
  --model devign \
  --layers 16 \
  --hidden-dim 768 \
  --dropout 0.20 \
  \
  --epochs 60 \
  --batch-size 16 \
  --accum-steps 4 \
  --lr 1e-4 \
  --weight-decay 1e-5 \
  \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "52c1749e0da6a379" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --collapse-policy orig \
  \
  --supcon-w 0.0 \
  --consistency-w 0.0 \
  --proto-w 0.0 \
  --focal-gamma 0.0 \
  --logit-l2 1e-5 \
  \
  --anti-collapse-w 0.01 \
  --anti-collapse-target 0.25 \
  \
  --num-workers 8 \
  --persistent-workers \
  --use-calib-config \
  --calib-beta 0.8 \
  --calib-max-pos-delta 1.5 \
  --calib-min-pos-frac 0.01 \
  --min-precision 0.50 \
  --clip-grad 1.0 \
  --debug-fusion \
  --debug-gate \
  --debug-sleep 0.0 \
  --debug-gate-sleep 0.0 \
  --gate-reg-w 0.01 \
  --gate-target-mean 0.4 \
  --gate-min-std 0.05\
  --output-dir "./results_devign_amplified_baseline_v2"




"""