import sys
import os
import time
import json
import random
import math
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from pathlib import Path  # <--- FIXED: Added missing import
import logging

# PyG Imports
from torch_geometric.loader import DataLoader
from torch_geometric.data import Dataset, Data, Batch
from torch_geometric.nn import RGCNConv, global_max_pool, global_mean_pool, JumpingKnowledge
from tqdm import tqdm
from sklearn.metrics import f1_score, precision_score, recall_score, roc_auc_score

# ==============================================================================
# 0. LOGGING SETUP (Saves to debug_mptcn.log)
# ==============================================================================
# Clear previous handlers if any
for handler in logging.root.handlers[:]:
    logging.root.removeHandler(handler)

logging.basicConfig(
    level=logging.INFO,
    format="%(message)s",
    handlers=[
        logging.FileHandler("debug_mptcn.log", mode='w'), # Overwrite each run
        logging.StreamHandler(sys.stdout)
    ]
)
logger = logging.getLogger()

def log(msg):
    logger.info(msg)

# ==============================================================================
# 1. DEBUG HELPERS (The "X-Ray" for your Model)
# ==============================================================================
def debug_tensor_stats(name, tensor):
    """Prints min/max/mean/std to detect dead signals."""
    if tensor is None:
        log(f"[DEBUG] {name} is None!")
        return
    
    t = tensor.float()
    log(f"[DEBUG] {name}: Shape={tuple(t.shape)} | "
          f"Mean={t.mean().item():.4f} | Std={t.std().item():.4f} | "
          f"Min={t.min().item():.4f} | Max={t.max().item():.4f}")

def debug_edge_types(edge_type, num_relations):
    """Checks if RGCN is actually using all 5 edge types."""
    if edge_type is None:
        log("[DEBUG] Edge Types: None (RGCN will fail!)")
        return
    
    # Count occurrences of each relation type (0..4)
    counts = torch.bincount(edge_type, minlength=num_relations)
    log(f"[DEBUG] Edge Distribution (0..{num_relations-1}): {counts.tolist()}")
    
    # Heuristic: If only 1 type is used, something is wrong
    active_types = (counts > 0).sum().item()
    if active_types < 2:
        log("[DEBUG] ⚠️ CRITICAL WARNING: Graph uses < 2 edge types! RGCN cannot learn semantics.")

# ==============================================================================
# 2. MODEL DEFINITIONS (Instrumented)
# ==============================================================================

class JKPoolingHead(nn.Module):
    def __init__(self, input_dim):
        super().__init__()
        self.input_dim = input_dim

    def forward(self, x, batch):
        # DEBUG: Check pooling inputs occasionally
        if random.random() < 0.01: 
             debug_tensor_stats("Node Embeddings (Pre-Pool)", x)

        h_max = global_max_pool(x, batch)
        h_mean = global_mean_pool(x, batch)
        
        # DEBUG: Check if Max is dominating Mean (Paranoia Check)
        if random.random() < 0.01:
            max_mag = h_max.abs().mean().item()
            mean_mag = h_mean.abs().mean().item()
            log(f"[DEBUG] Pooling: MaxMag={max_mag:.4f} | MeanMag={mean_mag:.4f}")
            
            if mean_mag > 0 and max_mag > 10 * mean_mag:
                 log("[DEBUG] ⚠️ WARNING: Max Pooling is 10x stronger than Mean. Sparse features dominating.")

        return torch.cat([h_max, h_mean], dim=1)

