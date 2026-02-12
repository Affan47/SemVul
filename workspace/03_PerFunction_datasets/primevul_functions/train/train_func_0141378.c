_ppdCacheGetSource(
    _ppd_cache_t *pc,
    const char   *input_slot)
{
  int		i;
  pwg_map_t	*source;


  if (!pc || !input_slot)
    return (NULL);

  for (i = pc->num_sources, source = pc->sources; i > 0; i --, source ++)
    if (!_cups_strcasecmp(input_slot, source->ppd))
      return (source->pwg);

  return (NULL);
}
