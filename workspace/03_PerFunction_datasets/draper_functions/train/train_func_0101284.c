got_file_size_cb (GObject *source_object,
                   GAsyncResult *res,
                   gpointer userdata)
{
  SwClientServiceCallClosure *closure = (SwClientServiceCallClosure *) userdata;
  SwClientServicePrivate *priv = GET_PRIVATE (closure->service);
  GFileInfo *info;
  char *filename;
  const char *signal;

  info = g_file_query_info_finish (G_FILE (source_object), res, NULL);
  if (info == NULL ||
      g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_STANDARD_TYPE) != G_FILE_TYPE_REGULAR) {
    g_simple_async_report_error_in_idle (G_OBJECT (closure->service),
                                         (GAsyncReadyCallback) closure->cb,
                                         closure->userdata,
                                         SW_CLIENT_SERVICE_ERROR,
                                         0,
					 "%s",
                                         info ? "File to upload is not a regular file" :
                                         "Could not get file size information for file");
    if (info)
      g_object_unref (info);
    g_object_unref (closure->service);
    g_hash_table_unref (closure->fields);
    g_slice_free (SwClientServiceCallClosure, closure);
    return;
  }

  closure->filesize = g_file_info_get_attribute_uint64 (info,
                                                        G_FILE_ATTRIBUTE_STANDARD_SIZE);
  g_object_unref (info);

  signal = (closure->iface == PHOTO_UPLOAD_IFACE ? "PhotoUploadProgress" : "VideoUploadProgress");
  dbus_g_proxy_connect_signal (priv->proxies[closure->iface], signal,
                               G_CALLBACK (_upload_file_progress_cb), closure, NULL);

  filename = g_file_get_path (G_FILE (source_object));
  if (closure->iface == PHOTO_UPLOAD_IFACE) {
    com_meego_libsocialweb_PhotoUpload_upload_photo_async (priv->proxies[PHOTO_UPLOAD_IFACE],
                                                           filename,
                                                           closure->fields,
                                                           _upload_file_cb,
                                                           closure);
  } else {
    com_meego_libsocialweb_VideoUpload_upload_video_async (priv->proxies[VIDEO_UPLOAD_IFACE],
                                                           filename,
                                                           closure->fields,
                                                           _upload_file_cb,
                                                           closure);
  }
  g_hash_table_unref (closure->fields);
  closure->fields = NULL;

  g_free (filename);
}
