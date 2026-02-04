#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Devign_baseline.py - Production-Grade GNN Vulnerability Detection

A comprehensive implementation supporting multiple GNN architectures for
source code vulnerability detection using Code Property Graphs (CPGs).

Supported Models:
  - 'ggnn':        Gated Graph Neural Network (Original Devign backbone)
  - 'gcn':         Graph Convolutional Network (Isotropic baseline)
  - 'gat':         Graph Attention Network v2 (Edge-aware attention)
  - 'transformer': Graph Transformer (Long-range dependencies)
  - 'hybrid':      GraphGPS-style (Local MPNN + Global Attention)
  - 'rgat':        Relational Graph Attention (Memory-efficient)
  - 'multiview':   Multi-View GGNN (Separate AST/CFG/DFG encoders)
  - 'hyper':       Dual-Attention (GAT + Transformer branches)
  - 'hgt':         Heterogeneous Graph Transformer

Key Features:
  - Size-bucket sampling for stable training with variable graph sizes
  - Memory-efficient implementations for large graphs
  - Dynamic threshold optimization for imbalanced data
  - Comprehensive logging and diagnostics
  - Gradient checkpointing support
  - Pre-activation residuals for deep networks

Author: Research Implementation
Version: 2.0 (Production)
"""

import argparse
import csv
import json
import random
import sys
import warnings
from pathlib import Path
from typing import Optional, Tuple, List, Dict, Any
from collections import defaultdict

import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset as TorchDataset, Sampler
from tqdm import tqdm

from torch_geometric.data import Data
from torch_geometric.loader import DataLoader
from torch_geometric.nn import (
    MessagePassing, GCNConv, GATv2Conv, TransformerConv, 
    GatedGraphConv, SAGPooling
)
from torch_geometric.utils import to_dense_batch, softmax, sort_edge_index

# Optional imports
try:
    from sklearn.metrics import (
        roc_auc_score, f1_score, precision_score, recall_score,
        average_precision_score, roc_curve, precision_recall_curve
    )
    _HAS_SKLEARN = True
except ImportError:
    _HAS_SKLEARN = False
    warnings.warn("scikit-learn not found. Limited metrics available.")

# External model imports (optional)
_HAS_MULTIVIEW = False
_HAS_HYPER = False
_HAS_HGT = False
_HAS_RGAT = False

try:
    from multiview_models import MultiViewGGNN
    _HAS_MULTIVIEW = True
except ImportError:
    pass

try:
    from hypergraph_models import HyperDevignModel
    _HAS_HYPER = True
except ImportError:
    pass

try:
    from hgt_models import HGTDevignModel
    _HAS_HGT = True
except ImportError:
    pass

try:
    from rgat_models import RGATDevignModel
    _HAS_RGAT = True
except ImportError:
    pass

# Anti-collapse utilities
_HAS_ANTI_COLLAPSE = False
try:
    from anti_collapse import (
        AntiCollapseLoss, GradientMonitor, WarmupCosineScheduler,
        compute_collapse_metrics, diagnose_collapse
    )
    _HAS_ANTI_COLLAPSE = True
except ImportError:
    pass


# =============================================================================
# UTILITIES
# =============================================================================

def set_seed(seed: int = 42):
    """Set random seeds for reproducibility."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)
        torch.backends.cudnn.deterministic = True
        torch.backends.cudnn.benchmark = False


def get_device(prefer_cuda: bool = True) -> torch.device:
    """Get the best available device."""
    if prefer_cuda and torch.cuda.is_available():
        device = torch.device("cuda")
        print(f"[Device] Using CUDA: {torch.cuda.get_device_name(0)}")
        print(f"[Device] Memory: {torch.cuda.get_device_properties(0).total_memory / 1e9:.1f} GB")
    else:
        device = torch.device("cpu")
        print("[Device] Using CPU")
    return device


class AverageMeter:
    """Computes and stores the average and current value."""
    def __init__(self):
        self.reset()
    
    def reset(self):
        self.val = 0
        self.avg = 0
        self.sum = 0
        self.count = 0
    
    def update(self, val, n=1):
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count if self.count > 0 else 0


# =============================================================================
# DATASET
# =============================================================================

