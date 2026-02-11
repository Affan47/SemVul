gst_rtp_jitter_buffer_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec)
{
  GstRtpJitterBuffer *jitterbuffer;
  GstRtpJitterBufferPrivate *priv;

  jitterbuffer = GST_RTP_JITTER_BUFFER (object);
  priv = jitterbuffer->priv;

  switch (prop_id) {
    case PROP_LATENCY:
    {
      guint new_latency, old_latency;

      new_latency = g_value_get_uint (value);

      JBUF_LOCK (priv);
      old_latency = priv->latency_ms;
      priv->latency_ms = new_latency;
      priv->latency_ns = priv->latency_ms * GST_MSECOND;
      rtp_jitter_buffer_set_delay (priv->jbuf, priv->latency_ns);
      JBUF_UNLOCK (priv);


      if (new_latency != old_latency) {
        GST_DEBUG_OBJECT (jitterbuffer, "latency changed to: %" GST_TIME_FORMAT,
            GST_TIME_ARGS (new_latency * GST_MSECOND));

        gst_element_post_message (GST_ELEMENT_CAST (jitterbuffer),
            gst_message_new_latency (GST_OBJECT_CAST (jitterbuffer)));
      }
      break;
    }
    case PROP_DROP_ON_LATENCY:
      JBUF_LOCK (priv);
      priv->drop_on_latency = g_value_get_boolean (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_TS_OFFSET:
      JBUF_LOCK (priv);
      priv->ts_offset = g_value_get_int64 (value);
      priv->ts_discont = TRUE;
      JBUF_UNLOCK (priv);
      break;
    case PROP_DO_LOST:
      JBUF_LOCK (priv);
      priv->do_lost = g_value_get_boolean (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_MODE:
      JBUF_LOCK (priv);
      rtp_jitter_buffer_set_mode (priv->jbuf, g_value_get_enum (value));
      JBUF_UNLOCK (priv);
      break;
    case PROP_DO_RETRANSMISSION:
      JBUF_LOCK (priv);
      priv->do_retransmission = g_value_get_boolean (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_RTX_DELAY:
      JBUF_LOCK (priv);
      priv->rtx_delay = g_value_get_int (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_RTX_DELAY_REORDER:
      JBUF_LOCK (priv);
      priv->rtx_delay_reorder = g_value_get_int (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_RTX_RETRY_TIMEOUT:
      JBUF_LOCK (priv);
      priv->rtx_retry_timeout = g_value_get_int (value);
      JBUF_UNLOCK (priv);
      break;
    case PROP_RTX_RETRY_PERIOD:
      JBUF_LOCK (priv);
      priv->rtx_retry_period = g_value_get_int (value);
      JBUF_UNLOCK (priv);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
