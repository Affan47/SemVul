gt_interval_tree_find_first_overlapping(GtIntervalTree *it,
                                                            unsigned long low,
                                                            unsigned long high)
{
  gt_assert(it);
  if (it->root == it->nil)
    return NULL;
  return interval_tree_search_internal(it, it->root, low, high);
}
