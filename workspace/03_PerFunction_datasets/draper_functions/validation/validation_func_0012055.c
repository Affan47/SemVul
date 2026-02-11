afAccessAso (key, mode)
     Af_key *key;
     int    mode;
{
  if (key == NULL)
    return (ERROR);
  if (key->af_ldes == NULL)
    return (ERROR);
  if ((key->af_lpos < 0) || (key->af_lpos >= key->af_ldes->af_listlen))
    return (ERROR);

  if (mode == 0)
    return (AF_OK);

  return (afRefreshList (key->af_ldes, mode));

}
