ospf_make_hello (struct ospf_interface *oi, struct stream *s)
{
  struct ospf_neighbor *nbr;
  struct route_node *rn;
  u_int16_t length = OSPF_HELLO_MIN_SIZE;
  struct in_addr mask;
  unsigned long p;
  int flag = 0;


  if (oi->type != OSPF_IFTYPE_POINTOPOINT &&
      oi->type != OSPF_IFTYPE_VIRTUALLINK)
    masklen2ip (oi->address->prefixlen, &mask);
  else
    memset ((char *) &mask, 0, sizeof (struct in_addr));
  stream_put_ipv4 (s, mask.s_addr);


  if (OSPF_IF_PARAM (oi, fast_hello) == 0)
    stream_putw (s, OSPF_IF_PARAM (oi, v_hello));
  else
    stream_putw (s, 0);

  if (IS_DEBUG_OSPF_EVENT)
    zlog_debug ("make_hello: options: %x, int: %s",
	       OPTIONS(oi), IF_NAME (oi));


  stream_putc (s, OPTIONS (oi));


  stream_putc (s, PRIORITY (oi));


  stream_putl (s, OSPF_IF_PARAM (oi, v_wait));


  stream_put_ipv4 (s, DR (oi).s_addr);

  p = stream_get_endp (s);


  stream_put_ipv4 (s, BDR (oi).s_addr);


  for (rn = route_top (oi->nbrs); rn; rn = route_next (rn))
    if ((nbr = rn->info))
      if (nbr->router_id.s_addr != 0)
	if (nbr->state != NSM_Attempt)
	if (nbr->state != NSM_Down)
	  if (!IPV4_ADDR_SAME (&nbr->router_id, &oi->ospf->router_id))
	    {

	      if (nbr->d_router.s_addr != 0
		  && IPV4_ADDR_SAME (&nbr->d_router, &oi->address->u.prefix4)
		  && IPV4_ADDR_SAME (&nbr->bd_router, &oi->address->u.prefix4))
		flag = 1;

	      stream_put_ipv4 (s, nbr->router_id.s_addr);
	      length += 4;
	    }


  if (flag == 1)
    stream_putl_at (s, p, 0);

  return length;
}
