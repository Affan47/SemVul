maybe_lookup_host(u8* name) {
  struct hostent* h;
  struct dns_entry *d = dns, *prev = NULL;
  u32 ret_addr = 0;
  struct in_addr in;

#ifdef PROXY_SUPPORT


  if (use_proxy) {

    if (!use_proxy_addr) {


      if (inet_aton((char*)use_proxy, &in))
        return (use_proxy_addr = (u32)in.s_addr);

      h = gethostbyname((char*)use_proxy);


      if (!h && h_errno == TRY_AGAIN) h = gethostbyname((char*)name);

      if (!h || !(use_proxy_addr = *(u32*)h->h_addr_list[0]))
        FATAL("Unable to resolve proxy host name '%s'.", use_proxy);

    }

    return use_proxy_addr;

  }


#endif


  if (inet_aton((char*)name, &in))
    return (u32)in.s_addr;

  while (d) {
    if (!strcasecmp((char*)name, (char*)d->name)) return d->addr;
    prev = d;
    d = d->next;
  }

  h = gethostbyname((char*)name);


  if (!h && h_errno == TRY_AGAIN) h = gethostbyname((char*)name);

  if (h) {

    u32 i = 0;


    while (h->h_addr_list[i]) {
      d = dns;
      while (d) {
        if (d->addr == *(u32*)h->h_addr_list[i]) {
          ret_addr = d->addr;
          goto dns_got_name;
        }
        d = d->next;
      }
      i++;
    }

    ret_addr = *(u32*)h->h_addr_list[0];

  }

dns_got_name:

  if (!prev) d = dns = ck_alloc(sizeof(struct dns_entry));
    else d = prev->next = ck_alloc(sizeof(struct dns_entry));

  d->name = ck_strdup(name);
  d->addr = ret_addr;

  return ret_addr;

}
