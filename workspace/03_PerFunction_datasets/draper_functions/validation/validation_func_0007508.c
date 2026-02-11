fs_rtp_session_stop_codec_param_gathering_unlock (FsRtpSession *session)
{

  GST_DEBUG ("Stopping Codec Param discovery for session %d", session->id);

  if (session->priv->discovery_codec)
  {
    fs_codec_destroy (session->priv->discovery_codec);
    session->priv->discovery_codec = NULL;
  }

  g_object_set (session->priv->discovery_valve, "drop", TRUE, NULL);

  FS_RTP_SESSION_UNLOCK (session);


  if (session->priv->discovery_fakesink)
  {
    gst_element_set_locked_state (session->priv->discovery_fakesink, TRUE);
    gst_element_set_state (session->priv->discovery_fakesink, GST_STATE_NULL);
    gst_bin_remove (GST_BIN (session->priv->conference),
        session->priv->discovery_fakesink);
    session->priv->discovery_fakesink = NULL;
  }

  if (session->priv->discovery_capsfilter)
  {
    gst_element_set_locked_state (session->priv->discovery_capsfilter, TRUE);
    gst_element_set_state (session->priv->discovery_capsfilter, GST_STATE_NULL);
    gst_bin_remove (GST_BIN (session->priv->conference),
        session->priv->discovery_capsfilter);
    session->priv->discovery_capsfilter = NULL;
  }

  if (session->priv->discovery_codecbin)
  {
    gst_element_set_locked_state (session->priv->discovery_codecbin, TRUE);
    gst_element_set_state (session->priv->discovery_codecbin, GST_STATE_NULL);
    gst_bin_remove (GST_BIN (session->priv->conference),
        session->priv->discovery_codecbin);
    session->priv->discovery_codecbin = NULL;
  }
}
