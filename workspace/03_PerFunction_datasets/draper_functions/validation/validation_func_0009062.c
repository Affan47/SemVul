gst_audio_base_sink_setcaps (GstBaseSink * bsink, GstCaps * caps)
{
  GstAudioBaseSink *sink = GST_AUDIO_BASE_SINK (bsink);
  GstAudioRingBufferSpec *spec;
  GstClockTime now;
  GstClockTime crate_num, crate_denom;

  if (!sink->ringbuffer)
    return FALSE;

  spec = &sink->ringbuffer->spec;

  if (G_UNLIKELY (spec->caps && gst_caps_is_equal (spec->caps, caps))) {
    GST_DEBUG_OBJECT (sink,
        "Ringbuffer caps haven't changed, skipping reconfiguration");
    return TRUE;
  }

  GST_DEBUG_OBJECT (sink, "release old ringbuffer");


  now = gst_clock_get_time (sink->provided_clock);

  GST_DEBUG_OBJECT (sink, "time was %" GST_TIME_FORMAT, GST_TIME_ARGS (now));


  gst_audio_ring_buffer_pause (sink->ringbuffer);
  gst_audio_ring_buffer_activate (sink->ringbuffer, FALSE);
  gst_audio_ring_buffer_release (sink->ringbuffer);

  GST_DEBUG_OBJECT (sink, "parse caps");

  spec->buffer_time = sink->buffer_time;
  spec->latency_time = sink->latency_time;


  if (!gst_audio_ring_buffer_parse_caps (spec, caps))
    goto parse_error;

  gst_audio_ring_buffer_debug_spec_buff (spec);

  GST_DEBUG_OBJECT (sink, "acquire ringbuffer");
  if (!gst_audio_ring_buffer_acquire (sink->ringbuffer, spec))
    goto acquire_error;


  sink->priv->avg_skew = -1;
  sink->next_sample = -1;
  sink->priv->eos_time = -1;
  sink->priv->discont_time = -1;

  if (bsink->pad_mode == GST_PAD_MODE_PUSH) {
    GST_DEBUG_OBJECT (sink, "activate ringbuffer");
    gst_audio_ring_buffer_activate (sink->ringbuffer, TRUE);
  }


  gst_clock_get_calibration (sink->provided_clock, NULL, NULL,
      &crate_num, &crate_denom);
  gst_clock_set_calibration (sink->provided_clock,
      gst_clock_get_internal_time (sink->provided_clock), now, crate_num,
      crate_denom);


  spec->latency_time = gst_util_uint64_scale (spec->segsize,
      (GST_SECOND / GST_USECOND), spec->info.rate * spec->info.bpf);

  spec->buffer_time = spec->segtotal * spec->latency_time;

  gst_audio_ring_buffer_debug_spec_buff (spec);

  return TRUE;


parse_error:
  {
    GST_DEBUG_OBJECT (sink, "could not parse caps");
    GST_ELEMENT_ERROR (sink, STREAM, FORMAT,
        (NULL), ("cannot parse audio format."));
    return FALSE;
  }
acquire_error:
  {
    GST_DEBUG_OBJECT (sink, "could not acquire ringbuffer");
    return FALSE;
  }
}
