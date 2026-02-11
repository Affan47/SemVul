gconf_settings_backend_find_notifier_or_parent (GConfSettingsBackend *gconf,
                                                const gchar          *path)
{
  GConfSettingsBackendNotifier *parent;
  GSList *l;

  l = gconf->priv->notifiers;
  parent = NULL;

  while (l != NULL)
    {
      GConfSettingsBackendNotifier *notifier;
      notifier = l->data;
      if (g_str_equal (path, notifier->path))
        return notifier;
      if (g_str_has_prefix (path, notifier->path))
        {
          parent = notifier;
          l = parent->subpaths;
          continue;
        }
      if (g_str_has_prefix (notifier->path, path))
        break;

      l = l->next;
    }

  return parent;
}
