gst_app_sink_set_max_buffers (GstAppSink * appsink, guint max)
{
  GstAppSinkPrivate *priv;

  g_return_if_fail (GST_IS_APP_SINK (appsink));

  priv = appsink->priv;

  g_mutex_lock (&priv->mutex);
  if (max != priv->max_buffers) {
    priv->max_buffers = max;

    g_cond_signal (&priv->cond);
  }
  g_mutex_unlock (&priv->mutex);
}
