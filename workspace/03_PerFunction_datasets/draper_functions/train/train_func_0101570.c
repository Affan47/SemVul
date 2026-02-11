gst_real_audio_demux_handle_seek (GstRealAudioDemux * demux, GstEvent * event)
{
  GstFormat format;
  GstSeekFlags flags;
  GstSeekType cur_type, stop_type;
  gboolean flush, update;
  gdouble rate;
  guint64 seek_pos;
  gint64 cur, stop;

  if (!demux->seekable)
    goto not_seekable;

  if (demux->byterate_num == 0 || demux->byterate_denom == 0)
    goto no_bitrate;

  gst_event_parse_seek (event, &rate, &format, &flags,
      &cur_type, &cur, &stop_type, &stop);

  if (format != GST_FORMAT_TIME)
    goto only_time_format_supported;

  if (rate <= 0.0)
    goto cannot_do_backwards_playback;

  flush = ((flags & GST_SEEK_FLAG_FLUSH) != 0);

  GST_DEBUG_OBJECT (demux, "flush=%d, rate=%g", flush, rate);


  if (flush) {
    gst_pad_push_event (demux->sinkpad, gst_event_new_flush_start ());
    gst_pad_push_event (demux->srcpad, gst_event_new_flush_start ());
  } else {
    gst_pad_pause_task (demux->sinkpad);
  }

  GST_PAD_STREAM_LOCK (demux->sinkpad);

  gst_segment_do_seek (&demux->segment, rate, format, flags,
      cur_type, cur, stop_type, stop, &update);

  GST_DEBUG_OBJECT (demux, "segment: %" GST_SEGMENT_FORMAT, &demux->segment);

  seek_pos = gst_util_uint64_scale (demux->segment.start,
      demux->byterate_num, demux->byterate_denom * GST_SECOND);
  if (demux->packet_size > 0) {
    seek_pos -= seek_pos % demux->packet_size;
  }
  seek_pos += demux->data_offset;

  GST_DEBUG_OBJECT (demux, "seek_pos = %" G_GUINT64_FORMAT, seek_pos);


  gst_pad_push_event (demux->sinkpad, gst_event_new_flush_stop (TRUE));
  gst_pad_push_event (demux->srcpad, gst_event_new_flush_stop (TRUE));

  demux->offset = seek_pos;
  demux->need_newsegment = TRUE;


  if (demux->segment.flags & GST_SEEK_FLAG_SEGMENT) {
    gst_element_post_message (GST_ELEMENT (demux),
        gst_message_new_segment_start (GST_OBJECT (demux),
            GST_FORMAT_TIME, demux->segment.position));
  }

  demux->segment_running = TRUE;

  gst_pad_start_task (demux->sinkpad,
      (GstTaskFunction) gst_real_audio_demux_loop, demux, NULL);


  GST_PAD_STREAM_UNLOCK (demux->sinkpad);

  return TRUE;


not_seekable:
  {
    GST_DEBUG_OBJECT (demux, "seek failed: cannot seek in streaming mode");
    return FALSE;
  }
no_bitrate:
  {
    GST_DEBUG_OBJECT (demux, "seek failed: bitrate unknown");
    return FALSE;
  }
only_time_format_supported:
  {
    GST_DEBUG_OBJECT (demux, "can only seek in TIME format");
    return FALSE;
  }
cannot_do_backwards_playback:
  {
    GST_DEBUG_OBJECT (demux, "can only seek with positive rate, not %lf", rate);
    return FALSE;
  }
}