class CachedDataset(TorchDataset):
    """
    Loads pre-built PyG Data objects from cache directory.
    
    Features:
    - Manifest-based filtering for train/val/test splits
    - Graph size tracking for bucket sampling
    - Automatic class weight calculation
    - Configurable graph size limits
    """
    
    def __init__(
        self,
        cache_dir: Path,
        manifest_path: Optional[Path] = None,
        max_nodes: Optional[int] = None,
        max_edges: Optional[int] = None,
        precompute_sizes: bool = True,
    ):
        super().__init__()
        self.cache_dir = Path(cache_dir)
        self.max_nodes = max_nodes
        self.max_edges = max_edges
        self.pt_paths = []
        self.graph_sizes = []  # For bucket sampling
        
        index_csv = self.cache_dir / "meta" / "index.csv"
        if not index_csv.is_file():
            raise FileNotFoundError(f"index.csv not found at: {index_csv}")

        # Load manifest keys if provided
        manifest_keys = None
        if manifest_path and Path(manifest_path).exists():
            manifest_keys = set()
            with Path(manifest_path).open("r", encoding="utf-8") as f:
                reader = csv.DictReader(f)
                for row in reader:
                    fid = row.get("function_id") or row.get("fid") or row.get("id")
                    if fid:
                        manifest_keys.add(fid.strip())
            print(f"[Dataset] Loaded {len(manifest_keys)} keys from manifest: {Path(manifest_path).name}")

        # Load index and filter
        with index_csv.open("r", newline="", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            for row in reader:
                rel_path = row.get("rel_path") or row.get("path") or row.get("pt_path")
                if not rel_path:
                    continue
                
                # Apply manifest filter
                if manifest_keys is not None:
                    fid = row.get("function_id", "").strip()
                    if fid not in manifest_keys:
                        continue
                
                self.pt_paths.append(self.cache_dir / rel_path)

        if len(self.pt_paths) == 0:
            warnings.warn("[Dataset] Dataset is empty! Check manifest filtering.")
        else:
            print(f"[Dataset] Loaded {len(self.pt_paths)} samples")
        
        # Precompute graph sizes for bucket sampling
        if precompute_sizes and len(self.pt_paths) > 0:
            self._precompute_sizes()
    
    def _precompute_sizes(self, sample_size: int = 5000):
        """Precompute graph sizes for a sample of the dataset."""
        print(f"[Dataset] Precomputing graph sizes (sampling {min(sample_size, len(self.pt_paths))} graphs)...")
        
        indices = list(range(len(self.pt_paths)))
        if len(indices) > sample_size:
            indices = random.sample(indices, sample_size)
        
        self.graph_sizes = [0] * len(self.pt_paths)
        
        for i in tqdm(indices, desc="Sizing", leave=False):
            try:
                data = torch.load(self.pt_paths[i], map_location="cpu")
                size = data.x.size(0) if hasattr(data, 'x') else 0
                self.graph_sizes[i] = size
            except Exception:
                self.graph_sizes[i] = 0
        
        # Estimate sizes for non-sampled graphs using median
        sampled_sizes = [self.graph_sizes[i] for i in indices if self.graph_sizes[i] > 0]
        if sampled_sizes:
            median_size = int(np.median(sampled_sizes))
            for i in range(len(self.graph_sizes)):
                if self.graph_sizes[i] == 0:
                    self.graph_sizes[i] = median_size
        
        sizes = [s for s in self.graph_sizes if s > 0]
        if sizes:
            print(f"[Dataset] Graph sizes: min={min(sizes)}, max={max(sizes)}, "
                  f"mean={np.mean(sizes):.1f}, median={np.median(sizes):.1f}")
    
    def calculate_pos_weight(self, sample_size: int = 2000) -> float:
        """Calculate positive class weight from random sample."""
        print(f"[Dataset] Calculating class weights (sampling {min(sample_size, len(self))})...")
        
        indices = list(range(len(self)))
        if len(indices) > sample_size:
            indices = random.sample(indices, sample_size)
        
        num_pos = 0
        num_neg = 0
        
        for i in indices:
            try:
                data = self[i]
                label = data.y.item() if hasattr(data, 'y') else 0
                if label == 1:
                    num_pos += 1
                else:
                    num_neg += 1
            except Exception:
                num_neg += 1
        
        if num_pos == 0:
            warnings.warn("[Dataset] No positive samples found!")
            return 1.0
        
        weight = num_neg / num_pos
        print(f"[Dataset] Class distribution: Neg={num_neg}, Pos={num_pos}, Weight={weight:.4f}")
        return weight

    def __len__(self):
        return len(self.pt_paths)
    
    def __getitem__(self, idx: int) -> Data:
        path = self.pt_paths[idx]
        try:
            data = torch.load(path, map_location="cpu")
        except Exception as e:
            warnings.warn(f"[Dataset] Failed to load {path}: {e}")
            return Data(
                x=torch.zeros(1, 1),
                edge_index=torch.zeros(2, 0, dtype=torch.long),
                y=torch.tensor([0])
            )
        
        if not hasattr(data, "y"):
            data.y = torch.tensor([0])
        
        # Apply size limits if configured
        if self.max_nodes and hasattr(data, 'x') and data.x.size(0) > self.max_nodes:
            data = self._truncate_graph(data)
        
        data.cache_index = idx
        return data
    
    def _truncate_graph(self, data: Data) -> Data:
        """Truncate graph to max_nodes, keeping most connected nodes."""
        num_nodes = data.x.size(0)
        
        # Calculate node degrees
        if data.edge_index.size(1) > 0:
            degrees = torch.zeros(num_nodes, dtype=torch.long)
            degrees.scatter_add_(0, data.edge_index[0], torch.ones(data.edge_index.size(1), dtype=torch.long))
            degrees.scatter_add_(0, data.edge_index[1], torch.ones(data.edge_index.size(1), dtype=torch.long))
            
            # Keep highest degree nodes
            _, keep_indices = torch.topk(degrees, min(self.max_nodes, num_nodes))
            keep_indices = keep_indices.sort()[0]
        else:
            keep_indices = torch.arange(min(self.max_nodes, num_nodes))
        
        # Create keep mask
        keep_mask = torch.zeros(num_nodes, dtype=torch.bool)
        keep_mask[keep_indices] = True
        
        # Filter nodes
        data.x = data.x[keep_mask]
        
        # Filter and remap edges
        if data.edge_index.size(1) > 0:
            edge_mask = keep_mask[data.edge_index[0]] & keep_mask[data.edge_index[1]]
            data.edge_index = data.edge_index[:, edge_mask]
            
            if hasattr(data, 'edge_type') and data.edge_type is not None:
                data.edge_type = data.edge_type[edge_mask]
            
            # Remap indices
            node_mapping = torch.cumsum(keep_mask.long(), 0) - 1
            data.edge_index = node_mapping[data.edge_index]
        
        return data


class SizeBucketBatchSampler(Sampler):
    """
    Batch sampler that groups graphs by similar sizes.
    
    This significantly reduces variance in batch computation cost and
    gradient magnitudes, leading to more stable training.
    """
    
    def __init__(
        self,
        dataset: CachedDataset,
        batch_size: int,
        shuffle: bool = True,
        drop_last: bool = False,
        num_buckets: int = 10,
    ):
        self.dataset = dataset
        self.batch_size = batch_size
        self.shuffle = shuffle
        self.drop_last = drop_last
        self.num_buckets = num_buckets
        
        # Get graph sizes
        if hasattr(dataset, 'graph_sizes') and len(dataset.graph_sizes) == len(dataset):
            self.sizes = dataset.graph_sizes
        else:
            # Fallback: assume uniform sizes
            self.sizes = [100] * len(dataset)
        
        self._create_buckets()
    
    def _create_buckets(self):
        """Create size-based buckets."""
        # Sort indices by size
        indexed_sizes = [(i, s) for i, s in enumerate(self.sizes)]
        indexed_sizes.sort(key=lambda x: x[1])
        
        # Create buckets
        self.buckets = []
        bucket_size = len(indexed_sizes) // self.num_buckets
        
        for b in range(self.num_buckets):
            start = b * bucket_size
            if b == self.num_buckets - 1:
                end = len(indexed_sizes)
            else:
                end = start + bucket_size
            
            bucket_indices = [idx for idx, _ in indexed_sizes[start:end]]
            self.buckets.append(bucket_indices)
    
    def __iter__(self):
        # Create batches within each bucket
        all_batches = []
        
        for bucket in self.buckets:
            indices = bucket.copy()
            if self.shuffle:
                random.shuffle(indices)
            
            for i in range(0, len(indices), self.batch_size):
                batch = indices[i:i + self.batch_size]
                if len(batch) == self.batch_size or not self.drop_last:
                    all_batches.append(batch)
        
        # Shuffle batches (not within batches)
        if self.shuffle:
            random.shuffle(all_batches)
        
        for batch in all_batches:
            yield batch
    
    def __len__(self):
        total = sum(len(b) for b in self.buckets)
        if self.drop_last:
            return total // self.batch_size
        return (total + self.batch_size - 1) // self.batch_size


def apply_collapse_policy(dataset: CachedDataset, policy: str = "all") -> CachedDataset:
    """Filter dataset based on original vs augmented graphs."""
    policy = str(policy or "all").lower()
    if policy in ("all", "none"):
        return dataset
    
    print(f"[Collapse] Applying policy: {policy}...")
    new_paths = []
    new_sizes = []
    
    for i, pt in enumerate(dataset.pt_paths):
        try:
            d = torch.load(pt, map_location="cpu")
            is_orig = False
            
            if hasattr(d, "is_original") and d.is_original:
                is_orig = True
            elif hasattr(d, "snapshot_idx") and int(d.snapshot_idx) == 0:
                is_orig = True
            
            keep = (policy == "orig" and is_orig) or (policy == "snap" and not is_orig)
            if keep:
                new_paths.append(pt)
                if hasattr(dataset, 'graph_sizes') and len(dataset.graph_sizes) > i:
                    new_sizes.append(dataset.graph_sizes[i])
        except Exception:
            continue
    
    print(f"[Collapse] Kept {len(new_paths)}/{len(dataset.pt_paths)} samples")
    dataset.pt_paths = new_paths
    if new_sizes:
        dataset.graph_sizes = new_sizes
    
    return dataset


def load_vocab(vocab_dir: Path) -> int:
    """Load vocabulary and return number of relations."""
    vocab_dir = Path(vocab_dir)
    
    for filename in ["devign_rel_vocab.json", "edge_type_vocab.json", "rel_vocab.json"]:
        vocab_path = vocab_dir / filename
        if vocab_path.is_file():
            with vocab_path.open("r", encoding="utf-8") as f:
                vocab = json.load(f)
            print(f"[Vocab] Loaded {len(vocab)} relations from {filename}")
            return len(vocab)
    
    warnings.warn("[Vocab] No vocabulary file found. Assuming 5 relations.")
    return 5


# =============================================================================
# LAYERS
# =============================================================================

class DevignConvHead(nn.Module):
    """
    Devign's Hierarchical Conv Readout Module (Section 2.4, Eq 6-9).
    
    Compares initial and final node representations through:
    1. Concatenation and parallel conv processing
    2. Hierarchical max pooling
    3. Element-wise multiplication for interaction
    4. Masked mean pooling for graph-level embedding
    """
    
    def __init__(self, hidden_dim: int, dropout: float = 0.1):
        super().__init__()
        self.hidden_dim = int(hidden_dim)
        
        # Z path (concatenated initial + final)
        self.conv1_z = nn.Conv1d(hidden_dim * 2, hidden_dim, kernel_size=3, padding=1)
        self.conv2_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        # Y path (final only)
        self.conv1_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=3, padding=1)
        self.conv2_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        self.pool = nn.MaxPool1d(kernel_size=2, stride=2)
        self.dropout = nn.Dropout(dropout)
        
        # Batch norm for stability
        self.bn_z = nn.BatchNorm1d(hidden_dim)
        self.bn_y = nn.BatchNorm1d(hidden_dim)
    
    def forward(
        self,
        h_input: torch.Tensor,
        h_final: torch.Tensor,
        batch: torch.Tensor
    ) -> torch.Tensor:
        # Concatenate initial and final representations
        h_cat = torch.cat([h_input, h_final], dim=1)
        
        # Convert to dense batch format
        z_dense, mask = to_dense_batch(h_cat, batch)  # [B, N, 2*H]
        y_dense, _ = to_dense_batch(h_final, batch)   # [B, N, H]
        
        # Transpose for conv1d: [B, C, N]
        z = z_dense.transpose(1, 2)
        y = y_dense.transpose(1, 2)
        
        # Handle small graphs (need at least 4 nodes for 2 pooling layers)
        min_size = 4
        if z.size(2) < min_size:
            pad_size = min_size - z.size(2)
            z = F.pad(z, (0, pad_size))
            y = F.pad(y, (0, pad_size))
            mask_float = F.pad(mask.unsqueeze(1).float(), (0, pad_size))
        else:
            mask_float = mask.unsqueeze(1).float()
        
        # Layer 1: Conv + ReLU + Pool
        z = self.pool(F.relu(self.conv1_z(z)))
        y = self.pool(F.relu(self.conv1_y(y)))
        mask_pooled = F.max_pool1d(mask_float, kernel_size=2, stride=2)
        
        # Layer 2: Conv + ReLU + Pool
        z = self.pool(F.relu(self.conv2_z(z)))
        y = self.pool(F.relu(self.conv2_y(y)))
        mask_pooled = F.max_pool1d(mask_pooled, kernel_size=2, stride=2)
        
        # Apply batch norm
        z = self.bn_z(z)
        y = self.bn_y(y)
        z = self.dropout(z)
        y = self.dropout(y)
        
        # MLP projection
        z_prime = self.mlp_z(z)
        y_prime = self.mlp_y(y)
        
        # Element-wise multiplication (interaction)
        h_mult = z_prime * y_prime
        
        # Masked mean pooling
        mask_bool = (mask_pooled > 0.5)
        h_mult = h_mult * mask_bool.float()
        sum_h = torch.sum(h_mult, dim=2)
        counts = torch.sum(mask_bool.float(), dim=2).clamp(min=1.0)
        
        return sum_h / counts


