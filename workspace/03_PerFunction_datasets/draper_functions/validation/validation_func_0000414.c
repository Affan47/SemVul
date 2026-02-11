_state_changed (FsStreamTransmitter *stream_transmitter,
    guint component,
    FsStreamState state,
    gpointer user_data)
{
  FsRtpStream *self = FS_RTP_STREAM (user_data);
  FsRtpSession *session = fs_rtp_stream_get_session (self, NULL);
  GstElement *conf = NULL;

  if (!session)
    return;

  g_object_get (session, "conference", &conf, NULL);

  gst_element_post_message (conf,
      gst_message_new_element (GST_OBJECT (conf),
          gst_structure_new ("farstream-component-state-changed",
              "stream", FS_TYPE_STREAM, self,
              "component", G_TYPE_UINT, component,
              "state", FS_TYPE_STREAM_STATE, state,
              NULL)));

  gst_object_unref (conf);
  g_object_unref (session);

  if (component == 1 && state == FS_STREAM_STATE_FAILED)
    fs_stream_emit_error (FS_STREAM (self), FS_ERROR_CONNECTION_FAILED,
        "Could not establish connection on the RTP component");
}
