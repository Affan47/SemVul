polkit_details_get_keys (PolkitDetails *details)
{
  GList *keys, *l;
  gchar **ret;
  guint n;

  g_return_val_if_fail (POLKIT_IS_DETAILS (details), NULL);

  if (details->hash == NULL)
    return NULL;

  keys = g_hash_table_get_keys (details->hash);
  ret = g_new0 (gchar*, g_list_length (keys) + 1);
  for (l = keys, n = 0; l != NULL; l = l->next, n++)
    ret[n] = g_strdup (l->data);

  g_list_free (keys);

  return ret;
}
