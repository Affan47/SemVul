ospf_db_desc_proc (struct stream *s, struct ospf_interface *oi,
		   struct ospf_neighbor *nbr, struct ospf_db_desc *dd,
		   u_int16_t size)
{
  struct ospf_lsa *new, *find;
  struct lsa_header *lsah;

  stream_forward_getp (s, OSPF_DB_DESC_MIN_SIZE);
  for (size -= OSPF_DB_DESC_MIN_SIZE;
       size >= OSPF_LSA_HEADER_SIZE; size -= OSPF_LSA_HEADER_SIZE)
    {
      lsah = (struct lsa_header *) STREAM_PNT (s);
      stream_forward_getp (s, OSPF_LSA_HEADER_SIZE);


      if (lsah->type < OSPF_MIN_LSA || lsah->type >= OSPF_MAX_LSA)
	{
	  zlog_warn ("Packet [DD:RECV]: Unknown LS type %d.", lsah->type);
	  OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
	  return;
	}

#ifdef HAVE_OPAQUE_LSA
      if (IS_OPAQUE_LSA (lsah->type)
      &&  ! CHECK_FLAG (nbr->options, OSPF_OPTION_O))
        {
          zlog_warn ("LSA[Type%d:%s]: Opaque capability mismatch?", lsah->type, inet_ntoa (lsah->id));
          OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
          return;
        }
#endif

      switch (lsah->type)
        {
        case OSPF_AS_EXTERNAL_LSA:
#ifdef HAVE_OPAQUE_LSA
	case OSPF_OPAQUE_AS_LSA:
#endif


          if (oi->area->external_routing == OSPF_AREA_STUB)
            {
              zlog_warn ("Packet [DD:RECV]: LSA[Type%d:%s] from %s area.",
                         lsah->type, inet_ntoa (lsah->id),
                         (oi->area->external_routing == OSPF_AREA_STUB) ?\
                         "STUB" : "NSSA");
              OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_SeqNumberMismatch);
              return;
            }
          break;
	default:
	  break;
        }


      new = ospf_ls_request_new (lsah);


      find = ospf_lsa_lookup_by_header (oi->area, lsah);


      switch (ospf_lsa_more_recent (find, new))
        {
          case -1:

            ospf_ls_request_add (nbr, new);
          case 0:


            if (find)
              ospf_lsdb_delete (&nbr->db_sum, find);
            ospf_lsa_discard (new);
            break;
          default:


            if (IS_DEBUG_OSPF_EVENT)
              zlog_debug ("Packet [DD:RECV]: LSA received Type %d, "
                         "ID %s is not recent.", lsah->type, inet_ntoa (lsah->id));
            ospf_lsa_discard (new);
        }
    }


  if (IS_SET_DD_MS (nbr->dd_flags))
    {
      nbr->dd_seqnum++;


      if (!IS_SET_DD_M (dd->flags) && !IS_SET_DD_M (nbr->dd_flags))
	OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_ExchangeDone);
      else
	ospf_db_desc_send (nbr);
    }

  else
    {
      nbr->dd_seqnum = ntohl (dd->dd_seqnum);


      ospf_db_desc_send (nbr);


      if (!IS_SET_DD_M (dd->flags) && !IS_SET_DD_M (nbr->dd_flags))
	OSPF_NSM_EVENT_SCHEDULE (nbr, NSM_ExchangeDone);
    }


  ospf_db_desc_save_current (nbr, dd);
}
