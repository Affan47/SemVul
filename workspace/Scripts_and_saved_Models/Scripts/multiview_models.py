#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
multiview_models.py - Multi-View Graph Neural Network for Vulnerability Detection

This model processes Code Property Graphs by separating them into semantic views:
  - AST View: Abstract Syntax Tree structure
  - CFG View: Control Flow Graph (including NCS edges)
  - DFG View: Data Flow Graph (REACHES/READ/WRITE edges)

Each view is processed by a dedicated GGNN encoder, then fused using
node-conditioned attention to produce the final representation.

Key Features:
  - Configurable edge type mappings (not hardcoded)
  - Node-conditioned attention fusion (each node learns its own view weights)
  - Proper residual connections in view encoders
  - Empty view handling with graceful fallback
  - Sorted edge indices for GGNN efficiency

Reference:
  Multi-view learning for software vulnerability detection (inspired by)
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import GatedGraphConv
from torch_geometric.utils import to_dense_batch, sort_edge_index
from typing import Dict, List, Optional, Tuple
import warnings


class DevignConvHead(nn.Module):
    """
    Devign's Hierarchical Conv Readout Module.
    Compares initial and final node representations through conv layers.
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
        
        self.bn_z = nn.BatchNorm1d(hidden_dim)
        self.bn_y = nn.BatchNorm1d(hidden_dim)
    
    def forward(
        self,
        h_input: torch.Tensor,
        h_final: torch.Tensor,
        batch: torch.Tensor,
    ) -> torch.Tensor:
        h_cat = torch.cat([h_input, h_final], dim=1)
        
        z_dense, mask = to_dense_batch(h_cat, batch)
        y_dense, _ = to_dense_batch(h_final, batch)
        
        z = z_dense.transpose(1, 2)
        y = y_dense.transpose(1, 2)
        
        # Handle small graphs
        min_size = 4
        if z.size(2) < min_size:
            pad_size = min_size - z.size(2)
            z = F.pad(z, (0, pad_size))
            y = F.pad(y, (0, pad_size))
            mask_float = F.pad(mask.unsqueeze(1).float(), (0, pad_size))
        else:
            mask_float = mask.unsqueeze(1).float()
        
        # Layer 1
        z = self.pool(F.relu(self.conv1_z(z)))
        y = self.pool(F.relu(self.conv1_y(y)))
        mask_pooled = F.max_pool1d(mask_float, kernel_size=2, stride=2)
        
        # Layer 2
        z = self.pool(F.relu(self.conv2_z(z)))
        y = self.pool(F.relu(self.conv2_y(y)))
        mask_pooled = F.max_pool1d(mask_pooled, kernel_size=2, stride=2)
        
        # Batch norm
        z = self.bn_z(z)
        y = self.bn_y(y)
        z = self.dropout(z)
        y = self.dropout(y)
        
        # MLP
        z_prime = self.mlp_z(z)
        y_prime = self.mlp_y(y)
        
        # Interaction
        h_mult = z_prime * y_prime
        
        # Masked mean pooling
        mask_bool = (mask_pooled > 0.5)
        h_mult = h_mult * mask_bool.float()
        sum_h = torch.sum(h_mult, dim=2)
        counts = torch.sum(mask_bool.float(), dim=2).clamp(min=1.0)
        
        return sum_h / counts


class ViewEncoder(nn.Module):
    """
    Processes a single graph view using Gated Graph Neural Network.
    
    Features:
    - GatedGraphConv for recurrent message passing
    - LayerNorm for stability
    - Residual connection from input
    - Handles empty edge indices gracefully
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_layers: int = 4,
        dropout: float = 0.2,
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.dropout_p = dropout
        
        # GatedGraphConv: num_layers = message passing iterations
        self.ggnn = GatedGraphConv(
            out_channels=hidden_dim,
            num_layers=num_layers,
        )
        
        self.norm = nn.LayerNorm(hidden_dim)
        self.dropout = nn.Dropout(dropout)
    
    def forward(self, x: torch.Tensor, edge_index: torch.Tensor) -> torch.Tensor:
        """
        Args:
            x: Node features [N, hidden_dim]
            edge_index: Edge connectivity for this view [2, E_view]
            
        Returns:
            Updated node features [N, hidden_dim]
        """
        # Handle empty view
        if edge_index.size(1) == 0:
            # No edges in this view - return normalized input
            return self.norm(x)
        
        # Sort edge index for GGNN efficiency
        edge_index = sort_edge_index(edge_index)
        
        # GGNN forward
        h = self.ggnn(x, edge_index)
        h = self.norm(h)
        h = self.dropout(h)
        
        # Residual connection
        return h + x


