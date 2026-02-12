void ndpi_connection_tracking(struct ndpi_detection_module_struct *ndpi_str,
			      struct ndpi_flow_struct *flow) {
  if(!flow) {
    return;
  } else {

    struct ndpi_packet_struct *packet = &flow->packet;
    const struct ndpi_iphdr *iph = packet->iph;
#ifdef NDPI_DETECTION_SUPPORT_IPV6
    const struct ndpi_ipv6hdr *iphv6 = packet->iphv6;
#endif
    const struct ndpi_tcphdr *tcph = packet->tcp;
    const struct ndpi_udphdr *udph = flow->packet.udp;

    packet->tcp_retransmission = 0, packet->packet_direction = 0;

    if(ndpi_str->direction_detect_disable) {
      packet->packet_direction = flow->packet_direction;
    } else {
      if(iph != NULL && ntohl(iph->saddr) < ntohl(iph->daddr))
	packet->packet_direction = 1;

#ifdef NDPI_DETECTION_SUPPORT_IPV6
      if(iphv6 != NULL && NDPI_COMPARE_IPV6_ADDRESS_STRUCTS(&iphv6->ip6_src, &iphv6->ip6_dst) != 0)
	packet->packet_direction = 1;
#endif
    }

    packet->packet_lines_parsed_complete = 0;

    if(flow->init_finished == 0) {
      flow->init_finished = 1;
      flow->setup_packet_direction = packet->packet_direction;
    }

    if(tcph != NULL) {

      packet->num_retried_bytes = 0;

      if(!ndpi_str->direction_detect_disable)
	packet->packet_direction = (ntohs(tcph->source) < ntohs(tcph->dest)) ? 1 : 0;

      if(tcph->syn != 0 && tcph->ack == 0 && flow->l4.tcp.seen_syn == 0 && flow->l4.tcp.seen_syn_ack == 0 &&
	 flow->l4.tcp.seen_ack == 0) {
	flow->l4.tcp.seen_syn = 1;
      }
      if(tcph->syn != 0 && tcph->ack != 0 && flow->l4.tcp.seen_syn == 1 && flow->l4.tcp.seen_syn_ack == 0 &&
	 flow->l4.tcp.seen_ack == 0) {
	flow->l4.tcp.seen_syn_ack = 1;
      }
      if(tcph->syn == 0 && tcph->ack == 1 && flow->l4.tcp.seen_syn == 1 && flow->l4.tcp.seen_syn_ack == 1 &&
	 flow->l4.tcp.seen_ack == 0) {
	flow->l4.tcp.seen_ack = 1;
      }
      if((flow->next_tcp_seq_nr[0] == 0 && flow->next_tcp_seq_nr[1] == 0) ||
	 (flow->next_tcp_seq_nr[0] == 0 || flow->next_tcp_seq_nr[1] == 0)) {


	if(tcph->ack != 0) {
	  flow->next_tcp_seq_nr[flow->packet.packet_direction] =
	    ntohl(tcph->seq) + (tcph->syn ? 1 : packet->payload_packet_len);

	  flow->next_tcp_seq_nr[1 - flow->packet.packet_direction] = ntohl(tcph->ack_seq);
	}
      } else if(packet->payload_packet_len > 0) {

	if(((u_int32_t)(ntohl(tcph->seq) - flow->next_tcp_seq_nr[packet->packet_direction])) >
	   ndpi_str->tcp_max_retransmission_window_size) {
	  packet->tcp_retransmission = 1;


	  if((flow->next_tcp_seq_nr[packet->packet_direction] - ntohl(tcph->seq) <
	      packet->payload_packet_len)) {


	    packet->num_retried_bytes =
	      (u_int16_t)(flow->next_tcp_seq_nr[packet->packet_direction] - ntohl(tcph->seq));
	    packet->actual_payload_len = packet->payload_packet_len - packet->num_retried_bytes;
	    flow->next_tcp_seq_nr[packet->packet_direction] = ntohl(tcph->seq) + packet->payload_packet_len;
	  }
	}


	else {
	  packet->num_retried_bytes = 0;
	  flow->next_tcp_seq_nr[packet->packet_direction] = ntohl(tcph->seq) + packet->payload_packet_len;
	}
      }

      if(tcph->rst) {
	flow->next_tcp_seq_nr[0] = 0;
	flow->next_tcp_seq_nr[1] = 0;
      }
    } else if(udph != NULL) {
      if(!ndpi_str->direction_detect_disable)
	packet->packet_direction = (htons(udph->source) < htons(udph->dest)) ? 1 : 0;
    }

    if(flow->packet_counter < MAX_PACKET_COUNTER && packet->payload_packet_len) {
      flow->packet_counter++;
    }

    if(flow->packet_direction_counter[packet->packet_direction] < MAX_PACKET_COUNTER &&
       packet->payload_packet_len) {
      flow->packet_direction_counter[packet->packet_direction]++;
    }

    if(flow->byte_counter[packet->packet_direction] + packet->payload_packet_len >
       flow->byte_counter[packet->packet_direction]) {
      flow->byte_counter[packet->packet_direction] += packet->payload_packet_len;
    }
  }
}
