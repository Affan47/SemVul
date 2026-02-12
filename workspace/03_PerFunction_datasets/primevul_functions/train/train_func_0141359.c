_ppdCacheGetOutputBin(
    _ppd_cache_t *pc,
    const char   *output_bin)
{
  int	i;


  if (!pc || !output_bin)
    return (NULL);


  for (i = 0; i < pc->num_bins; i ++)
    if (!_cups_strcasecmp(output_bin, pc->bins[i].pwg))
      return (pc->bins[i].ppd);

  return (NULL);
}
