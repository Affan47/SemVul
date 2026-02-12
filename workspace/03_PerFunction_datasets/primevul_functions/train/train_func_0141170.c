do_remote_deliveries(BOOL fallback)
{
int parmax;
int delivery_count;
int poffset;

parcount = 0;


if (continue_transport) remote_max_parallel = 1;
parmax = remote_max_parallel;


if (!parlist)
  {
  parlist = store_get(remote_max_parallel * sizeof(pardata));
  for (poffset = 0; poffset < remote_max_parallel; poffset++)
    parlist[poffset].pid = 0;
  }


for (delivery_count = 0; addr_remote; delivery_count++)
  {
  pid_t pid;
  uid_t uid;
  gid_t gid;
  int pfd[2];
  int address_count = 1;
  int address_count_max;
  BOOL multi_domain;
  BOOL use_initgroups;
  BOOL pipe_done = FALSE;
  transport_instance *tp;
  address_item **anchor = &addr_remote;
  address_item *addr = addr_remote;
  address_item *last = addr;
  address_item *next;
  uschar * panicmsg;
  uschar * serialize_key = NULL;


  addr_remote = addr->next;
  addr->next = NULL;

  DEBUG(D_deliver|D_transport)
    debug_printf("--------> %s <--------\n", addr->address);


  if (!(tp = addr->transport))
    {
    disable_logging = FALSE;
    panicmsg = US"No transport set by router";
    goto panic_continue;
    }


  if (previously_transported(addr, FALSE)) continue;


  if (tp->message_size_limit)
    {
    int rc = check_message_size(tp, addr);
    if (rc != OK)
      {
      addr->transport_return = rc;
      remote_post_process(addr, LOG_MAIN, NULL, fallback);
      continue;
      }
    }


  if (tp->expand_multi_domain)
    deliver_set_expansions(addr);

  if (exp_bool(addr, US"transport", tp->name, D_transport,
		US"multi_domain", tp->multi_domain, tp->expand_multi_domain,
		&multi_domain) != OK)
    {
    deliver_set_expansions(NULL);
    panicmsg = addr->message;
    goto panic_continue;
    }


  address_count_max = tp->max_addresses;
  if (address_count_max == 0 || mua_wrapper) address_count_max = 999999;


  if (  address_count_max != 1
     && address_count_max < remote_delivery_count/remote_max_parallel
     )
    {
    int new_max = remote_delivery_count/remote_max_parallel;
    int message_max = tp->connection_max_messages;
    if (connection_max_messages >= 0) message_max = connection_max_messages;
    message_max -= continue_sequence - 1;
    if (message_max > 0 && new_max > address_count_max * message_max)
      new_max = address_count_max * message_max;
    address_count_max = new_max;
    }


  while ((next = *anchor) && address_count < address_count_max)
    {
    BOOL md;
    if (  (multi_domain || Ustrcmp(next->domain, addr->domain) == 0)
       && tp == next->transport
       && same_hosts(next->host_list, addr->host_list)
       && same_strings(next->prop.errors_address, addr->prop.errors_address)
       && same_headers(next->prop.extra_headers, addr->prop.extra_headers)
       && same_ugid(tp, next, addr)
       && (  next->prop.remove_headers == addr->prop.remove_headers
	  || (  next->prop.remove_headers
	     && addr->prop.remove_headers
	     && Ustrcmp(next->prop.remove_headers, addr->prop.remove_headers) == 0
	  )  )
       && (  !multi_domain
	  || (  (
		(void)(!tp->expand_multi_domain || ((void)deliver_set_expansions(next), 1)),
	        exp_bool(addr,
		    US"transport", next->transport->name, D_transport,
		    US"multi_domain", next->transport->multi_domain,
		    next->transport->expand_multi_domain, &md) == OK
	        )
	     && md
       )  )  )
      {
      *anchor = next->next;
      next->next = NULL;
      next->first = addr;
      last->next = next;
      last = next;
      address_count++;
      }
    else anchor = &(next->next);
    deliver_set_expansions(NULL);
    }


  if (mua_wrapper && addr_remote)
    {
    last->next = addr_remote;
    addr_remote = addr;
    return FALSE;
    }


  if (tpt_parallel_check(tp, addr, &serialize_key))
    if ((panicmsg = expand_string_message))
      goto panic_continue;
    else
      continue;


  deliver_set_expansions(addr);


  addr->authenticator = addr->auth_id = addr->auth_sndr = NULL;


  if(addr->prop.errors_address)
    return_path = addr->prop.errors_address;
#ifdef EXPERIMENTAL_SRS
  else if(addr->prop.srs_sender)
    return_path = addr->prop.srs_sender;
#endif
  else
    return_path = sender_address;

  if (tp->return_path)
    {
    uschar *new_return_path = expand_string(tp->return_path);
    if (new_return_path)
      return_path = new_return_path;
    else if (!expand_string_forcedfail)
      {
      panicmsg = string_sprintf("Failed to expand return path \"%s\": %s",
	tp->return_path, expand_string_message);
      goto enq_continue;
      }
    }


  if (!findugid(addr, tp, &uid, &gid, &use_initgroups))
    {
    panicmsg = NULL;
    goto enq_continue;
    }


  if (tp->setup)
    (void)((tp->setup)(addr->transport, addr, NULL, uid, gid, NULL));


  if (cutthrough.fd >= 0 && cutthrough.callout_hold_only)
    {
    DEBUG(D_deliver)
      debug_printf("lazy-callout-close: have conn still open from verification\n");
    continue_transport = cutthrough.transport;
    continue_hostname = string_copy(cutthrough.host.name);
    continue_host_address = string_copy(cutthrough.host.address);
    continue_sequence = 1;
    sending_ip_address = cutthrough.snd_ip;
    sending_port = cutthrough.snd_port;
    smtp_peer_options = cutthrough.peer_options;
    }


  continue_more = FALSE;
  if (continue_transport)
    {
    BOOL ok = Ustrcmp(continue_transport, tp->name) == 0;


    if (ok)
      {
      smtp_transport_options_block * ob;

      if (  !(  Ustrcmp(tp->info->driver_name, "smtp") == 0
	     && (ob = (smtp_transport_options_block *)tp->options_block)
	     && ob->hosts_override && ob->hosts
	     )
	 && addr->host_list
	 )
	{
	host_item * h;
	ok = FALSE;
	for (h = addr->host_list; h; h = h->next)
	  if (Ustrcmp(h->name, continue_hostname) == 0)

	    { ok = TRUE; break; }
	}
      }


    if (!ok)
      {
      DEBUG(D_deliver) debug_printf("not suitable for continue_transport (%s)\n",
	Ustrcmp(continue_transport, tp->name) != 0
	? string_sprintf("tpt %s vs %s", continue_transport, tp->name)
	: string_sprintf("no host matching %s", continue_hostname));
      if (serialize_key) enq_end(serialize_key);

      if (addr->fallback_hosts && !fallback)
        {
	for (next = addr; ; next = next->next)
          {
          next->host_list = next->fallback_hosts;
          DEBUG(D_deliver) debug_printf("%s queued for fallback host(s)\n", next->address);
          if (!next->next) break;
          }
        next->next = addr_fallback;
        addr_fallback = addr;
        }

      else
	{
	for (next = addr; ; next = next->next)
	  {
	  DEBUG(D_deliver) debug_printf(" %s to def list\n", next->address);
          if (!next->next) break;
	  }
	next->next = addr_defer;
	addr_defer = addr;
	}

      continue;
      }


    for (next = addr_remote; next && !continue_more; next = next->next)
      {
      host_item *h;
      for (h = next->host_list; h; h = h->next)
        if (Ustrcmp(h->name, continue_hostname) == 0)
          { continue_more = TRUE; break; }
      }
    }


  transport_filter_argv = NULL;


  while (!pipe_done)
    {
    if (pipe(pfd) == 0) pipe_done = TRUE;
      else if (parcount > 0) parmax = parcount;
        else break;


    par_reduce(parmax - 1, fallback);
    }


  if (!pipe_done)
    {
    panicmsg = string_sprintf("unable to create pipe: %s", strerror(errno));
    goto enq_continue;
    }


  for (poffset = 0; poffset < remote_max_parallel; poffset++)
    if (parlist[poffset].pid == 0)
      break;


  if (poffset >= remote_max_parallel)
    {
    (void)close(pfd[pipe_write]);
    (void)close(pfd[pipe_read]);
    panicmsg = US"Unexpectedly no free subprocess slot";
    goto enq_continue;
    }


  search_tidyup();


  if ((pid = fork()) == 0)
    {
    int fd = pfd[pipe_write];
    host_item *h;
    DEBUG(D_deliver) debug_selector |= D_pid;


    transport_name = tp->name;


    disable_logging = tp->disable_logging;


    if (parmax > 1 && (parcount > 0 || addr_remote))
      {
      DEBUG(D_any|D_v) debug_selector |= D_pid;
      DEBUG(D_deliver) debug_printf("Remote delivery process started\n");
      }


    random_seed = running_in_test_harness ? 42 + 2*delivery_count : 0;


    (void)fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);


    for (poffset = 0; poffset < remote_max_parallel; poffset++)
      if (parlist[poffset].pid != 0) (void)close(parlist[poffset].fd);


    (void)close(deliver_datafile);
    {
    uschar * fname = spool_fname(US"input", message_subdir, message_id, US"-D");

    if ((deliver_datafile = Uopen(fname,
#ifdef O_CLOEXEC
					O_CLOEXEC |
#endif
					O_RDWR | O_APPEND, 0)) < 0)
      log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Failed to reopen %s for remote "
        "parallel delivery: %s", fname, strerror(errno));
    }


#ifndef O_CLOEXEC
    (void)fcntl(deliver_datafile, F_SETFD, fcntl(deliver_datafile, F_GETFD) |
      FD_CLOEXEC);
#endif


    exim_setugid(uid, gid, use_initgroups,
      string_sprintf("remote delivery to %s with transport=%s",
        addr->address, tp->name));


    (void)close(pfd[pipe_read]);
    set_process_info("delivering %s using %s", message_id, tp->name);
    debug_print_string(tp->debug_string);
    if (!(tp->info->code)(addr->transport, addr)) replicate_status(addr);

    set_process_info("delivering %s (just run %s for %s%s in subprocess)",
      message_id, tp->name, addr->address, addr->next ? ", ..." : "");


    search_tidyup();


    for (h = addr->host_list; h; h = h->next)
      {
      if (!h->address || h->status < hstatus_unusable) continue;
      sprintf(CS big_buffer, "%c%c%s", h->status, h->why, h->address);
      rmt_dlv_checked_write(fd, 'H', '0', big_buffer, Ustrlen(big_buffer+2) + 3);
      }


    memcpy(big_buffer, &transport_count, sizeof(transport_count));
    rmt_dlv_checked_write(fd, 'S', '0', big_buffer, sizeof(transport_count));


    for(; addr; addr = addr->next)
      {
      uschar *ptr;
      retry_item *r;


      if (tls_out.certificate_verified) setflag(addr, af_cert_verified);
#ifdef SUPPORT_DANE
      if (tls_out.dane_verified)        setflag(addr, af_dane_verified);
#endif


#ifdef SUPPORT_TLS
      if (addr->cipher)
        {
        ptr = big_buffer + sprintf(CS big_buffer, "%.128s", addr->cipher) + 1;
        if (!addr->peerdn)
	  *ptr++ = 0;
	else
          ptr += sprintf(CS ptr, "%.512s", addr->peerdn) + 1;

        rmt_dlv_checked_write(fd, 'X', '1', big_buffer, ptr - big_buffer);
        }
      else if (continue_proxy_cipher)
	{
        ptr = big_buffer + sprintf(CS big_buffer, "%.128s", continue_proxy_cipher) + 1;
	*ptr++ = 0;
        rmt_dlv_checked_write(fd, 'X', '1', big_buffer, ptr - big_buffer);
	}

      if (addr->peercert)
	{
        ptr = big_buffer;
	if (!tls_export_cert(ptr, big_buffer_size-2, addr->peercert))
	  while(*ptr++);
	else
	  *ptr++ = 0;
        rmt_dlv_checked_write(fd, 'X', '2', big_buffer, ptr - big_buffer);
	}
      if (addr->ourcert)
	{
        ptr = big_buffer;
	if (!tls_export_cert(ptr, big_buffer_size-2, addr->ourcert))
	  while(*ptr++);
	else
	  *ptr++ = 0;
        rmt_dlv_checked_write(fd, 'X', '3', big_buffer, ptr - big_buffer);
	}
# ifndef DISABLE_OCSP
      if (addr->ocsp > OCSP_NOT_REQ)
	{
	ptr = big_buffer + sprintf(CS big_buffer, "%c", addr->ocsp + '0') + 1;
        rmt_dlv_checked_write(fd, 'X', '4', big_buffer, ptr - big_buffer);
	}
# endif
#endif

      if (client_authenticator)
        {
	ptr = big_buffer + sprintf(CS big_buffer, "%.64s", client_authenticator) + 1;
        rmt_dlv_checked_write(fd, 'C', '1', big_buffer, ptr - big_buffer);
	}
      if (client_authenticated_id)
        {
        ptr = big_buffer + sprintf(CS big_buffer, "%.64s", client_authenticated_id) + 1;
        rmt_dlv_checked_write(fd, 'C', '2', big_buffer, ptr - big_buffer);
	}
      if (client_authenticated_sender)
        {
        ptr = big_buffer + sprintf(CS big_buffer, "%.64s", client_authenticated_sender) + 1;
        rmt_dlv_checked_write(fd, 'C', '3', big_buffer, ptr - big_buffer);
	}

#ifndef DISABLE_PRDR
      if (testflag(addr, af_prdr_used))
	rmt_dlv_checked_write(fd, 'P', '0', NULL, 0);
#endif

      if (testflag(addr, af_chunking_used))
	rmt_dlv_checked_write(fd, 'K', '0', NULL, 0);

      if (testflag(addr, af_tcp_fastopen_conn))
	rmt_dlv_checked_write(fd, 'T',
	  testflag(addr, af_tcp_fastopen) ? '1' : '0', NULL, 0);

      memcpy(big_buffer, &addr->dsn_aware, sizeof(addr->dsn_aware));
      rmt_dlv_checked_write(fd, 'D', '0', big_buffer, sizeof(addr->dsn_aware));


      for (r = addr->retries; r; r = r->next)
        {
        sprintf(CS big_buffer, "%c%.500s", r->flags, r->key);
        ptr = big_buffer + Ustrlen(big_buffer+2) + 3;
        memcpy(ptr, &r->basic_errno, sizeof(r->basic_errno));
        ptr += sizeof(r->basic_errno);
        memcpy(ptr, &r->more_errno, sizeof(r->more_errno));
        ptr += sizeof(r->more_errno);
        if (!r->message) *ptr++ = 0; else
          {
          sprintf(CS ptr, "%.512s", r->message);
          while(*ptr++);
          }
        rmt_dlv_checked_write(fd, 'R', '0', big_buffer, ptr - big_buffer);
        }

#ifdef SUPPORT_SOCKS
      if (LOGGING(proxy) && proxy_session)
	{
	ptr = big_buffer;
	if (proxy_local_address)
	  {
	  DEBUG(D_deliver) debug_printf("proxy_local_address '%s'\n", proxy_local_address);
	  ptr = big_buffer + sprintf(CS ptr, "%.128s", proxy_local_address) + 1;
	  DEBUG(D_deliver) debug_printf("proxy_local_port %d\n", proxy_local_port);
	  memcpy(ptr, &proxy_local_port, sizeof(proxy_local_port));
	  ptr += sizeof(proxy_local_port);
	  }
	else
	  *ptr++ = '\0';
	rmt_dlv_checked_write(fd, 'A', '2', big_buffer, ptr - big_buffer);
	}
#endif

#ifdef EXPERIMENTAL_DSN_INFO

      if (addr->smtp_greeting)
	{
	DEBUG(D_deliver) debug_printf("smtp_greeting '%s'\n", addr->smtp_greeting);
	ptr = big_buffer + sprintf(CS big_buffer, "%.128s", addr->smtp_greeting) + 1;
	if (addr->helo_response)
	  {
	  DEBUG(D_deliver) debug_printf("helo_response '%s'\n", addr->helo_response);
	  ptr += sprintf(CS ptr, "%.128s", addr->helo_response) + 1;
	  }
	else
	  *ptr++ = '\0';
        rmt_dlv_checked_write(fd, 'A', '1', big_buffer, ptr - big_buffer);
	}
#endif


      sprintf(CS big_buffer, "%c%c", addr->transport_return, addr->special_action);
      ptr = big_buffer + 2;
      memcpy(ptr, &addr->basic_errno, sizeof(addr->basic_errno));
      ptr += sizeof(addr->basic_errno);
      memcpy(ptr, &addr->more_errno, sizeof(addr->more_errno));
      ptr += sizeof(addr->more_errno);
      memcpy(ptr, &addr->delivery_usec, sizeof(addr->delivery_usec));
      ptr += sizeof(addr->delivery_usec);
      memcpy(ptr, &addr->flags, sizeof(addr->flags));
      ptr += sizeof(addr->flags);

      if (!addr->message) *ptr++ = 0; else
        ptr += sprintf(CS ptr, "%.1024s", addr->message) + 1;

      if (!addr->user_message) *ptr++ = 0; else
        ptr += sprintf(CS ptr, "%.1024s", addr->user_message) + 1;

      if (!addr->host_used) *ptr++ = 0; else
        {
        ptr += sprintf(CS ptr, "%.256s", addr->host_used->name) + 1;
        ptr += sprintf(CS ptr, "%.64s", addr->host_used->address) + 1;
        memcpy(ptr, &addr->host_used->port, sizeof(addr->host_used->port));
        ptr += sizeof(addr->host_used->port);


	*ptr++ = addr->host_used->dnssec==DS_YES ? '2'
	       : addr->host_used->dnssec==DS_NO ? '1' : '0';

        }
      rmt_dlv_checked_write(fd, 'A', '0', big_buffer, ptr - big_buffer);
      }


#ifdef EXPERIMENTAL_DSN_INFO
    if (sending_ip_address)
#else
    if (LOGGING(incoming_interface) && sending_ip_address)
#endif
      {
      uschar * ptr;
      ptr = big_buffer + sprintf(CS big_buffer, "%.128s", sending_ip_address) + 1;
      ptr += sprintf(CS ptr, "%d", sending_port) + 1;
      rmt_dlv_checked_write(fd, 'I', '0', big_buffer, ptr - big_buffer);
      }


    big_buffer[0] = continue_transport ? '1' : '0';
    rmt_dlv_checked_write(fd, 'Z', '0', big_buffer, 1);
    (void)close(fd);
    exit(EXIT_SUCCESS);
    }


  (void)close(pfd[pipe_write]);


  if (cutthrough.fd >= 0 && cutthrough.callout_hold_only)
    {
#ifdef SUPPORT_TLS
    tls_close(FALSE, TLS_NO_SHUTDOWN);
#endif
    (void) close(cutthrough.fd);
    release_cutthrough_connection(US"passed to transport proc");
    }


  if (pid == -1)
    {
    (void)close(pfd[pipe_read]);
    panicmsg = string_sprintf("fork failed for remote delivery to %s: %s",
        addr->domain, strerror(errno));
    goto enq_continue;
    }


  parcount++;
  parlist[poffset].addrlist = parlist[poffset].addr = addr;
  parlist[poffset].pid = pid;
  parlist[poffset].fd = pfd[pipe_read];
  parlist[poffset].done = FALSE;
  parlist[poffset].msg = NULL;
  parlist[poffset].return_path = return_path;


  if (continue_transport) par_reduce(0, fallback);


  else if (running_in_test_harness) millisleep(500);

  continue;

enq_continue:
  if (serialize_key) enq_end(serialize_key);
panic_continue:
  remote_post_process(addr, LOG_MAIN|LOG_PANIC, panicmsg, fallback);
  continue;
  }


par_reduce(0, fallback);
return TRUE;
}
