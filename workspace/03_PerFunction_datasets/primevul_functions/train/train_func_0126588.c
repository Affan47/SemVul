smtp_start_session(void)
{
int esclen;
uschar *user_msg, *log_msg;
uschar *code, *esc;
uschar *p, *s;
gstring * ss;

gettimeofday(&smtp_connection_start, NULL);
for (smtp_ch_index = 0; smtp_ch_index < SMTP_HBUFF_SIZE; smtp_ch_index++)
  smtp_connection_had[smtp_ch_index] = SCH_NONE;
smtp_ch_index = 0;


fl.helo_seen = fl.esmtp = fl.helo_accept_junk = FALSE;
smtp_mailcmd_count = 0;
count_nonmail = TRUE_UNSET;
synprot_error_count = unknown_command_count = nonmail_command_count = 0;
smtp_delay_mail = smtp_rlm_base;
fl.auth_advertised = FALSE;
f.smtp_in_pipelining_advertised = f.smtp_in_pipelining_used = FALSE;
f.pipelining_enable = TRUE;
sync_cmd_limit = NON_SYNC_CMD_NON_PIPELINING;
fl.smtp_exit_function_called = FALSE;


if (!host_checking && !f.sender_host_notsocket)
  sender_host_auth_pubname = sender_host_authenticated = NULL;
authenticated_by = NULL;

#ifdef SUPPORT_TLS
tls_in.cipher = tls_in.peerdn = NULL;
tls_in.ourcert = tls_in.peercert = NULL;
tls_in.sni = NULL;
tls_in.ocsp = OCSP_NOT_REQ;
fl.tls_advertised = FALSE;
# ifdef EXPERIMENTAL_REQUIRETLS
fl.requiretls_advertised = FALSE;
# endif
#endif
fl.dsn_advertised = FALSE;
#ifdef SUPPORT_I18N
fl.smtputf8_advertised = FALSE;
#endif


acl_var_c = NULL;


if (!(smtp_cmd_buffer = US malloc(2*SMTP_CMD_BUFFER_SIZE + 2)))
  log_write(0, LOG_MAIN|LOG_PANIC_DIE,
    "malloc() failed for SMTP command buffer");

smtp_cmd_buffer[0] = 0;
smtp_data_buffer = smtp_cmd_buffer + SMTP_CMD_BUFFER_SIZE + 1;


if (smtp_batched_input)
  {
  if (!received_protocol) received_protocol = US"local-bsmtp";
  }


else
  received_protocol =
    (sender_host_address ? protocols : protocols_local) [pnormal];


if (!(smtp_inbuffer = US malloc(IN_BUFFER_SIZE)))
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "malloc() failed for SMTP input buffer");
smtp_inbuffer[IN_BUFFER_SIZE-1] = '\0';

receive_getc = smtp_getc;
receive_getbuf = smtp_getbuf;
receive_get_cache = smtp_get_cache;
receive_ungetc = smtp_ungetc;
receive_feof = smtp_feof;
receive_ferror = smtp_ferror;
receive_smtp_buffered = smtp_buffered;
smtp_inptr = smtp_inend = smtp_inbuffer;
smtp_had_eof = smtp_had_error = 0;


thismessage_size_limit = expand_string_integer(message_size_limit, TRUE);
if (expand_string_message)
  {
  if (thismessage_size_limit == -1)
    log_write(0, LOG_MAIN|LOG_PANIC, "unable to expand message_size_limit: "
      "%s", expand_string_message);
  else
    log_write(0, LOG_MAIN|LOG_PANIC, "invalid message_size_limit: "
      "%s", expand_string_message);
  smtp_closedown(US"Temporary local problem - please try later");
  return FALSE;
  }