class RelGraphConv(MessagePassing):
    """
    Memory-Efficient Relational Graph Convolution.
    
    Iterates over relation types instead of expanding weight tensors,
    achieving O(N*R*D) memory instead of O(E*D*D).
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_relations: int,
        dropout: float = 0.2,
        num_bases: Optional[int] = None,
    ):
        super().__init__(aggr="add")
        self.hidden_dim = hidden_dim
        self.num_relations = num_relations
        self.dropout_p = dropout
        
        # Relation-specific weights
        if num_bases is not None and num_bases < num_relations:
            # Basis decomposition for memory efficiency
            self.num_bases = num_bases
            self.basis = nn.Parameter(torch.empty(num_bases, hidden_dim, hidden_dim))
            self.coefficients = nn.Parameter(torch.empty(num_relations, num_bases))
            self.weight = None
        else:
            self.num_bases = None
            self.weight = nn.Parameter(torch.empty(num_relations, hidden_dim, hidden_dim))
            self.basis = None
            self.coefficients = None
        
        self.root_weight = nn.Parameter(torch.empty(hidden_dim, hidden_dim))
        self.bias = nn.Parameter(torch.zeros(hidden_dim))
        
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
        
        self.reset_parameters()
    
    def reset_parameters(self):
        if self.weight is not None:
            nn.init.xavier_uniform_(self.weight)
        if self.basis is not None:
            nn.init.xavier_uniform_(self.basis)
            nn.init.xavier_uniform_(self.coefficients)
        nn.init.xavier_uniform_(self.root_weight)
        nn.init.zeros_(self.bias)
    
    def get_weights(self) -> torch.Tensor:
        if self.weight is not None:
            return self.weight
        return torch.einsum('rb,bio->rio', self.coefficients, self.basis)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor
    ) -> torch.Tensor:
        x_in = x
        out = torch.zeros_like(x)
        
        if edge_type is None:
            edge_type = x.new_zeros(edge_index.size(1), dtype=torch.long)
        
        W = self.get_weights()
        
        for r in range(self.num_relations):
            mask = (edge_type == r)
            if not mask.any():
                continue
            
            edge_index_r = edge_index[:, mask]
            h_r = x @ W[r]
            out = out + self.propagate(edge_index_r, x=h_r)
        
        out = out + x @ self.root_weight + self.bias
        out = F.relu(out)
        out = self.norm(out)
        out = self.dropout(out)
        
        return out + x_in  # Residual
    
    def message(self, x_j: torch.Tensor) -> torch.Tensor:
        return x_j


class HybridGPSLayer(nn.Module):
    """
    GraphGPS-style layer combining local MPNN with global attention.
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_relations: int,
        heads: int = 4,
        dropout: float = 0.2,
    ):
        super().__init__()
        
        # Local: Relational GCN
        self.local_conv = RelGraphConv(hidden_dim, num_relations, dropout)
        
        # Global: Transformer attention
        self.global_conv = TransformerConv(
            hidden_dim, hidden_dim,
            heads=heads, concat=False,
            dropout=dropout, edge_dim=hidden_dim
        )
        
        # Fusion
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
        
        # FFN
        self.ffn = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim * 4),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim * 4, hidden_dim),
        )
        self.norm_ffn = nn.LayerNorm(hidden_dim)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor,
        edge_attr: torch.Tensor,
    ) -> torch.Tensor:
        x_res = x
        
        # Local path (includes residual internally)
        h_local = self.local_conv(x, edge_index, edge_type)
        
        # Global path
        h_global = self.global_conv(x, edge_index, edge_attr=edge_attr)
        
        # Combine (subtract x_res from h_local since it already has residual)
        h = (h_local - x_res) + h_global + x_res
        h = self.norm(h)
        h = self.dropout(h)
        
        # FFN with residual
        h = h + self.ffn(h)
        h = self.norm_ffn(h)
        
        return h


# =============================================================================
# MODELS
# =============================================================================

