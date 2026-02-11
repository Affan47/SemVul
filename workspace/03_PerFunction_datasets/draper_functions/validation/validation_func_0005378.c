new_from_values (const gchar * name, const gchar * nick, gint value)
{
  GladeStockItem *new_gsi = NULL;
  gchar *clean_name;
  size_t len = 0;
  guint i = 0;
  guint j = 0;

  new_gsi = (GladeStockItem *) g_malloc0 (sizeof (GladeStockItem));

  new_gsi->value_name = g_strdup (name);
  new_gsi->value_nick = g_strdup (nick);
  new_gsi->value = value;


  clean_name = g_strdup (name);
  len = strlen (clean_name);

  while (i + j <= len)
    {
      if (clean_name[i + j] == '_')
        j++;

      clean_name[i] = clean_name[i + j];
      i++;
    }

  new_gsi->clean_name = g_utf8_collate_key (clean_name, i - j);

  g_free (clean_name);

  return new_gsi;
}
