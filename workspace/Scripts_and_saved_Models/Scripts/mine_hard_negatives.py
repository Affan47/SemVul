import pandas as pd
import csv
import argparse

def mine():
    parser = argparse.ArgumentParser()
    parser.add_argument("--preds", type=str, required=True, help="Path to train_mining_analysis.csv")
    parser.add_argument("--manifest", type=str, required=True, help="Path to original manifest_train.csv")
    parser.add_argument("--output", type=str, default="manifest_train_hard.csv")
    args = parser.parse_args()

    print("Loading data...")
    preds = pd.read_csv(args.preds)
    
    # Load original manifest to preserve all columns (path, project, etc.)
    # We assume 'function_id' or 'filename' matches the ID in predictions
    orig_df = pd.read_csv(args.manifest)
    
    # Ensure IDs match (strip extensions if needed)
    # Adjust 'function_id' column name if your manifest uses 'filename' or 'id'
    id_col = 'function_id' if 'function_id' in orig_df.columns else 'filename'
    
    # Merge predictions into manifest
    # We assume preds has 'function_id'
    merged = orig_df.merge(preds[['function_id', 'probability']], left_on=id_col, right_on='function_id', how='inner')

    print(f"Original Training Size: {len(merged)}")

    # 1. Select ALL Positives (Label == 1)
    positives = merged[merged['label'] == 1]
    print(f"Positives (Keep All): {len(positives)}")

    # 2. Identify Negatives (Label == 0)
    negatives = merged[merged['label'] == 0]
    
    # 3. Find HARD Negatives (Safe but model thinks Prob > 0.20)
    # We use a low threshold to catch anything even slightly confusing
    hard_negatives = negatives[negatives['probability'] > 0.20]
    print(f"Hard Negatives (Keep All): {len(hard_negatives)}")
    
    # 4. Find EASY Negatives (Safe and model correctly says Prob <= 0.20)
    easy_negatives = negatives[negatives['probability'] <= 0.20]
    
    # 5. Sample Easy Negatives (Keep only 10% to reduce noise)
    easy_sample = easy_negatives.sample(frac=0.10, random_state=42)
    print(f"Easy Negatives (Sampled 10%): {len(easy_sample)}")

    # Combine
    final_df = pd.concat([positives, hard_negatives, easy_sample])
    
    # Shuffle
    final_df = final_df.sample(frac=1, random_state=42).reset_index(drop=True)
    
    # Save
    # We drop the extra columns added by inference (probability, function_id_y) 
    # to match original manifest format
    cols_to_save = orig_df.columns
    final_df[cols_to_save].to_csv(args.output, index=False)
    
    print(f"\n[Success] Created {args.output} with {len(final_df)} samples.")
    print(f"New Class Balance: {len(positives)} Pos / {len(hard_negatives)+len(easy_sample)} Neg")

if __name__ == "__main__":
    mine()



"""

python mine_hard_negatives.py \
  --preds "train_mining_v2.csv" \
  --manifest "./workspace/03_PerFunction_datasets/normalized_devign_functions/normalized_devign_functions/manifest_train.csv" \
  --output "manifest_train_hard_v2.csv"

"""

