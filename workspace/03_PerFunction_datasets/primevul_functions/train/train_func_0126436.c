smtp_setup_msg(void)
{
int done = 0;
BOOL toomany = FALSE;
BOOL discarded = FALSE;
BOOL last_was_rej_mail = FALSE;
BOOL last_was_rcpt = FALSE;
void *reset_point = store_get(0);

DEBUG(D_receive) debug_printf("smtp_setup_msg entered\n");


smtp_reset(reset_point);
message_ended = END_NOTSTARTED;

chunking_state = f.chunking_offered ? CHUNKING_OFFERED : CHUNKING_NOT_OFFERED;

cmd_list[CMD_LIST_RSET].is_mail_cmd = TRUE;
cmd_list[CMD_LIST_HELO].is_mail_cmd = TRUE;
cmd_list[CMD_LIST_EHLO].is_mail_cmd = TRUE;
#ifdef SUPPORT_TLS
cmd_list[CMD_LIST_STARTTLS].is_mail_cmd = TRUE;
#endif


had_command_sigterm = 0;
os_non_restarting_signal(SIGTERM, command_sigterm_handler);


if (smtp_batched_input) return smtp_setup_batch_msg();


while (done <= 0)
  {
  const uschar **argv;
  uschar *etrn_command;
  uschar *etrn_serialize_key;
  uschar *errmess;
  uschar *log_msg, *smtp_code;
  uschar *user_msg = NULL;
  uschar *recipient = NULL;
  uschar *hello = NULL;
  uschar *s, *ss;
  BOOL was_rej_mail = FALSE;
  BOOL was_rcpt = FALSE;
  void (*oldsignal)(int);
  pid_t pid;
  int start, end, sender_domain, recipient_domain;
  int rc;
  int c;
  auth_instance *au;
  uschar *orcpt = NULL;
  int dsn_flags;
  gstring * g;

#ifdef AUTH_TLS

  if (  tls_in.active.sock >= 0
     && tls_in.peercert
     && tls_in.certificate_verified
     && cmd_list[CMD_LIST_TLS_AUTH].is_mail_cmd
     )
    {
    cmd_list[CMD_LIST_TLS_AUTH].is_mail_cmd = FALSE;

    for (au = auths; au; au = au->next)
      if (strcmpic(US"tls", au->driver_name) == 0)
	{
	if (  acl_smtp_auth
	   && (rc = acl_check(ACL_WHERE_AUTH, NULL, acl_smtp_auth,
		      &user_msg, &log_msg)) != OK
	   )
	  done = smtp_handle_acl_fail(ACL_WHERE_AUTH, rc, user_msg, log_msg);
	else
	  {
	  smtp_cmd_data = NULL;

	  if (smtp_in_auth(au, &s, &ss) == OK)
	    { DEBUG(D_auth) debug_printf("tls auth succeeded\n"); }
	  else
	    { DEBUG(D_auth) debug_printf("tls auth not succeeded\n"); }
	  }
	break;
	}
    }
#endif

#ifdef TCP_QUICKACK
  if (smtp_in)
    (void) setsockopt(fileno(smtp_in), IPPROTO_TCP, TCP_QUICKACK,
	    US &off, sizeof(off));
#endif

  switch(smtp_read_command(
#ifdef EXPERIMENTAL_PIPE_CONNECT
	  !fl.pipe_connect_acceptable,
#else
	  TRUE,
#endif
	  GETC_BUFFER_UNLIMITED))
    {


    case AUTH_CMD:
      HAD(SCH_AUTH);
      authentication_failed = TRUE;
      cmd_list[CMD_LIST_AUTH].is_mail_cmd = FALSE;

      if (!fl.auth_advertised && !f.allow_auth_unadvertised)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"AUTH command used when not advertised");
	break;
	}
      if (sender_host_authenticated)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"already authenticated");
	break;
	}
      if (sender_address)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"not permitted in mail transaction");
	break;
	}


      if (  acl_smtp_auth
	 && (rc = acl_check(ACL_WHERE_AUTH, NULL, acl_smtp_auth,
		    &user_msg, &log_msg)) != OK
	 )
	{
	done = smtp_handle_acl_fail(ACL_WHERE_AUTH, rc, user_msg, log_msg);
	break;
	}


      s = smtp_cmd_data;
      while ((c = *smtp_cmd_data) != 0 && !isspace(c))
	{
	if (!isalnum(c) && c != '-' && c != '_')
	  {
	  done = synprot_error(L_smtp_syntax_error, 501, NULL,
	    US"invalid character in authentication mechanism name");
	  goto COMMAND_LOOP;
	  }
	smtp_cmd_data++;
	}


      if (*smtp_cmd_data != 0)
	{
	*smtp_cmd_data++ = 0;
	while (isspace(*smtp_cmd_data)) smtp_cmd_data++;
	}


      for (au = auths; au; au = au->next)
	if (strcmpic(s, au->public_name) == 0 && au->server &&
	    (au->advertised || f.allow_auth_unadvertised))
	  break;

      if (au)
	{
	c = smtp_in_auth(au, &s, &ss);

	smtp_printf("%s\r\n", FALSE, s);
	if (c != OK)
	  log_write(0, LOG_MAIN|LOG_REJECT, "%s authenticator failed for %s: %s",
	    au->name, host_and_ident(FALSE), ss);
	}
      else
	done = synprot_error(L_smtp_protocol_error, 504, NULL,
	  string_sprintf("%s authentication mechanism not supported", s));

      break;


    case HELO_CMD:
      HAD(SCH_HELO);
      hello = US"HELO";
      fl.esmtp = FALSE;
      goto HELO_EHLO;

    case EHLO_CMD:
      HAD(SCH_EHLO);
      hello = US"EHLO";
      fl.esmtp = TRUE;

    HELO_EHLO:
      cmd_list[CMD_LIST_HELO].is_mail_cmd = FALSE;
      cmd_list[CMD_LIST_EHLO].is_mail_cmd = FALSE;


      if (!check_helo(smtp_cmd_data))
	{
	smtp_printf("501 Syntactically invalid %s argument(s)\r\n", FALSE, hello);

	log_write(0, LOG_MAIN|LOG_REJECT, "rejected %s from %s: syntactically "
	  "invalid argument(s): %s", hello, host_and_ident(FALSE),
	  *smtp_cmd_argument == 0 ? US"(no argument given)" :
			     string_printing(smtp_cmd_argument));

	if (++synprot_error_count > smtp_max_synprot_errors)
	  {
	  log_write(0, LOG_MAIN|LOG_REJECT, "SMTP call from %s dropped: too many "
	    "syntax or protocol errors (last command was \"%s\")",
	    host_and_ident(FALSE), string_printing(smtp_cmd_buffer));
	  done = 1;
	  }

	break;
	}


      if (!f.sender_host_unknown)
	{
	BOOL old_helo_verified = f.helo_verified;
	uschar *p = smtp_cmd_data;

	while (*p != 0 && !isspace(*p)) { *p = tolower(*p); p++; }
	*p = 0;


	if (  !sender_host_name
	   && (deliver_domain = sender_helo_name,
	       match_isinlist(sender_helo_name, CUSS &helo_lookup_domains, 0,
		&domainlist_anchor, NULL, MCL_DOMAIN, TRUE, NULL)) == OK)
	  (void)host_name_lookup();


	host_build_sender_fullhost();
	set_process_info("handling%s incoming connection from %s",
	  tls_in.active.sock >= 0 ? " TLS" : "", host_and_ident(FALSE));


	f.helo_verified = f.helo_verify_failed = sender_helo_dnssec = FALSE;
	if (fl.helo_required || fl.helo_verify)
	  {
	  BOOL tempfail = !smtp_verify_helo();
	  if (!f.helo_verified)
	    {
	    if (fl.helo_required)
	      {
	      smtp_printf("%d %s argument does not match calling host\r\n", FALSE,
		tempfail? 451 : 550, hello);
	      log_write(0, LOG_MAIN|LOG_REJECT, "%srejected \"%s %s\" from %s",
		tempfail? "temporarily " : "",
		hello, sender_helo_name, host_and_ident(FALSE));
	      f.helo_verified = old_helo_verified;
	      break;
	      }
	    HDEBUG(D_all) debug_printf("%s verification failed but host is in "
	      "helo_try_verify_hosts\n", hello);
	    }
	  }
	}

