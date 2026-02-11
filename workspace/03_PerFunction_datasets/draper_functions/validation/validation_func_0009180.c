enca_pair_analyse(EncaAnalyserState *analyser)
{
  const unsigned char *const *letters = analyser->lang->letters;
  const unsigned char **const *pairs = analyser->lang->pairs;
  size_t ncharsets = analyser->ncharsets;
  size_t i, best, all8bitpairs;
  double q;

  if (!letters || !pairs)
    return 0;

  if (!analyser->pairratings)
    analyser->pairratings = NEW(size_t, ncharsets);


  if (!analyser->pair2bits) {
    compute_pair2bits(analyser);
    analyser->bitcounts = NEW(size_t, 1 << ncharsets);
  }
  memset(analyser->pairratings, 0, ncharsets*sizeof(size_t));
  all8bitpairs = count_all_8bit_pairs(analyser);
  count_good_pairs(analyser);

  best = 0;
  for (i = 1; i < ncharsets; i++) {
    if (analyser->pairratings[i] > analyser->pairratings[best])
      best = i;
  }


  q = 1.0 - exp(3.0*(1.0 - analyser->options.threshold));
  if (analyser->pairratings[best] >= analyser->options.min_chars
      && analyser->pairratings[best] >= q*all8bitpairs) {
    analyser->result.charset = analyser->charsets[best];
    return 1;
  }


  return 0;
}
