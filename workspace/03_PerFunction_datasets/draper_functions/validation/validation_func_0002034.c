pick_next(SplitStruct *node, int n_entries, double *g1, double *g2,
    SplitStruct **choice, int *n_group, int n_dim)
{
  SplitStruct *cur = node;
  SplitStruct *end = node + n_entries;

  double max_diff = -DBL_MAX;

  for (; cur<end; ++cur)
  {
    double diff;
    double abs_diff;

    if (cur->n_node)
    {
      continue;
    }

    diff = mbr_join_square(g1, cur->coords, n_dim) -
      mbr_join_square(g2, cur->coords, n_dim);

    abs_diff = fabs(diff);
    if (abs_diff  > max_diff)
    {
      max_diff = abs_diff;
      *n_group = 1 + (diff > 0);
      *choice = cur;
    }
  }
}
