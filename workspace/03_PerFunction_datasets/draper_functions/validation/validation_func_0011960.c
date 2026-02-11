rsn_audiomunge_make_audio (RsnAudioMunge * munge,
    GstClockTime start, GstClockTime fill_time)
{
  GstFlowReturn ret;
  GstBuffer *audio_buf;
  GstCaps *caps;
  guint buf_size;


#if 0
  caps =
      gst_caps_from_string
      ("audio/x-raw-int,rate=48000,channels=2,width=16,depth=16,signed=(boolean)true,endianness=4321");
  buf_size = 4 * (48000 * fill_time / GST_SECOND);
#else
  caps = gst_caps_from_string ("audio/x-raw-float, endianness=(int)1234,"
      "width=(int)32, channels=(int)2, rate=(int)48000");
  buf_size = 2 * 4 * (48000 * fill_time / GST_SECOND);
#endif

  audio_buf = gst_buffer_new_and_alloc (buf_size);

  gst_buffer_set_caps (audio_buf, caps);
  gst_caps_unref (caps);

  GST_BUFFER_TIMESTAMP (audio_buf) = start;
  GST_BUFFER_DURATION (audio_buf) = fill_time;
  GST_BUFFER_FLAG_SET (audio_buf, GST_BUFFER_FLAG_DISCONT);

  memset (GST_BUFFER_DATA (audio_buf), 0, buf_size);

  GST_LOG_OBJECT (munge, "Sending %u bytes (%" GST_TIME_FORMAT
      ") of audio data with TS %" GST_TIME_FORMAT,
      buf_size, GST_TIME_ARGS (fill_time), GST_TIME_ARGS (start));

  ret = gst_pad_push (munge->srcpad, audio_buf);

  return ret;
}
