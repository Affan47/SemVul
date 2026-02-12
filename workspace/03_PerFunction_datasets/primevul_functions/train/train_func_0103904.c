ospf_db_desc_send (struct ospf_neighbor *nbr)
{
  struct ospf_interface *oi;
  struct ospf_packet *op;
  u_int16_t length = OSPF_HEADER_SIZE;

  oi = nbr->oi;
  op = ospf_packet_new (oi->ifp->mtu);


  ospf_make_header (OSPF_MSG_DB_DESC, oi, op->s);


  length += ospf_make_db_desc (oi, nbr, op->s);


  ospf_fill_header (oi, op->s, length);


  op->length = length;


  if (oi->type == OSPF_IFTYPE_POINTOPOINT)
    op->dst.s_addr = htonl (OSPF_ALLSPFROUTERS);
  else
    op->dst = nbr->address.u.prefix4;


  ospf_packet_add (oi, op);


  OSPF_ISM_WRITE_ON (oi->ospf);


  if (nbr->last_send)
    ospf_packet_free (nbr->last_send);
  nbr->last_send = ospf_packet_dup (op);
  quagga_gettime (QUAGGA_CLK_MONOTONIC, &nbr->last_send_ts);
}