class NodeConditionedAttentionFusion(nn.Module):
    """
    Fuses representations from multiple views using node-conditioned attention.
    
    Unlike simple attention with a shared query vector, this allows each node
    to learn its own attention weights over views based on its features.
    This is important because:
    - Vulnerability-indicating nodes should attend more to DFG
    - Structural nodes should attend more to AST
    - Control flow nodes should attend more to CFG
    
    Args:
        hidden_dim: Dimension of node embeddings
        num_views: Number of views to fuse
    """
    
    def __init__(self, hidden_dim: int, num_views: int = 3):
        super().__init__()
        self.num_views = num_views
        self.hidden_dim = hidden_dim
        
        # Node-conditioned query generation
        self.query_net = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.Tanh(),
        )
        
        # Key projection for views
        self.key_proj = nn.Linear(hidden_dim, hidden_dim)
        
        # Scaling factor
        self.scale = hidden_dim ** -0.5
    
    def forward(
        self,
        view_embeddings: torch.Tensor,
        node_context: torch.Tensor,
    ) -> Tuple[torch.Tensor, torch.Tensor]:
        """
        Args:
            view_embeddings: [N, num_views, hidden_dim] - stacked view outputs
            node_context: [N, hidden_dim] - context for query generation (e.g., h0)
            
        Returns:
            fused: [N, hidden_dim] - fused node representations
            attention: [N, num_views] - attention weights for interpretability
        """
        # Generate node-specific queries
        query = self.query_net(node_context)  # [N, hidden_dim]
        
        # Project view embeddings to keys
        keys = self.key_proj(view_embeddings)  # [N, num_views, hidden_dim]
        
        # Compute attention scores
        # [N, 1, hidden_dim] @ [N, hidden_dim, num_views] -> [N, 1, num_views]
        attn_scores = torch.bmm(query.unsqueeze(1), keys.transpose(1, 2))
        attn_scores = attn_scores.squeeze(1) * self.scale  # [N, num_views]
        
        # Softmax over views
        attention = F.softmax(attn_scores, dim=-1)  # [N, num_views]
        
        # Weighted sum of view embeddings
        # [N, num_views, 1] * [N, num_views, hidden_dim] -> sum -> [N, hidden_dim]
        fused = (view_embeddings * attention.unsqueeze(-1)).sum(dim=1)
        
        return fused, attention