class RgcnResBackbone(nn.Module):
    def __init__(self, input_dim: int, hidden_dim: int, layers: int = 8, num_relations: int = 5, dropout: float = 0.2):
        super().__init__()
        self.layers = int(layers)
        self.dropout = dropout
        self.convs = nn.ModuleList()
        self.bns = nn.ModuleList()
        self.num_relations = num_relations

        self.input_proj = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.BatchNorm1d(hidden_dim),
            nn.ReLU()
        )

        for _ in range(layers):
            self.convs.append(RGCNConv(hidden_dim, hidden_dim, num_relations=num_relations))
            self.bns.append(nn.BatchNorm1d(hidden_dim))

        self.jk = JumpingKnowledge(mode='cat')

    def forward(self, x, edge_index, edge_type):
        # DEBUG: Inspect Inputs once per epoch roughly
        if random.random() < 0.005:
             log("\n" + "="*40)
             log(" [RGCN LAYER INPUT DEBUG] ")
             debug_tensor_stats("Input Features X", x)
             debug_edge_types(edge_type, self.num_relations)
             log("="*40 + "\n")

        x = self.input_proj(x)
        xs = [] 
        
        if edge_type is not None:
            edge_type = edge_type.long()

        for i, conv in enumerate(self.convs):
            x_in = x
            x = conv(x, edge_index, edge_type)
            x = self.bns[i](x)
            x = F.relu(x)
            x = F.dropout(x, p=self.dropout, training=self.training)
            x = x + x_in
            xs.append(x)

        x_final = self.jk(xs)
        return x_final

class DevignNet(nn.Module):
    def __init__(self, input_dim, hidden_dim, out_dim, steps=8, dropout=0.2, num_relations=5, **kwargs):
        super().__init__()
        
        self.backbone = RgcnResBackbone(
            input_dim=int(input_dim),
            hidden_dim=int(hidden_dim),
            layers=int(steps),
            num_relations=int(num_relations),
            dropout=dropout
        )

        jk_dim = int(hidden_dim) * int(steps)
        self.readout = JKPoolingHead(jk_dim)
        classifier_input_dim = jk_dim * 2
        
        self.encoder = nn.Sequential(
            nn.Linear(classifier_input_dim, 512),
            nn.BatchNorm1d(512), nn.ReLU(), nn.Dropout(dropout),
            nn.Linear(512, 256),
            nn.BatchNorm1d(256), nn.ReLU()
        )
        
        self.cls_head = nn.Sequential(nn.Dropout(dropout), nn.Linear(256, int(out_dim)))
        self.supcon_head = nn.Sequential(nn.Linear(256, 256), nn.ReLU(), nn.Linear(256, 128))

    def forward(self, data):
        x, edge_index = data.x.float(), data.edge_index
        edge_type = data.edge_type if hasattr(data, 'edge_type') else None
        
        batch = data.batch if hasattr(data, "batch") and data.batch is not None else x.new_zeros(x.size(0), dtype=torch.long)
        
        node_embs = self.backbone(x, edge_index, edge_type)
        graph_emb = self.readout(node_embs, batch)
        feat = self.encoder(graph_emb)
        
        logits = self.cls_head(feat)
        proj = F.normalize(self.supcon_head(feat), dim=1)

        return {"logits": logits, "emb": graph_emb, "proj": proj}

# ==============================================================================
# 3. DATA LOADING (Simplified for Cache)
# ==============================================================================

class CachedDevignDataset(Dataset):
    def __init__(self, root, dataset_name, split, signature):
        super().__init__()
        # Construct path: root / dataset_name / split / sig / objects
        self.root_dir = Path(root) / dataset_name / split / signature / "objects"
        
        log(f"[Dataset] Looking for data in: {self.root_dir}")
        
        if not self.root_dir.exists():
            raise RuntimeError(f"Cache dir not found: {self.root_dir}")
            
        self.files = sorted(list(self.root_dir.rglob("*.pt")))
        log(f"[Dataset] Loaded {len(self.files)} graphs for split {split}")

    def len(self):
        return len(self.files)

    def get(self, idx):
        try:
            data = torch.load(self.files[idx], map_location="cpu")
            return data
        except Exception as e:
            log(f"Error loading {self.files[idx]}: {e}")
            return Data(x=torch.zeros(1, 1), edge_index=torch.zeros(2, 0, dtype=torch.long), y=torch.tensor([0]))

# ==============================================================================
# 4. TRAINING LOOP (With Diagnostics)
# ==============================================================================