if (!f.sender_host_unknown)
  {
  int rc;
  BOOL reserved_host = FALSE;


#if !HAVE_IPV6 && !defined(NO_IP_OPTIONS)

  #ifdef GLIBC_IP_OPTIONS
    #if (!defined __GLIBC__) || (__GLIBC__ < 2)
    #define OPTSTYLE 1
    #else
    #define OPTSTYLE 2
    #endif
  #elif defined DARWIN_IP_OPTIONS
    #define OPTSTYLE 2
  #else
    #define OPTSTYLE 3
  #endif

  if (!host_checking && !f.sender_host_notsocket)
    {
    #if OPTSTYLE == 1
    EXIM_SOCKLEN_T optlen = sizeof(struct ip_options) + MAX_IPOPTLEN;
    struct ip_options *ipopt = store_get(optlen);
    #elif OPTSTYLE == 2
    struct ip_opts ipoptblock;
    struct ip_opts *ipopt = &ipoptblock;
    EXIM_SOCKLEN_T optlen = sizeof(ipoptblock);
    #else
    struct ipoption ipoptblock;
    struct ipoption *ipopt = &ipoptblock;
    EXIM_SOCKLEN_T optlen = sizeof(ipoptblock);
    #endif


    DEBUG(D_receive) debug_printf("checking for IP options\n");

    if (getsockopt(fileno(smtp_out), IPPROTO_IP, IP_OPTIONS, US (ipopt),
          &optlen) < 0)
      {
      if (errno != ENOPROTOOPT)
        {
        log_write(0, LOG_MAIN, "getsockopt() failed from %s: %s",
          host_and_ident(FALSE), strerror(errno));
        smtp_printf("451 SMTP service not available\r\n", FALSE);
        return FALSE;
        }
      }


    else if (optlen > 0)
      {
      uschar *p = big_buffer;
      uschar *pend = big_buffer + big_buffer_size;
      uschar *opt, *adptr;
      int optcount;
      struct in_addr addr;

      #if OPTSTYLE == 1
      uschar *optstart = US (ipopt->__data);
      #elif OPTSTYLE == 2
      uschar *optstart = US (ipopt->ip_opts);
      #else
      uschar *optstart = US (ipopt->ipopt_list);
      #endif

      DEBUG(D_receive) debug_printf("IP options exist\n");

      Ustrcpy(p, "IP options on incoming call:");
      p += Ustrlen(p);

      for (opt = optstart; opt != NULL &&
           opt < US (ipopt) + optlen;)
        {
        switch (*opt)
          {
          case IPOPT_EOL:
          opt = NULL;
          break;

          case IPOPT_NOP:
          opt++;
          break;

          case IPOPT_SSRR:
          case IPOPT_LSRR:
          if (!string_format(p, pend-p, " %s [@%s",
               (*opt == IPOPT_SSRR)? "SSRR" : "LSRR",
               #if OPTSTYLE == 1
               inet_ntoa(*((struct in_addr *)(&(ipopt->faddr))))))
               #elif OPTSTYLE == 2
               inet_ntoa(ipopt->ip_dst)))
               #else
               inet_ntoa(ipopt->ipopt_dst)))
               #endif
            {
            opt = NULL;
            break;
            }

          p += Ustrlen(p);
          optcount = (opt[1] - 3) / sizeof(struct in_addr);
          adptr = opt + 3;
          while (optcount-- > 0)
            {
            memcpy(&addr, adptr, sizeof(addr));
            if (!string_format(p, pend - p - 1, "%s%s",
                  (optcount == 0)? ":" : "@", inet_ntoa(addr)))
              {
              opt = NULL;
              break;
              }
            p += Ustrlen(p);
            adptr += sizeof(struct in_addr);
            }
          *p++ = ']';
          opt += opt[1];
          break;

          default:
            {
            int i;
            if (pend - p < 4 + 3*opt[1]) { opt = NULL; break; }
            Ustrcat(p, "[ ");
            p += 2;
            for (i = 0; i < opt[1]; i++)
              p += sprintf(CS p, "%2.2x ", opt[i]);
            *p++ = ']';
            }
          opt += opt[1];
          break;
          }
        }

      *p = 0;
      log_write(0, LOG_MAIN, "%s", big_buffer);


      log_write(0, LOG_MAIN|LOG_REJECT,
        "connection from %s refused (IP options)", host_and_ident(FALSE));

      smtp_printf("554 SMTP service not available\r\n", FALSE);
      return FALSE;
      }


    else DEBUG(D_receive) debug_printf("no IP options found\n");
    }
