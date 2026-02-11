terminal_app_delete_profile (TerminalApp *app,
                             TerminalProfile *profile)
{
  GHashTableIter iter;
  GSList *name_list;
  const char *name, *profile_name;
  char *gconf_dir;
  GError *error = NULL;
  const char **nameptr = &name;

  profile_name = terminal_profile_get_property_string (profile, TERMINAL_PROFILE_NAME);
  gconf_dir = gconf_concat_dir_and_key (CONF_PREFIX "/profiles", profile_name);

  name_list = NULL;
  g_hash_table_iter_init (&iter, app->profiles);
  while (g_hash_table_iter_next (&iter, (gpointer *) nameptr, NULL))
    {
      if (strcmp (name, profile_name) == 0)
        continue;

      name_list = g_slist_prepend (name_list, g_strdup (name));
    }

  gconf_client_set_list (app->conf,
                         CONF_GLOBAL_PREFIX"/profile_list",
                         GCONF_VALUE_STRING,
                         name_list,
                         NULL);

  g_slist_foreach (name_list, (GFunc) g_free, NULL);
  g_slist_free (name_list);


  if (!gconf_client_recursive_unset (app->conf, gconf_dir, GCONF_UNSET_INCLUDING_SCHEMA_NAMES, &error))
    {
      g_warning ("Failed to recursively unset %s: %s\n", gconf_dir, error->message);
      g_error_free (error);
    }

  g_free (gconf_dir);
}
