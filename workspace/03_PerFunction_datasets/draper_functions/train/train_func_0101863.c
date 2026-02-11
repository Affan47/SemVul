rfb_decoder_state_reason (RfbDecoder * decoder)
{
  gint reason_length;

  rfb_decoder_read (decoder, 4);

  reason_length = RFB_GET_UINT32 (decoder->data);
  rfb_decoder_read (decoder, reason_length);
  GST_WARNING ("Reason by server: %s", decoder->data);

  return FALSE;
}
