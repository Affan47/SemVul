gt_match_get_range_seq1(const GtMatch *match, GtRange *range)
{
  gt_assert(match && range);
  range->start = match->range_seq1.start;
  range->end = match->range_seq1.end;
}
