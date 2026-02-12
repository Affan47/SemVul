get_dnp3_message_len(packet_info *pinfo _U_, tvbuff_t *tvb,
                     int offset, void *data _U_)
{
  guint16 message_len;
  guint16 data_crc;

  message_len = tvb_get_guint8(tvb, offset + 2);


  data_crc = (guint16)(ceil((message_len - 5) / 16.0)) * 2;
  message_len += 2 + 1 + 2 + data_crc;
  return message_len;
}
