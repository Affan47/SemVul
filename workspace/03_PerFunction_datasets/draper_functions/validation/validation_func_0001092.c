default_app_changed (GtkAppChooserButton *button,
                     CcInfoPanel         *self)
{
  GAppInfo *info;
  GError *error = NULL;
  DefaultAppData *app_data;
  int i;

  info = gtk_app_chooser_get_app_info (GTK_APP_CHOOSER (button));
  app_data = g_object_get_data (G_OBJECT (button), "cc-default-app-data");

  if (g_app_info_set_as_default_for_type (info, app_data->content_type, &error) == FALSE)
    {
      g_warning ("Failed to set '%s' as the default application for '%s': %s",
                 g_app_info_get_name (info), app_data->content_type, error->message);
      g_error_free (error);
      error = NULL;
    }

  if (app_data->extra_type_filter)
    {
      const char *const *mime_types;
      GPatternSpec *pattern;

      pattern = g_pattern_spec_new (app_data->extra_type_filter);
      mime_types = g_app_info_get_supported_types (info);

      for (i = 0; mime_types[i]; i++)
        {
          if (!g_pattern_match_string (pattern, mime_types[i]))
            continue;

          if (g_app_info_set_as_default_for_type (info, mime_types[i], &error) == FALSE)
            {
              g_warning ("Failed to set '%s' as the default application for secondary "
                         "content type '%s': %s",
                         g_app_info_get_name (info), mime_types[i], error->message);
              g_error_free (error);
            }
        }

      g_pattern_spec_free (pattern);
    }

  g_object_unref (info);
}
