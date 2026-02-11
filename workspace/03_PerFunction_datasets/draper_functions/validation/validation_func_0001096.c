gst_audio_visualizer_src_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  gboolean res;
  GstAudioVisualizer *scope;

  scope = GST_AUDIO_VISUALIZER (parent);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_QOS:
    {
      gdouble proportion;
      GstClockTimeDiff diff;
      GstClockTime timestamp;

      gst_event_parse_qos (event, NULL, &proportion, &diff, &timestamp);


      GST_OBJECT_LOCK (scope);
      scope->proportion = proportion;
      if (diff >= 0)


        scope->earliest_time = timestamp + 2 * diff + scope->frame_duration;
      else
        scope->earliest_time = timestamp + diff;
      GST_OBJECT_UNLOCK (scope);

      res = gst_pad_push_event (scope->sinkpad, event);
      break;
    }
    case GST_EVENT_RECONFIGURE:

      gst_event_unref (event);
      res = TRUE;
      break;
    default:
      res = gst_pad_event_default (pad, parent, event);
      break;
  }

  return res;
}
