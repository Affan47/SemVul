ospf_hello (struct ip *iph, struct ospf_header *ospfh,
	    struct stream * s, struct ospf_interface *oi, int size)
{
  struct ospf_hello *hello;
  struct ospf_neighbor *nbr;
  int old_state;
  struct prefix p;


  oi->hello_in++;

  hello = (struct ospf_hello *) STREAM_PNT (s);


  if (IPV4_ADDR_SAME (&ospfh->router_id, &oi->ospf->router_id))
    {
      if (IS_DEBUG_OSPF_PACKET (ospfh->type - 1, RECV))
        {
          zlog_debug ("ospf_header[%s/%s]: selforiginated, "
                     "dropping.",
                     LOOKUP (ospf_packet_type_str, ospfh->type),
                     inet_ntoa (iph->ip_src));
        }
      return;
    }


  p.family = AF_INET;
  p.prefixlen = ip_masklen (hello->network_mask);
  p.u.prefix4 = iph->ip_src;


  if (oi->type != OSPF_IFTYPE_POINTOPOINT
      && oi->type != OSPF_IFTYPE_VIRTUALLINK)
    if (oi->address->prefixlen != p.prefixlen)
      {
	zlog_warn ("Packet %s [Hello:RECV]: NetworkMask mismatch on %s (configured prefix length is %d, but hello packet indicates %d).",
		   inet_ntoa(ospfh->router_id), IF_NAME(oi),
		   (int)oi->address->prefixlen, (int)p.prefixlen);
	return;
      }


  if (OSPF_IF_PARAM (oi, v_wait) != ntohl (hello->dead_interval))
    {
      zlog_warn ("Packet %s [Hello:RECV]: RouterDeadInterval mismatch "
      		 "(expected %u, but received %u).",
		 inet_ntoa(ospfh->router_id),
		 OSPF_IF_PARAM(oi, v_wait), ntohl(hello->dead_interval));
      return;
    }


  if (OSPF_IF_PARAM (oi, fast_hello) == 0)
    {
      if (OSPF_IF_PARAM (oi, v_hello) != ntohs (hello->hello_interval))
        {
          zlog_warn ("Packet %s [Hello:RECV]: HelloInterval mismatch "
		     "(expected %u, but received %u).",
		     inet_ntoa(ospfh->router_id),
		     OSPF_IF_PARAM(oi, v_hello), ntohs(hello->hello_interval));
          return;
        }
    }

  if (IS_DEBUG_OSPF_EVENT)
    zlog_debug ("Packet %s [Hello:RECV]: Options %s",
	       inet_ntoa (ospfh->router_id),
	       ospf_options_dump (hello->options));


#define REJECT_IF_TBIT_ON	1
#ifdef REJECT_IF_TBIT_ON
  if (CHECK_FLAG (hello->options, OSPF_OPTION_T))
    {


      zlog_warn ("Packet %s [Hello:RECV]: T-bit on, drop it.",
		 inet_ntoa (ospfh->router_id));
      return;
    }
#endif

#ifdef HAVE_OPAQUE_LSA
  if (CHECK_FLAG (oi->ospf->config, OSPF_OPAQUE_CAPABLE)
      && CHECK_FLAG (hello->options, OSPF_OPTION_O))
    {


      zlog_warn ("Packet %s [Hello:RECV]: O-bit abuse?",
		 inet_ntoa (ospfh->router_id));
#ifdef STRICT_OBIT_USAGE_CHECK
      return;
#else
      UNSET_FLAG (hello->options, OSPF_OPTION_O);
#endif
    }
#endif


  if (oi->area->external_routing == OSPF_AREA_NSSA)
    {
      if (! (CHECK_FLAG (OPTIONS (oi), OSPF_OPTION_NP)
	     && CHECK_FLAG (hello->options, OSPF_OPTION_NP)
	     && ! CHECK_FLAG (OPTIONS (oi), OSPF_OPTION_E)
	     && ! CHECK_FLAG (hello->options, OSPF_OPTION_E)))
	{
	  zlog_warn ("NSSA-Packet-%s[Hello:RECV]: my options: %x, his options %x", inet_ntoa (ospfh->router_id), OPTIONS (oi), hello->options);
	  return;
	}
      if (IS_DEBUG_OSPF_NSSA)
        zlog_debug ("NSSA-Hello:RECV:Packet from %s:", inet_ntoa(ospfh->router_id));
    }
  else