class DevignModel(nn.Module):
    """
    Unified Devign model with switchable GNN backbones.
    
    Supports: ggnn, gcn, gat, transformer, hybrid
    """
    
    def __init__(
        self,
        in_dim: int,
        hidden_dim: int,
        num_relations: int,
        num_layers: int = 4,
        dropout: float = 0.2,
        model_type: str = "ggnn",
        heads: int = 4,
        use_pooling: bool = False,
        pooling_ratio: float = 0.5,
        readout_type: str = "devign",  # NEW: "devign", "mean", "max", "mean_max"
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        self.model_type = model_type.lower()
        self.num_relations = num_relations
        self.use_pooling = use_pooling
        self.readout_type = readout_type.lower()  # NEW
        
        # Input projection - SIMPLE: matches diagnostic that works
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.ReLU(),
        )
        
        # Optional graph pooling
        if use_pooling:
            self.pool = SAGPooling(hidden_dim, ratio=pooling_ratio)
        else:
            self.pool = None
        
        # Edge type embedding (for attention-based models)
        self.edge_embedding = nn.Embedding(num_relations, hidden_dim)
        
        # GNN layers
        self.layers = nn.ModuleList()
        self.norms = nn.ModuleList()
        
        for _ in range(num_layers):
            if self.model_type == "ggnn":
                self.layers.append(RelGraphConv(hidden_dim, num_relations, dropout))
            
            elif self.model_type == "gcn":
                self.layers.append(GCNConv(hidden_dim, hidden_dim))
                self.norms.append(nn.LayerNorm(hidden_dim))
            
            elif self.model_type == "gat":
                self.layers.append(GATv2Conv(
                    hidden_dim, hidden_dim,
                    heads=heads, concat=False,
                    dropout=dropout, edge_dim=hidden_dim
                ))
                self.norms.append(nn.LayerNorm(hidden_dim))
            
            elif self.model_type == "transformer":
                self.layers.append(TransformerConv(
                    hidden_dim, hidden_dim,
                    heads=heads, concat=False,
                    dropout=dropout, edge_dim=hidden_dim
                ))
                self.norms.append(nn.LayerNorm(hidden_dim))
            
            elif self.model_type == "hybrid":
                self.layers.append(HybridGPSLayer(
                    hidden_dim, num_relations,
                    heads=heads, dropout=dropout
                ))
            
            else:
                raise ValueError(f"Unknown model type: {model_type}")
        
        self.dropout = nn.Dropout(dropout)
        
        # Readout - NEW: flexible pooling options
        if self.readout_type == "devign":
            self.readout = DevignConvHead(hidden_dim, dropout)
            classifier_in_dim = hidden_dim
        elif self.readout_type == "mean_max":
            self.readout = None  # Will use global pooling
            classifier_in_dim = hidden_dim * 2  # concat of mean and max
        else:  # "mean" or "max"
            self.readout = None
            classifier_in_dim = hidden_dim
        
        # Classifier - SIMPLE: single linear layer (matches diagnostic that works)
        self.classifier = nn.Linear(classifier_in_dim, 1)
        
        # NOTE: Removed _init_weights() - it was reinitializing GCNConv internal weights!
        # PyTorch Geometric layers have their own proper initialization.
    
    def _init_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                # Use Xavier uniform (default PyTorch) - more stable
                nn.init.xavier_uniform_(module.weight)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
    
    def forward(self, data: Data) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        # Handle missing attributes
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        else:
            edge_type = edge_type.long().clamp(0, self.num_relations - 1)
        
        # Input projection
        h0 = self.input_proj(x)
        h = h0
        
        # Optional pooling
        if self.pool is not None:
            h, edge_index, edge_type, batch, perm, _ = self.pool(
                h, edge_index, edge_attr=edge_type, batch=batch
            )
            h0 = h0[perm]
            if edge_type is None:
                edge_type = torch.zeros(edge_index.size(1), dtype=torch.long, device=x.device)
        
        # Get edge embeddings
        edge_attr = self.edge_embedding(edge_type)
        
        # GNN layers
        for i, layer in enumerate(self.layers):
            h_in = h
            
            if self.model_type == "ggnn":
                h = layer(h, edge_index, edge_type)
            
            elif self.model_type == "gcn":
                h = layer(h, edge_index)
                h = F.relu(h)
                # No residual, no dropout in GCN - matches diagnostic
            
            elif self.model_type == "gat":
                h = layer(h, edge_index, edge_attr=edge_attr)
                h = self.norms[i](h)
                h = F.elu(h)
                h = self.dropout(h)
                h = h + h_in  # Residual
            
            elif self.model_type == "transformer":
                h = layer(h, edge_index, edge_attr=edge_attr)
                h = self.norms[i](h)
                h = F.elu(h)
                h = self.dropout(h)
                h = h + h_in  # Residual
            
            elif self.model_type == "hybrid":
                h = layer(h, edge_index, edge_type, edge_attr)
        
        # Readout - NEW: flexible pooling
        if self.readout_type == "devign":
            graph_emb = self.readout(h_input=h0, h_final=h, batch=batch)
        elif self.readout_type == "mean":
            from torch_geometric.nn import global_mean_pool
            graph_emb = global_mean_pool(h, batch)
        elif self.readout_type == "max":
            from torch_geometric.nn import global_max_pool
            graph_emb = global_max_pool(h, batch)
        elif self.readout_type == "mean_max":
            from torch_geometric.nn import global_mean_pool, global_max_pool
            graph_emb = torch.cat([
                global_mean_pool(h, batch),
                global_max_pool(h, batch)
            ], dim=1)
        else:
            # Fallback to mean
            from torch_geometric.nn import global_mean_pool
            graph_emb = global_mean_pool(h, batch)
        
        # Classification
        logits = self.classifier(graph_emb)
        
        return {"logits": logits}


# =============================================================================
# TRAINING UTILITIES
# =============================================================================

def find_best_threshold(
    probs: np.ndarray,
    targets: np.ndarray,
    metric: str = "f1"
) -> Tuple[float, float]:
    """Find threshold that maximizes the specified metric."""
    best_score = 0.0
    best_thresh = 0.5
    
    thresholds = np.linspace(0.1, 0.9, 50)
    
    for t in thresholds:
        preds = (probs > t).astype(int)
        
        if metric == "f1":
            score = f1_score(targets, preds, zero_division=0)
        elif metric == "balanced":
            prec = precision_score(targets, preds, zero_division=0)
            rec = recall_score(targets, preds, zero_division=0)
            score = 2 * prec * rec / (prec + rec + 1e-8)
        else:
            score = f1_score(targets, preds, zero_division=0)
        
        if score > best_score:
            best_score = score
            best_thresh = t
    
    return best_thresh, best_score


def debug_prediction_distribution(probs: np.ndarray, targets: np.ndarray, epoch: int):
    """Print diagnostic information about model predictions."""
    probs = np.array(probs)
    targets = np.array(targets)
    
    safe_preds = probs[targets == 0]
    vuln_preds = probs[targets == 1]
    
    print("\n" + "=" * 70)
    print(f"📊 EPOCH {epoch} - PREDICTION DISTRIBUTION ANALYSIS")
    print("=" * 70)
    
    if len(safe_preds) > 0:
        print(f"SAFE graphs (n={len(safe_preds)}):")
        print(f"  Range: [{safe_preds.min():.4f}, {safe_preds.max():.4f}]")
        print(f"  Mean:  {safe_preds.mean():.4f} ± {safe_preds.std():.4f}")
    
    if len(vuln_preds) > 0:
        print(f"VULN graphs (n={len(vuln_preds)}):")
        print(f"  Range: [{vuln_preds.min():.4f}, {vuln_preds.max():.4f}]")
        print(f"  Mean:  {vuln_preds.mean():.4f} ± {vuln_preds.std():.4f}")
    
    # Distribution buckets
    print(f"\nDistribution by probability bucket:")
    print(f"  {'Range':<12} | {'Safe':<15} | {'Vuln':<15} | {'Separation'}")
    print("-" * 60)
    
    buckets = [(0.0, 0.3), (0.3, 0.5), (0.5, 0.7), (0.7, 1.0)]
    for low, high in buckets:
        n_safe = ((safe_preds >= low) & (safe_preds < high)).sum() if len(safe_preds) > 0 else 0
        n_vuln = ((vuln_preds >= low) & (vuln_preds < high)).sum() if len(vuln_preds) > 0 else 0
        pct_safe = 100 * n_safe / max(len(safe_preds), 1)
        pct_vuln = 100 * n_vuln / max(len(vuln_preds), 1)
        
        # Separation indicator
        if low >= 0.5:
            sep = "✓" if pct_vuln > pct_safe else "✗"
        else:
            sep = "✓" if pct_safe > pct_vuln else "✗"
        
        print(f"  {low:.1f}-{high:.1f}      | {n_safe:5d} ({pct_safe:5.1f}%) | {n_vuln:5d} ({pct_vuln:5.1f}%) | {sep}")
    
    # Collapse detection
    overall_std = probs.std()
    if overall_std < 0.1:
        print(f"\n⚠️  WARNING: Low prediction variance ({overall_std:.4f}) - possible model collapse!")
    
    print("=" * 70 + "\n")


