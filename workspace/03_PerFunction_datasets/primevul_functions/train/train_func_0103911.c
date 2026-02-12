ospf_db_desc (struct ip *iph, struct ospf_header *ospfh,
	      struct stream *s, struct ospf_interface *oi, u_int16_t size)
{
  struct ospf_db_desc *dd;
  struct ospf_neighbor *nbr;


  oi->db_desc_in++;

  dd = (struct ospf_db_desc *) STREAM_PNT (s);

  nbr = ospf_nbr_lookup (oi, iph, ospfh);
  if (nbr == NULL)
    {
      zlog_warn ("Packet[DD]: Unknown Neighbor %s",
		 inet_ntoa (ospfh->router_id));
      return;
    }


  if ((OSPF_IF_PARAM (oi, mtu_ignore) == 0) &&
      (ntohs (dd->mtu) > oi->ifp->mtu))
    {
      zlog_warn ("Packet[DD]: Neighbor %s MTU %u is larger than [%s]'s MTU %u",
		 inet_ntoa (nbr->router_id), ntohs (dd->mtu),
		 IF_NAME (oi), oi->ifp->mtu);
      return;
    }


  if ( (oi->area->external_routing == OSPF_AREA_NSSA)
       && (CHECK_FLAG (nbr->options, OSPF_OPTION_NP))
       && (!CHECK_FLAG (dd->options, OSPF_OPTION_NP)) )
    {
      if (IS_DEBUG_OSPF_EVENT)
        zlog_debug ("Packet[DD]: Neighbour %s: Has NSSA capability, sends with N bit clear in DD options",
                    inet_ntoa (nbr->router_id) );
      SET_FLAG (dd->options, OSPF_OPTION_NP);
    }

#ifdef REJECT_IF_TBIT_ON
  if (CHECK_FLAG (dd->options, OSPF_OPTION_T))
    {


      zlog_warn ("Packet[DD]: Neighbor %s: T-bit on?", inet_ntoa (nbr->router_id));
      return;
    }
#endif

#ifdef HAVE_OPAQUE_LSA
  if (CHECK_FLAG (dd->options, OSPF_OPTION_O)
      && !CHECK_FLAG (oi->ospf->config, OSPF_OPAQUE_CAPABLE))
    {


      UNSET_FLAG (dd->options, OSPF_OPTION_O);
    }
#endif


  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_PacketReceived);


  switch (nbr->state)
    {
    case NSM_Down:
    case NSM_Attempt:
    case NSM_TwoWay:
      zlog_warn ("Packet[DD]: Neighbor %s state is %s, packet discarded.",
		 inet_ntoa(nbr->router_id),
		 LOOKUP (ospf_nsm_state_msg, nbr->state));
      break;
    case NSM_Init:
      OSPF_NSM_EVENT_EXECUTE (nbr, NSM_TwoWayReceived);


      if (nbr->state != NSM_ExStart)
	break;
    case NSM_ExStart:

      if ((IS_SET_DD_ALL (dd->flags) == OSPF_DD_FLAG_ALL) &&
	  (size == OSPF_DB_DESC_MIN_SIZE))
	{
	  if (IPV4_ADDR_CMP (&nbr->router_id, &oi->ospf->router_id) > 0)
	    {

	      zlog_info ("Packet[DD]: Neighbor %s Negotiation done (Slave).",
	      		 inet_ntoa(nbr->router_id));
	      nbr->dd_seqnum = ntohl (dd->dd_seqnum);


	      UNSET_FLAG (nbr->dd_flags, (OSPF_DD_FLAG_MS|OSPF_DD_FLAG_I));
	    }
	  else
	    {

	      zlog_info ("Packet[DD]: Neighbor %s: Initial DBD from Slave, "
	      		 "ignoring.", inet_ntoa(nbr->router_id));
	      break;
	    }
	}

      else if (!IS_SET_DD_MS (dd->flags) && !IS_SET_DD_I (dd->flags) &&
	       ntohl (dd->dd_seqnum) == nbr->dd_seqnum &&
	       IPV4_ADDR_CMP (&nbr->router_id, &oi->ospf->router_id) < 0)
	{
	  zlog_info ("Packet[DD]: Neighbor %s Negotiation done (Master).",
		     inet_ntoa(nbr->router_id));

          UNSET_FLAG (nbr->dd_flags, OSPF_DD_FLAG_I);
	}
      else
	{
	  zlog_warn ("Packet[DD]: Neighbor %s Negotiation fails.",
		     inet_ntoa(nbr->router_id));
	  break;
	}


      nbr->options = dd->options;

#ifdef HAVE_OPAQUE_LSA
      if (CHECK_FLAG (oi->ospf->config, OSPF_OPAQUE_CAPABLE))
        {
          if (IS_DEBUG_OSPF_EVENT)
            zlog_debug ("Neighbor[%s] is %sOpaque-capable.",
		       inet_ntoa (nbr->router_id),
		       CHECK_FLAG (nbr->options, OSPF_OPTION_O) ? "" : "NOT ");

          if (! CHECK_FLAG (nbr->options, OSPF_OPTION_O)
          &&  IPV4_ADDR_SAME (&DR (oi), &nbr->address.u.prefix4))
            {
              zlog_warn ("DR-neighbor[%s] is NOT opaque-capable; "
                         "Opaque-LSAs cannot be reliably advertised "
                         "in this network.",
                         inet_ntoa (nbr->router_id));

            }
        }
#endif

      OSPF_NSM_EVENT_EXECUTE (nbr, NSM_NegotiationDone);


      ospf_db_desc_proc (s, oi, nbr, dd, size);
      break;
    case NSM_Exchange:
      if (ospf_db_desc_is_dup (dd, nbr))
	{
	  if (IS_SET_DD_MS (nbr->dd_flags))

	    zlog_info ("Packet[DD] (Master): Neighbor %s packet duplicated.",
		       inet_ntoa (nbr->router_id));
	  else

	    {
	      zlog_info ("Packet[DD] [Slave]: Neighbor %s packet duplicated.",
			 inet_ntoa (nbr->router_id));
	      ospf_db_desc_resend (nbr);
	    }
	  break;
	}


      if (IS_SET_DD_MS (dd->flags) != IS_SET_DD_MS (nbr->last_recv.flags))
	{
	  zlog_warn ("Packet[DD]: Neighbor %s MS-bit mismatch.",
		     inet_ntoa(nbr->router_id));
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
	  if (IS_DEBUG_OSPF_EVENT)
	    zlog_debug ("Packet[DD]: dd->flags=%d, nbr->dd_flags=%d",
		        dd->flags, nbr->dd_flags);
	  break;
	}


      if (IS_SET_DD_I (dd->flags))
	{
	  zlog_info ("Packet[DD]: Neighbor %s I-bit set.",
		     inet_ntoa(nbr->router_id));
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
	  break;
	}


      if (dd->options != nbr->options)
	{
#ifdef ORIGINAL_CODING

	  nbr->options = dd->options;
#endif
	  zlog_warn ("Packet[DD]: Neighbor %s options mismatch.",
		     inet_ntoa(nbr->router_id));
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
	  break;
	}


      if ((IS_SET_DD_MS (nbr->dd_flags) &&
	   ntohl (dd->dd_seqnum) != nbr->dd_seqnum) ||
	  (!IS_SET_DD_MS (nbr->dd_flags) &&
	   ntohl (dd->dd_seqnum) != nbr->dd_seqnum + 1))
	{
	  zlog_warn ("Packet[DD]: Neighbor %s sequence number mismatch.",
		     inet_ntoa(nbr->router_id));
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
	  break;
	}


      ospf_db_desc_proc (s, oi, nbr, dd, size);
      break;
    case NSM_Loading:
    case NSM_Full:
      if (ospf_db_desc_is_dup (dd, nbr))
	{
	  if (IS_SET_DD_MS (nbr->dd_flags))
	    {

	      zlog_info ("Packet[DD]: Neighbor %s duplicated, "
	                 "packet discarded.",
			inet_ntoa(nbr->router_id));
	      break;
	    }
	  else
	    {
	      struct timeval t, now;
	      quagga_gettime (QUAGGA_CLK_MONOTONIC, &now);
	      t = tv_sub (now, nbr->last_send_ts);
	      if (tv_cmp (t, int2tv (nbr->v_inactivity)) < 0)
		{


		  ospf_db_desc_resend (nbr);
		  break;
		}
	    }
	}

      OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
      break;
    default:
      zlog_warn ("Packet[DD]: Neighbor %s NSM illegal status %u.",
		 inet_ntoa(nbr->router_id), nbr->state);
      break;
    }
}