#endif


  if (smtp_accept_keepalive && !f.sender_host_notsocket)
    ip_keepalive(fileno(smtp_out), sender_host_address, FALSE);


  if (verify_check_host(&host_lookup) == OK)
    {
    (void)host_name_lookup();
    host_build_sender_fullhost();
    }


  set_process_info("handling incoming connection from %s",
    host_and_ident(FALSE));


  if (smtp_receive_timeout_s)
    {
    uschar * exp;
    if (  !(exp = expand_string(smtp_receive_timeout_s))
       || !(*exp)
       || (smtp_receive_timeout = readconf_readtime(exp, 0, FALSE)) < 0
       )
      log_write(0, LOG_MAIN|LOG_PANIC,
	"bad value for smtp_receive_timeout: '%s'", exp ? exp : US"");
    }


  if (verify_check_host(&host_reject_connection) == OK)
    {
    log_write(L_connection_reject, LOG_MAIN|LOG_REJECT, "refused connection "
      "from %s (host_reject_connection)", host_and_ident(FALSE));
    smtp_printf("554 SMTP service not available\r\n", FALSE);
    return FALSE;
    }


#ifdef USE_TCP_WRAPPERS
  errno = 0;
  if (!(tcp_wrappers_name = expand_string(tcp_wrappers_daemon_name)))
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Expansion of \"%s\" "
      "(tcp_wrappers_name) failed: %s", string_printing(tcp_wrappers_name),
        expand_string_message);

  if (!hosts_ctl(tcp_wrappers_name,
         sender_host_name ? CS sender_host_name : STRING_UNKNOWN,
         sender_host_address ? CS sender_host_address : STRING_UNKNOWN,
         sender_ident ? CS sender_ident : STRING_UNKNOWN))
    {
    if (errno == 0 || errno == ENOENT)
      {
      HDEBUG(D_receive) debug_printf("tcp wrappers rejection\n");
      log_write(L_connection_reject,
                LOG_MAIN|LOG_REJECT, "refused connection from %s "
                "(tcp wrappers)", host_and_ident(FALSE));
      smtp_printf("554 SMTP service not available\r\n", FALSE);
      }
    else
      {
      int save_errno = errno;
      HDEBUG(D_receive) debug_printf("tcp wrappers rejected with unexpected "
        "errno value %d\n", save_errno);
      log_write(L_connection_reject,
                LOG_MAIN|LOG_REJECT, "temporarily refused connection from %s "
                "(tcp wrappers errno=%d)", host_and_ident(FALSE), save_errno);
      smtp_printf("451 Temporary local problem - please try later\r\n", FALSE);
      }
    return FALSE;
    }
#endif


  if (smtp_accept_max > 0 &&
      smtp_accept_count > smtp_accept_max - smtp_accept_reserve)
    {
    if ((rc = verify_check_host(&smtp_reserve_hosts)) != OK)
      {
      log_write(L_connection_reject,
        LOG_MAIN, "temporarily refused connection from %s: not in "
        "reserve list: connected=%d max=%d reserve=%d%s",
        host_and_ident(FALSE), smtp_accept_count - 1, smtp_accept_max,
        smtp_accept_reserve, (rc == DEFER)? " (lookup deferred)" : "");
      smtp_printf("421 %s: Too many concurrent SMTP connections; "
        "please try again later\r\n", FALSE, smtp_active_hostname);
      return FALSE;
      }
    reserved_host = TRUE;
    }


  if (smtp_load_reserve >= 0 &&
       load_average > smtp_load_reserve &&
       !reserved_host &&
       verify_check_host(&smtp_reserve_hosts) != OK)
    {
    log_write(L_connection_reject,
      LOG_MAIN, "temporarily refused connection from %s: not in "
      "reserve list and load average = %.2f", host_and_ident(FALSE),
      (double)load_average/1000.0);
    smtp_printf("421 %s: Too much load; please try again later\r\n", FALSE,
      smtp_active_hostname);
    return FALSE;
    }


  f.allow_unqualified_sender =
    verify_check_host(&sender_unqualified_hosts) == OK;

  f.allow_unqualified_recipient =
    verify_check_host(&recipient_unqualified_hosts) == OK;


  fl.helo_required = verify_check_host(&helo_verify_hosts) == OK;
  if (!fl.helo_required)
    fl.helo_verify = verify_check_host(&helo_try_verify_hosts) == OK;


  fl.helo_accept_junk = verify_check_host(&helo_accept_junk_hosts) == OK;
  }


