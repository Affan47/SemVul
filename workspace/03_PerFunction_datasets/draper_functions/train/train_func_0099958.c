rsn_audiomunge_sink_event (GstPad * pad, GstEvent * event)
{
  gboolean ret = FALSE;
  RsnAudioMunge *munge = RSN_AUDIOMUNGE (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_STOP:
      rsn_audiomunge_reset (munge);
      ret = gst_pad_push_event (munge->srcpad, event);
      break;
    case GST_EVENT_NEWSEGMENT:
    {
      GstSegment *segment;
      gboolean update;
      GstFormat format;
      gdouble rate, arate;
      gint64 start, stop, time;

      gst_event_parse_new_segment_full (event, &update, &rate, &arate, &format,
          &start, &stop, &time);


      if (format != GST_FORMAT_TIME)
        goto newseg_wrong_format;


      segment = &munge->sink_segment;

      gst_segment_set_newsegment_full (segment, update,
          rate, arate, format, start, stop, time);


      if (!update) {
        GST_DEBUG_OBJECT (munge,
            "Sending newsegment: update %d start %" GST_TIME_FORMAT " stop %"
            GST_TIME_FORMAT " accum now %" GST_TIME_FORMAT, update,
            GST_TIME_ARGS (start), GST_TIME_ARGS (stop),
            GST_TIME_ARGS (segment->accum));

        ret = gst_pad_push_event (munge->srcpad, event);
      }

      if (!munge->have_audio) {
        if ((update && segment->accum >= AUDIO_FILL_THRESHOLD)
            || munge->in_still) {
          GST_DEBUG_OBJECT (munge,
              "Sending audio fill with ts %" GST_TIME_FORMAT ": accum = %"
              GST_TIME_FORMAT " still-state=%d", GST_TIME_ARGS (segment->start),
              GST_TIME_ARGS (segment->accum), munge->in_still);


          if (rsn_audiomunge_make_audio (munge, segment->start,
                  GST_SECOND / 5) == GST_FLOW_OK)
            munge->have_audio = TRUE;
        } else {
          GST_LOG_OBJECT (munge, "Not sending audio fill buffer: "
              "Not segment update, or segment accum below thresh: accum = %"
              GST_TIME_FORMAT, GST_TIME_ARGS (segment->accum));
        }
      }

      if (update) {
        GST_DEBUG_OBJECT (munge,
            "Sending newsegment: update %d start %" GST_TIME_FORMAT " stop %"
            GST_TIME_FORMAT " accum now %" GST_TIME_FORMAT, update,
            GST_TIME_ARGS (start), GST_TIME_ARGS (stop),
            GST_TIME_ARGS (segment->accum));

        ret = gst_pad_push_event (munge->srcpad, event);
      }

      break;
    }
    case GST_EVENT_CUSTOM_DOWNSTREAM:
    {
      gboolean in_still;

      if (gst_video_event_parse_still_frame (event, &in_still)) {


        munge->in_still = in_still;
        GST_INFO_OBJECT (munge, "AUDIO MUNGE: still-state now %d",
            munge->in_still);
      }

      ret = gst_pad_push_event (munge->srcpad, event);
      break;
    }
    default:
      ret = gst_pad_push_event (munge->srcpad, event);
      break;
  }

  gst_object_unref (munge);
  return ret;

newseg_wrong_format:

  GST_DEBUG_OBJECT (munge, "received non TIME newsegment");
  gst_event_unref (event);
  gst_object_unref (munge);
  return FALSE;
}
