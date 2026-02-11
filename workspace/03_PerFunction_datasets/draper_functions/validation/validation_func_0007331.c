gconf_sources_sync_all    (GConfSources* sources, GError** err)
{
  GList* tmp;
  gboolean failed = FALSE;
  GError* all_errors = NULL;

  tmp = sources->sources;

  while (tmp != NULL)
    {
      GConfSource* src = tmp->data;
      GError* error = NULL;

      if (!gconf_source_sync_all(src, &error))
        {
          failed = TRUE;
          g_assert(error != NULL);
        }


      if (error != NULL)
        {
          if (err)
            all_errors = gconf_compose_errors(all_errors, error);

          g_error_free(error);
        }

      tmp = g_list_next(tmp);
    }

  if (err)
    {
      g_return_val_if_fail(*err == NULL, !failed);
      *err = all_errors;
    }

  return !failed;
}
