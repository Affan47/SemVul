get_path_from_GNUNET_PREFIX ()
{
  const char *p;

  p = getenv ("GNUNET_PREFIX");
  if (p != NULL)
    return GNUNET_strdup (p);
  return NULL;
}
