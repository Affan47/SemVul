net_linux_gethostbyname(JsNetwork *net, char * hostName, unsigned long* out_ip_addr) {
  NOT_USED(net);
  struct hostent * host_addr_p = gethostbyname(hostName);
  if (host_addr_p)
    *out_ip_addr = *(unsigned long*)*host_addr_p->h_addr_list;
}