class BatchStatistics:
    """Track and report batch statistics."""
    
    def __init__(self):
        self.node_counts = []
        self.edge_counts = []
    
    def update(self, nodes: int, edges: int):
        self.node_counts.append(nodes)
        self.edge_counts.append(edges)
    
    def report(self):
        if not self.node_counts:
            return
        
        nodes = np.array(self.node_counts)
        edges = np.array(self.edge_counts)
        
        print(f"\n[Batch Stats] Nodes: {nodes.mean():.0f} ± {nodes.std():.0f} "
              f"(min={nodes.min()}, max={nodes.max()})")
        print(f"[Batch Stats] Edges: {edges.mean():.0f} ± {edges.std():.0f} "
              f"(min={edges.min()}, max={edges.max()})")
        print(f"[Batch Stats] Avg edges/node: {edges.sum() / nodes.sum():.2f}")
    
    def reset(self):
        self.node_counts = []
        self.edge_counts = []


# =============================================================================
# TRAINING LOOP
# =============================================================================

def train_epoch(
    model: nn.Module,
    loader: DataLoader,
    optimizer: torch.optim.Optimizer,
    device: torch.device,
    pos_weight: Optional[float] = None,
    accumulation_steps: int = 1,
    max_grad_norm: float = 1.0,
    batch_stats: Optional[BatchStatistics] = None,
    criterion: Optional[nn.Module] = None,
    grad_monitor: Optional[Any] = None,
) -> Tuple[float, float, Dict[str, float]]:
    """
    Train for one epoch with anti-collapse support.
    
    Args:
        model: The model to train
        loader: Training data loader
        optimizer: Optimizer
        device: Device to train on
        pos_weight: Class weight for positive examples
        accumulation_steps: Gradient accumulation steps
        max_grad_norm: Max gradient norm for clipping
        batch_stats: Optional batch statistics tracker
        criterion: Loss function (uses BCE if None)
        grad_monitor: Optional gradient monitor
    
    Returns:
        Tuple of (average loss, average batch size, loss components dict)
    """
    model.train()
    loss_meter = AverageMeter()
    loss_components = defaultdict(float)
    component_counts = 0
    
    # Default criterion
    if criterion is None:
        if pos_weight is not None:
            weight_tensor = torch.tensor([pos_weight], device=device)
            criterion = nn.BCEWithLogitsLoss(pos_weight=weight_tensor)
        else:
            criterion = nn.BCEWithLogitsLoss()
    
    # Check if criterion returns components
    use_anti_collapse = hasattr(criterion, 'variance_weight')
    
    optimizer.zero_grad()
    accumulated_loss = 0.0
    accumulated_steps = 0
    
    pbar = tqdm(loader, desc="Training", unit="batch", leave=False)
    
    for batch_idx, batch in enumerate(pbar):
        batch = batch.to(device)
        
        # Track statistics
        if batch_stats is not None:
            batch_stats.update(batch.x.size(0), batch.edge_index.size(1))
        
        # Forward pass
        try:
            out = model(batch)
            logits = out["logits"].view(-1)
            y = batch.y.float().view(-1)
            
            # Handle shape mismatch
            if logits.shape != y.shape:
                min_len = min(logits.shape[0], y.shape[0])
                logits = logits[:min_len]
                y = y[:min_len]
            
            # Compute loss
            if use_anti_collapse:
                loss, components = criterion(logits, y)
                for k, v in components.items():
                    loss_components[k] += v
                component_counts += 1
            else:
                loss = criterion(logits, y)
            
            # Scale loss for accumulation
            if accumulation_steps > 1:
                loss = loss / accumulation_steps
            
            loss.backward()
            accumulated_loss += loss.item()
            accumulated_steps += 1
            
        except RuntimeError as e:
            if "out of memory" in str(e):
                warnings.warn(f"OOM on batch {batch_idx}, skipping...")
                torch.cuda.empty_cache()
                continue
            raise
        
        # Gradient step
        if accumulated_steps >= accumulation_steps or batch_idx == len(loader) - 1:
            # Monitor gradients before clipping (warn only once per epoch)
            if grad_monitor is not None and hasattr(grad_monitor, 'should_warn'):
                if grad_monitor.should_warn():
                    warnings.warn("Vanishing gradients detected in >50% of parameters!")
            elif grad_monitor is not None:
                grad_stats = grad_monitor.get_gradient_stats()
                if grad_stats.get('min_grad', 1) < 1e-8:
                    warnings.warn("Vanishing gradients detected!")
            
            torch.nn.utils.clip_grad_norm_(model.parameters(), max_grad_norm)
            optimizer.step()
            optimizer.zero_grad()
            
            # Log actual loss (unscaled)
            actual_loss = accumulated_loss * accumulation_steps / max(accumulated_steps, 1)
            loss_meter.update(actual_loss)
            
            accumulated_loss = 0.0
            accumulated_steps = 0
        
        pbar.set_postfix({
            "loss": f"{loss_meter.avg:.4f}",
            "nodes": batch.x.size(0),
        })
    
    # Average loss components
    avg_components = {}
    if component_counts > 0:
        for k, v in loss_components.items():
            avg_components[k] = v / component_counts
    
    return loss_meter.avg, np.mean(batch_stats.node_counts) if batch_stats else 0, avg_components


@torch.no_grad()
def evaluate(
    model: nn.Module,
    loader: DataLoader,
    device: torch.device,
    threshold: float = 0.5,
) -> Tuple[Dict[str, float], np.ndarray, np.ndarray, float]:
    """
    Evaluate model on a dataset.
    
    Returns:
        Tuple of (metrics dict, predictions, targets, avg loss)
    """
    model.eval()
    
    all_probs = []
    all_targets = []
    total_loss = 0.0
    criterion = nn.BCEWithLogitsLoss()
    
    for batch in tqdm(loader, desc="Evaluating", leave=False):
        batch = batch.to(device)
        
        out = model(batch)
        logits = out["logits"].view(-1)
        y = batch.y.view(-1)
        
        # Handle shape mismatch
        if logits.shape != y.shape:
            min_len = min(logits.shape[0], y.shape[0])
            logits = logits[:min_len]
            y = y[:min_len]
        
        loss = criterion(logits, y.float())
        total_loss += loss.item()
        
        probs = torch.sigmoid(logits)
        all_probs.append(probs.cpu().numpy())
        all_targets.append(y.cpu().numpy())
    
    if not all_probs:
        return {"acc": 0.0, "f1": 0.0}, np.array([]), np.array([]), 0.0
    
    probs = np.concatenate(all_probs)
    targets = np.concatenate(all_targets)
    
    # Compute metrics
    preds = (probs > threshold).astype(int)
    acc = (preds == targets).mean()
    
    metrics = {"acc": acc, "threshold": threshold}
    
    if _HAS_SKLEARN:
        metrics["f1"] = f1_score(targets, preds, zero_division=0)
        metrics["precision"] = precision_score(targets, preds, zero_division=0)
        metrics["recall"] = recall_score(targets, preds, zero_division=0)
        
        try:
            if len(np.unique(targets)) > 1:
                metrics["auc"] = roc_auc_score(targets, probs)
                metrics["pr_auc"] = average_precision_score(targets, probs)
            else:
                metrics["auc"] = 0.5
                metrics["pr_auc"] = 0.5
        except Exception:
            metrics["auc"] = 0.0
            metrics["pr_auc"] = 0.0
    
    avg_loss = total_loss / len(loader)
    
    return metrics, probs, targets, avg_loss


