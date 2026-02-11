gst_multi_file_sink_stop (GstBaseSink * sink)
{
  GstMultiFileSink *multifilesink;
  int i;

  multifilesink = GST_MULTI_FILE_SINK (sink);

  if (multifilesink->file != NULL) {
    fclose (multifilesink->file);
    multifilesink->file = NULL;
  }

  if (multifilesink->streamheaders) {
    for (i = 0; i < multifilesink->n_streamheaders; i++) {
      gst_buffer_unref (multifilesink->streamheaders[i]);
    }
    g_free (multifilesink->streamheaders);
    multifilesink->streamheaders = NULL;
  }

  multifilesink->force_key_unit_count = -1;

  return TRUE;
}
