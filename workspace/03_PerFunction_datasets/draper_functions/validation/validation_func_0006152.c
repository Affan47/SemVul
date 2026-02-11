check_free (struct dl_action_result *rec)
{
  if (rec->errstring != NULL
      && strcmp (rec->errstring, "out of memory") != 0)
    {


#ifdef SHARED
      struct link_map *map = NULL;
      Dl_info info;
      if (_dl_addr (check_free, &info, &map, NULL) != 0 && map->l_ns == 0)
#endif
	free ((char *) rec->errstring);
    }
}