# =============================================================================
# MAIN
# =============================================================================

def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Devign Baseline: GNN-based Vulnerability Detection",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    
    # Data paths
    data_group = parser.add_argument_group("Data Configuration")
    data_group.add_argument("--cache-dir", type=str, required=True,
                           help="Root directory for cached graph data")
    data_group.add_argument("--dataset-name", type=str, required=True,
                           help="Name of the dataset")
    data_group.add_argument("--cache-signature", type=str, required=True,
                           help="Cache signature/version")
    data_group.add_argument("--vocab-dir", type=str, required=True,
                           help="Directory containing vocabulary files")
    data_group.add_argument("--train-manifest", type=str, required=True,
                           help="Path to training manifest CSV")
    data_group.add_argument("--val-manifest", type=str, required=True,
                           help="Path to validation manifest CSV")
    data_group.add_argument("--test-manifest", type=str, required=True,
                           help="Path to test manifest CSV")
    
    # Data processing
    data_group.add_argument("--collapse-policy", type=str, default="all",
                           choices=["all", "orig", "snap"],
                           help="Policy for handling augmented graphs")
    data_group.add_argument("--max-nodes", type=int, default=None,
                           help="Maximum nodes per graph (truncate larger)")
    data_group.add_argument("--max-edges", type=int, default=None,
                           help="Maximum edges per graph")
    
    # Model architecture
    model_group = parser.add_argument_group("Model Architecture")
    model_group.add_argument("--model-type", type=str, default="ggnn",
                            choices=["ggnn", "gcn", "gat", "transformer", "hybrid",
                                    "rgat", "multiview", "hyper", "hgt"],
                            help="GNN backbone type")
    model_group.add_argument("--hidden-dim", type=int, default=256,
                            help="Hidden dimension size")
    model_group.add_argument("--layers", type=int, default=4,
                            help="Number of GNN layers")
    model_group.add_argument("--heads", type=int, default=4,
                            help="Number of attention heads")
    model_group.add_argument("--dropout", type=float, default=0.3,
                            help="Dropout rate")
    model_group.add_argument("--use-pooling", action="store_true",
                            help="Use SAGPooling")
    model_group.add_argument("--pooling-ratio", type=float, default=0.5,
                            help="Ratio for SAGPooling")
    model_group.add_argument("--readout-type", type=str, default="devign",
                            choices=["devign", "mean", "max", "mean_max"],
                            help="Graph readout method: devign (1D conv), mean, max, or mean_max")
    
    # Training
    train_group = parser.add_argument_group("Training Configuration")
    train_group.add_argument("--epochs", type=int, default=100,
                            help="Number of training epochs")
    train_group.add_argument("--batch-size", type=int, default=32,
                            help="Batch size")
    train_group.add_argument("--lr", type=float, default=5e-4,
                            help="Learning rate")
    train_group.add_argument("--weight-decay", type=float, default=1e-5,
                            help="Weight decay")
    train_group.add_argument("--accumulation-steps", type=int, default=1,
                            help="Gradient accumulation steps")
    train_group.add_argument("--max-grad-norm", type=float, default=1.0,
                            help="Maximum gradient norm for clipping")
    train_group.add_argument("--patience", type=int, default=15,
                            help="Early stopping patience")
    train_group.add_argument("--use-bucket-sampling", action="store_true",
                            help="Use size-bucket batch sampling")
    train_group.add_argument("--use-checkpoint", action="store_true",
                            help="Use gradient checkpointing")
    
    # Anti-collapse settings
    collapse_group = parser.add_argument_group("Anti-Collapse Settings")
    collapse_group.add_argument("--use-focal-loss", action="store_true",
                               help="Use focal loss instead of BCE")
    collapse_group.add_argument("--focal-gamma", type=float, default=2.0,
                               help="Focal loss gamma (focusing parameter)")
    collapse_group.add_argument("--focal-alpha", type=float, default=0.5,
                               help="Focal loss alpha (class balance)")
    collapse_group.add_argument("--variance-weight", type=float, default=0.0,
                               help="Weight for variance regularizer (0 to disable)")
    collapse_group.add_argument("--min-variance", type=float, default=0.05,
                               help="Target minimum prediction variance")
    collapse_group.add_argument("--separation-weight", type=float, default=0.0,
                               help="Weight for class separation loss (0 to disable)")
    collapse_group.add_argument("--separation-margin", type=float, default=0.2,
                               help="Target separation between class means")
    collapse_group.add_argument("--label-smoothing", type=float, default=0.0,
                               help="Label smoothing factor (0 to disable)")
    collapse_group.add_argument("--warmup-epochs", type=int, default=0,
                               help="Number of warmup epochs (0 to disable)")
    collapse_group.add_argument("--monitor-gradients", action="store_true",
                               help="Monitor gradient flow")
    
    # Misc
    misc_group = parser.add_argument_group("Miscellaneous")
    misc_group.add_argument("--seed", type=int, default=42,
                           help="Random seed")
    misc_group.add_argument("--num-workers", type=int, default=4,
                           help="DataLoader workers")
    misc_group.add_argument("--output-dir", type=str, default="results",
                           help="Output directory")
    misc_group.add_argument("--debug-interval", type=int, default=5,
                           help="Epochs between debug outputs")
    misc_group.add_argument("--no-cuda", action="store_true",
                           help="Disable CUDA")
    
    return parser


def make_split_dir(cache_dir: str, dataset_name: str, cache_sig: str, split: str) -> Path:
    """Construct path to split directory."""
    return Path(cache_dir) / dataset_name / split / cache_sig


def create_model(
    args: argparse.Namespace,
    input_dim: int,
    num_relations: int,
    device: torch.device,
) -> nn.Module:
    """Create model based on arguments."""
    
    common_kwargs = {
        "in_dim": input_dim,
        "hidden_dim": args.hidden_dim,
        "num_relations": num_relations,
        "num_layers": args.layers,
        "dropout": args.dropout,
        "heads": args.heads,
    }
    
    if args.model_type == "rgat":
        if not _HAS_RGAT:
            raise ImportError("rgat_models.py required for --model-type rgat")
        model = RGATDevignModel(
            **common_kwargs,
            use_checkpoint=args.use_checkpoint,
        )
    
    elif args.model_type == "multiview":
        if not _HAS_MULTIVIEW:
            raise ImportError("multiview_models.py required for --model-type multiview")
        model = MultiViewGGNN(
            in_dim=input_dim,
            hidden_dim=args.hidden_dim,
            num_layers=args.layers,
            dropout=args.dropout,
        )
    
    elif args.model_type == "hyper":
        if not _HAS_HYPER:
            raise ImportError("hypergraph_models.py required for --model-type hyper")
        model = HyperDevignModel(**common_kwargs)
    
    elif args.model_type == "hgt":
        if not _HAS_HGT:
            raise ImportError("hgt_models.py required for --model-type hgt")
        model = HGTDevignModel(**common_kwargs)
    
    else:
        model = DevignModel(
            **common_kwargs,
            model_type=args.model_type,
            use_pooling=args.use_pooling,
            pooling_ratio=args.pooling_ratio,
            readout_type=args.readout_type,  # NEW
        )
    
    return model.to(device)


