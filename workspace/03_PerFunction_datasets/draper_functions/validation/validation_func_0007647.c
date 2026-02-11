backtrace_path_end_cutoffs_are_set(const GthBacktracePath *bp)
{
  gt_assert(bp);
  if (bp->cutoffs.end.genomiccutoff   ||
      bp->cutoffs.end.referencecutoff ||
      bp->cutoffs.end.eopcutoff) {
    return true;
  }
  return false;
}
