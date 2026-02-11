gst_audio_decoder_get_estimate_rate (GstAudioDecoder * dec)
{
  g_return_val_if_fail (GST_IS_AUDIO_DECODER (dec), 0);

  return dec->priv->ctx.do_estimate_rate;
}
