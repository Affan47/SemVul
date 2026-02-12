_ppdCacheGetType(
    _ppd_cache_t *pc,
    const char   *media_type)
{
  int		i;
  pwg_map_t	*type;


  if (!pc || !media_type)
    return (NULL);

  for (i = pc->num_types, type = pc->types; i > 0; i --, type ++)
    if (!_cups_strcasecmp(media_type, type->ppd))
      return (type->pwg);

  return (NULL);
}
