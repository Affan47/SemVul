# gcn_devign.py – baseline GCN for the Devign vulnerability dataset
"""
A reproducible PyG pipeline that trains a 2-layer GCN on Devign function
graphs exported by Joern (GraphSON).

This is the **baseline** for an ablation study. Only a plain GCN is
implemented; you can swap in more advanced GNN layers later.

Key upgrades over the first draft
---------------------------------
* **Sparse node embedding** (vs. one-hot) → smaller & faster.
* **Deterministic seeding** for reproducibility.
* **Edge attributes dropped** (unused by GCN) to save VRAM.
* **Class-balanced CE loss** computed from the training split.
* **Dropout + BatchNorm1d** between GCN layers.
* **LR scheduler** + early-stop on validation *loss* **and** F1.
* **CLI** for quick hyper-parameter overrides.
* **Results CSV & plots** under `GCN_devign/results/`.
"""

from __future__ import annotations

import argparse
import json
import os
import random
from pathlib import Path
from typing import Dict, List

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
import torch
import torch.nn.functional as F
from sklearn.metrics import (accuracy_score, average_precision_score,
                             confusion_matrix, f1_score, precision_recall_curve,
                             precision_score, recall_score, roc_curve, auc)
from torch import nn
from torch_geometric.data import Dataset, Data
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GCNConv, GATConv, global_mean_pool, BatchNorm
from tqdm import tqdm

# ─────────────────────────────────────────────────────────────────────────────
# Utility
# ─────────────────────────────────────────────────────────────────────────────


def set_seed(seed: int = 42) -> None:
    """Force-deterministic behaviour (CUDA + CPU)."""
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.deterministic = True  # type: ignore[attr-defined]
    torch.backends.cudnn.benchmark = False     # type: ignore[attr-defined]

# ─────────────────────────────────────────────────────────────────────────────
# Dataset
# ─────────────────────────────────────────────────────────────────────────────


class DevignGCNDataset(Dataset):
    """Loads GAT → PyG `Data` objects on-the-fly.

    *Nodes* are represented by a **type index** (int) that gets embedded
    inside the model.  Edge labels are ignored in this baseline.
    """

    def __init__(
        self,
        manifest_csv: Path | str,
        json_root: Path | str,
        node_type_vocab: Dict[str, int] | None = None,
        transform=None,
    ):
        super().__init__()
        self.df = pd.read_csv(manifest_csv)
        self.json_root = Path(json_root)
        self.transform = transform

        # Keep only rows whose JSON exists
        good: List[int] = []
        for idx in tqdm (self.df["index"],desc="Scanning JSON paths",unit="file"):
            if (self.json_root / f"F{int(idx):06d}" / "export.json").is_file():
                good.append(idx)
        before = len(self.df)
        self.df = self.df[self.df["index"].isin(good)].reset_index(drop=True)
        print(f"[Dataset] {len(self.df)}/{before} JSON graphs found in {json_root}")

        # Build or reuse vocab
        self.node_type_vocab = (
            node_type_vocab if node_type_vocab is not None else self._build_vocab()
        )
        self.num_node_types = len(self.node_type_vocab)

    # ------------------------------------------------------------------ #
    # vocab
    # ------------------------------------------------------------------ #

    def _build_vocab(self) -> Dict[str, int]:
        vocab = set()
        for idx in tqdm (self.df["index"],desc="Building node-type vocab",unit="file"):
            jpath = self.json_root / f"F{int(idx):06d}" / "export.json"
            with open(jpath) as f:
                j = json.load(f)
            for e in j["@value"]["edges"]:
                vocab.add(e["inVLabel"])
                vocab.add(e["outVLabel"])
        print(f"[Vocab] {len(vocab)} distinct node types")
        return {t: i for i, t in enumerate(sorted(vocab))}

    # ------------------------------------------------------------------ #
    # torch Dataset API
    # ------------------------------------------------------------------ #

    def len(self) -> int:  # type: ignore[override]
        return len(self.df)

    def get(self, idx: int) -> Data:  # type: ignore[override]
        row = self.df.iloc[idx]
        func_id, label = int(row["index"]), int(row["label"])
        jpath = self.json_root / f"F{func_id:06d}" / "export.json"

        with open(jpath) as f:
            j = json.load(f)
        edges = j["@value"]["edges"]

        node_ids = set()
        node_types: Dict[int, str] = {}
        for e in edges:
            in_id = e["inV"]["@value"]
            out_id = e["outV"]["@value"]
            node_ids.update([in_id, out_id])
            node_types[in_id] = e["inVLabel"]
            node_types[out_id] = e["outVLabel"]

        node_ids = sorted(node_ids)
        id_map = {nid: i for i, nid in enumerate(node_ids)}

        x = torch.tensor(
            [self.node_type_vocab[node_types[nid]] for nid in node_ids],
            dtype=torch.long,
        )  # [N]

        edge_index = torch.tensor(
            [[id_map[e["outV"]["@value"]], id_map[e["inV"]["@value"]]] for e in edges],
            dtype=torch.long,
        ).t().contiguous()  # [2, E]

        data = Data(x=x, edge_index=edge_index, y=torch.tensor(label, dtype=torch.long))
        return self.transform(data) if self.transform else data


