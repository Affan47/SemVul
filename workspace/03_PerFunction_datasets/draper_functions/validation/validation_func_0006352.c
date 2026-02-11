dump_dns_answers(packet_t *pkt, u_int8_t num, char *answer_type)
{
  char holder[HOLDER_SIZE];
  u_int16_t query_type, query_class;
  u_int32_t ttl;
  u_int16_t rdl;
  u_int8_t resource_data[64];

  while(num > 0)
    {


      parse_ns_labels(pkt, holder);


      if (get_packet_bytes((u_int8_t *) &query_type, pkt, 2) == 0)
	return;
      if (get_packet_bytes((u_int8_t *) &query_class, pkt, 2) == 0)
	return;
      if (get_packet_bytes((u_int8_t *) &ttl, pkt, 4) == 0)
	return;
      if (get_packet_bytes((u_int8_t *) &rdl, pkt, 2) == 0)
	return;


      query_type = ntohs(query_type);
      query_class = ntohs(query_class);
      ttl = ntohl(ttl);
      rdl = ntohs(rdl);


      switch (query_type)
	{
	case DNS_QUERYTYPE_NS:
	case DNS_QUERYTYPE_CNAME:
	case DNS_QUERYTYPE_SOA:
	case DNS_QUERYTYPE_PTR:
	  parse_ns_labels(pkt, resource_data);
	  break;

	case DNS_QUERYTYPE_A:
	default:
	  if (get_packet_bytes((u_int8_t *) &resource_data, pkt,
			       rdl) == 0)
	    return;
	  break;

	}


      if (my_args->m)
	{
	  if (query_type == DNS_QUERYTYPE_A && !strcmp(answer_type, "Answers"))
	    {
	      display_minimal_ipv4((u_int8_t *) resource_data);
	      display_minimal_string(" ");
	    }
	  if (query_type == DNS_QUERYTYPE_AAAA &&
	      !strcmp(answer_type, "Answers") && rdl == 16 )
	    {
	      display_minimal_ipv6((u_int8_t *) resource_data);
	      display_minimal_string(" ");
	    }
	}
      else
	{
	  display_string(answer_type, holder);
	  snprintf(holder, HOLDER_SIZE, "%d (%s)", query_type,
		  map2str(dns_querytype_map, query_type));
	  display_string("  Query type", holder);
	  snprintf(holder, HOLDER_SIZE, "%d (%s)", query_class,
		  map2str(dns_queryclass_map, query_class));
	  display_string("  Query class", holder);
	  display("  TTL", (u_int8_t *) &ttl, 4, DISP_DEC);
	  display("  Resource data length", (u_int8_t *) &rdl, 2,
		  DISP_DEC);
	  switch(query_type)
	    {
	    case DNS_QUERYTYPE_A:
	      display_ipv4("  Resource data", (u_int8_t *) resource_data);
	      break;

	    case DNS_QUERYTYPE_AAAA:
	      display_ipv6("  Resource data", (u_int8_t *) resource_data);
	      break;

	    case DNS_QUERYTYPE_NS:
	    case DNS_QUERYTYPE_CNAME:
	    case DNS_QUERYTYPE_SOA:
	    case DNS_QUERYTYPE_PTR:
	      display_string("  Resource data", resource_data);
	      break;

	    default:
	      display("  Resource data", (u_int8_t *) resource_data, rdl,
		      DISP_HEX);
	    }
	}

      num --;
    }

}
