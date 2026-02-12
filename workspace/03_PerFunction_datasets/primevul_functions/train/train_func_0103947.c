ospf_hello_send_sub (struct ospf_interface *oi, in_addr_t addr)
{
  struct ospf_packet *op;
  u_int16_t length = OSPF_HEADER_SIZE;

  op = ospf_packet_new (oi->ifp->mtu);


  ospf_make_header (OSPF_MSG_HELLO, oi, op->s);


  length += ospf_make_hello (oi, op->s);


  ospf_fill_header (oi, op->s, length);


  op->length = length;

  op->dst.s_addr = addr;


  ospf_packet_add_top (oi, op);


  OSPF_ISM_WRITE_ON (oi->ospf);
}
