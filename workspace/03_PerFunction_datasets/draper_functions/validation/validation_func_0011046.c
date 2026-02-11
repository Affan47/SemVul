gst_base_src_new_seamless_segment (GstBaseSrc * src, gint64 start, gint64 stop,
    gint64 position)
{
  gboolean res = TRUE;

  GST_DEBUG_OBJECT (src,
      "Starting new seamless segment. Start %" GST_TIME_FORMAT " stop %"
      GST_TIME_FORMAT " position %" GST_TIME_FORMAT, GST_TIME_ARGS (start),
      GST_TIME_ARGS (stop), GST_TIME_ARGS (position));

  GST_OBJECT_LOCK (src);
  if (src->data.ABI.running && !src->priv->newsegment_pending) {
    if (src->priv->close_segment)
      gst_event_unref (src->priv->close_segment);
    src->priv->close_segment =
        gst_event_new_new_segment_full (TRUE,
        src->segment.rate, src->segment.applied_rate, src->segment.format,
        src->segment.start, src->segment.last_stop, src->segment.time);
  }

  gst_segment_set_newsegment_full (&src->segment, FALSE, src->segment.rate,
      src->segment.applied_rate, src->segment.format, start, stop, position);

  if (src->priv->start_segment)
    gst_event_unref (src->priv->start_segment);
  if (src->segment.rate >= 0.0) {

    src->priv->start_segment =
        gst_event_new_new_segment_full (FALSE,
        src->segment.rate, src->segment.applied_rate, src->segment.format,
        src->segment.last_stop, stop, src->segment.time);
  } else {

    src->priv->start_segment =
        gst_event_new_new_segment_full (FALSE,
        src->segment.rate, src->segment.applied_rate, src->segment.format,
        src->segment.start, src->segment.last_stop, src->segment.time);
  }
  GST_OBJECT_UNLOCK (src);

  src->priv->discont = TRUE;
  src->data.ABI.running = TRUE;

  return res;
}
