gst_app_src_start (GstBaseSrc * bsrc)
{
  GstAppSrc *appsrc = GST_APP_SRC_CAST (bsrc);
  GstAppSrcPrivate *priv = appsrc->priv;

  g_mutex_lock (&priv->mutex);
  GST_DEBUG_OBJECT (appsrc, "starting");
  priv->new_caps = FALSE;
  priv->started = TRUE;


  priv->offset = -1;
  priv->flushing = FALSE;
  g_mutex_unlock (&priv->mutex);

  gst_base_src_set_format (bsrc, priv->format);

  return TRUE;
}
