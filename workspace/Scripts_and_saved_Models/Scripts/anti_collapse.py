#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
anti_collapse.py - Loss Functions and Utilities to Prevent Model Collapse

This module provides advanced loss functions and training utilities that prevent
the common "model collapse" problem where GNNs output ~0.5 for all predictions.

Key Components:
  - FocalLoss: Focuses on hard examples, down-weights easy ones
  - AntiCollapseLoss: Combines multiple loss terms with collapse prevention
  - GradientMonitor: Tracks gradient flow through the network
  - AdaptiveLRScheduler: Warmup + cosine decay with restarts

Usage:
    from anti_collapse import AntiCollapseLoss, GradientMonitor
    
    criterion = AntiCollapseLoss(
        pos_weight=1.5,
        focal_gamma=2.0,
        variance_weight=0.1,
        separation_weight=0.1,
    )
    
    grad_monitor = GradientMonitor(model)
    
    # In training loop:
    loss = criterion(logits, targets)
    loss.backward()
    grad_stats = grad_monitor.get_gradient_stats()
"""

import torch
import torch.nn as nn
import torch.nn.functional as F
from typing import Dict, Optional, Tuple, List
import warnings
import math


class FocalLoss(nn.Module):
    """
    Focal Loss for addressing class imbalance and hard example mining.
    
    From "Focal Loss for Dense Object Detection" (Lin et al., 2017)
    
    FL(p_t) = -α_t * (1 - p_t)^γ * log(p_t)
    
    Where:
        - p_t = p if y=1 else 1-p
        - α_t = α if y=1 else 1-α (class balancing)
        - γ = focusing parameter (γ > 0 reduces loss for well-classified examples)
    
    Key insight: When γ > 0, the loss for well-classified examples (p_t > 0.5)
    is down-weighted, forcing the model to focus on hard examples.
    
    Args:
        alpha: Class balance weight (default: 0.25 for rare class)
        gamma: Focusing parameter (default: 2.0)
        reduction: 'mean', 'sum', or 'none'
    """
    
    def __init__(
        self,
        alpha: float = 0.25,
        gamma: float = 2.0,
        reduction: str = 'mean',
    ):
        super().__init__()
        self.alpha = alpha
        self.gamma = gamma
        self.reduction = reduction
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        """
        Args:
            logits: Raw model outputs (before sigmoid) [N]
            targets: Binary labels [N]
        """
        # Convert to probabilities
        probs = torch.sigmoid(logits)
        
        # Compute p_t
        p_t = targets * probs + (1 - targets) * (1 - probs)
        
        # Compute alpha_t
        alpha_t = targets * self.alpha + (1 - targets) * (1 - self.alpha)
        
        # Compute focal weight
        focal_weight = (1 - p_t) ** self.gamma
        
        # BCE loss (without reduction)
        bce = F.binary_cross_entropy_with_logits(logits, targets, reduction='none')
        
        # Apply focal weighting
        focal_loss = alpha_t * focal_weight * bce
        
        if self.reduction == 'mean':
            return focal_loss.mean()
        elif self.reduction == 'sum':
            return focal_loss.sum()
        return focal_loss


class VarianceRegularizer(nn.Module):
    """
    Regularizer that penalizes low variance in predictions.
    
    When models collapse, they output similar values for all inputs.
    This regularizer adds a penalty when the variance of predictions
    falls below a threshold.
    
    L_var = max(0, min_variance - Var(predictions))
    
    Args:
        min_variance: Target minimum variance (default: 0.1)
        weight: Regularization strength
    """
    
    def __init__(self, min_variance: float = 0.1, weight: float = 1.0):
        super().__init__()
        self.min_variance = min_variance
        self.weight = weight
    
    def forward(self, logits: torch.Tensor) -> torch.Tensor:
        probs = torch.sigmoid(logits)
        variance = probs.var()
        
        # Penalty when variance is too low
        penalty = F.relu(self.min_variance - variance)
        
        return self.weight * penalty


class SeparationLoss(nn.Module):
    """
    Loss that encourages separation between positive and negative predictions.
    
    Computes the overlap between positive and negative class distributions
    and penalizes when they are too similar.
    
    L_sep = -|mean(p_pos) - mean(p_neg)| + margin
    
    Args:
        margin: Desired separation between class means (default: 0.3)
        weight: Loss weight
    """
    
    def __init__(self, margin: float = 0.3, weight: float = 1.0):
        super().__init__()
        self.margin = margin
        self.weight = weight
    
    def forward(
        self,
        logits: torch.Tensor,
        targets: torch.Tensor,
    ) -> torch.Tensor:
        probs = torch.sigmoid(logits)
        
        # Split by class
        pos_mask = (targets == 1)
        neg_mask = (targets == 0)
        
        if pos_mask.sum() == 0 or neg_mask.sum() == 0:
            return torch.tensor(0.0, device=logits.device)
        
        pos_mean = probs[pos_mask].mean()
        neg_mean = probs[neg_mask].mean()
        
        # Separation (should be positive and large)
        separation = pos_mean - neg_mean
        
        # Penalize when separation is below margin
        # We want pos_mean > neg_mean by at least margin
        loss = F.relu(self.margin - separation)
        
        return self.weight * loss


class LabelSmoothingBCE(nn.Module):
    """
    Binary Cross-Entropy with Label Smoothing.
    
    Smooths hard labels (0, 1) to soft labels (ε, 1-ε) to prevent
    overconfident predictions and improve generalization.
    
    Args:
        smoothing: Smoothing factor (default: 0.1)
        pos_weight: Weight for positive class
    """
    
    def __init__(
        self,
        smoothing: float = 0.1,
        pos_weight: Optional[float] = None,
    ):
        super().__init__()
        self.smoothing = smoothing
        self.pos_weight = pos_weight
    
    def forward(self, logits: torch.Tensor, targets: torch.Tensor) -> torch.Tensor:
        # Smooth labels
        targets_smooth = targets * (1 - self.smoothing) + 0.5 * self.smoothing
        
        if self.pos_weight is not None:
            weight = torch.where(
                targets > 0.5,
                torch.tensor(self.pos_weight, device=logits.device),
                torch.tensor(1.0, device=logits.device),
            )
            bce = F.binary_cross_entropy_with_logits(
                logits, targets_smooth, weight=weight
            )
        else:
            bce = F.binary_cross_entropy_with_logits(logits, targets_smooth)
        
        return bce


class AntiCollapseLoss(nn.Module):
    """
    Comprehensive loss function that prevents model collapse.
    
    Combines multiple loss terms:
    1. Focal Loss - focuses on hard examples
    2. Variance Regularizer - prevents uniform outputs
    3. Separation Loss - encourages class separation
    4. Label Smoothing BCE - prevents overconfidence
    
    Total Loss = α₁·L_focal + α₂·L_variance + α₃·L_separation
    
    Args:
        pos_weight: Weight for positive class in focal loss
        focal_gamma: Focusing parameter for focal loss
        focal_alpha: Class balance for focal loss
        variance_weight: Weight for variance regularizer
        min_variance: Minimum target variance
        separation_weight: Weight for separation loss
        separation_margin: Target separation margin
        label_smoothing: Label smoothing factor (0 to disable)
    """
    
    def __init__(
        self,
        pos_weight: float = 1.0,
        focal_gamma: float = 2.0,
        focal_alpha: float = 0.5,
        variance_weight: float = 0.1,
        min_variance: float = 0.05,
        separation_weight: float = 0.1,
        separation_margin: float = 0.2,
        label_smoothing: float = 0.05,
    ):
        super().__init__()
        
        # Primary loss
        if focal_gamma > 0:
            self.primary_loss = FocalLoss(
                alpha=focal_alpha,
                gamma=focal_gamma,
            )
        else:
            self.primary_loss = LabelSmoothingBCE(
                smoothing=label_smoothing,
                pos_weight=pos_weight,
            )
        
        # Regularizers
        self.variance_reg = VarianceRegularizer(
            min_variance=min_variance,
            weight=variance_weight,
        )
        
        self.separation_loss = SeparationLoss(
            margin=separation_margin,
            weight=separation_weight,
        )
        
        # Store weights for logging
        self.variance_weight = variance_weight
        self.separation_weight = separation_weight
    
    def forward(
        self,
        logits: torch.Tensor,
        targets: torch.Tensor,
    ) -> Tuple[torch.Tensor, Dict[str, float]]:
        """
        Compute total loss with component breakdown.
        
        Returns:
            total_loss: Combined loss value
            loss_dict: Dictionary with individual loss components
        """
        # Primary loss
        l_primary = self.primary_loss(logits, targets)
        
        # Regularizers
        l_variance = self.variance_reg(logits)
        l_separation = self.separation_loss(logits, targets)
        
        # Total
        total = l_primary + l_variance + l_separation
        
        # Log components
        loss_dict = {
            'primary': l_primary.item(),
            'variance': l_variance.item(),
            'separation': l_separation.item(),
            'total': total.item(),
        }
        
        return total, loss_dict


class GradientMonitor:
    """
    Monitors gradient flow through the network to detect vanishing gradients.
    
    Usage:
        monitor = GradientMonitor(model)
        
        # After loss.backward():
        stats = monitor.get_gradient_stats()
        
        if stats['min_grad'] < 1e-7:
            print("Warning: Vanishing gradients detected!")
    """
    
    def __init__(self, model: nn.Module, threshold: float = 1e-8):
        self.model = model
        self.gradient_norms = {}
        self.threshold = threshold
        self._warned = False
    
    def get_gradient_stats(self) -> Dict[str, float]:
        """Get statistics about gradient magnitudes."""
        grad_norms = []
        zero_count = 0
        
        for name, param in self.model.named_parameters():
            if param.grad is not None:
                grad_norm = param.grad.data.norm(2).item()
                grad_norms.append(grad_norm)
                self.gradient_norms[name] = grad_norm
                if grad_norm < self.threshold:
                    zero_count += 1
        
        if not grad_norms:
            return {
                'mean_grad': 0.0,
                'max_grad': 0.0,
                'min_grad': 0.0,
                'std_grad': 0.0,
                'zero_count': 0,
                'total_params': 0,
            }
        
        return {
            'mean_grad': sum(grad_norms) / len(grad_norms),
            'max_grad': max(grad_norms),
            'min_grad': min(grad_norms),
            'std_grad': torch.tensor(grad_norms).std().item(),
            'zero_count': zero_count,
            'total_params': len(grad_norms),
        }
    
    def get_layer_gradients(self) -> Dict[str, float]:
        """Get gradient norms per layer."""
        return self.gradient_norms.copy()
    
    def check_vanishing(self, threshold: float = None) -> List[str]:
        """Return names of layers with vanishing gradients."""
        if threshold is None:
            threshold = self.threshold
        vanishing = []
        for name, norm in self.gradient_norms.items():
            if norm < threshold:
                vanishing.append(name)
        return vanishing
    
    def should_warn(self) -> bool:
        """Check if we should warn about vanishing gradients (only once per epoch)."""
        stats = self.get_gradient_stats()
        # Warn if >50% of parameters have vanishing gradients
        if stats['total_params'] > 0:
            vanishing_ratio = stats['zero_count'] / stats['total_params']
            if vanishing_ratio > 0.5 and not self._warned:
                self._warned = True
                return True
        return False
    
    def reset_warning(self):
        """Reset warning flag for new epoch."""
        self._warned = False


class WarmupCosineScheduler:
    """
    Learning rate scheduler with linear warmup and cosine decay.
    
    Warmup helps prevent early collapse by starting with a small LR.
    Cosine decay allows the model to fine-tune at lower LRs.
    
    Args:
        optimizer: PyTorch optimizer
        warmup_epochs: Number of warmup epochs
        total_epochs: Total training epochs
        min_lr_ratio: Minimum LR as fraction of initial LR
        warmup_start_lr_ratio: Starting LR ratio during warmup (default: 0.1)
    """
    
    def __init__(
        self,
        optimizer: torch.optim.Optimizer,
        warmup_epochs: int,
        total_epochs: int,
        min_lr_ratio: float = 0.01,
        warmup_start_lr_ratio: float = 0.1,
    ):
        self.optimizer = optimizer
        self.warmup_epochs = warmup_epochs
        self.total_epochs = total_epochs
        self.min_lr_ratio = min_lr_ratio
        self.warmup_start_lr_ratio = warmup_start_lr_ratio
        self.base_lrs = [group['lr'] for group in optimizer.param_groups]
        self.current_epoch = 0
    
    def step(self, epoch: Optional[int] = None):
        if epoch is not None:
            self.current_epoch = epoch
        else:
            self.current_epoch += 1
        
        if self.current_epoch < self.warmup_epochs:
            # Linear warmup from warmup_start_lr_ratio to 1.0
            progress = self.current_epoch / max(self.warmup_epochs, 1)
            lr_scale = self.warmup_start_lr_ratio + progress * (1.0 - self.warmup_start_lr_ratio)
        else:
            # Cosine decay
            progress = (self.current_epoch - self.warmup_epochs) / max(
                self.total_epochs - self.warmup_epochs, 1
            )
            lr_scale = self.min_lr_ratio + 0.5 * (1 - self.min_lr_ratio) * (
                1 + math.cos(math.pi * progress)
            )
        
        for param_group, base_lr in zip(self.optimizer.param_groups, self.base_lrs):
            param_group['lr'] = base_lr * lr_scale
    
    def get_lr(self) -> float:
        return self.optimizer.param_groups[0]['lr']


def compute_collapse_metrics(
    probs: torch.Tensor,
    targets: torch.Tensor,
) -> Dict[str, float]:
    """
    Compute metrics to detect model collapse.
    
    Returns:
        Dictionary with:
        - variance: Prediction variance
        - separation: Mean difference between classes
        - pos_mean: Mean prediction for positive class
        - neg_mean: Mean prediction for negative class
        - entropy: Average prediction entropy
        - collapse_score: Overall collapse indicator (0-1, higher = more collapse)
    """
    pos_mask = (targets == 1)
    neg_mask = (targets == 0)
    
    # Basic stats
    variance = probs.var().item()
    
    pos_mean = probs[pos_mask].mean().item() if pos_mask.sum() > 0 else 0.5
    neg_mean = probs[neg_mask].mean().item() if neg_mask.sum() > 0 else 0.5
    
    separation = pos_mean - neg_mean
    
    # Entropy (higher = more uncertain = potential collapse)
    # Binary entropy: -p*log(p) - (1-p)*log(1-p)
    eps = 1e-7
    entropy = -(probs * torch.log(probs + eps) + 
                (1 - probs) * torch.log(1 - probs + eps)).mean().item()
    
    # Collapse score: high when variance low and separation low
    # Normalized to 0-1 range
    variance_score = max(0, 1 - variance / 0.1)  # Low variance = high score
    separation_score = max(0, 1 - abs(separation) / 0.3)  # Low sep = high score
    collapse_score = 0.5 * variance_score + 0.5 * separation_score
    
    return {
        'variance': variance,
        'separation': separation,
        'pos_mean': pos_mean,
        'neg_mean': neg_mean,
        'entropy': entropy,
        'collapse_score': collapse_score,
    }


def diagnose_collapse(
    probs: torch.Tensor,
    targets: torch.Tensor,
) -> str:
    """
    Diagnose the type of model collapse and suggest fixes.
    
    Returns:
        Diagnostic message with recommendations.
    """
    metrics = compute_collapse_metrics(probs, targets)
    
    messages = []
    recommendations = []
    
    # Check variance
    if metrics['variance'] < 0.05:
        messages.append(f"🚨 SEVERE: Very low variance ({metrics['variance']:.4f})")
        recommendations.append("- Increase learning rate 2-3x")
        recommendations.append("- Add variance regularization (variance_weight=0.2)")
        recommendations.append("- Check for vanishing gradients")
    elif metrics['variance'] < 0.1:
        messages.append(f"⚠️ WARNING: Low variance ({metrics['variance']:.4f})")
        recommendations.append("- Consider increasing variance_weight")
    
    # Check separation
    if abs(metrics['separation']) < 0.05:
        messages.append(f"🚨 SEVERE: No class separation ({metrics['separation']:.4f})")
        recommendations.append("- Add separation loss (separation_weight=0.2)")
        recommendations.append("- Check if labels are correct")
        recommendations.append("- Try focal loss with gamma=2.0")
    elif abs(metrics['separation']) < 0.1:
        messages.append(f"⚠️ WARNING: Poor separation ({metrics['separation']:.4f})")
        recommendations.append("- Increase separation_weight")
    
    # Check if predictions are centered around 0.5
    center = (metrics['pos_mean'] + metrics['neg_mean']) / 2
    if 0.45 < center < 0.55:
        messages.append(f"⚠️ Predictions centered around {center:.3f}")
        if metrics['pos_mean'] < 0.55 and metrics['neg_mean'] > 0.45:
            recommendations.append("- Model is predicting ~0.5 for everything!")
            recommendations.append("- This is classic collapse - try all recommendations above")
    
    # Check entropy
    if metrics['entropy'] > 0.65:  # Max binary entropy is ~0.693
        messages.append(f"⚠️ High entropy ({metrics['entropy']:.4f}) - very uncertain predictions")
        recommendations.append("- Consider label smoothing to reduce this")
    
    # Build output
    output = "\n".join(messages) if messages else "✅ No obvious collapse detected"
    
    if recommendations:
        output += "\n\nRecommendations:\n" + "\n".join(recommendations)
    
    return output