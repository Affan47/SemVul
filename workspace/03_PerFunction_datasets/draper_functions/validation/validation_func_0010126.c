gsasl_property_set_raw (Gsasl_session * sctx, Gsasl_property prop,
			const char *data, size_t len)
{
  char **p = map (sctx, prop);

  if (p)
    {
      free (*p);
      if (data)
	{
	  *p = malloc (len + 1);
	  if (*p)
	    {
	      memcpy (*p, data, len);
	      (*p)[len] = '\0';
	    }
	}
      else
	*p = NULL;
    }
}