#ifdef SUPPORT_SPF

      spf_init(sender_helo_name, sender_host_address);
#endif


      if (acl_smtp_helo)
	if ((rc = acl_check(ACL_WHERE_HELO, NULL, acl_smtp_helo,
		  &user_msg, &log_msg)) != OK)
	  {
	  done = smtp_handle_acl_fail(ACL_WHERE_HELO, rc, user_msg, log_msg);
	  if (sender_helo_name)
	    {
	    store_free(sender_helo_name);
	    sender_helo_name = NULL;
	    }
	  host_build_sender_fullhost();
	  break;
	  }
#ifdef EXPERIMENTAL_PIPE_CONNECT
	else if (!fl.pipe_connect_acceptable && !check_sync())
#else
	else if (!check_sync())
#endif
	  goto SYNC_FAILURE;


      fl.auth_advertised = FALSE;
      f.smtp_in_pipelining_advertised = FALSE;
#ifdef SUPPORT_TLS
      fl.tls_advertised = FALSE;
# ifdef EXPERIMENTAL_REQUIRETLS
      fl.requiretls_advertised = FALSE;
# endif
#endif
      fl.dsn_advertised = FALSE;
#ifdef SUPPORT_I18N
      fl.smtputf8_advertised = FALSE;
#endif

      smtp_code = US"250 ";
      if (!user_msg)
	{
	s = string_sprintf("%.3s %s Hello %s%s%s",
	  smtp_code,
	  smtp_active_hostname,
	  sender_ident ? sender_ident : US"",
	  sender_ident ? US" at " : US"",
	  sender_host_name ? sender_host_name : sender_helo_name);
	g = string_cat(NULL, s);

	if (sender_host_address)
	  {
	  g = string_catn(g, US" [", 2);
	  g = string_cat (g, sender_host_address);
	  g = string_catn(g, US"]", 1);
	  }
	}


      else
	{
	char *ss;
	int codelen = 4;
	smtp_message_code(&smtp_code, &codelen, &user_msg, NULL, TRUE);
	s = string_sprintf("%.*s%s", codelen, smtp_code, user_msg);
	if ((ss = strpbrk(CS s, "\r\n")) != NULL)
	  {
	  log_write(0, LOG_MAIN|LOG_PANIC, "EHLO/HELO response must not contain "
	    "newlines: message truncated: %s", string_printing(s));
	  *ss = 0;
	  }
	g = string_cat(NULL, s);
	}

      g = string_catn(g, US"\r\n", 2);


      if (fl.esmtp)
	{
	g->s[3] = '-';


	if (thismessage_size_limit > 0)
	  {
	  sprintf(CS big_buffer, "%.3s-SIZE %d\r\n", smtp_code,
	    thismessage_size_limit);
	  g = string_cat(g, big_buffer);
	  }
	else
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-SIZE\r\n", 7);
	  }


	if (accept_8bitmime)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-8BITMIME\r\n", 11);
	  }


	if (verify_check_host(&dsn_advertise_hosts) != FAIL)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-DSN\r\n", 6);
	  fl.dsn_advertised = TRUE;
	  }


	if (acl_smtp_etrn)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-ETRN\r\n", 7);
	  }
	if (acl_smtp_vrfy)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-VRFY\r\n", 7);
	  }
	if (acl_smtp_expn)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-EXPN\r\n", 7);
	  }


	if (  f.pipelining_enable
	   && verify_check_host(&pipelining_advertise_hosts) == OK)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-PIPELINING\r\n", 13);
	  sync_cmd_limit = NON_SYNC_CMD_PIPELINING;
	  f.smtp_in_pipelining_advertised = TRUE;

#ifdef EXPERIMENTAL_PIPE_CONNECT
	  if (fl.pipe_connect_acceptable)
	    {
	    f.smtp_in_early_pipe_advertised = TRUE;
	    g = string_catn(g, smtp_code, 3);
	    g = string_catn(g, US"-" EARLY_PIPE_FEATURE_NAME "\r\n", EARLY_PIPE_FEATURE_LEN+3);
	    }
#endif
	  }


	if (  auths
#ifdef AUTH_TLS
	   && !sender_host_authenticated
#endif
	   && verify_check_host(&auth_advertise_hosts) == OK
	   )
	  {
	  auth_instance *au;
	  BOOL first = TRUE;
	  for (au = auths; au; au = au->next)
	    {
	    au->advertised = FALSE;
	    if (au->server)
	      {
	      DEBUG(D_auth+D_expand) debug_printf_indent(
		"Evaluating advertise_condition for %s athenticator\n",
		au->public_name);
	      if (  !au->advertise_condition
		 || expand_check_condition(au->advertise_condition, au->name,
			US"authenticator")
		 )
		{
		int saveptr;
		if (first)
		  {
		  g = string_catn(g, smtp_code, 3);
		  g = string_catn(g, US"-AUTH", 5);
		  first = FALSE;
		  fl.auth_advertised = TRUE;
		  }
		saveptr = g->ptr;
		g = string_catn(g, US" ", 1);
		g = string_cat (g, au->public_name);
		while (++saveptr < g->ptr) g->s[saveptr] = toupper(g->s[saveptr]);
		au->advertised = TRUE;
		}
	      }
	    }

	  if (!first) g = string_catn(g, US"\r\n", 2);
	  }


	if (verify_check_host(&chunking_advertise_hosts) != FAIL)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-CHUNKING\r\n", 11);
	  f.chunking_offered = TRUE;
	  chunking_state = CHUNKING_OFFERED;
	  }


#ifdef SUPPORT_TLS
	if (tls_in.active.sock < 0 &&
	    verify_check_host(&tls_advertise_hosts) != FAIL)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-STARTTLS\r\n", 11);
	  fl.tls_advertised = TRUE;
	  }

