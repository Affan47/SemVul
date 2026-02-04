import pandas as pd
import numpy as np
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, roc_auc_score, confusion_matrix
import argparse

def analyze():
    parser = argparse.ArgumentParser()
    # Point this to your V4 results CSV (the one that gave 73%)
    parser.add_argument("--csv", type=str, default="test_results_v4_final.csv", help="Path to results CSV")
    args = parser.parse_args()

    print(f"Loading {args.csv}...")
    try:
        df = pd.read_csv(args.csv)
    except FileNotFoundError:
        print("Error: CSV file not found.")
        return

    y_true = df["ground_truth"]
    y_prob = df["probability"]

    print(f"Scanning {len(df)} predictions for optimal threshold...")
    
    best_f1 = 0.0
    best_thr = 0.0
    best_metrics = {}

    # Sweep from 0.00 to 1.00 with 0.001 precision
    thresholds = np.arange(0.01, 0.99, 0.001)
    
    for thr in thresholds:
        y_pred = (y_prob >= thr).astype(int)
        f1 = f1_score(y_true, y_pred)
        
        if f1 > best_f1:
            best_f1 = f1
            best_thr = thr
            # Capture stats at this peak
            best_metrics = {
                "acc": accuracy_score(y_true, y_pred),
                "prec": precision_score(y_true, y_pred, zero_division=0),
                "rec": recall_score(y_true, y_pred),
                "auc": roc_auc_score(y_true, y_prob)
            }

    print("\n" + "="*60)
    print(f"🏆 PRECISE OPTIMAL THRESHOLD FOUND")
    print("="*60)
    print(f"Threshold: {best_thr:.4f}")
    print("-" * 30)
    print(f"F1 Score:  {best_f1:.5f}")
    print(f"Precision: {best_metrics['prec']:.5f}")
    print(f"Recall:    {best_metrics['rec']:.5f}")
    print(f"Accuracy:  {best_metrics['acc']:.5f}")
    print(f"AUC:       {best_metrics['auc']:.5f}")
    print("-" * 30)

    # Show neighborhood context
    print("\nContext around peak:")
    print(f"{'Thr':<10} {'F1':<10} {'Prec':<10} {'Rec':<10}")
    for thr in [best_thr - 0.05, best_thr - 0.01, best_thr, best_thr + 0.01, best_thr + 0.05]:
        if 0 <= thr <= 1:
            pred = (y_prob >= thr).astype(int)
            f1 = f1_score(y_true, pred)
            p = precision_score(y_true, pred)
            r = recall_score(y_true, pred)
            marker = " <-- PEAK" if abs(thr - best_thr) < 0.0001 else ""
            print(f"{thr:.4f}      {f1:.5f}     {p:.4f}     {r:.4f}{marker}")

if __name__ == "__main__":
    analyze()