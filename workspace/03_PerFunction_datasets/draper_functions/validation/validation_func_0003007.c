theora_dec_src_event (GstPad * pad, GstEvent * event)
{
  gboolean res = TRUE;
  GstTheoraDec *dec;

  dec = GST_THEORA_DEC (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_SEEK:
    {
      GstFormat format, tformat;
      gdouble rate;
      GstEvent *real_seek;
      GstSeekFlags flags;
      GstSeekType cur_type, stop_type;
      gint64 cur, stop;
      gint64 tcur, tstop;
      guint32 seqnum;

      gst_event_parse_seek (event, &rate, &format, &flags, &cur_type, &cur,
          &stop_type, &stop);
      seqnum = gst_event_get_seqnum (event);
      gst_event_unref (event);


      tformat = GST_FORMAT_TIME;
      if (!(res = theora_dec_src_convert (pad, format, cur, &tformat, &tcur)))
        goto convert_error;
      if (!(res = theora_dec_src_convert (pad, format, stop, &tformat, &tstop)))
        goto convert_error;


      real_seek = gst_event_new_seek (rate, GST_FORMAT_TIME,
          flags, cur_type, tcur, stop_type, tstop);
      gst_event_set_seqnum (real_seek, seqnum);

      res = gst_pad_push_event (dec->sinkpad, real_seek);
      break;
    }
    case GST_EVENT_QOS:
    {
      gdouble proportion;
      GstClockTimeDiff diff;
      GstClockTime timestamp;

      gst_event_parse_qos (event, &proportion, &diff, &timestamp);


      GST_OBJECT_LOCK (dec);
      dec->proportion = proportion;
      dec->earliest_time = timestamp + diff;
      GST_OBJECT_UNLOCK (dec);

      GST_DEBUG_OBJECT (dec, "got QoS %" GST_TIME_FORMAT ", %" G_GINT64_FORMAT,
          GST_TIME_ARGS (timestamp), diff);

      res = gst_pad_push_event (dec->sinkpad, event);
      break;
    }
    default:
      res = gst_pad_push_event (dec->sinkpad, event);
      break;
  }
done:
  gst_object_unref (dec);

  return res;


convert_error:
  {
    GST_DEBUG_OBJECT (dec, "could not convert format");
    goto done;
  }
}
