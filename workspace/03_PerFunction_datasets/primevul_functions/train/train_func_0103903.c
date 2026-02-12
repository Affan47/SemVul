ospf_hello_send (struct ospf_interface *oi)
{

  if (OSPF_IF_PASSIVE_STATUS (oi) == OSPF_IF_PASSIVE)
    return;

  if (oi->type == OSPF_IFTYPE_NBMA)
    {
      struct ospf_neighbor *nbr;
      struct route_node *rn;

      for (rn = route_top (oi->nbrs); rn; rn = route_next (rn))
	if ((nbr = rn->info))
	  if (nbr != oi->nbr_self)
	    if (nbr->state != NSM_Down)
	      {


		if (PRIORITY(oi) == 0 &&
		    IPV4_ADDR_CMP(&DR(oi),  &nbr->address.u.prefix4) &&
		    IPV4_ADDR_CMP(&BDR(oi), &nbr->address.u.prefix4))
		  continue;


		if (nbr->priority == 0 && oi->state == ISM_DROther)
		  continue;

		ospf_hello_send_sub (oi, nbr->address.u.prefix4.s_addr);
	      }
    }
  else
    {

      if (oi->type == OSPF_IFTYPE_VIRTUALLINK)
        ospf_hello_send_sub (oi, oi->vl_data->peer_addr.s_addr);
      else
        ospf_hello_send_sub (oi, htonl (OSPF_ALLSPFROUTERS));
    }
}
