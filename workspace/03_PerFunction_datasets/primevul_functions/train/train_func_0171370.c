bool Ordered_key::lookup()
{
  DBUG_ASSERT(key_buff_elements);

  ha_rows lo= 0;
  ha_rows hi= key_buff_elements - 1;
  ha_rows mid;
  int cmp_res;

  while (lo <= hi)
  {
    mid= lo + (hi - lo) / 2;
    cmp_res= cmp_key_with_search_key(key_buff[mid]);


    if (!cmp_res && mid > 0)
      cmp_res= !cmp_key_with_search_key(key_buff[mid - 1]) ? 1 : 0;

    if (cmp_res == -1)
    {

      lo= mid + 1;
    }
    else if (cmp_res == 1)
    {

      if (!mid)
        goto not_found;
      hi= mid - 1;
    }
    else
    {

      cur_key_idx= mid;
      return TRUE;
    }
  }
not_found:
  cur_key_idx= HA_POS_ERROR;
  return FALSE;
}
