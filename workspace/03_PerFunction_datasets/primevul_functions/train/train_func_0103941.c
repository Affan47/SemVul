ospf_ls_upd (struct ip *iph, struct ospf_header *ospfh,
	     struct stream *s, struct ospf_interface *oi, u_int16_t size)
{
  struct ospf_neighbor *nbr;
  struct list *lsas;
  struct listnode *node, *nnode;
  struct ospf_lsa *lsa = NULL;


  oi->ls_upd_in++;


  nbr = ospf_nbr_lookup (oi, iph, ospfh);
  if (nbr == NULL)
    {
      zlog_warn ("Link State Update: Unknown Neighbor %s on int: %s",
		 inet_ntoa (ospfh->router_id), IF_NAME (oi));
      return;
    }


  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_PacketReceived);


  if (nbr->state < NSM_Exchange)
    {
      zlog_warn ("Link State Update: "
      		 "Neighbor[%s] state %s is less than Exchange",
		 inet_ntoa (ospfh->router_id),
		 LOOKUP(ospf_nsm_state_msg, nbr->state));
      return;
    }


  lsas = ospf_ls_upd_list_lsa (nbr, s, oi, size);

#ifdef HAVE_OPAQUE_LSA


   ospf_opaque_adjust_lsreq (nbr, lsas);
#endif

