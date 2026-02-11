gst_rtp_buffer_get_payload_bytes (GstRTPBuffer * rtp)
{
  gpointer data;

  g_return_val_if_fail (rtp != NULL, NULL);

  data = gst_rtp_buffer_get_payload (rtp);
  if (data == NULL)
    return NULL;

  return g_bytes_new (data, gst_rtp_buffer_get_payload_len (rtp));
}
