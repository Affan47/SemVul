processbranchingedge_spmvar(GT_UNUSED bool firstsucc,
    unsigned long fatherdepth,
    GT_UNUSED GtBUinfo_spmvar *afather, GT_UNUSED unsigned long sondepth,
    GT_UNUSED unsigned long sonwidth,
    GT_UNUSED GtBUinfo_spmvar *ason, GT_UNUSED GtBUstate_spmvar *state,
    GT_UNUSED GtError *err)
{
  if (fatherdepth < state->minmatchlength)
  {
#ifdef GT_READJOINER_STATISTICS
    reset_subtree_stats(state);
#endif
    state->w_nextfree = 0;
  }
  return 0;
}