# ifdef EXPERIMENTAL_REQUIRETLS

	if (  tls_in.active.sock >= 0
	   && verify_check_host(&tls_advertise_requiretls) != FAIL)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-REQUIRETLS\r\n", 13);
	  fl.requiretls_advertised = TRUE;
	  }
# endif
#endif

#ifndef DISABLE_PRDR

	if (prdr_enable)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-PRDR\r\n", 7);
	  }
#endif

#ifdef SUPPORT_I18N
	if (  accept_8bitmime
	   && verify_check_host(&smtputf8_advertise_hosts) != FAIL)
	  {
	  g = string_catn(g, smtp_code, 3);
	  g = string_catn(g, US"-SMTPUTF8\r\n", 11);
	  fl.smtputf8_advertised = TRUE;
	  }
#endif


	g = string_catn(g, smtp_code, 3);
	g = string_catn(g, US" HELP\r\n", 7);
	}


#ifdef SUPPORT_TLS
      if (tls_in.active.sock >= 0)
	(void)tls_write(NULL, g->s, g->ptr,
# ifdef EXPERIMENTAL_PIPE_CONNECT
			fl.pipe_connect_acceptable && pipeline_connect_sends());
# else
			FALSE);
# endif
      else
#endif

	{
	int i = fwrite(g->s, 1, g->ptr, smtp_out); i = i;
	}
      DEBUG(D_receive)
	{
	uschar *cr;

	(void) string_from_gstring(g);
	while ((cr = Ustrchr(g->s, '\r')) != NULL)
	  memmove(cr, cr + 1, (g->ptr--) - (cr - g->s));
	debug_printf("SMTP>> %s", g->s);
	}
      fl.helo_seen = TRUE;


      received_protocol =
	(sender_host_address ? protocols : protocols_local)
	  [ (fl.esmtp
	    ? pextend + (sender_host_authenticated ? pauthed : 0)
	    : pnormal)
	  + (tls_in.active.sock >= 0 ? pcrpted : 0)
	  ];
      cancel_cutthrough_connection(TRUE, US"sent EHLO response");
      smtp_reset(reset_point);
      toomany = FALSE;
      break;


    case MAIL_CMD:
      HAD(SCH_MAIL);
      smtp_mailcmd_count++;
      was_rej_mail = TRUE;
      env_mail_type_t * mail_args;

      if (fl.helo_required && !fl.helo_seen)
	{
	smtp_printf("503 HELO or EHLO required\r\n", FALSE);
	log_write(0, LOG_MAIN|LOG_REJECT, "rejected MAIL from %s: no "
	  "HELO/EHLO given", host_and_ident(FALSE));
	break;
	}

      if (sender_address)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"sender already given");
	break;
	}

      if (!*smtp_cmd_data)
	{
	done = synprot_error(L_smtp_protocol_error, 501, NULL,
	  US"MAIL must have an address operand");
	break;
	}


      if (smtp_accept_max_per_connection > 0 &&
	  smtp_mailcmd_count > smtp_accept_max_per_connection)
	{
	smtp_printf("421 too many messages in this connection\r\n", FALSE);
	log_write(0, LOG_MAIN|LOG_REJECT, "rejected MAIL command %s: too many "
	  "messages in one connection", host_and_ident(TRUE));
	break;
	}


      cancel_cutthrough_connection(TRUE, US"MAIL received");
      smtp_reset(reset_point);
      toomany = FALSE;
      sender_data = recipient_data = NULL;


      if (fl.esmtp) for(;;)
	{
	uschar *name, *value, *end;
	unsigned long int size;
	BOOL arg_error = FALSE;

	if (!extract_option(&name, &value)) break;

	for (mail_args = env_mail_type_list;
	     mail_args->value != ENV_MAIL_OPT_NULL;
	     mail_args++
	    )
	  if (strcmpic(name, mail_args->name) == 0)
	    break;
	if (mail_args->need_value && strcmpic(value, US"") == 0)
	  break;

	switch(mail_args->value)
	  {


	  case ENV_MAIL_OPT_SIZE:
	    if (((size = Ustrtoul(value, &end, 10)), *end == 0))
	      {
	      if ((size == ULONG_MAX && errno == ERANGE) || size > INT_MAX)
		size = INT_MAX;
	      message_size = (int)size;
	      }
	    else
	      arg_error = TRUE;
	    break;


	  case ENV_MAIL_OPT_BODY:
	    if (accept_8bitmime) {
	      if (strcmpic(value, US"8BITMIME") == 0)
		body_8bitmime = 8;
	      else if (strcmpic(value, US"7BIT") == 0)
		body_8bitmime = 7;
	      else
		{
		body_8bitmime = 0;
		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"invalid data for BODY");
		goto COMMAND_LOOP;
		}
	      DEBUG(D_receive) debug_printf("8BITMIME: %d\n", body_8bitmime);
	      break;
	    }
	    arg_error = TRUE;
	    break;


	  case ENV_MAIL_OPT_RET:
	    if (fl.dsn_advertised)
	      {

	      if (dsn_ret > 0)
		{
		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"RET can be specified once only");
		goto COMMAND_LOOP;
		}
	      dsn_ret = strcmpic(value, US"HDRS") == 0
		? dsn_ret_hdrs
		: strcmpic(value, US"FULL") == 0
		? dsn_ret_full
		: 0;
	      DEBUG(D_receive) debug_printf("DSN_RET: %d\n", dsn_ret);

	      if (dsn_ret == 0)
		{
		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"Value for RET is invalid");
		goto COMMAND_LOOP;
		}
	      }
	    break;
	  case ENV_MAIL_OPT_ENVID:
	    if (fl.dsn_advertised)
	      {

	      if (dsn_envid)
		{
		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"ENVID can be specified once only");
		goto COMMAND_LOOP;
		}
	      dsn_envid = string_copy(value);
	      DEBUG(D_receive) debug_printf("DSN_ENVID: %s\n", dsn_envid);
	      }
	    break;


	  case ENV_MAIL_OPT_AUTH:
	    if (Ustrcmp(value, "<>") != 0)
	      {
	      int rc;
	      uschar *ignore_msg;

	      if (auth_xtextdecode(value, &authenticated_sender) < 0)
		{

		value[-1] = '=';
		name[-1] = ' ';
		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"invalid data for AUTH");
		goto COMMAND_LOOP;
		}
	      if (!acl_smtp_mailauth)
		{
		ignore_msg = US"client not authenticated";
		rc = sender_host_authenticated ? OK : FAIL;
		}
	      else
		{
		ignore_msg = US"rejected by ACL";
		rc = acl_check(ACL_WHERE_MAILAUTH, NULL, acl_smtp_mailauth,
		  &user_msg, &log_msg);
		}

	      switch (rc)
		{
		case OK:
		  if (authenticated_by == NULL ||
		      authenticated_by->mail_auth_condition == NULL ||
		      expand_check_condition(authenticated_by->mail_auth_condition,
			  authenticated_by->name, US"authenticator"))
		    break;

		  ignore_msg = US"server_mail_auth_condition failed";
		  if (authenticated_id != NULL)
		    ignore_msg = string_sprintf("%s: authenticated ID=\"%s\"",
		      ignore_msg, authenticated_id);


		case FAIL:
		  authenticated_sender = NULL;
		  log_write(0, LOG_MAIN, "ignoring AUTH=%s from %s (%s)",
		    value, host_and_ident(TRUE), ignore_msg);
		  break;


		default:
		  value[-1] = '=';
		  name[-1] = ' ';
		  (void)smtp_handle_acl_fail(ACL_WHERE_MAILAUTH, rc, user_msg,
		    log_msg);
		  goto COMMAND_LOOP;
		}
	      }
	      break;

