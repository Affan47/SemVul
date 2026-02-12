_ppdCacheGetBin(
    _ppd_cache_t *pc,
    const char   *output_bin)
{
  int	i;


  if (!pc || !output_bin)
    return (NULL);


  for (i = 0; i < pc->num_bins; i ++)
    if (!_cups_strcasecmp(output_bin, pc->bins[i].ppd))
      return (pc->bins[i].pwg);

  return (NULL);
}
