ospf_ls_ack_send_list (struct ospf_interface *oi, struct list *ack,
		       struct in_addr dst)
{
  struct ospf_packet *op;
  u_int16_t length = OSPF_HEADER_SIZE;

  op = ospf_packet_new (oi->ifp->mtu);


  ospf_make_header (OSPF_MSG_LS_ACK, oi, op->s);


  length += ospf_make_ls_ack (oi, ack, op->s);


  ospf_fill_header (oi, op->s, length);


  op->length = length;


  op->dst = dst;


  ospf_packet_add (oi, op);


  OSPF_ISM_WRITE_ON (oi->ospf);
}
