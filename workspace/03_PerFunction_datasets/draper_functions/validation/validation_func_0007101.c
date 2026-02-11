gt_ranges_do_not_overlap(const GtArray *ranges)
{
  unsigned long i;

  gt_assert(ranges && gt_array_size(ranges));

  for (i = 1; i < gt_array_size(ranges); i++) {
    if (gt_range_overlap(gt_array_get(ranges, i-1), gt_array_get(ranges, i)))
      return false;
  }
  return true;
}
