void ndpi_process_extra_packet(struct ndpi_detection_module_struct *ndpi_str, struct ndpi_flow_struct *flow,
                               const unsigned char *packet, const unsigned short packetlen,
                               const u_int64_t current_tick_l, struct ndpi_id_struct *src, struct ndpi_id_struct *dst) {
  if(flow == NULL)
    return;

  if(flow->server_id == NULL)
    flow->server_id = dst;


  if(packetlen < 20) {
    return;
  }

  flow->packet.tick_timestamp_l = current_tick_l;
  flow->packet.tick_timestamp = (u_int32_t)(current_tick_l / ndpi_str->ticks_per_second);


  flow->packet.iph = (struct ndpi_iphdr *) packet;


  if(ndpi_init_packet_header(ndpi_str, flow, packetlen) != 0)
    return;


  flow->src = src, flow->dst = dst;
  ndpi_connection_tracking(ndpi_str, flow);


  if(flow->extra_packets_func) {
    if((flow->extra_packets_func(ndpi_str, flow)) == 0)
      flow->check_extra_packets = 0;

    if(++flow->num_extra_packets_checked == flow->max_extra_packets_to_check)
      flow->extra_packets_func = NULL;
  }
}
