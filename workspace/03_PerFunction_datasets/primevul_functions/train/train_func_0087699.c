u_int8_t is_udp_guessable_protocol(u_int16_t l7_guessed_proto) {
  switch (l7_guessed_proto) {
  case NDPI_PROTOCOL_QUIC:
  case NDPI_PROTOCOL_SNMP:
  case NDPI_PROTOCOL_NETFLOW:

    return(1);
  }

  return(0);
}
