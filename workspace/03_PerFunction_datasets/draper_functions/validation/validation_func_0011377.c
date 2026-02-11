FinalizeTokenProbas(VP8EncProba* const proba) {
  int has_changed = 0;
  int size = 0;
  int t, b, c, p;
  for (t = 0; t < NUM_TYPES; ++t) {
    for (b = 0; b < NUM_BANDS; ++b) {
      for (c = 0; c < NUM_CTX; ++c) {
        for (p = 0; p < NUM_PROBAS; ++p) {
          const proba_t stats = proba->stats_[t][b][c][p];
          const int nb = (stats >> 0) & 0xffff;
          const int total = (stats >> 16) & 0xffff;
          const int update_proba = VP8CoeffsUpdateProba[t][b][c][p];
          const int old_p = VP8CoeffsProba0[t][b][c][p];
          const int new_p = CalcTokenProba(nb, total);
          const int old_cost = BranchCost(nb, total, old_p)
                             + VP8BitCost(0, update_proba);
          const int new_cost = BranchCost(nb, total, new_p)
                             + VP8BitCost(1, update_proba)
                             + 8 * 256;
          const int use_new_p = (old_cost > new_cost);
          size += VP8BitCost(use_new_p, update_proba);
          if (use_new_p) {
            proba->coeffs_[t][b][c][p] = new_p;
            has_changed |= (new_p != old_p);
            size += 8 * 256;
          } else {
            proba->coeffs_[t][b][c][p] = old_p;
          }
        }
      }
    }
  }
  proba->dirty_ = has_changed;
  return size;
}
