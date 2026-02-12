remote_post_process(address_item *addr, int logflags, uschar *msg,
  BOOL fallback)
{
host_item *h;


for (h = addr->host_list; h; h = h->next)
  if (h->address)
    if (h->status >= hstatus_unusable) tree_add_unusable(h);


while (addr)
  {
  address_item *next = addr->next;


  if (  addr->transport_return == DEFER
     && addr->fallback_hosts
     && !fallback
     && !msg
     )
    {
    addr->host_list = addr->fallback_hosts;
    addr->next = addr_fallback;
    addr_fallback = addr;
    DEBUG(D_deliver) debug_printf("%s queued for fallback host(s)\n", addr->address);
    }


  else
    {
    if (msg)
      {
      addr->message = msg;
      addr->transport_return = DEFER;
      }
    (void)post_process_one(addr, addr->transport_return, logflags,
      EXIM_DTYPE_TRANSPORT, addr->special_action);
    }


  addr = next;
  }


if (!continue_transport) continue_sequence = 1;
}
