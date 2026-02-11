gst_rtsp_watch_reset (GstRTSPWatch * watch)
{
  if (watch->readsrc) {
    g_source_remove_child_source ((GSource *) watch, watch->readsrc);
    g_source_unref (watch->readsrc);
  }
  if (watch->writesrc) {
    g_source_remove_child_source ((GSource *) watch, watch->writesrc);
    g_source_unref (watch->writesrc);
    watch->writesrc = NULL;
  }

  if (watch->conn->input_stream) {
    watch->readsrc =
        g_pollable_input_stream_create_source (G_POLLABLE_INPUT_STREAM
        (watch->conn->input_stream), NULL);
    g_source_set_callback (watch->readsrc,
        (GSourceFunc) gst_rtsp_source_dispatch_read, watch, NULL);
    g_source_add_child_source ((GSource *) watch, watch->readsrc);
  } else {
    watch->readsrc = NULL;
  }


}