def run(args: argparse.Namespace):
    """Main training loop."""
    
    # Setup
    set_seed(args.seed)
    device = get_device(prefer_cuda=not args.no_cuda)
    
    print("\n" + "=" * 70)
    print("DEVIGN BASELINE - GNN VULNERABILITY DETECTION")
    print("=" * 70)
    print(f"Model: {args.model_type.upper()} | Layers: {args.layers} | "
          f"Hidden: {args.hidden_dim} | Heads: {args.heads}")
    print(f"Readout: {args.readout_type.upper()}")  # NEW
    print("=" * 70 + "\n")
    
    # Setup directories
    train_dir = make_split_dir(args.cache_dir, args.dataset_name, args.cache_signature, "train")
    val_dir = make_split_dir(args.cache_dir, args.dataset_name, args.cache_signature, "valid")
    test_dir = make_split_dir(args.cache_dir, args.dataset_name, args.cache_signature, "test")
    
    # Load metadata
    sig_path = train_dir / "meta" / "signature.json"
    if not sig_path.exists():
        raise FileNotFoundError(f"Signature file not found: {sig_path}")
    
    with sig_path.open("r") as f:
        sig = json.load(f)
    input_dim = sig["features"]["final_x_dim"]
    print(f"[Config] Input dimension: {input_dim}")
    
    num_relations = load_vocab(Path(args.vocab_dir))
    
    # Create datasets
    print("\n[Loading Datasets]")
    train_ds = CachedDataset(
        train_dir, args.train_manifest,
        max_nodes=args.max_nodes, max_edges=args.max_edges,
    )
    val_ds = CachedDataset(
        val_dir, args.val_manifest,
        max_nodes=args.max_nodes, max_edges=args.max_edges,
        precompute_sizes=False,
    )
    test_ds = CachedDataset(
        test_dir, args.test_manifest,
        max_nodes=args.max_nodes, max_edges=args.max_edges,
        precompute_sizes=False,
    )
    
    # Apply collapse policy
    train_ds = apply_collapse_policy(train_ds, args.collapse_policy)
    val_ds = apply_collapse_policy(val_ds, args.collapse_policy)
    test_ds = apply_collapse_policy(test_ds, args.collapse_policy)
    
    # Calculate class weights
    pos_weight = train_ds.calculate_pos_weight()
    
    # Create data loaders
    if args.use_bucket_sampling:
        print("[DataLoader] Using size-bucket batch sampling")
        train_sampler = SizeBucketBatchSampler(
            train_ds, batch_size=args.batch_size, shuffle=True,
        )
        train_loader = DataLoader(
            train_ds,
            batch_sampler=train_sampler,
            num_workers=args.num_workers,
        )
    else:
        train_loader = DataLoader(
            train_ds,
            batch_size=args.batch_size,
            shuffle=True,
            num_workers=args.num_workers,
            drop_last=False,
        )
    
    val_loader = DataLoader(
        val_ds,
        batch_size=args.batch_size,
        shuffle=False,
        num_workers=args.num_workers,
    )
    test_loader = DataLoader(
        test_ds,
        batch_size=args.batch_size,
        shuffle=False,
        num_workers=args.num_workers,
    )
    
    print(f"\n[Data] Train: {len(train_ds)} | Val: {len(val_ds)} | Test: {len(test_ds)}")
    
    # Create model
    model = create_model(args, input_dim, num_relations, device)
    
    num_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
    print(f"[Model] Parameters: {num_params:,}")
    
    # Optimizer and scheduler
    optimizer = torch.optim.AdamW(
        model.parameters(),
        lr=args.lr,
        weight_decay=args.weight_decay,
    )
    
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(
        optimizer,
        mode='max',  # Maximize F1
        factor=0.5,
        patience=5,
        min_lr=1e-6,
    )
    
    # Setup anti-collapse loss
    criterion = None
    grad_monitor = None
    warmup_scheduler = None
    
    if _HAS_ANTI_COLLAPSE and (args.use_focal_loss or args.variance_weight > 0):
        print("\n[Loss] Using AntiCollapseLoss with:")
        print(f"  - Focal Loss: gamma={args.focal_gamma}, alpha={args.focal_alpha}")
        print(f"  - Variance regularizer: weight={args.variance_weight}, min={args.min_variance}")
        print(f"  - Separation loss: weight={args.separation_weight}, margin={args.separation_margin}")
        
        criterion = AntiCollapseLoss(
            pos_weight=pos_weight,
            focal_gamma=args.focal_gamma if args.use_focal_loss else 0,
            focal_alpha=args.focal_alpha,
            variance_weight=args.variance_weight,
            min_variance=args.min_variance,
            separation_weight=args.separation_weight,
            separation_margin=args.separation_margin,
            label_smoothing=args.label_smoothing,
        )
        
        if args.monitor_gradients:
            grad_monitor = GradientMonitor(model)
            print("  - Gradient monitoring: ENABLED")
        
        if args.warmup_epochs > 0:
            warmup_scheduler = WarmupCosineScheduler(
                optimizer,
                warmup_epochs=args.warmup_epochs,
                total_epochs=args.epochs,
            )
            print(f"  - Warmup: {args.warmup_epochs} epochs")
    elif not _HAS_ANTI_COLLAPSE and args.use_focal_loss:
        warnings.warn("anti_collapse.py not found. Using standard BCE loss.")
    
    # Output directory
    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    
    # Save config
    with (out_dir / "config.json").open("w") as f:
        json.dump(vars(args), f, indent=2, default=str)
    
    # Training state
    best_f1 = 0.0
    best_threshold = 0.5
    best_epoch = 0
    epochs_without_improvement = 0
    
    batch_stats = BatchStatistics()
    history = defaultdict(list)
    
    print("\n" + "=" * 70)
    print("TRAINING")
    print("=" * 70 + "\n")
    
    for epoch in range(1, args.epochs + 1):
        batch_stats.reset()
        
        # Reset gradient monitor warning flag
        if grad_monitor is not None and hasattr(grad_monitor, 'reset_warning'):
            grad_monitor.reset_warning()
        
        # Update warmup scheduler if present
        if warmup_scheduler is not None:
            warmup_scheduler.step(epoch - 1)
        
        # Train
        train_loss, avg_nodes, loss_components = train_epoch(
            model, train_loader, optimizer, device,
            pos_weight=pos_weight,
            accumulation_steps=args.accumulation_steps,
            max_grad_norm=args.max_grad_norm,
            batch_stats=batch_stats,
            criterion=criterion,
            grad_monitor=grad_monitor,
        )
        
        # Validate
        val_metrics, val_probs, val_targets, val_loss = evaluate(
            model, val_loader, device, threshold=0.5
        )
        
        # Find optimal threshold
        if _HAS_SKLEARN and len(val_targets) > 0:
            opt_thresh, opt_f1 = find_best_threshold(val_probs, val_targets)
            val_metrics["f1_opt"] = opt_f1
            val_metrics["threshold_opt"] = opt_thresh
        else:
            opt_thresh = 0.5
            opt_f1 = val_metrics.get("f1", 0.0)
        
        # Update scheduler (only after warmup)
        if warmup_scheduler is None or epoch > args.warmup_epochs:
            scheduler.step(opt_f1)
        current_lr = optimizer.param_groups[0]['lr']
        
        # Log history
        history["epoch"].append(epoch)
        history["train_loss"].append(train_loss)
        history["val_loss"].append(val_loss)
        history["val_f1"].append(opt_f1)
        history["val_auc"].append(val_metrics.get("auc", 0.0))
        history["lr"].append(current_lr)
        
        # Print progress with loss components if available
        loss_info = f"Loss: {train_loss:.4f} / {val_loss:.4f}"
        if loss_components:
            loss_info += f" [P:{loss_components.get('primary', 0):.3f} V:{loss_components.get('variance', 0):.3f} S:{loss_components.get('separation', 0):.3f}]"
        
        print(
            f"Epoch {epoch:03d} | "
            f"{loss_info} | "
            f"F1: {opt_f1:.4f} (T={opt_thresh:.2f}) | "
            f"AUC: {val_metrics.get('auc', 0):.4f} | "
            f"LR: {current_lr:.1e}"
        )
        
        # Debug diagnostics
        if epoch % args.debug_interval == 0:
            debug_prediction_distribution(val_probs, val_targets, epoch)
            batch_stats.report()
            
            # Additional collapse diagnosis
            if _HAS_ANTI_COLLAPSE:
                collapse_metrics = compute_collapse_metrics(
                    torch.tensor(val_probs), torch.tensor(val_targets)
                )
                if collapse_metrics['collapse_score'] > 0.7:
                    print("\n" + diagnose_collapse(
                        torch.tensor(val_probs), torch.tensor(val_targets)
                    ))
        
        # Save best model
        if opt_f1 > best_f1:
            best_f1 = opt_f1
            best_threshold = opt_thresh
            best_epoch = epoch
            epochs_without_improvement = 0
            
            torch.save(model.state_dict(), out_dir / "best_model.pt")
            with (out_dir / "best_threshold.txt").open("w") as f:
                f.write(f"{best_threshold:.4f}")
            
            print(f"  → New best! F1={best_f1:.4f} @ threshold={best_threshold:.2f}")
        else:
            epochs_without_improvement += 1
        
        # Early stopping
        if epochs_without_improvement >= args.patience:
            print(f"\n[Early Stopping] No improvement for {args.patience} epochs")
            break
    
    # Save training history
    with (out_dir / "history.json").open("w") as f:
        json.dump(history, f, indent=2)
    
    # Final evaluation
    print("\n" + "=" * 70)
    print("FINAL EVALUATION")
    print("=" * 70 + "\n")
    
    # Load best model
    if (out_dir / "best_model.pt").exists():
        model.load_state_dict(torch.load(out_dir / "best_model.pt", map_location=device))
        print(f"[Loaded] Best model from epoch {best_epoch}")
    
    # Evaluate on test set
    test_metrics, test_probs, test_targets, test_loss = evaluate(
        model, test_loader, device, threshold=best_threshold
    )
    
    print(f"\nTest Results (threshold={best_threshold:.2f}):")
    print(f"  Accuracy:  {test_metrics['acc']:.4f}")
    print(f"  F1 Score:  {test_metrics.get('f1', 0):.4f}")
    print(f"  Precision: {test_metrics.get('precision', 0):.4f}")
    print(f"  Recall:    {test_metrics.get('recall', 0):.4f}")
    print(f"  ROC-AUC:   {test_metrics.get('auc', 0):.4f}")
    print(f"  PR-AUC:    {test_metrics.get('pr_auc', 0):.4f}")
    
    # Debug diagnostics on test set
    debug_prediction_distribution(test_probs, test_targets, epoch=-1)
    
    # Save test results
    test_metrics["best_epoch"] = best_epoch
    test_metrics["best_threshold"] = best_threshold
    
    with (out_dir / "test_results.json").open("w") as f:
        json.dump(test_metrics, f, indent=2)
    
    # Save curves if sklearn available
    if _HAS_SKLEARN and len(test_probs) > 0:
        fpr, tpr, _ = roc_curve(test_targets, test_probs)
        prec, rec, _ = precision_recall_curve(test_targets, test_probs)
        
        with (out_dir / "test_curves.json").open("w") as f:
            json.dump({
                "roc": {"fpr": fpr.tolist(), "tpr": tpr.tolist()},
                "pr": {"precision": prec.tolist(), "recall": rec.tolist()},
            }, f)
    
    print(f"\n[Done] Results saved to: {out_dir}")
    print("=" * 70 + "\n")
    
    return test_metrics


