DELETE_MAP_real_to_virtual(DELETE_MAP *dmap, int rpos)
{
  DELETE_SLOT *slot = (DELETE_SLOT *)dmap;
  int vpos = rpos;

  while (slot)
  {
    if (rpos < slot->start)
      break;
    if (rpos < (slot->start + slot->length))
      return (-1);
    vpos -= slot->length;
    slot = slot->next;
  }

  #ifdef DEBUG_ME
  printf("DELETE_MAP_real_to_virtual: %ld => %ld\n", rpos, vpos);
  #endif

  return vpos;
}