#define DISCARD_LSA(L,N) {\
        if (IS_DEBUG_OSPF_EVENT) \
          zlog_debug ("ospf_lsa_discard() in ospf_ls_upd() point %d: lsa %p Type-%d", N, lsa, (int) lsa->data->type); \
        ospf_lsa_discard (L); \
	continue; }


  for (ALL_LIST_ELEMENTS (lsas, node, nnode, lsa))
    {
      struct ospf_lsa *ls_ret, *current;
      int ret = 1;

      if (IS_DEBUG_OSPF_NSSA)
	{
	  char buf1[INET_ADDRSTRLEN];
	  char buf2[INET_ADDRSTRLEN];
	  char buf3[INET_ADDRSTRLEN];

	  zlog_debug("LSA Type-%d from %s, ID: %s, ADV: %s",
		  lsa->data->type,
		  inet_ntop (AF_INET, &ospfh->router_id,
			     buf1, INET_ADDRSTRLEN),
		  inet_ntop (AF_INET, &lsa->data->id,
			     buf2, INET_ADDRSTRLEN),
		  inet_ntop (AF_INET, &lsa->data->adv_router,
			     buf3, INET_ADDRSTRLEN));
	}

      listnode_delete (lsas, lsa);


      if (lsa->data->type == OSPF_AS_EXTERNAL_LSA)

        if (nbr->oi->area->external_routing != OSPF_AREA_DEFAULT)
	  {
	    if (IS_DEBUG_OSPF_NSSA)
	      zlog_debug("Incoming External LSA Discarded: We are NSSA/STUB Area");
	    DISCARD_LSA (lsa, 1);
	  }

      if (lsa->data->type == OSPF_AS_NSSA_LSA)
	if (nbr->oi->area->external_routing != OSPF_AREA_NSSA)
	  {
	    if (IS_DEBUG_OSPF_NSSA)
	      zlog_debug("Incoming NSSA LSA Discarded:  Not NSSA Area");
	    DISCARD_LSA (lsa,2);
	  }


      current = ospf_lsa_lookup_by_header (oi->area, lsa->data);


      if (IS_LSA_MAXAGE (lsa) && !current &&
	  (ospf_nbr_count (oi, NSM_Exchange) +
	   ospf_nbr_count (oi, NSM_Loading)) == 0)
	{

	  ospf_ls_ack_send (nbr, lsa);


	  zlog_info ("Link State Update[%s]: LS age is equal to MaxAge.",
		     dump_lsa_key(lsa));
          DISCARD_LSA (lsa, 3);
	}

#ifdef HAVE_OPAQUE_LSA
      if (IS_OPAQUE_LSA (lsa->data->type)
      &&  IPV4_ADDR_SAME (&lsa->data->adv_router, &oi->ospf->router_id))
        {


          if (IS_LSA_MAXAGE (lsa))
            {
              zlog_warn ("LSA[%s]: Boomerang effect?", dump_lsa_key (lsa));
              ospf_ls_ack_send (nbr, lsa);
              ospf_lsa_discard (lsa);

              if (current != NULL && ! IS_LSA_MAXAGE (current))
                ospf_opaque_lsa_refresh_schedule (current);
              continue;
            }


          if (current == NULL)
            {
              if (IS_DEBUG_OSPF_EVENT)
                zlog_debug ("LSA[%s]: Previously originated Opaque-LSA,"
                            "not found in the LSDB.", dump_lsa_key (lsa));

              SET_FLAG (lsa->flags, OSPF_LSA_SELF);

              ospf_opaque_self_originated_lsa_received (nbr, lsa);
              ospf_ls_ack_send (nbr, lsa);

              continue;
            }
        }
#endif


      if(lsa->data->type == OSPF_NETWORK_LSA)
      {
        struct listnode *oinode, *oinnode;
        struct ospf_interface *out_if;
        int Flag = 0;

        for (ALL_LIST_ELEMENTS (oi->ospf->oiflist, oinode, oinnode, out_if))
        {
          if(out_if == NULL)
            break;

          if((IPV4_ADDR_SAME(&out_if->address->u.prefix4, &lsa->data->id)) &&
              (!(IPV4_ADDR_SAME(&oi->ospf->router_id, &lsa->data->adv_router))))
          {
            if(out_if->network_lsa_self)
            {
              ospf_lsa_flush_area(lsa,out_if->area);
              if(IS_DEBUG_OSPF_EVENT)
                zlog_debug ("ospf_lsa_discard() in ospf_ls_upd() point 9: lsa %p Type-%d",
                            lsa, (int) lsa->data->type);
              ospf_lsa_discard (lsa);
              Flag = 1;
            }
            break;
          }
        }
        if(Flag)
          continue;
      }


      if (current == NULL ||
	  (ret = ospf_lsa_more_recent (current, lsa)) < 0)
	{

	  if (ospf_flood (oi->ospf, nbr, current, lsa) < 0)
	    DISCARD_LSA (lsa, 4);
	  continue;
	}


      if (ospf_ls_request_lookup (nbr, lsa))
	{
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_BadLSReq);
	  zlog_warn("LSA[%s] instance exists on Link state request list",
	  	    dump_lsa_key(lsa));


          ospf_upd_list_clean (lsas);

	  ospf_lsa_discard (lsa);
	  return;
	}


      if (ret == 0)
	{


	  ls_ret = ospf_ls_retransmit_lookup (nbr, lsa);

	  if (ls_ret != NULL)
	    {
	      ospf_ls_retransmit_delete (nbr, ls_ret);


	      if (oi->state == ISM_Backup)
		if (NBR_IS_DR (nbr))
		  listnode_add (oi->ls_ack, ospf_lsa_lock (lsa));

              DISCARD_LSA (lsa, 5);
	    }
	  else


	    {
	      ospf_ls_ack_send (nbr, lsa);
	      DISCARD_LSA (lsa, 6);
	    }
	}


      else if (ret > 0)
	{
	  if (IS_LSA_MAXAGE (current) &&
	      current->data->ls_seqnum == htonl (OSPF_MAX_SEQUENCE_NUMBER))
	    {
	      DISCARD_LSA (lsa, 7);
	    }


	  else
	    {
	      struct timeval now;

	      quagga_gettime (QUAGGA_CLK_MONOTONIC, &now);

	      if (tv_cmp (tv_sub (now, current->tv_orig),
			  int2tv (OSPF_MIN_LS_ARRIVAL)) >= 0)

		ospf_ls_upd_send_lsa (nbr, current, OSPF_SEND_PACKET_DIRECT);
	      DISCARD_LSA (lsa, 8);
	    }
	}
    }
#undef DISCARD_LSA

  assert (listcount (lsas) == 0);
  list_delete (lsas);
}
