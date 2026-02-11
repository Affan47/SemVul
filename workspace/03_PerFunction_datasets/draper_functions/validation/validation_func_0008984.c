gt_SRLCompact(struct seqRangeList *rangeList)
{
  gt_assert(rangeList);
  rangeList->ranges = gt_realloc(rangeList->ranges,
                                 sizeof (rangeList->ranges[0])
                                 * rangeList->numRanges);
  if (rangeList->partialSymSums)
    rangeList->partialSymSums =
      gt_realloc(rangeList->partialSymSums, sizeof (unsigned long)
                 * gt_MRAEncGetSize(rangeList->alphabet)
                 * rangeList->numRanges);
  rangeList->numRangesStorable = rangeList->numRanges;
}