# ─────────────────────────────────────────────────────────────────────────────
# Model
# ─────────────────────────────────────────────────────────────────────────────


class GATBaseline(nn.Module):
    def __init__(self, num_node_types: int,
                 emb_dim: int = 64, hidden_dim: int = 128,
                 heads: int = 8, dropout: float = 0.3, num_classes: int = 2):
        super().__init__()
        self.emb = nn.Embedding(num_node_types, emb_dim)

        self.gat1 = GATConv(
            in_channels=emb_dim,
            out_channels=hidden_dim,
            heads=heads,
            concat=False,          # ← change here
            dropout=dropout
        )
        self.bn1 = BatchNorm(hidden_dim)

        self.gat2 = GATConv(
            in_channels=hidden_dim,
            out_channels=hidden_dim,
            heads=heads,
            concat=False,          # ← change here
            dropout=dropout
        )
        self.bn2 = BatchNorm(hidden_dim)

        self.lin  = nn.Linear(hidden_dim, num_classes)
        self.drop = nn.Dropout(dropout)
    # ────────────────────────────────────────────────────────────────
    # forward
    # ────────────────────────────────────────────────────────────────
    def forward(self, x, edge_index, batch):
        """
        x          LongTensor[N]   – node-type indices
        edge_index LongTensor[2,E] – COO format
        batch      LongTensor[N]   – graph ID for each node
        """
        x = self.emb(x)                                 # [N] → [N, emb_dim]
        x = F.relu(self.bn1(self.gat1(x, edge_index)))  # GAT layer 1
        x = self.drop(x)
        x = F.relu(self.bn2(self.gat2(x, edge_index)))  # GAT layer 2
        x = global_mean_pool(x, batch)                  # graph-level readout
        return self.lin(x)                              # [B, num_classes]


# ─────────────────────────────────────────────────────────────────────────────
# Evaluation helpers
# ─────────────────────────────────────────────────────────────────────────────


@torch.no_grad()
def evaluate(model: nn.Module, loader: DataLoader, device: torch.device):
    model.eval()
    ys, preds, probs = [], [], []
    for batch in loader:
        batch = batch.to(device)
        logits = model(batch.x, batch.edge_index, batch.batch)
        soft = F.softmax(logits, dim=1)
        preds.extend(soft.argmax(dim=1).cpu().tolist())
        probs.extend(soft[:, 1].cpu().tolist())  # P(class=1)
        ys.extend(batch.y.cpu().tolist())
    return np.array(ys), np.array(preds), np.array(probs)


def plot_conf_mat(y_true, y_pred, out: Path):
    cm = confusion_matrix(y_true, y_pred)
    plt.figure(figsize=(4, 3))
    sns.heatmap(
        cm,
        annot=True,
        fmt="d",
        cmap="Blues",
        xticklabels=["Benign", "Vuln"],
        yticklabels=["Benign", "Vuln"],
    )
    plt.ylabel("True label")
    plt.xlabel("Pred label")
    plt.tight_layout()
    plt.savefig(out)
    plt.close()


def plot_roc_pr(y_true, y_prob, roc_out: Path, pr_out: Path):
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
    plt.plot(rec, prec, label=f"AP={average_precision_score(y_true, y_prob):.2f}")
    plt.xlabel("Recall")
    plt.ylabel("Precision")
    plt.legend()
    plt.tight_layout()
    plt.savefig(pr_out)
    plt.close()


# ─────────────────────────────────────────────────────────────────────────────
# Training loop
# ─────────────────────────────────────────────────────────────────────────────


def train(args):
    set_seed(args.seed)

    # ── I/O dirs ────────────────────────────────────────────────────────
    root = Path("GAT_devign")
    results_dir = root / "results"
    model_dir = root / "models"
    results_dir.mkdir(parents=True, exist_ok=True)
    model_dir.mkdir(parents=True, exist_ok=True)

    # ── Dataset paths (edit if needed) ─────────────────────────────────