#ifndef DISABLE_PRDR
	  case ENV_MAIL_OPT_PRDR:
	    if (prdr_enable)
	      prdr_requested = TRUE;
	    break;
#endif

#ifdef SUPPORT_I18N
	  case ENV_MAIL_OPT_UTF8:
	    if (!fl.smtputf8_advertised)
	      {
	      done = synprot_error(L_smtp_syntax_error, 501, NULL,
		US"SMTPUTF8 used when not advertised");
	      goto COMMAND_LOOP;
	      }

	    DEBUG(D_receive) debug_printf("smtputf8 requested\n");
	    message_smtputf8 = allow_utf8_domains = TRUE;
	    if (Ustrncmp(received_protocol, US"utf8", 4) != 0)
	      {
	      int old_pool = store_pool;
	      store_pool = POOL_PERM;
	      received_protocol = string_sprintf("utf8%s", received_protocol);
	      store_pool = old_pool;
	      }
	    break;
#endif

#if defined(SUPPORT_TLS) && defined(EXPERIMENTAL_REQUIRETLS)
	  case ENV_MAIL_OPT_REQTLS:
	    {
	    uschar * r, * t;

	    if (!fl.requiretls_advertised)
	      {
	      done = synprot_error(L_smtp_syntax_error, 555, NULL,
		US"unadvertised MAIL option: REQUIRETLS");
	      goto COMMAND_LOOP;
	      }

	    DEBUG(D_receive) debug_printf("requiretls requested\n");
	    tls_requiretls = REQUIRETLS_MSG;

	    r = string_copy_malloc(received_protocol);
	    if ((t = Ustrrchr(r, 's'))) *t = 'S';
	    received_protocol = r;
	    }
	    break;
#endif


	  case ENV_MAIL_OPT_NULL:
	    value[-1] = '=';
	    name[-1] = ' ';
	    arg_error = TRUE;
	    break;

	  default:  assert(0);
	  }


	if (arg_error) break;
	}

#if defined(SUPPORT_TLS) && defined(EXPERIMENTAL_REQUIRETLS)
      if (tls_requiretls & REQUIRETLS_MSG)
	{


	DEBUG(D_receive) if (dsn_ret == dsn_ret_full)
	  debug_printf("requiretls override: dsn_ret_full -> dsn_ret_hdrs\n");
	dsn_ret = dsn_ret_hdrs;
	}
