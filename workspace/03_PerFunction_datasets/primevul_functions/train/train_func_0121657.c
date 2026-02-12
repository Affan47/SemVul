mpeg_sys_is_valid_pes (GstTypeFind * tf, const guint8 * data, guint len,
    guint * pack_size)
{
  guint pes_packet_len;


  if (len < 6)
    return FALSE;


  pes_packet_len = GST_READ_UINT16_BE (data + 4);
  if (pes_packet_len == 0)
    return FALSE;


  if (6 + pes_packet_len + 4 <= len) {
    if (!IS_MPEG_HEADER (data + 6 + pes_packet_len))
      return FALSE;
  }

  if (pack_size)
    *pack_size = 6 + pes_packet_len;
  return TRUE;
}
