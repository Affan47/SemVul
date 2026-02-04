import pandas as pd
import numpy as np
from sklearn.metrics import (
    accuracy_score, 
    precision_score, 
    recall_score, 
    f1_score, 
    roc_auc_score, 
    confusion_matrix, 
    classification_report
)
import argparse

def analyze():
    parser = argparse.ArgumentParser()
    parser.add_argument("--csv", type=str, default="test_results_analysis.csv", help="Path to results CSV")
    args = parser.parse_args()

    # 1. Load Data
    print(f"Loading {args.csv}...")
    try:
        df = pd.read_csv(args.csv)
    except FileNotFoundError:
        print("Error: CSV file not found. Check the path.")
        return

    y_true = df["ground_truth"]
    y_pred = df["prediction"]
    y_prob = df["probability"]

    # 2. Calculate Metrics
    acc = accuracy_score(y_true, y_pred)
    prec = precision_score(y_true, y_pred)
    rec = recall_score(y_true, y_pred)
    f1 = f1_score(y_true, y_pred)
    auc = roc_auc_score(y_true, y_prob)

    # 3. Confusion Matrix
    tn, fp, fn, tp = confusion_matrix(y_true, y_pred).ravel()

    print("\n" + "="*60)
    print("FINAL PERFORMANCE METRICS")
    print("="*60)
    print(f"threshold used in inference: (Pre-calculated in CSV)")
    print("-" * 30)
    print(f"Accuracy:  {acc:.4f}")
    print(f"F1 Score:  {f1:.4f}")
    print(f"Precision: {prec:.4f}  (How many predicted vulnerable were actually vulnerable?)")
    print(f"Recall:    {rec:.4f}  (How many real vulnerabilities did we find?)")
    print(f"AUC:       {auc:.4f}  (Ranking ability)")
    print("-" * 30)
    print("\nCONFUSION MATRIX:")
    print(f"True Negatives (Safe correctly identified):      {tn}")
    print(f"False Positives (Safe flagged as Vuln):          {fp}  <-- High cost of auditing")
    print(f"False Negatives (Vuln missed):                   {fn}  <-- High security risk")
    print(f"True Positives (Vuln correctly identified):      {tp}")

    print("\n" + "="*60)
    print("POST-MORTEM: THRESHOLD SWEEP")
    print("="*60)
    print("What if we used a different threshold? (Calculated from probabilities)")
    print(f"{'Thr':<10} {'F1':<10} {'Prec':<10} {'Rec':<10} {'Acc':<10}")
    print("-" * 50)

    best_f1 = 0
    best_thr = 0

    # Check thresholds from 0.1 to 0.9
    for thr in np.arange(0.1, 0.95, 0.05):
        new_pred = (y_prob >= thr).astype(int)
        new_f1 = f1_score(y_true, new_pred)
        new_prec = precision_score(y_true, new_pred, zero_division=0)
        new_rec = recall_score(y_true, new_pred)
        new_acc = accuracy_score(y_true, new_pred)
        
        marker = " <--" if new_f1 > best_f1 else ""
        if new_f1 > best_f1:
            best_f1 = new_f1
            best_thr = thr
            
        print(f"{thr:.2f}      {new_f1:.4f}     {new_prec:.4f}     {new_rec:.4f}     {new_acc:.4f}{marker}")

    print("-" * 50)
    print(f"Best Theoretical Threshold on TEST set: {best_thr:.2f} (F1={best_f1:.4f})")

if __name__ == "__main__":
    analyze()


"""
python analyze_metrics.py --csv check_run_v5.csv

"""    