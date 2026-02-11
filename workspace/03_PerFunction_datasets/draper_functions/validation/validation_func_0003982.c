gst_videomixer2_sink_clip (GstCollectPads2 * pads,
    GstCollectData2 * data, GstBuffer * buf, GstBuffer ** outbuf,
    GstVideoMixer2 * mix)
{
  GstVideoMixer2Pad *pad = GST_VIDEO_MIXER2_PAD (data->pad);
  GstVideoMixer2Collect *mixcol = pad->mixcol;
  GstClockTime start_time, end_time;

  start_time = GST_BUFFER_TIMESTAMP (buf);
  if (start_time == -1) {
    GST_ERROR_OBJECT (pad, "Timestamped buffers required!");
    gst_buffer_unref (buf);
    return GST_FLOW_ERROR;
  }

  end_time = GST_BUFFER_DURATION (buf);
  if (end_time == -1)
    end_time = gst_util_uint64_scale_int (GST_SECOND, pad->fps_d, pad->fps_n);
  if (end_time == -1) {
    *outbuf = buf;
    return GST_FLOW_OK;
  }

  start_time = MAX (start_time, mixcol->collect.segment.start);
  start_time =
      gst_segment_to_running_time (&mixcol->collect.segment,
      GST_FORMAT_TIME, start_time);

  end_time += GST_BUFFER_TIMESTAMP (buf);
  if (mixcol->collect.segment.stop != -1)
    end_time = MIN (end_time, mixcol->collect.segment.stop);
  end_time =
      gst_segment_to_running_time (&mixcol->collect.segment,
      GST_FORMAT_TIME, end_time);


  if (mix->segment.abs_rate != 1.0) {
    start_time *= mix->segment.abs_rate;
    end_time *= mix->segment.abs_rate;
  }

  if (mixcol->buffer != NULL && end_time < mixcol->end_time) {
    gst_buffer_unref (buf);
    *outbuf = NULL;
    return GST_FLOW_OK;
  }

  *outbuf = buf;
  return GST_FLOW_OK;
}
