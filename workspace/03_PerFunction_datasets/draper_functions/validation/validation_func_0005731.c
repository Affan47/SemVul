gt_reads2twobit_tbe_flush_and_realloc(GtReads2Twobit *r2t,
    GtReads2TwobitEncodeState *state)
{
  if (state->current.codepos > 0)
  {
    unsigned long shift = (GT_UNITSIN2BITENC - state->current.codepos) << 1UL;
    *(state->current.tbe_next++) =
      (GtTwobitencoding)(state->current.kmercode << shift);
  }
  if (state->current.nofseqs > 0)
  {
    gt_log_log("realloc tbe, total_seqlength=%lu", r2t->total_seqlength);
    r2t->twobitencoding = gt_realloc(r2t->twobitencoding,
        sizeof (*r2t->twobitencoding) *
        (GT_DIVBYUNITSIN2BITENC(r2t->total_seqlength) + 2UL));
  }
  else
  {
    gt_free(r2t->twobitencoding);
    r2t->twobitencoding = NULL;
  }
}
