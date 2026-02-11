gconf_database_set_schema (GConfDatabase  *db,
                           const gchar    *key,
                           const gchar    *schema_key,
                           GError        **err)
{
  g_return_if_fail (err == NULL || *err == NULL);
  g_assert (db->listeners != NULL);

  db->last_access = time (NULL);

  gconf_sources_set_schema (db->sources, key, schema_key, err);

  if (err && *err != NULL)
    {
      gconf_log (GCL_ERR, _("Error setting schema for `%s': %s"),
                key, (*err)->message);
    }
  else
    {
      gconf_database_schedule_sync (db);
    }
}
