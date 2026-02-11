checktag (int tag)
{
  if (!(L->last_tag <= tag && tag <= 0))
    luaL_verror("%d is not a valid tag", tag);
}