    if (CHECK_FLAG (OPTIONS (oi), OSPF_OPTION_E) !=
	CHECK_FLAG (hello->options, OSPF_OPTION_E))
      {
	zlog_warn ("Packet %s [Hello:RECV]: my options: %x, his options %x",
		   inet_ntoa(ospfh->router_id), OPTIONS (oi), hello->options);
	return;
      }


  nbr = ospf_nbr_get (oi, ospfh, iph, &p);


  assert (nbr);

  old_state = nbr->state;


  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_PacketReceived);


  if (oi->type == OSPF_IFTYPE_NBMA)
    if (PRIORITY(oi) == 0 && hello->priority > 0
	&& IPV4_ADDR_CMP(&DR(oi),  &iph->ip_src)
	&& IPV4_ADDR_CMP(&BDR(oi), &iph->ip_src))
      OSPF_NSM_TIMER_ON (nbr->t_hello_reply, ospf_hello_reply_timer,
			 OSPF_HELLO_REPLY_DELAY);


  if (oi->type == OSPF_IFTYPE_NBMA &&
      (old_state == NSM_Down || old_state == NSM_Attempt))
    {
      OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_OneWayReceived);
      nbr->priority = hello->priority;
      nbr->d_router = hello->d_router;
      nbr->bd_router = hello->bd_router;
      return;
    }

  if (ospf_nbr_bidirectional (&oi->ospf->router_id, hello->neighbors,
			      size - OSPF_HELLO_MIN_SIZE))
    {
      OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_TwoWayReceived);
      nbr->options |= hello->options;
    }
  else
    {
      OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_OneWayReceived);

      nbr->priority = hello->priority;
      nbr->d_router = hello->d_router;
      nbr->bd_router = hello->bd_router;
      return;
    }


  if (IPV4_ADDR_SAME (&nbr->address.u.prefix4, &hello->d_router))
    if (hello->bd_router.s_addr == 0 && oi->state == ISM_Waiting)
      OSPF_ISM_EVENT_SCHEDULE (oi, ISM_BackupSeen);


  if (oi->state == ISM_Waiting &&
      IPV4_ADDR_SAME (&nbr->address.u.prefix4, &hello->bd_router))
    OSPF_ISM_EVENT_SCHEDULE (oi, ISM_BackupSeen);


  if ((IPV4_ADDR_SAME (&nbr->address.u.prefix4, &hello->d_router) &&
       IPV4_ADDR_CMP (&nbr->address.u.prefix4, &nbr->d_router)) ||
      (IPV4_ADDR_CMP (&nbr->address.u.prefix4, &hello->d_router) &&
       IPV4_ADDR_SAME (&nbr->address.u.prefix4, &nbr->d_router)))
    OSPF_ISM_EVENT_SCHEDULE (oi, ISM_NeighborChange);


  if ((IPV4_ADDR_SAME (&nbr->address.u.prefix4, &hello->bd_router) &&
       IPV4_ADDR_CMP (&nbr->address.u.prefix4, &nbr->bd_router)) ||
      (IPV4_ADDR_CMP (&nbr->address.u.prefix4, &hello->bd_router) &&
       IPV4_ADDR_SAME (&nbr->address.u.prefix4, &nbr->bd_router)))
    OSPF_ISM_EVENT_SCHEDULE (oi, ISM_NeighborChange);


  if (nbr->priority >= 0 && nbr->priority != hello->priority)
    OSPF_ISM_EVENT_SCHEDULE (oi, ISM_NeighborChange);


  nbr->priority = hello->priority;
  nbr->d_router = hello->d_router;
  nbr->bd_router = hello->bd_router;
}
