ephy_string_collate_key_for_domain (const char *str,
                                    gssize      len)
{
  GString *result;
  const char *dot;
  gssize newlen;

  if (len < 0)
    len = strlen (str);

  result = g_string_sized_new (len + 6 * strlen (COLLATION_SENTINEL));


  while ((dot = g_strrstr_len (str, len, ".")) != NULL) {
    newlen = dot - str;

    g_string_append_len (result, dot + 1, len - newlen - 1);
    g_string_append (result, COLLATION_SENTINEL);

    len = newlen;
  }

  if (len > 0)
    g_string_append_len (result, str, len);

  return g_string_free (result, FALSE);
}
