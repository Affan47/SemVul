#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
layers.py - Shared Neural Network Layers for Vulnerability Detection

This module contains common layers used across multiple model architectures,
eliminating code duplication and ensuring consistency.

Contents:
    - DevignConvHead: Hierarchical conv readout from Devign paper
    - RelGraphConv: Memory-efficient relational graph convolution
    - NodeConditionedAttention: Attention mechanism for view fusion
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import MessagePassing
from torch_geometric.utils import to_dense_batch
from typing import Optional, Tuple


class DevignConvHead(nn.Module):
    """
    Devign's Hierarchical Convolutional Readout Module.
    
    From Section 2.4 of the Devign paper (Zhou et al., 2019), Equations 6-9.
    
    This module compares initial and final node representations through:
    1. Concatenation of h_input and h_final
    2. Parallel 1D convolution paths
    3. Hierarchical max pooling
    4. Element-wise multiplication for feature interaction
    5. Masked mean pooling for graph-level embedding
    
    The comparison between initial and final representations helps capture
    how node features evolve through the GNN, which is informative for
    vulnerability detection.
    
    Args:
        hidden_dim: Dimension of node embeddings
        dropout: Dropout rate (default: 0.1)
        use_batch_norm: Whether to use batch normalization (default: True)
    """
    
    def __init__(
        self,
        hidden_dim: int,
        dropout: float = 0.1,
        use_batch_norm: bool = True,
    ):
        super().__init__()
        self.hidden_dim = int(hidden_dim)
        self.use_batch_norm = use_batch_norm
        
        # Z path: processes concatenated [h_input, h_final]
        self.conv1_z = nn.Conv1d(hidden_dim * 2, hidden_dim, kernel_size=3, padding=1)
        self.conv2_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_z = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        # Y path: processes h_final only
        self.conv1_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=3, padding=1)
        self.conv2_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        self.mlp_y = nn.Conv1d(hidden_dim, hidden_dim, kernel_size=1)
        
        # Pooling
        self.pool = nn.MaxPool1d(kernel_size=2, stride=2)
        
        # Regularization
        self.dropout = nn.Dropout(dropout)
        
        if use_batch_norm:
            self.bn_z = nn.BatchNorm1d(hidden_dim)
            self.bn_y = nn.BatchNorm1d(hidden_dim)
        else:
            self.bn_z = nn.Identity()
            self.bn_y = nn.Identity()
    
    def forward(
        self,
        h_input: torch.Tensor,
        h_final: torch.Tensor,
        batch: torch.Tensor,
    ) -> torch.Tensor:
        """
        Compute graph-level embedding from node representations.
        
        Args:
            h_input: Initial node embeddings [N, hidden_dim]
            h_final: Final node embeddings after GNN [N, hidden_dim]
            batch: Batch assignment vector [N]
            
        Returns:
            Graph-level embeddings [B, hidden_dim]
        """
        # Concatenate initial and final representations
        h_cat = torch.cat([h_input, h_final], dim=1)  # [N, 2*hidden_dim]
        
        # Convert to dense batch format for conv1d
        z_dense, mask = to_dense_batch(h_cat, batch)  # [B, max_N, 2*H]
        y_dense, _ = to_dense_batch(h_final, batch)   # [B, max_N, H]
        
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
        
        # Batch normalization (if enabled)
        z = self.bn_z(z)
        y = self.bn_y(y)
        z = self.dropout(z)
        y = self.dropout(y)
        
        # MLP projection
        z_prime = self.mlp_z(z)
        y_prime = self.mlp_y(y)
        
        # Element-wise multiplication (feature interaction)
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
    
    Processes different edge types (relations) separately to avoid
    materializing large intermediate tensors. This achieves O(N*R*D)
    memory complexity instead of O(E*D*D).
    
    Mathematical formulation:
        h_i' = σ( Σ_r Σ_{j∈N_r(i)} (1/c_{i,r}) W_r h_j + W_0 h_i )
    
    Where:
        - W_r: Relation-specific weight matrix
        - W_0: Self-loop (root) weight matrix
        - c_{i,r}: Normalization constant
    
    Args:
        hidden_dim: Input and output feature dimension
        num_relations: Number of edge types
        dropout: Dropout rate
        num_bases: Number of bases for weight decomposition (optional)
        add_self_loops: Whether to add self-loop transformation
    """
    
    def __init__(
        self,
        hidden_dim: int,
        num_relations: int,
        dropout: float = 0.2,
        num_bases: Optional[int] = None,
        add_self_loops: bool = True,
    ):
        super().__init__(aggr="add")
        self.hidden_dim = hidden_dim
        self.num_relations = num_relations
        self.dropout_p = dropout
        self.add_self_loops = add_self_loops
        
        # Relation-specific weights (with optional basis decomposition)
        if num_bases is not None and num_bases < num_relations:
            self.num_bases = num_bases
            self.basis = nn.Parameter(
                torch.empty(num_bases, hidden_dim, hidden_dim)
            )
            self.coefficients = nn.Parameter(
                torch.empty(num_relations, num_bases)
            )
            self.weight = None
        else:
            self.num_bases = None
            self.weight = nn.Parameter(
                torch.empty(num_relations, hidden_dim, hidden_dim)
            )
            self.basis = None
            self.coefficients = None
        
        # Self-loop transformation
        self.root_weight = nn.Parameter(torch.empty(hidden_dim, hidden_dim))
        self.bias = nn.Parameter(torch.zeros(hidden_dim))
        
        # Normalization and regularization
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
        """Get relation-specific weight matrices."""
        if self.weight is not None:
            return self.weight
        # Basis decomposition: W_r = Σ_b c_{rb} * B_b
        return torch.einsum('rb,bio->rio', self.coefficients, self.basis)
    
    def forward(
        self,
        x: torch.Tensor,
        edge_index: torch.Tensor,
        edge_type: torch.Tensor,
    ) -> torch.Tensor:
        """
        Forward pass.
        
        Args:
            x: Node features [N, hidden_dim]
            edge_index: Edge connectivity [2, E]
            edge_type: Edge type labels [E]
            
        Returns:
            Updated node features [N, hidden_dim]
        """
        x_in = x  # Save for residual
        out = torch.zeros_like(x)
        
        if edge_type is None:
            edge_type = x.new_zeros(edge_index.size(1), dtype=torch.long)
        
        W = self.get_weights()
        
        # Process each relation type separately (memory efficient)
        for r in range(self.num_relations):
            mask = (edge_type == r)
            if not mask.any():
                continue
            
            edge_index_r = edge_index[:, mask]
            h_r = x @ W[r]
            out = out + self.propagate(edge_index_r, x=h_r)
        
        # Self-loop transformation
        if self.add_self_loops:
            out = out + x @ self.root_weight
        
        out = out + self.bias
        out = F.relu(out)
        out = self.norm(out)
        out = self.dropout(out)
        
        return out + x_in  # Residual connection
    
    def message(self, x_j: torch.Tensor) -> torch.Tensor:
        return x_j


class NodeConditionedAttention(nn.Module):
    """
    Node-Conditioned Attention for Multi-View Fusion.
    
    Unlike simple attention with a shared query, this mechanism generates
    node-specific queries based on node features. This allows each node
    to attend differently to multiple views (e.g., AST, CFG, DFG).
    
    Use case: In vulnerability detection, a node representing a function
    call might attend more to data flow, while a control structure node
    might attend more to control flow.
    
    Args:
        hidden_dim: Dimension of embeddings
        num_views: Number of views to fuse
    """
    
    def __init__(self, hidden_dim: int, num_views: int):
        super().__init__()
        self.hidden_dim = hidden_dim
        self.num_views = num_views
        
        # Query generation network
        self.query_net = nn.Sequential(
            nn.Linear(hidden_dim, hidden_dim),
            nn.Tanh(),
        )
        
        # Key projection
        self.key_proj = nn.Linear(hidden_dim, hidden_dim)
        
        # Scaling factor for attention
        self.scale = hidden_dim ** -0.5
    
    def forward(
        self,
        view_embeddings: torch.Tensor,
        node_context: torch.Tensor,
    ) -> Tuple[torch.Tensor, torch.Tensor]:
        """
        Fuse multiple view embeddings using node-conditioned attention.
        
        Args:
            view_embeddings: [N, num_views, hidden_dim]
            node_context: [N, hidden_dim] - context for query generation
            
        Returns:
            fused: [N, hidden_dim] - fused node embeddings
            attention: [N, num_views] - attention weights (for interpretability)
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
        
        # Weighted sum
        # [N, num_views, 1] * [N, num_views, hidden_dim] -> sum -> [N, hidden_dim]
        fused = (view_embeddings * attention.unsqueeze(-1)).sum(dim=1)
        
        return fused, attention