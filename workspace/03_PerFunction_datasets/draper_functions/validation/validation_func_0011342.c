rfb_decoder_send (RfbDecoder * decoder, guint8 * buffer, guint len)
{
  g_return_val_if_fail (decoder->fd != 0, FALSE);
  g_return_val_if_fail (buffer != NULL, FALSE);
  g_return_val_if_fail (len > 0, FALSE);

  return write (decoder->fd, buffer, len);
}
