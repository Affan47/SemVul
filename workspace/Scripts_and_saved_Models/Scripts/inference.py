import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import RGCNConv, global_max_pool, global_mean_pool, JumpingKnowledge
from torch_geometric.loader import DataLoader
from torch_geometric.data import Batch
import pandas as pd
import argparse
import sys
import os
from tqdm import tqdm

# ==============================================================================
# 1. MODEL DEFINITIONS (Matches V5 Gated Fusion Architecture)
# ==============================================================================

class GatedNodeFusion(nn.Module):
    """
    Splits the concatenated input [OneHot | CodeBERT] and fuses them dynamically.
    Matches the training architecture.
    """
    def __init__(self, total_dim, hidden_dim, one_hot_dim):
        super().__init__()
        self.one_hot_dim = one_hot_dim
        self.emb_dim = total_dim - one_hot_dim
        
        # Independent projections with BN
        self.proj_type = nn.Sequential(
            nn.Linear(self.one_hot_dim, hidden_dim),
            nn.BatchNorm1d(hidden_dim),
            nn.ReLU()
        )
        self.proj_code = nn.Sequential(
            nn.Linear(self.emb_dim, hidden_dim),
            nn.BatchNorm1d(hidden_dim),
            nn.ReLU()
        )

        # Gating Mechanism
        self.gate_net = nn.Sequential(
            nn.Linear(hidden_dim * 2, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, 1),
            nn.Sigmoid()
        )

    def forward(self, x):
        # Safety check
        if x.shape[1] != (self.one_hot_dim + self.emb_dim):
            # Fallback for pure embeddings
            return self.proj_code(x[:, -self.emb_dim:])

        x_type = x[:, :self.one_hot_dim]
        x_code = x[:, self.one_hot_dim:]

        h_type = self.proj_type(x_type)
        h_code = self.proj_code(x_code)

        gate_input = torch.cat([h_type, h_code], dim=1)
        alpha = self.gate_net(gate_input) 

        h_fused = (alpha * h_code) + ((1 - alpha) * h_type)
        return h_fused

class JKPoolingHead(nn.Module):
    def __init__(self, input_dim):
        super().__init__()
        self.input_dim = input_dim

    def forward(self, x, batch):
        h_max = global_max_pool(x, batch)
        h_mean = global_mean_pool(x, batch)
        return torch.cat([h_max, h_mean], dim=1)

class RgcnResBackbone(nn.Module):
    def __init__(self, input_dim: int, hidden_dim: int, layers: int = 8, num_relations: int = 5, dropout: float = 0.2, num_node_types=28):
        super().__init__()
        self.layers = int(layers)
        self.dropout = dropout
        self.convs = nn.ModuleList()
        self.bns = nn.ModuleList()
        self.norms = nn.ModuleList()
        
        # USE GATED FUSION
        self.input_proj = GatedNodeFusion(
            total_dim=input_dim, 
            hidden_dim=hidden_dim, 
            one_hot_dim=num_node_types
        )

        for _ in range(layers):
            self.convs.append(RGCNConv(hidden_dim, hidden_dim, num_relations=num_relations))
            self.bns.append(nn.BatchNorm1d(hidden_dim))
            self.norms.append(nn.LayerNorm(hidden_dim))

        self.jk = JumpingKnowledge(mode='cat')

    def forward(self, x, edge_index, edge_type):
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
            x = self.norms[i](x)
            xs.append(x)

        x_final = self.jk(xs)
        return x_final

