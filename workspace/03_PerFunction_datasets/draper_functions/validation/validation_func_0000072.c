create_segment_event (GstRTPBaseDepayload * filter, GstClockTime position)
{
  GstEvent *event;
  GstClockTime stop;
  GstRTPBaseDepayloadPrivate *priv;
  GstSegment segment;

  priv = filter->priv;

  if (priv->npt_stop != -1)
    stop = priv->npt_stop - priv->npt_start;
  else
    stop = -1;

  gst_segment_init (&segment, GST_FORMAT_TIME);
  segment.rate = priv->play_speed;
  segment.applied_rate = priv->play_scale;
  segment.start = 0;
  segment.stop = stop;
  segment.time = priv->npt_start;
  segment.position = position;

  event = gst_event_new_segment (&segment);

  return event;
}