if __name__ == "__main__":
    args = build_parser().parse_args()
    run(args)

"""
python Devign_baseline.py \
  --model-type gcn \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --hidden-dim 256 \
  --layers 3 \
  --lr 1e-2 \
  --batch-size 32 \
  --epochs 100 \
  --dropout 0.2 \
  --weight-decay 1e-5 \
  --debug-interval 5 \
  --variance-weight 0 \
  --separation-weight 0 \
  --warmup-epochs 0 \
  --readout-type mean \
  \
  --output-dir "devign_baseline_GCN_results" \
  --num-workers 4

######################################






## GNN type ---- GAT ###############
python Devign_baseline.py \
  --model-type gat --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --hidden-dim 256 \
  --layers 2 \
  --lr 2e-4 \
  --batch-size 128 \
  --epochs 100 \
  --dropout 0.4 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  \
  --output-dir "devign_baseline_GAT_results" \
  --num-workers 4



######################################

### GNN type ---- GGNN ###############

python Devign_baseline.py \
  --model-type ggnn \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --ccaffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --hidden-dim 256 \
  --layers 2 \
  --lr 2e-4 \
  --batch-size 128 \
  --epochs 100 \
  --dropout 0.4 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  \
  --output-dir "devign_baseline_GGNN_results" \
  --num-workers 4


#######################################



### GNN type ---- Transformer ###############

python Devign_baseline.py \
  --model-type transformer --heads 4 \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "2913d0ac45337fed" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --hidden-dim 256 \
  --layers 2 \
  --lr 2e-4 \
  --batch-size 32 \
  --epochs 100 \
  --dropout 0.4 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  \
  --output-dir "devign_baseline_Transformer_results" \
  --num-workers 4



python Devign_baseline.py \
  --model-type hybrid \
  --heads 6 \
  --hidden-dim 256 \
  --layers 2 \
  --lr 5e-4 \
  --batch-size 16 \
  --max-nodes 1000 \
  --max-edges 5000 \
  --use-bucket-sampling \
  --epochs 200 \
  --dropout 0.3 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --output-dir "devign_baseline_hybrid_256" \
  --num-workers 4


python Devign_baseline.py \
  --model-type hyper \
  --heads 64 \
  --hidden-dim 128 \
  --layers 2 \
  --lr 5e-4 \
  --batch-size 32 \
  --max-nodes 1000 \
  --max-edges 5000 \
  --use-bucket-sampling \
  --epochs 100 \
  --dropout 0.3 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --output-dir "devign_baseline_HYPERGRAPH_results" \
  --num-workers 4




  python Devign_baseline.py \
  --model-type multiview \
  --hidden-dim 256 \
  --layers 2 \
  --lr 5e-4 \
  --batch-size 32 \
  --max-nodes 1000 \
  --max-edges 5000 \
  --use-bucket-sampling \
  --epochs 100 \
  --dropout 0.3 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --output-dir "devign_baseline_MULTIVIEW_results" \
  --num-workers 4


python Devign_baseline.py \
  --model-type hgt \
  --heads 16 \
  --hidden-dim 128 \
  --layers 2 \
  --lr 5e-4 \
  --batch-size 32 \
  --max-nodes 1000 \
  --max-edges 5000 \
  --use-bucket-sampling \
  --patience 20 \
  --batch-size 16 \
  --epochs 100 \
  --dropout 0.3 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.2 \
  --min-variance 0.08 \
  --separation-weight 0.2 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --output-dir "devign_baseline_HGT_results" \
  --num-workers 4


python Devign_baseline.py \
  --model-type rgat \
  --heads 4 \
  --hidden-dim 256\
  --layers 3 \
  --lr 1e-3 \
  --max-nodes 500 \
  --max-edges 3000 \
  --use-bucket-sampling \
  --batch-size 16 \
  --epochs 100 \
  --dropout 0.3 \
  --weight-decay 1e-5 \
  \
  --use-focal-loss \
  --focal-gamma 2.0 \
  --focal-alpha 0.5 \
  --variance-weight 0.15 \
  --min-variance 0.08 \
  --separation-weight 0.15 \
  --separation-margin 0.25 \
  --warmup-epochs 5 \
  --monitor-gradients \
  --cache-dir "./Clean_exports/cache_devign_v2" \
  --dataset-name "devign_normfunc_v2" \
  --cache-signature "caffd6ae8652870d" \
  --vocab-dir "./Clean_exports/devign_vocab_normfunc_v2" \
  \
  --train-manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --val-manifest   "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_validation.csv" \
  --test-manifest  "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_test.csv" \
  \
  --output-dir "devign_baseline_RGAT_results" \
  --num-workers 4

"""