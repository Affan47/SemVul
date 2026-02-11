init_route (struct route *r,
	    const struct route_option *ro,
	    const struct route_special_addr *spec)
{
  const in_addr_t default_netmask = ~0;
  bool status;

  r->option = ro;
  r->defined = false;


  if (!is_route_parm_defined (ro->network))
    {
      goto fail;
    }

  if (!get_special_addr (spec, ro->network, &r->network, &status))
    {
      r->network = getaddr (
			    GETADDR_RESOLVE
			    | GETADDR_HOST_ORDER
			    | GETADDR_WARN_ON_SIGNAL,
			    ro->network,
			    0,
			    &status,
			    NULL);
    }

  if (!status)
    goto fail;


  if (is_route_parm_defined (ro->netmask))
    {
      r->netmask = getaddr (
			    GETADDR_HOST_ORDER
			    | GETADDR_WARN_ON_SIGNAL,
			    ro->netmask,
			    0,
			    &status,
			    NULL);
      if (!status)
	goto fail;
    }
  else
    r->netmask = default_netmask;


  if (is_route_parm_defined (ro->gateway))
    {
      if (!get_special_addr (spec, ro->gateway, &r->gateway, &status))
	{
	  r->gateway = getaddr (
				GETADDR_RESOLVE
				| GETADDR_HOST_ORDER
				| GETADDR_WARN_ON_SIGNAL,
				ro->gateway,
				0,
				&status,
				NULL);
	}
      if (!status)
	goto fail;
    }
  else
    {
      if (spec->remote_endpoint_defined)
	r->gateway = spec->remote_endpoint;
      else
	{
	  msg (M_WARN, PACKAGE_NAME " ROUTE: " PACKAGE_NAME " needs a gateway parameter for a --route option and no default was specified by either --route-gateway or --ifconfig options");
	  goto fail;
	}
    }


  r->metric_defined = false;
  r->metric = 0;
  if (is_route_parm_defined (ro->metric))
    {
      r->metric = atoi (ro->metric);
      if (r->metric < 0)
	{
	  msg (M_WARN, PACKAGE_NAME " ROUTE: route metric for network %s (%s) must be >= 0",
	       ro->network,
	       ro->metric);
	  goto fail;
	}
      r->metric_defined = true;
    }
  else if (spec->default_metric_defined)
    {
      r->metric = spec->default_metric;
      r->metric_defined = true;
    }

  r->defined = true;

  return true;

 fail:
  msg (M_WARN, PACKAGE_NAME " ROUTE: failed to parse/resolve route for host/network: %s",
       ro->network);
  r->defined = false;
  return false;
}
