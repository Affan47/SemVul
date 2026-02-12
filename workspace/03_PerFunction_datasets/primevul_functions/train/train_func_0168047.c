check_packet_auth(NTP_Packet *pkt, int length, int *has_auth, uint32_t *key_id)
{
  int i, remainder, ext_length;
  unsigned char *data;
  uint32_t id;


  i = NTP_NORMAL_PACKET_LENGTH;
  data = (void *)pkt;

  while (1) {
    remainder = length - i;


    if (remainder >= NTP_MIN_MAC_LENGTH && remainder <= NTP_MAX_MAC_LENGTH) {
      id = ntohl(*(uint32_t *)(data + i));
      if (KEY_CheckAuth(id, (void *)pkt, i, (void *)(data + i + 4),
                        remainder - 4)) {
        if (key_id)
          *key_id = id;
        if (has_auth)
          *has_auth = 1;
        return 1;
      }
    }


    if (remainder >= NTP_MIN_EXTENSION_LENGTH) {
      ext_length = ntohs(*(uint16_t *)(data + i + 2));
      if (ext_length >= NTP_MIN_EXTENSION_LENGTH &&
          ext_length <= remainder && ext_length % 4 == 0) {
        i += ext_length;
        continue;
      }
    }


    break;
  }


  if (has_auth)
    *has_auth = remainder >= NTP_MIN_MAC_LENGTH;

  return 0;
}
