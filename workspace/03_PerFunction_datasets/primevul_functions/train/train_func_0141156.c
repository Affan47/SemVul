do_local_deliveries(void)
{
open_db dbblock;
open_db *dbm_file = NULL;
time_t now = time(NULL);


while (addr_local)
  {
  struct timeval delivery_start;
  struct timeval deliver_time;
  address_item *addr2, *addr3, *nextaddr;
  int logflags = LOG_MAIN;
  int logchar = dont_deliver? '*' : '=';
  transport_instance *tp;
  uschar * serialize_key = NULL;


  address_item *addr = addr_local;
  addr_local = addr->next;
  addr->next = NULL;

  DEBUG(D_deliver|D_transport)
    debug_printf("--------> %s <--------\n", addr->address);


  if (!(tp = addr->transport))
    {
    logflags |= LOG_PANIC;
    disable_logging = FALSE;
    addr->message = addr->router
      ? string_sprintf("No transport set by %s router", addr->router->name)
      : string_sprintf("No transport set by system filter");
    post_process_one(addr, DEFER, logflags, EXIM_DTYPE_TRANSPORT, 0);
    continue;
    }


  if (previously_transported(addr, FALSE)) continue;


  disable_logging = tp->disable_logging;


  if (tp->batch_max > 1 && addr_local)
    {
    int batch_count = 1;
    BOOL uses_dom = readconf_depends((driver_instance *)tp, US"domain");
    BOOL uses_lp = (  testflag(addr, af_pfr)
		   && (testflag(addr, af_file) || addr->local_part[0] == '|')
		   )
		|| readconf_depends((driver_instance *)tp, US"local_part");
    uschar *batch_id = NULL;
    address_item **anchor = &addr_local;
    address_item *last = addr;
    address_item *next;


    if (tp->batch_id)
      {
      deliver_set_expansions(addr);
      batch_id = expand_string(tp->batch_id);
      deliver_set_expansions(NULL);
      if (!batch_id)
        {
        log_write(0, LOG_MAIN|LOG_PANIC, "Failed to expand batch_id option "
          "in %s transport (%s): %s", tp->name, addr->address,
          expand_string_message);
        batch_count = tp->batch_max;
        }
      }


    while ((next = *anchor) && batch_count < tp->batch_max)
      {
      BOOL ok =
           tp == next->transport
	&& !previously_transported(next, TRUE)
	&& testflag(addr, af_pfr) == testflag(next, af_pfr)
	&& testflag(addr, af_file) == testflag(next, af_file)
	&& (!uses_lp  || Ustrcmp(next->local_part, addr->local_part) == 0)
	&& (!uses_dom || Ustrcmp(next->domain, addr->domain) == 0)
	&& same_strings(next->prop.errors_address, addr->prop.errors_address)
	&& same_headers(next->prop.extra_headers, addr->prop.extra_headers)
	&& same_strings(next->prop.remove_headers, addr->prop.remove_headers)
	&& same_ugid(tp, addr, next)
	&& (  !addr->host_list && !next->host_list
	   ||    addr->host_list
	      && next->host_list
	      && Ustrcmp(addr->host_list->name, next->host_list->name) == 0
	   );


      if (ok && batch_id)
        {
        uschar *bid;
        address_item *save_nextnext = next->next;
        next->next = NULL;
        deliver_set_expansions(next);
        next->next = save_nextnext;
        bid = expand_string(tp->batch_id);
        deliver_set_expansions(NULL);
        if (!bid)
          {
          log_write(0, LOG_MAIN|LOG_PANIC, "Failed to expand batch_id option "
            "in %s transport (%s): %s", tp->name, next->address,
            expand_string_message);
          ok = FALSE;
          }
        else ok = (Ustrcmp(batch_id, bid) == 0);
        }


      if (ok)
        {
        *anchor = next->next;
        next->next = NULL;
        last->next = next;
        last = next;
        batch_count++;
        }
      else anchor = &next->next;
      }
    }


  if (tp->message_size_limit)
    {
    int rc = check_message_size(tp, addr);
    if (rc != OK)
      {
      replicate_status(addr);
      while (addr)
        {
        addr2 = addr->next;
        post_process_one(addr, rc, logflags, EXIM_DTYPE_TRANSPORT, 0);
        addr = addr2;
        }
      continue;
      }
    }


  if (!(dbm_file = dbfn_open(US"retry", O_RDONLY, &dbblock, FALSE)))
    {
    DEBUG(D_deliver|D_retry|D_hints_lookup)
      debug_printf("no retry data available\n");
    }

  addr2 = addr;
  addr3 = NULL;
  while (addr2)
    {
    BOOL ok = TRUE;
    uschar *retry_key;


    retry_key = string_copy(
      tp->retry_use_local_part ? addr2->address_retry_key :
        addr2->domain_retry_key);
    *retry_key = 'T';


    if (dbm_file)
      {
      dbdata_retry *retry_record = dbfn_read(dbm_file, retry_key);


      if (retry_record)
        {
        setflag(addr2, af_lt_retry_exists);


        DEBUG(D_retry)
          {
          debug_printf("retry record exists: age=%s ",
            readconf_printtime(now - retry_record->time_stamp));
          debug_printf("(max %s)\n", readconf_printtime(retry_data_expire));
          debug_printf("  time to retry = %s expired = %d\n",
            readconf_printtime(retry_record->next_try - now),
            retry_record->expired);
          }

        if (queue_running && !deliver_force)
          {
          ok = (now - retry_record->time_stamp > retry_data_expire)
	    || (now >= retry_record->next_try)
	    || retry_record->expired;


          if (!ok)
            ok = retry_ultimate_address_timeout(retry_key, addr2->domain,
                retry_record, now);
          }
        }
      else DEBUG(D_retry) debug_printf("no retry record exists\n");
      }


    if (ok)
      {
      addr3 = addr2;
      addr2 = addr2->next;
      }


    else
      {
      address_item *this = addr2;
      this->message = US"Retry time not yet reached";
      this->basic_errno = ERRNO_LRETRY;
      addr2 = addr3 ? (addr3->next = addr2->next)
		    : (addr = addr2->next);
      post_process_one(this, DEFER, logflags, EXIM_DTYPE_TRANSPORT, 0);
      }
    }

  if (dbm_file) dbfn_close(dbm_file);


  if (!addr) continue;


  if (tpt_parallel_check(tp, addr, &serialize_key))
    {
    if (expand_string_message)
      {
      logflags |= LOG_PANIC;
      do
	{
	addr = addr->next;
	post_process_one(addr, DEFER, logflags, EXIM_DTYPE_TRANSPORT, 0);
	} while ((addr = addr2));
      }
    continue;
    }


  deliver_set_expansions(addr);

  gettimeofday(&delivery_start, NULL);
  deliver_local(addr, FALSE);
  timesince(&deliver_time, &delivery_start);


  if (  tp->shadow
     && (  !tp->shadow_condition
        || expand_check_condition(tp->shadow_condition, tp->name, US"transport")
     )  )
    {
    transport_instance *stp;
    address_item *shadow_addr = NULL;
    address_item **last = &shadow_addr;

    for (stp = transports; stp; stp = stp->next)
      if (Ustrcmp(stp->name, tp->shadow) == 0) break;

    if (!stp)
      log_write(0, LOG_MAIN|LOG_PANIC, "shadow transport \"%s\" not found ",
        tp->shadow);


    else for (addr2 = addr; addr2; addr2 = addr2->next)
      if (addr2->transport_return == OK)
	{
	addr3 = store_get(sizeof(address_item));
	*addr3 = *addr2;
	addr3->next = NULL;
	addr3->shadow_message = US &addr2->shadow_message;
	addr3->transport = stp;
	addr3->transport_return = DEFER;
	addr3->return_filename = NULL;
	addr3->return_file = -1;
	*last = addr3;
	last = &addr3->next;
	}


    if (shadow_addr)
      {
      int save_count = transport_count;

      DEBUG(D_deliver|D_transport)
        debug_printf(">>>>>>>>>>>>>>>> Shadow delivery >>>>>>>>>>>>>>>>\n");
      deliver_local(shadow_addr, TRUE);

      for(; shadow_addr; shadow_addr = shadow_addr->next)
        {
        int sresult = shadow_addr->transport_return;
        *(uschar **)shadow_addr->shadow_message =
	  sresult == OK
	  ? string_sprintf(" ST=%s", stp->name)
	  : string_sprintf(" ST=%s (%s%s%s)", stp->name,
	      shadow_addr->basic_errno <= 0
	      ? US""
	      : US strerror(shadow_addr->basic_errno),
	      shadow_addr->basic_errno <= 0 || !shadow_addr->message
	      ? US""
	      : US": ",
	      shadow_addr->message
	      ? shadow_addr->message
	      : shadow_addr->basic_errno <= 0
	      ? US"unknown error"
	      : US"");

        DEBUG(D_deliver|D_transport)
          debug_printf("%s shadow transport returned %s for %s\n",
            stp->name,
            sresult == OK ?    "OK" :
            sresult == DEFER ? "DEFER" :
            sresult == FAIL ?  "FAIL" :
            sresult == PANIC ? "PANIC" : "?",
            shadow_addr->address);
        }

      DEBUG(D_deliver|D_transport)
        debug_printf(">>>>>>>>>>>>>>>> End shadow delivery >>>>>>>>>>>>>>>>\n");

      transport_count = save_count;
      }
    }


  deliver_set_expansions(NULL);


  if (serialize_key) enq_end(serialize_key);


  for (addr2 = addr; addr2; addr2 = nextaddr)
    {
    int result = addr2->transport_return;
    nextaddr = addr2->next;

    DEBUG(D_deliver|D_transport)
      debug_printf("%s transport returned %s for %s\n",
        tp->name,
        result == OK ?    "OK" :
        result == DEFER ? "DEFER" :
        result == FAIL ?  "FAIL" :
        result == PANIC ? "PANIC" : "?",
        addr2->address);


    if (result == DEFER || testflag(addr2, af_lt_retry_exists))
      {
      int flags = result == DEFER ? 0 : rf_delete;
      uschar *retry_key = string_copy(tp->retry_use_local_part
	? addr2->address_retry_key : addr2->domain_retry_key);
      *retry_key = 'T';
      retry_add_item(addr2, retry_key, flags);
      }


    if (result == OK)
      {
      addr2->more_errno = deliver_time.tv_sec;
      addr2->delivery_usec = deliver_time.tv_usec;
      }
    post_process_one(addr2, result, logflags, EXIM_DTYPE_TRANSPORT, logchar);


    if (addr2->transport_return != result)
      {
      for (addr3 = nextaddr; addr3; addr3 = addr3->next)
        {
        addr3->transport_return = addr2->transport_return;
        addr3->basic_errno = addr2->basic_errno;
        addr3->message = addr2->message;
        }
      result = addr2->transport_return;
      }


    addr2->return_file = addr->return_file;


    if (result == OK) logchar = '-';
    }
  }
}
