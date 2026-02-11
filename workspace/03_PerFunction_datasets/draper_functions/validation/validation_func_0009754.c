gst_audio_cd_src_update_duration (GstAudioCdSrc * src)
{
  GstBaseSrc *basesrc;
  gint64 dur;

  basesrc = GST_BASE_SRC (src);

  if (!gst_pad_query_duration (GST_BASE_SRC_PAD (src), GST_FORMAT_TIME, &dur)) {
    dur = GST_CLOCK_TIME_NONE;
  }
  basesrc->segment.duration = dur;

  gst_element_post_message (GST_ELEMENT (src),
      gst_message_new_duration_changed (GST_OBJECT (src)));

  GST_LOG_OBJECT (src, "duration updated to %" GST_TIME_FORMAT,
      GST_TIME_ARGS (dur));
}
