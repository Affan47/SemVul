gst_base_video_decoder_do_seek (GstBaseVideoDecoder * dec, GstEvent * event)
{
  GstBaseVideoCodec *codec = GST_BASE_VIDEO_CODEC (dec);
  GstSeekFlags flags;
  GstSeekType start_type, end_type;
  GstFormat format;
  gdouble rate;
  gint64 start, start_time, end_time;
  GstSegment seek_segment;
  guint32 seqnum;

  gst_event_parse_seek (event, &rate, &format, &flags, &start_type,
      &start_time, &end_type, &end_time);


  if (rate != 1.0) {
    GST_DEBUG_OBJECT (dec, "unsupported seek: rate");
    return FALSE;
  }

  if (start_type != GST_SEEK_TYPE_SET) {
    GST_DEBUG_OBJECT (dec, "unsupported seek: start time");
    return FALSE;
  }

  if (end_type != GST_SEEK_TYPE_NONE ||
      (end_type == GST_SEEK_TYPE_SET && end_time != GST_CLOCK_TIME_NONE)) {
    GST_DEBUG_OBJECT (dec, "unsupported seek: end time");
    return FALSE;
  }

  if (!(flags & GST_SEEK_FLAG_FLUSH)) {
    GST_DEBUG_OBJECT (dec, "unsupported seek: not flushing");
    return FALSE;
  }

  memcpy (&seek_segment, &codec->segment, sizeof (seek_segment));
  gst_segment_set_seek (&seek_segment, rate, format, flags, start_type,
      start_time, end_type, end_time, NULL);
  start_time = seek_segment.last_stop;

  format = GST_FORMAT_BYTES;
  if (!gst_pad_query_convert (codec->sinkpad, GST_FORMAT_TIME, start_time,
          &format, &start)) {
    GST_DEBUG_OBJECT (dec, "conversion failed");
    return FALSE;
  }

  seqnum = gst_event_get_seqnum (event);
  event = gst_event_new_seek (1.0, GST_FORMAT_BYTES, flags,
      GST_SEEK_TYPE_SET, start, GST_SEEK_TYPE_NONE, -1);
  gst_event_set_seqnum (event, seqnum);

  GST_DEBUG_OBJECT (dec, "seeking to %" GST_TIME_FORMAT " at byte offset %"
      G_GINT64_FORMAT, GST_TIME_ARGS (start_time), start);

  return gst_pad_push_event (codec->sinkpad, event);
}
