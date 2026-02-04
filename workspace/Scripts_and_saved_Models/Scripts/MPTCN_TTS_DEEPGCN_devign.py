# ================== Imports & hard safety patches (paste at very top) ==================
# Make sure fused pyg_lib CUDA kernels never load. Must be set before torch/pyg import.
import os as _os
_os.environ.setdefault("PYG_FORCE_NO_PYG_LIB", "1")   # canonical switch recognized by PyG to disable pyg_lib
_os.environ.setdefault("WITH_PYG_LIB", "0")           # extra belt-and-suspenders for some codepaths
_os.environ.setdefault("PYG_DEBUG", "1")              # optional: extra checks/logs from PyG
_os.environ["TOKENIZERS_PARALLELISM"] = "false"
_os.environ.setdefault("PYTORCH_SHARING_STRATEGY", "file_system")
# _os.environ["CUDA_LAUNCH_BLOCKING"] = "1"           # optional: enable for precise stack traces

# --- Core & utilities
import argparse, json, os, random, hashlib, pickle, logging
from pathlib import Path
from typing import Dict, List, Optional
from collections import defaultdict, OrderedDict
from tqdm import tqdm
import sklearn.metrics as skm
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import sklearn.metrics as skm  # used in the training loop
import matplotlib.pyplot as plt  # for plotting utils below
import seaborn as sns           # for confusion matrix heatmap
from sklearn.metrics import (
    confusion_matrix,
    roc_curve,
    auc,
    precision_recall_curve,
    average_precision_score,
)

# --- Torch
import torch
from torch import nn
import torch.nn.functional as F
from torch.cuda.amp import autocast, GradScaler
import torch.nn.utils.parametrizations as param
torch.set_printoptions(precision=4, sci_mode=False, edgeitems=3, threshold=200, linewidth=140)

# --- Logging
logging.basicConfig(format="%(asctime)s %(levelname)s %(message)s", level=logging.INFO)
log = logging.getLogger("mptcn_tts")
logging.getLogger("transformers").setLevel(logging.ERROR)
logging.getLogger("urllib3").setLevel(logging.ERROR)

# --- HuggingFace (optional)
try:
    from transformers import AutoModel, AutoTokenizer, AddedToken
except Exception:  # keep training usable even if HF not installed
    AutoModel = AutoTokenizer = AddedToken = None

# --- Metrics
from sklearn.metrics import (
    accuracy_score, average_precision_score, confusion_matrix, f1_score,
    precision_recall_curve, precision_score, recall_score, roc_curve, auc
)

# --- PyG imports (AFTER env flags!)
from torch_geometric.data import Batch, HeteroData, Dataset, Data
from torch_geometric.loader import DataLoader
from torch_geometric.utils import add_self_loops
from torch_geometric.nn import (
    ChebConv, RGCNConv, HGTConv, GINConv, GCNConv, GATConv, HANConv,
    DynamicEdgeConv, PNAConv, GENConv, DeepGCNLayer,  # ← new
    global_add_pool, global_mean_pool, BatchNorm
)


# --- Disable fused path at PyG typing/dense.linear gates
import torch_geometric.typing as _tg_typing
_tg_typing.WITH_PYG_LIB = False

import torch_geometric.nn.dense.linear as _tg_linear
_tg_linear.WITH_PYG_LIB = False

# ================== HARD PATCHES (Linear, GroupLinear, and pyg_lib fallbacks) ==================
def _sanitize_ptr(ptr: torch.Tensor, N: int, device, dtype=torch.long):
    """Clamp to [0, N], make non-decreasing, and force last == N."""
    ptr = ptr.to(device=device, dtype=dtype).clone()
    if ptr.numel() == 0:
        return torch.tensor([0, N], device=device, dtype=dtype)
    ptr.clamp_(0, N)
    if ptr.numel() >= 2:
        ptr[1:] = torch.maximum(ptr[1:], ptr[:-1])
    if ptr[-1].item() != N:
        ptr[-1] = torch.tensor(N, device=device, dtype=dtype)
    return ptr

def _linear_safe_forward(self, x: torch.Tensor, type_ptr: Optional[torch.Tensor] = None) -> torch.Tensor:
    """
    Safe forward for torch_geometric.nn.dense.linear.Linear:
      • If weight is [Fout, Fin] -> plain matmul.
      • If weight is [G, Fout, Fin] -> per-group matmul using sanitized type_ptr.
    Fully differentiable; avoids pyg_lib.* and fused CUDA kernels.
    """
    W, B = self.weight, self.bias

    # Non-grouped (common case)
    if W.dim() == 2 or type_ptr is None:
        out = x @ W.t()
        if B is not None:
            out = out + (B if B.dim() == 1 else B[0]).clone()
        return out

    # Grouped
    N = int(x.size(0))
    ptr = _sanitize_ptr(type_ptr, N, x.device)

    outs = []
    G = max(0, ptr.numel() - 1)
    for g in range(G):
        s, e = int(ptr[g].item()), int(ptr[g+1].item())
        if e <= s:
            continue
        Xi = x[s:e]                           # [Si, Fin]
        Wi = W[min(g, W.size(0)-1)]           # [Fout, Fin]
        Yi = Xi @ Wi.t()                      # [Si, Fout]
        if B is not None:
            bi = B[min(g, B.size(0)-1)] if B.dim() == 2 else B
            Yi = Yi + bi
        outs.append(Yi)
    if not outs:
        Fout = int(W.size(-2)) if W.dim() == 3 else int(W.size(0))
        return x.new_zeros((0, Fout))
    return torch.cat(outs, dim=0)

# Install safe Linear everywhere; disable segmm/timing cache so PyG never probes fused paths
_tg_linear.Linear.forward               = _linear_safe_forward
_tg_linear.Linear.forward_naive         = _linear_safe_forward
_tg_linear.Linear.forward_segmm         = lambda self, x, type_ptr: _linear_safe_forward(self, x, type_ptr)
_tg_linear.Linear._update_timing_cache  = lambda self, x, type_ptr, key: None
print("[Patch] Linear: segmm disabled; safe forward installed")

# Safer GroupLinear (used by HGTConv) so it never calls pyg_lib.grouped_matmul
if hasattr(_tg_linear, "GroupLinear"):
    GroupLinear = _tg_linear.GroupLinear
    def _grouplinear_safe_forward(self, x_dict: Dict[str, torch.Tensor]):
        outs = {}
        # Build type map robustly across PyG versions
        tmap = getattr(self, "type_to_id", None) or getattr(self, "_type_to_id", None) \
               or getattr(self, "type_index", None)
        if tmap is None:
            names = getattr(self, "types", None) or getattr(self, "type_names", None) or []
            tmap = {t: i for i, t in enumerate(names)}

        for tname, x in x_dict.items():
            if x is None or tname not in tmap:
                continue
            idx = int(tmap[tname])
            W = self.weight[idx]                    # [Fout, Fin]
            y = x @ W.t()                           # [*, Fout]
            if self.bias is not None:
                b = self.bias[idx] if self.bias.dim() == 2 else self.bias
                y = y + b
            outs[tname] = y
        return outs
    GroupLinear.forward = _grouplinear_safe_forward
    print("[Patch] GroupLinear: safe dict-based matmul installed")

# Fallback for pyg_lib.ops.segment_matmul so timing/others can never trigger fused CUDA
try:
    import pyg_lib.ops as _pyg_ops
    def _safe_segment_matmul(inputs: torch.Tensor, ptr: torch.Tensor, other: torch.Tensor) -> torch.Tensor:
        """
        Pure-PyTorch replacement for pyg_lib.ops.segment_matmul.
        Supports both grouped ([G, Fout, Fin]) and non-grouped 'other'.
        """
        N = int(inputs.size(0))
        ptr = _sanitize_ptr(ptr, N, inputs.device)
        outs, ofs = [], 0
        sizes = (ptr[1:] - ptr[:-1]).tolist()
        for g, s in enumerate(sizes):
            s = int(max(0, s))
            if s == 0:
                continue
            Xg = inputs[ofs:ofs+s]  # [s, Fin]
            Wg = other[min(g, other.size(0)-1)] if other.dim() == 3 else other
            Yg = Xg @ (Wg.t() if Wg.dim() == 2 else Wg)  # [s, Fout]
            outs.append(Yg)
            ofs += s
        Fout = other.size(-2) if other.dim()==3 else other.size(0)
        return torch.cat(outs, dim=0) if outs else inputs.new_zeros((0, Fout))
    _pyg_ops.segment_matmul = _safe_segment_matmul
    print("[Patch] pyg_lib.ops.segment_matmul: Python fallback installed")
except Exception as _e:
    print(f"[Patch] segment_matmul override not applied: {_e}")

# (Optional last resort) Shadow pyg_lib.ops.grouped_matmul with a safe Python fallback.
# Only enable if you still see GroupedGEMM in traces after the patches above.
SAFE_SHADOW_GROUPED_MATMUL = False
if SAFE_SHADOW_GROUPED_MATMUL:
    try:
        import pyg_lib.ops as _pyg_ops
        def _safe_grouped_matmul(A: torch.Tensor, B: torch.Tensor) -> torch.Tensor:
            # Covers [N,K]@[K,M] and [G,S,K]@[G,K,M], otherwise broadcast matmul.
            if A.dim() == 2 and B.dim() == 2:
                return A @ B
            if A.dim() == 3 and B.dim() == 3 and A.size(0) == B.size(0):
                return torch.bmm(A, B)
            return torch.matmul(A, B)
        _pyg_ops.grouped_matmul = _safe_grouped_matmul
        print("[Patch] pyg_lib.ops.grouped_matmul: generic Python fallback installed")
    except Exception as _e:
        print(f"[Patch] grouped_matmul override not applied: {_e}")

# Log what PyG thinks the flags are (helps confirm the fused path is really off)
print("[PyG] typing.WITH_PYG_LIB =", getattr(_tg_typing, "WITH_PYG_LIB", None))
print("[PyG] dense.linear.WITH_PYG_LIB =", getattr(_tg_linear, "WITH_PYG_LIB", None))
# =================================================================================================

# --- Replace your helper with this ---


def _has_node_type(g: HeteroData, nt: str) -> bool:
    """Public, exception-safe check for a node type in (batched) HeteroData."""
    try:
        _ = g[nt]   # raises KeyError if nt doesn't exist
        return True
    except Exception:
        return False

def _get_node_feat(g: HeteroData, nt: str):
    """
    Returns the tensor to embed for node type `nt`, preferring `x_seq` then `x`.
    Returns None if the node type or features are absent.
    """
    if not _has_node_type(g, nt):
        return None
    store = g[nt]
    # Some datasets keep features in `x_seq`, others in `x`
    if hasattr(store, "x_seq") and store.x_seq is not None:
        return store.x_seq
    if hasattr(store, "x") and store.x is not None:
        return store.x
    return None

class _CudaIllegalAccess(RuntimeError):
    """Raised to signal the caller to SKIP this batch without any CUDA calls."""
    pass

class _DegenerateBatch(RuntimeError):
    """Raised when a batch has 0 nodes, no x_seq, or constant features → flat logits."""
    pass

def _is_illegal_cuda(err: BaseException) -> bool:
    s = str(err).lower()
    return ("illegal memory access" in s) or ("cuda error: an illegal memory access" in s)


def _assert_valid_batch(data) -> None:
    """Raise _DegenerateBatch if batch is empty or flagged degenerate/constant."""
    if getattr(data, "_degenerate", False):
        const = getattr(data, "_const_types", ())
        msg = "[Degenerate] empty graph or constant features"
        if const:
            msg += f" | constant types={list(const)[:6]}"
        raise _DegenerateBatch(msg)

def safe_embed(model, g, *, retry_once: bool = True):
    if g is None:
        raise RuntimeError("safe_embed: got None graph.")

    dev = next(model.parameters()).device
    is_hetero = isinstance(g, HeteroData)

    if not is_hetero and hasattr(g, "num_nodes"):
        n = int(getattr(g, "num_nodes", 0) or 0)
        if n == 0:
            raise _DegenerateBatch("[Degenerate] empty homogeneous graph (num_nodes==0)")

    if is_hetero:
        try:
            num_node_types = None
            emb = getattr(model, "node_emb", None)
            if emb is not None and hasattr(emb, "num_embeddings"):
                num_node_types = int(emb.num_embeddings)
            if num_node_types is None:
                raise RuntimeError("safe_embed: cannot infer num_node_types for hetero batch.")
            _sanitize_hetero_batch_(g, num_node_types=num_node_types, device=dev)
            _assert_valid_batch(g)
        except Exception as e:
            # Propagate degenerate batches explicitly so callers can skip cleanly
            if isinstance(e, _DegenerateBatch):
                raise
            raise RuntimeError(f"safe_embed: hetero batch invalid → {type(e).__name__}: {e}") from e

    g = g.to(dev, non_blocking=True)

    try:
        with torch.cuda.amp.autocast(enabled=False):
            z = model.embed(g)

        if z is None or z.ndim != 2 or z.size(0) == 0:
            raise RuntimeError(f"safe_embed: model.embed returned invalid shape {tuple(z.shape) if z is not None else None}")

        # Dead-encoder probe: normalized z all-zeros → nothing flowed
        if not torch.isfinite(z).all() or float(z.abs().sum().detach().cpu()) == 0.0:
            raise _DegenerateBatch("[Probe] Encoder produced flat/zero embeddings")

        return z

    except RuntimeError as e:
        msg = str(e).lower()
        if retry_once and "same device" in msg:
            _force_hetero_to_device_(g, dev)
            return safe_embed(model, g, retry_once=False)
        if retry_once and any(k in msg for k in ("grouped_matmul","segment_matmul","groupedgemm","split_with_sizes")):
            try:
                import torch_geometric.nn.dense.linear as _pyg_linear
                _pyg_linear.WITH_PYG_LIB = False
            except Exception:
                pass
            return safe_embed(model, g, retry_once=False)
        raise


def _force_hetero_to_device_(data, device):
    """Move all stores/tensors inside HeteroData to `device` in-place."""
    try:
        data.to(device, non_blocking=True)
    except Exception:
        # Fallback: move the few fields we care about
        for nt in getattr(data, "node_types", []):
            st = data[nt]
            if hasattr(st, "x_seq"):
                st.x_seq = st.x_seq.to(device, non_blocking=True)
            if hasattr(st, "x"):
                st.x = st.x.to(device, non_blocking=True)
            if hasattr(st, "batch"):
                st.batch = st.batch.to(device, non_blocking=True)
        for et in getattr(data, "edge_types", []):
            est = data[et]
            if hasattr(est, "edge_index"):
                est.edge_index = est.edge_index.to(device, non_blocking=True)





def _infer_num_node_types(model, g) -> int | None:
    # Prefer the model’s embedding rows:
    try:
        emb = getattr(model, "node_emb", None)
        if emb is not None and hasattr(emb, "num_embeddings"):
            return int(emb.num_embeddings)
    except Exception:
        pass

    # Fallback: infer from the batch (max token id + 1 across all node types)
    try:
        import torch
        mx = -1
        if hasattr(g, "node_types"):
            for nt in getattr(g, "node_types", []):
                x_seq = getattr(g[nt], "x_seq", None)
                if x_seq is None:
                    x_seq = getattr(g[nt], "x", None)
                if x_seq is None or x_seq.numel() == 0:
                    continue
                mx = max(mx, int(torch.as_tensor(x_seq).max().item()))
        elif hasattr(g, "x"):
            x = getattr(g, "x", None)
            if x is not None and x.numel() > 0:
                mx = max(mx, int(torch.as_tensor(x).max().item()))
        return (mx + 1) if mx >= 0 else None
    except Exception:
        return None


def _sanitize_hetero_batch_(data, *, num_node_types: int, device):
    """
    In-place guards for HeteroData before HGT:
      - enforce long dtype & device for x_seq
      - clamp token ids into [0, num_node_types-1]
      - set num_nodes; trim OOB edges; drop explicit self-loops
      - flag degenerate/constant-feature batches for skipping upstream
    """
    import torch

    total_nodes = 0
    const_types: list[str] = []
    present_types: list[str] = list(getattr(data, "node_types", []))

    # ---------- 1) Nodes ----------
    for nt in present_types:
        store = data[nt]
        x_seq = getattr(store, "x_seq", None)

        if x_seq is None:
            nn = int(getattr(store, "num_nodes", 0) or 0)
            store.x_seq = torch.zeros((nn, 1), dtype=torch.long, device=device)
            x_seq = store.x_seq
        else:
            if x_seq.dtype != torch.long:
                x_seq = x_seq.long()
            if x_seq.device != device:
                x_seq = x_seq.to(device, non_blocking=True)
            if num_node_types is not None and num_node_types > 0:
                x_seq = x_seq.clamp(0, num_node_types - 1)
            store.x_seq = x_seq.contiguous()

        rows = int(store.x_seq.size(0))
        store.num_nodes = rows
        total_nodes += rows

        # detect constant features per type (min == max across all tokens/steps)
        if rows > 0 and (store.x_seq.min() == store.x_seq.max()):
            const_types.append(nt)

    # ---------- 2) Edges (unchanged from your logic, trimmed for brevity) ----------
    for et in list(getattr(data, "edge_types", [])):
        estore = data[et]
        ei = getattr(estore, "edge_index", None)
        if ei is None or ei.numel() == 0 or ei.dim() != 2 or ei.size(0) != 2:
            try: del data[et]
            except Exception: pass
            continue
        if ei.device != device:
            ei = ei.to(device, non_blocking=True)
        src_nt, _, dst_nt = et
        nsrc = int(getattr(data[src_nt], "num_nodes", 0) or 0)
        ndst = int(getattr(data[dst_nt], "num_nodes", 0) or 0)
        ok = (ei[0] >= 0) & (ei[0] < nsrc) & (ei[1] >= 0) & (ei[1] < ndst)
        if ok.dim() > 1:
            ok = ok.all(dim=0)
        if ok.sum().item() == 0:
            try: del data[et]
            except Exception: pass
            continue
        ei = ei[:, ok].contiguous()
        estore.edge_index = ei
        if hasattr(estore, "edge_attr") and estore.edge_attr is not None:
            estore.edge_attr = estore.edge_attr.to(device, non_blocking=True)
            if estore.edge_attr.size(0) != ei.size(1):
                estore.edge_attr = estore.edge_attr[: ei.size(1)].contiguous()

    # ---------- 3) Drop explicit self-loops (unchanged) ----------
    for et in list(getattr(data, "edge_types", [])):
        estore = data[et]
        if not hasattr(estore, "edge_index"): continue
        ei = estore.edge_index
        if ei.numel() > 0:
            mask = ~(ei[0] == ei[1])
            if mask.ndim > 1: mask = mask.all(dim=0)
            if mask.sum().item() < ei.size(1):
                ei = ei[:, mask]
                if ei.numel() == 0:
                    try: del data[et]
                    except Exception: pass
                    continue
                estore.edge_index = ei.contiguous()
                if hasattr(estore, "edge_attr") and estore.edge_attr is not None:
                    estore.edge_attr = estore.edge_attr[mask].contiguous()

    # ---------- 4) Final align & flags ----------
    data = data.to(device, non_blocking=True)
    data._sanitized   = True
    data._degenerate  = bool(total_nodes == 0)
    data._const_types = tuple(const_types)

    # If ALL present types are constant, mark degenerate for skipping
    if present_types and (len(const_types) == len(present_types)):
        data._degenerate = True

    return data




def _safe_loss_combine(contrastive_loss, domain_loss=None, domain_lambda=0.0):
    """
    Combine contrastive and optional domain losses safely.
    """
    if domain_loss is None or domain_lambda <= 0:
        return contrastive_loss
    return contrastive_loss + domain_lambda * domain_loss

# ── Data locations (single source of truth) ───────────────────────────────────
# You can override with ENV var DEVIGN_DATA_ROOT if you move the folder.
import os
from pathlib import Path

DATA_ROOT = Path(os.environ.get("DEVIGN_DATA_ROOT", "."))

# Defaults (keep your current train/val set to advT6; default test is original)
MANIFESTS = {
    "train": DATA_ROOT / "workspace/01_Normalized_datasets/03_normalized_devign/manifest_train_advT6.csv",
    "val":   DATA_ROOT / "workspace/01_Normalized_datasets/03_normalized_devign/manifest_valid_advT6.csv",
    "test":  DATA_ROOT / "workspace/01_Normalized_datasets/03_normalized_devign/manifest_test.csv",
}

# Optional augmented (windowed) test manifest (T=6), provided by you
AUG_TEST_MANIFEST = Path(
    "./workspace/01_Normalized_datasets/03_normalized_devign/manifest_test_advT6.csv"
)

JSON_ROOTS = {
    "train": DATA_ROOT / "Json_exports/normalized_devign_json/train_graphson",
    "val":   DATA_ROOT / "Json_exports/normalized_devign_json/valid_graphson",
    "test":  DATA_ROOT / "Json_exports/normalized_devign_json/test_graphson",
}

# ─────────────────────────────────────────────────────────────────────────────
# Utility
# ─────────────────────────────────────────────────────────────────────────────
# --- Logging & display guards ---------------------------------
import logging
logging.basicConfig(format="%(asctime)s %(levelname)s %(message)s", level=logging.INFO)
log = logging.getLogger("mptcn_tts")

# truncate numpy/torch prints in case anything slips through
np.set_printoptions(edgeitems=3, threshold=20, linewidth=120)

from functools import partial
def make_tqdm(args, *, leave=False, desc=None):
    return partial(
        tqdm,
        ncols=100,
        dynamic_ncols=True,
        smoothing=0.1,
        leave=leave,
        disable=getattr(args, "no_progress", False),
        desc=desc,
    )


def make_loader(
    dataset,
    *,
    batch_size,
    shuffle,
    num_workers,
    collate_fn,
    pin_memory=False,
    persistent_workers=False,
    prefetch_factor=2
):
    kwargs = dict(
        batch_size=batch_size,
        shuffle=shuffle,
        num_workers=num_workers,
        pin_memory=pin_memory,
        persistent_workers=persistent_workers,
        collate_fn=collate_fn,
    )
    # prefetch_factor is only valid when num_workers > 0
    if num_workers > 0 and prefetch_factor is not None:
        kwargs["prefetch_factor"] = int(prefetch_factor)
    return DataLoader(dataset, **kwargs)



def vprint(args, *msg):
    """verbose-only print that never dumps huge arrays by accident."""
    if getattr(args, "verbose", False):
        tqdm.write(" ".join(str(m) for m in msg))

def _read_list_arg(spec: str) -> list[str]:
    """Parse 'a,b,c' or '@path.txt' (one token per line). Returns a unique, order-preserving list."""
    if not spec:
        return []
    spec = spec.strip()
    items: list[str] = []
    if spec.startswith("@"):
        path = spec[1:]
        with open(path, "r", encoding="utf-8") as f:
            for line in f:
                tok = line.strip()
                if tok:
                    items.append(tok)
    else:
        items = [t.strip() for t in spec.split(",") if t.strip()]
    # de-dup, keep order
    seen = set(); out = []
    for t in items:
        if t not in seen:
            seen.add(t); out.append(t)
    return out

@torch.no_grad()
def _avg_init_new_embeddings(hf_model, hf_tokenizer, new_tokens: list[str]) -> None:
    """
    Re-init newly-added token embeddings to the mean of *existing* rows only.
    Works after resize; we exclude all new token ids from the average.
    """
    if not new_tokens:
        return
    emb = hf_model.get_input_embeddings()
    W = emb.weight  # [V, D]
    # find ids for new tokens
    new_ids = []
    for tok in new_tokens:
        tid = hf_tokenizer.convert_tokens_to_ids(tok)
        if isinstance(tid, int) and 0 <= tid < W.size(0):
            new_ids.append(tid)
    if not new_ids:
        return
    mask = torch.ones(W.size(0), dtype=torch.bool, device=W.device)
    mask[torch.tensor(new_ids, device=W.device, dtype=torch.long)] = False
    if not mask.any():
        mean_vec = torch.zeros_like(W[0])
    else:
        mean_vec = W[mask].mean(dim=0, keepdim=False)
    for tid in new_ids:
        W[tid].copy_(mean_vec)


class _TokenChunksProxy:
    """Lightweight wrapper so Batch.__repr__ doesn't dump millions of ints."""
    def __init__(self, raw: list | None):
        self.raw = raw or []

    # behave like the underlying list for iteration/len/indexing
    def __len__(self): return len(self.raw)
    def __iter__(self): return iter(self.raw)
    def __getitem__(self, i): return self.raw[i]

    def __repr__(self):
        # concise summary only
        n_samples = len(self.raw)
        n_chunks  = sum(len(ch or []) for ch in self.raw)
        return f"<TokenChunksProxy samples={n_samples}, chunks={n_chunks}>"

def contrastive_collate(batch):
    orig_list = [item["orig"] for item in batch]
    adv_list  = [item["adv"]  for item in batch]
    orig = Batch.from_data_list(orig_list)
    adv  = Batch.from_data_list(adv_list)
    return {"orig": orig, "adv": adv}

def set_bn_eval(m):
    if isinstance(m, nn.BatchNorm1d):
        m.eval()


