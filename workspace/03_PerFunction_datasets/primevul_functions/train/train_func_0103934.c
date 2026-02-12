ospf_ls_req_send (struct ospf_neighbor *nbr)
{
  struct ospf_interface *oi;
  struct ospf_packet *op;
  u_int16_t length = OSPF_HEADER_SIZE;

  oi = nbr->oi;
  op = ospf_packet_new (oi->ifp->mtu);


  ospf_make_header (OSPF_MSG_LS_REQ, oi, op->s);


  length += ospf_make_ls_req (nbr, op->s);
  if (length == OSPF_HEADER_SIZE)
    {
      ospf_packet_free (op);
      return;
    }


  ospf_fill_header (oi, op->s, length);


  op->length = length;


  if (oi->type == OSPF_IFTYPE_POINTOPOINT)
    op->dst.s_addr = htonl (OSPF_ALLSPFROUTERS);
  else
    op->dst = nbr->address.u.prefix4;


  ospf_packet_add (oi, op);


  OSPF_ISM_WRITE_ON (oi->ospf);


  OSPF_NSM_TIMER_ON (nbr->t_ls_req, ospf_ls_req_timer, nbr->v_ls_req);
}
