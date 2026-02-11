gst_base_video_decoder_add_timestamp (GstBaseVideoDecoder * base_video_decoder,
    GstBuffer * buffer)
{
  Timestamp *ts;

  ts = g_malloc (sizeof (Timestamp));

  GST_LOG_OBJECT (base_video_decoder,
      "adding timestamp %" GST_TIME_FORMAT " %" GST_TIME_FORMAT,
      GST_TIME_ARGS (base_video_decoder->input_offset),
      GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)));

  ts->offset = base_video_decoder->input_offset;
  ts->timestamp = GST_BUFFER_TIMESTAMP (buffer);
  ts->duration = GST_BUFFER_DURATION (buffer);

  base_video_decoder->timestamps =
      g_list_append (base_video_decoder->timestamps, ts);
}
