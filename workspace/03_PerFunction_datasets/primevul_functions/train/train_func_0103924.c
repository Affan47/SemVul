ospf_ls_upd_queue_send (struct ospf_interface *oi, struct list *update,
			struct in_addr addr)
{
  struct ospf_packet *op;
  u_int16_t length = OSPF_HEADER_SIZE;

  if (IS_DEBUG_OSPF_EVENT)
    zlog_debug ("listcount = %d, dst %s", listcount (update), inet_ntoa(addr));

  op = ospf_ls_upd_packet_new (update, oi);


  ospf_make_header (OSPF_MSG_LS_UPD, oi, op->s);


  length += ospf_make_ls_upd (oi, update, op->s);


  ospf_fill_header (oi, op->s, length);


  op->length = length;


  if (oi->type == OSPF_IFTYPE_POINTOPOINT)
    op->dst.s_addr = htonl (OSPF_ALLSPFROUTERS);
  else
    op->dst.s_addr = addr.s_addr;


  ospf_packet_add (oi, op);


  OSPF_ISM_WRITE_ON (oi->ospf);
}