#endif


      if (smtp_mailcmd_count > smtp_rlm_threshold &&
	  verify_check_host(&smtp_ratelimit_hosts) == OK)
	{
	DEBUG(D_receive) debug_printf("rate limit MAIL: delay %.3g sec\n",
	  smtp_delay_mail/1000.0);
	millisleep((int)smtp_delay_mail);
	smtp_delay_mail *= smtp_rlm_factor;
	if (smtp_delay_mail > (double)smtp_rlm_limit)
	  smtp_delay_mail = (double)smtp_rlm_limit;
	}


      raw_sender = rewrite_existflags & rewrite_smtp
	? rewrite_one(smtp_cmd_data, rewrite_smtp, NULL, FALSE, US"",
		      global_rewrite_rules)
	: smtp_cmd_data;

      raw_sender =
	parse_extract_address(raw_sender, &errmess, &start, &end, &sender_domain,
	  TRUE);

      if (!raw_sender)
	{
	done = synprot_error(L_smtp_syntax_error, 501, smtp_cmd_data, errmess);
	break;
	}

      sender_address = raw_sender;


      if (thismessage_size_limit > 0 && message_size > thismessage_size_limit)
	{
	smtp_printf("552 Message size exceeds maximum permitted\r\n", FALSE);
	log_write(L_size_reject,
	    LOG_MAIN|LOG_REJECT, "rejected MAIL FROM:<%s> %s: "
	    "message too big: size%s=%d max=%d",
	    sender_address,
	    host_and_ident(TRUE),
	    (message_size == INT_MAX)? ">" : "",
	    message_size,
	    thismessage_size_limit);
	sender_address = NULL;
	break;
	}


      if (!receive_check_fs(
	   (smtp_check_spool_space && message_size >= 0)?
	      message_size + 5000 : 0))
	{
	smtp_printf("452 Space shortage, please try later\r\n", FALSE);
	sender_address = NULL;
	break;
	}


      if (!sender_domain && *sender_address)
	if (f.allow_unqualified_sender)
	  {
	  sender_domain = Ustrlen(sender_address) + 1;
	  sender_address = rewrite_address_qualify(sender_address, FALSE);
	  DEBUG(D_receive) debug_printf("unqualified address %s accepted\n",
	    raw_sender);
	  }
	else
	  {
	  smtp_printf("501 %s: sender address must contain a domain\r\n", FALSE,
	    smtp_cmd_data);
	  log_write(L_smtp_syntax_error,
	    LOG_MAIN|LOG_REJECT,
	    "unqualified sender rejected: <%s> %s%s",
	    raw_sender,
	    host_and_ident(TRUE),
	    host_lookup_msg);
	  sender_address = NULL;
	  break;
	  }


      if (acl_smtp_mail)
	{
	rc = acl_check(ACL_WHERE_MAIL, NULL, acl_smtp_mail, &user_msg, &log_msg);
	if (rc == OK && !f.smtp_in_pipelining_advertised && !check_sync())
	  goto SYNC_FAILURE;
	}
      else
	rc = OK;

      if (rc == OK || rc == DISCARD)
	{
	BOOL more = pipeline_response();

	if (!user_msg)
	  smtp_printf("%s%s%s", more, US"250 OK",
		    #ifndef DISABLE_PRDR
		      prdr_requested ? US", PRDR Requested" : US"",
		    #else
		      US"",
		    #endif
		      US"\r\n");
	else
	  {
	#ifndef DISABLE_PRDR
	  if (prdr_requested)
	     user_msg = string_sprintf("%s%s", user_msg, US", PRDR Requested");
	#endif
	  smtp_user_msg(US"250", user_msg);
	  }
	smtp_delay_rcpt = smtp_rlr_base;
	f.recipients_discarded = (rc == DISCARD);
	was_rej_mail = FALSE;
	}
      else
	{
	done = smtp_handle_acl_fail(ACL_WHERE_MAIL, rc, user_msg, log_msg);
	sender_address = NULL;
	}
      break;


    case RCPT_CMD:
      HAD(SCH_RCPT);
      rcpt_count++;
      was_rcpt = fl.rcpt_in_progress = TRUE;


      if (sender_address == NULL)
	{
	if (f.smtp_in_pipelining_advertised && last_was_rej_mail)
	  {
	  smtp_printf("503 sender not yet given\r\n", FALSE);
	  was_rej_mail = TRUE;
	  }
	else
	  {
	  done = synprot_error(L_smtp_protocol_error, 503, NULL,
	    US"sender not yet given");
	  was_rcpt = FALSE;
	  }
	rcpt_fail_count++;
	break;
	}


      if (smtp_cmd_data[0] == 0)
	{
	done = synprot_error(L_smtp_syntax_error, 501, NULL,
	  US"RCPT must have an address operand");
	rcpt_fail_count++;
	break;
	}


      orcpt = NULL;
      dsn_flags = 0;

      if (fl.esmtp) for(;;)
	{
	uschar *name, *value;

	if (!extract_option(&name, &value))
	  break;

	if (fl.dsn_advertised && strcmpic(name, US"ORCPT") == 0)
	  {

	  if (orcpt)
	    {
	    done = synprot_error(L_smtp_syntax_error, 501, NULL,
	      US"ORCPT can be specified once only");
	    goto COMMAND_LOOP;
	    }
	  orcpt = string_copy(value);
	  DEBUG(D_receive) debug_printf("DSN orcpt: %s\n", orcpt);
	  }

	else if (fl.dsn_advertised && strcmpic(name, US"NOTIFY") == 0)
	  {

	  if (dsn_flags > 0)
	    {
	    done = synprot_error(L_smtp_syntax_error, 501, NULL,
		US"NOTIFY can be specified once only");
	    goto COMMAND_LOOP;
	    }
	  if (strcmpic(value, US"NEVER") == 0)
	    dsn_flags |= rf_notify_never;
	  else
	    {
	    uschar *p = value;
	    while (*p != 0)
	      {
	      uschar *pp = p;
	      while (*pp != 0 && *pp != ',') pp++;
	      if (*pp == ',') *pp++ = 0;
	      if (strcmpic(p, US"SUCCESS") == 0)
		{
		DEBUG(D_receive) debug_printf("DSN: Setting notify success\n");
		dsn_flags |= rf_notify_success;
		}
	      else if (strcmpic(p, US"FAILURE") == 0)
		{
		DEBUG(D_receive) debug_printf("DSN: Setting notify failure\n");
		dsn_flags |= rf_notify_failure;
		}
	      else if (strcmpic(p, US"DELAY") == 0)
		{
		DEBUG(D_receive) debug_printf("DSN: Setting notify delay\n");
		dsn_flags |= rf_notify_delay;
		}
	      else
		{

		done = synprot_error(L_smtp_syntax_error, 501, NULL,
		  US"Invalid value for NOTIFY parameter");
		goto COMMAND_LOOP;
		}
	      p = pp;
	      }
	      DEBUG(D_receive) debug_printf("DSN Flags: %x\n", dsn_flags);
	    }
	  }


	else
	  {
	  DEBUG(D_receive) debug_printf("Invalid RCPT option: %s : %s\n", name, value);
	  name[-1] = ' ';
	  value[-1] = '=';
	  break;
	  }
	}


      recipient = rewrite_existflags & rewrite_smtp
	? rewrite_one(smtp_cmd_data, rewrite_smtp, NULL, FALSE, US"",
	    global_rewrite_rules)
	: smtp_cmd_data;

      if (!(recipient = parse_extract_address(recipient, &errmess, &start, &end,
	&recipient_domain, FALSE)))
	{
	done = synprot_error(L_smtp_syntax_error, 501, smtp_cmd_data, errmess);
	rcpt_fail_count++;
	break;
	}


      if (!recipient_domain)
	if (!(recipient_domain = qualify_recipient(&recipient, smtp_cmd_data,
				    US"recipient")))
	  {
	  rcpt_fail_count++;
	  break;
	  }


      if (rcpt_count > recipients_max && recipients_max > 0)
	{
	if (recipients_max_reject)
	  {
	  rcpt_fail_count++;
	  smtp_printf("552 too many recipients\r\n", FALSE);
	  if (!toomany)
	    log_write(0, LOG_MAIN|LOG_REJECT, "too many recipients: message "
	      "rejected: sender=<%s> %s", sender_address, host_and_ident(TRUE));
	  }
	else
	  {
	  rcpt_defer_count++;
	  smtp_printf("452 too many recipients\r\n", FALSE);
	  if (!toomany)
	    log_write(0, LOG_MAIN|LOG_REJECT, "too many recipients: excess "
	      "temporarily rejected: sender=<%s> %s", sender_address,
	      host_and_ident(TRUE));
	  }

	toomany = TRUE;
	break;
	}


      if (rcpt_count > smtp_rlr_threshold &&
	  verify_check_host(&smtp_ratelimit_hosts) == OK)
	{
	DEBUG(D_receive) debug_printf("rate limit RCPT: delay %.3g sec\n",
	  smtp_delay_rcpt/1000.0);
	millisleep((int)smtp_delay_rcpt);
	smtp_delay_rcpt *= smtp_rlr_factor;
	if (smtp_delay_rcpt > (double)smtp_rlr_limit)
	  smtp_delay_rcpt = (double)smtp_rlr_limit;
	}


      if (f.recipients_discarded)
	rc = DISCARD;
      else
	if (  (rc = acl_check(ACL_WHERE_RCPT, recipient, acl_smtp_rcpt, &user_msg,
		      &log_msg)) == OK
	   && !f.smtp_in_pipelining_advertised && !check_sync())
	  goto SYNC_FAILURE;


      if (rc == OK)
	{
	BOOL more = pipeline_response();

	if (user_msg)
	  smtp_user_msg(US"250", user_msg);
	else
	  smtp_printf("250 Accepted\r\n", more);
	receive_add_recipient(recipient, -1);


	recipients_list[recipients_count-1].orcpt = orcpt;
	recipients_list[recipients_count-1].dsn_flags = dsn_flags;

	DEBUG(D_receive) debug_printf("DSN: orcpt: %s  flags: %d\n",
	  recipients_list[recipients_count-1].orcpt,
	  recipients_list[recipients_count-1].dsn_flags);
	}


      else if (rc == DISCARD)
	{
	if (user_msg)
	  smtp_user_msg(US"250", user_msg);
	else
	  smtp_printf("250 Accepted\r\n", FALSE);
	rcpt_fail_count++;
	discarded = TRUE;
	log_write(0, LOG_MAIN|LOG_REJECT, "%s F=<%s> RCPT %s: "
	  "discarded by %s ACL%s%s", host_and_ident(TRUE),
	  sender_address_unrewritten? sender_address_unrewritten : sender_address,
	  smtp_cmd_argument, f.recipients_discarded? "MAIL" : "RCPT",
	  log_msg ? US": " : US"", log_msg ? log_msg : US"");
	}


      else
	{
	if (rc == FAIL) rcpt_fail_count++; else rcpt_defer_count++;
	done = smtp_handle_acl_fail(ACL_WHERE_RCPT, rc, user_msg, log_msg);
	}
      break;


    case BDAT_CMD:
      {
      int n;

      HAD(SCH_BDAT);
      if (chunking_state != CHUNKING_OFFERED)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"BDAT command used when CHUNKING not advertised");
	break;
	}


      if (sscanf(CS smtp_cmd_data, "%u %n", &chunking_datasize, &n) < 1)
	{
	done = synprot_error(L_smtp_protocol_error, 501, NULL,
	  US"missing size for BDAT command");
	break;
	}
      chunking_state = strcmpic(smtp_cmd_data+n, US"LAST") == 0
	? CHUNKING_LAST : CHUNKING_ACTIVE;
      chunking_data_left = chunking_datasize;
      DEBUG(D_receive) debug_printf("chunking state %d, %d bytes\n",
				    (int)chunking_state, chunking_data_left);


      lwr_receive_getc = receive_getc;
      lwr_receive_getbuf = receive_getbuf;
      lwr_receive_ungetc = receive_ungetc;

      receive_getc = bdat_getc;
      receive_ungetc = bdat_ungetc;

      f.dot_ends = FALSE;

      goto DATA_BDAT;
      }

    case DATA_CMD:
      HAD(SCH_DATA);
      f.dot_ends = TRUE;

    DATA_BDAT:
