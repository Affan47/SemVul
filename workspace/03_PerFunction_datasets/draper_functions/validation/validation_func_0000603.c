_gsasl_obsolete_property_map (Gsasl_session * sctx, Gsasl_property prop)
{
  const char *ret;
  char *buf;

  buf = malloc (BUFSIZ);
  if (!buf)
    return NULL;

  ret = pmap (sctx, prop, buf, BUFSIZ - 1);

  free (buf);

  return ret;
}
