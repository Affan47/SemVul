gst_rtp_base_audio_payload_sample_time_to_bytes (GstRTPBaseAudioPayload *
    payload, guint64 time)
{
  guint64 samples;

  samples = gst_util_uint64_scale_int (time,
      GST_RTP_BASE_PAYLOAD (payload)->clock_rate, GST_SECOND);


  if (G_LIKELY (payload->sample_size != 8))
    return gst_util_uint64_scale_int (samples, payload->sample_size, 8);
  else
    return samples;
}