def train_epoch(model, loader, optimizer, device, scaler):
    model.train()
    total_loss = 0
    
    loss_fn = nn.BCEWithLogitsLoss(pos_weight=torch.tensor([1.0], device=device))
    
    # Wrap loader in tqdm but write to our logger
    pbar = tqdm(loader, desc="Training")
    for batch in pbar:
        batch = batch.to(device)
        optimizer.zero_grad()
        
        with torch.cuda.amp.autocast():
            out = model(batch)
            logits = out["logits"]
            
            if logits.size(1) == 2:
                delta = logits[:, 1] - logits[:, 0]
            else:
                delta = logits.squeeze(1)
                
            loss = loss_fn(delta, batch.y.float())

        scaler.scale(loss).backward()
        scaler.step(optimizer)
        scaler.update()
        
        total_loss += loss.item()
        
    return total_loss / len(loader)

def evaluate(model, loader, device):
    model.eval()
    all_probs = []
    all_labels = []
    
    with torch.no_grad():
        for batch in tqdm(loader, desc="Evaluating"):
            batch = batch.to(device)
            out = model(batch)
            logits = out["logits"]
            
            if logits.size(1) == 2:
                delta = logits[:, 1] - logits[:, 0]
            else:
                delta = logits.squeeze(1)
            
            probs = torch.sigmoid(delta).cpu().numpy()
            labels = batch.y.cpu().numpy()
            
            all_probs.extend(probs)
            all_labels.extend(labels)
            
    return np.array(all_labels), np.array(all_probs)

# ==============================================================================
# 5. MAIN
# ==============================================================================

def main():
    # --- CONFIGURATION (EDIT THESE IF NEEDED) ---
    # Path to the CLEAN V4 cache (restored topology)
    CACHE_ROOT = "./Clean_exports/cache_devign_v4" 
    DATASET_NAME = "devign_normfunc"
    
    # The signature from your V4 build
    # If you don't know it, run: ls ./Clean_exports/cache_devign_v4/devign_normfunc/train/
    SIGNATURE = "7033bf97f7eb49f0" 
    
    BATCH_SIZE = 64
    LR = 0.0005
    HIDDEN_DIM = 256
    INPUT_DIM = 796
    
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    log(f"[Init] Using device: {device}")
    log(f"[Init] Cache Root: {CACHE_ROOT}")
    log(f"[Init] Signature: {SIGNATURE}")
    
    # Load Data
    try:
        train_ds = CachedDevignDataset(CACHE_ROOT, DATASET_NAME, "train", SIGNATURE)
        val_ds = CachedDevignDataset(CACHE_ROOT, DATASET_NAME, "valid", SIGNATURE)
        test_ds = CachedDevignDataset(CACHE_ROOT, DATASET_NAME, "test", SIGNATURE)
    except RuntimeError as e:
        log(f"[FATAL] {e}")
        return

    train_loader = DataLoader(train_ds, batch_size=BATCH_SIZE, shuffle=True, num_workers=4)
    test_loader = DataLoader(test_ds, batch_size=BATCH_SIZE, shuffle=False, num_workers=4)
    
    # Init Model
    model = DevignNet(input_dim=INPUT_DIM, hidden_dim=HIDDEN_DIM, out_dim=2).to(device)
    optimizer = optim.AdamW(model.parameters(), lr=LR, weight_decay=1e-4)
    scaler = torch.cuda.amp.GradScaler()
    
    log("[Init] Model initialized. Starting Debug Run (1 Epoch)...")
    
    # Run 1 Epoch
    loss = train_epoch(model, train_loader, optimizer, device, scaler)
    log(f"\n[Result] Train Loss: {loss:.4f}")
    
    # Evaluate
    y_true, y_probs = evaluate(model, test_loader, device)
    
    auc = roc_auc_score(y_true, y_probs)
    preds = (y_probs > 0.5).astype(int)
    f1 = f1_score(y_true, preds)
    rec = recall_score(y_true, preds)
    prec = precision_score(y_true, preds)
    
    log("\n" + "="*40)
    log(f"DEBUG METRICS (Thr=0.5):")
    log(f"AUC: {auc:.4f}")
    log(f"F1:  {f1:.4f}")
    log(f"Rec: {rec:.4f}")
    log(f"Prec:{prec:.4f}")
    log("="*40)
    log(f"Full log saved to debug_mptcn.log")

if __name__ == "__main__":
    main()
