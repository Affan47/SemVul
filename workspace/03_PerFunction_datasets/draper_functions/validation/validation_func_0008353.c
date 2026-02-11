FillValues_(Index n_entries, const ExpansionMatrix& matrix, Number* values)
  {
    DBG_ASSERT(n_entries == matrix.NCols());
    for (Index i=0; i<n_entries; i++) {
      values[i] = 1.0;
    }
  }
