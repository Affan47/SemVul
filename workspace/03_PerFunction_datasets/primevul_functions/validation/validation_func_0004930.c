static int processTLSBlock(struct ndpi_detection_module_struct *ndpi_struct,
			   struct ndpi_flow_struct *flow) {
  struct ndpi_packet_struct *packet = &flow->packet;

  switch(packet->payload[0] ) {
  case 0x01:
  case 0x02:
    processClientServerHello(ndpi_struct, flow);
    flow->l4.tcp.tls.hello_processed = 1;
    ndpi_int_tls_add_connection(ndpi_struct, flow, NDPI_PROTOCOL_TLS);
    break;

  case 0x0b:


    if(flow->l4.tcp.tls.hello_processed) {
      processCertificate(ndpi_struct, flow);
      flow->l4.tcp.tls.certificate_processed = 1;
    }
    break;

  default:
    return(-1);
  }

  return(0);
}