# ── Dataset paths (absolute) ───────────────────────────────────────
    paths = {
        "train": {
            "manifest_csv": "./"
                            "workspace/01_Normalized_datasets/03_normalized_devign/"
                            "manifest_train.csv",
            "json_root":   "./"
                            "Json_exports/normalized_devign_json/train_graphson",
        },
        "val": {
            "manifest_csv": "./"
                            "workspace/01_Normalized_datasets/03_normalized_devign/"
                            "manifest_valid.csv",
            "json_root":   "./"
                            "Json_exports/normalized_devign_json/valid_graphson",
        },
        "test": {
            "manifest_csv": "./"
                            "workspace/01_Normalized_datasets/03_normalized_devign/"
                            "manifest_test.csv",
            "json_root":   "./"
                            "Json_exports/normalized_devign_json/test_graphson",
        },
    }


    print("Loading datasets …")
    train_ds = DevignGCNDataset(**paths["train"])
    val_ds = DevignGCNDataset(
        **paths["val"], node_type_vocab=train_ds.node_type_vocab
    )
    test_ds = DevignGCNDataset(
        **paths["test"], node_type_vocab=train_ds.node_type_vocab
    )

    # ── Class weights for imbalance ────────────────────────────────────
    counts = train_ds.df["label"].value_counts().to_dict()
    class_weights = torch.tensor(
        [counts.get(0, 1), counts.get(1, 1)], dtype=torch.float
    )

    # ── DataLoaders ────────────────────────────────────────────────────
    dl_kw = dict(
        batch_size=args.batch_size,
        num_workers=os.cpu_count(),
        pin_memory=True,
        follow_batch=[],
    )
    train_loader = DataLoader(train_ds, shuffle=True, **dl_kw)
    val_loader = DataLoader(val_ds, shuffle=False, **dl_kw)
    test_loader = DataLoader(test_ds, shuffle=False, **dl_kw)

    # ── Model / optim ──────────────────────────────────────────────────
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model = GATBaseline(
        num_node_types=train_ds.num_node_types,
        emb_dim=args.emb_dim,        # keep CLI flexibility
        hidden_dim=args.hidden_dim,
        heads=args.heads,            # new CLI argument (see below)
        dropout=args.dropout,
    ).to(device)


    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(
        optimizer, mode="min", patience=3, factor=0.5
    )
    ce_loss = nn.CrossEntropyLoss(weight=class_weights.to(device))

    best_f1, no_improve = 0.0, 0
    for epoch in range(1, args.epochs + 1):
        model.train()
        total_loss = 0.0
        for batch in tqdm(train_loader, desc=f"Epoch {epoch}/{args.epochs}"):
            batch = batch.to(device)
            optimizer.zero_grad()
            logits = model(batch.x, batch.edge_index, batch.batch)
            loss = ce_loss(logits, batch.y)
            loss.backward()
            optimizer.step()
            total_loss += loss.item()

        # ── Validation ────────────────────────────────────────────────
        model.eval()
        val_loss = 0.0
        for batch in val_loader:
            batch = batch.to(device)
            with torch.no_grad():
                logits = model(batch.x, batch.edge_index, batch.batch)
                val_loss += ce_loss(logits, batch.y).item()
        val_loss /= len(val_loader)
        scheduler.step(val_loss)

        y_true, y_pred, _ = evaluate(model, val_loader, device)
        val_f1 = f1_score(y_true, y_pred, zero_division=0)
        print(
            f"Epoch {epoch:02d} "
            f"| train_loss {total_loss/len(train_loader):.4f} "
            f"| val_loss {val_loss:.4f} "
            f"| val_f1 {val_f1:.4f}"
        )

        # ── Early stopping ───────────────────────────────────────────
        if val_f1 > best_f1:
            best_f1, no_improve = val_f1, 0
            torch.save(model.state_dict(), model_dir / "best_GAT.pt")
        else:
            no_improve += 1
            if no_improve >= args.early_stop:
                print("Early stopping triggered.")
                break

    # ──────────────────────────────────────────────────────────────────
    # Test-set evaluation
    # ──────────────────────────────────────────────────────────────────
    print("Evaluating best checkpoint on the test split …")
    model.load_state_dict(torch.load(model_dir / "best_GAT.pt"))
    y_true, y_pred, y_prob = evaluate(model, test_loader, device)

    metrics = {
        "accuracy": accuracy_score(y_true, y_pred),
        "precision": precision_score(y_true, y_pred, zero_division=0),
        "recall": recall_score(y_true, y_pred, zero_division=0),
        "f1": f1_score(y_true, y_pred, zero_division=0),
    }
    print("Test metrics:", metrics)

    # ── Save artefacts ────────────────────────────────────────────────
    pd.DataFrame([metrics]).to_csv(results_dir / "test_metrics.csv", index=False)
    pd.DataFrame(
        {
            "ground_truth": y_true,
            "prediction": y_pred,
            "probability": y_prob,
        }
    ).to_csv(results_dir / "predictions.csv", index=False)

    plot_conf_mat(y_true, y_pred, results_dir / "confusion_matrix.png")
    plot_roc_pr(
        y_true,
        y_prob,
        results_dir / "roc_curve.png",
        results_dir / "pr_curve.png",
    )


# ─────────────────────────────────────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────────────────────────────────────


def parse_args():
    p = argparse.ArgumentParser(prog="GAT_devign.py", description="GAT baseline")
    p.add_argument("--batch-size", type=int, default=64)
    p.add_argument("--heads", type=int, default=8,
               help="Number of attention heads")
    p.add_argument("--lr", type=float, default=1e-3)
    p.add_argument("--epochs", type=int, default=30)
    p.add_argument("--early-stop", type=int, default=30)
    p.add_argument("--emb-dim", type=int, default=64)
    p.add_argument("--hidden-dim", type=int, default=128)
    p.add_argument("--dropout", type=float, default=0.3)
    p.add_argument("--seed", type=int, default=42)
    return p.parse_args()


if __name__ == "__main__":
    sns.set_theme(style="whitegrid")
    args = parse_args()
    train(args)






### python GAT_devign.py