#ifdef EXPERIMENTAL_PIPE_CONNECT
      fl.pipe_connect_acceptable = FALSE;
#endif
      if (!discarded && recipients_count <= 0)
	{
	if (fl.rcpt_smtp_response_same && rcpt_smtp_response != NULL)
	  {
	  uschar *code = US"503";
	  int len = Ustrlen(rcpt_smtp_response);
	  smtp_respond(code, 3, FALSE, US"All RCPT commands were rejected with "
	    "this error:");

	  if (len > 2 && rcpt_smtp_response[len-2] == '\r')
	    rcpt_smtp_response[len-2] = 0;
	  smtp_respond(code, 3, FALSE, rcpt_smtp_response);
	  }
	if (f.smtp_in_pipelining_advertised && last_was_rcpt)
	  smtp_printf("503 Valid RCPT command must precede %s\r\n", FALSE,
	    smtp_names[smtp_connection_had[smtp_ch_index-1]]);
	else
	  done = synprot_error(L_smtp_protocol_error, 503, NULL,
	    smtp_connection_had[smtp_ch_index-1] == SCH_DATA
	    ? US"valid RCPT command must precede DATA"
	    : US"valid RCPT command must precede BDAT");

	if (chunking_state > CHUNKING_OFFERED)
	  bdat_flush_data();
	break;
	}

      if (toomany && recipients_max_reject)
	{
	sender_address = NULL;
	sender_address_unrewritten = NULL;
	smtp_printf("554 Too many recipients\r\n", FALSE);
	break;
	}

      if (chunking_state > CHUNKING_OFFERED)
	rc = OK;
      else
	{


	if (acl_smtp_predata == NULL && cutthrough.cctx.sock < 0)
	  rc = OK;
	else
	  {
	  uschar * acl = acl_smtp_predata ? acl_smtp_predata : US"accept";
	  f.enable_dollar_recipients = TRUE;
	  rc = acl_check(ACL_WHERE_PREDATA, NULL, acl, &user_msg,
	    &log_msg);
	  f.enable_dollar_recipients = FALSE;
	  if (rc == OK && !check_sync())
	    goto SYNC_FAILURE;

	  if (rc != OK)
	    {
	    done = smtp_handle_acl_fail(ACL_WHERE_PREDATA, rc, user_msg, log_msg);
	    break;
	    }
	  }

	if (user_msg)
	  smtp_user_msg(US"354", user_msg);
	else
	  smtp_printf(
	    "354 Enter message, ending with \".\" on a line by itself\r\n", FALSE);
	}

#ifdef TCP_QUICKACK
      if (smtp_in)
	(void) setsockopt(fileno(smtp_in), IPPROTO_TCP, TCP_QUICKACK,
		US &on, sizeof(on));
