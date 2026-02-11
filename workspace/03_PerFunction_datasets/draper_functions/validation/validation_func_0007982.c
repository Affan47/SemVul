gconf_key_directory  (const gchar* key)
{
  const gchar* end;
  gchar* retval;
  int len;

  end = strrchr(key, '/');

  if (end == NULL)
    {
      gconf_log(GCL_ERR, _("No '/' in key \"%s\""), key);
      return NULL;
    }

  len = end-key+1;

  if (len == 1)
    {

      retval = g_strdup("/");
    }
  else
    {
      retval = g_malloc(len);

      strncpy(retval, key, len);

      retval[len-1] = '\0';
    }

  return retval;
}
