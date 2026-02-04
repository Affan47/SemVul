# gcn_devign.py – baseline GCN for the Devign vulnerability dataset
"""
A reproducible PyG pipeline that trains a GIN on Devign function
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
* **Results CSV & plots** under `GIN_devign/results/`.
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
from torch_geometric.nn import NNConv, global_add_pool, BatchNorm
from torch_geometric.utils import softmax
from torch_geometric.data import Dataset, Data
from torch_geometric.loader import DataLoader
from torch_geometric.nn import GINConv, global_mean_pool, BatchNorm
from torch_geometric.nn import GCNConv, GATConv,HANConv, global_mean_pool, BatchNorm, RGCNConv
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


class DevignDataset(Dataset):
    """Loads GAT → PyG `Data` objects on-the-fly.

    *Nodes* are represented by a **type index** (int) that gets embedded
    inside the model.  Edge labels are ignored in this baseline.
    """

    def __init__(
        self,
        manifest_csv: Path | str,
        json_root: Path | str,
        node_type_vocab: Dict[str, int] | None = None,
        edge_type_vocab: Dict[str, int] | None = None,
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

        # Build or reuse vocabularies
        ### Node-types vocab
        self.node_type_vocab = (
            node_type_vocab if node_type_vocab is not None else self._build_vocab()
        )
        self.num_node_types = len(self.node_type_vocab)

        ### Edge-types vocab
        self.edge_type_vocab = (
            edge_type_vocab if edge_type_vocab is not None else self._build_edge_vocab()
        )
        self.num_edge_types = len(self.edge_type_vocab)

    # ------------------------------------------------------------------ #
    # vocab
    # ------------------------------------------------------------------ #

    # Builds a node-type vocabulary from the dataset.
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

    # Builds an edge-type vocabulary from the dataset.
    # Note: this is not used in the GCN baseline, but is needed for MPNN.

    def _build_edge_vocab(self) -> Dict[str, int]:
        vocab = set()
        for idx in tqdm(self.df["index"],
                        desc="Building edge-type vocab",
                        unit="file"):
            jpath = self.json_root / f"F{int(idx):06d}" / "export.json"
            with open(jpath) as f:
                j = json.load(f)
            for e in j["@value"]["edges"]:
                vocab.add(e["label"])
        print(f"[Vocab] {len(vocab)} distinct edge types")
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
        ).t().contiguous()                      # [2, E]

        edge_attr = torch.tensor(
            [self.edge_type_vocab[e["label"]] for e in edges],
            dtype=torch.long
        ) 

        data = Data(
            x=x,
            edge_index=edge_index,
            edge_attr=edge_attr,
            y=torch.tensor(label, dtype=torch.long)
        )
        return self.transform(data) if self.transform else data


# ─────────────────────────────────────────────────────────────────────────────
# Model
# ─────────────────────────────────────────────────────────────────────────────

# ────────────────────────────────────────────────────────────────────
# Edge network
# ────────────────────────────────────────────────────────────────────
class HANBaseline(nn.Module):
    """
    Heterogeneous Attention Network for Devign graphs.
    Every edge-type (relation ID) is treated as its own meta-path.
    """
    def __init__(
        self,
        num_node_types: int,
        num_relations: int,
        emb_dim: int = 128,
        hidden_dim: int = 128,
        num_layers: int = 2,
        heads: int = 8,
        dropout: float = 0.6,
        num_classes: int = 2,
    ):
        super().__init__()

        # ── Node embedding ────────────────────────────────────────────
        self.node_emb = nn.Embedding(num_node_types, emb_dim)

        # ── HAN metadata (1 node-type, many edge-types) ──────────────
        node_types = ["node"]
        edge_types = [("node", str(r), "node") for r in range(num_relations)]
        self.metadata: tuple[list[str], list[tuple[str, str, str]]] = (
            node_types,
            edge_types,
        )

        # ── Stack of HANConv layers ──────────────────────────────────
        self.han_layers = nn.ModuleList()
        in_dim = emb_dim                           # first layer input
        for _ in range(num_layers):
            self.han_layers.append(
                HANConv(
                    in_dim,                        # in_channels
                    hidden_dim,                    # out_channels
                    self.metadata,                 # metadata (3rd arg)
                    heads=heads,
                    dropout=dropout,
                )
            )
            in_dim = hidden_dim                    # **not multiplied by heads**

        # ── Classifier head ──────────────────────────────────────────
        self.dropout   = nn.Dropout(dropout)
        self.project   = nn.Linear(in_dim, hidden_dim)
        self.classifier = nn.Linear(hidden_dim, num_classes)

    # -----------------------------------------------------------------
    def forward(
        self,
        x: torch.Tensor,          # [N]
        edge_index: torch.Tensor, # [2, E]
        edge_attr: torch.Tensor,  # [E]
        batch: torch.Tensor,      # [N]
    ) -> torch.Tensor:
        # 1) initial node features
        x = self.node_emb(x)                                # [N, emb_dim]

        # 2) build hetero dictionaries for HANConv
        x_dict = {"node": x}
        edge_index_dict: dict[tuple[str, str, str], torch.Tensor] = {}
        for rel_id in edge_attr.unique():
            rid = int(rel_id)
            edge_index_dict[("node", str(rid), "node")] = edge_index[:, edge_attr == rid]

        # 3) stacked HAN layers
        for han in self.han_layers:
            x_dict = han(x_dict, edge_index_dict)          # hetero → hetero
            x_dict["node"] = self.dropout(F.elu(x_dict["node"]))

        x = x_dict["node"]                                 # [N, hidden_dim]

        # 4) graph-level read-out & prediction
        g = global_add_pool(x, batch)                      # [B, hidden_dim]
        g = F.elu(self.project(g))
        return self.classifier(g)




# ─────────────────────────────────────────────────────────────────────────────
# Evaluation helpers
# ─────────────────────────────────────────────────────────────────────────────


@torch.no_grad()
def evaluate(model: nn.Module, loader: DataLoader, device: torch.device):
    model.eval()
    ys, preds, probs = [], [], []
    for batch in loader:
        batch = batch.to(device)
        logits = model(batch.x, batch.edge_index, batch.edge_attr, batch.batch)
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
    root = Path("HAN_devign")
    results_dir = root / "results"
    model_dir = root / "models"
    results_dir.mkdir(parents=True, exist_ok=True)
    model_dir.mkdir(parents=True, exist_ok=True)

    # ── load or defer-create vocabularies ───────────────────────────
    node_vocab_file = model_dir / "node_vocab.json"
    edge_vocab_file = model_dir / "edge_vocab.json"

    cached_node_vocab = cached_edge_vocab = None          # defaults

    if node_vocab_file.exists() and edge_vocab_file.exists():
        try:
            with open(node_vocab_file) as f:
                cached_node_vocab = json.load(f)
            with open(edge_vocab_file) as f:
                cached_edge_vocab = json.load(f)
            print(f"[Vocab] Reusing cached vocabularies "
                  f"({len(cached_node_vocab)} node types, "
                  f"{len(cached_edge_vocab)} edge types)")
        except Exception as err:
            print(f"[Vocab] Cache damaged or unreadable ({err}); "
                  "will rebuild this run and overwrite.")
            cached_node_vocab = cached_edge_vocab = None


   
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

    # ---- train split -------------------------------------------------------
    train_ds = DevignDataset(
        **paths["train"],
        node_type_vocab=cached_node_vocab,
        edge_type_vocab=cached_edge_vocab
    )

    # If nothing was cached, we’ve just built the vocabs — save them
    if cached_node_vocab is None:
        with open(node_vocab_file, "w") as f:
            json.dump(train_ds.node_type_vocab, f)
        with open(edge_vocab_file, "w") as f:
            json.dump(train_ds.edge_type_vocab, f)
        print(f"[Vocab] Saved vocabularies to {model_dir}/")

    # ---- val / test splits -------------------------------------------------
    val_ds = DevignDataset(
        **paths["val"],
        node_type_vocab=train_ds.node_type_vocab,
        edge_type_vocab=train_ds.edge_type_vocab
    )
    test_ds = DevignDataset(
        **paths["test"],
        node_type_vocab=train_ds.node_type_vocab,
        edge_type_vocab=train_ds.edge_type_vocab
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
    # ---- choose backbone ----------------------------------------------------
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
    else:
        raise ValueError(f"Unknown --model '{args.model}'")


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
            logits = model(batch.x, batch.edge_index, batch.edge_attr, batch.batch)
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
                logits = model(batch.x, batch.edge_index, batch.edge_attr, batch.batch)
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
            torch.save(model.state_dict(), model_dir / ckpt_name)
        else:
            no_improve += 1
            if no_improve >= args.early_stop:
                print("Early stopping triggered.")
                break

    # ──────────────────────────────────────────────────────────────────
    # Test-set evaluation
    # ──────────────────────────────────────────────────────────────────
    print("Evaluating best checkpoint on the test split …")
    model.load_state_dict(torch.load(model_dir / ckpt_name))
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
    p = argparse.ArgumentParser(prog="HAN_devign.py", description="HAN baseline")
    p.add_argument("--batch-size", type=int, default=64)
    p.add_argument("--heads", type=int, default=8,
               help="Number of attention heads")
    p.add_argument("--layers", type=int, default=3,
                help="Number of message-passing layers (mpnn/gin)")
    p.add_argument("--edge-emb-dim", type=int, default=64)
    p.add_argument("--model", choices=["mpnn", "gin", "gat", "gcn", "sage", "rgcn", "han"],
               default="mpnn",
               help="Which backbone to instantiate")
    p.add_argument(
        "--bases", type=int, default=30,
        help="Number of RGCN bases (only for --model rgcn)"
    )           
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





"""
python HAN_devign.py \
  --model han \
  --emb-dim 64 \
  --hidden-dim 128 \
  --layers 2 \
  --heads 8 \
  --batch-size 256 \
  --epochs 20 \
  --lr 1e-3 \
  --dropout 0.6






"""