class DevignNet(nn.Module):
    def __init__(self, input_dim, hidden_dim, out_dim, steps=8, dropout=0.2, num_relations=5, num_node_tokens=28, **kwargs):
        super().__init__()
        
        self.backbone = RgcnResBackbone(
            input_dim=int(input_dim),
            hidden_dim=int(hidden_dim),
            layers=int(steps),
            num_relations=int(num_relations),
            dropout=dropout,
            num_node_types=int(num_node_tokens)
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

        return {"logits": logits}

# ==============================================================================
# 2. UTILS
# ==============================================================================
def load_cached_dataset(cache_dir, split):
    from pathlib import Path
    import csv
    from torch.utils.data import Dataset
    
    class SimpleCachedDataset(Dataset):
        def __init__(self, root_dir):
            self.root = Path(root_dir)
            self.index_file = self.root / "meta" / "index.csv"
            if not self.index_file.exists(): raise FileNotFoundError(f"No index at {self.index_file}")
            
            self.samples = []
            with open(self.index_file, "r") as f:
                reader = csv.DictReader(f)
                for row in reader:
                    self.samples.append(row)
                    
        def __len__(self): return len(self.samples)
        
        def __getitem__(self, idx):
            info = self.samples[idx]
            pt_path = self.root / info["rel_path"]
            try:
                data = torch.load(pt_path, map_location="cpu")
                row_key = info.get("row_key", "unknown")
                func_id = row_key.split("__")[0] if "__" in row_key else row_key
                setattr(data, "func_id", func_id)
                return data
            except Exception as e:
                return None

    return SimpleCachedDataset(cache_dir)

def graph_collate(batch):
    batch = [b for b in batch if b is not None]
    if not batch: return None
    return Batch.from_data_list(batch)

# ==============================================================================
# 3. MAIN
# ==============================================================================
def run_inference():
    parser = argparse.ArgumentParser()
    parser.add_argument("--checkpoint", type=str, required=True)
    parser.add_argument("--cache-path", type=str, required=True)
    parser.add_argument("--threshold", type=float, default=0.5)
    parser.add_argument("--output", type=str, default="final_predictions.csv")
    args = parser.parse_args()

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"[Inference] Using device: {device}")

    print(f"[Inference] Loading test data from {args.cache_path}...")
    test_ds = load_cached_dataset(args.cache_path, "test")
    loader = DataLoader(test_ds, batch_size=64, shuffle=False, collate_fn=graph_collate, num_workers=4)

    print(f"[Inference] Loading model from {args.checkpoint}...")
    checkpoint = torch.load(args.checkpoint, map_location=device)
    
    hid_dim = 256
    in_dim = 796 
    
    # Standard V4/V5 vocab size is 28
    model = DevignNet(input_dim=in_dim, hidden_dim=hid_dim, out_dim=2, 
                      steps=8, dropout=0.0, num_relations=5, num_node_tokens=28).to(device)
    
    try:
        model.load_state_dict(checkpoint["model_state"])
        print("[Inference] Model weights loaded successfully.")
    except RuntimeError as e:
        print(f"[Inference] Strict load failed: {e}")
        sys.exit(1)

    model.eval()
    results = []
    
    print("[Inference] Running prediction...")
    with torch.no_grad():
        for batch in tqdm(loader):
            if batch is None: continue
            batch = batch.to(device)
            out = model(batch)
            logits = out["logits"]
            
            if logits.size(1) == 2:
                delta = logits[:, 1] - logits[:, 0]
            else:
                delta = logits.squeeze(1)
            
            probs = torch.sigmoid(delta).cpu().numpy()
            labels = batch.y.cpu().numpy()
            func_ids = batch.func_id if isinstance(batch.func_id, list) else [batch.func_id]
            
            for i in range(len(probs)):
                p = probs[i]
                pred = 1 if p >= args.threshold else 0
                results.append({
                    "function_id": func_ids[i],
                    "probability": float(p),
                    "prediction": pred,
                    "ground_truth": int(labels[i]),
                    "correct": pred == int(labels[i])
                })

    df = pd.DataFrame(results)
    df.to_csv(args.output, index=False)
    print(f"\n[Inference] Done. Results saved to {args.output}")

if __name__ == "__main__":
    run_inference()
"""




python inference.py \
  --checkpoint "./workspace/Scripts_and_saved_Models/Scripts/MPTCN_TTS_devign/devign/checkpoints/best.pt" \
  --cache-path "./Clean_exports/cache_devign_v4/devign_normfunc/train/7033bf97f7eb49f0" \
  --threshold 0.2850 \
  --output "final_submission_f1_73.csv"


  python inference.py \
  --checkpoint "./workspace/Scripts_and_saved_Models/Scripts/results_rgcn_v5_onecycle/checkpoints/best.pt" \
  --cache-path "./Clean_exports/cache_devign_v5/devign_normfunc/test/c8e3494d09f26be4" \
  --threshold 0.1316 \
  --output "testing_A"
  """


