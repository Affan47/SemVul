post_process_one(address_item *addr, int result, int logflags, int driver_type,
  int logchar)
{
uschar *now = tod_stamp(tod_log);
uschar *driver_kind = NULL;
uschar *driver_name = NULL;

DEBUG(D_deliver) debug_printf("post-process %s (%d)\n", addr->address, result);


if (driver_type == EXIM_DTYPE_TRANSPORT)
  {
  if (addr->transport)
    {
    driver_name = addr->transport->name;
    driver_kind = US" transport";
    disable_logging = addr->transport->disable_logging;
    }
  else driver_kind = US"transporting";
  }
else if (driver_type == EXIM_DTYPE_ROUTER)
  {
  if (addr->router)
    {
    driver_name = addr->router->name;
    driver_kind = US" router";
    disable_logging = addr->router->disable_logging;
    }
  else driver_kind = US"routing";
  }


if (addr->message)
  {
  const uschar * s = string_printing(addr->message);


  addr->message = expand_hide_passwords(US s);
  }


if (addr->return_file >= 0 && addr->return_filename)
  {
  BOOL return_output = FALSE;
  struct stat statbuf;
  (void)EXIMfsync(addr->return_file);


  if (fstat(addr->return_file, &statbuf) == 0 && statbuf.st_size > 0)
    {
    transport_instance *tb = addr->transport;


    if (  tb->log_output
       || result == FAIL  && tb->log_fail_output
       || result == DEFER && tb->log_defer_output
       )
      {
      uschar *s;
      FILE *f = Ufopen(addr->return_filename, "rb");
      if (!f)
        log_write(0, LOG_MAIN|LOG_PANIC, "failed to open %s to log output "
          "from %s transport: %s", addr->return_filename, tb->name,
          strerror(errno));
      else
        if ((s = US Ufgets(big_buffer, big_buffer_size, f)))
          {
          uschar *p = big_buffer + Ustrlen(big_buffer);
	  const uschar * sp;
          while (p > big_buffer && isspace(p[-1])) p--;
          *p = 0;
          sp = string_printing(big_buffer);
          log_write(0, LOG_MAIN, "<%s>: %s transport output: %s",
            addr->address, tb->name, sp);
          }
        (void)fclose(f);
      }


    if (sender_address[0] != 0 || addr->prop.errors_address)
      if (tb->return_output)
        {
        addr->transport_return = result = FAIL;
        if (addr->basic_errno == 0 && !addr->message)
          addr->message = US"return message generated";
        return_output = TRUE;
        }
      else
        if (tb->return_fail_output && result == FAIL) return_output = TRUE;
    }


  if (!return_output)
    {
    Uunlink(addr->return_filename);
    addr->return_filename = NULL;
    addr->return_file = -1;
    }

  (void)close(addr->return_file);
  }


if (result == OK)
  {
  addr->next = addr_succeed;
  addr_succeed = addr;


  address_done(addr, now);
  DEBUG(D_deliver) debug_printf("%s delivered\n", addr->address);

  if (!addr->parent)
    deliver_msglog("%s %s: %s%s succeeded\n", now, addr->address,
      driver_name, driver_kind);
  else
    {
    deliver_msglog("%s %s <%s>: %s%s succeeded\n", now, addr->address,
      addr->parent->address, driver_name, driver_kind);
    child_done(addr, now);
    }


#ifdef SUPPORT_TLS
  tls_out.ourcert = addr->ourcert;
  addr->ourcert = NULL;
  tls_out.peercert = addr->peercert;
  addr->peercert = NULL;

  tls_out.cipher = addr->cipher;
  tls_out.peerdn = addr->peerdn;
  tls_out.ocsp = addr->ocsp;
# ifdef SUPPORT_DANE
  tls_out.dane_verified = testflag(addr, af_dane_verified);
# endif
#endif

  delivery_log(LOG_MAIN, addr, logchar, NULL);

#ifdef SUPPORT_TLS
  tls_free_cert(&tls_out.ourcert);
  tls_free_cert(&tls_out.peercert);
  tls_out.cipher = NULL;
  tls_out.peerdn = NULL;
  tls_out.ocsp = OCSP_NOT_REQ;
# ifdef SUPPORT_DANE
  tls_out.dane_verified = FALSE;
# endif
#endif
  }


else if (result == DEFER || result == PANIC)
  {
  if (result == PANIC) logflags |= LOG_PANIC;


  addr->next = addr_defer;
  addr_defer = addr;


  if (addr->special_action == SPECIAL_FREEZE)
    {
    deliver_freeze = TRUE;
    deliver_frozen_at = time(NULL);
    update_spool = TRUE;
    }


  if (!queue_2stage || addr->basic_errno != 0)
    deferral_log(addr, now, logflags, driver_name, driver_kind);
  }


else
  {


  if (!*sender_address && message_age >= ignore_bounce_errors_after)
    addr->prop.ignore_error = TRUE;


  if (  !addr->prop.ignore_error
     && (  addr->special_action == SPECIAL_FREEZE
        || (sender_address[0] == 0 && !addr->prop.errors_address)
     )  )
    {
    frozen_info = addr->special_action == SPECIAL_FREEZE
      ? US""
      : sender_local && !local_error_message
      ? US" (message created with -f <>)"
      : US" (delivery error message)";
    deliver_freeze = TRUE;
    deliver_frozen_at = time(NULL);
    update_spool = TRUE;


    addr->next = addr_defer;
    addr_defer = addr;
    }


  else
    {
    addr->next = addr_failed;
    addr_failed = addr;
    }

  failure_log(addr, driver_name ? NULL : driver_kind, now);
  }


disable_logging = FALSE;
}
