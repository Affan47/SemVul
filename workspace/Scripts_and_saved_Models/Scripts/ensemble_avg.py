import pandas as pd
import numpy as np
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, roc_auc_score
import argparse

def ensemble():
    parser = argparse.ArgumentParser()
    parser.add_argument("--csvs", nargs="+", required=True, help="List of CSV files to ensemble")
    parser.add_argument("--output", type=str, default="ensemble_final.csv")
    args = parser.parse_args()

    print(f"Ensembling {len(args.csvs)} models...")
    
    dfs = []
    for path in args.csvs:
        try:
            df = pd.read_csv(path)
            # Sort by function_id to ensure alignment
            df = df.sort_values("function_id").reset_index(drop=True)
            dfs.append(df)
            print(f"Loaded {path}: {len(df)} rows")
        except Exception as e:
            print(f"Error loading {path}: {e}")
            return

    # Verify alignment
    base_ids = dfs[0]["function_id"]
    for i, df in enumerate(dfs[1:]):
        if not base_ids.equals(df["function_id"]):
            print(f"❌ Alignment Error: function_id mismatch in file {args.csvs[i+1]}")
            return

    # Average Probabilities
    print("Averaging probabilities...")
    avg_probs = np.zeros(len(dfs[0]))
    for df in dfs:
        avg_probs += df["probability"].values
    avg_probs /= len(dfs)

    y_true = dfs[0]["ground_truth"].values
    
    # Sweep for best threshold
    print("Scanning for optimal ensemble threshold...")
    best_f1 = 0.0
    best_thr = 0.0
    best_metrics = {}
    
    thresholds = np.arange(0.01, 0.99, 0.001)
    
    for thr in thresholds:
        y_pred = (avg_probs >= thr).astype(int)
        f1 = f1_score(y_true, y_pred)
        
        if f1 > best_f1:
            best_f1 = f1
            best_thr = thr
            best_metrics = {
                "acc": accuracy_score(y_true, y_pred),
                "prec": precision_score(y_true, y_pred, zero_division=0),
                "rec": recall_score(y_true, y_pred),
                "auc": roc_auc_score(y_true, avg_probs)
            }

    print("\n" + "="*60)
    print(f"🏆 FINAL ENSEMBLE RESULTS (Voting)")
    print("="*60)
    print(f"Optimal Threshold: {best_thr:.4f}")
    print("-" * 30)
    print(f"F1 Score:  {best_f1:.5f}")
    print(f"Precision: {best_metrics['prec']:.5f}")
    print(f"Recall:    {best_metrics['rec']:.5f}")
    print(f"Accuracy:  {best_metrics['acc']:.5f}")
    print(f"AUC:       {best_metrics['auc']:.5f}")
    print("-" * 30)
    
    # Save final predictions
    final_df = dfs[0].copy()
    final_df["probability"] = avg_probs
    final_df["prediction"] = (avg_probs >= best_thr).astype(int)
    final_df.to_csv(args.output, index=False)
    print(f"Saved final ensemble predictions to {args.output}")

if __name__ == "__main__":
    ensemble()


"""
 
 python ensemble_avg.py --csvs preds_A.csv preds_B.csv preds_C.csv --output final_submission.csv
"""   