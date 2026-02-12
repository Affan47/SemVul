handle_smtp_call(int *listen_sockets, int listen_socket_count,
  int accept_socket, struct sockaddr *accepted)
{
pid_t pid;
union sockaddr_46 interface_sockaddr;
EXIM_SOCKLEN_T ifsize = sizeof(interface_sockaddr);
int dup_accept_socket = -1;
int max_for_this_host = 0;
int wfsize = 0;
int wfptr = 0;
int use_log_write_selector = log_write_selector;
uschar *whofrom = NULL;

void *reset_point = store_get(0);


sender_host_address = host_ntoa(-1, accepted, NULL, &sender_host_port);
DEBUG(D_any) debug_printf("Connection request from %s port %d\n",
  sender_host_address, sender_host_port);


smtp_out = fdopen(accept_socket, "wb");
if (smtp_out == NULL)
  {
  never_error(US"daemon: fdopen() for smtp_out failed", US"", errno);
  goto ERROR_RETURN;
  }

dup_accept_socket = dup(accept_socket);
if (dup_accept_socket < 0)
  {
  never_error(US"daemon: couldn't dup socket descriptor",
    US"Connection setup failed", errno);
  goto ERROR_RETURN;
  }

smtp_in = fdopen(dup_accept_socket, "rb");
if (smtp_in == NULL)
  {
  never_error(US"daemon: fdopen() for smtp_in failed",
    US"Connection setup failed", errno);
  goto ERROR_RETURN;
  }


if (getsockname(accept_socket, (struct sockaddr *)(&interface_sockaddr),
     &ifsize) < 0)
  {
  log_write(0, LOG_MAIN | ((errno == ECONNRESET)? 0 : LOG_PANIC),
    "getsockname() failed: %s", strerror(errno));
  smtp_printf("421 Local problem: getsockname() failed; please try again later\r\n");
  goto ERROR_RETURN;
  }

interface_address = host_ntoa(-1, &interface_sockaddr, NULL, &interface_port);
DEBUG(D_interface) debug_printf("interface address=%s port=%d\n",
  interface_address, interface_port);


whofrom = string_append(whofrom, &wfsize, &wfptr, 3, "[", sender_host_address, "]");

if ((log_extra_selector & LX_incoming_port) != 0)
  whofrom = string_append(whofrom, &wfsize, &wfptr, 2, ":", string_sprintf("%d",
    sender_host_port));

if ((log_extra_selector & LX_incoming_interface) != 0)
  whofrom = string_append(whofrom, &wfsize, &wfptr, 4, " I=[",
    interface_address, "]:", string_sprintf("%d", interface_port));

whofrom[wfptr] = 0;


if (smtp_accept_max > 0 && smtp_accept_count >= smtp_accept_max)
  {
  DEBUG(D_any) debug_printf("rejecting SMTP connection: count=%d max=%d\n",
    smtp_accept_count, smtp_accept_max);
  smtp_printf("421 Too many concurrent SMTP connections; "
    "please try again later.\r\n");
  log_write(L_connection_reject,
            LOG_MAIN, "Connection from %s refused: too many connections",
    whofrom);
  goto ERROR_RETURN;
  }


if (smtp_load_reserve >= 0)
  {
  load_average = OS_GETLOADAVG();
  if (smtp_reserve_hosts == NULL && load_average > smtp_load_reserve)
    {
    DEBUG(D_any) debug_printf("rejecting SMTP connection: load average = %.2f\n",
      (double)load_average/1000.0);
    smtp_printf("421 Too much load; please try again later.\r\n");
    log_write(L_connection_reject,
              LOG_MAIN, "Connection from %s refused: load average = %.2f",
      whofrom, (double)load_average/1000.0);
    goto ERROR_RETURN;
    }
  }


if (smtp_accept_max_per_host != NULL)
  {
  uschar *expanded = expand_string(smtp_accept_max_per_host);
  if (expanded == NULL)
    {
    if (!expand_string_forcedfail)
      log_write(0, LOG_MAIN|LOG_PANIC, "expansion of smtp_accept_max_per_host "
        "failed for %s: %s", whofrom, expand_string_message);
    }

  else
    {
    uschar *s = expanded;
    while (isdigit(*s))
      max_for_this_host = max_for_this_host * 10 + *s++ - '0';
    if (*s != 0)
      log_write(0, LOG_MAIN|LOG_PANIC, "expansion of smtp_accept_max_per_host "
        "for %s contains non-digit: %s", whofrom, expanded);
    }
  }


if ((max_for_this_host > 0) &&
    (smtp_accept_count >= max_for_this_host))
  {
  int i;
  int host_accept_count = 0;
  int other_host_count = 0;

  for (i = 0; i < smtp_accept_max; ++i)
    {
    if (smtp_slots[i].host_address != NULL)
      {
      if (Ustrcmp(sender_host_address, smtp_slots[i].host_address) == 0)
       host_accept_count++;
      else
       other_host_count++;


      if ((host_accept_count >= max_for_this_host) ||
         ((smtp_accept_count - other_host_count) < max_for_this_host))
       break;
      }
    }

  if (host_accept_count >= max_for_this_host)
    {
    DEBUG(D_any) debug_printf("rejecting SMTP connection: too many from this "
      "IP address: count=%d max=%d\n",
      host_accept_count, max_for_this_host);
    smtp_printf("421 Too many concurrent SMTP connections "
      "from this IP address; please try again later.\r\n");
    log_write(L_connection_reject,
              LOG_MAIN, "Connection from %s refused: too many connections "
      "from that IP address", whofrom);
    goto ERROR_RETURN;
    }
  }


if ((log_write_selector & L_smtp_connection) != 0)
  {
  uschar *list = hosts_connection_nolog;
  if (list != NULL && verify_check_host(&list) == OK)
    use_log_write_selector &= ~L_smtp_connection;
  else
    log_write(L_smtp_connection, LOG_MAIN, "SMTP connection from %s "
      "(TCP/IP connection count = %d)", whofrom, smtp_accept_count + 1);
  }


search_tidyup();
pid = fork();


if (pid == 0)
  {
  int i;
  int queue_only_reason = 0;
  int old_pool = store_pool;
  int save_debug_selector = debug_selector;
  BOOL local_queue_only;
  BOOL session_local_queue_only;
  #ifdef SA_NOCLDWAIT
  struct sigaction act;
  #endif

  smtp_accept_count++;


  log_write_selector = use_log_write_selector;


  store_pool = POOL_PERM;
  interface_address = string_copy(interface_address);
  store_pool = old_pool;


  if (host_is_tls_on_connect_port(interface_port)) tls_on_connect = TRUE;


  smtp_active_hostname = primary_hostname;
  if (raw_active_hostname != NULL)
    {
    uschar *nah = expand_string(raw_active_hostname);
    if (nah == NULL)
      {
      if (!expand_string_forcedfail)
        {
        log_write(0, LOG_MAIN|LOG_PANIC, "failed to expand \"%s\" "
          "(smtp_active_hostname): %s", raw_active_hostname,
          expand_string_message);
        smtp_printf("421 Local configuration error; "
          "please try again later.\r\n");
        mac_smtp_fflush();
        search_tidyup();
        _exit(EXIT_FAILURE);
        }
      }
    else if (nah[0] != 0) smtp_active_hostname = nah;
    }


  queue_check_only();
  session_local_queue_only = queue_only;


  for (i = 0; i < listen_socket_count; i++) (void)close(listen_sockets[i]);

  #ifdef SA_NOCLDWAIT
  act.sa_handler = SIG_IGN;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = SA_NOCLDWAIT;
  sigaction(SIGCHLD, &act, NULL);
  #else
  signal(SIGCHLD, SIG_IGN);
  #endif


  if (debug_daemon) debug_selector = 0;
  verify_get_ident(IDENT_PORT);
  host_build_sender_fullhost();
  debug_selector = save_debug_selector;

  DEBUG(D_any)
    debug_printf("Process %d is handling incoming connection from %s\n",
      (int)getpid(), sender_fullhost);


  if (debug_daemon) debug_selector = 0;


  if (smtp_accept_queue > 0 && smtp_accept_count > smtp_accept_queue)
    {
    session_local_queue_only = TRUE;
    queue_only_reason = 1;
    }


  if (!smtp_start_session())
    {
    mac_smtp_fflush();
    search_tidyup();
    _exit(EXIT_SUCCESS);
    }

  for (;;)
    {
    int rc;
    message_id[0] = 0;
    reset_point = store_get(0);

    DEBUG(D_any)
      debug_printf("Process %d is ready for new message\n", (int)getpid());


    if ((rc = smtp_setup_msg()) > 0)
      {
      BOOL ok = receive_msg(FALSE);
      search_tidyup();
      if (!ok)
        {
        mac_smtp_fflush();
        smtp_log_no_mail();
        _exit(EXIT_SUCCESS);
        }
      if (message_id[0] == 0) continue;
      }
    else
      {
      mac_smtp_fflush();
      search_tidyup();
      smtp_log_no_mail();
      _exit((rc == 0)? EXIT_SUCCESS : EXIT_FAILURE);
      }


    DEBUG(D_receive)
      {
      int i;
      if (sender_address != NULL)
        debug_printf("Sender: %s\n", sender_address);
      if (recipients_list != NULL)
        {
        debug_printf("Recipients:\n");
        for (i = 0; i < recipients_count; i++)
          debug_printf("  %s\n", recipients_list[i].address);
        }
      }


    #ifndef SIG_IGN_WORKS
    while (waitpid(-1, NULL, WNOHANG) > 0);
    #endif


    store_reset(reset_point);


    if (!session_local_queue_only &&
        smtp_accept_queue_per_connection > 0 &&
        receive_messagecount > smtp_accept_queue_per_connection)
      {
      session_local_queue_only = TRUE;
      queue_only_reason = 2;
      }


    local_queue_only = session_local_queue_only;
    if (!local_queue_only && queue_only_load >= 0)
      {
      local_queue_only = (load_average = OS_GETLOADAVG()) > queue_only_load;
      if (local_queue_only)
        {
        queue_only_reason = 3;
        if (queue_only_load_latch) session_local_queue_only = TRUE;
        }
      }


    if (local_queue_only) switch(queue_only_reason)
      {
      case 1:
      log_write(L_delay_delivery,
                LOG_MAIN, "no immediate delivery: too many connections "
                "(%d, max %d)", smtp_accept_count, smtp_accept_queue);
      break;

      case 2:
      log_write(L_delay_delivery,
                LOG_MAIN, "no immediate delivery: more than %d messages "
                "received in one connection", smtp_accept_queue_per_connection);
      break;

      case 3:
      log_write(L_delay_delivery,
                LOG_MAIN, "no immediate delivery: load average %.2f",
                (double)load_average/1000.0);
      break;
      }


    else if (!queue_only_policy && !deliver_freeze)
      {
      pid_t dpid;


      mac_smtp_fflush();

      if ((dpid = fork()) == 0)
        {
        (void)fclose(smtp_in);
        (void)fclose(smtp_out);


        #ifdef SUPPORT_TLS
        tls_close(FALSE);
        #endif


        signal(SIGHUP,  SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        if (geteuid() != root_uid && !deliver_drop_privilege)
          {
          signal(SIGALRM, SIG_DFL);
          (void)child_exec_exim(CEE_EXEC_PANIC, FALSE, NULL, FALSE, 2, US"-Mc",
            message_id);

          }


        (void)deliver_message(message_id, FALSE, FALSE);
        search_tidyup();
        _exit(EXIT_SUCCESS);
        }

      if (dpid > 0)
        {
        DEBUG(D_any) debug_printf("forked delivery process %d\n", (int)dpid);
        }
      else
        {
        log_write(0, LOG_MAIN|LOG_PANIC, "daemon: delivery process fork "
          "failed: %s", strerror(errno));
        }
      }
    }
  }


if (pid < 0)
  {
  never_error(US"daemon: accept process fork failed", US"Fork failed", errno);
  }
else
  {
  int i;
  for (i = 0; i < smtp_accept_max; ++i)
    {
    if (smtp_slots[i].pid <= 0)
      {
      smtp_slots[i].pid = pid;
      if (smtp_accept_max_per_host != NULL)
        smtp_slots[i].host_address = string_copy_malloc(sender_host_address);
      smtp_accept_count++;
      break;
      }
    }
  DEBUG(D_any) debug_printf("%d SMTP accept process%s running\n",
    smtp_accept_count, (smtp_accept_count == 1)? "" : "es");
  }


ERROR_RETURN:


if (smtp_out != NULL)
  {
  if (fclose(smtp_out) != 0 && errno != ECONNRESET && errno != EPIPE)
    log_write(0, LOG_MAIN|LOG_PANIC, "daemon: fclose(smtp_out) failed: %s",
      strerror(errno));
  smtp_out = NULL;
  }
else (void)close(accept_socket);

if (smtp_in != NULL)
  {
  if (fclose(smtp_in) != 0 && errno != ECONNRESET && errno != EPIPE)
    log_write(0, LOG_MAIN|LOG_PANIC, "daemon: fclose(smtp_in) failed: %s",
      strerror(errno));
  smtp_in = NULL;
  }
else (void)close(dup_accept_socket);


store_reset(reset_point);
sender_host_address = NULL;
}
