dirserv_router_has_valid_address(routerinfo_t *ri)
{
  struct in_addr iaddr;
  if (get_options()->DirAllowPrivateAddresses)
    return 0;
  if (!tor_inet_aton(ri->address, &iaddr)) {
    log_info(LD_DIRSERV,"Router %s published non-IP address '%s'. Refusing.",
             router_describe(ri),
             ri->address);
    return -1;
  }
  if (is_internal_IP(ntohl(iaddr.s_addr), 0)) {
    log_info(LD_DIRSERV,
             "Router %s published internal IP address '%s'. Refusing.",
             router_describe(ri), ri->address);
    return -1;
  }
  return 0;
}
