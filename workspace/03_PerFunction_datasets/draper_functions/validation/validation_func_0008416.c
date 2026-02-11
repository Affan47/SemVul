Threshold(RNScalar threshold, RNScalar low, RNScalar high)
{

  RNScalar *grid_valuep = grid_values;
  for (int i = 0; i < grid_size; i++) {
    if (*grid_valuep <= threshold) {
      if (low != R3_GRID_KEEP_VALUE) *grid_valuep = low;
    }
    else {
      if (high != R3_GRID_KEEP_VALUE) *grid_valuep = high;
    }
    grid_valuep++;
  }
}
