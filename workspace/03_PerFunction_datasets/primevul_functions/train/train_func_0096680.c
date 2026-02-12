uipbuf_get_last_header(uint8_t *buffer, uint16_t size, uint8_t *protocol)
{
  uint8_t *nbuf;

  nbuf = uipbuf_get_next_header(buffer, size, protocol, true);
  while(nbuf != NULL && uip_is_proto_ext_hdr(*protocol)) {

    nbuf = uipbuf_get_next_header(nbuf, size - (nbuf - buffer), protocol, false);
  }


  return nbuf;
}
