get_string_nofail (GITypelib *typelib, guint32 offset)
{
  const char *ret = get_string (typelib, offset, NULL);
  g_assert (ret);
  return ret;
}
