processlcpinterval_spmvar(unsigned long lcp,
    GtBUinfo_spmvar *info, GtBUstate_spmvar *state, GT_UNUSED GtError *err)
{
  if (lcp >= state->minmatchlength)
  {
    unsigned long i;
    for (i = 0; i < state->l_nextfree; i++)
    {
      combine_terminal_with_wset(state->l_set[i],
          gt_encseq_seqstartpos(state->encseq, state->l_set[i]),
          gt_encseq_seqlength(state->encseq, state->l_set[i]), info->w_left,
          lcp, state);
    }
    state->l_nextfree = 0;
  }
  return 0;
}
