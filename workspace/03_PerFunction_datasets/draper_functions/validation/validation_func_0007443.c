gst_rtmp_src_do_seek (GstBaseSrc * basesrc, GstSegment * segment)
{
  GstRTMPSrc *src;

  src = GST_RTMP_SRC (basesrc);

  if (segment->format != GST_FORMAT_TIME) {
    GST_LOG_OBJECT (src, "Only time based seeks are supported");
    return FALSE;
  }

  if (!src->rtmp) {
    GST_LOG_OBJECT (src, "Not connected yet");
    return FALSE;
  }

  src->discont = TRUE;


  if (src->cur_offset == 0 && segment->start == 0)
    return TRUE;

  if (!src->seekable) {
    GST_LOG_OBJECT (src, "Not a seekable stream");
    return FALSE;
  }

  src->last_timestamp = GST_CLOCK_TIME_NONE;
  if (!RTMP_SendSeek (src->rtmp, segment->start / GST_MSECOND)) {
    GST_ERROR_OBJECT (src, "Seeking failed");
    src->seekable = FALSE;
    return FALSE;
  }

  GST_DEBUG_OBJECT (src, "Seek to %" GST_TIME_FORMAT " successfull",
      GST_TIME_ARGS (segment->start));

  return TRUE;
}