#endif
      done = 3;
      message_ended = END_NOTENDED;

      break;


    case VRFY_CMD:
      {
      uschar * address;

      HAD(SCH_VRFY);

      if (!(address = parse_extract_address(smtp_cmd_data, &errmess,
            &start, &end, &recipient_domain, FALSE)))
	{
	smtp_printf("501 %s\r\n", FALSE, errmess);
	break;
	}

      if (!recipient_domain)
	if (!(recipient_domain = qualify_recipient(&address, smtp_cmd_data,
				    US"verify")))
	  break;

      if ((rc = acl_check(ACL_WHERE_VRFY, address, acl_smtp_vrfy,
		    &user_msg, &log_msg)) != OK)
	done = smtp_handle_acl_fail(ACL_WHERE_VRFY, rc, user_msg, log_msg);
      else
	{
	uschar * s = NULL;
	address_item * addr = deliver_make_addr(address, FALSE);

	switch(verify_address(addr, NULL, vopt_is_recipient | vopt_qualify, -1,
	       -1, -1, NULL, NULL, NULL))
	  {
	  case OK:
	    s = string_sprintf("250 <%s> is deliverable", address);
	    break;

	  case DEFER:
	    s = (addr->user_message != NULL)?
	      string_sprintf("451 <%s> %s", address, addr->user_message) :
	      string_sprintf("451 Cannot resolve <%s> at this time", address);
	    break;

	  case FAIL:
	    s = (addr->user_message != NULL)?
	      string_sprintf("550 <%s> %s", address, addr->user_message) :
	      string_sprintf("550 <%s> is not deliverable", address);
	    log_write(0, LOG_MAIN, "VRFY failed for %s %s",
	      smtp_cmd_argument, host_and_ident(TRUE));
	    break;
	  }

	smtp_printf("%s\r\n", FALSE, s);
	}
      break;
      }


    case EXPN_CMD:
      HAD(SCH_EXPN);
      rc = acl_check(ACL_WHERE_EXPN, NULL, acl_smtp_expn, &user_msg, &log_msg);
      if (rc != OK)
	done = smtp_handle_acl_fail(ACL_WHERE_EXPN, rc, user_msg, log_msg);
      else
	{
	BOOL save_log_testing_mode = f.log_testing_mode;
	f.address_test_mode = f.log_testing_mode = TRUE;
	(void) verify_address(deliver_make_addr(smtp_cmd_data, FALSE),
	  smtp_out, vopt_is_recipient | vopt_qualify | vopt_expn, -1, -1, -1,
	  NULL, NULL, NULL);
	f.address_test_mode = FALSE;
	f.log_testing_mode = save_log_testing_mode;
	}
      break;


    #ifdef SUPPORT_TLS

    case STARTTLS_CMD:
      HAD(SCH_STARTTLS);
      if (!fl.tls_advertised)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"STARTTLS command used when not advertised");
	break;
	}


      if (  acl_smtp_starttls
	 && (rc = acl_check(ACL_WHERE_STARTTLS, NULL, acl_smtp_starttls,
		    &user_msg, &log_msg)) != OK
	 )
	{
	done = smtp_handle_acl_fail(ACL_WHERE_STARTTLS, rc, user_msg, log_msg);
	break;
	}


      incomplete_transaction_log(US"STARTTLS");
      cancel_cutthrough_connection(TRUE, US"STARTTLS received");
      smtp_reset(reset_point);
      toomany = FALSE;
      cmd_list[CMD_LIST_STARTTLS].is_mail_cmd = FALSE;


      if (receive_smtp_buffered())
	{
	DEBUG(D_any)
	  debug_printf("Non-empty input buffer after STARTTLS; naive attack?\n");
	if (tls_in.active.sock < 0)
	  smtp_inend = smtp_inptr = smtp_inbuffer;

	}


      memset(smtp_inbuffer, 0, IN_BUFFER_SIZE);


      s = NULL;
      if ((rc = tls_server_start(tls_require_ciphers, &s)) == OK)
	{
	if (!tls_remember_esmtp)
	  fl.helo_seen = fl.esmtp = fl.auth_advertised = f.smtp_in_pipelining_advertised = FALSE;
	cmd_list[CMD_LIST_EHLO].is_mail_cmd = TRUE;
	cmd_list[CMD_LIST_AUTH].is_mail_cmd = TRUE;
	cmd_list[CMD_LIST_TLS_AUTH].is_mail_cmd = TRUE;
	if (sender_helo_name)
	  {
	  store_free(sender_helo_name);
	  sender_helo_name = NULL;
	  host_build_sender_fullhost();
	  set_process_info("handling incoming TLS connection from %s",
	    host_and_ident(FALSE));
	  }
	received_protocol =
	  (sender_host_address ? protocols : protocols_local)
	    [ (fl.esmtp
	      ? pextend + (sender_host_authenticated ? pauthed : 0)
	      : pnormal)
	    + (tls_in.active.sock >= 0 ? pcrpted : 0)
	    ];

	sender_host_auth_pubname = sender_host_authenticated = NULL;
	authenticated_id = NULL;
	sync_cmd_limit = NON_SYNC_CMD_NON_PIPELINING;
	DEBUG(D_tls) debug_printf("TLS active\n");
	break;
	}
      else
	(void) smtp_log_tls_fail(s);


      if (rc == DEFER)
	{
	smtp_printf("454 TLS currently unavailable\r\n", FALSE);
	break;
	}


      DEBUG(D_tls) debug_printf("TLS failed to start\n");
      while (done <= 0) switch(smtp_read_command(FALSE, GETC_BUFFER_UNLIMITED))
	{
	case EOF_CMD:
	  log_write(L_smtp_connection, LOG_MAIN, "%s closed by EOF",
	    smtp_get_connection_info());
	  smtp_notquit_exit(US"tls-failed", NULL, NULL);
	  done = 2;
	  break;


	case QUIT_CMD:
	  user_msg = NULL;
	  if (  acl_smtp_quit
	     && ((rc = acl_check(ACL_WHERE_QUIT, NULL, acl_smtp_quit, &user_msg,
				&log_msg)) == ERROR))
	      log_write(0, LOG_MAIN|LOG_PANIC, "ACL for QUIT returned ERROR: %s",
		log_msg);
	  if (user_msg)
	    smtp_respond(US"221", 3, TRUE, user_msg);
	  else
	    smtp_printf("221 %s closing connection\r\n", FALSE, smtp_active_hostname);
	  log_write(L_smtp_connection, LOG_MAIN, "%s closed by QUIT",
	    smtp_get_connection_info());
	  done = 2;
	  break;

	default:
	  smtp_printf("554 Security failure\r\n", FALSE);
	  break;
	}
      tls_close(NULL, TLS_SHUTDOWN_NOWAIT);
      break;
    #endif


    case QUIT_CMD:
      smtp_quit_handler(&user_msg, &log_msg);
      done = 2;
      break;


    case RSET_CMD:
      smtp_rset_handler();
      cancel_cutthrough_connection(TRUE, US"RSET received");
      smtp_reset(reset_point);
      toomany = FALSE;
      break;


    case NOOP_CMD:
      HAD(SCH_NOOP);
      smtp_printf("250 OK\r\n", FALSE);
      break;


    case HELP_CMD:
      HAD(SCH_HELP);
      smtp_printf("214-Commands supported:\r\n", TRUE);
	{
	uschar buffer[256];
	buffer[0] = 0;
	Ustrcat(buffer, " AUTH");
	#ifdef SUPPORT_TLS
	if (tls_in.active.sock < 0 &&
	    verify_check_host(&tls_advertise_hosts) != FAIL)
	  Ustrcat(buffer, " STARTTLS");
	#endif
	Ustrcat(buffer, " HELO EHLO MAIL RCPT DATA BDAT");
	Ustrcat(buffer, " NOOP QUIT RSET HELP");
	if (acl_smtp_etrn != NULL) Ustrcat(buffer, " ETRN");
	if (acl_smtp_expn != NULL) Ustrcat(buffer, " EXPN");
	if (acl_smtp_vrfy != NULL) Ustrcat(buffer, " VRFY");
	smtp_printf("214%s\r\n", FALSE, buffer);
	}
      break;


    case EOF_CMD:
      incomplete_transaction_log(US"connection lost");
      smtp_notquit_exit(US"connection-lost", US"421",
	US"%s lost input connection", smtp_active_hostname);


      if (sender_address || recipients_count > 0)
	log_write(L_lost_incoming_connection, LOG_MAIN,
	  "unexpected %s while reading SMTP command from %s%s%s D=%s",
	  f.sender_host_unknown ? "EOF" : "disconnection",
	  f.tcp_in_fastopen_logged
	  ? US""
	  : f.tcp_in_fastopen
	  ? f.tcp_in_fastopen_data ? US"TFO* " : US"TFO "
	  : US"",
	  host_and_ident(FALSE), smtp_read_error,
	  string_timesince(&smtp_connection_start)
	  );

      else
	log_write(L_smtp_connection, LOG_MAIN, "%s %slost%s D=%s",
	  smtp_get_connection_info(),
	  f.tcp_in_fastopen && !f.tcp_in_fastopen_logged ? US"TFO " : US"",
	  smtp_read_error,
	  string_timesince(&smtp_connection_start)
	  );

      done = 1;
      break;


    case ETRN_CMD:
      HAD(SCH_ETRN);
      if (sender_address)
	{
	done = synprot_error(L_smtp_protocol_error, 503, NULL,
	  US"ETRN is not permitted inside a transaction");
	break;
	}

      log_write(L_etrn, LOG_MAIN, "ETRN %s received from %s", smtp_cmd_argument,
	host_and_ident(FALSE));

      if ((rc = acl_check(ACL_WHERE_ETRN, NULL, acl_smtp_etrn,
		  &user_msg, &log_msg)) != OK)
	{
	done = smtp_handle_acl_fail(ACL_WHERE_ETRN, rc, user_msg, log_msg);
	break;
	}


      etrn_serialize_key = string_sprintf("etrn-%s\n", smtp_cmd_data);


      if (smtp_etrn_command)
	{
	uschar *error;
	BOOL rc;
	etrn_command = smtp_etrn_command;
	deliver_domain = smtp_cmd_data;
	rc = transport_set_up_command(&argv, smtp_etrn_command, TRUE, 0, NULL,
	  US"ETRN processing", &error);
	deliver_domain = NULL;
	if (!rc)
	  {
	  log_write(0, LOG_MAIN|LOG_PANIC, "failed to set up ETRN command: %s",
	    error);
	  smtp_printf("458 Internal failure\r\n", FALSE);
	  break;
	  }
	}


      else
	{
	if (*smtp_cmd_data++ != '#')
	  {
	  done = synprot_error(L_smtp_syntax_error, 501, NULL,
	    US"argument must begin with #");
	  break;
	  }
	etrn_command = US"exim -R";
	argv = CUSS child_exec_exim(CEE_RETURN_ARGV, TRUE, NULL, TRUE,
	  *queue_name ? 4 : 2,
	  US"-R", smtp_cmd_data,
	  US"-MCG", queue_name);
	}


      if (host_checking)
	{
	HDEBUG(D_any)
	  {
	  debug_printf("ETRN command is: %s\n", etrn_command);
	  debug_printf("ETRN command execution skipped\n");
	  }
	if (user_msg == NULL) smtp_printf("250 OK\r\n", FALSE);
	  else smtp_user_msg(US"250", user_msg);
	break;
	}


      if (smtp_etrn_serialize && !enq_start(etrn_serialize_key, 1))
	{
	smtp_printf("458 Already processing %s\r\n", FALSE, smtp_cmd_data);
	break;
	}


      oldsignal = signal(SIGCHLD, SIG_IGN);

      if ((pid = fork()) == 0)
	{
	smtp_input = FALSE;
	(void)fclose(smtp_in);
	(void)fclose(smtp_out);

	signal(SIGCHLD, SIG_DFL);


	if (!smtp_etrn_serialize || (pid = fork()) == 0)
	  {
	  DEBUG(D_exec) debug_print_argv(argv);
	  exim_nullstd();
	  execv(CS argv[0], (char *const *)argv);
	  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "exec of \"%s\" (ETRN) failed: %s",
	    etrn_command, strerror(errno));
	  _exit(EXIT_FAILURE);
	  }


	if (pid < 0)
	  log_write(0, LOG_MAIN|LOG_PANIC, "2nd fork for serialized ETRN "
	    "failed: %s", strerror(errno));
	else
	  {
	  int status;
	  DEBUG(D_any) debug_printf("waiting for serialized ETRN process %d\n",
	    (int)pid);
	  (void)wait(&status);
	  DEBUG(D_any) debug_printf("serialized ETRN process %d ended\n",
	    (int)pid);
	  }

	enq_end(etrn_serialize_key);
	_exit(EXIT_SUCCESS);
	}


      if (pid < 0)
	{
	log_write(0, LOG_MAIN|LOG_PANIC, "fork of process for ETRN failed: %s",
	  strerror(errno));
	smtp_printf("458 Unable to fork process\r\n", FALSE);
	if (smtp_etrn_serialize) enq_end(etrn_serialize_key);
	}
      else
	{
	if (user_msg == NULL) smtp_printf("250 OK\r\n", FALSE);
	  else smtp_user_msg(US"250", user_msg);
	}

      signal(SIGCHLD, oldsignal);
      break;


    case BADARG_CMD:
      done = synprot_error(L_smtp_syntax_error, 501, NULL,
	US"unexpected argument data");
      break;


    case BADCHAR_CMD:
      done = synprot_error(L_smtp_syntax_error, 0, NULL,
	US"NUL character(s) present (shown as '?')");
      smtp_printf("501 NUL characters are not allowed in SMTP commands\r\n",
		  FALSE);
      break;


    case BADSYN_CMD:
    SYNC_FAILURE:
      if (smtp_inend >= smtp_inbuffer + IN_BUFFER_SIZE)
	smtp_inend = smtp_inbuffer + IN_BUFFER_SIZE - 1;
      c = smtp_inend - smtp_inptr;
      if (c > 150) c = 150;
      smtp_inptr[c] = 0;
      incomplete_transaction_log(US"sync failure");
      log_write(0, LOG_MAIN|LOG_REJECT, "SMTP protocol synchronization error "
	"(next input sent too soon: pipelining was%s advertised): "
	"rejected \"%s\" %s next input=\"%s\"",
	f.smtp_in_pipelining_advertised ? "" : " not",
	smtp_cmd_buffer, host_and_ident(TRUE),
	string_printing(smtp_inptr));
      smtp_notquit_exit(US"synchronization-error", US"554",
	US"SMTP synchronization error");
      done = 1;
      break;


    case TOO_MANY_NONMAIL_CMD:
      s = smtp_cmd_buffer;
      while (*s != 0 && !isspace(*s)) s++;
      incomplete_transaction_log(US"too many non-mail commands");
      log_write(0, LOG_MAIN|LOG_REJECT, "SMTP call from %s dropped: too many "
	"nonmail commands (last was \"%.*s\")",  host_and_ident(FALSE),
	(int)(s - smtp_cmd_buffer), smtp_cmd_buffer);
      smtp_notquit_exit(US"bad-commands", US"554", US"Too many nonmail commands");
      done = 1;
      break;

#ifdef SUPPORT_PROXY
    case PROXY_FAIL_IGNORE_CMD:
      smtp_printf("503 Command refused, required Proxy negotiation failed\r\n", FALSE);
      break;
#endif

    default:
      if (unknown_command_count++ >= smtp_max_unknown_commands)
	{
	log_write(L_smtp_syntax_error, LOG_MAIN,
	  "SMTP syntax error in \"%s\" %s %s",
	  string_printing(smtp_cmd_buffer), host_and_ident(TRUE),
	  US"unrecognized command");
	incomplete_transaction_log(US"unrecognized command");
	smtp_notquit_exit(US"bad-commands", US"500",
	  US"Too many unrecognized commands");
	done = 2;
	log_write(0, LOG_MAIN|LOG_REJECT, "SMTP call from %s dropped: too many "
	  "unrecognized commands (last was \"%s\")", host_and_ident(FALSE),
	  string_printing(smtp_cmd_buffer));
	}
      else
	done = synprot_error(L_smtp_syntax_error, 500, NULL,
	  US"unrecognized command");
      break;
    }


  COMMAND_LOOP:
  last_was_rej_mail = was_rej_mail;
  last_was_rcpt = was_rcpt;
  continue;
  }

return done - 2;
}