if (smtp_batched_input) return TRUE;


#ifdef SUPPORT_PROXY
proxy_session = FALSE;
f.proxy_session_failed = FALSE;
if (check_proxy_protocol_host())
  setup_proxy_protocol_host();
#endif


#ifdef SUPPORT_TLS
  if (tls_in.on_connect)
    {
    if (tls_server_start(tls_require_ciphers, &user_msg) != OK)
      return smtp_log_tls_fail(user_msg);
    cmd_list[CMD_LIST_TLS_AUTH].is_mail_cmd = TRUE;
    }
#endif


user_msg = NULL;
if (acl_smtp_connect)
  {
  int rc;
  if ((rc = acl_check(ACL_WHERE_CONNECT, NULL, acl_smtp_connect, &user_msg,
		      &log_msg)) != OK)
    {
    (void) smtp_handle_acl_fail(ACL_WHERE_CONNECT, rc, user_msg, log_msg);
    return FALSE;
    }
  }


code = US"220";
esc = US"";
esclen = 0;

if (!user_msg)
  {
  if (!(s = expand_string(smtp_banner)))
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Expansion of \"%s\" (smtp_banner) "
      "failed: %s", smtp_banner, expand_string_message);
  }
else
  {
  int codelen = 3;
  s = user_msg;
  smtp_message_code(&code, &codelen, &s, NULL, TRUE);
  if (codelen > 4)
    {
    esc = code + 4;
    esclen = codelen - 4;
    }
  }


p = s + Ustrlen(s);
while (p > s && isspace(p[-1])) p--;
*p = 0;


ss = string_get(256);

p = s;
do
  {
  int len;
  uschar *linebreak = Ustrchr(p, '\n');
  ss = string_catn(ss, code, 3);
  if (!linebreak)
    {
    len = Ustrlen(p);
    ss = string_catn(ss, US" ", 1);
    }
  else
    {
    len = linebreak - p;
    ss = string_catn(ss, US"-", 1);
    }
  ss = string_catn(ss, esc, esclen);
  ss = string_catn(ss, p, len);
  ss = string_catn(ss, US"\r\n", 2);
  p += len;
  if (linebreak) p++;
  }
while (*p);


#ifdef EXPERIMENTAL_PIPE_CONNECT
fl.pipe_connect_acceptable =
  sender_host_address && verify_check_host(&pipe_connect_advertise_hosts) == OK;

if (!check_sync())
  if (fl.pipe_connect_acceptable)
    f.smtp_in_early_pipe_used = TRUE;
  else
#else
if (!check_sync())
#endif
    {
    unsigned n = smtp_inend - smtp_inptr;
    if (n > 32) n = 32;

    log_write(0, LOG_MAIN|LOG_REJECT, "SMTP protocol "
      "synchronization error (input sent without waiting for greeting): "
      "rejected connection from %s input=\"%s\"", host_and_ident(TRUE),
      string_printing(string_copyn(smtp_inptr, n)));
    smtp_printf("554 SMTP synchronization error\r\n", FALSE);
    return FALSE;
    }


smtp_printf("%s",
#ifdef EXPERIMENTAL_PIPE_CONNECT
  fl.pipe_connect_acceptable && pipeline_connect_sends(),
#else
  FALSE,
#endif
  string_from_gstring(ss));


#ifdef TCP_FASTOPEN
tfo_in_check();
#endif

return TRUE;
}
