got_file_info (GFile *file,
               GAsyncResult *result,
               GrlSourceResolveSpec *rs)
{
  GCancellable *cancellable;
  GFileInfo *info;
  GError *error = NULL;
  const gchar *thumbnail_path;
  gboolean thumbnail_is_valid;

  GRL_DEBUG ("got_file_info");


  cancellable = grl_operation_get_data (rs->operation_id);

  g_clear_object (&cancellable);

  info = g_file_query_info_finish (file, result, &error);
  if (error)
    goto error;

  thumbnail_path =
      g_file_info_get_attribute_byte_string (info, G_FILE_ATTRIBUTE_THUMBNAIL_PATH);
#if GLIB_CHECK_VERSION (2, 39, 0)
  thumbnail_is_valid =
      g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_THUMBNAIL_IS_VALID);
#else
  thumbnail_is_valid = TRUE;
#endif


  if (thumbnail_path && thumbnail_is_valid) {
    gchar *thumbnail_uri = g_filename_to_uri (thumbnail_path, NULL, &error);
    if (error)
      goto error;

    GRL_INFO ("Got thumbnail %s for media: %s", thumbnail_uri,
              grl_media_get_url (rs->media));
    grl_media_set_thumbnail (rs->media, thumbnail_uri);
    g_free (thumbnail_uri);
  } else if (thumbnail_path && !thumbnail_is_valid) {
    GRL_INFO ("Found outdated thumbnail %s for media: %s", thumbnail_path,
              grl_media_get_url (rs->media));
  } else {
    GRL_INFO ("Could not find thumbnail for media: %s",
              grl_media_get_url (rs->media));
  }

  rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, NULL);

  goto exit;

error:
    {
      GError *new_error = g_error_new (GRL_CORE_ERROR,
                                       GRL_CORE_ERROR_RESOLVE_FAILED,
                                       _("Failed to resolve: %s"),
                                       error->message);
      rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, new_error);

      g_error_free (error);
      g_error_free (new_error);
    }

exit:
    g_clear_object (&info);
}
