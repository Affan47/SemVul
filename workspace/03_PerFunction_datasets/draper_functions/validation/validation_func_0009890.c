gst_base_sink_set_render_delay (GstBaseSink * sink, GstClockTime delay)
{
  GstClockTime old_render_delay;

  g_return_if_fail (GST_IS_BASE_SINK (sink));

  GST_OBJECT_LOCK (sink);
  old_render_delay = sink->priv->render_delay;
  sink->priv->render_delay = delay;
  GST_LOG_OBJECT (sink, "set render delay to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (delay));
  GST_OBJECT_UNLOCK (sink);

  if (delay != old_render_delay) {
    GST_DEBUG_OBJECT (sink, "posting latency changed");
    gst_element_post_message (GST_ELEMENT_CAST (sink),
        gst_message_new_latency (GST_OBJECT_CAST (sink)));
  }
}