def set_seed(seed: int = 42) -> None:
    """Force-deterministic behaviour (CUDA + CPU)."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)

def safe_probs(logits: torch.Tensor) -> torch.Tensor:
    # sanitize logits first
    x = torch.nan_to_num(logits.float(), nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
    p = F.softmax(x, dim=1)
    # clamp away from exact 0/1 to avoid PR/ROC edge pathologies
    return p.clamp_min(1e-6).clamp_max(1.0 - 1e-6)





def add_regular_tokens_robust(tok, tokens):
    to_add = []
    vocab = tok.get_vocab()
    for t in tokens or []:
        t = t.strip()
        if not t or t in vocab:
            continue
        to_add.append(AddedToken(t, single_word=False, lstrip=False, rstrip=False, normalized=False))
    return tok.add_tokens(to_add) if to_add else 0

def verify_added_tokens_transformers(tok, model, regulars, specials=None):
    specials = specials or []
    regulars = regulars or []
    print("\n[TokenVerify] — GraphCodeBERT tokenizer —")
    missing = []
    for t in specials + regulars:
        tid = tok.convert_tokens_to_ids(t)
        print(f"[TokenVerify] '{t}' → id={tid}")
        if tid is None or tid < 0:
            missing.append(t)
    if missing:
        raise RuntimeError(f"[TokenVerify] Missing IDs for: {missing} (did you resize embeddings?)")

    emb_rows = model.get_input_embeddings().weight.shape[0]
    try:
        tok_size = len(tok)  # includes added tokens
    except Exception:
        tok_size = len(tok.get_vocab())

    print(f"[TokenVerify] tokenizer_length={tok_size} | embedding_rows={emb_rows}")
    if emb_rows != tok_size:
        raise RuntimeError(
            f"Embedding rows ({emb_rows}) != tokenizer length ({tok_size}). "
            "Call model.resize_token_embeddings(len(tok))."
        )

    probe = " ".join((specials + regulars)[:8])
    if probe:
        ids = tok.encode(probe, add_special_tokens=True)
        toks = tok.convert_ids_to_tokens(ids)
        print(f"[TokenVerify] probe: {probe}")
        print(f"[TokenVerify] ids  : {ids[:24]}")
        print(f"[TokenVerify] toks : {toks[:24]}")
    print("[TokenVerify] ✓ tokenizer & embeddings consistent.\n")


def preview_tokenization_on_sample(tok, ds, *, max_chars=300, max_pairs=80, custom_tokens=None):
    custom_tokens = set(custom_tokens or [])
    text = None
    for d in getattr(ds, "_cache", []):
        if hasattr(d, "code_text") and isinstance(d.code_text, str) and d.code_text.strip():
            text = d.code_text
            break
    if not text:
        print("[TokenPreview] No code_text available to preview."); return
    snippet = text[:max_chars]
    ids  = tok.encode(snippet, add_special_tokens=True)
    toks = tok.convert_ids_to_tokens(ids)
    print("\n[TokenPreview] — sample function (truncated) —")
    print(snippet)
    print("\n[TokenPreview] id ↔ token (first pairs):")
    hits = 0
    for i, (i_id, tk) in enumerate(zip(ids, toks)):
        if i >= max_pairs: break
        star = " *" if tk in custom_tokens else ""
        print(f"  {i:03d}: {i_id:>6}  {tk}{star}")
        hits += int(tk in custom_tokens)

    print(f"[TokenPreview] custom-token hits in this sample: {hits}\n")
    if custom_tokens:
            seen = [tk for tk in toks if tk in custom_tokens][:10]
            print(f"[TokenPreview] first custom-token matches: {seen}")

def get_graph_size_info(batch):
    """
    Get node and edge counts for both homogeneous and heterogeneous graphs
    """
    if hasattr(batch, 'edge_index'):
        # Homogeneous graph
        N = batch.num_nodes
        E = batch.edge_index.size(1) if hasattr(batch, 'edge_index') else 0
        T = batch.x.size(1) if batch.x.dim() == 2 else 1
        return f"N={N}, E={E}, T={T}"
    else:
        # Heterogeneous graph
        total_nodes = 0
        total_edges = 0
        T = 1
        
        # Sum nodes across all node types
        for node_type in batch.node_types:
            if hasattr(batch[node_type], 'num_nodes'):
                total_nodes += batch[node_type].num_nodes
            if hasattr(batch[node_type], 'x_seq') and batch[node_type].x_seq.dim() == 2:
                T = batch[node_type].x_seq.size(1)  # Get temporal dimension
        
        # Sum edges across all edge types
        for edge_type in batch.edge_types:
            if hasattr(batch[edge_type], 'edge_index'):
                total_edges += batch[edge_type].edge_index.size(1)
        
        return f"N={total_nodes}, E={total_edges}, T={T}"

# ──────────────────────────────────────────────────────────────
# PR-based threshold search (+ optional precision/recall floors)
# ──────────────────────────────────────────────────────────────
# ──────────────────────────────────────────────────────────────
# PR-based threshold search (+ optional precision/recall floors)
# ──────────────────────────────────────────────────────────────
def find_optimal_threshold_from_pr(
    y_true: np.ndarray,
    y_prob: np.ndarray,
    *,
    beta: float = 0.7,                  # <1 favors precision
    min_precision: float | None = None, # e.g. 0.85, or None (disabled)
    min_recall: float | None = None,    # e.g. 0.25, or None (disabled)
    cap_over_base: float = 0.08,        # pos_rate <= base_rate + cap_over_base
    min_pos_frac: float = 0.01,         # avoid predicting 0 positives
) -> float:
    from sklearn.metrics import precision_recall_curve

    if y_prob.size == 0 or len(np.unique(y_true)) < 2:
        return 0.5

    P, R, T = precision_recall_curve(y_true, y_prob)
    if T.size == 0:
        return 0.5

    p = P[:-1]; r = R[:-1]
    beta2 = beta * beta
    fbeta = (1.0 + beta2) * p * r / (beta2 * p + r + 1e-12)
    fbeta = np.nan_to_num(fbeta, nan=0.0, posinf=0.0, neginf=0.0)

    ok = np.ones_like(fbeta, dtype=bool)
    if min_precision is not None:
        ok &= (p >= float(min_precision))
    if min_recall is not None:
        ok &= (r >= float(min_recall))

    if ok.any():
        idx = int(np.argmax(np.where(ok, fbeta, -np.inf)))
    else:
        idx = int(np.argmax(fbeta))

    thr = float(T[idx])

    base_rate = float(y_true.mean())
    pos_rate  = float((y_prob > thr).mean())
    cap   = min(0.75, base_rate + float(cap_over_base))
    floor = max(float(min_pos_frac), min(base_rate, 0.49))
    eps = 1e-7

    if pos_rate > cap:
        thr = float(np.quantile(y_prob, 1.0 - cap)) + eps
    elif pos_rate < floor:
        thr = float(np.quantile(y_prob, 1.0 - floor)) - eps

    n_pos = int((y_prob > thr).sum())
    if n_pos == 0:
        thr -= eps
    elif n_pos == y_prob.size:
        thr += eps

    if not np.isfinite(thr):
        thr = 0.5
    return float(thr)


# Small wrapper to match the name used inside the training loop
def _pick_thr_from_pr(
    y_true: np.ndarray,
    y_prob: np.ndarray,
    *,
    beta: float,
    min_precision: float | None,
    min_recall: float | None,
    cap_over_base: float,
    min_pos_frac: float,
) -> float:
    return find_optimal_threshold_from_pr(
        y_true, y_prob,
        beta=beta,
        min_precision=min_precision,
        min_recall=min_recall,
        cap_over_base=cap_over_base,
        min_pos_frac=min_pos_frac,
    )

# ──────────────────────────────────────────────────────────────
# Online augs: random DropEdge + temporal jitter (copy prev→last)
# ──────────────────────────────────────────────────────────────
def _drop_edges_homo(data: Data, p: float) -> Data:
    if p <= 0 or not hasattr(data, "edge_index") or data.edge_index.numel() == 0:
        return data
    ei = data.edge_index
    E  = ei.size(1)
    keep = torch.rand(E, device=ei.device) > float(p)
    if keep.sum() == 0:
        return data
    data.edge_index = ei[:, keep].contiguous()
    if hasattr(data, "edge_type") and data.edge_type is not None and data.edge_type.numel() == E:
        data.edge_type = data.edge_type[keep].contiguous()
    return data

def _drop_edges_hetero(data: HeteroData, p: float) -> HeteroData:
    if p <= 0:
        return data
    for et in list(getattr(data, "edge_types", [])):
        store = data[et]
        if not hasattr(store, "edge_index") or store.edge_index.numel() == 0:
            continue
        ei = store.edge_index
        E  = ei.size(1)
        keep = torch.rand(E, device=ei.device) > float(p)
        if keep.sum() == 0:
            # drop the whole relation for this batch
            try: del data[et]
            except Exception: pass
            continue
        store.edge_index = ei[:, keep].contiguous()
        if hasattr(store, "edge_attr") and store.edge_attr is not None and store.edge_attr.size(0) == E:
            store.edge_attr = store.edge_attr[keep].contiguous()
    return data

def _temporal_jitter_last_inplace(data, pj: float):
    if pj <= 0.0:
        return
    if isinstance(data, Data):
        if hasattr(data, "x") and data.x.dim() == 2 and data.x.size(1) > 1:
            N, T = data.x.size()
            last = data.x[:, -1]
            prev = data.x[:, -2]
            mask = torch.rand(N, device=last.device) < float(pj)
            data.x[:, -1] = torch.where(mask, prev, last)
    else:
        for nt in getattr(data, "node_types", []):
            if hasattr(data[nt], "x_seq") and data[nt].x_seq is not None and data[nt].x_seq.dim() == 2:
                X = data[nt].x_seq
                if X.size(1) <= 1:
                    continue
                N, T = X.size()
                last = X[:, -1]
                prev = X[:, -2]
                mask = torch.rand(N, device=last.device) < float(pj)
                X[:, -1] = torch.where(mask, prev, last)

def augment_batch(batch, *, dropedge_p: float = 0.0, temporal_jitter: float = 0.0):
    """Apply online augs in-place to a single Batch/HeteroData batch."""
    if isinstance(batch, HeteroData):
        batch = _drop_edges_hetero(batch, dropedge_p)
        _temporal_jitter_last_inplace(batch, temporal_jitter)
    else:
        batch = _drop_edges_homo(batch, dropedge_p)
        _temporal_jitter_last_inplace(batch, temporal_jitter)
    return batch






# ──────────────────────────────────────────────────────────────────────────
# DevignDataset  – snapshot or temporal-window loader  (adds .fid and .domain)
# ──────────────────────────────────────────────────────────────────────────
class DevignDataset(Dataset):
    PAD_TOKEN = "<PAD>"

    def __init__(self,
             manifest_csv: Path | str,
             json_root:    Path | str,
             T: int = 1,
             node_type_vocab: Optional[Dict[str, int]] = None,
             edge_type_vocab: Optional[Dict[str, int]] = None,
             transform=None,
             cache_root:    Path | str | None = None):
        super().__init__()
        self.T = max(1, T)
        self.json_root = Path(json_root)
        self.transform = transform

        df = pd.read_csv(manifest_csv)

        # ----- ensure json_path column + a real/synthetic flag
        if "json_path" not in df.columns:
            df["json_path"] = pd.NA

        def _is_real_jsonpath(x):
            # real iff json_path is NOT a non-empty string (i.e., it's export.json)
            return not (isinstance(x, str) and len(x) > 0)

        has_any_real = df["json_path"].apply(_is_real_jsonpath).any()

        # ----- inject one real export.json row per function if T>1 and none present
        if self.T > 1 and not has_any_real:
            extras = []
            for fid, g in df.groupby("index"):
                lbl = int(g["label"].iloc[0]) if "label" in g.columns else 0
                new_row = {"index": int(fid), "label": lbl, "json_path": pd.NA}
                for col in ("src_path", "code_path", "code"):
                    if col in g.columns:
                        new_row[col] = g[col].iloc[0]
                extras.append(new_row)
            if extras:
                df = pd.concat([pd.DataFrame(extras), df], ignore_index=True)

        # mark real rows so we can order them before synthetic per function
        df["__is_real"] = df["json_path"].apply(_is_real_jsonpath)

        # ----- filter to rows whose JSON actually exists (handles injected rows too)
        def _path_exists(row):
            if isinstance(row.get("json_path"), str) and row["json_path"]:
                p = self.json_root / row["json_path"]
            else:
                p = self._json_path_for_id(int(row["index"]))
            return p.is_file()

        mask = df.apply(_path_exists, axis=1)
        df = df[mask].reset_index(drop=True)
        print(f"[Dataset] {mask.sum()}/{len(mask)} JSONs found in {json_root}")

        self.row_df = df

        # ----- build per-function ordered row lists: real → synthetic, then by row index
        raw_map: Dict[int, List[int]] = df.groupby("index").indices
        self.func2rows: Dict[int, List[int]] = {fid: sorted(idxs) for fid, idxs in raw_map.items()}
        self.func2rows_ordered: Dict[int, List[int]] = {}
        for fid, idxs in raw_map.items():
            ordered = sorted(list(idxs), key=lambda i: (0 if df.loc[i, "__is_real"] else 1, i))
            self.func2rows_ordered[fid] = ordered

        # ----- window starts from the ordered lists
        self.window_starts: List[int] = []
        for fid, ordered in self.func2rows_ordered.items():
            if len(ordered) < self.T:
                continue
            if self.T == 1:
                self.window_starts.extend(ordered)
            else:
                self.window_starts.extend(ordered[: len(ordered) - self.T + 1])

        # ----- vocab setup
        self.node_type_vocab = (node_type_vocab if node_type_vocab else self._build_node_vocab())
        self.edge_type_vocab = (edge_type_vocab if edge_type_vocab else self._build_edge_vocab())
        if self.PAD_TOKEN not in self.node_type_vocab:
            self.node_type_vocab[self.PAD_TOKEN] = len(self.node_type_vocab)
        self.num_node_types  = len(self.node_type_vocab)
        self.num_edge_types  = len(self.edge_type_vocab)

        # ----- cache dir
        self.cache_dir = (self.json_root.parent / f"cache_T{self.T}"
                        if cache_root is None else Path(cache_root) / f"cache_T{self.T}")
        self.cache_dir.mkdir(parents=True, exist_ok=True)

        # ----- Build/load cache; patch missing attrs from old caches
        self._cache: List[Data] = []
        for start in tqdm(self.window_starts, desc=f"Loading cache T={self.T}", ncols=80):
            pkl_path = self.cache_dir / f"{start}.pt"
            if pkl_path.exists():
                data = torch.load(pkl_path)
            else:
                data = self._build_data(start)
                torch.save(data, pkl_path)

            # ensure meta fields
            if not hasattr(data, "fid"):
                fid = int(self.row_df.loc[start, "index"])
                data.fid = torch.tensor([fid], dtype=torch.long)

            if not hasattr(data, "domain"):
                # domain = 1 (real) if ANY snapshot in the window is real
                fid = int(self.row_df.loc[start, "index"])
                rows_ord = self.func2rows_ordered.get(fid, self.func2rows.get(fid, []))
                try:
                    pos = rows_ord.index(start)
                    idxs = rows_ord[pos : pos + self.T]
                except ValueError:
                    # fallback to single-row window
                    idxs = [start]
                is_real_any = any(self.row_df.loc[i, "__is_real"] for i in idxs)
                data.domain = torch.tensor([1 if is_real_any else 0], dtype=torch.long)

            if not hasattr(data, "edge_type"):
                E = data.edge_index.size(1) if hasattr(data, "edge_index") else 0
                unk_id = self.edge_type_vocab.get("UNK", 0)
                data.edge_type = torch.full((E,), unk_id, dtype=torch.long)

            # stable cache index for this sample
            data.cache_idx = torch.tensor([len(self._cache)], dtype=torch.long)
            self._cache.append(data)




    def _json_path_for_id(self, func_id: int) -> Path:
        return self.json_root / f"F{func_id:06d}" / "export.json"

    def _jpath(self, row_idx: int) -> Path:
        row = self.row_df.loc[row_idx]
        if isinstance(row.get("json_path"), str) and row["json_path"]:
            return self.json_root / row["json_path"]
        return self._json_path_for_id(int(row["index"]))

    def _build_node_vocab(self) -> Dict[str, int]:
        labels = set()
        for i in tqdm(self.row_df.index, desc="Building node vocab"):
            edges = json.load(open(self._jpath(i)))["@value"]["edges"]
            for e in edges:
                labels.add(e["inVLabel"])
                labels.add(e["outVLabel"])
        return {lbl: idx for idx, lbl in enumerate(sorted(labels))}



    def _build_edge_vocab(self) -> Dict[str, int]:
        """Build relation/edge-type vocabulary from JSON."""
        labels = set()
        for i in tqdm(self.row_df.index, desc="Building edge vocab"):
            edges = json.load(open(self._jpath(i)))["@value"]["edges"]
            for e in edges:
                et = (
                    e.get("label")
                    or e.get("edgeLabel")
                    or e.get("type")
                    or e.get("rel")
                )
                labels.add(str(et) if et is not None else "UNK")
        vocab = {lbl: idx for idx, lbl in enumerate(sorted(labels))}
        if "UNK" not in vocab:
            vocab["UNK"] = len(vocab)
        return vocab


    def __len__(self) -> int:
        return len(self._cache)

    def __getitem__(self, idx: int) -> Data:
        data = self._cache[idx]
        return self.transform(data) if self.transform else data

    # REPLACE the whole _build_data() in DevignDataset with this
    def _build_data(self, start: int) -> Data:
        fid = int(self.row_df.loc[start, "index"])

        # Use the ordered per-function sequence (real → synthetic), not plain sorted
        rows_ord = self.func2rows_ordered.get(fid, self.func2rows.get(fid, []))
        if start not in rows_ord:
            # very defensive: fall back to sorted list if needed
            rows_ord = sorted(self.func2rows.get(fid, []))

        pos = rows_ord.index(start)
        snaps_idx = rows_ord[pos : pos + self.T]
        snaps = [json.load(open(self._jpath(i))) for i in snaps_idx]

        # unique nodes across the window
        node_ids = sorted({
            nid
            for snap in snaps
            for edge in snap["@value"]["edges"]
            for nid in (edge["inV"]["@value"], edge["outV"]["@value"])
        })

        # label from the final row in the window
        label_row = snaps_idx[-1]
        row_meta  = self.row_df.loc[label_row]
        label     = int(row_meta["label"])

        # window is "real" if ANY of its rows is real
        is_real_any = any(self.row_df.loc[i, "__is_real"] for i in snaps_idx)

        if not node_ids:
            pad_id = self.node_type_vocab[self.PAD_TOKEN]
            x = torch.full((1, self.T), pad_id, dtype=torch.long)
            edge_index = torch.empty((2, 0), dtype=torch.long)
            edge_type  = torch.empty((0,), dtype=torch.long)
            data = Data(x=x, edge_index=edge_index, edge_type=edge_type,
                        y=torch.tensor(label, dtype=torch.long))
        else:
            pad_id = self.node_type_vocab[self.PAD_TOKEN]
            xs = []
            for snap in snaps:
                lbl = {e["inV"]["@value"]:  e["inVLabel"] for e in snap["@value"]["edges"]}
                lbl.update({e["outV"]["@value"]: e["outVLabel"] for e in snap["@value"]["edges"]})
                xs.append(torch.tensor([self.node_type_vocab.get(lbl.get(n), pad_id)
                                        for n in node_ids], dtype=torch.long))
            x = torch.stack(xs, dim=1)  # [N, T]

            last_edges = snaps[-1]["@value"]["edges"]
            id_map = {nid: idx for idx, nid in enumerate(node_ids)}
            ei_src, ei_dst, etypes = [], [], []
            for e in last_edges:
                s = id_map[e["outV"]["@value"]]; d = id_map[e["inV"]["@value"]]
                ei_src.append(s); ei_dst.append(d)
                et = e.get("label") or e.get("edgeLabel") or e.get("type") or e.get("rel") or "UNK"
                etypes.append(self.edge_type_vocab.get(str(et), self.edge_type_vocab["UNK"]))
            edge_index = torch.tensor([ei_src, ei_dst], dtype=torch.long)
            edge_type  = torch.tensor(etypes, dtype=torch.long)

            edge_index, _ = add_self_loops(edge_index, num_nodes=len(node_ids))
            if edge_index.size(1) > edge_type.numel():
                extra = edge_index.size(1) - edge_type.numel()
                edge_type = torch.cat(
                    [edge_type, torch.full((extra,), self.edge_type_vocab["UNK"], dtype=torch.long)]
                )
            data = Data(x=x, edge_index=edge_index, edge_type=edge_type,
                        y=torch.tensor(label, dtype=torch.long))

        # meta
        data.domain = torch.tensor([1 if is_real_any else 0], dtype=torch.long)
        data.fid    = torch.tensor([fid], dtype=torch.long)

        # optional text for GraphCodeBERT fusion
        text = None
        if "code" in self.row_df.columns:
            text = str(self.row_df.loc[label_row, "code"])
        if (text is None) and ("src_path" in self.row_df.columns):
            sp = self.row_df.loc[label_row, "src_path"]
            try:
                text = open(sp, "r", errors="ignore").read()
            except Exception:
                text = None
        if (text is None) and ("code_path" in self.row_df.columns):
            sp = self.row_df.loc[label_row, "code_path"]
            try:
                text = open(sp, "r", errors="ignore").read()
            except Exception:
                text = None
        if text is None:
            try:
                js = snaps[-1]
                text = js.get("code") or js.get("source") or None
            except Exception:
                text = None
        if text is not None:
            data.code_text = text

        return data


# --- Hetero dataset for HGT ---------------------------------------------------
# --- Hetero dataset for HGT ---------------------------------------------------
# --- Hetero dataset for HGT (CACHED) -----------------------------------------
# --- Hetero dataset for HGT (disk-cached) ------------------------------------
class DevignHeteroDataset(DevignDataset):
    """
    Builds HeteroData for the *last* snapshot in the window ONCE and caches to disk.
    __getitem__ then loads the cached object – ~O(1) CPU work per sample.

    Cache invalidation: if T, node vocab or edge vocab changes, we rebuild.
    """

    CACHE_VERSION = "het_v2"  # bump to force a rebuild if you change layout

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # ---------- derive a cache directory that is unique to (T, vocabs) ----------
        # hash node/edge vocabs so cache survives runs but invalidates on changes
        def _hash_vocab(v: dict[str, int]) -> str:
            # stable json -> sha1
            s = json.dumps(v, sort_keys=True).encode("utf-8")
            return hashlib.sha1(s).hexdigest()[:8]

        node_h = _hash_vocab(self.node_type_vocab)
        edge_h = _hash_vocab(self.edge_type_vocab)

        base_name = Path(self.cache_dir).name  # e.g. cache_T6
        self.hetero_cache_dir = Path(self.cache_dir).with_name(
            f"{base_name}_hetero_{self.CACHE_VERSION}_{node_h}_{edge_h}"
        )
        self.hetero_cache_dir.mkdir(parents=True, exist_ok=True)

        # small manifest describing what this cache was built from
        self._cache_meta_path = self.hetero_cache_dir / "_meta.json"
        want_meta = {
            "version": self.CACHE_VERSION,
            "T": int(self.T),
            "node_vocab_hash": node_h,
            "edge_vocab_hash": edge_h,
            "count": len(self.window_starts),
        }

        # if existing meta mismatches, wipe the directory (only the files we created)
        if self._cache_meta_path.exists():
            try:
                have = json.loads(self._cache_meta_path.read_text())
            except Exception:
                have = {}
            mismatch = (
                have.get("version") != want_meta["version"] or
                have.get("T") != want_meta["T"] or
                have.get("node_vocab_hash") != want_meta["node_vocab_hash"] or
                have.get("edge_vocab_hash") != want_meta["edge_vocab_hash"]
            )
            if mismatch:
                for p in self.hetero_cache_dir.glob("*.pt"):
                    try: p.unlink()
                    except Exception: pass

        # (re)write meta
        try:
            self._cache_meta_path.write_text(json.dumps(want_meta))
        except Exception:
            pass

        # ---------- build hetero cache lazily (only missing files) ----------
        self._hetero_index: list[Path] = []  # filenames aligned to window_starts

        inv_node = {v: k for k, v in self.node_type_vocab.items()}
        inv_edge = {v: k for k, v in self.edge_type_vocab.items()}

        from tqdm import tqdm as _tqdm
        for k, start in enumerate(_tqdm(self.window_starts, desc=f"Build HETERO cache T={self.T}", ncols=80)):
            tgt = self.hetero_cache_dir / f"{start}.pt"
            self._hetero_index.append(tgt)
            if tgt.exists():
                continue  # already cached

            base: Data = self._cache[k]  # same ordering as window_starts

            # ---- convert 'base' (homogeneous) -> HeteroData for the last snapshot ----
            # Node types from last step
            x_last = base.x[:, -1] if base.x.dim() == 2 else base.x.view(-1)
            node_labels = [inv_node.get(int(t), "UNK_NODE") for t in x_last.tolist()]

            # Group global node indices by their string type
            from collections import defaultdict as _dd
            type_to_gidx = _dd(list)
            for g_idx, tname in enumerate(node_labels):
                type_to_gidx[tname].append(g_idx)

            data = HeteroData()

            # Per-type node sequences x_seq: [N_t, T] and num_nodes
            for tname, gidxs in type_to_gidx.items():
                gidxs_t = torch.tensor(gidxs, dtype=torch.long)
                x_seq_t = base.x.index_select(0, gidxs_t).contiguous()       # [N_t, T]
                data[tname].x_seq = x_seq_t
                data[tname].num_nodes = int(x_seq_t.size(0))                 # helps batching

            # Map from global idx -> local idx per type for edge projection
            local_map = {t: {g: i for i, g in enumerate(gidxs)} for t, gidxs in type_to_gidx.items()}

            # Edges of the last snapshot (already built in base)
            ei = base.edge_index.contiguous()                 # [2, E], long
            et = getattr(base, "edge_type", None)
            if et is None:
                unk_id = self.edge_type_vocab.get("UNK", 0)
                et = torch.full((ei.size(1),), unk_id, dtype=torch.long, device=ei.device)
            else:
                et = et.contiguous().long()

            E = int(ei.size(1))
            src_g = ei[0].tolist()
            dst_g = ei[1].tolist()
            et_list = et.tolist()

            # Append edges grouped by (src_type, rel, dst_type)
            for e_idx in range(E):
                g_s = src_g[e_idx]
                g_d = dst_g[e_idx]
                st  = node_labels[g_s]
                dt  = node_labels[g_d]
                rel_id  = int(et_list[e_idx])
                rel_sym = inv_edge.get(rel_id, "UNK")
                key = (st, rel_sym, dt)

                # Map global -> local indices under their types
                s_local = local_map[st][g_s]
                d_local = local_map[dt][g_d]

                new_e = torch.tensor([[s_local], [d_local]], dtype=torch.long)
                prev  = getattr(data[key], "edge_index", None)
                data[key].edge_index = (new_e if prev is None else torch.cat([prev, new_e], dim=1)).contiguous()

            # Labels / meta carried over
            data.y      = base.y
            data.domain = base.domain
            data.fid    = base.fid
            if hasattr(base, "code_text"):
                data.code_text = base.code_text

            # Quick helpers for debug (optional)
            data._node_types = list(type_to_gidx.keys())
            data._edge_types = list(data.edge_types)

            # Mark as pre-sanitized so training can skip sanitizer work
            data._sanitized = True

            # Save to disk
            torch.save(data, tgt)

    def __len__(self) -> int:
        return len(self._hetero_index)

    def __getitem__(self, idx: int) -> HeteroData:
        # load cached hetero graph and return directly (CPU tensors)
        return torch.load(self._hetero_index[idx], map_location="cpu")





# --- Collate helpers to keep code_text across batching ------------------------
# REPLACE graph_collate and contrastive_collate_any with this
from torch_geometric.loader.dataloader import Collater

def graph_collate(items):
    if isinstance(items[0], HeteroData):
        return Collater(follow_batch=[], exclude_keys=[])(items)
    return Batch.from_data_list(items)

def contrastive_collate_any(batch):
    orig_list = [b["orig"] for b in batch]
    adv_list  = [b["adv"]  for b in batch]
    if isinstance(orig_list[0], HeteroData):
        coll = Collater(follow_batch=[], exclude_keys=[])
        return {"orig": coll(orig_list), "adv": coll(adv_list)}
    return {"orig": Batch.from_data_list(orig_list),
            "adv":  Batch.from_data_list(adv_list)}


# ──────────────────────────────────────────────────────────────
# Domain-adversarial bridge  (synthetic → real gap)
# ──────────────────────────────────────────────────────────────
class GradRev(torch.autograd.Function):
    λ = 0.05

    @staticmethod
    def forward(ctx, x):
        return x.view_as(x)

    @staticmethod
    def backward(ctx, g):
        return -GradRev.λ * g    # ← return ONE gradient, not (g, None)


class DomainAdapter(nn.Module):
    """Binary domain classifier attached to the shared backbone."""
    def __init__(self, in_dim: int):
        super().__init__()
        self.classifier = nn.Sequential(
            nn.Linear(in_dim, 64),
            nn.ReLU(),
            nn.Linear(64, 2)      # 0 = synthetic, 1 = real
        )

    def forward(self, h: torch.Tensor) -> torch.Tensor:
        h = GradRev.apply(h)
        return self.classifier(h)

# ─────────────────────────────────────────────────────────────────────────────
# top of file (utilities to prevent gigantic accidental prints)
# ─────────────────────────────────────────────────────────────────────────────
import sys
from contextlib import contextmanager

class _FilteredStream:
    """Proxy around a text stream that truncates very long writes."""
    def __init__(self, stream, max_chars: int = 50_000):
        self._stream = stream
        self._max = int(max_chars)

    def write(self, s):
        # Be defensive: coerce to str and truncate huge chunks
        if not isinstance(s, str):
            s = str(s)
        if len(s) <= self._max:
            return self._stream.write(s)
        # Truncate instead of dumping megabytes to the terminal.
        return self._stream.write(s[: self._max] + " …[truncated]\n")

    def flush(self):
        return self._stream.flush()

    # Delegate anything else to the wrapped stream (isatty, fileno, encoding, etc.)
    def __getattr__(self, name):
        return getattr(self._stream, name)


@contextmanager
def suppress_huge_prints(max_chars: int = 50_000, also_stderr: bool = True):
    """
    Context manager that guards stdout (and optionally stderr) against
    accidental massive tensor/list dumps that can freeze terminals.
    """
    orig_out, orig_err = sys.stdout, sys.stderr
    sys.stdout = _FilteredStream(orig_out, max_chars=max_chars)
    if also_stderr:
        sys.stderr = _FilteredStream(orig_err, max_chars=max_chars)
    try:
        yield
    finally:
        sys.stdout = orig_out
        if also_stderr:
            sys.stderr = orig_err



# ────────────────────────────────────────────────────────────────
# Contrastive dataset – pairs two snapshots of the *same* function
# ────────────────────────────────────────────────────────────────
class DevignContrastiveDataset(torch.utils.data.Dataset):
    """
    Works on a *T = 1* DevignDataset.

    For every function that has at least two snapshots
    (export.json + ≥1 mutants) we sample pairs:

        • 50 % probability : (original , random mutant)
        • 50 % probability : (mutant_i , mutant_j)   with i ≠ j

    This produces stronger invariance to mutation noise than always
    anchoring on the original snapshot.
    """

    def __init__(self, base_ds: DevignDataset):
        super().__init__()
        self.base_ds = base_ds

        # ------------------------------------------------------------------
        # Build  func_id → list[index_in_base_ds]  mapping
        # ------------------------------------------------------------------
        self.func2idx: dict[int, list[int]] = defaultdict(list)
        for ds_idx, start_row in enumerate(base_ds.window_starts):
            fid = int(base_ds.row_df.loc[start_row, "index"])
            self.func2idx[fid].append(ds_idx)

        # Keep only functions that have ≥ 2 snapshots
        self.valid_funcs: list[int] = [
            fid for fid, idxs in self.func2idx.items() if len(idxs) > 1
        ]

    # ------------------------------------------------------------------
    def __len__(self) -> int:
        # one entry per *function*, not per snapshot
        return len(self.valid_funcs)

    # ------------------------------------------------------------------
    def __getitem__(self, idx: int) -> dict[str, Data]:
        """
        Returns
        -------
        dict with keys:
            • 'orig' : torch_geometric.data.Data
            • 'adv'  : torch_geometric.data.Data
        """
        fid  = self.valid_funcs[idx]
        idxs = self.func2idx[fid]          # all snapshot indices of this func

        # ------------------------------------------------------------------
        # Decide which two snapshots to pair
        # ------------------------------------------------------------------
        if random.random() < 0.5:
            # 50 % : (original , random mutant)
            i_idx = idxs[0]                # by construction idx 0 = export.json
            j_idx = random.choice(idxs[1:])  # pick any mutant
        else:
            # 50 % : (mutant_i , mutant_j)  with i ≠ j
            i_idx, j_idx = random.sample(idxs[1:], 2)

        return {
            "orig": self.base_ds[i_idx],
            "adv":  self.base_ds[j_idx],
        }


class PairedContrastiveDataset(torch.utils.data.Dataset):
    """
    Simple 1:1 zip of two DevignDatasets of equal length.
    For each index i, returns {'orig': orig_ds[i], 'adv': adv_ds[i]}.
    """
    def __init__(self, orig_ds: DevignDataset, adv_ds: DevignDataset):
        assert len(orig_ds) == len(adv_ds), \
            f"orig ({len(orig_ds)}) vs adv ({len(adv_ds)}) lengths must match"
        self.orig_ds = orig_ds
        self.adv_ds  = adv_ds

    def __len__(self):
        return len(self.orig_ds)

    def __getitem__(self, i: int):
        return {
            "orig": self.orig_ds[i],
            "adv":  self.adv_ds[i],
        }


# ─────────────────────────────────────────────────────────────────────────────
# Model
# ─────────────────────────────────────────────────────────────────────────────

# ──────────────────────────────────────────────────────────────
# MPTCN-TTS  (Time-Then-Space GNN)
# ──────────────────────────────────────────────────────────────

class MPTCNTTS(nn.Module):
    """
    Base MPTCN-TTS (Time-Then-Space):
      temporal encoder (TCN|GRU) -> spatial stack (Cheb|RGCN) -> pooling.
    No text fusion, no transformers.
    """
    def __init__(
        self,
        num_node_types: int,
        emb_dim: int = 64,
        hidden_dim: int = 64,
        L_T: int = 2,
        L_S: int = 2,
        Kt: int = 3,
        Ks: int = 3,
        dropout: float = 0.30,
        row_norm: bool = False,
        num_classes: int = 2,
        spatial_type: str = "cheb",     # {"cheb","rgcn"}
        num_relations: int | None = None,
        temporal: str = "tcn",          # {"tcn","gru"}
    ):
        super().__init__()
        self.Kt, self.Ks = int(Kt), int(Ks)
        self.emb_dim, self.hidden_dim = int(emb_dim), int(hidden_dim)
        self.temporal_kind = str(temporal).lower()
        self.spatial_type  = str(spatial_type).lower()

        # embeddings + simple projection (for T=1)
        self.node_emb   = nn.Embedding(num_node_types, self.emb_dim)
        self.input_proj = nn.Linear(self.emb_dim, self.hidden_dim)

        # temporal encoder (causal TCN or GRU)
        tcn_layers, in_ch = [], self.emb_dim
        for _ in range(int(L_T)):
            tcn_layers.append(nn.ConstantPad1d((self.Kt - 1, 0), 0.0))  # causal
            conv = nn.Conv1d(in_ch, self.hidden_dim, kernel_size=self.Kt, padding=0)
            if row_norm:
                conv = param.weight_norm(conv, dim=1, name="weight")
            tcn_layers += [
                conv,
                nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3),
                nn.ReLU(),
                nn.Dropout(dropout),
            ]
            in_ch = self.hidden_dim
        self.tcn = nn.Sequential(*tcn_layers)

        self.gru = nn.GRU(
            input_size=self.emb_dim,
            hidden_size=self.hidden_dim,
            num_layers=max(1, int(L_T)),
            batch_first=True,
        )

        # spatial stack
        if self.spatial_type == "rgcn":
            nr = int(num_relations or 1)
            self.spatial = nn.ModuleList([
                RGCNConv(self.hidden_dim, self.hidden_dim, num_relations=nr, num_bases=min(32, nr))
                for _ in range(int(L_S))
            ])
        else:
            self.spatial = nn.ModuleList([
                ChebConv(self.hidden_dim, self.hidden_dim, self.Ks)
                for _ in range(int(L_S))
            ])

        self.bn_layers = nn.ModuleList([
            nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3)
            for _ in range(int(L_S))
        ])
        self.dropout = nn.Dropout(dropout)

        # heads
        self.classifier = nn.Sequential(
            nn.Linear(self.hidden_dim, self.hidden_dim), nn.ReLU(), nn.Dropout(dropout),
            nn.Linear(self.hidden_dim, num_classes),
        )
        self.projector = nn.Sequential(
            nn.Linear(self.hidden_dim, 2 * self.hidden_dim),
            nn.BatchNorm1d(2 * self.hidden_dim, momentum=0.05, eps=1e-3),
            nn.ReLU(),
            nn.Linear(2 * self.hidden_dim, self.hidden_dim),
        )

        # safe gate (kept for compat; identity)
        self.attn_gate = nn.Identity()

    # time -> space
    def _encode_backbone(
        self,
        x_seq: torch.LongTensor,                # [N, T]
        edge_index: torch.LongTensor,           # [2, E]
        edge_type: Optional[torch.LongTensor] = None
    ) -> torch.Tensor:
        N, T = x_seq.shape
        if T == 1:
            h = self.input_proj(self.node_emb(x_seq).squeeze(1))   # [N,H]
        else:
            if self.temporal_kind == "gru":
                x_emb = self.node_emb(x_seq)                       # [N,T,E]
                out, _ = self.gru(x_emb)                           # [N,T,H]
                h = out[:, -1, :]                                  # last step
            else:
                x_emb = self.node_emb(x_seq).permute(0, 2, 1)      # [N,E,T]
                h_feat = self.tcn(x_emb)                           # [N,H,T]
                h = h_feat[:, :, -1]                               # causal last step

        for conv, bn in zip(self.spatial, self.bn_layers):
            res = h
            if self.spatial_type == "rgcn":
                h = conv(h, edge_index, edge_type)
            else:
                h = conv(h, edge_index)
            h = F.relu(bn(h))
            h = self.dropout(h) + res.clone()


        return h * (self.attn_gate(h) if hasattr(self, "attn_gate") else 1.0)

    def forward(self, data: Batch) -> torch.Tensor:
        et = getattr(data, "edge_type", None)
        h  = self._encode_backbone(data.x, data.edge_index, et)
        g  = global_add_pool(h, data.batch)
        return self.classifier(g)

    def embed(self, data: Batch) -> torch.Tensor:
        et = getattr(data, "edge_type", None)
        h  = self._encode_backbone(data.x, data.edge_index, et)
        g  = global_add_pool(h, data.batch)
        z  = self.projector(g)
        return F.normalize(z, dim=1, eps=1e-8)

    def graph_embed(self, data: Batch) -> torch.Tensor:
        et = getattr(data, "edge_type", None)
        h  = self._encode_backbone(data.x, data.edge_index, et)
        return global_add_pool(h, data.batch)


# ──────────────────────────────────────────────────────────────
# EnhancedMPTCNTTS – multi–scale, temporal-attn, domain-aware
# ──────────────────────────────────────────────────────────────

class EnhancedMPTCNTTS(MPTCNTTS):
    def __init__(self, *, domain_adapt: bool = True,
                 dilations: tuple[int, ...] = (1, 2, 4), **kwargs):
        super().__init__(**kwargs)
        # drop base single-path TCN
        del self.tcn

        row_norm  = bool(kwargs.get("row_norm", False))
        Ls        = int(kwargs.get("L_S", 2))
        drop_p    = float(kwargs.get("dropout", 0.30))

        # multi-branch temporal convs
        n_br = len(dilations)
        base_w = self.hidden_dim // n_br
        branch_dims = [base_w] * n_br
        for i in range(self.hidden_dim - base_w * n_br):
            branch_dims[i] += 1

        branches = []
        for i, d in enumerate(dilations):
            pad  = nn.ConstantPad1d((d * (self.Kt - 1), 0), 0.0)
            conv = nn.Conv1d(self.emb_dim, branch_dims[i],
                             kernel_size=self.Kt, dilation=d, padding=0)
            if row_norm:
                conv = param.weight_norm(conv, dim=1, name="weight")
            branches.append(nn.Sequential(
                pad, conv,
                nn.BatchNorm1d(branch_dims[i], momentum=0.05, eps=1e-3),
                nn.ReLU(), nn.Dropout(drop_p),
            ))
        self.tcn_branches = nn.ModuleList(branches)

        self.tcn_out_dim = sum(branch_dims)
        self.realign = (nn.Identity() if self.tcn_out_dim == self.hidden_dim
                        else nn.Conv1d(self.tcn_out_dim, self.hidden_dim, kernel_size=1, bias=False))
        self.temp_attn = nn.Conv1d(self.hidden_dim, 1, kernel_size=1, bias=False)
        self.attn_gate = nn.Sequential(nn.Linear(self.hidden_dim, 1), nn.Sigmoid())
        self.domain_adapter = (DomainAdapter(self.hidden_dim) if domain_adapt else nn.Identity())

        # rebuild spatial stack if cheb
        if self.spatial_type != "rgcn":
            self.spatial   = nn.ModuleList([ChebConv(self.hidden_dim, self.hidden_dim, self.Ks) for _ in range(Ls)])
            self.bn_layers = nn.ModuleList(
                [nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3) for _ in range(Ls)]
            )

    def _encode_backbone(self, x_seq, edge_index, edge_type=None):
        x = self.node_emb(x_seq).permute(0, 2, 1)              # [N,E,T]
        h_cat = torch.cat([b(x) for b in self.tcn_branches], dim=1)
        h_cat = self.realign(h_cat)                             # [N,H,T]
        w = F.softmax(self.temp_attn(h_cat), dim=2)             # [N,1,T]
        h = (h_cat * w).sum(dim=2)                              # [N,H]
        for conv, bn in zip(self.spatial, self.bn_layers):
            res = h
            if self.spatial_type == "rgcn":
                h = conv(h, edge_index, edge_type)
            else:
                h = conv(h, edge_index)
            h = F.relu(bn(h))
            h = self.dropout(h) + res.clone()
        return h * self.attn_gate(h)

    def forward(self, data: Batch) -> torch.Tensor:
        et = getattr(data, "edge_type", None)
        h  = self._encode_backbone(data.x, data.edge_index, et)
        g  = global_add_pool(h, data.batch)
        return self.classifier(g)





# ──────────────────────────────────────────────────────────────
# PNABaseline (homogeneous, time→space like MPTCN_TTS, PNA spatial)
# ──────────────────────────────────────────────────────────────
class PNABaseline(nn.Module):
    def __init__(self,
                 num_node_types: int,
                 emb_dim: int = 64,
                 hidden_dim: int = 256,
                 L_T: int = 2,
                 L_S: int = 4,
                 Kt: int = 3,
                 dropout: float = 0.30,
                 row_norm: bool = False,
                 num_classes: int = 2,
                 deg: torch.Tensor | None = None):
        super().__init__()
        self.emb_dim = int(emb_dim)
        self.hidden_dim = int(hidden_dim)
        self.Kt = int(Kt)

        # token embedding
        self.node_emb   = nn.Embedding(num_node_types, self.emb_dim)
        self.input_proj = nn.Linear(self.emb_dim, self.hidden_dim)

        # temporal encoder (causal TCN stack)
        tcn_layers, in_ch = [], self.emb_dim
        for _ in range(int(L_T)):
            tcn_layers.append(nn.ConstantPad1d((self.Kt - 1, 0), 0.0))
            conv = nn.Conv1d(in_ch, self.hidden_dim, kernel_size=self.Kt, padding=0)
            if row_norm:
                # requires: from torch.nn.utils import parametrize as param
                conv = param.weight_norm(conv, dim=1, name="weight")
            tcn_layers += [
                conv,
                nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3),
                nn.ReLU(),
                nn.Dropout(dropout),
            ]
            in_ch = self.hidden_dim
        self.tcn = nn.Sequential(*tcn_layers)

        # PNA spatial stack
        aggregators = ['mean', 'min', 'max', 'std']
        scalers     = ['identity', 'amplification', 'attenuation']
        self.pna_layers = nn.ModuleList([
            PNAConv(self.hidden_dim, self.hidden_dim,
                    aggregators=aggregators, scalers=scalers,
                    edge_dim=None, towers=1, pre_layers=1, post_layers=1,
                    divide_input=False, deg=deg)
            for _ in range(int(L_S))
        ])
        self.bn_layers = nn.ModuleList([
            nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3)
            for _ in range(int(L_S))
        ])
        self.dropout = nn.Dropout(dropout)

        # ---- Heads ----
        # Classifier: add LayerNorm to tame large magnitudes and ensure independent 2-logit head
        self.classifier = nn.Sequential(
            nn.LayerNorm(self.hidden_dim),
            nn.Linear(self.hidden_dim, self.hidden_dim),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(self.hidden_dim, num_classes),   # <- truly 2 independent logits
        )

        # Projector for contrastive/embedding paths
        self.projector = nn.Sequential(
            nn.Linear(self.hidden_dim, 2 * self.hidden_dim),
            nn.BatchNorm1d(2 * self.hidden_dim, momentum=0.05, eps=1e-3),
            nn.ReLU(),
            nn.Linear(2 * self.hidden_dim, self.hidden_dim),
        )

    def _encode_temporal(self, x_seq: torch.LongTensor) -> torch.Tensor:
        N, T = x_seq.shape
        if T == 1:
            h = self.input_proj(self.node_emb(x_seq).squeeze(1))  # [N,H]
        else:
            x_emb = self.node_emb(x_seq).permute(0, 2, 1)         # [N,E,T]
            h_feat = self.tcn(x_emb)                              # [N,H,T]
            h = h_feat[:, :, -1]                                  # last step (causal)
        return h                                                  # [N,H]

    def forward(self, data: Data):
        h = self._encode_temporal(data.x)                         # [N,H]
        for conv, bn in zip(self.pna_layers, self.bn_layers):
            res = h
            h = conv(h, data.edge_index)                          # [N,H]
            h = F.relu(bn(h))
            h = self.dropout(h) + res                             # residual
        g = global_add_pool(h, data.batch)                        # [B,H]
        return self.classifier(g)                                 # [B,2]

    def embed(self, data: Data) -> torch.Tensor:
        h = self._encode_temporal(data.x)
        for conv, bn in zip(self.pna_layers, self.bn_layers):
            h = F.relu(bn(conv(h, data.edge_index)))
            h = self.dropout(h)
        g = global_add_pool(h, data.batch)                        # [B,H]
        z = self.projector(g)                                     # [B,H]
        return F.normalize(z, dim=1, eps=1e-8)

    def graph_embed(self, data: Data) -> torch.Tensor:
        h = self._encode_temporal(data.x)
        for conv, bn in zip(self.pna_layers, self.bn_layers):
            h = F.relu(bn(conv(h, data.edge_index)))
            h = self.dropout(h)
        return global_add_pool(h, data.batch)                     # [B,H]


# ──────────────────────────────────────────────────────────────
# DeeperGCNBaseline (homogeneous, TCN temporal → Deep GCN spatial)
# ──────────────────────────────────────────────────────────────
from torch_geometric.data import Data
from torch_geometric.nn import GCNConv, global_add_pool
from torch_geometric.nn.models import DeepGCNLayer

class DeeperGCNBaseline(nn.Module):
    def __init__(self,
                 num_node_types: int,
                 emb_dim: int = 64,
                 hidden_dim: int = 256,
                 L_T: int = 2,          # temporal layers (TCN)
                 L_S: int = 6,          # spatial layers (DeepGCN)
                 Kt: int = 3,           # temporal kernel
                 dropout: float = 0.30,
                 row_norm: bool = False,
                 num_classes: int = 2):
        super().__init__()
        self.emb_dim    = int(emb_dim)
        self.hidden_dim = int(hidden_dim)
        self.Kt         = int(Kt)

        # --- token embedding + linear projection ---
        self.node_emb   = nn.Embedding(num_node_types, self.emb_dim)
        self.input_proj = nn.Linear(self.emb_dim, self.hidden_dim)

        # --- causal TCN temporal encoder ---
        tcn_layers, in_ch = [], self.emb_dim
        for _ in range(int(L_T)):
            tcn_layers.append(nn.ConstantPad1d((self.Kt - 1, 0), 0.0))
            conv = nn.Conv1d(in_ch, self.hidden_dim, kernel_size=self.Kt, padding=0)
            if row_norm:
                conv = param.weight_norm(conv, dim=1, name="weight")
            tcn_layers += [
                conv,
                nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3),
                nn.ReLU(),
                nn.Dropout(dropout),
            ]
            in_ch = self.hidden_dim
        self.tcn = nn.Sequential(*tcn_layers)

        # --- DeepGCN spatial stack ---
        L_S = int(L_S)
        self.gcn_convs = nn.ModuleList([
            GCNConv(self.hidden_dim, self.hidden_dim)
            for _ in range(L_S)
        ])
        # IMPORTANT: pass **modules**, not strings, to DeepGCNLayer
        self.gcn_norms = nn.ModuleList([
            nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3)
            for _ in range(L_S)
        ])
        self.gcn_acts = nn.ModuleList([
            nn.ReLU(inplace=True)
            for _ in range(L_S)
        ])
        self.gcn_layers = nn.ModuleList([
            DeepGCNLayer(
                conv=self.gcn_convs[i],
                norm=self.gcn_norms[i],   # module
                act=self.gcn_acts[i],     # module
                block='res+',
                dropout=dropout,
            )
            for i in range(L_S)
        ])

        self.dropout = nn.Dropout(dropout)

        # --- heads ---
        self.classifier = nn.Sequential(
            nn.Linear(self.hidden_dim, self.hidden_dim), nn.ReLU(), nn.Dropout(dropout),
            nn.Linear(self.hidden_dim, num_classes),
        )
        # projector for SupCon / contrastive
        self.projector = nn.Sequential(
            nn.Linear(self.hidden_dim, 2 * self.hidden_dim),
            nn.BatchNorm1d(2 * self.hidden_dim, momentum=0.05, eps=1e-3),
            nn.ReLU(),
            nn.Linear(2 * self.hidden_dim, self.hidden_dim),
        )

    # ---- temporal encoder (tokens → last-step features) ----
    def _encode_temporal(self, x_seq: torch.LongTensor) -> torch.Tensor:
        # x_seq: [N, T] of token ids
        N, T = x_seq.shape
        if T == 1:
            h = self.input_proj(self.node_emb(x_seq).squeeze(1))  # [N,E]→[N,H]
        else:
            x_emb = self.node_emb(x_seq).permute(0, 2, 1)         # [N,E,T]
            h_feat = self.tcn(x_emb)                               # [N,H,T]
            h = h_feat[:, :, -1]                                   # last step (causal)
        return h  # [N,H]

    # ---- forward: TCN → DeepGCN → pool → classifier ----
    def forward(self, data: Data):
        h = self._encode_temporal(data.x)                          # [N,H]
        for layer in self.gcn_layers:
            h = layer(h, data.edge_index)                          # DeepGCNLayer applies conv+norm+act(+res)
        g = global_add_pool(h, data.batch)                         # [B,H]
        return self.classifier(g)                                   # [B,2]

    # ---- embed: features for SupCon ----
    def embed(self, data: Data) -> torch.Tensor:
        h = self._encode_temporal(data.x)
        for layer in self.gcn_layers:
            h = layer(h, data.edge_index)
        g = global_add_pool(h, data.batch)
        z = self.projector(g)
        return F.normalize(z, dim=1, eps=1e-8)

    # ---- graph_embed: penultimate pooled features ----
    def graph_embed(self, data: Data) -> torch.Tensor:
        h = self._encode_temporal(data.x)
        for layer in self.gcn_layers:
            h = layer(h, data.edge_index)
        return global_add_pool(h, data.batch)



# --- HGT variant on HeteroData ------------------------------------------------
class HGTMPTCNTTS(nn.Module):
    """
    HGT version of MPTCN-TTS on HeteroData:
      • temporal encode per node type (TCN|GRU)
      • HGTConv stack over observed edge types only (batch-pruned)
      • safe pooling across node types
    """
    def __init__(self,
                 node_types: list[str],
                 edge_types: list[tuple[str, str, str]],
                 num_node_types: int,
                 emb_dim=64, hidden_dim=128,
                 L_T=2, L_S=2, Kt=3, dropout=0.3, temporal="tcn",
                 num_classes=2,
                 hgt_heads: int = 2):
        super().__init__()
        # --- metadata (already pruned in train(); do NOT touch here) ---
        self.node_types = list(node_types)
        self.edge_types = [tuple(t) for t in edge_types]
        self.metadata   = (self.node_types, self.edge_types)
        self.edge_types_set = set(self.edge_types)

        print(f"[HGT] node_types={len(self.node_types)}, edge_types={len(self.edge_types)}")

        # --- dims/temporal ---
        self.emb_dim = int(emb_dim)
        self.hidden_dim = int(hidden_dim)
        self.temporal_kind = str(temporal).lower()

        self.node_emb = nn.Embedding(num_node_types, self.emb_dim)

        # light multi-layer TCN branches (averaged) OR GRU
        self.branches = nn.ModuleList([
            nn.Sequential(
                nn.ConstantPad1d((Kt - 1, 0), 0.0),
                nn.Conv1d(self.emb_dim, self.hidden_dim, Kt, padding=0),
                nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3),
                nn.ReLU(), nn.Dropout(dropout)
            ) for _ in range(int(L_T))
        ])
        self.gru = nn.GRU(self.emb_dim, self.hidden_dim,
                          num_layers=max(1, int(L_T)), batch_first=True)

        # HGT stack
        self.hgt_layers = nn.ModuleList([
            HGTConv(in_channels=self.hidden_dim,
                    out_channels=self.hidden_dim,
                    metadata=self.metadata,
                    heads=int(hgt_heads))
            for _ in range(int(L_S))
        ])

        # BN per node type per layer
        self.bn_layers = nn.ModuleList([
            nn.ModuleDict({nt: nn.BatchNorm1d(self.hidden_dim, momentum=0.05, eps=1e-3)
                           for nt in self.node_types})
            for _ in range(int(L_S))
        ])
        self.dropout = nn.Dropout(dropout)

        # heads
        self.classifier = nn.Sequential(
            nn.Linear(self.hidden_dim, self.hidden_dim), nn.ReLU(), nn.Dropout(dropout),
            nn.Linear(self.hidden_dim, num_classes)
        )
        self.projector  = nn.Sequential(
            nn.Linear(self.hidden_dim, 2 * self.hidden_dim),
            nn.BatchNorm1d(2 * self.hidden_dim, momentum=0.05, eps=1e-3),
            nn.ReLU(), nn.Linear(2 * self.hidden_dim, self.hidden_dim)
        )
        self.domain_adapter = DomainAdapter(self.hidden_dim)




        # --- helpers to keep HGT stable across batches --------------------------------
    def _ordered_hgt_inputs(self, h_dict: dict[str, torch.Tensor]) -> dict[str, torch.Tensor]:
        """
        Return an OrderedDict-like dict whose keys follow self.node_types exactly.
        Any node type missing in this batch is filled with a [0, H] empty tensor.
        """
        if len(h_dict) == 0:
            # never happens, but be defensive
            device = next(self.parameters()).device
            return {nt: torch.zeros(0, self.hidden_dim, device=device) for nt in self.node_types}

        # infer dtype/device from any present tensor
        _any = next(iter(h_dict.values()))
        device = _any.device
        dtype  = _any.dtype

        ordered = {}
        for nt in self.node_types:
            if nt in h_dict:
                ordered[nt] = h_dict[nt]
            else:
                ordered[nt] = torch.zeros(0, self.hidden_dim, device=device, dtype=dtype)
        return ordered

    # REPLACE the whole _build_edge_index_dict with this
    def _build_edge_index_dict(self, data: HeteroData) -> dict:
        """
        Build edge_index_dict aligned to metadata and **trim OOB** edges.
        Linear-time assembly (list->single cat) and optional per-type cap.

        Uses: self.max_edges_per_type (int|None) if present.
        """
        dev = self.node_emb.weight.device
        edge_index_dict = {}

        # helpers
        def _nn(nt: str) -> int:
            try:
                st = data[nt]
                if getattr(st, "x_seq", None) is not None:
                    return int(st.x_seq.size(0))
                if getattr(st, "num_nodes", None) is not None:
                    return int(st.num_nodes)
            except Exception:
                pass
            return 0

        # collect lists, then cat once – much faster than repeated concatenation
        tmp_lists = {}  # (src,rel,dst) -> list[tensor [2, e_i]]

        for et in getattr(data, "edge_types", []):
            store = data[et] if hasattr(data, "__getitem__") else None
            if store is None or not hasattr(store, "edge_index"):
                continue

            key = et if et in self.edge_types_set else (et[0], "UNK", et[2])
            if key not in self.edge_types_set:
                continue

            ei = store.edge_index
            if ei is None or ei.numel() == 0 or ei.dim() != 2 or ei.size(0) != 2:
                continue

            if ei.device != dev:
                ei = ei.to(dev, non_blocking=True)

            src_nt, _, dst_nt = key
            nsrc, ndst = _nn(src_nt), _nn(dst_nt)
            if nsrc <= 0 or ndst <= 0:
                continue

            ok = (ei[0] >= 0) & (ei[0] < nsrc) & (ei[1] >= 0) & (ei[1] < ndst)
            if ok.dim() > 1:
                ok = ok.all(dim=0)
            if ok.sum().item() == 0:
                continue

            ei = ei[:, ok].contiguous()

            # optional per-type cap (to keep worst-case stores bounded)
            cap = getattr(self, "max_edges_per_type", None)
            if cap is not None and ei.size(1) > int(cap):
                ei = ei[:, :int(cap)].contiguous()

            lst = tmp_lists.get(key)
            if lst is None:
                tmp_lists[key] = [ei]
            else:
                lst.append(ei)

        # finalize once
        for k, parts in tmp_lists.items():
            if len(parts) == 1:
                edge_index_dict[k] = parts[0]
            else:
                edge_index_dict[k] = torch.cat(parts, dim=1).contiguous()

        return edge_index_dict




    def _align_hdict_to_batch(self, data: HeteroData, h_dict: dict[str, torch.Tensor]) -> dict[str, torch.Tensor]:
        """
        Ensure each h_dict[nt] has exactly data[nt].x_seq.size(0) rows.
        Pad with zeros or trim as needed so HGT residual add cannot misalign.
        """
        dev  = self.node_emb.weight.device
        H    = int(self.hidden_dim)
        out: dict[str, torch.Tensor] = {}
        for nt in self.node_types:
            expN = 0
            if nt in getattr(data, "node_types", []):
                xseq = getattr(data[nt], "x_seq", None)
                if xseq is not None:
                    expN = int(xseq.size(0))
            h = h_dict.get(nt, None)
            if h is None:
                out[nt] = torch.zeros(expN, H, device=dev)
                continue
            if h.device != dev:
                h = h.to(dev, non_blocking=True)
            if h.size(0) == expN:
                out[nt] = h
            elif h.size(0) < expN:
                pad = torch.zeros(expN - h.size(0), h.size(1), device=dev, dtype=h.dtype)
                out[nt] = torch.cat([h, pad], dim=0)
            else:  # h.size(0) > expN
                out[nt] = h[:expN]
        return out


    def _pool_all_types(self, h_dict: dict[str, torch.Tensor], data: HeteroData) -> torch.Tensor:
        """
        Global add pool per node type with a common batch size B, then sum across types.
        """
        # Find B from any type that has a batch vector:
        B = 1
        for nt in self.node_types:
            bt = getattr(data[nt], "batch", None)
            if bt is not None and bt.numel() > 0:
                B = max(B, int(bt.max().item()) + 1)

        outs = []
        for nt in self.node_types:
            h  = h_dict[nt]
            bt = getattr(data[nt], "batch", None)
            if bt is None:
                bt = torch.zeros(h.size(0), dtype=torch.long, device=h.device)
            outs.append(global_add_pool(h, bt, size=B))
        return torch.stack(outs, dim=0).sum(dim=0)  # [B, H]



    # ---------- helpers ----------
    def _build_x_seq_dict(self, data: HeteroData) -> "OrderedDict[str, torch.Tensor]":
        """
        Collect x_seq per node type in a stable order (=metadata node_types).
        """
        out = OrderedDict()
        for nt in self.node_types:
            if hasattr(data[nt], "x_seq"):
                out[nt] = data[nt].x_seq
        return out

    @staticmethod
    def _prune_edges(edge_index_dict: dict,
                     allowed: set[tuple[str, str, str]]) -> dict:
        """
        Keep only (src,rel,dst) present in this batch AND registered in HGT.
        Drop empty tensors.
        """
        pruned = {}
        for k, ei in edge_index_dict.items():
            if k in allowed and ei is not None and ei.numel() > 0:
                pruned[k] = ei
        return pruned

    @staticmethod
    def _pool_per_type(h_dict: dict, data: HeteroData) -> torch.Tensor:
        """
        Global add pool per node type, align to common batch size B, and sum.
        """
        B = 1
        for nt, h in h_dict.items():
            bt = getattr(data[nt], "batch", None)
            if bt is not None and bt.numel() > 0:
                B = max(B, int(bt.max().item()) + 1)

        g_list = []
        for nt, h in h_dict.items():
            bt = getattr(data[nt], "batch", None)
            if bt is None:
                bt = torch.zeros(h.size(0), dtype=torch.long, device=h.device)
            g_nt = global_add_pool(h, bt, size=B)
            g_list.append(g_nt)
        return torch.stack(g_list, dim=0).sum(dim=0)  # [B, H]

    # ---------- temporal ----------
    def temporal_encode(self, x_seq_dict: "OrderedDict[str, torch.Tensor]") -> dict[str, torch.Tensor]:
        h_dict = {}
        dev = self.node_emb.weight.device
        for nt, x_seq in x_seq_dict.items():              # [N_t, T]
            if x_seq.device != dev:
                x_seq = x_seq.to(dev, non_blocking=True)
            if x_seq.dtype != torch.long:
                x_seq = x_seq.long()

            # Constant-token detector (min==max over all rows/steps)
            if x_seq.numel() > 0 and (x_seq.min() == x_seq.max()):
                # mark on data via side-channel if present
                try:
                    setattr(x_seq, "_const_type", nt)
                except Exception:
                    pass

            x = self.node_emb(x_seq).permute(0, 2, 1)     # [N_t, E, T]
            if x_seq.size(-1) == 1:
                h = x.squeeze(-1)
            else:
                if self.temporal_kind == "gru":
                    out, _ = self.gru(x.permute(0, 2, 1))  # [N_t, T, H]
                    h = out[:, -1, :]
                else:
                    outs = [br(x)[:, :, -1] for br in self.branches]
                    h = torch.mean(torch.stack(outs, dim=0), dim=0)
            h_dict[nt] = h
        return h_dict

    # ---------- forward paths ----------
    def forward(self, data: HeteroData) -> torch.Tensor:
        dev = self.node_emb.weight.device
        with torch.cuda.amp.autocast(enabled=False):
            # HeteroData now cached device-agnostic; just ensure device
            if getattr(data, "__cached_ok", False):
                data = data.to(dev, non_blocking=True)
            else:
                data = data.to(dev, non_blocking=True)
                try:
                    _sanitize_hetero_batch_(data,
                                            num_node_types=int(self.node_emb.num_embeddings),
                                            device=dev)
                    setattr(data, "__cached_ok", True)
                except Exception:
                    pass


        # Collect per-type sequences present in THIS batch
        x_seq_dict = {nt: data[nt].x_seq
                    for nt in getattr(self, "node_types", [])
                    if (nt in getattr(data, "node_types", []) and hasattr(data[nt], "x_seq"))}

        # Degenerate batch: return zero graph safely
        # Degenerate batch handling: mark and (optionally) raise to skip upstream
        if not x_seq_dict:
            setattr(data, "_degenerate", True)
            # NOTE: We'll wire the train/val loop (Part 2) to catch _DegenerateBatch and skip.
            # If you want hard-fail here immediately, uncomment the next line:
            # raise _DegenerateBatch("[Degenerate] No x_seq for any node type in batch")
            B = 1
            for nt in getattr(data, "node_types", []):
                bt = getattr(data[nt], "batch", None)
                if bt is not None and bt.numel() > 0:
                    B = max(B, int(bt.max().item()) + 1)
            g = torch.zeros(B, self.hidden_dim, device=dev)
            return self.classifier(g)


        # Temporal encode → align rows to batch, then ensure all keys exist
        h_dict = self.temporal_encode(x_seq_dict)
        h_dict = self._align_hdict_to_batch(data, h_dict)
        h_dict = self._ordered_hgt_inputs(h_dict)

        # Edges: build & prune strictly within per-type bounds
        edge_index_dict = self._build_edge_index_dict(data)
        edge_index_dict = self._prune_edges(edge_index_dict, self.edge_types_set)

        # HGT stack
        for hgt, bns in zip(self.hgt_layers, self.bn_layers):
            h_dict = hgt(h_dict, edge_index_dict)
            for nt in h_dict:
                if h_dict[nt].size(0) == 0:
                    continue
                h_res = h_dict[nt]
                h_new = self.dropout(F.relu(bns[nt](h_dict[nt].clone())))
                h_dict[nt] = h_new + h_res


        # Pool per type to common B and sum
        B = 1
        for nt in self.node_types:
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is not None and bt.numel() > 0:
                B = max(B, int(bt.max().item()) + 1)

        g_list = []
        for nt in self.node_types:
            h = h_dict[nt]
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is None:
                bt = torch.zeros(h.size(0), dtype=torch.long, device=h.device)
            g_nt = global_add_pool(h, bt, size=B)
            g_list.append(g_nt)

        g = torch.stack(g_list, dim=0).sum(dim=0)  # [B, H]
        return self.classifier(g)



    def embed(self, data: HeteroData) -> torch.Tensor:
        dev = self.node_emb.weight.device
        with torch.cuda.amp.autocast(enabled=True):  # <<< add this line
                data = data.to(dev, non_blocking=True)

                # Sanitize hetero batch (bounds & devices)
                try:
                    _sanitize_hetero_batch_(data,
                                            num_node_types=int(self.node_emb.num_embeddings),
                                            device=dev)
                except Exception:
                    pass

        x_seq_dict = {nt: data[nt].x_seq
                    for nt in getattr(self, "node_types", [])
                    if (nt in getattr(data, "node_types", []) and hasattr(data[nt], "x_seq"))}

        if not x_seq_dict:
            B = 1
            for nt in getattr(data, "node_types", []):
                bt = getattr(data[nt], "batch", None)
                if bt is not None and bt.numel() > 0:
                    B = max(B, int(bt.max().item()) + 1)
            g = torch.zeros(B, self.hidden_dim, device=dev)
            z = self.projector(g)
            return F.normalize(z, dim=1, eps=1e-8)

        h_dict = self.temporal_encode(x_seq_dict)
        h_dict = self._align_hdict_to_batch(data, h_dict)
        h_dict = self._ordered_hgt_inputs(h_dict)

        edge_index_dict = self._build_edge_index_dict(data)
        edge_index_dict = self._prune_edges(edge_index_dict, self.edge_types_set)

        for hgt, bns in zip(self.hgt_layers, self.bn_layers):
            h_dict = hgt(h_dict, edge_index_dict)
            for nt in h_dict:
                if h_dict[nt].size(0) == 0:
                    continue
                h_dict[nt] = self.dropout(F.relu(bns[nt](h_dict[nt])))

        B = 1
        for nt in self.node_types:
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is not None and bt.numel() > 0:
                B = max(B, int(bt.max().item()) + 1)

        g_list = []
        for nt in self.node_types:
            h = h_dict[nt]
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is None:
                bt = torch.zeros(h.size(0), dtype=torch.long, device=h.device)
            g_nt = global_add_pool(h, bt, size=B)
            g_list.append(g_nt)

        g = torch.stack(g_list, dim=0).sum(dim=0)
        z = self.projector(g)
        return F.normalize(z, dim=1, eps=1e-8)


    def graph_embed(self, data: HeteroData) -> torch.Tensor:
        dev = self.node_emb.weight.device
        with torch.cuda.amp.autocast(enabled=True):  # <<< add this line
                data = data.to(dev, non_blocking=True)

                # Sanitize hetero batch (bounds & devices)
                try:
                    _sanitize_hetero_batch_(data,
                                            num_node_types=int(self.node_emb.num_embeddings),
                                            device=dev)
                except Exception:
                    pass

        x_seq_dict = {nt: data[nt].x_seq
                    for nt in getattr(self, "node_types", [])
                    if (nt in getattr(data, "node_types", []) and hasattr(data[nt], "x_seq"))}

        if not x_seq_dict:
            B = 1
            for nt in getattr(data, "node_types", []):
                bt = getattr(data[nt], "batch", None)
                if bt is not None and bt.numel() > 0:
                    B = max(B, int(bt.max().item()) + 1)
            return torch.zeros(B, self.hidden_dim, device=dev)

        h_dict = self.temporal_encode(x_seq_dict)
        h_dict = self._align_hdict_to_batch(data, h_dict)
        h_dict = self._ordered_hgt_inputs(h_dict)

        edge_index_dict = self._build_edge_index_dict(data)
        edge_index_dict = self._prune_edges(edge_index_dict, self.edge_types_set)

        for hgt, bns in zip(self.hgt_layers, self.bn_layers):
            h_dict = hgt(h_dict, edge_index_dict)
            for nt in h_dict:
                if h_dict[nt].size(0) == 0:
                    continue
                h_dict[nt] = self.dropout(F.relu(bns[nt](h_dict[nt])))

        B = 1
        for nt in self.node_types:
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is not None and bt.numel() > 0:
                B = max(B, int(bt.max().item()) + 1)

        g_list = []
        for nt in self.node_types:
            h = h_dict[nt]
            bt = getattr(data[nt], "batch", None) if nt in getattr(data, "node_types", []) else None
            if bt is None:
                bt = torch.zeros(h.size(0), dtype=torch.long, device=h.device)
            g_nt = global_add_pool(h, bt, size=B)
            g_list.append(g_nt)

        return torch.stack(g_list, dim=0).sum(dim=0)  # [B, H]




# ──────────────────────────────────────────────────────────────
# Numerically-stable InfoNCE (no -inf in fp16, explicit ε-guard)
# ──────────────────────────────────────────────────────────────
def info_nce_loss(
    z1: torch.Tensor,
    z2: torch.Tensor,
    temperature: float = 0.1,
    eps: float = 1e-8,
    block_rows: int = 64,
    block_cols: int = 64,
) -> torch.Tensor:
    """
    CUBLAS‑free InfoNCE:
      - normalizes z1/z2
      - builds the 2B x 2B similarity matrix using broadcasted dot products
        in blocks (elementwise mul + sum), avoiding GEMM entirely.
    """
    # Normalize in fp32
    z1 = F.normalize(z1.float().contiguous(), dim=1, eps=eps)
    z2 = F.normalize(z2.float().contiguous(), dim=1, eps=eps)

    B, D = z1.shape
    z = torch.cat([z1, z2], dim=0)  # [2B, D]

    N = z.size(0)
    sim = z.new_empty((N, N))

    # Build similarity by blocks: sim[i:i+br, j:j+bc] = (zi * zj).sum(-1)
    br = max(16, min(block_rows, N))
    bc = max(16, min(block_cols, N))
    for i in range(0, N, br):
        zi = z[i:i+br]                    # [br, D]
        zi = zi.unsqueeze(1)              # [br, 1, D]
        for j in range(0, N, bc):
            zj = z[j:j+bc]                # [bc, D]
            # broadcasted dot product (no GEMM):
            s = (zi * zj.unsqueeze(0)).sum(dim=-1)   # [br, bc]
            sim[i:i+br, j:j+bc] = s

    sim = sim / max(temperature, eps)

    # Mask self‑similarities with a big negative that’s safe in fp32
    eye = torch.eye(N, device=sim.device, dtype=torch.bool)
    sim.masked_fill_(eye, -1e4)

    # Positives: (0↔B), (1↔B+1), …
    labels = torch.arange(B, device=sim.device)
    labels = torch.cat([labels + B, labels], dim=0)

    return F.cross_entropy(sim, labels)
# ───────────────────────────────────────────────────────────────────────────

def instance_contrastive_loss(z: torch.Tensor,
                              ids: torch.Tensor,       # function ids, shape [N]
                              temperature: float = 0.07,
                              eps: float = 1e-8) -> torch.Tensor:
    z   = F.normalize(z, dim=1, eps=eps)                 # [N, D]
    sim = (z @ z.t()) / max(temperature, eps)            # [N, N]

    N   = sim.size(0)
    eye = torch.eye(N, device=z.device, dtype=torch.bool)
    sim = sim.masked_fill(eye, -1e4)                     # drop self

    same = (ids.view(-1, 1) == ids.view(1, -1)) & (~eye) # positives mask

    log_prob = sim - torch.logsumexp(sim, dim=1, keepdim=True)
    pos_cnt  = same.float().sum(dim=1).clamp_min(1.0)
    loss     = -(log_prob * same.float()).sum(dim=1) / pos_cnt
    return loss.mean()


def supervised_contrastive_loss(z: torch.Tensor, y: torch.Tensor, temperature: float = 0.07, eps: float = 1e-8) -> torch.Tensor:
    """SupCon with labels; exclude self-comparisons."""
    z = F.normalize(z, dim=1, eps=eps)
    sim = (z @ z.t()) / max(temperature, eps)
    N = sim.size(0)
    eye = torch.eye(N, device=z.device, dtype=torch.bool)
    sim = sim.masked_fill(eye, -1e4)
    same = (y.view(-1, 1) == y.view(1, -1)) & (~eye)
    log_prob = sim - torch.logsumexp(sim, dim=1, keepdim=True)
    pos_cnt = same.float().sum(dim=1).clamp_min(1.0)
    loss = -(log_prob * same.float()).sum(dim=1) / pos_cnt
    return loss.mean()


# ─── Supervised Training ─────────────────────────────────────────────────────
def train_supervised(model, train_loader, val_loader, optimizer, criterion, device, args, ckpt_path: Path):
    best_f1, no_improve = 0.0, 0
    scaler = GradScaler()
    bf16 = torch.cuda.is_bf16_supported()

    for epoch in range(1, args.epochs + 1):
        model.train()
        total_loss = 0.0

        # optional unfreeze of text encoder
        if (getattr(args, "text_fusion", False)
            and getattr(args, "unfreeze_text_epoch", 0) > 0
            and epoch == args.unfreeze_text_epoch
            and hasattr(model, "text_model")
            and model.text_model is not None):
            for p in model.text_model.parameters():
                p.requires_grad = True
            print(f"[Info] Unfroze text encoder @ epoch {epoch}")

        # use full-fp32 on epoch 1; AMP from epoch 2 onward
        use_amp = True  # enable AMP from the first epoch for speed

        for batch in tqdm(train_loader, desc=f"Sup Epoch {epoch}/{args.epochs}"):
            batch = batch.to(device, non_blocking=True)
            optimizer.zero_grad(set_to_none=True)

            if use_amp:
                with autocast(dtype=(torch.bfloat16 if bf16 else torch.float16), enabled=True):
                    logits = model(batch)
                    loss   = criterion(logits, batch.y)
                try:
                    scaler.scale(loss).backward()
                except RuntimeError as e:
                    if "illegal memory access" in str(e).lower():
                        print("[Fatal] CUDA illegal memory access – exiting to reset context.")
                        import sys
                        sys.exit(2)   # do NOT call any torch.cuda.* here
                    raise

                scaler.unscale_(optimizer)
                torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
                scaler.step(optimizer)
                scaler.update()
            else:
                # full-fp32 path on epoch 1 (safer)
                logits = model(batch)
                loss   = criterion(logits, batch.y)
                try:
                    loss.backward()
                except RuntimeError as e:
                    if "illegal memory access" in str(e).lower():
                        print("[Fatal] CUDA illegal memory access – exiting to reset context.")
                        import sys
                        sys.exit(2)   # do NOT call any torch.cuda.* here
                    raise

                torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
                optimizer.step()


            total_loss += float(loss.item())

        val = evaluate(model, val_loader, device)
        print(f"[Epoch {epoch}] Train Loss: {total_loss/len(train_loader):.4f} | Val F1: {val['f1']:.4f}")

        if val["f1"] > best_f1 + 1e-3:
            best_f1, no_improve = val["f1"], 0
            torch.save(model.state_dict(), ckpt_path)
        else:
            no_improve += 1
            if no_improve >= args.early_stop:
                print("Early stopping triggered.")
                break


class FocalLoss(nn.Module):
    def __init__(self, gamma=2.0, weight=None):
        super().__init__()
        self.gamma = gamma
        self.weight = weight
        
    def forward(self, inputs, targets):
        ce_loss = F.cross_entropy(inputs, targets, weight=self.weight, reduction='none')
        pt = torch.exp(-ce_loss)
        return ((1 - pt) ** self.gamma * ce_loss).mean()





# ─────────────────────────────────────────────────────────────────────────────
# Evaluation helpers
# ─────────────────────────────────────────────────────────────────────────────
import numpy as np
import sklearn.metrics as skm



# ──────────────────────────────────────────────────────────────
# Helper: build degree histogram for PNA (homogeneous graphs only)
# ──────────────────────────────────────────────────────────────
def build_pna_degree_hist(ds, max_cap: int = 4096) -> torch.Tensor:
    """
    Returns a degree histogram tensor 'deg' of shape [max_degree+1].
    Only for homogeneous Data (spatial != HGT).
    """
    import torch
    max_deg = 0
    counts = {}
    for data in getattr(ds, "_cache", []):
        if not hasattr(data, "edge_index") or data.edge_index.numel() == 0:
            continue
        N = int(data.x.size(0))
        deg = torch.bincount(data.edge_index[0], minlength=N).cpu().tolist()
        for d in deg:
            counts[d] = counts.get(d, 0) + 1
            max_deg = max(max_deg, d)
        if max_deg > max_cap:
            break
    deg_hist = torch.zeros(max_deg + 1, dtype=torch.long)
    for d, c in counts.items():
        if d <= max_deg:
            deg_hist[d] = c
    if deg_hist.sum() == 0:
        deg_hist[0] = 1
    return deg_hist


import math
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.cuda.amp import autocast
import sklearn.metrics as skm
from tqdm import tqdm


# ──────────────────────────────────────────────────────────────
# numerics: prob/logit transforms (keep names)
# ──────────────────────────────────────────────────────────────
def _prob_to_logit(p: float, eps: float = 1e-6) -> float:
    p = float(np.clip(p, eps, 1.0 - eps))
    return float(np.log(p / (1.0 - p)))

def _logit_to_prob(z: float) -> float:
    # stable sigmoid
    if z >= 0:
        ez = math.exp(-z)
        return 1.0 / (1.0 + ez)
    else:
        ez = math.exp(z)
        return ez / (1.0 + ez)


def _jitter_thr(thr: float, eps: float = 1e-6) -> float:
    if thr <= eps: return eps
    if thr >= 1.0 - eps: return 1.0 - eps
    return float(thr)


# ──────────────────────────────────────────────────────────────
# temperature fitting / application (keep names)
# ──────────────────────────────────────────────────────────────
class TemperatureScaler(nn.Module):
    """Simple temperature wrapper used by fit_temperature."""
    def __init__(self, T: float = 1.0):
        super().__init__()
        self.log_T = nn.Parameter(torch.tensor(float(np.log(max(T, 1e-3))), dtype=torch.float32))

    def forward(self, logits: torch.Tensor) -> torch.Tensor:
        T = torch.clamp(self.log_T.exp(), 1e-3, 100.0)
        return logits / T


class _GapTemperature(nn.Module):
    def __init__(self, init_T: float = 1.0):
        super().__init__()
        self.log_T = nn.Parameter(torch.tensor(float(np.log(max(init_T, 1e-3))), dtype=torch.float32))
    def forward(self, d: torch.Tensor) -> torch.Tensor:
        # d is the logit gap (logit1 - logit0)
        T = torch.clamp(self.log_T.exp(), 0.4, 3.0)
        return d / T

@torch.no_grad()
def _collect_gaps_and_labels(model, loader, device):
    model.eval()
    ds, ys = [], []
    for batch in loader:
        b = batch.to(device, non_blocking=True)
        logits = model(b).float()
        logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
        d = logits[:, 1] - logits[:, 0]
        ds.append(d.detach().cpu())
        ys.append(b.y.detach().cpu())
    if not ds:  # empty
        return None, None
    return torch.cat(ds, 0).to(device), torch.cat(ys, 0).to(device)

@torch.no_grad()
def fit_temperature(model, loader, device, max_iter=200, lr=1e-2) -> float:
    """
    Fit a single temperature on VAL by minimizing NLL on the logit gap (Δlogit/T).
    Bounded T in [0.4, 3.0]. If improvement is tiny or the distribution is flat, return 1.0.
    """
    import torch
    import torch.nn as nn

    d, y = _collect_gaps_and_labels(model, loader, device)
    if (d is None) or (y is None) or (d.numel() == 0):
        return 1.0

    # If distribution is essentially flat, skip scaling
    if float(d.std().item()) < 1e-3:
        return 1.0

    ts = _GapTemperature(1.0).to(device)
    ce = nn.BCEWithLogitsLoss()
    opt = torch.optim.LBFGS(ts.parameters(), lr=lr, max_iter=max_iter, line_search_fn="strong_wolfe")

    # baseline NLL @ T=1
    base_loss = ce(d, y.float()).item()

    def closure():
        opt.zero_grad(set_to_none=True)
        dT = ts(d)
        loss = ce(dT, y.float())
        loss.backward()
        return loss

    opt.step(closure)
    T = float(torch.clamp(ts.log_T.exp(), 0.4, 3.0).item())

    # accept only if improved by a useful margin
    with torch.no_grad():
        final_loss = ce(d / max(T, 1e-6), y.float()).item()
    if (base_loss - final_loss) < 1e-4:
        return 1.0
    return T

def _apply_temperature(logits: torch.Tensor, T: float) -> torch.Tensor:
    # Guard T into a sane band; avoids division by ~0 or huge blowups
    T = float(max(0.1, min(10.0, T)))
    return logits / T


# ──────────────────────────────────────────────────────────────
# robust probability extraction (keep names)
# ──────────────────────────────────────────────────────────────
# helpers.py (or wherever you define it)
def _probs_from_logits_binary(logits: torch.Tensor, T: float = 1.0) -> torch.Tensor:
    """
    Stable p(y=1) for binary heads.
    - If shape [...,2]: use Δlogit = logit_pos - logit_neg
    - If shape [...,1] or [...]: treat as single-logit BCE head
    """
    z: torch.Tensor
    logits = logits.float()
    if logits.dim() == 1 or logits.size(-1) == 1:
        z = logits.squeeze(-1) / max(T, 1e-6)
    elif logits.size(-1) == 2:
        z = (logits[..., 1] - logits[..., 0]) / max(T, 1e-6)
    else:
        raise ValueError(f"Binary probability requested but logits shape={tuple(logits.shape)}")
    p = torch.sigmoid(z)
    return torch.nan_to_num(p, nan=0.5, posinf=1.0, neginf=0.0).clamp_(1e-6, 1.0 - 1e-6)




@torch.inference_mode()
def collect_probs_with_T(model, loader, device, T: float = 1.0):
    """
    Run model and return (y_true, y_prob) with optional temperature.
    Uses Δlogit/T → sigmoid for stability (no softmax).
    """
    model.eval()
    ys, probs = [], []
    T = float(max(0.1, min(10.0, T)))
    for batch in loader:
        batch = batch.to(device, non_blocking=True)
        with autocast(enabled=False):
            logits = model(batch).float()
        # apply temperature on the *gap*
        gap = (logits[:, 1] - logits[:, 0])
        gap = torch.nan_to_num(gap, nan=0.0, posinf=50.0, neginf=-50.0) / T
        p1 = torch.sigmoid(gap.clamp_(-60, 60))
        ys.extend(batch.y.detach().cpu().tolist())
        probs.extend(p1.detach().cpu().tolist())
    return np.asarray(ys), np.asarray(probs, dtype=np.float32)


# ──────────────────────────────────────────────────────────────
# collapse handling + PR threshold search (keep names)
# ──────────────────────────────────────────────────────────────
# ──────────────────────────────────────────────────────────────
# Single-source threshold calibration (keep these; delete others)
# ──────────────────────────────────────────────────────────────
import numpy as _np
import sklearn.metrics as _skm
import torch



def _pick_thr_on_collapse(
    y_true: _np.ndarray,
    y_prob: _np.ndarray,
    *,
    beta: float = 0.7,
    cap_over_base: float = 0.08,
    min_pos_frac: float = 0.01,
    eps: float = 1e-7,
) -> float:
    """
    When scores are ~constant near 0.5, try both sides and pick better F_beta.
    Uses strict '>' to turn probs -> labels.
    """
    best_thr, best_f = 0.5, -1.0
    for thr in (0.5 - eps, 0.5 + eps):
        y_pred = (y_prob > thr).astype(_np.int64)
        f = _skm.fbeta_score(y_true, y_pred, beta=beta, zero_division=0)
        if f > best_f:
            best_f, best_thr = f, float(thr)
    return float(best_thr)



def calibrate_threshold_from_arrays(
    y_true: np.ndarray,
    y_prob: np.ndarray,
    *,
    beta: float = 0.7,
    min_precision: float | None = None,
    max_pos_rate_over_base: float = 0.08,
    min_pos_frac: float = 0.01,
) -> float:
    """
    Array-only variant of PR-based threshold calibration.
    Mirrors `calibrate_threshold` but works directly from y_true/y_prob.
    """
    import numpy as np
    import sklearn.metrics as skm

    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = np.asarray(y_prob, dtype=np.float32)

    if y_prob.size == 0 or np.unique(y_true).size < 2:
        return 0.5

    base_rate = float(y_true.mean())
    upper_cap = min(0.75, base_rate + float(max_pos_rate_over_base))
    lower_cap = max(float(min_pos_frac), min(base_rate, 0.49))
    eps = 1e-6

    if float(np.std(y_prob)) < 1e-9:
        target_rate = float(np.clip(base_rate, lower_cap, upper_cap))
        thr = float(np.quantile(y_prob, 1.0 - target_rate))
        thr = float(np.clip(thr, eps, 1.0 - eps))
        n_pos = int((y_prob > thr).sum())
        if n_pos == 0: thr -= eps
        if n_pos == y_prob.size: thr += eps
        return float(thr)

    P, R, T = skm.precision_recall_curve(y_true, y_prob)
    if T.size == 0:
        target_rate = float(np.clip(base_rate, lower_cap, upper_cap))
        thr = float(np.quantile(y_prob, 1.0 - target_rate))
        thr = float(np.clip(thr, eps, 1.0 - eps))
        n_pos = int((y_prob > thr).sum())
        if n_pos == 0: thr -= eps
        if n_pos == y_prob.size: thr += eps
        return float(thr)

    p, r = P[:-1], R[:-1]
    beta2 = beta * beta
    fbeta = (1.0 + beta2) * p * r / (beta2 * p + r + 1e-12)
    fbeta = np.nan_to_num(fbeta, nan=0.0, posinf=0.0, neginf=0.0)

    idx = None
    if min_precision is not None:
        ok = p >= float(min_precision)
        if ok.any():
            idx = int((np.where(ok, fbeta, -np.inf)).argmax())
    if idx is None:
        idx = int(fbeta.argmax())

    chosen_thr = float(T[idx])
    pos_rate = float((y_prob > chosen_thr).mean())
    if pos_rate > upper_cap:
        chosen_thr = float(np.quantile(y_prob, 1.0 - upper_cap)) + eps
    elif pos_rate < lower_cap:
        chosen_thr = float(np.quantile(y_prob, 1.0 - lower_cap)) - eps

    chosen_thr = float(np.clip(chosen_thr, eps, 1.0 - eps))
    n_pos = int((y_prob > chosen_thr).sum())
    if n_pos == 0: chosen_thr -= eps
    if n_pos == y_prob.size: chosen_thr += eps

    if not np.isfinite(chosen_thr):
        chosen_thr = 0.5
    return float(chosen_thr)


# ──────────────────────────────────────────────────────────────
# PR-based optimal threshold calibration on VAL (probability-based)
# ──────────────────────────────────────────────────────────────
@torch.inference_mode()
def calibrate_threshold(
    model,
    loader,
    device,
    *,
    beta: float = 0.7,
    min_precision: float | None = None,
    max_pos_rate_over_base: float = 0.08,
    min_pos_frac: float = 0.01,
) -> float:
    """
    Robust PR-based threshold search for binary models.
    - Uses stable p(y=1) via Δlogit -> sigmoid (no softmax)
    - Enforces strict '>' and rate guardrails
    - Never returns exactly 0 or 1; clamps with small eps
    """
    import numpy as np
    import sklearn.metrics as skm
    model.eval()

    y_true, y_prob = [], []
    for batch in loader:
        b = batch.to(device, non_blocking=True)
        logits = model(b).float()
        logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
        p1 = _probs_from_logits_binary(logits)        # Δlogit -> sigmoid
        y_true.extend(b.y.detach().cpu().tolist())
        y_prob.extend(p1.detach().cpu().tolist())

    y_true = np.asarray(y_true, dtype=np.int64)
    y_prob = np.asarray(y_prob, dtype=np.float32)
    if y_prob.size == 0 or np.unique(y_true).size < 2:
        return 0.5

    base_rate = float(y_true.mean())
    upper_cap = min(0.75, base_rate + float(max_pos_rate_over_base))
    lower_cap = max(float(min_pos_frac), min(base_rate, 0.49))
    eps = 1e-6

    # Handle collapse safely
    if float(np.std(y_prob)) < 1e-9:
        # Pick near 0.5 but still apply guardrails via quantiles
        target_rate = float(np.clip(base_rate, lower_cap, upper_cap))
        thr = float(np.quantile(y_prob, 1.0 - target_rate))
        thr = float(np.clip(thr, eps, 1.0 - eps))
        # avoid all/none at strict '>'
        n_pos = int((y_prob > thr).sum())
        if n_pos == 0: thr -= eps
        if n_pos == y_prob.size: thr += eps
        return float(thr)

    P, R, T = skm.precision_recall_curve(y_true, y_prob)
    if T.size == 0:
        target_rate = float(np.clip(base_rate, lower_cap, upper_cap))
        thr = float(np.quantile(y_prob, 1.0 - target_rate))
        thr = float(np.clip(thr, eps, 1.0 - eps))
        n_pos = int((y_prob > thr).sum())
        if n_pos == 0: thr -= eps
        if n_pos == y_prob.size: thr += eps
        return float(thr)

    p, r = P[:-1], R[:-1]
    beta2 = beta * beta
    fbeta = (1.0 + beta2) * p * r / (beta2 * p + r + 1e-12)
    fbeta = np.nan_to_num(fbeta, nan=0.0, posinf=0.0, neginf=0.0)

    idx = None
    if min_precision is not None:
        ok = p >= float(min_precision)
        if ok.any():
            idx = int((np.where(ok, fbeta, -np.inf)).argmax())
    if idx is None:
        idx = int(fbeta.argmax())

    chosen_thr = float(T[idx])
    # rate guardrails with strict '>'
    pos_rate = float((y_prob > chosen_thr).mean())
    if pos_rate > upper_cap:
        chosen_thr = float(np.quantile(y_prob, 1.0 - upper_cap)) + eps
    elif pos_rate < lower_cap:
        chosen_thr = float(np.quantile(y_prob, 1.0 - lower_cap)) - eps

    # clamp & avoid edges / all or none
    chosen_thr = float(np.clip(chosen_thr, eps, 1.0 - eps))
    n_pos = int((y_prob > chosen_thr).sum())
    if n_pos == 0: chosen_thr -= eps
    if n_pos == y_prob.size: chosen_thr += eps

    if not np.isfinite(chosen_thr):
        chosen_thr = 0.5
    return float(chosen_thr)

def _jitter_thr(thr: float, eps: float = 1e-6) -> float:
    if thr <= eps: return eps
    if thr >= 1.0 - eps: return 1.0 - eps
    return float(thr)



# ──────────────────────────────────────────────────────────────
# optional: domain / tokens / caching utilities (keep names)
# ──────────────────────────────────────────────────────────────
def setup_domain_adaptation(model, train_loader):
    """
    Enable domain adapter if both 0/1 domains exist in a small probe of the loader.
    """
    seen = set()
    for i, batch in enumerate(train_loader):
        if hasattr(batch, "domain"):
            seen.update(batch.domain.detach().cpu().tolist())
        if i >= 3:  # small probe
            break
    enable = (0 in seen) and (1 in seen)
    if enable and not hasattr(model, "domain_adapter"):
        model.domain_adapter = DomainAdapter(model.hidden_dim).to(next(model.parameters()).device)
    return float(enable)


def _format_token_debug(chunks, max_chunks=2, max_ids=16):
    if not chunks:
        return "no_text"
    parts = []
    for i, ch in enumerate(chunks[:max_chunks]):
        head = ch[:max_ids]
        parts.append(f"ch{i}(len={len(ch)}): {head}" + (" …" if len(ch) > max_ids else ""))
    if len(chunks) > max_chunks:
        parts.append(f"+{len(chunks)-max_chunks} more chunks")
    return " | ".join(parts)

def _parse_extra_tokens_spec(spec: str) -> list[str]:
    if not spec:
        return []
    from pathlib import Path
    import re
    s = spec.strip()
    if s.startswith("@") or Path(s).exists():
        path = Path(s[1:]) if s.startswith("@") else Path(s)
        lines = path.read_text(encoding="utf-8").splitlines()
        candidates = [ln.strip() for ln in lines if ln.strip()]
    else:
        candidates = re.split(r"[,\s]+", s)
    out, seen = [], set()
    for t in candidates:
        if t and t not in seen:
            seen.add(t); out.append(t)
    return out

def _maybe_add_tokens_to_gcb(tok, model, tokens: list[str], init: str = "avg") -> int:
    if not tokens:
        return 0
    to_add = [t for t in tokens if t not in tok.get_vocab()]
    if not to_add:
        return 0
    added = tok.add_tokens(to_add, special_tokens=False)
    if added <= 0:
        return 0
    if hasattr(model, "text_tok"):
        model.text_tok = tok
    model.text_model.resize_token_embeddings(len(tok))
    if init in {"avg", "zero"}:
        emb = model.text_model.get_input_embeddings()
        W = emb.weight.data
        old_n = W.shape[0] - added
        new_slice = W[old_n:]
        if init == "avg":
            ref = W[:old_n].mean(dim=0, keepdim=True)
            new_slice.copy_(ref.expand_as(new_slice))
        else:
            new_slice.zero_()
    return added

@torch.no_grad()
def cache_embeddings(model, loader, device="cpu", out_path="train_cache.pt"):
    import gc
    orig_device = next(model.parameters()).device
    model.eval().to(device)
    X, Y = [], []
    step = 0
    with torch.inference_mode():
        for batch in tqdm(loader, desc="[Cache]"):
            b = batch.to(device, non_blocking=False)
            if hasattr(model, "graph_embed"):
                g = model.graph_embed(b)
            elif hasattr(model, "embed"):
                g = model.embed(b)
            else:
                raise RuntimeError("Model has neither graph_embed() nor embed().")
            X.append(g.detach().cpu().float())
            Y.append(getattr(b, "y").detach().cpu().long())
            step += 1
            if (step % 64) == 0:
                del g, b
                gc.collect()
    X = torch.cat(X, dim=0)
    Y = torch.cat(Y, dim=0)
    torch.save({"x": X, "y": Y}, out_path)
    print(f"[Cache] Saved embeddings {tuple(X.shape)} to {out_path}")
    model.to(orig_device).train()

def train_head_from_cache(cache_path, head: nn.Module, epochs=10, device="cuda"):
    blob = torch.load(cache_path, map_location="cpu")
    ds = torch.utils.data.TensorDataset(blob["x"], blob["y"])
    dl = torch.utils.data.DataLoader(ds, batch_size=512, shuffle=True, num_workers=2)
    head = head.to(device)
    opt = torch.optim.AdamW(head.parameters(), lr=3e-4, weight_decay=1e-2)
    ce  = nn.CrossEntropyLoss()
    for ep in range(1, epochs + 1):
        head.train()
        running = 0.0
        for xb, yb in dl:
            xb, yb = xb.to(device), yb.to(device)
            opt.zero_grad(set_to_none=True)
            logits = head(xb)
            loss = ce(logits, yb)
            loss.backward()
            opt.step()
            running += float(loss.item())
        print(f"[Head] epoch={ep} loss={running/len(dl):.4f}")

def freeze_all_but_classifier(model):
    for name, p in model.named_parameters():
        p.requires_grad = ("classifier" in name)
def clamp01_np(a: np.ndarray, eps: float = 1e-6) -> np.ndarray:
    return np.clip(a, eps, 1.0 - eps)

def decide_from_prob(y_prob: np.ndarray, thr: float) -> np.ndarray:
    return (y_prob > float(thr)).astype(np.int64)



@torch.inference_mode()
def collect_arrays(model, loader, device, temperature: float | None = None):
    model.eval()
    y_true, y_prob = [], []

    T = float(temperature) if (temperature is not None and np.isfinite(temperature) and temperature > 0.0) else 1.0
    T = max(0.1, min(10.0, T))

    for batch in loader:
        b = batch.to(device, non_blocking=True)
        logits = model(b).float()
        logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
        if T != 1.0:
            logits = logits / T
        p1 = _probs_from_logits_binary(logits)  # your stable helper: Δlogit→sigmoid
        y_prob.append(p1.detach().cpu())
        y_true.extend(b.y.detach().cpu().tolist())

    y_prob = (torch.cat(y_prob).numpy() if y_prob else np.array([], dtype=np.float32))
    y_true = np.asarray(y_true, dtype=np.int64)
    return y_true, y_prob




### Evaluation function (standard metrics) & plots ######
################───────────────────────────────────######

@torch.inference_mode()
def evaluate(model, loader, device, temperature: float | None = None) -> dict:
    """
    Stable eval for binary models:
      • fp32 forward (no AMP)
      • optional temperature on the logit gap
      • probabilities from Δlogit/T → sigmoid (no softmax)
      • strict '>' 0.5 for default predictions here (training loop may use a tuned thr)
    """
    import numpy as _np

    model.eval()
    y_true, prob_list = [], []

    # clamp T like elsewhere
    T = float(temperature) if (temperature is not None and _np.isfinite(temperature) and temperature > 0.0) else 1.0
    T = max(0.1, min(10.0, T))

    for batch in loader:
        b = batch.to(device, non_blocking=True)
        logits = model(b).float()
        logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
        p1 = _probs_from_logits_binary(logits, T=T)  # Δlogit → sigmoid with optional temperature
        prob_list.append(p1.detach().cpu())
        y_true.extend(b.y.detach().cpu().tolist())

        y_true = _np.asarray(y_true, dtype=_np.int64)

        if prob_list:
            y_prob = _np.asarray(torch.cat(prob_list).numpy(), dtype=_np.float32)
        else:
            y_prob = _np.empty((0,), dtype=_np.float32)

        y_prob = clamp01_np(y_prob)
        y_pred = decide_from_prob(y_prob, 0.5)



    acc  = skm.accuracy_score(y_true, y_pred) if y_true.size else 0.0
    prec = skm.precision_score(y_true, y_pred, zero_division=0) if y_true.size else 0.0
    rec  = skm.recall_score(y_true, y_pred, zero_division=0) if y_true.size else 0.0
    f1   = skm.f1_score(y_true, y_pred, zero_division=0) if y_true.size else 0.0

    try:
        auroc = skm.roc_auc_score(y_true, y_prob) if (_np.unique(y_true).size == 2) else None
    except Exception:
        auroc = None
    try:
        aupr  = skm.average_precision_score(y_true, y_prob) if (_np.unique(y_true).size == 2) else None
    except Exception:
        aupr = None

    return {
        "y_true": y_true,
        "y_pred": y_pred,
        "y_prob": y_prob,
        "threshold_used": 0.5,
        "accuracy": acc,
        "precision": prec,
        "recall": rec,
        "f1": f1,
        "auroc": auroc,
        "aupr": aupr,
    }







def plot_conf_mat(y_true, y_pred, out: Path):
    from sklearn.metrics import confusion_matrix
    import matplotlib.pyplot as plt
    import seaborn as sns
    cm = confusion_matrix(y_true, y_pred)
    plt.figure(figsize=(4, 3))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues",
                xticklabels=["Benign", "Vuln"], yticklabels=["Benign", "Vuln"])
    plt.ylabel("True label")
    plt.xlabel("Pred label")
    plt.tight_layout()
    plt.savefig(out)
    plt.close()

def plot_roc_pr(y_true, y_prob, roc_out: Path, pr_out: Path):
    from sklearn.metrics import roc_curve, auc, precision_recall_curve, average_precision_score
    import matplotlib.pyplot as plt

    fpr, tpr, _ = roc_curve(y_true, y_prob)
    plt.figure()
    plt.plot(fpr, tpr, label=f"AUC={auc(fpr, tpr):.2f}")
    plt.plot([0, 1], [0, 1], "--")
    plt.xlabel("FPR")
    plt.ylabel("TPR")
    plt.legend()
    plt.tight_layout()
    plt.savefig(roc_out)
    plt.close()

    prec, rec, _ = precision_recall_curve(y_true, y_prob)
    plt.figure()
    ap = average_precision_score(y_true, y_prob)
    plt.plot(rec, prec, label=f"AP={ap:.2f}")
    plt.xlabel("Recall")
    plt.ylabel("Precision")
    plt.legend()
    plt.tight_layout()
    plt.savefig(pr_out)
    plt.close()
# ─────────────────────────────────────────────────────────────────────


from pathlib import Path
import json
import tempfile
import shutil

def _atomic_write_json(obj, path: Path):
    path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile("w", delete=False, dir=str(path.parent), encoding="utf-8") as tmp:
        json.dump(obj, tmp)
        tmp.flush()
        os.fsync(tmp.fileno())
        tmp_name = tmp.name
    os.replace(tmp_name, str(path))  # atomic on POSIX

def _load_vocabs(vocabs_dir: Path) -> tuple[dict|None, dict|None]:
    node_file = vocabs_dir / "node_vocab.json"
    edge_file = vocabs_dir / "edge_vocab.json"
    if node_file.exists() and edge_file.exists():
        try:
            node_vocab = json.loads(node_file.read_text())
            edge_vocab = json.loads(edge_file.read_text())
            # sanity check: both must be dict-like
            if isinstance(node_vocab, dict) and isinstance(edge_vocab, dict) and len(node_vocab) and len(edge_vocab):
                print(f"[Vocab] Loaded node({len(node_vocab)})/edge({len(edge_vocab)}) from: {vocabs_dir}")
                return node_vocab, edge_vocab
        except Exception as e:
            print(f"[Vocab][Warn] Failed to load existing vocabs ({e}); will rebuild.")
    return None, None

def _build_vocabs_from_train(DSClass, train_manifest: str, train_json_root: str, T_for_vocab: int = 1):
    """
    Build vocabs once from TRAIN (small T is fine; T=1 recommended to keep it light).
    Requires Devign*Dataset to expose .node_type_vocab and .edge_type_vocab after init.
    """
    print("[Vocab] Not found → building from TRAIN … (this happens once)")
    tmp_ds = DSClass(
        manifest_csv   = train_manifest,
        json_root      = train_json_root,
        T              = T_for_vocab,
        node_type_vocab= None,
        edge_type_vocab= None,
        cache_root     = None,   # do NOT pollute persistent cache during vocab build
    )
    node_vocab = tmp_ds.node_type_vocab
    edge_vocab = tmp_ds.edge_type_vocab
    if not isinstance(node_vocab, dict) or not isinstance(edge_vocab, dict) or len(node_vocab) == 0 or len(edge_vocab) == 0:
        raise RuntimeError("[Vocab] Failed to build node/edge vocabs from TRAIN.")
    print(f"[Vocab] Built node({len(node_vocab)})/edge({len(edge_vocab)}) from TRAIN.")
    return node_vocab, edge_vocab

def ensure_vocabs(DSClass, vocabs_dir: Path, force_rebuild: bool,
                  train_manifest: str, train_json_root: str) -> tuple[dict, dict]:
    if not force_rebuild:
        node_vocab, edge_vocab = _load_vocabs(vocabs_dir)
        if node_vocab is not None and edge_vocab is not None:
            return node_vocab, edge_vocab

    # build (or force rebuild), then save atomically
    node_vocab, edge_vocab = _build_vocabs_from_train(
        DSClass, train_manifest, train_json_root, T_for_vocab=1
    )
    _atomic_write_json(node_vocab, vocabs_dir / "node_vocab.json")
    _atomic_write_json(edge_vocab, vocabs_dir / "edge_vocab.json")
    print(f"[Vocab] Saved node/edge vocabs to: {vocabs_dir}")
    return node_vocab, edge_vocab


# ─────────────────────────────────────────────────────────────────────
# GraphCodeBERT token cache (per split)
# ─────────────────────────────────────────────────────────────────────
def _sha256_file(p: Path, chunk: int = 1 << 20) -> str:
    h = hashlib.sha256()
    with open(p, "rb") as f:
        while (b := f.read(chunk)):
            h.update(b)
    return h.hexdigest()

def _text_cache_key(manifest_csv: str, tok, args) -> str:
    meta = {
        "csv_sha": _sha256_file(Path(manifest_csv)),
        "tok_name": getattr(tok, "name_or_path", "graphcodebert"),
        "vocab_size": len(tok),
        "pad_id": int(tok.pad_token_id) if tok.pad_token_id is not None else -1,
        "cfg": {
            "max_len": args.text_max_len,
            "chunk_len": args.text_chunk_len,
            "stride": args.text_chunk_stride,
            "max_chunks": args.text_max_chunks,
            "pool": args.text_pool,
        },
        "impl": "gcb-cache-v1",
    }
    raw = json.dumps(meta, sort_keys=True).encode()
    return hashlib.sha256(raw).hexdigest()[:16]

def _tokenize_code_to_chunks(text: str, tok, args) -> list[list[int]]:
    """
    Returns: list of chunks; each chunk is a list[int] token ids with [CLS]/[SEP] included.
    Attention mask is trivially 1..L (we build it at use time).
    """
    text = text or ""
    ids = tok.encode(text, add_special_tokens=True)
    CLS = int(tok.cls_token_id); SEP = int(tok.sep_token_id)
    max_len   = int(args.text_max_len)
    chunk_len = int(min(args.text_chunk_len, max_len))
    stride    = int(args.text_chunk_stride)
    max_chunks= int(args.text_max_chunks)

    # short path
    if len(ids) <= max_len:
        return [ids[:max_len]]

    core = ids[1:-1] if len(ids) >= 2 else ids
    inner = max(4, chunk_len - 2)
    chunks = []
    for s in range(0, len(core), stride):
        if len(chunks) >= max_chunks:
            break
        seg = core[s:s+inner]
        chunks.append([CLS] + seg + [SEP])
    return chunks

def build_or_load_text_cache(ds, split_name: str, tok, args, model_dir: Path):
    """
    Builds (or loads) a per-split cache aligned with ds.__getitem__(i).cache_idx.
    Each entry: list[list[int]]  (variable #chunks per sample).
    Disk layout:
        models/
          tokenizer_artifacts/...
          text_cache/{split}_{key}.pkl
    """
    parent_model_dir = model_dir                # keep everything under run_dir/models
    arti_dir = parent_model_dir / "tokenizer_artifacts"
    arti_dir.mkdir(parents=True, exist_ok=True)
    # persist tokenizer files & vocab for reproducibility
    tok.save_pretrained(arti_dir)
    with open(arti_dir / "vocab.pkl", "wb") as f:
        pickle.dump(tok.get_vocab(), f)

    cache_dir = parent_model_dir / "text_cache"
    cache_dir.mkdir(parents=True, exist_ok=True)
    key = _text_cache_key(ds.row_df.attrs.get("source_csv", ds.row_df), tok, args) \
          if isinstance(ds.row_df, pd.DataFrame) else _text_cache_key("unknown", tok, args)
    # safer: always key by actual manifest path you passed in
    # (we have it in train(), we’ll compute key there and pass)
    # so here just use a filename handed from train()
    # (we’ll override 'key' in train() call)

    # we will pass the true key from train(); placeholder to avoid confusion
    return None  # we replace this with the real builder below

def make_graph_collate_with_text_cache(cache_list):
    from torch_geometric.loader.dataloader import Collater
    def _collate(items):
        if isinstance(items[0], HeteroData):
            coll = Collater(follow_batch=[])
            batch = coll(items)
        else:
            batch = Batch.from_data_list(items)
        batch.code_text_list = [getattr(it, "code_text", None) for it in items]

        cached = []
        for it in items:
            if hasattr(it, "cache_idx"):
                idx = int(it.cache_idx.item())
                cached.append(cache_list[idx] if cache_list is not None else None)
            else:
                cached.append(None)

        # <<< only change: wrap in proxy >>>
        batch.text_tok_cached = _TokenChunksProxy(cached)
        return batch
    return _collate
import sys, contextlib

class _NoHuge:
    def __init__(self, stream): self.stream = stream
    def write(self, s):
        # drop ultra-long lines (accidental tensor/list dumps)
        if len(s) > 50000:  # ~50 KB
            return
        self.stream.write(s)
    def flush(self): self.stream.flush()

# ─────────────────────────────────────────────────────────────────────────────
# contrastive training (robust stdout + first-batch shape probe, no huge prints)
# ─────────────────────────────────────────────────────────────────────────────
import os
os.environ["TOKENIZERS_PARALLELISM"] = "false"

# Add this at the very beginning of your script, before any other imports

def train_contrastive(
    model,
    loader,
    device,                      # kept for symmetry; contrastive runs on CPU
    epochs: int = 30,
    tau: float = 0.5,
    lr: float = 3e-4,
    weight_decay: float = 5e-4,
    patience: int = 5,
    grad_clip: float = 1.0,
) -> bool:
    """
    CPU-only FAST contrastive pretrain that:
      • Encodes per-type sequences with model.temporal_encode
      • Pools safely to [B, H*] (H* = projector's input dim) with a COMMON B
      • Uses lazy per-type Linear adapters to map varying dims → H*
      • Avoids HGTConv/HGT layers entirely
    Returns True on success so the caller proceeds to supervised training.
    """
    import traceback
    from collections import OrderedDict
    import torch
    import torch.nn as nn
    import torch.nn.functional as F
    from torch_geometric.nn import global_add_pool
    from tqdm import tqdm

    # Prefer your numerically-stable InfoNCE if it exists; otherwise fallback.
    _has_stable_infonce = "info_nce_loss" in globals()

    # ---------------- helpers ----------------
    def _force_bn_eval(m: nn.Module):
        for mod in m.modules():
            if isinstance(mod, nn.BatchNorm1d):
                mod.eval()

    def _present_types(dcpu) -> list[str]:
        nts = []
        for nt in getattr(model, "node_types", []):
            if nt in getattr(dcpu, "node_types", []):
                st = dcpu[nt]
                if hasattr(st, "x_seq") and st.x_seq is not None and st.x_seq.numel() > 0:
                    nts.append(nt)
        return nts

    def _common_B(dcpu) -> int:
        B = 1
        for nt in getattr(model, "node_types", []):
            if nt in getattr(dcpu, "node_types", []):
                bt = getattr(dcpu[nt], "batch", None)
                if bt is not None and bt.numel() > 0:
                    B = max(B, int(bt.max().item()) + 1)
        return B

    def _infer_proj_in_features(m: nn.Module, fallback: int = 256) -> int:
        proj = getattr(m, "projector", None)
        if isinstance(proj, nn.Sequential):
            for mod in proj.modules():
                if isinstance(mod, nn.Linear):
                    return int(mod.in_features)
        if isinstance(proj, nn.Linear):
            return int(proj.in_features)
        return int(getattr(m, "hidden_dim", fallback))

    @torch.no_grad()
    def _sanitize_cpu(dcpu):
        try:
            num_nt = int(getattr(model, "node_emb").num_embeddings)
        except Exception:
            num_nt = None
        try:
            _sanitize_hetero_batch_(dcpu, num_node_types=num_nt, device=torch.device("cpu"))
        except Exception:
            pass

    # Lazy per-type adapters: H_in → H_tgt
    if not hasattr(model, "_adapters"):
        model._adapters = nn.ModuleDict()
    model._adapters_dirty = False

    def _ensure_adapter(nt: str, H_in: int, H_tgt: int) -> nn.Module:
        key = f"{nt}:{H_in}->{H_tgt}"
        if key not in model._adapters:
            model._adapters[key] = nn.Sequential(
                nn.LayerNorm(H_in),
                nn.Linear(H_in, H_tgt, bias=False),
            )
            model._adapters_dirty = True
        return model._adapters[key]

    def _pool_per_type_SAFE(h_dict: dict[str, torch.Tensor], data_batch, H_tgt: int) -> torch.Tensor:
        """
        h_dict: {node_type: [N_t, H_in]} → [B_common, H_tgt]
        Pools each type with global_add_pool(..., size=B_common), then sums across types.
        """
        B_common = _common_B(data_batch)
        outs = []
        for nt, h in h_dict.items():
            if h is None or h.numel() == 0:
                outs.append(torch.zeros(B_common, H_tgt))
                continue
            if h.dim() != 2:
                h = h.view(h.size(0), -1)
            H_in = int(h.size(1))
            if H_in != H_tgt:
                h = _ensure_adapter(nt, H_in, H_tgt)(h)
            bt = getattr(data_batch[nt], "batch", None)
            if bt is None or bt.numel() == 0:
                bt = torch.zeros(h.size(0), dtype=torch.long)
            g_nt = global_add_pool(h, bt, size=B_common)  # [B_common, H_tgt]
            outs.append(g_nt)
        return torch.stack(outs, dim=0).sum(dim=0)  # [B_common, H_tgt]

    # Stable InfoNCE fallback (matmul version)
    def _info_nce_simple(z1: torch.Tensor, z2: torch.Tensor, temperature: float) -> torch.Tensor:
        z1 = F.normalize(z1.float(), dim=1, eps=1e-8)
        z2 = F.normalize(z2.float(), dim=1, eps=1e-8)
        B  = z1.size(0)
        z  = torch.cat([z1, z2], dim=0)                        # [2B, D]
        sim = (z @ z.t()) / max(float(temperature), 1e-8)      # [2B, 2B]
        eye = torch.eye(2*B, device=sim.device, dtype=torch.bool)
        sim.masked_fill_(eye, -1e4)
        labels = torch.arange(B, device=z.device)
        labels = torch.cat([labels + B, labels], dim=0)
        return F.cross_entropy(sim, labels)

    # Fast embed on CPU (temporal → pool → projector)
    dbg_prints = 0
    def _fast_embed_cpu(m, dcpu, H_tgt: int) -> torch.Tensor | None:
        nonlocal dbg_prints
        try:
            _sanitize_cpu(dcpu)
            x_seq_dict = OrderedDict()
            for nt in _present_types(dcpu):
                xseq = dcpu[nt].x_seq
                if xseq.dtype != torch.long:
                    xseq = xseq.long()
                if xseq.device.type != "cpu":
                    xseq = xseq.to("cpu", non_blocking=True)
                x_seq_dict[nt] = xseq

            if not x_seq_dict:
                return None

            _force_bn_eval(m)
            h_dict = m.temporal_encode(x_seq_dict)         # {nt: [N_t, H_in]}
            g = _pool_per_type_SAFE(h_dict, dcpu, H_TGT)   # [B, H_TGT]
            if g is None or g.numel() == 0:
                return None

            z = m.projector(g)                             # [B, D]
            if not torch.isfinite(z).all():
                return None
            return F.normalize(z.float(), dim=1, eps=1e-8)

        except Exception as e:
            if dbg_prints < 3:
                print("[Contrastive/CPU][embed_fail]", repr(e))
                traceback.print_exc(limit=1)
                try:
                    print("  present_types:", _present_types(dcpu))
                    print("  common_B:", _common_B(dcpu))
                except Exception:
                    pass
                dbg_prints += 1
            return None

    # ---------------- stage setup ----------------
    try:
        orig_device = next(model.parameters()).device
    except StopIteration:
        orig_device = torch.device("cpu")
    was_training = model.training

    # Move to CPU for contrastive stage
    if orig_device.type == "cuda":
        print("[Contrastive/CPU] Moving model to CPU …")
    model_cpu = model.to("cpu")
    model_cpu.train()
    _force_bn_eval(model_cpu)

    # Projector input (= pooling target dim)
    H_TGT = _infer_proj_in_features(model_cpu, fallback=int(getattr(model_cpu, "hidden_dim", 256)))
    print(f"[Contrastive/CPU] target pooling dim H* = {H_TGT}")

    # Local optimizer (recreated if adapters are added lazily)
    def _make_opt():
        return torch.optim.AdamW(model_cpu.parameters(), lr=float(lr), weight_decay=float(weight_decay))
    opt = _make_opt()

    best = float("inf"); bad = 0
    any_steps = False

    try:
        for epoch in range(1, epochs + 1):
            total, steps = 0.0, 0
            n_smallB = 0
            n_nonfinite = 0
            n_embed_fail = 0

            pbar = tqdm(loader, desc=f"Contrastive {epoch}/{epochs} (CPU/FAST)", ncols=100, leave=False)
            for batch in pbar:
                if not (isinstance(batch, dict) and "orig" in batch and "adv" in batch):
                    n_embed_fail += 1
                    pbar.set_postfix(avg=f"{(total/max(1,steps)):.4f}", ef=n_embed_fail, nf=n_nonfinite, smallB=n_smallB)
                    continue

                orig_cpu = batch["orig"].to("cpu")
                adv_cpu  = batch["adv"].to("cpu")

                z1 = _fast_embed_cpu(model_cpu, orig_cpu, H_TGT)
                z2 = _fast_embed_cpu(model_cpu, adv_cpu,  H_TGT)

                # If new adapters were added lazily, rebuild optimizer once
                if getattr(model_cpu, "_adapters_dirty", False):
                    opt = _make_opt()
                    model_cpu._adapters_dirty = False

                if z1 is None or z2 is None:
                    n_embed_fail += 1
                    pbar.set_postfix(avg=f"{(total/max(1,steps)):.4f}", ef=n_embed_fail, nf=n_nonfinite, smallB=n_smallB)
                    continue

                B = min(z1.size(0), z2.size(0))
                if B < 2:
                    n_smallB += 1
                    pbar.set_postfix(avg=f"{(total/max(1,steps)):.4f}", ef=n_embed_fail, nf=n_nonfinite, smallB=n_smallB)
                    continue
                if z1.size(0) != z2.size(0):
                    z1, z2 = z1[:B], z2[:B]

                # Stable InfoNCE
                if _has_stable_infonce:
                    loss = info_nce_loss(z1, z2, temperature=float(tau))  # uses your numerics-safe impl
                else:
                    loss = _info_nce_simple(z1, z2, temperature=float(tau))

                if not torch.isfinite(loss):
                    n_nonfinite += 1
                    pbar.set_postfix(avg=f"{(total/max(1,steps)):.4f}", ef=n_embed_fail, nf=n_nonfinite, smallB=n_smallB)
                    continue

                opt.zero_grad(set_to_none=True)
                loss.backward()
                torch.nn.utils.clip_grad_norm_(model_cpu.parameters(), float(grad_clip))
                opt.step()

                total += float(loss.detach().item())
                steps += 1
                any_steps = True
                pbar.set_postfix(avg=f"{(total/steps):.4f}", ef=n_embed_fail, nf=n_nonfinite, smallB=n_smallB)

            avg = total / steps if steps > 0 else float("inf")
            print(f"[Contrastive/CPU] Epoch {epoch} | avg_loss={avg:.4f} "
                  f"| steps={steps} | skipped(smallB={n_smallB}, nonfinite={n_nonfinite}, embed_fail={n_embed_fail})")

            if avg + 1e-6 < best:
                best, bad = avg, 0
            else:
                bad += 1
                if bad >= int(patience):
                    print(f"[Contrastive/CPU] EarlyStop @ epoch={epoch} best_avg_loss={best:.4f}")
                    break

    finally:
        # Restore original device and training mode
        if orig_device.type == "cuda":
            print("[Contrastive/CPU] Moving model back to CUDA for supervised training …")
        model_cpu.to(orig_device)
        model.train(was_training)

    return bool(any_steps)












# ============================================================================ 
# ─────────────────────────────────────────────────────────────────────────────
# Training loop
# ─────────────────────────────────────────────────────────────────────────────


def train(args):
    # ── Boilerplate ────────────────────────────────────────────────────────────
    import os
    import json as _json
    import hashlib as _hashlib
    import pathlib
    _P = pathlib.Path

    torch.cuda.empty_cache()
    bf16 = torch.cuda.is_bf16_supported()
    set_seed(args.seed)
    torch.backends.cudnn.deterministic = False
    torch.use_deterministic_algorithms(False)
    torch.backends.cudnn.enabled = True
    torch.backends.cudnn.benchmark = True
    torch.backends.cudnn.allow_tf32 = True
    torch.backends.cuda.matmul.allow_tf32 = True

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    try:
        if device.type == "cuda":
            print(f"[Device] CUDA available → {torch.cuda.get_device_name(0)}")
        else:
            print("[Device] Using CPU")
    except Exception:
        pass
    try:
        torch.set_float32_matmul_precision("high")
    except Exception:
        pass
    accum_steps = max(1, int(getattr(args, "accum_steps", 1)))

    # ── Run directories (short, stable names) ──────────────────────────────────
    def _family_name(a) -> str:
        if a.model.lower() == "mptcn_tts":
            return f"{a.model.upper()}_{a.spatial.upper()}"
        return a.model.upper()

    def _combo_name(a) -> str:
        key = {
            "temporal": a.temporal.lower(),
            "T": a.T, "Lt": a.Lt, "Ls": a.Ls, "Kt": a.Kt,
            "Ks": getattr(a, "Ks", None),
            "hd": a.hidden_dim, "ed": a.emb_dim,
            "dropout": a.dropout, "lr": a.lr,
            "focal": a.focal_gamma, "dom": a.lambda_dom,
        }
        h = _hashlib.sha1(_json.dumps(key, sort_keys=True).encode("utf-8")).hexdigest()[:3]
        return f"{a.temporal.upper()}_{h}"

    root      = _P("MPTCN_TTS_devign")
    family    = _family_name(args)           # e.g., "MPTCN_TTS_HGT" or "PNA"
    run_slug  = _combo_name(args)            # e.g., "TCN_a9f"

    run_dir     = root / family / run_slug
    model_dir   = run_dir / "models"
    results_dir = run_dir / "results"
    model_dir.mkdir(parents=True, exist_ok=True)
    results_dir.mkdir(parents=True, exist_ok=True)

    print(f"[Dirs] parent={root.resolve()}")
    print(f"[Dirs] run   ={family}/{run_slug}")

    # ── Central artifacts (persist across runs) ────────────────────────────────
    artifacts_dir = root / "artifacts"
    vocabs_dir    = artifacts_dir / "vocabs"
    pyg_cache_dir = artifacts_dir / "pyg_cache"
    vocabs_dir.mkdir(parents=True, exist_ok=True)
    pyg_cache_dir.mkdir(parents=True, exist_ok=True)

    # ── Load (or later save) node/edge vocabs once ────────────────────────────
    node_vocab_file = vocabs_dir / "node_vocab.json"
    edge_vocab_file = vocabs_dir / "edge_vocab.json"
    cached_node_vocab = None
    cached_edge_vocab = None
    if node_vocab_file.exists() and edge_vocab_file.exists():
        try:
            cached_node_vocab = _json.loads(node_vocab_file.read_text())
            cached_edge_vocab = _json.loads(edge_vocab_file.read_text())
            print(f"[Vocab] Loaded node/edge vocabs "
                  f"({len(cached_node_vocab)} nodes, {len(cached_edge_vocab)} edges) from {vocabs_dir}")
        except Exception as e:
            print(f"[Vocab] Failed to read saved vocabs → will rebuild once. Reason: {e}")

    # ── Data locations (with CLI overrides) ────────────────────────────────────
    def _resolve(split, default_manifest, default_root, override_manifest, override_root):
        man  = _P(override_manifest) if override_manifest else default_manifest
        root = _P(override_root)     if override_root    else default_root
        print(f"[Paths][{split}] manifest={man} | json_root={root}")
        return {"manifest_csv": str(man), "json_root": str(root)}

    paths = {
        "train": _resolve("train", MANIFESTS["train"], JSON_ROOTS["train"],
                          getattr(args, "train_manifest", None), getattr(args, "train_json_root", None)),
        "val":   _resolve("val",   MANIFESTS["val"],   JSON_ROOTS["val"],
                          getattr(args, "val_manifest", None),   getattr(args, "val_json_root", None)),
        "test":  _resolve("test",  MANIFESTS["test"],  JSON_ROOTS["test"],
                          getattr(args, "test_manifest", None),  getattr(args, "test_json_root", None)),
    }

    # Optional: environment fallback for augmented test manifest (no NameError risk)
    if getattr(args, "use_aug_test", False) and (args.test_manifest is None):
        aug_env = os.environ.get("DEVIGN_AUG_TEST_MANIFEST", "").strip()
        if aug_env:
            paths["test"]["manifest_csv"] = aug_env
            print(f"[Paths][test] --use-aug-test → using augmented test manifest (env): {aug_env}")
        else:
            print("[Warn] --use-aug-test set but no augmented test manifest provided "
                  "(--test-manifest or DEVIGN_AUG_TEST_MANIFEST). Using default test manifest.")

    # Prefer T_test=6 automatically when using an augmented/windowed test and user didn't set it
    T_test_local = int(getattr(args, "T_test", 1))
    if getattr(args, "use_aug_test", False) and (int(getattr(args, "T_test", 0)) <= 1):
        T_test_local = 6

    # Friendly note when T_test mismatches T and user didn’t supply a specific test manifest
    if (T_test_local != int(args.T)) and (getattr(args, "test_manifest", None) is None) and (not getattr(args, "use_aug_test", False)):
        print("[Warn] T_test != T but --test-manifest not provided (and --use-aug-test not set). "
              "If your manifests are pre-windowed per T, pass a matching file via --test-manifest.")

    # ── Build datasets (unique caches per manifest) ────────────────────────────
    def _short_sha(p: str, n: int = 8) -> str:
        try:
            return _sha256_file(_P(p))[:n]
        except Exception:
            return "nohash"

    print("Loading datasets …")

    DSClass = DevignHeteroDataset if (args.model == "mptcn_tts" and args.spatial == "hgt") else DevignDataset

    tr_key = _short_sha(paths["train"]["manifest_csv"])
    va_key = _short_sha(paths["val"]["manifest_csv"])
    te_key = _short_sha(paths["test"]["manifest_csv"])

    train_cache_root = pyg_cache_dir / f"train_{tr_key}"
    val_cache_root   = pyg_cache_dir / f"val_{va_key}"
    test_cache_root  = pyg_cache_dir / f"test_{te_key}"
    train_cache_root.mkdir(parents=True, exist_ok=True)
    val_cache_root.mkdir(parents=True, exist_ok=True)
    test_cache_root.mkdir(parents=True, exist_ok=True)

    # Train dataset (uses cached vocabs if available; otherwise dataset will build them once)
    train_ds = DSClass(
        manifest_csv    = paths["train"]["manifest_csv"],
        json_root       = paths["train"]["json_root"],
        T               = args.T,
        node_type_vocab = cached_node_vocab,
        edge_type_vocab = cached_edge_vocab,
        cache_root      = train_cache_root,
    )
    # If we didn’t have vocabs, save the ones the train dataset just built so we NEVER rebuild again
    if (cached_node_vocab is None) or (cached_edge_vocab is None):
        try:
            node_vocab_file.write_text(_json.dumps(train_ds.node_type_vocab))
            edge_vocab_file.write_text(_json.dumps(train_ds.edge_type_vocab))
            print(f"[Vocab] Saved node/edge vocabs to {vocabs_dir} "
                  f"({len(train_ds.node_type_vocab)} nodes, {len(train_ds.edge_type_vocab)} edges)")
        except Exception as e:
            print(f"[Vocab] Failed to save vocabs (non-fatal): {e}")

    # Val/Test must re-use train’s vocab (no rebuilds, no drift)
    val_ds = DSClass(
        manifest_csv    = paths["val"]["manifest_csv"],
        json_root       = paths["val"]["json_root"],
        T               = args.T,
        node_type_vocab = train_ds.node_type_vocab,
        edge_type_vocab = train_ds.edge_type_vocab,
        cache_root      = val_cache_root,
    )
    test_ds = DSClass(
        manifest_csv    = paths["test"]["manifest_csv"],
        json_root       = paths["test"]["json_root"],
        T               = T_test_local,
        node_type_vocab = train_ds.node_type_vocab,
        edge_type_vocab = train_ds.edge_type_vocab,
        cache_root      = test_cache_root,
    )

    print(f"[Chk] T_train={train_ds.T} | T_val={val_ds.T} | T_test={test_ds.T}")

    # (Optional) T=1 coverage scan only for HGT + contrastive pretraining
    aug_ds = None
    if args.spatial == "hgt" and getattr(args, "do_contrastive", False):
        AugDS = DevignHeteroDataset
        aug_ds = AugDS(
            manifest_csv    = paths["train"]["manifest_csv"],
            json_root       = paths["train"]["json_root"],
            T               = int(getattr(args, "pre_T", 6)),  # default 6 unless changed
            node_type_vocab = train_ds.node_type_vocab,
            edge_type_vocab = train_ds.edge_type_vocab,
            cache_root      = None,
        )

    # ── Sanity: real vs synthetic counts ───────────────────────────────────────
    for ds, name in [(train_ds, "train"), (val_ds, "val"), (test_ds, "test")]:
        df = ds.row_df
        if "json_path" in df.columns:
            real = df["json_path"].isna().sum()
            synthetic = df.shape[0] - real
        else:
            real, synthetic = df.shape[0], 0
        print(f"[Chk] {name:5s} → real={real:,}  synthetic={synthetic:,}")

    if len(train_ds) == 0:
        raise RuntimeError(f"[Loader] Train set is empty! Check --T (={args.T}) and paths.")


    # --- model -----------------------------------------------------------------
    if args.model == "gin":
        model = GINBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.layers,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_GIN.pt"

    elif args.model == "gat":
        model = GATBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            heads=args.heads,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_GAT.pt"

    elif args.model == "gcn":
        model = GCNBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_GCN.pt"

    elif args.model == "sage":
        model = SAGEBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_SAGE.pt"

    elif args.model == "mpnn":
        model = MPNNBaseline(
            num_node_types=train_ds.num_node_types,
            num_edge_types=train_ds.num_edge_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            edge_emb_dim=args.edge_emb_dim,
            num_layers=args.layers,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_MPNN.pt"

    elif args.model == "rgcn":
        model = RGCNBaseline(
            num_node_types=train_ds.num_node_types,
            num_relations=train_ds.num_edge_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.layers,
            num_bases=args.bases,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_RGCN.pt"

    elif args.model == "han":
        model = HANBaseline(
            num_node_types=train_ds.num_node_types,
            num_relations=train_ds.num_edge_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.layers,
            heads=args.heads,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_HAN.pt"

    elif args.model == "dgcnn":
        model = DGCNNBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.layers,
            k=args.knn,
            sort_pool_k=args.sort_pool_k,
            dropout=args.dropout,
        ).to(device)
        ckpt_name = "best_DGCNN.pt"

    elif args.model == "pna":
        # Safety: PNA expects homogeneous graphs (torch_geometric.data.Data), not HeteroData.
        if isinstance(train_ds, DevignHeteroDataset):
            raise RuntimeError("PNA baseline expects homogeneous Data. Run with --spatial cheb/gcn/gat (not hgt).")
        deg_hist = build_pna_degree_hist(train_ds)  # make sure this helper is defined
        model = PNABaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            L_T=args.Lt,
            L_S=args.Ls,
            Kt=args.Kt,
            dropout=args.dropout,
            row_norm=args.row_norm,
            num_classes=2,
            deg=deg_hist,
        ).to(device)
        ckpt_name = "best_PNA.pt"

    elif args.model == "deepergcn":
        # DeeperGCN expects homogeneous Data graphs
        if isinstance(train_ds, DevignHeteroDataset):
            raise RuntimeError("DeeperGCN baseline expects homogeneous Data. Run with --spatial cheb/gcn/gat (not hgt).")
        model = DeeperGCNBaseline(
            num_node_types=train_ds.num_node_types,
            emb_dim=args.emb_dim,
            hidden_dim=args.hidden_dim,
            L_T=args.Lt,
            L_S=max(6, args.Ls),   # deeper spatial stack (default ≥ 6)
            Kt=args.Kt,
            dropout=args.dropout,
            row_norm=args.row_norm,
            num_classes=2,
        ).to(device)
        ckpt_name = "best_DeeperGCN.pt"


    elif args.model == "mptcn_tts":
        if args.spatial == "hgt":
            # Build metadata from TRAIN cache (observed coverage)
            meta_path = model_dir / "hgt_metadata.json"
            if meta_path.exists():
                meta = json.load(open(meta_path))
                node_types = meta["node_types"]
                edge_types = [tuple(t) for t in meta["edge_types"]]
                print(f"[HGT] metadata loaded: node={len(node_types)}, edge={len(edge_types)}")
            else:
                print("[HGT] Building metadata from cached graphs (observed, coverage-safe)…")
                from collections import Counter

                inv_node = {v: k for k, v in train_ds.node_type_vocab.items()}
                inv_edge = {v: k for k, v in train_ds.edge_type_vocab.items()}

                def _scan(ds):
                    node_set, pair_set, trip_ctr = set(), set(), Counter()
                    for data in tqdm(ds._cache, desc="[HGT] scan", ncols=100):
                        # node labels of the last snapshot
                        x_last = data.x[:, -1] if data.x.dim() == 2 else data.x.squeeze(-1)
                        node_labels = [inv_node[int(t)] for t in x_last.tolist()]
                        node_set.update(node_labels)

                        s = data.edge_index[0].tolist()
                        d = data.edge_index[1].tolist()
                        et = data.edge_type.tolist() if hasattr(data, "edge_type") else []

                        for si, di, eid in zip(s, d, et):
                            st = node_labels[si]
                            dt = node_labels[di]
                            rel = inv_edge.get(int(eid), "UNK")
                            pair_set.add((st, dt))
                            trip_ctr[(st, rel, dt)] += 1
                    return node_set, pair_set, trip_ctr

                # Scan T=6 TRAIN (supervised)
                nodeA, pairA, ctrA = _scan(train_ds)
                node_types_set = set(nodeA)
                pair_set = set(pairA)
                trip_ctr = Counter(ctrA)

                # Optionally include T=1 contrastive TRAIN for coverage
                if aug_ds is not None:
                    nodeB, pairB, ctrB = _scan(aug_ds)
                    node_types_set.update(nodeB)
                    pair_set.update(pairB)
                    trip_ctr.update(ctrB)

                node_types = sorted(node_types_set)

                # Keep most frequent triplets up to a cap
                MAX_HGT_REL = int(getattr(args, "hgt_max_rel", 800))
                top_trips = [t for t, _ in trip_ctr.most_common(MAX_HGT_REL)]

                # Always add fallback ('UNK') for each observed (src,dst) pair
                trip_set = set(top_trips)
                for st, dt in pair_set:
                    if (st, "UNK", dt) not in trip_set:
                        trip_set.add((st, "UNK", dt))

                edge_types = sorted(trip_set)

                json.dump({"node_types": node_types, "edge_types": [list(t) for t in edge_types]}, open(meta_path, "w"))
                print(f"[HGT] metadata saved (node={len(node_types)}, edge={len(edge_types)})")

            model = HGTMPTCNTTS(
                node_types=node_types,
                edge_types=edge_types,
                num_node_types=train_ds.num_node_types,
                emb_dim=args.emb_dim,
                hidden_dim=args.hidden_dim,
                L_T=args.Lt,
                L_S=args.Ls,
                Kt=args.Kt,
                dropout=args.dropout,
                temporal=args.temporal,
                num_classes=2,
                hgt_heads=int(getattr(args, "hgt_heads", 1)),
            ).to(device)

            print(f"[HGT] node_types={len(node_types)}, edge_types={len(edge_types)}")
            total = sum(p.numel() for p in model.parameters())
            print(f"[HGT] params≈{total/1e6:.2f}M")

        else:
            model = EnhancedMPTCNTTS(
                domain_adapt=True,
                dilations=(1, 2, 4),
                num_node_types=train_ds.num_node_types,
                emb_dim=args.emb_dim,
                hidden_dim=args.hidden_dim,
                L_T=args.Lt,
                L_S=args.Ls,
                Kt=args.Kt,
                Ks=args.Ks,
                row_norm=args.row_norm,
                dropout=args.dropout,
                spatial_type=args.spatial,
                num_relations=getattr(train_ds, "num_edge_types", 1),
                temporal=args.temporal,
            ).to(device)

        ckpt_name = "best_MPTCN_TTS.pt"

    else:
        raise ValueError(f"Unknown --model '{args.model}'")



    optimizer = torch.optim.AdamW(model.parameters(), lr=(args.lr or 3e-4), weight_decay=5e-4)



    # --- optional contrastive pre-training (T=1) -------------------------------
    # --- optional contrastive pre-training (T = args.pre_T) -----------------------
    if getattr(args, "do_contrastive", False):
        pre_T = int(getattr(args, "pre_T", 6))
        if args.spatial == "hgt":
            AugDS = DevignHeteroDataset
        else:
            AugDS = DevignDataset

        aug_ds = AugDS(
            manifest_csv   = paths["train"]["manifest_csv"],
            json_root      = paths["train"]["json_root"],
            T              = pre_T,    # <── use pretraining temporal length
            node_type_vocab= train_ds.node_type_vocab,
            edge_type_vocab= train_ds.edge_type_vocab,
            cache_root     = None,
        )

        contrastive_ds = DevignContrastiveDataset(aug_ds)
        if len(contrastive_ds) == 0:
            print("Warning: no function has ≥2 snapshots; skipping contrastive pre-training.")
        else:
            contrastive_loader = DataLoader(
                contrastive_ds,
                batch_size=args.batch_size,
                shuffle=True,
                num_workers=min(8, os.cpu_count() or 8),
                pin_memory=False,
                persistent_workers=False,
                prefetch_factor=2,
                collate_fn=contrastive_collate_any,
                drop_last=True,
            )
            print(f"[Contrastive] (T={pre_T}) {len(contrastive_ds)} pairs → {len(contrastive_loader)} batches/epoch")
            ok = train_contrastive(model, contrastive_loader, device,
                                epochs=args.pre_epochs, tau=args.tau)
            if not ok:
                print("[Fatal] Contrastive stage aborted due to repeated failures.")
                import sys; sys.exit(111)
            print("→ Contrastive pre-training complete.\n")



    # --- class weights ---------------------------------------------------------
    if args.T > 1:
        label_series = pd.Series([train_ds.row_df.loc[s + args.T - 1, "label"] for s in train_ds.window_starts])
    else:
        label_series = train_ds.row_df["label"]
    counts = label_series.value_counts().reindex([0, 1], fill_value=0)
    print("[Chk] label distribution train :", counts.to_dict())

    n0, n1 = int(counts.loc[0]), int(counts.loc[1])


    # --- class weights ---------------------------------------------------------
    freq = torch.tensor([max(n0, 1), max(n1, 1)], dtype=torch.float)
    inv  = 1.0 / freq
    class_weights_cpu = inv / inv.mean()
    print(f"[Debug] CE weights (inv-freq norm) → {class_weights_cpu.tolist()}")

    # --- IMPORTANT: set classifier bias to dataset prior (breaks 0.5/0.5 symmetry)
    # --- IMPORTANT: set classifier bias to dataset prior (breaks 0.5/0.5 symmetry)
    try:
        p1 = float(n1) / float(max(1, (n0 + n1)))
        p1 = min(max(p1, 1e-6), 1.0 - 1e-6)
        prior_logit = float(np.log(p1 / (1.0 - p1)))

        def _set_bias_and_break_ties(lin: nn.Linear):
            if lin is None or lin.out_features != 2 or lin.bias is None:
                return
            with torch.no_grad():
                # center then set class priors as ±Δ/2 so (b1 - b0) = prior_logit
                lin.bias.zero_()
                lin.bias[1] =  + prior_logit / 2.0
                lin.bias[0] =  - prior_logit / 2.0

                # if the two class rows start (nearly) identical, add tiny jitter to avoid Δlogit=0 collapse
                W = lin.weight.data
                if torch.allclose(W[0], W[1], atol=1e-8):
                    W[1].add_(1e-3 * torch.randn_like(W[1]))

        if hasattr(model, "classifier"):
            last_linear = None
            if isinstance(model.classifier, nn.Sequential):
                for m in model.classifier.modules():
                    if isinstance(m, nn.Linear) and m.out_features == 2:
                        last_linear = m
                _set_bias_and_break_ties(last_linear)
            elif isinstance(model.classifier, nn.Linear) and model.classifier.out_features == 2:
                _set_bias_and_break_ties(model.classifier)

        # optional: quick sanity log if we found a 2-way head
        if 'last_linear' in locals() and isinstance(last_linear, nn.Linear):
            with torch.no_grad():
                diff = (last_linear.weight[1] - last_linear.weight[0]).norm().item()
            print(f"[Init] classifier prior p1={p1:.4f} → Δbias≈{prior_logit:.4f} | ||W1-W0||={diff:.3e}")
        else:
            print(f"[Init] classifier prior p1={p1:.4f} → Δbias≈{prior_logit:.4f}")
    except Exception as e:
        print("[Init] classifier prior bias set failed:", repr(e))



    # --- loaders ---------------------------------------------------------------
    is_cuda = (device.type == "cuda")
    # Good defaults for ETL-heavy graphs:
    num_workers = max(2, (os.cpu_count() or 8) // 2)
    if is_cuda:
        pin = True
        persistent = True
        pf = 8
    else:
        pin = False
        persistent = False
        pf = 4

    # --- loaders ---------------------------------------------------------------
    # Multiprocess DataLoader tuned for heavy HeteroData collation
    # --- loaders ---------------------------------------------------------------
    num_cpu = os.cpu_count() or 8
    num_workers = max(4, min(16, num_cpu // 2))
    pin_memory = torch.cuda.is_available()
    persistent_workers = pin_memory  # only keep workers alive when pinned mem helps

    train_collate = graph_collate
    val_collate   = graph_collate
    test_collate  = graph_collate

    train_loader = DataLoader(
        train_ds,
        batch_size=args.batch_size,
        shuffle=True,
        num_workers=num_workers,
        pin_memory=pin_memory,
        persistent_workers=persistent_workers,
        prefetch_factor=2,
        collate_fn=train_collate,
        drop_last=False,
    )
    val_loader = DataLoader(
        val_ds,
        batch_size=args.batch_size,
        shuffle=False,
        num_workers=max(2, num_workers // 2),
        pin_memory=pin_memory,
        persistent_workers=persistent_workers,
        prefetch_factor=2,
        collate_fn=val_collate,
    )
    test_loader = DataLoader(
        test_ds,
        batch_size=args.batch_size,
        shuffle=False,
        num_workers=max(2, num_workers // 2),
        pin_memory=pin_memory,
        persistent_workers=persistent_workers,
        prefetch_factor=2,
        collate_fn=test_collate,
    )



    if float(getattr(args, "lambda_dom", 0.0)) > 0.0:
        enabled = setup_domain_adaptation(model, train_loader)
        if not enabled:
            print("[Domain] Both domains not observed; disabling domain loss.")
            args.lambda_dom = 0.0

    print("[Chk][train] manifest columns:", list(train_ds.row_df.columns))
    print("[Chk][val  ] manifest columns:", list(val_ds.row_df.columns))
    print("[Chk][test ] manifest columns:", list(test_ds.row_df.columns))


    # ===== Optional: cache embeddings → train only the head =====
    if args.spatial.lower() == "hgt" and args.do_contrastive and getattr(args, "cache_after_pretrain", False):
        print("[Pipeline] Caching train/val embeddings on CPU and training head on GPU …")

        # ---- dedicate lean CPU DataLoaders for caching (no workers, no pin) ----
        cache_bs = max(32, min(args.batch_size, 128))  # small batches reduce peak RAM during caching
        cache_train_loader = make_loader(
            train_ds,
            batch_size=args.batch_size,
            shuffle=False,
            num_workers=0,         # ← single-process
            pin_memory=False,
            persistent_workers=False,
            collate_fn=train_collate,
            prefetch_factor=None,  # ← explicitly disable
        )
        cache_val_loader = make_loader(
            val_ds,
            batch_size=args.batch_size,
            shuffle=False,
            num_workers=0,
            pin_memory=False,
            persistent_workers=False,
            collate_fn=val_collate,
            prefetch_factor=None,
        )


        # 1) Build LIGHTWEIGHT CPU cache loaders: workers=0, no pin/prefetch/persistent
        def _make_cache_loader(ds, collate):
            return DataLoader(
                ds,
                batch_size=args.batch_size,
                shuffle=False,
                num_workers=0,             # ← single-process
                pin_memory=False,          # ← avoid pin-memory thread
                persistent_workers=False,  # ← not used with workers=0, but explicit
                collate_fn=collate         # ← reuse the same collate you chose above
                # IMPORTANT: do NOT pass prefetch_factor when num_workers == 0
            )

        cache_train_loader = _make_cache_loader(train_ds, train_collate)
        cache_val_loader   = _make_cache_loader(val_ds,   val_collate)

        # 2) Cache CPU embeddings (graph_embed → [B, H])
        cache_embeddings(model, cache_train_loader, device="cpu", out_path="train_cache.pt")
        cache_embeddings(model, cache_val_loader,   device="cpu", out_path="val_cache.pt")


        # 2) Freeze everything except the classifier
        freeze_all_but_classifier(model)

        # 3) Train the head from cached embeddings
        device_head = "cuda" if torch.cuda.is_available() else "cpu"
        head = getattr(model, "classifier", None)
        if head is None:
            raise RuntimeError("Expected model.classifier to exist for head-only training.")
        head_epochs = int(getattr(args, "cache_head_epochs", 10))
        train_head_from_cache("train_cache.pt", head, epochs=head_epochs, device=device_head)

        # 4) Unfreeze encoder and rebuild optimizer → continue to full supervised training
        for p in model.parameters():
            p.requires_grad = True
        optimizer = torch.optim.AdamW(model.parameters(), lr=(args.lr or 3e-4), weight_decay=5e-4)
        print("[Pipeline] Unfroze encoder + rebuilt optimizer; continuing to full supervised training …")
        model.to(device)


        # 5) (optional) evaluate head on val_cache.pt similarly
        # Done with this branch; skip the full supervised encoder training if you want
        # return



    # real-only validation subset (aligns distribution with test)
    real_indices = []
    if args.T == 1:
        for i in range(len(val_ds.row_df)):
            row = val_ds.row_df.iloc[i]
            is_real = not (isinstance(row.get("json_path"), str) and row["json_path"])
            if is_real: real_indices.append(i)
    else:
        for k, start in enumerate(val_ds.window_starts):
            label_row = start + args.T - 1
            row = val_ds.row_df.loc[label_row]
            is_real = not (isinstance(row.get("json_path"), str) and row["json_path"])
            if is_real: real_indices.append(k)

    from torch.utils.data import Subset
    if len(real_indices) > 0:
        real_val_loader = DataLoader(
            Subset(val_ds, real_indices), shuffle=False,
            batch_size=args.batch_size, num_workers=num_workers,
            pin_memory=False, persistent_workers=False, prefetch_factor=2,
            collate_fn=val_collate,
        )

    else:
        print("[Warn] Could not build real-only val subset; falling back to full val.")
        real_val_loader = val_loader

    # --- loss/optim schedules --------------------------------------------------
    class_weights = class_weights_cpu.to(device)

    lbl_smooth = float(getattr(args, "label_smoothing", 0.02))
    if float(getattr(args, "focal_gamma", 0.0)) > 0.0:
        γ = float(args.focal_gamma)
        def criterion(logits, targets):
            ce = F.cross_entropy(logits, targets, weight=class_weights, reduction="none", label_smoothing=lbl_smooth)
            pt = torch.exp(-ce)
            return ((1.0 - pt)**γ * ce).mean()
    else:
        criterion = nn.CrossEntropyLoss(weight=class_weights, label_smoothing=lbl_smooth)


    warmup_scheduler  = torch.optim.lr_scheduler.LinearLR(optimizer, start_factor=0.30, total_iters=3)
    plateau_scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode="max", factor=0.5, patience=4, verbose=True)

    # --- book-keeping -----------------------------------------------------------
    scaler         = GradScaler()
    no_improve     = 0
    best_global_thr= 0.50
    best_global_f1 = -1.0

    # seed EMA from first calibration; do not assume 0.50 a priori
    thr_ema        = None
    print("→ training on", device)


    with torch.no_grad():
        m = next(iter(train_loader))
        m = m.to(device)
        test_logits = model(m).float()
        print("[Sanity] logits shape:", tuple(test_logits.shape),
            "dtype:", test_logits.dtype, 
            "mean/std:", float(test_logits.mean().item()), float(test_logits.std().item()))

    # --- train loop ------------------------------------------------------------
    for epoch in range(1, args.epochs + 1):
        model.train()
        # model.apply(set_bn_eval)

        total_loss = 0.0
        step_count = 0
        use_amp    = True  # keep AMP on for speed

        pbar = tqdm(train_loader, desc=f"Epoch {epoch}/{args.epochs}", leave=False, ncols=100)
        for batch_idx, batch in enumerate(pbar, start=1):
            batch = batch.to(device, non_blocking=True)

            # Hetero sanitation (no-op for homogeneous)
            if isinstance(batch, HeteroData):
                try:
                    _sanitize_hetero_batch_(
                        batch,
                        num_node_types=int(getattr(model, "node_emb").num_embeddings),
                        device=device,
                    )
                except Exception:
                    pass

            # Online augs (drop-edge / temporal jitter)
            if model.training and (float(getattr(args, "dropedge_p", 0.0)) > 0.0 or float(getattr(args, "temporal_jitter", 0.0)) > 0.0):
                if "augment_batch" in globals():
                    try:
                        augment_batch(
                            batch,
                            dropedge_p=float(getattr(args, "dropedge_p", 0.0)),
                            temporal_jitter=float(getattr(args, "temporal_jitter", 0.0)),
                        )
                    except Exception:
                        pass  # be robust

            # First-batch probes (compact)
            if epoch == 1 and batch_idx == 1:
                try:
                    print(f"[Chk] batch graph size: {get_graph_size_info(batch)}")
                except Exception:
                    pass
                if hasattr(batch, "y") and batch.y is not None:
                    try:
                        uniq, cnt = torch.unique(batch.y, return_counts=True)
                        print("[Chk] first-batch label histogram →",
                            dict(zip(uniq.detach().cpu().tolist(), cnt.detach().cpu().tolist())))
                    except Exception:
                        pass
                if args.model == "mptcn_tts" and args.spatial == "hgt":
                    try:
                        sizes = {}
                        for nt in getattr(batch, "node_types", []):
                            if hasattr(batch[nt], "x_seq") and batch[nt].x_seq is not None:
                                sizes[nt] = int(batch[nt].x_seq.size(0))
                        print("[HGT first-batch per-type sizes]", sizes if sizes else "none")
                    except Exception:
                        pass

            optimizer.zero_grad(set_to_none=True)

            # ---------- Forward (MixUp optional) ----------
            got_mix = False
            y_a_mix = y_b_mix = lam_mix = None

            if "mixup_graph_logits" in globals() and float(getattr(args, "mixup_alpha", 0.0)) > 0.0:
                try:
                    mix_tuple = mixup_graph_logits(model, batch, alpha=float(args.mixup_alpha))
                    if mix_tuple is not None:
                        logits, y_a_mix, y_b_mix, lam_mix = mix_tuple
                        got_mix = True
                except Exception:
                    got_mix = False

            if not got_mix:
                if use_amp:
                    with autocast(enabled=True, dtype=(torch.bfloat16 if bf16 else torch.float16)):
                        logits = model(batch)
                else:
                    logits = model(batch)

            # ---------- Classification + auxiliary losses (robust) ----------
            # Always sanitize logits first
            if not torch.isfinite(logits).all():
                optimizer.zero_grad(set_to_none=True)
                torch.cuda.empty_cache()
                continue
            logits = torch.nan_to_num(logits.float(), nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)

            # 1) Classification loss (MixUp or vanilla)
            if hasattr(batch, "y_mix"):
                y_a, y_b, lam = batch.y_mix
                cls_loss = lam * F.cross_entropy(logits, y_a) + (1.0 - lam) * F.cross_entropy(logits, y_b)
            elif got_mix and (y_a_mix is not None):
                cls_loss = lam_mix * F.cross_entropy(logits, y_a_mix) + (1.0 - lam_mix) * F.cross_entropy(logits, y_b_mix)
            else:
                cls_loss = criterion(logits, batch.y)  # may include label smoothing / weights

            # ---- NEW: logit penalty to discourage extreme margins / improve calibration
            penalty_coef = float(getattr(args, "logit_penalty", 1e-4))
            logit_penalty = penalty_coef * logits.float().pow(2).mean()

            # 2) Initialize aux losses to zero (so they always exist)
            supc     = torch.zeros((), device=logits.device, dtype=logits.dtype)
            dom_loss = torch.zeros((), device=logits.device, dtype=logits.dtype)

            # 3) Supervised Contrastive (optional)
            _supcon_lambda = float(getattr(args, "supcon_lambda", 0.0))
            if _supcon_lambda > 0.0:
                try:
                    # prefer model.embed if available; fallback to graph_embed if not
                    if hasattr(model, "embed"):
                        z = model.embed(batch)
                    elif hasattr(model, "graph_embed"):
                        z = model.graph_embed(batch)
                    else:
                        z = None
                    if (z is not None) and torch.is_tensor(z) and z.numel() > 0:
                        supc = supervised_contrastive_loss(
                            z.float(), batch.y, temperature=float(getattr(args, "supcon_tau", 0.07))
                        ).to(logits.dtype)
                except Exception:
                    pass  # keep supc at 0.0

            # 4) Domain adaptation (optional)
            _lambda_dom = float(getattr(args, "lambda_dom", 0.0))
            if _lambda_dom > 0.0 and hasattr(model, "domain_adapter"):
                try:
                    GradRev.λ = _lambda_dom
                    if use_amp:
                        with autocast(enabled=True, dtype=(torch.bfloat16 if bf16 else torch.float16)):
                            g = model.graph_embed(batch)
                            dom_logits = model.domain_adapter(g)
                    else:
                        g = model.graph_embed(batch)
                        dom_logits = model.domain_adapter(g)
                    if torch.isfinite(dom_logits).all():
                        dom_logits = torch.nan_to_num(dom_logits.float(), nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)
                        dom_loss   = F.cross_entropy(dom_logits, batch.domain).to(logits.dtype)
                except Exception:
                    GradRev.λ = 0.0
                    pass
            else:
                GradRev.λ = 0.0

            # 5) Total loss (CLS + LOGIT_PENALTY + optional SUPC + optional DOMAIN)
            # 5) Total loss with Δlogit L2 penalty (warmup)
            # Compute the *gap* only (safe for CE or BCE heads)
            if logits.size(-1) == 2:
                delta = (logits[:, 1] - logits[:, 0]).float()
            else:
                delta = logits.squeeze(-1).float()  # BCE head

            if (epoch == 1 and batch_idx % 200 == 0) or (epoch % 2 == 0 and batch_idx == 1):
                with torch.no_grad():
                    dmean = float(delta.mean().abs().item())
                    dstd  = float(delta.std().item())
                    print(f"[TrainDiag] Δlogit |mean|={dmean:.4f} std={dstd:.4f} pen_w={pen_warm:.2f} λ={gap_l2:.1e}")



            # Warmup the penalty over first 3 epochs
            pen_warm = min(1.0, max(0.0, (epoch - 1) / 3.0))
            gap_l2   = float(getattr(args, "logit_l2", 0.0)) * pen_warm
            logit_penalty = gap_l2 * delta.pow(2).mean()

            loss = cls_loss + logit_penalty
            if _supcon_lambda > 0.0:
                loss = loss + _supcon_lambda * supc
            if _lambda_dom > 0.0:
                loss = loss + _lambda_dom * dom_loss

            total_loss += float(loss.detach().item())

            # ---------- Backward ----------
            if use_amp:
                try:
                    scaler.scale(loss / accum_steps).backward()
                except RuntimeError as e:
                    if "illegal memory access" in str(e).lower():
                        print("[Fatal] CUDA illegal memory access – exiting to reset context.")
                        import sys; sys.exit(2)
                    raise
                if (batch_idx % accum_steps == 0) or (batch_idx == len(train_loader)):
                    scaler.unscale_(optimizer)
                    bad_grad = False
                    for p in model.parameters():
                        if p.grad is not None and not torch.isfinite(p.grad).all():
                            bad_grad = True; break
                    if bad_grad:
                        optimizer.zero_grad(set_to_none=True)
                        torch.cuda.empty_cache()
                        continue
                    torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
                    scaler.step(optimizer)
                    scaler.update()
                    optimizer.zero_grad(set_to_none=True)
                    step_count += 1
            else:
                try:
                    (loss / accum_steps).backward()
                except RuntimeError as e:
                    if "illegal memory access" in str(e).lower():
                        print("[Fatal] CUDA illegal memory access – exiting to reset context.")
                        import sys; sys.exit(2)
                    raise
                if (batch_idx % accum_steps == 0) or (batch_idx == len(train_loader)):
                    torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
                    optimizer.step()
                    optimizer.zero_grad(set_to_none=True)
                    step_count += 1

            pbar.set_postfix(loss=f"{(total_loss / max(1, step_count)):.4f}")

        train_loss = total_loss / max(1, step_count)


 
        # --- VALIDATION: compute probs on VAL in fp32 (no AMP) ---
        # --- VALIDATION: compute probs on VAL in fp32 (no AMP) ---
        # --- VALIDATION: compute probs on VAL in fp32 (no AMP), using Δlogit→sigmoid ---


        # --- VALIDATION: compute p(y=1) on VAL in fp32 (no AMP) ---
        # --- VALIDATION: compute p(y=1) on VAL in fp32 (no AMP) ---
        # --- VALIDATION: compute p(y=1) on VAL in fp32 (no AMP) ---
        # --- VALIDATION: collect p(y=1) on VAL in fp32 ---
        # --- VALIDATION: compute p(y=1) on VAL in fp32 (no AMP) ---

       # --- VALIDATION: compute p(y=1) on VAL in fp32 (no AMP) ---
        model.eval()
        y_true, y_prob = [], []
        deltas = []  # <-- collect Δlogit for diagnostics

        with torch.no_grad():
            for batch in val_loader:
                b = batch.to(device, non_blocking=True)
                logits = model(b).float()                 # [B, 2] in fp32
                logits = torch.nan_to_num(logits, nan=0.0, posinf=50.0, neginf=-50.0).clamp_(-60, 60)

                # --- NEW: monitor Δlogit distribution to catch collapses ---
                if logits.size(-1) == 2:
                    d = (logits[:, 1] - logits[:, 0]).float()
                else:
                    d = logits.squeeze(-1).float()
                deltas.append(d.detach().cpu())

                # stable Δlogit→sigmoid (returns p(y=1))
                p1 = _probs_from_logits_binary(logits)

                y_true.extend(b.y.detach().cpu().tolist())
                y_prob.extend(p1.detach().cpu().tolist())

        y_true = np.asarray(y_true, dtype=np.int64)
        y_prob = np.asarray(y_prob, dtype=np.float32)

        # Diagnostics: p(y=1)
        if y_prob.size:
            q5, q25, q50, q75, q95 = np.quantile(y_prob, [0.05, 0.25, 0.50, 0.75, 0.95])
            std_p = float(np.std(y_prob))
            print(f"[Diag] p1 quantiles: 5%={q5:.3f}, 25%={q25:.3f}, 50%={q50:.3f}, 75%={q75:.3f}, 95%={q95:.3f} | std={std_p:.4f}")
        else:
            print("[Diag] p1 unavailable (empty VAL)")

        # Diagnostics: Δlogit (optional but useful)
        if len(deltas):
            dcat = torch.cat(deltas).numpy()
            dq5, dq25, dq50, dq75, dq95 = np.quantile(dcat, [0.05, 0.25, 0.50, 0.75, 0.95])
            dmean, dstd = float(np.mean(dcat)), float(np.std(dcat))
            print(f"[Diag][Δlogit] mean={dmean:.3f} std={dstd:.3f} | q5={dq5:.3f} q25={dq25:.3f} q50={dq50:.3f} q75={dq75:.3f} q95={dq95:.3f}")
        else:
            print("[Diag][Δlogit] unavailable (empty VAL)")

        # PR-based thresholding on VAL (probabilities only)
        best_thr = calibrate_threshold_from_arrays(
            y_true, y_prob,
            beta=float(getattr(args, "calib_beta", 0.7)),
            min_precision=(None if getattr(args, "min_precision", None) is None else float(getattr(args, "min_precision"))),
            max_pos_rate_over_base=float(getattr(args, "calib_max_pos_delta", 0.08)),
            min_pos_frac=float(getattr(args, "calib_min_pos_frac", 0.01)),
        )
        best_thr = _jitter_thr(best_thr)

        # Report calibration point (strict '>')
        pos_rate_cal = float((y_prob > best_thr).mean()) if y_prob.size else 0.0
        y_pred_cal   = (y_prob > best_thr).astype(np.int64) if y_prob.size else np.array([], dtype=np.int64)
        print(f"[Calib/VAL] thr={best_thr:.3f} | P={skm.precision_score(y_true, y_pred_cal, zero_division=0):.3f} "
            f"| R={skm.recall_score(y_true, y_pred_cal, zero_division=0):.3f} | pos@thr={pos_rate_cal:.3f}")

        # EMA smoothing for threshold across epochs
       # EMA smoothing for threshold across epochs
        alpha   = float(getattr(args, "thr_ema_alpha", 0.10))
        thr_ema = float(best_thr) if (thr_ema is None) else (1.0 - alpha) * float(thr_ema) + alpha * float(best_thr)
        use_thr = float(_jitter_thr(thr_ema))

        # Guardrails derived from VAL base rate
        base_rate = float(y_true.mean()) if y_true.size else 0.5
        cap   = min(0.75, base_rate + float(getattr(args, "calib_max_pos_delta", 0.08)))
        floor = max(float(getattr(args, "calib_min_pos_frac", 0.01)), min(base_rate, 0.49))

        # Recompute pos_rate at the *smoothed* threshold
        pos_rate = float((y_prob > use_thr).mean()) if y_prob.size else 0.0

        # Apply guardrails (strict '>')
        if pos_rate > cap:
            use_thr = float(np.quantile(y_prob, 1.0 - cap))
        elif pos_rate < floor and std_p > 1e-9:
            use_thr = float(np.quantile(y_prob, 1.0 - floor))

        use_thr = float(_jitter_thr(use_thr))



        # Metrics on VAL at use_thr
        y_pred = (y_prob > use_thr).astype(np.int64) if y_prob.size else np.array([], dtype=np.int64)
        prec   = skm.precision_score(y_true, y_pred, zero_division=0) if y_true.size else 0.0
        rec    = skm.recall_score(y_true, y_pred, zero_division=0)    if y_true.size else 0.0
        val_f1 = skm.f1_score(y_true, y_pred, zero_division=0)        if y_true.size else 0.0
        cnt    = np.bincount(y_pred, minlength=2) if y_pred.size else np.array([0, 0])
        print(f"[Val] thr={use_thr:.3f} | preds 0={cnt[0]} 1={cnt[1]} | prec {prec:.3f} | rec {rec:.3f} | f1 {val_f1:.3f}")

        # Schedulers & logging
        warmup_scheduler.step()
        plateau_scheduler.step(val_f1)
        print(f"Epoch {epoch:02d} | train_loss {train_loss:.4f} | val_f1 {val_f1:.4f}")

        # Checkpoint logic
        improved = bool(val_f1 > (best_global_f1 + 1e-4))
        if improved:
            best_global_f1  = val_f1
            best_global_thr = float(use_thr)   # save the smoothed threshold actually used
            torch.save(model.state_dict(), model_dir / ckpt_name)
            no_improve = 0
        else:
            no_improve += 1
            if no_improve >= args.early_stop:
                print("Early stopping triggered.")
                break

        # === After each epoch: reload best ckpt, optionally fit temperature on VAL logits, then TEST once ===
        print("Reloading best checkpoint …")
        model.load_state_dict(torch.load(model_dir / ckpt_name, map_location=device))
        model.to(device).eval()

        # Temperature scaling (skip if collapse)
        fit_T = (std_p >= 1e-6)
        if fit_T:
            print("Calibrating temperature on validation …")
            T_val = fit_temperature(model, val_loader, device)        # returns scalar T
            print(f"[TempScale] learned T = {T_val:.3f}")

            # Transform the EMA-smoothed threshold into post-T space:
            thr_preT   = float(use_thr)
            logit_thr  = _prob_to_logit(thr_preT)
            thr_postT  = _logit_to_prob(logit_thr / max(T_val, 1e-6))
            use_thr    = _jitter_thr(thr_postT)
            print(f"[ThrTransform] pre-T thr={thr_preT:.6f} → post-T thr={use_thr:.6f} (T={T_val:.3f})")
        else:
            print("[TempScale] skipped (scores collapsed).")
            T_val = 1.0

        # --- VAL sanity with T applied (using post-T 'use_thr') ---
        with torch.no_grad():
            y_true_val, y_prob_valT = [], []
            for batch in val_loader:
                b = batch.to(device, non_blocking=True)
                logits = model(b).float()
                logits = _apply_temperature(logits, T_val)
                p1T    = _probs_from_logits_binary(logits)
                y_true_val.extend(b.y.detach().cpu().tolist())
                y_prob_valT.extend(p1T.detach().cpu().tolist())

        f1_valT = skm.f1_score(np.asarray(y_true_val),
                            (np.asarray(y_prob_valT) > use_thr).astype(np.int64),
                            zero_division=0)
        print(f"[Final/VAL] thr@T={use_thr:.3f} | F1={f1_valT:.3f}")

        # --- TEST with (T_val, use_thr) chosen on VAL ---
        print("Evaluating best checkpoint on the test split …")
        model.eval()
        y_true_te, y_prob_teT = [], []
        with torch.no_grad():
            for batch in test_loader:
                b = batch.to(device, non_blocking=True)
                logits = model(b).float()
                logits = _apply_temperature(logits, T_val)
                p1T    = _probs_from_logits_binary(logits)
                y_true_te.extend(b.y.detach().cpu().tolist())
                y_prob_teT.extend(p1T.detach().cpu().tolist())

        y_true_te  = np.asarray(y_true_te, dtype=np.int64)
        y_prob_teT = np.asarray(y_prob_teT, dtype=np.float32)
        y_pred_te  = (y_prob_teT > use_thr).astype(np.int64)

        metrics = {
            "accuracy":  skm.accuracy_score(y_true_te, y_pred_te),
            "precision": skm.precision_score(y_true_te, y_pred_te, zero_division=0),
            "recall":    skm.recall_score(y_true_te, y_pred_te, zero_division=0),
            "f1":        skm.f1_score(y_true_te, y_pred_te, zero_division=0),
        }
        print("Test metrics (T & thr from VAL):", metrics)

        pd.DataFrame([metrics]).to_csv(results_dir / "test_metrics.csv", index=False)
        pd.DataFrame({"ground_truth": y_true_te, "prediction": y_pred_te, "probability": y_prob_teT}).to_csv(
            results_dir / "predictions.csv", index=False
        )

        # Plotting only if both classes predicted
        if len(np.unique(y_pred_te)) > 1:
            plot_conf_mat(y_true_te, y_pred_te, results_dir / "confusion_matrix.png")
            plot_roc_pr(y_true_te, y_prob_teT, results_dir / "roc_curve.png", results_dir / "pr_curve.png")
        else:
            print("[Warn] Only one class predicted on test; skipping plots.")







def parse_args():
    import argparse

    parser = argparse.ArgumentParser(
        description="MPTCN-TTS / HGT training on Devign",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )

    # ---------------- Model / baseline ----------------
    parser.add_argument(
        "--model",
        choices=["mptcn_tts", "gin", "gat", "gcn", "sage", "mpnn", "rgcn", "han", "dgcnn", "pna", "deepergcn"],
        default="mptcn_tts",
        help="Which architecture/baseline to train.",
    )
    parser.add_argument("--spatial", default="hgt", help="Spatial operator / variant (e.g., hgt/gcn/gat/cheb...).")
    parser.add_argument("--temporal", choices=["tcn", "gru"], default="tcn", help="Temporal encoder type.")

    # ---------------- Calibration / thresholding ----------------
    parser.add_argument(
        "--min-precision",
        type=float,
        default=None,
        help="Optional precision floor during PR-based threshold calibration (e.g., 0.70). Omit to disable.",
    )
    parser.add_argument(
        "--min-recall",
        type=float,
        default=None,
        help="Optional recall floor during PR-based threshold calibration (e.g., 0.25). Omit to disable.",
    )
    parser.add_argument(
        "--calib-beta",
        type=float,
        default=0.7,
        help="F-beta used in PR-space threshold calibration (beta<1 favors precision).",
    )
    parser.add_argument(
        "--thr-ema-alpha",
        type=float,
        default=0.10,
        help="EMA smoothing for threshold across epochs (0..1). Set 0 to disable.",
    )
    parser.add_argument(
        "--calib-max-pos-delta",
        type=float,
        default=0.08,
        help="Cap on positive rate during calibration: pos_rate <= base_rate + delta.",
    )
    parser.add_argument(
        "--calib-min-pos-frac",
        type=float,
        default=0.01,
        help="Floor on positive rate during calibration to avoid predicting zero positives.",
    )

    # ---------------- Data: per-split overrides & augmented test ----------------
    parser.add_argument(
        "--train-manifest",
        type=str,
        default=None,
        help="CSV manifest for TRAIN split (overrides MANIFESTS['train']).",
    )
    parser.add_argument(
        "--val-manifest",
        type=str,
        default=None,
        help="CSV manifest for VAL split (overrides MANIFESTS['val']).",
    )
    parser.add_argument(
        "--test-manifest",
        type=str,
        default=None,
        help="CSV manifest for TEST split (overrides MANIFESTS['test']). Use this for T=6 test if you have a dedicated file.",
    )

    parser.add_argument(
        "--train-json-root",
        type=str,
        default=None,
        help="JSON root for TRAIN split (overrides JSON_ROOTS['train']).",
    )
    parser.add_argument(
        "--val-json-root",
        type=str,
        default=None,
        help="JSON root for VAL split (overrides JSON_ROOTS['val']).",
    )
    parser.add_argument(
        "--test-json-root",
        type=str,
        default=None,
        help="JSON root for TEST split (overrides JSON_ROOTS['test']).",
    )

    parser.add_argument(
        "--use-aug-test",
        action="store_true",
        help="If set (and --test-manifest not provided), try to use an augmented/windowed test manifest and prefer T_test=6.",
    )

    # ---------------- Temporal lengths ----------------
    parser.add_argument("--T", type=int, default=6, help="Temporal length for TRAIN/VAL.")
    parser.add_argument("--T-test", dest="T_test", type=int, default=1, help="Temporal length for TEST.")
    parser.add_argument(
        "--pre-T",
        type=int,
        default=6,
        help="Temporal length for contrastive pretraining dataset (if used).",
    )

    # ---------------- Architecture hyperparams ----------------
    parser.add_argument("--Lt", type=int, default=2, help="# temporal layers.")
    parser.add_argument("--Ls", type=int, default=2, help="# spatial layers.")
    parser.add_argument("--Kt", type=int, default=3, help="Temporal kernel/receptive field.")
    parser.add_argument("--Ks", type=int, default=3, help="Spatial kernel (if applicable).")

    parser.add_argument("--emb-dim", dest="emb_dim", type=int, default=64, help="Embedding dim.")
    parser.add_argument("--hidden-dim", dest="hidden_dim", type=int, default=256, help="Hidden dim.")
    parser.add_argument("--num-classes", dest="num_classes", type=int, default=2, help="# classes.")



    

    # Baseline-specific knobs
    parser.add_argument("--layers", type=int, default=3, help="# GNN layers (for many baselines).")
    parser.add_argument("--heads", type=int, default=2, help="# attention heads (GAT/HAN/HGT).")
    parser.add_argument("--bases", type=int, default=32, help="# bases (RGCN).")
    parser.add_argument("--edge-emb-dim", type=int, default=32, help="Edge embedding dim (MPNN/RGCN).")
    parser.add_argument("--knn", type=int, default=20, help="k for DGCNN.")
    parser.add_argument("--sort-pool-k", type=int, default=30, help="SortPool k for DGCNN.")

    # HGT extras
    parser.add_argument("--hgt-max-rel", type=int, default=800, help="Max HGT relation triplets to keep.")
    parser.add_argument("--hgt-heads", type=int, default=2, help="HGT heads.")

    # ---------------- Regularization / augs ----------------
    parser.add_argument("--dropout", type=float, default=0.30, help="Dropout.")
    parser.add_argument("--row-norm", action="store_true", help="Use row-normalization where supported.")
    parser.add_argument("--mixup-alpha", type=float, default=0.0, help="Graph-level MixUp alpha (0=off).")
    parser.add_argument("--dropedge-p", type=float, default=0.0, help="Random edge drop prob (train only).")
    parser.add_argument(
        "--temporal-jitter",
        type=float,
        default=0.0,
        help="Probability to copy prev step token into last step (T>1).",
    )


    parser.add_argument("--logit-l2", type=float, default=1e-6,
    help="L2 on the binary logit gap (Δ=logit1-logit0). Use tiny values; warmed up over first 3 epochs.")

    # ---------------- Losses / aux objectives ----------------
    parser.add_argument("--focal-gamma", type=float, default=0.0, help="Focal loss gamma (0=off).")
    parser.add_argument("--lambda-dom", dest="lambda_dom", type=float, default=0.0, help="Domain adaptation weight.")
    parser.add_argument("--supcon-lambda", type=float, default=0.0, help="Supervised contrastive loss weight.")
    parser.add_argument("--supcon-tau", type=float, default=0.07, help="SupCon temperature.")

    # ---------------- Optimization / scheduling ----------------
    parser.add_argument("--epochs", type=int, default=25, help="# training epochs.")
    parser.add_argument("--batch-size", type=int, default=128, help="Batch size.")
    parser.add_argument("--train-batch-size", type=int, default=None, help="Alias to override --batch-size.")
    parser.add_argument("--accum-steps", type=int, default=1, help="Gradient accumulation steps.")
    parser.add_argument("--lr", type=float, default=1e-4, help="Learning rate.")
    parser.add_argument("--early-stop", type=int, default=8, help="Early-stop patience (in epochs).")
    parser.add_argument("--val-interval", type=int, default=2, help="Validate every N epochs.")
    parser.add_argument("--seed", type=int, default=42, help="Random seed.")
    parser.add_argument("--no-progress", action="store_true", help="Disable progress bars/logging noise.")
    # parser.add_argument("--logit-l2", type=float, default=1e-4,
    #     help="L2 penalty on logits to prevent overconfident/saturated scores (0 to disable).")
    parser.add_argument("--label-smoothing", type=float, default=0.02,
        help="Label smoothing for CE (0..0.1 typical).")

    # AMP/bfloat16 handled internally; no flags here.

    # ---------------- Contrastive pretraining pipeline ----------------
    parser.add_argument("--do-contrastive", action="store_true", help="Run contrastive pretraining before supervised.")
    parser.add_argument("--pre-epochs", type=int, default=60, help="# epochs for contrastive pretraining.")
    parser.add_argument("--tau", type=float, default=0.1, help="InfoNCE temperature (contrastive).")

    parser.add_argument(
        "--cache-after-pretrain",
        action="store_true",
        help="After contrastive pretrain: cache embeddings and train only the head, then unfreeze.",
    )
    parser.add_argument("--cache-head-epochs", type=int, default=10, help="Head-only training epochs if caching.")

    # ---------------- Text fusion (optional) ----------------
    parser.add_argument("--text-fusion", action="store_true", help="Enable text/code fusion.")
    parser.add_argument("--unfreeze-text-epoch", type=int, default=0, help="Epoch to unfreeze text encoder (0=never).")
    parser.add_argument("--text-max-len", type=int, default=512)
    parser.add_argument("--text-chunk-len", type=int, default=256)
    parser.add_argument("--text-chunk-stride", type=int, default=128)
    parser.add_argument("--text-max-chunks", type=int, default=8)
    parser.add_argument("--text-pool", choices=["mean", "cls", "attn"], default="mean")

    # ---------------- Parse & post-process ----------------
    args = parser.parse_args()

    # Allow --train-batch-size to override --batch-size
    if args.train_batch_size is not None and args.train_batch_size > 0:
        args.batch_size = int(args.train_batch_size)

    # Clamp/sanitize a couple of knobs
    args.accum_steps = max(1, int(getattr(args, "accum_steps", 1)))

    return args




if __name__ == "__main__":
    args = parse_args()
    train(args)





"""


#combination A


python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial cheb\
  --temporal tcn \
  --T 6\
  --Lt 3\
  --Ls 1\
  --Kt 5\
  --Ks 3 \
  --batch-size 256\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 25\
  --lr 1e-4\
  --dropout 0.5 \
  --focal-gamma 1 \
  --row-norm \
  --do-contrastive\
  --pre-epochs 60\
  --tau 0.09 \
  --T-test 1


#combination B

python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial cheb\
  --temporal tcn \
  --T 6\
  --Lt 2\
  --Ls 2\
  --Kt 3\
  --Ks 3 \
  --row-norm \
  --batch-size 256\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 25\
  --lr 3e-4\
  --dropout 0.2 \
  --do-contrastive\
  --pre-epochs 60\
  --tau 0.1 \
  --supcon-lambda 0.1\
  --supcon-tau 0.07

#combination C

python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial cheb\
  --temporal gru \
  --T 6\
  --Lt 2\
  --Ls 2\
  --Kt 3\
  --Ks 3 \
  --batch-size 256\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 25\
  --lr 5e-4\
  --dropout 0.3 \
  --focal-gamma 1




#combination D

python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial rgcn\
  --temporal tcn \
  --T 6\
  --Lt 2\
  --Ls 2\
  --Kt 3 \
  --batch-size 128\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 25\
  --lr 3e-4\
  --dropout 0.3 \
  --do-contrastive\
  --pre-epochs 60\
  --tau 0.15 \
  --supcon-lambda 0.1\
  --supcon-tau 0.07



#combination E

CUDA_LAUNCH_BLOCKING=1 TORCH_USE_CUDA_DSA=1 \
python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 6 \
  --T-test 1 \
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
  --cache-head-epochs 10



#combination F

python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial cheb\
  --temporal tcn \
  --T 6\
  --Lt 2\
  --Ls 2\
  --Kt 3\
  --Ks 3 \
  --batch-size 256\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 25\
  --lr 3e-4\
  --dropout 0.3


#Combination G
python MPTCN_TTS_devign.py \
  --model mptcn_tts \
  --spatial rgcn\
  --temporal gru \
  --T 6\
  --Lt 2\
  --Ls 2\
  --Kt 3 \
  --batch-size 192\
  --hidden-dim 256\
  --emb-dim 64 \
  --epochs 30\
  --lr 2e-4\
  --dropout 0.25 \
  --lambda-dom 0.02


#combination H
python MPTCN_TTS_DEEPGCN_devign.py \
  --model mptcn_tts \
  --spatial hgt \
  --temporal tcn \
  --T 6 \
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
  --hgt-max-rel 800


#combination I
python MPTCN_TTS_DEEPGCN_devign.py \
  --model pna \
  --temporal tcn \
  --T 6 \
  --T-test 6 \
  --Lt 2 \
  --Ls 2 \
  --Kt 3 \
  --batch-size 16 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
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
  --test-manifest "./workspace/01_Normalized_datasets/03_normalized_devign/manifest_test_advT6.csv"



python MPTCN_TTS_DEEPGCN_devign.py \
  --model pna \
  --temporal tcn \
  --T 6 \
  --T-test 6 \
  --Lt 2 \
  --Ls 4 \
  --Kt 3 \
  --batch-size 16 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 30 \
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
  --test-manifest "./workspace/01_Normalized_datasets/03_normalized_devign/manifest_test_advT6.csv"







#combination J
# combination J (rewritten to match PNA knobs)
python MPTCN_TTS_DEEPGCN_devign.py \
  --model deepergcn \
  --spatial gcn \
  --temporal tcn \
  --T 6 \
  --T-test 6 \
  --Lt 2 \
  --Ls 6 \
  --Kt 3 \
  --batch-size 128 \
  --hidden-dim 256 \
  --emb-dim 64 \
  --epochs 25 \
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
  --test-manifest "./workspace/01_Normalized_datasets/03_normalized_devign/manifest_test_advT6.csv"








"""