class MultiViewGGNN(nn.Module):
    """
    Multi-View Graph Neural Network for Vulnerability Detection.
    
    Separates the Code Property Graph into semantic views (AST, CFG, DFG),
    processes each with a dedicated encoder, and fuses using attention.
    
    Architecture:
        Input -> Projection -> [View Encoders] -> Attention Fusion -> Readout -> Classifier
    
    Args:
        in_dim: Input feature dimension
        hidden_dim: Hidden dimension for all layers
        num_layers: Number of GGNN iterations per view
        dropout: Dropout rate
        edge_type_config: Dict mapping view names to edge type indices
            Default: {'ast': [0], 'cfg': [1, 4], 'dfg': [2, 3]}
    """
    
    # Default edge type configuration
    DEFAULT_EDGE_CONFIG = {
        'ast': [0],        # AST edges
        'cfg': [1, 4],     # CFG + NCS (Next Control Statement)
        'dfg': [2, 3],     # REACHES + WRITE (data flow)
    }
    
    def __init__(
        self,
        in_dim: int,
        hidden_dim: int,
        num_layers: int = 4,
        dropout: float = 0.2,
        edge_type_config: Optional[Dict[str, List[int]]] = None,
        **kwargs
    ):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_layers = num_layers
        
        # Edge type configuration
        self.edge_type_config = edge_type_config or self.DEFAULT_EDGE_CONFIG
        self.num_views = len(self.edge_type_config)
        
        # Input projection
        self.input_proj = nn.Sequential(
            nn.Linear(in_dim, hidden_dim),
            nn.LayerNorm(hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
        )
        
        # View encoders
        self.view_encoders = nn.ModuleDict()
        for view_name in self.edge_type_config.keys():
            self.view_encoders[view_name] = ViewEncoder(
                hidden_dim=hidden_dim,
                num_layers=num_layers,
                dropout=dropout,
            )
        
        # Attention fusion
        self.fusion = NodeConditionedAttentionFusion(
            hidden_dim=hidden_dim,
            num_views=self.num_views,
        )
        
        # Readout
        self.readout = DevignConvHead(hidden_dim, dropout)
        
        # Classifier
        self.classifier = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.GELU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_dim, 1),
        )
        
        self._init_weights()
    
    def _init_weights(self):
        for module in self.modules():
            if isinstance(module, nn.Linear):
                nn.init.trunc_normal_(module.weight, std=0.02)
                if module.bias is not None:
                    nn.init.zeros_(module.bias)
    
    def _get_view_mask(
        self,
        edge_type: torch.Tensor,
        view_types: List[int],
    ) -> torch.Tensor:
        """Create boolean mask for edges belonging to specified types."""
        mask = torch.zeros_like(edge_type, dtype=torch.bool)
        for t in view_types:
            mask = mask | (edge_type == t)
        return mask
    
    def forward(self, data) -> Dict[str, torch.Tensor]:
        x = data.x.float()
        edge_index = data.edge_index
        batch = data.batch
        edge_type = getattr(data, "edge_type", None)
        
        # Handle missing attributes
        if batch is None:
            batch = x.new_zeros(x.size(0), dtype=torch.long)
        
        if edge_type is None:
            edge_type = torch.zeros(
                edge_index.size(1), dtype=torch.long, device=x.device
            )
        else:
            edge_type = edge_type.long()
        
        # Input projection
        h0 = self.input_proj(x)
        
        # Process each view
        view_outputs = []
        view_edge_counts = {}
        
        for view_name, view_types in self.edge_type_config.items():
            # Get edges for this view
            mask = self._get_view_mask(edge_type, view_types)
            edge_index_view = edge_index[:, mask]
            
            # Track edge count for debugging
            view_edge_counts[view_name] = edge_index_view.size(1)
            
            # Encode view
            h_view = self.view_encoders[view_name](h0, edge_index_view)
            view_outputs.append(h_view)
        
        # Stack views: [N, num_views, hidden_dim]
        h_stacked = torch.stack(view_outputs, dim=1)
        
        # Fuse views using node-conditioned attention
        h_fused, attention_weights = self.fusion(h_stacked, node_context=h0)
        
        # Readout
        graph_emb = self.readout(h_input=h0, h_final=h_fused, batch=batch)
        
        # Classification
        logits = self.classifier(graph_emb)
        
        return {
            "logits": logits,
            "view_attention": attention_weights,
            "view_edge_counts": view_edge_counts,
        }
    
    def get_view_attention_stats(self, attention_weights: torch.Tensor) -> Dict[str, float]:
        """Get mean attention per view for interpretability."""
        view_names = list(self.edge_type_config.keys())
        stats = {}
        
        mean_attn = attention_weights.mean(dim=0)  # [num_views]
        for i, name in enumerate(view_names):
            stats[name] = mean_attn[i].item()
        
        return stats