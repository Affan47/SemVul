gst_rtp_base_payload_audio_sink_event (GstRTPBasePayload * basep,
    GstEvent * event)
{
  GstRTPBaseAudioPayload *payload;
  gboolean res = FALSE;

  payload = GST_RTP_BASE_AUDIO_PAYLOAD (basep);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:

      gst_rtp_base_audio_payload_flush (payload, -1, -1);
      break;
    case GST_EVENT_FLUSH_STOP:
      gst_adapter_clear (payload->priv->adapter);
      break;
    default:
      break;
  }


  res = GST_RTP_BASE_PAYLOAD_CLASS (parent_class)->sink_event (basep, event);

  return res;
}
