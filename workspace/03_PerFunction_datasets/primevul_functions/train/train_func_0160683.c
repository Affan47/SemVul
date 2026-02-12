deliver_message(uschar *id, BOOL forced, BOOL give_up)
{
int i, rc;
int final_yield = DELIVER_ATTEMPTED_NORMAL;
time_t now = time(NULL);
address_item *addr_last = NULL;
uschar *filter_message = NULL;
int process_recipients = RECIP_ACCEPT;
open_db dbblock;
open_db *dbm_file;
extern int acl_where;

uschar *info = queue_run_pid == (pid_t)0
  ? string_sprintf("delivering %s", id)
  : string_sprintf("delivering %s (queue run pid %d)", id, queue_run_pid);


set_process_info("%s", info);

if (  !(debug_selector & D_process_info)
   && (debug_selector & (D_deliver|D_queue_run|D_v))
   )
  debug_printf("%s\n", info);


#ifdef SA_NOCLDWAIT
  {
  struct sigaction act;
  act.sa_handler = SIG_DFL;
  sigemptyset(&(act.sa_mask));
  act.sa_flags = 0;
  sigaction(SIGCHLD, &act, NULL);
  }
#else
signal(SIGCHLD, SIG_DFL);
#endif


Ustrcpy(message_id, id);
f.deliver_force = forced;
return_count = 0;
message_size = 0;


update_spool = FALSE;
remove_journal = TRUE;


acl_where = ACL_WHERE_DELIVERY;


random_seed = 0;


if ((deliver_datafile = spool_open_datafile(id)) < 0)
  return continue_closedown();


  {
  uschar * spoolname = string_sprintf("%s-H", id);
  if ((rc = spool_read_header(spoolname, TRUE, TRUE)) != spool_read_OK)
    {
    if (errno == ERRNO_SPOOLFORMAT)
      {
      struct stat statbuf;
      if (Ustat(spool_fname(US"input", message_subdir, spoolname, US""),
		&statbuf) == 0)
	log_write(0, LOG_MAIN, "Format error in spool file %s: "
	  "size=" OFF_T_FMT, spoolname, statbuf.st_size);
      else
	log_write(0, LOG_MAIN, "Format error in spool file %s", spoolname);
      }
    else
      log_write(0, LOG_MAIN, "Error reading spool file %s: %s", spoolname,
	strerror(errno));


    if (rc != spool_read_hdrerror)
      {
      received_time.tv_sec = received_time.tv_usec = 0;

      for (i = 0; i < 6; i++)
	received_time.tv_sec = received_time.tv_sec * BASE_62 + tab62[id[i] - '0'];
      }


    if (now - received_time.tv_sec > keep_malformed)
      {
      Uunlink(spool_fname(US"msglog", message_subdir, id, US""));
      Uunlink(spool_fname(US"input", message_subdir, id, US"-D"));
      Uunlink(spool_fname(US"input", message_subdir, id, US"-H"));
      Uunlink(spool_fname(US"input", message_subdir, id, US"-J"));
      log_write(0, LOG_MAIN, "Message removed because older than %s",
	readconf_printtime(keep_malformed));
      }

    (void)close(deliver_datafile);
    deliver_datafile = -1;
    return continue_closedown();
    }
  }


  {
  uschar * fname = spool_fname(US"input", message_subdir, id, US"-J");
  FILE * jread;

  if (  (journal_fd = Uopen(fname, O_RDWR|O_APPEND
#ifdef O_CLOEXEC
				    | O_CLOEXEC
#endif
#ifdef O_NOFOLLOW
				    | O_NOFOLLOW
#endif
	, SPOOL_MODE)) >= 0
     && lseek(journal_fd, 0, SEEK_SET) == 0
     && (jread = fdopen(journal_fd, "rb"))
     )
    {
    while (Ufgets(big_buffer, big_buffer_size, jread))
      {
      int n = Ustrlen(big_buffer);
      big_buffer[n-1] = 0;
      tree_add_nonrecipient(big_buffer);
      DEBUG(D_deliver) debug_printf("Previously delivered address %s taken from "
	"journal file\n", big_buffer);
      }
    rewind(jread);
    if ((journal_fd = dup(fileno(jread))) < 0)
      journal_fd = fileno(jread);
    else
      (void) fclose(jread);


    (void)spool_write_header(message_id, SW_DELIVERING, NULL);
    }
  else if (errno != ENOENT)
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "attempt to open journal for reading gave: "
      "%s", strerror(errno));
    return continue_closedown();
    }


  if (!recipients_list)
    {
    (void)close(deliver_datafile);
    deliver_datafile = -1;
    log_write(0, LOG_MAIN, "Spool error: no recipients for %s", fname);
    return continue_closedown();
    }
  }


if (f.deliver_freeze)
  {
#ifdef SUPPORT_MOVE_FROZEN_MESSAGES


  if (  move_frozen_messages
     && spool_move_message(id, message_subdir, US"", US"F")
     )
    return continue_closedown();
#endif


  if (timeout_frozen_after > 0 && message_age >= timeout_frozen_after)
    {
    log_write(0, LOG_MAIN, "cancelled by timeout_frozen_after");
    process_recipients = RECIP_FAIL_TIMEOUT;
    }


  else if (!*sender_address && message_age >= ignore_bounce_errors_after)
    log_write(0, LOG_MAIN, "Unfrozen by errmsg timer");


  else
    {
    if (  (  sender_address[0] == 0
	  || auto_thaw <= 0
	  || now <= deliver_frozen_at + auto_thaw
          )
       && (  !forced || !f.deliver_force_thaw
	  || !f.admin_user || continue_hostname
       )  )
      {
      (void)close(deliver_datafile);
      deliver_datafile = -1;
      log_write(L_skip_delivery, LOG_MAIN, "Message is frozen");
      return continue_closedown();
      }


    if (forced)
      {
      f.deliver_manual_thaw = TRUE;
      log_write(0, LOG_MAIN, "Unfrozen by forced delivery");
      }
    else log_write(0, LOG_MAIN, "Unfrozen by auto-thaw");
    }


  f.deliver_freeze = FALSE;
  update_spool = TRUE;
  }


if (message_logs)
  {
  uschar * fname = spool_fname(US"msglog", message_subdir, id, US"");
  uschar * error;
  int fd;

  if ((fd = open_msglog_file(fname, SPOOL_MODE, &error)) < 0)
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't %s message log %s: %s", error,
      fname, strerror(errno));
    return continue_closedown();
    }


  if (!(message_log = fdopen(fd, "a")))
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't fdopen message log %s: %s",
      fname, strerror(errno));
    return continue_closedown();
    }
  }


if (give_up)
  {
  struct passwd *pw = getpwuid(real_uid);
  log_write(0, LOG_MAIN, "cancelled by %s",
      pw ? US pw->pw_name : string_sprintf("uid %ld", (long int)real_uid));
  process_recipients = RECIP_FAIL;
  }


else if (received_count > received_headers_max)
  process_recipients = RECIP_FAIL_LOOP;


else if (system_filter && process_recipients != RECIP_FAIL_TIMEOUT)
  {
  int rc;
  int filtertype;
  ugid_block ugid;
  redirect_block redirect;

  if (system_filter_uid_set)
    {
    ugid.uid = system_filter_uid;
    ugid.gid = system_filter_gid;
    ugid.uid_set = ugid.gid_set = TRUE;
    }
  else
    {
    ugid.uid_set = ugid.gid_set = FALSE;
    }

  return_path = sender_address;
  f.enable_dollar_recipients = TRUE;
  f.system_filtering = TRUE;


  redirect.string = system_filter;
  redirect.isfile = TRUE;
  redirect.check_owner = redirect.check_group = FALSE;
  redirect.owners = NULL;
  redirect.owngroups = NULL;
  redirect.pw = NULL;
  redirect.modemask = 0;

  DEBUG(D_deliver|D_filter) debug_printf("running system filter\n");

  rc = rda_interpret(
    &redirect,
    RDO_DEFER |
      RDO_FAIL |
      RDO_FILTER |
      RDO_FREEZE |
      RDO_REALLOG |
      RDO_REWRITE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ugid,
    &addr_new,
    &filter_message,
    NULL,
    &filtertype,
    US"system filter");

  DEBUG(D_deliver|D_filter) debug_printf("system filter returned %d\n", rc);

  if (rc == FF_ERROR || rc == FF_NONEXIST)
    {
    (void)close(deliver_datafile);
    deliver_datafile = -1;
    log_write(0, LOG_MAIN|LOG_PANIC, "Error in system filter: %s",
      string_printing(filter_message));
    return continue_closedown();
    }


  f.system_filtering = FALSE;
  f.enable_dollar_recipients = FALSE;
  if (filter_message && filter_message[0] == 0) filter_message = NULL;


  memcpy(filter_sn, filter_n, sizeof(filter_sn));


  if (rc == FF_DEFER)
    {
    process_recipients = RECIP_DEFER;
    deliver_msglog("Delivery deferred by system filter\n");
    log_write(0, LOG_MAIN, "Delivery deferred by system filter");
    }


  else if (rc == FF_FREEZE && !f.deliver_manual_thaw)
    {
    f.deliver_freeze = TRUE;
    deliver_frozen_at = time(NULL);
    process_recipients = RECIP_DEFER;
    frozen_info = string_sprintf(" by the system filter%s%s",
      filter_message ? US": " : US"",
      filter_message ? filter_message : US"");
    }


  else if (rc == FF_FAIL)
    {
    uschar *colon = US"";
    uschar *logmsg = US"";
    int loglen = 0;

    process_recipients = RECIP_FAIL_FILTER;

    if (filter_message)
      {
      uschar *logend;
      colon = US": ";
      if (  filter_message[0] == '<'
         && filter_message[1] == '<'
	 && (logend = Ustrstr(filter_message, ">>"))
	 )
        {
        logmsg = filter_message + 2;
        loglen = logend - logmsg;
        filter_message = logend + 2;
        if (filter_message[0] == 0) filter_message = NULL;
        }
      else
        {
        logmsg = filter_message;
        loglen = Ustrlen(filter_message);
        }
      }

    log_write(0, LOG_MAIN, "cancelled by system filter%s%.*s", colon, loglen,
      logmsg);
    }


  else if (rc == FF_DELIVERED)
    {
    process_recipients = RECIP_IGNORE;
    if (addr_new)
      log_write(0, LOG_MAIN, "original recipients ignored (system filter)");
    else
      log_write(0, LOG_MAIN, "=> discarded (system filter)");
    }


  if (addr_new)
    {
    int uid = (system_filter_uid_set)? system_filter_uid : geteuid();
    int gid = (system_filter_gid_set)? system_filter_gid : getegid();


    address_item *p = addr_new;
    address_item *parent = deliver_make_addr(US"system-filter", FALSE);

    parent->domain = string_copylc(qualify_domain_recipient);
    parent->local_part = US"system-filter";


    while (p)
      {
      if (parent->child_count == USHRT_MAX)
        log_write(0, LOG_MAIN|LOG_PANIC_DIE, "system filter generated more "
          "than %d delivery addresses", USHRT_MAX);
      parent->child_count++;
      p->parent = parent;

      if (testflag(p, af_pfr))
        {
        uschar *tpname;
        uschar *type;
        p->uid = uid;
        p->gid = gid;
        setflag(p, af_uid_set);
        setflag(p, af_gid_set);
        setflag(p, af_allow_file);
        setflag(p, af_allow_pipe);
        setflag(p, af_allow_reply);


        if (p->address[0] == '|')
          {
          type = US"pipe";
          tpname = system_filter_pipe_transport;
          address_pipe = p->address;
          }
        else if (p->address[0] == '>')
          {
          type = US"reply";
          tpname = system_filter_reply_transport;
          }
        else
          {
          if (p->address[Ustrlen(p->address)-1] == '/')
            {
            type = US"directory";
            tpname = system_filter_directory_transport;
            }
          else
            {
            type = US"file";
            tpname = system_filter_file_transport;
            }
          address_file = p->address;
          }


        if (tpname)
          {
          uschar *tmp = expand_string(tpname);
          address_file = address_pipe = NULL;
          if (!tmp)
            p->message = string_sprintf("failed to expand \"%s\" as a "
              "system filter transport name", tpname);
          tpname = tmp;
          }
        else
          p->message = string_sprintf("system_filter_%s_transport is unset",
            type);

        if (tpname)
          {
          transport_instance *tp;
          for (tp = transports; tp; tp = tp->next)
            if (Ustrcmp(tp->name, tpname) == 0)
              {
              p->transport = tp;
              break;
              }
          if (!tp)
            p->message = string_sprintf("failed to find \"%s\" transport "
              "for system filter delivery", tpname);
          }


        if (!p->transport)
          {
          address_item *badp = p;
          p = p->next;
          if (!addr_last) addr_new = p; else addr_last->next = p;
          badp->local_part = badp->address;
          post_process_one(badp, DEFER, LOG_MAIN|LOG_PANIC, EXIM_DTYPE_ROUTER, 0);
          continue;
          }
        }


      DEBUG(D_deliver|D_filter)
        debug_printf("system filter added %s\n", p->address);

      addr_last = p;
      p = p->next;
      }
    }
  }


if (process_recipients != RECIP_IGNORE)
  for (i = 0; i < recipients_count; i++)
    if (!tree_search(tree_nonrecipients, recipients_list[i].address))
      {
      recipient_item *r = recipients_list + i;
      address_item *new = deliver_make_addr(r->address, FALSE);
      new->prop.errors_address = r->errors_to;
#ifdef SUPPORT_I18N
      if ((new->prop.utf8_msg = message_smtputf8))
	{
	new->prop.utf8_downcvt =       message_utf8_downconvert == 1;
	new->prop.utf8_downcvt_maybe = message_utf8_downconvert == -1;
	DEBUG(D_deliver) debug_printf("utf8, downconvert %s\n",
	  new->prop.utf8_downcvt ? "yes"
	  : new->prop.utf8_downcvt_maybe ? "ifneeded"
	  : "no");
	}
#endif

      if (r->pno >= 0)
        new->onetime_parent = recipients_list[r->pno].address;


      new->dsn_flags = r->dsn_flags & rf_dsnflags;
      new->dsn_orcpt = r->orcpt;
      DEBUG(D_deliver) debug_printf("DSN: set orcpt: %s  flags: %d\n",
	new->dsn_orcpt ? new->dsn_orcpt : US"", new->dsn_flags);

      switch (process_recipients)
        {


        case RECIP_DEFER:
	  new->next = addr_defer;
	  addr_defer = new;
	  break;


        case RECIP_FAIL_FILTER:
	  new->message =
	    filter_message ? filter_message : US"delivery cancelled";
	  setflag(new, af_pass_message);
	  goto RECIP_QUEUE_FAILED;


        case RECIP_FAIL_TIMEOUT:
	  new->message  = US"delivery cancelled; message timed out";
	  goto RECIP_QUEUE_FAILED;


        case RECIP_FAIL:
	  new->message  = US"delivery cancelled by administrator";


        RECIP_QUEUE_FAILED:
	  if (sender_address[0])
	    {
	    new->next = addr_failed;
	    addr_failed = new;
	    }
        break;


        case RECIP_FAIL_LOOP:
	  new->message = US"Too many \"Received\" headers - suspected mail loop";
	  post_process_one(new, FAIL, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
	  break;


        default:
	  if (!addr_new) addr_new = new; else addr_last->next = new;
	  addr_last = new;
	  break;
        }

#ifndef DISABLE_EVENT
      if (process_recipients != RECIP_ACCEPT)
	{
	uschar * save_local =  deliver_localpart;
	const uschar * save_domain = deliver_domain;
	uschar * addr = new->address, * errmsg = NULL;
	int start, end, dom;

	if (!parse_extract_address(addr, &errmsg, &start, &end, &dom, TRUE))
	  log_write(0, LOG_MAIN|LOG_PANIC,
                "failed to parse address '%.100s': %s\n", addr, errmsg);
	else
	  {
	  deliver_localpart =
	    string_copyn(addr+start, dom ? (dom-1) - start : end - start);
	  deliver_domain = dom ? CUS string_copyn(addr+dom, end - dom) : CUS"";

	  event_raise(event_action, US"msg:fail:internal", new->message);

	  deliver_localpart = save_local;
	  deliver_domain = save_domain;
	  }
	}
#endif
      }

DEBUG(D_deliver)
  {
  address_item *p;
  debug_printf("Delivery address list:\n");
  for (p = addr_new; p; p = p->next)
    debug_printf("  %s %s\n", p->address,
      p->onetime_parent ? p->onetime_parent : US"");
  }


deliver_in_buffer = store_malloc(DELIVER_IN_BUFFER_SIZE);
deliver_out_buffer = store_malloc(DELIVER_OUT_BUFFER_SIZE);


f.header_rewritten = FALSE;
while (addr_new)
  {
  address_item *addr, *parent;


  if (!(dbm_file = dbfn_open(US"retry", O_RDONLY, &dbblock, FALSE)))
    DEBUG(D_deliver|D_retry|D_route|D_hints_lookup)
      debug_printf("no retry data available\n");


  while (addr_new)
    {
    int rc;
    uschar *p;
    tree_node *tnode;
    dbdata_retry *domain_retry_record;
    dbdata_retry *address_retry_record;

    addr = addr_new;
    addr_new = addr->next;

    DEBUG(D_deliver|D_retry|D_route)
      {
      debug_printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
      debug_printf("Considering: %s\n", addr->address);
      }


    if (testflag(addr, af_pfr))
      {


      if (testflag(addr, af_bad_reply))
        {
        addr->basic_errno = ERRNO_BADADDRESS2;
        addr->local_part = addr->address;
        addr->message =
          US"filter autoreply generated syntactically invalid recipient";
        addr->prop.ignore_error = TRUE;
        (void) post_process_one(addr, FAIL, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
        continue;
        }


      addr->unique =
        string_sprintf("%s:%s", addr->address, addr->parent->unique +
          (testflag(addr->parent, af_homonym)? 3:0));

      addr->address_retry_key = addr->domain_retry_key =
        string_sprintf("T:%s", addr->unique);


      if (addr->address[0] == '>')
        {
        while (tree_search(tree_duplicates, addr->unique))
          addr->unique = string_sprintf(">%s", addr->unique);
        }

      else if ((tnode = tree_search(tree_duplicates, addr->unique)))
        {
        DEBUG(D_deliver|D_route)
          debug_printf("%s is a duplicate address: discarded\n", addr->address);
        addr->dupof = tnode->data.ptr;
        addr->next = addr_duplicate;
        addr_duplicate = addr;
        continue;
        }

      DEBUG(D_deliver|D_route) debug_printf("unique = %s\n", addr->unique);


      if (tree_search(tree_nonrecipients, addr->unique))
        {
        DEBUG(D_deliver|D_route)
          debug_printf("%s was previously delivered: discarded\n", addr->address);
        child_done(addr, tod_stamp(tod_log));
        continue;
        }


      tree_add_duplicate(addr->unique, addr);


      addr->local_part = addr->address;
      addr->domain = addr->parent->domain;


      if (testflag(addr, af_file))
        {
        if (!testflag(addr, af_allow_file))
          {
          addr->basic_errno = ERRNO_FORBIDFILE;
          addr->message = US"delivery to file forbidden";
          (void)post_process_one(addr, FAIL, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
          continue;
          }
        }
      else if (addr->address[0] == '|')
        {
        if (!testflag(addr, af_allow_pipe))
          {
          addr->basic_errno = ERRNO_FORBIDPIPE;
          addr->message = US"delivery to pipe forbidden";
          (void)post_process_one(addr, FAIL, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
          continue;
          }
        }
      else if (!testflag(addr, af_allow_reply))
        {
        addr->basic_errno = ERRNO_FORBIDREPLY;
        addr->message = US"autoreply forbidden";
        (void)post_process_one(addr, FAIL, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
        continue;
        }


      if (addr->basic_errno == ERRNO_BADTRANSPORT)
        {
        (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
        continue;
        }


      if (Ustrcmp(addr->address, "/dev/null") == 0)
        {
        uschar *save = addr->transport->name;
        addr->transport->name = US"**bypassed**";
        (void)post_process_one(addr, OK, LOG_MAIN, EXIM_DTYPE_TRANSPORT, '=');
        addr->transport->name = save;
        continue;
        }


      DEBUG(D_deliver|D_route)
        debug_printf("queued for %s transport\n", addr->transport->name);
      addr->next = addr_local;
      addr_local = addr;
      continue;
      }


    if ((rc = deliver_split_address(addr)) == DEFER)
      {
      addr->message = US"cannot check percent_hack_domains";
      addr->basic_errno = ERRNO_LISTDEFER;
      (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_NONE, 0);
      continue;
      }


    deliver_domain = addr->domain;
    if (  !forced && hold_domains
       && (rc = match_isinlist(addr->domain, (const uschar **)&hold_domains, 0,
           &domainlist_anchor, addr->domain_cache, MCL_DOMAIN, TRUE,
           NULL)) != FAIL
       )
      {
      if (rc == DEFER)
        {
        addr->message = US"hold_domains lookup deferred";
        addr->basic_errno = ERRNO_LISTDEFER;
        }
      else
        {
        addr->message = US"domain is held";
        addr->basic_errno = ERRNO_HELD;
        }
      (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_NONE, 0);
      continue;
      }


    for (parent = addr->parent; parent; parent = parent->parent)
      if (strcmpic(addr->address, parent->address) == 0) break;


    if (parent)
      {
      setflag(addr, af_homonym);
      if (parent->unique[0] != '\\')
        addr->unique = string_sprintf("\\0\\%s", addr->address);
      else
        addr->unique = string_sprintf("\\%c\\%s", parent->unique[1] + 1,
          addr->address);
      }


    p = Ustrrchr(addr->unique, '@');
    while (*p != 0) { *p = tolower(*p); p++; }

    DEBUG(D_deliver|D_route) debug_printf("unique = %s\n", addr->unique);

    if (tree_search(tree_nonrecipients, addr->unique))
      {
      DEBUG(D_deliver|D_route)
        debug_printf("%s was previously delivered: discarded\n", addr->unique);
      child_done(addr, tod_stamp(tod_log));
      continue;
      }


    addr->domain_retry_key = string_sprintf("R:%s", addr->domain);
    addr->address_retry_key = string_sprintf("R:%s@%s", addr->local_part,
      addr->domain);

    if (dbm_file)
      {
      domain_retry_record = dbfn_read(dbm_file, addr->domain_retry_key);
      if (  domain_retry_record
         && now - domain_retry_record->time_stamp > retry_data_expire
	 )
        domain_retry_record = NULL;

      address_retry_record = dbfn_read(dbm_file, addr->address_retry_key);
      if (  address_retry_record
         && now - address_retry_record->time_stamp > retry_data_expire
	 )
        address_retry_record = NULL;

      if (!address_retry_record)
        {
        uschar *altkey = string_sprintf("%s:<%s>", addr->address_retry_key,
          sender_address);
        address_retry_record = dbfn_read(dbm_file, altkey);
        if (  address_retry_record
	   && now - address_retry_record->time_stamp > retry_data_expire)
          address_retry_record = NULL;
        }
      }
    else
      domain_retry_record = address_retry_record = NULL;

    DEBUG(D_deliver|D_retry)
      {
      if (!domain_retry_record)
        debug_printf("no domain retry record\n");
      if (!address_retry_record)
        debug_printf("no address retry record\n");
      }


    if (continue_hostname && domain_retry_record)
      {
      addr->message = US"reusing SMTP connection skips previous routing defer";
      addr->basic_errno = ERRNO_RRETRY;
      (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
      }


    else if (  (  f.queue_running && !f.deliver_force
	       || continue_hostname
	       )
            && (  (  domain_retry_record
		  && now < domain_retry_record->next_try
		  && !domain_retry_record->expired
		  )
	       || (  address_retry_record
		  && now < address_retry_record->next_try
	       )  )
            && (  domain_retry_record
	       || !address_retry_record
	       || !retry_ultimate_address_timeout(addr->address_retry_key,
				 addr->domain, address_retry_record, now)
	    )  )
      {
      addr->message = US"retry time not reached";
      addr->basic_errno = ERRNO_RRETRY;
      (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
      }


    else
      {
      if (domain_retry_record || address_retry_record)
        setflag(addr, af_dr_retry_exists);
      addr->next = addr_route;
      addr_route = addr;
      DEBUG(D_deliver|D_route)
        debug_printf("%s: queued for routing\n", addr->address);
      }
    }


  if (dbm_file) dbfn_close(dbm_file);


  if (!f.deliver_force && queue_domains)
    {
    address_item *okaddr = NULL;
    while (addr_route)
      {
      address_item *addr = addr_route;
      addr_route = addr->next;

      deliver_domain = addr->domain;
      if ((rc = match_isinlist(addr->domain, (const uschar **)&queue_domains, 0,
            &domainlist_anchor, addr->domain_cache, MCL_DOMAIN, TRUE, NULL))
              != OK)
        if (rc == DEFER)
          {
          addr->basic_errno = ERRNO_LISTDEFER;
          addr->message = US"queue_domains lookup deferred";
          (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
          }
        else
          {
          addr->next = okaddr;
          okaddr = addr;
          }
      else
        {
        addr->basic_errno = ERRNO_QUEUE_DOMAIN;
        addr->message = US"domain is in queue_domains";
        (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
        }
      }

    addr_route = okaddr;
    }


  while (addr_route)
    {
    int rc;
    address_item *addr = addr_route;
    const uschar *old_domain = addr->domain;
    uschar *old_unique = addr->unique;
    addr_route = addr->next;
    addr->next = NULL;


    if (!(return_path = addr->prop.errors_address))
      return_path = sender_address;


    if ((rc = route_address(addr, &addr_local, &addr_remote, &addr_new,
         &addr_succeed, v_none)) == DEFER)
      retry_add_item(addr,
        addr->router->retry_use_local_part
        ? string_sprintf("R:%s@%s", addr->local_part, addr->domain)
	: string_sprintf("R:%s", addr->domain),
	0);


    else if (testflag(addr, af_dr_retry_exists))
      {
      uschar *altkey = string_sprintf("%s:<%s>", addr->address_retry_key,
        sender_address);
      retry_add_item(addr, altkey, rf_delete);
      retry_add_item(addr, addr->address_retry_key, rf_delete);
      retry_add_item(addr, addr->domain_retry_key, rf_delete);
      if (Ustrcmp(addr->domain, old_domain) != 0)
        retry_add_item(addr, string_sprintf("R:%s", old_domain), rf_delete);
      }


    if (rc == DISCARD)
      {
      address_done(addr, tod_stamp(tod_log));
      continue;
      }


    if (rc != OK)
      {
      (void)post_process_one(addr, rc, LOG_MAIN, EXIM_DTYPE_ROUTER, 0);
      continue;
      }


    if (  addr->unique != old_unique
       && tree_search(tree_nonrecipients, addr->unique) != 0
       )
      {
      DEBUG(D_deliver|D_route) debug_printf("%s was previously delivered: "
        "discarded\n", addr->address);
      if (addr_remote == addr) addr_remote = addr->next;
      else if (addr_local == addr) addr_local = addr->next;
      }


    if (  addr_remote == addr
       && addr->router->same_domain_copy_routing
       && !addr->prop.extra_headers
       && !addr->prop.remove_headers
       && old_domain == addr->domain
       )
      {
      address_item **chain = &addr_route;
      while (*chain)
        {
        address_item *addr2 = *chain;
        if (Ustrcmp(addr2->domain, addr->domain) != 0)
          {
          chain = &(addr2->next);
          continue;
          }


        *chain = addr2->next;
        addr2->next = addr_remote;
        addr_remote = addr2;


        addr2->domain = addr->domain;
        addr2->router = addr->router;
        addr2->transport = addr->transport;
        addr2->host_list = addr->host_list;
        addr2->fallback_hosts = addr->fallback_hosts;
        addr2->prop.errors_address = addr->prop.errors_address;
        copyflag(addr2, addr, af_hide_child);
        copyflag(addr2, addr, af_local_host_removed);

        DEBUG(D_deliver|D_route)
          debug_printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
                       "routing %s\n"
                       "Routing for %s copied from %s\n",
            addr2->address, addr2->address, addr->address);
        }
      }
    }
  }


DEBUG(D_deliver|D_retry|D_route)
  {
  address_item *p;
  debug_printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
  debug_printf("After routing:\n  Local deliveries:\n");
  for (p = addr_local; p; p = p->next)
    debug_printf("    %s\n", p->address);

  debug_printf("  Remote deliveries:\n");
  for (p = addr_remote; p; p = p->next)
    debug_printf("    %s\n", p->address);

  debug_printf("  Failed addresses:\n");
  for (p = addr_failed; p; p = p->next)
    debug_printf("    %s\n", p->address);

  debug_printf("  Deferred addresses:\n");
  for (p = addr_defer; p; p = p->next)
    debug_printf("    %s\n", p->address);
  }


search_tidyup();
route_tidyup();


local_user_gid = (gid_t)(-1);
local_user_uid = (uid_t)(-1);


do_duplicate_check(&addr_local);
do_duplicate_check(&addr_remote);


if (  mua_wrapper
   && (addr_local || addr_failed || addr_defer)
   )
  {
  address_item *addr;
  uschar *which, *colon, *msg;

  if (addr_local)
    {
    addr = addr_local;
    which = US"local";
    }
  else if (addr_defer)
    {
    addr = addr_defer;
    which = US"deferred";
    }
  else
    {
    addr = addr_failed;
    which = US"failed";
    }

  while (addr->parent) addr = addr->parent;

  if (addr->message)
    {
    colon = US": ";
    msg = addr->message;
    }
  else colon = msg = US"";


  if (addr != addr_failed)
    log_write(0, LOG_MAIN, "** %s routing yielded a %s delivery",
      addr->address, which);


  fprintf(stderr, "routing %s yielded a %s delivery%s%s\n", addr->address,
    which, colon, msg);

  final_yield = DELIVER_MUA_FAILED;
  addr_failed = addr_defer = NULL;
  goto DELIVERY_TIDYUP;
  }


if (continue_transport)
  {
  if (addr_defer)
    {
    address_item *addr = addr_defer;
    while (addr->next) addr = addr->next;
    addr->next = addr_local;
    }
  else
    addr_defer = addr_local;
  addr_local = NULL;
  }


if (  f.header_rewritten
   && (  addr_local && (addr_local->next || addr_remote)
      || addr_remote && addr_remote->next
   )  )
  {

  (void)spool_write_header(message_id, SW_DELIVERING, NULL);
  f.header_rewritten = FALSE;
  }


if (addr_local || addr_remote)
  {
  if (journal_fd < 0)
    {
    uschar * fname = spool_fname(US"input", message_subdir, id, US"-J");

    if ((journal_fd = Uopen(fname,
#ifdef O_CLOEXEC
			O_CLOEXEC |
#endif
			O_WRONLY|O_APPEND|O_CREAT|O_EXCL, SPOOL_MODE)) < 0)
      {
      log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't open journal file %s: %s",
	fname, strerror(errno));
      return DELIVER_NOT_ATTEMPTED;
      }


    if(  fchown(journal_fd, exim_uid, exim_gid)
      || fchmod(journal_fd, SPOOL_MODE)
#ifndef O_CLOEXEC
      || fcntl(journal_fd, F_SETFD, fcntl(journal_fd, F_GETFD) | FD_CLOEXEC)
#endif
      )
      {
      int ret = Uunlink(fname);
      log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't set perms on journal file %s: %s",
	fname, strerror(errno));
      if(ret  &&  errno != ENOENT)
	log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to unlink %s: %s",
	  fname, strerror(errno));
      return DELIVER_NOT_ATTEMPTED;
      }
    }
  }
else if (journal_fd >= 0)
  {
  close(journal_fd);
  journal_fd = -1;
  }


if (!regex_IGNOREQUOTA)
  regex_IGNOREQUOTA =
    regex_must_compile(US"\\n250[\\s\\-]IGNOREQUOTA(\\s|\\n|$)", FALSE, TRUE);


if (addr_local)
  {
  DEBUG(D_deliver|D_transport)
    debug_printf(">>>>>>>>>>>>>>>> Local deliveries >>>>>>>>>>>>>>>>\n");
  do_local_deliveries();
  f.disable_logging = FALSE;
  }


if (f.queue_run_local)
  while (addr_remote)
    {
    address_item *addr = addr_remote;
    addr_remote = addr->next;
    addr->next = NULL;
    addr->basic_errno = ERRNO_LOCAL_ONLY;
    addr->message = US"remote deliveries suppressed";
    (void)post_process_one(addr, DEFER, LOG_MAIN, EXIM_DTYPE_TRANSPORT, 0);
    }


if (addr_remote)
  {
  DEBUG(D_deliver|D_transport)
    debug_printf(">>>>>>>>>>>>>>>> Remote deliveries >>>>>>>>>>>>>>>>\n");


  deliver_init();


  if (remote_sort_domains) sort_remote_deliveries();
  if (!do_remote_deliveries(FALSE))
    {
    log_write(0, LOG_MAIN, "** mua_wrapper is set but recipients cannot all "
      "be delivered in one transaction");
    fprintf(stderr, "delivery to smarthost failed (configuration problem)\n");

    final_yield = DELIVER_MUA_FAILED;
    addr_failed = addr_defer = NULL;
    goto DELIVERY_TIDYUP;
    }


  if (addr_fallback && !mua_wrapper)
    {
    DEBUG(D_deliver) debug_printf("Delivering to fallback hosts\n");
    addr_remote = addr_fallback;
    addr_fallback = NULL;
    if (remote_sort_domains) sort_remote_deliveries();
    do_remote_deliveries(TRUE);
    }
  f.disable_logging = FALSE;
  }


DEBUG(D_deliver)
  debug_printf(">>>>>>>>>>>>>>>> deliveries are done >>>>>>>>>>>>>>>>\n");
cancel_cutthrough_connection(TRUE, US"deliveries are done");


exim_setugid(exim_uid, exim_gid, FALSE, US"post-delivery tidying");

set_process_info("tidying up after delivering %s", message_id);
signal(SIGTERM, SIG_IGN);


if (mua_wrapper)
  {
  if (addr_defer)
    {
    address_item *addr, *nextaddr;
    for (addr = addr_defer; addr; addr = nextaddr)
      {
      log_write(0, LOG_MAIN, "** %s mua_wrapper forced failure for deferred "
        "delivery", addr->address);
      nextaddr = addr->next;
      addr->next = addr_failed;
      addr_failed = addr;
      }
    addr_defer = NULL;
    }


  if (!addr_failed)
    final_yield = DELIVER_MUA_SUCCEEDED;
  else
    {
    host_item * host;
    uschar *s = addr_failed->user_message;

    if (!s) s = addr_failed->message;

    fprintf(stderr, "Delivery failed: ");
    if (addr_failed->basic_errno > 0)
      {
      fprintf(stderr, "%s", strerror(addr_failed->basic_errno));
      if (s) fprintf(stderr, ": ");
      }
    if ((host = addr_failed->host_used))
      fprintf(stderr, "H=%s [%s]: ", host->name, host->address);
    if (s)
      fprintf(stderr, "%s", CS s);
    else if (addr_failed->basic_errno <= 0)
      fprintf(stderr, "unknown error");
    fprintf(stderr, "\n");

    final_yield = DELIVER_MUA_FAILED;
    addr_failed = NULL;
    }
  }


else if (!f.dont_deliver)
  retry_update(&addr_defer, &addr_failed, &addr_succeed);


addr_senddsn = NULL;

for (addr_dsntmp = addr_succeed; addr_dsntmp; addr_dsntmp = addr_dsntmp->next)
  {

  DEBUG(D_deliver) debug_printf("DSN: processing router : %s\n"
      "DSN: processing successful delivery address: %s\n"
      "DSN: Sender_address: %s\n"
      "DSN: orcpt: %s  flags: %d\n"
      "DSN: envid: %s  ret: %d\n"
      "DSN: Final recipient: %s\n"
      "DSN: Remote SMTP server supports DSN: %d\n",
      addr_dsntmp->router ? addr_dsntmp->router->name : US"(unknown)",
      addr_dsntmp->address,
      sender_address,
      addr_dsntmp->dsn_orcpt ? addr_dsntmp->dsn_orcpt : US"NULL",
      addr_dsntmp->dsn_flags,
      dsn_envid ? dsn_envid : US"NULL", dsn_ret,
      addr_dsntmp->address,
      addr_dsntmp->dsn_aware
      );


  if (  (  addr_dsntmp->dsn_aware != dsn_support_yes
	|| addr_dsntmp->dsn_flags & rf_dsnlasthop
        )
     && addr_dsntmp->dsn_flags & rf_dsnflags
     && addr_dsntmp->dsn_flags & rf_notify_success
     )
    {

    address_item * addr_next = addr_senddsn;
    addr_senddsn = store_get(sizeof(address_item));
    *addr_senddsn = *addr_dsntmp;
    addr_senddsn->next = addr_next;
    }
  else
    DEBUG(D_deliver) debug_printf("DSN: not sending DSN success message\n");
  }

if (addr_senddsn)
  {
  pid_t pid;
  int fd;


  pid = child_open_exim(&fd);

  DEBUG(D_deliver) debug_printf("DSN: child_open_exim returns: %d\n", pid);

  if (pid < 0)
    {
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Process %d (parent %d) failed to "
      "create child process to send failure message: %s", getpid(),
      getppid(), strerror(errno));

    DEBUG(D_deliver) debug_printf("DSN: child_open_exim failed\n");
    }
  else
    {
    FILE *f = fdopen(fd, "wb");

    uschar * bound;
    transport_ctx tctx = {{0}};

    DEBUG(D_deliver)
      debug_printf("sending error message to: %s\n", sender_address);


    bound = string_sprintf(TIME_T_FMT "-eximdsn-%d", time(NULL), rand());
    DEBUG(D_deliver) debug_printf("DSN: MIME boundary: %s\n", bound);

    if (errors_reply_to)
      fprintf(f, "Reply-To: %s\n", errors_reply_to);

    fprintf(f, "Auto-Submitted: auto-generated\n"
	"From: Mail Delivery System <Mailer-Daemon@%s>\n"
	"To: %s\n"
	"Subject: Delivery Status Notification\n"
	"Content-Type: multipart/report; report-type=delivery-status; boundary=%s\n"
	"MIME-Version: 1.0\n\n"

	"--%s\n"
	"Content-type: text/plain; charset=us-ascii\n\n"

	"This message was created automatically by mail delivery software.\n"
	" ----- The following addresses had successful delivery notifications -----\n",
      qualify_domain_sender, sender_address, bound, bound);

    for (addr_dsntmp = addr_senddsn; addr_dsntmp;
	 addr_dsntmp = addr_dsntmp->next)
      fprintf(f, "<%s> (relayed %s)\n\n",
	addr_dsntmp->address,
	(addr_dsntmp->dsn_flags & rf_dsnlasthop) == 1
	  ? "via non DSN router"
	  : addr_dsntmp->dsn_aware == dsn_support_no
	  ? "to non-DSN-aware mailer"
	  : "via non \"Remote SMTP\" router"
	);

    fprintf(f, "--%s\n"
	"Content-type: message/delivery-status\n\n"
	"Reporting-MTA: dns; %s\n",
      bound, smtp_active_hostname);

    if (dsn_envid)
      {
      uschar *xdec_envid;
      if (auth_xtextdecode(dsn_envid, &xdec_envid) > 0)
        fprintf(f, "Original-Envelope-ID: %s\n", dsn_envid);
      else
        fprintf(f, "X-Original-Envelope-ID: error decoding xtext formatted ENVID\n");
      }
    fputc('\n', f);

    for (addr_dsntmp = addr_senddsn;
	 addr_dsntmp;
	 addr_dsntmp = addr_dsntmp->next)
      {
      if (addr_dsntmp->dsn_orcpt)
        fprintf(f,"Original-Recipient: %s\n", addr_dsntmp->dsn_orcpt);

      fprintf(f, "Action: delivered\n"
	  "Final-Recipient: rfc822;%s\n"
	  "Status: 2.0.0\n",
	addr_dsntmp->address);

      if (addr_dsntmp->host_used && addr_dsntmp->host_used->name)
        fprintf(f, "Remote-MTA: dns; %s\nDiagnostic-Code: smtp; 250 Ok\n\n",
	  addr_dsntmp->host_used->name);
      else
	fprintf(f, "Diagnostic-Code: X-Exim; relayed via non %s router\n\n",
	  (addr_dsntmp->dsn_flags & rf_dsnlasthop) == 1 ? "DSN" : "SMTP");
      }

    fprintf(f, "--%s\nContent-type: text/rfc822-headers\n\n", bound);

    fflush(f);
    transport_filter_argv = NULL;
    return_path = sender_address;


    tctx.u.fd = fileno(f);
    tctx.options = topt_add_return_path | topt_no_body;
    transport_write_message(&tctx, 0);
    fflush(f);

    fprintf(f,"\n--%s--\n", bound);

    fflush(f);
    fclose(f);
    rc = child_close(pid, 0);
    }
  }


while (addr_failed)
  {
  pid_t pid;
  int fd;
  uschar *logtod = tod_stamp(tod_log);
  address_item *addr;
  address_item *handled_addr = NULL;
  address_item **paddr;
  address_item *msgchain = NULL;
  address_item **pmsgchain = &msgchain;


  f.disable_logging = FALSE;
  if (addr_failed->transport)
    f.disable_logging = addr_failed->transport->disable_logging;

  DEBUG(D_deliver)
    debug_printf("processing failed address %s\n", addr_failed->address);


  if (sender_address[0] == 0 && !addr_failed->prop.errors_address)
    {
    if (  !testflag(addr_failed, af_retry_timedout)
       && !addr_failed->prop.ignore_error)
      log_write(0, LOG_MAIN|LOG_PANIC, "internal error: bounce message "
        "failure is neither frozen nor ignored (it's been ignored)");

    addr_failed->prop.ignore_error = TRUE;
    }


  if (  addr_failed->prop.ignore_error
     || (  addr_failed->dsn_flags & rf_dsnflags
        && (addr_failed->dsn_flags & rf_notify_failure) != rf_notify_failure
     )  )
    {
    addr = addr_failed;
    addr_failed = addr->next;
    if (addr->return_filename) Uunlink(addr->return_filename);

    log_write(0, LOG_MAIN, "%s%s%s%s: error ignored",
      addr->address,
      !addr->parent ? US"" : US" <",
      !addr->parent ? US"" : addr->parent->address,
      !addr->parent ? US"" : US">");

    address_done(addr, logtod);
    child_done(addr, logtod);

    (void)spool_write_header(message_id, SW_DELIVERING, NULL);
    }


  else
    {
    if (!(bounce_recipient = addr_failed->prop.errors_address))
      bounce_recipient = sender_address;


    if ((pid = child_open_exim(&fd)) < 0)
      log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Process %d (parent %d) failed to "
        "create child process to send failure message: %s", getpid(),
        getppid(), strerror(errno));


    else
      {
      int ch, rc;
      int filecount = 0;
      int rcount = 0;
      uschar *bcc, *emf_text;
      FILE * fp = fdopen(fd, "wb");
      FILE * emf = NULL;
      BOOL to_sender = strcmpic(sender_address, bounce_recipient) == 0;
      int max = (bounce_return_size_limit/DELIVER_IN_BUFFER_SIZE + 1) *
        DELIVER_IN_BUFFER_SIZE;
      uschar * bound;
      uschar *dsnlimitmsg;
      uschar *dsnnotifyhdr;
      int topt;

      DEBUG(D_deliver)
        debug_printf("sending error message to: %s\n", bounce_recipient);


      paddr = &addr_failed;
      for (addr = addr_failed; addr; addr = *paddr)
        if (Ustrcmp(bounce_recipient, addr->prop.errors_address
	      ? addr->prop.errors_address : sender_address) == 0)
          {
          *paddr = addr->next;
          *pmsgchain = addr;
          addr->next = NULL;
          pmsgchain = &(addr->next);
          }
        else
          paddr = &addr->next;


      for (addr = msgchain; addr; addr = addr->next)
        {
        if (testflag(addr, af_hide_child)) continue;
        if (rcount >= 50)
          {
          fprintf(fp, "\n");
          rcount = 0;
          }
        fprintf(fp, "%s%s",
          rcount++ == 0
	  ? "X-Failed-Recipients: "
	  : ",\n  ",
          testflag(addr, af_pfr) && addr->parent
	  ? string_printing(addr->parent->address)
	  : string_printing(addr->address));
        }
      if (rcount > 0) fprintf(fp, "\n");


      if (errors_reply_to)
        fprintf(fp, "Reply-To: %s\n", errors_reply_to);
      fprintf(fp, "Auto-Submitted: auto-replied\n");
      moan_write_from(fp);
      fprintf(fp, "To: %s\n", bounce_recipient);


      bound = string_sprintf(TIME_T_FMT "-eximdsn-%d", time(NULL), rand());

      fprintf(fp, "Content-Type: multipart/report;"
	    " report-type=delivery-status; boundary=%s\n"
	  "MIME-Version: 1.0\n",
	bound);


      if (bounce_message_file)
        if (!(emf = Ufopen(bounce_message_file, "rb")))
          log_write(0, LOG_MAIN|LOG_PANIC, "Failed to open %s for error "
            "message texts: %s", bounce_message_file, strerror(errno));


      if ((bcc = moan_check_errorcopy(bounce_recipient)))
	fprintf(fp, "Bcc: %s\n", bcc);


      if ((emf_text = next_emf(emf, US"header")))
	fprintf(fp, "%s\n", emf_text);
      else
        fprintf(fp, "Subject: Mail delivery failed%s\n\n",
          to_sender? ": returning message to sender" : "");


      fprintf(fp, "--%s\n"
	  "Content-type: text/plain; charset=us-ascii\n\n",
	bound);

      if ((emf_text = next_emf(emf, US"intro")))
	fprintf(fp, "%s", CS emf_text);
      else
        {
        fprintf(fp,


"This message was created automatically by mail delivery software.\n");

        if (bounce_message_text)
	  fprintf(fp, "%s", CS bounce_message_text);
        if (to_sender)
          fprintf(fp,
"\nA message that you sent could not be delivered to one or more of its\n"
"recipients. This is a permanent error. The following address(es) failed:\n");
        else
          fprintf(fp,
"\nA message sent by\n\n  <%s>\n\n"
"could not be delivered to one or more of its recipients. The following\n"
"address(es) failed:\n", sender_address);
        }
      fputc('\n', fp);


      paddr = &msgchain;
      for (addr = msgchain; addr; addr = *paddr)
        {
        if (print_address_information(addr, fp, US"  ", US"\n    ", US""))
          print_address_error(addr, fp, US"");


        fputc('\n', fp);


        if (addr->return_file >= 0)
          {
          paddr = &(addr->next);
          filecount++;
          }


        else
          {
          *paddr = addr->next;
          addr->next = handled_addr;
          handled_addr = addr;
          }
        }

      fputc('\n', fp);


      emf_text = next_emf(emf, US"generated text");


      if (msgchain)
        {
        address_item *nextaddr;

        if (emf_text)
	  fprintf(fp, "%s", CS emf_text);
	else
          fprintf(fp,
            "The following text was generated during the delivery "
            "attempt%s:\n", (filecount > 1)? "s" : "");

        for (addr = msgchain; addr; addr = nextaddr)
          {
          FILE *fm;
          address_item *topaddr = addr;


	  fputc('\n', fp);
          while(addr)
            {
            print_address_information(addr, fp, US"------ ",  US"\n       ",
              US" ------\n");
            if (addr->return_filename) break;
            addr = addr->next;
            }
	  fputc('\n', fp);


          if (!(fm = Ufopen(addr->return_filename, "rb")))
            fprintf(fp, "    +++ Exim error... failed to open text file: %s\n",
              strerror(errno));
          else
            {
            while ((ch = fgetc(fm)) != EOF) fputc(ch, fp);
            (void)fclose(fm);
            }
          Uunlink(addr->return_filename);


          nextaddr = addr->next;
          addr->next = handled_addr;
          handled_addr = topaddr;
          }
	fputc('\n', fp);
        }


#ifdef SUPPORT_I18N
      if (message_smtputf8)
	fprintf(fp, "--%s\n"
	    "Content-type: message/global-delivery-status\n\n"
	    "Reporting-MTA: dns; %s\n",
	  bound, smtp_active_hostname);
      else
#endif
	fprintf(fp, "--%s\n"
	    "Content-type: message/delivery-status\n\n"
	    "Reporting-MTA: dns; %s\n",
	  bound, smtp_active_hostname);

      if (dsn_envid)
	{

        uschar *xdec_envid;
        if (auth_xtextdecode(dsn_envid, &xdec_envid) > 0)
          fprintf(fp, "Original-Envelope-ID: %s\n", dsn_envid);
        else
          fprintf(fp, "X-Original-Envelope-ID: error decoding xtext formatted ENVID\n");
        }
      fputc('\n', fp);

      for (addr = handled_addr; addr; addr = addr->next)
        {
	host_item * hu;
        fprintf(fp, "Action: failed\n"
	    "Final-Recipient: rfc822;%s\n"
	    "Status: 5.0.0\n",
	    addr->address);
        if ((hu = addr->host_used) && hu->name)
	  {
	  fprintf(fp, "Remote-MTA: dns; %s\n", hu->name);
#ifdef EXPERIMENTAL_DSN_INFO
	  {
	  const uschar * s;
	  if (hu->address)
	    {
	    uschar * p = hu->port == 25
	      ? US"" : string_sprintf(":%d", hu->port);
	    fprintf(fp, "Remote-MTA: X-ip; [%s]%s\n", hu->address, p);
	    }
	  if ((s = addr->smtp_greeting) && *s)
	    fprintf(fp, "X-Remote-MTA-smtp-greeting: X-str; %s\n", s);
	  if ((s = addr->helo_response) && *s)
	    fprintf(fp, "X-Remote-MTA-helo-response: X-str; %s\n", s);
	  if ((s = addr->message) && *s)
	    fprintf(fp, "X-Exim-Diagnostic: X-str; %s\n", s);
	  }
#endif
	  print_dsn_diagnostic_code(addr, fp);
	  }
	fputc('\n', fp);
        }


      emf_text = next_emf(emf, US"copy");


      fprintf(fp, "--%s\n", bound);

      dsnlimitmsg = US"X-Exim-DSN-Information: Due to administrative limits only headers are returned";
      dsnnotifyhdr = NULL;
      topt = topt_add_return_path;


      if (dsn_ret == dsn_ret_hdrs)
        topt |= topt_no_body;
      else
	{
	struct stat statbuf;


        if (!bounce_return_body)
          {
          topt |= topt_no_body;

          if (dsn_ret == dsn_ret_full)
            dsnnotifyhdr = dsnlimitmsg;
          }


	else if (  max_received_linelength > bounce_return_linesize_limit
		|| (  bounce_return_size_limit > 0
		   && fstat(deliver_datafile, &statbuf) == 0
		   && statbuf.st_size > max
		)  )
	  {
	  topt |= topt_no_body;
	  dsnnotifyhdr = dsnlimitmsg;
          }
	}

#ifdef SUPPORT_I18N
      if (message_smtputf8)
	fputs(topt & topt_no_body ? "Content-type: message/global-headers\n\n"
				  : "Content-type: message/global\n\n",
	      fp);
      else
#endif
	fputs(topt & topt_no_body ? "Content-type: text/rfc822-headers\n\n"
				  : "Content-type: message/rfc822\n\n",
	      fp);

      fflush(fp);
      transport_filter_argv = NULL;
      return_path = sender_address;
	{
	transport_ctx tctx = {{0}};
	transport_instance tb = {0};

	tctx.u.fd = fileno(fp);
	tctx.tblock = &tb;
	tctx.options = topt;
	tb.add_headers = dsnnotifyhdr;

	transport_write_message(&tctx, 0);
	}
      fflush(fp);


      if (emf)
        (void)fclose(emf);

      fprintf(fp, "\n--%s--\n", bound);


      (void)fclose(fp);
      rc = child_close(pid, 0);


      if (f.running_in_test_harness) millisleep(500);


      if (rc != 0)
        {
        uschar *s = US"";
        if (now - received_time.tv_sec < retry_maximum_timeout && !addr_defer)
          {
          addr_defer = (address_item *)(+1);
          f.deliver_freeze = TRUE;
          deliver_frozen_at = time(NULL);

          (void)spool_write_header(message_id, SW_DELIVERING, NULL);
          s = US" (frozen)";
          }
        deliver_msglog("Process failed (%d) when writing error message "
          "to %s%s", rc, bounce_recipient, s);
        log_write(0, LOG_MAIN, "Process failed (%d) when writing error message "
          "to %s%s", rc, bounce_recipient, s);
        }


      else
        {
        for (addr = handled_addr; addr; addr = addr->next)
          {
          address_done(addr, logtod);
          child_done(addr, logtod);
          }

        (void)spool_write_header(message_id, SW_DELIVERING, NULL);
        }
      }
    }
  }

f.disable_logging = FALSE;


DELIVERY_TIDYUP:


if (!addr_defer)
  {
  uschar * fname;

  if (message_logs)
    {
    fname = spool_fname(US"msglog", message_subdir, id, US"");
    if (preserve_message_logs)
      {
      int rc;
      uschar * moname = spool_fname(US"msglog.OLD", US"", id, US"");

      if ((rc = Urename(fname, moname)) < 0)
        {
        (void)directory_make(spool_directory,
			      spool_sname(US"msglog.OLD", US""),
			      MSGLOG_DIRECTORY_MODE, TRUE);
        rc = Urename(fname, moname);
        }
      if (rc < 0)
        log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to move %s to the "
          "msglog.OLD directory", fname);
      }
    else
      if (Uunlink(fname) < 0)
        log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to unlink %s: %s",
		  fname, strerror(errno));
    }


  fname = spool_fname(US"input", message_subdir, id, US"-D");
  if (Uunlink(fname) < 0)
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to unlink %s: %s",
      fname, strerror(errno));
  fname = spool_fname(US"input", message_subdir, id, US"-H");
  if (Uunlink(fname) < 0)
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to unlink %s: %s",
      fname, strerror(errno));


  if (LOGGING(queue_time_overall))
    log_write(0, LOG_MAIN, "Completed QT=%s", string_timesince(&received_time));
  else
    log_write(0, LOG_MAIN, "Completed");


  f.deliver_freeze = FALSE;

#ifndef DISABLE_EVENT
  (void) event_raise(event_action, US"msg:complete", NULL);
#endif
  }


else if (addr_defer != (address_item *)(+1))
  {
  address_item *addr;
  uschar *recipients = US"";
  BOOL delivery_attempted = FALSE;

  deliver_domain = testflag(addr_defer, af_pfr)
    ? addr_defer->parent->domain : addr_defer->domain;

  for (addr = addr_defer; addr; addr = addr->next)
    {
    address_item *otaddr;

    if (addr->basic_errno > ERRNO_RETRY_BASE) delivery_attempted = TRUE;

    if (deliver_domain)
      {
      const uschar *d = testflag(addr, af_pfr)
	? addr->parent->domain : addr->domain;


      if (!d || Ustrcmp(d, deliver_domain) != 0)
        deliver_domain = NULL;
      }

    if (addr->return_filename) Uunlink(addr->return_filename);


    for (otaddr = addr; otaddr; otaddr = otaddr->parent)
      if (otaddr->onetime_parent) break;

    if (otaddr)
      {
      int i;
      int t = recipients_count;

      for (i = 0; i < recipients_count; i++)
        {
        uschar *r = recipients_list[i].address;
        if (Ustrcmp(otaddr->onetime_parent, r) == 0) t = i;
        if (Ustrcmp(otaddr->address, r) == 0) break;
        }


      if (  i >= recipients_count && t < recipients_count
         && Ustrcmp(otaddr->address, otaddr->parent->address) != 0)
        {
        DEBUG(D_deliver) debug_printf("one_time: adding %s in place of %s\n",
          otaddr->address, otaddr->parent->address);
        receive_add_recipient(otaddr->address, t);
        recipients_list[recipients_count-1].errors_to = otaddr->prop.errors_address;
        tree_add_nonrecipient(otaddr->parent->address);
        update_spool = TRUE;
        }
      }


    if (sender_address[0])
      {
      uschar * s = addr->prop.errors_address;
      if (!s) s = sender_address;
      if (Ustrstr(recipients, s) == NULL)
	recipients = string_sprintf("%s%s%s", recipients,
	  recipients[0] ? "," : "", s);
      }
    }


  if (  !f.queue_2stage
     && delivery_attempted
     && (  ((addr_defer->dsn_flags & rf_dsnflags) == 0)
        || (addr_defer->dsn_flags & rf_notify_delay) == rf_notify_delay
	)
     && delay_warning[1] > 0
     && sender_address[0] != 0
     && (  !delay_warning_condition
        || expand_check_condition(delay_warning_condition,
            US"delay_warning", US"option")
	)
     )
    {
    int count;
    int show_time;
    int queue_time = time(NULL) - received_time.tv_sec;


    if (f.running_in_test_harness && fudged_queue_times[0] != 0)
      {
      int qt = readconf_readtime(fudged_queue_times, '/', FALSE);
      if (qt >= 0)
        {
        DEBUG(D_deliver) debug_printf("fudged queue_times = %s\n",
          fudged_queue_times);
        queue_time = qt;
        }
      }


    for (count = 0; count < delay_warning[1]; count++)
      if (queue_time < delay_warning[count+2]) break;

    show_time = delay_warning[count+1];

    if (count >= delay_warning[1])
      {
      int extra;
      int last_gap = show_time;
      if (count > 1) last_gap -= delay_warning[count];
      extra = (queue_time - delay_warning[count+1])/last_gap;
      show_time += last_gap * extra;
      count += extra;
      }

    DEBUG(D_deliver)
      {
      debug_printf("time on queue = %s\n", readconf_printtime(queue_time));
      debug_printf("warning counts: required %d done %d\n", count,
        warning_count);
      }


    if (warning_count < count)
      {
      header_line *h;
      int fd;
      pid_t pid = child_open_exim(&fd);

      if (pid > 0)
        {
        uschar *wmf_text;
        FILE *wmf = NULL;
        FILE *f = fdopen(fd, "wb");
	uschar * bound;
	transport_ctx tctx = {{0}};

        if (warn_message_file)
          if (!(wmf = Ufopen(warn_message_file, "rb")))
            log_write(0, LOG_MAIN|LOG_PANIC, "Failed to open %s for warning "
              "message texts: %s", warn_message_file, strerror(errno));

        warnmsg_recipients = recipients;
        warnmsg_delay = queue_time < 120*60
	  ? string_sprintf("%d minutes", show_time/60)
	  : string_sprintf("%d hours", show_time/3600);

        if (errors_reply_to)
          fprintf(f, "Reply-To: %s\n", errors_reply_to);
        fprintf(f, "Auto-Submitted: auto-replied\n");
        moan_write_from(f);
        fprintf(f, "To: %s\n", recipients);


        bound = string_sprintf(TIME_T_FMT "-eximdsn-%d", time(NULL), rand());

        fprintf(f, "Content-Type: multipart/report;"
	    " report-type=delivery-status; boundary=%s\n"
	    "MIME-Version: 1.0\n",
	  bound);

        if ((wmf_text = next_emf(wmf, US"header")))
          fprintf(f, "%s\n", wmf_text);
        else
          fprintf(f, "Subject: Warning: message %s delayed %s\n\n",
            message_id, warnmsg_delay);


        fprintf(f, "--%s\n"
	    "Content-type: text/plain; charset=us-ascii\n\n",
	  bound);

        if ((wmf_text = next_emf(wmf, US"intro")))
	  fprintf(f, "%s", CS wmf_text);
	else
          {
          fprintf(f,
"This message was created automatically by mail delivery software.\n");

          if (Ustrcmp(recipients, sender_address) == 0)
            fprintf(f,
"A message that you sent has not yet been delivered to one or more of its\n"
"recipients after more than ");

          else
	    fprintf(f,
"A message sent by\n\n  <%s>\n\n"
"has not yet been delivered to one or more of its recipients after more than \n",
	      sender_address);

          fprintf(f, "%s on the queue on %s.\n\n"
	      "The message identifier is:     %s\n",
	    warnmsg_delay, primary_hostname, message_id);

          for (h = header_list; h; h = h->next)
            if (strncmpic(h->text, US"Subject:", 8) == 0)
              fprintf(f, "The subject of the message is: %s", h->text + 9);
            else if (strncmpic(h->text, US"Date:", 5) == 0)
              fprintf(f, "The date of the message is:    %s", h->text + 6);
          fputc('\n', f);

          fprintf(f, "The address%s to which the message has not yet been "
            "delivered %s:\n",
            !addr_defer->next ? "" : "es",
            !addr_defer->next ? "is": "are");
          }


        address_item *addr_dsndefer = addr_defer;
        fputc('\n', f);
        while (addr_defer)
          {
          address_item *addr = addr_defer;
          addr_defer = addr->next;
          if (print_address_information(addr, f, US"  ", US"\n    ", US""))
            print_address_error(addr, f, US"Delay reason: ");
          fputc('\n', f);
          }
        fputc('\n', f);


        if (wmf)
          {
          if ((wmf_text = next_emf(wmf, US"final")))
	    fprintf(f, "%s", CS wmf_text);
          (void)fclose(wmf);
          }
        else
          {
          fprintf(f,
"No action is required on your part. Delivery attempts will continue for\n"
"some time, and this warning may be repeated at intervals if the message\n"
"remains undelivered. Eventually the mail delivery software will give up,\n"
"and when that happens, the message will be returned to you.\n");
          }


        fprintf(f, "\n--%s\n"
	    "Content-type: message/delivery-status\n\n"
	    "Reporting-MTA: dns; %s\n",
	  bound,
	  smtp_active_hostname);


        if (dsn_envid)
	  {

          uschar *xdec_envid;
          if (auth_xtextdecode(dsn_envid, &xdec_envid) > 0)
            fprintf(f,"Original-Envelope-ID: %s\n", dsn_envid);
          else
            fprintf(f,"X-Original-Envelope-ID: error decoding xtext formatted ENVID\n");
          }
        fputc('\n', f);

        for ( ; addr_dsndefer; addr_dsndefer = addr_dsndefer->next)
          {
          if (addr_dsndefer->dsn_orcpt)
            fprintf(f, "Original-Recipient: %s\n", addr_dsndefer->dsn_orcpt);

          fprintf(f, "Action: delayed\n"
	      "Final-Recipient: rfc822;%s\n"
	      "Status: 4.0.0\n",
	    addr_dsndefer->address);
          if (addr_dsndefer->host_used && addr_dsndefer->host_used->name)
            {
            fprintf(f, "Remote-MTA: dns; %s\n",
		    addr_dsndefer->host_used->name);
            print_dsn_diagnostic_code(addr_dsndefer, f);
            }
	  fputc('\n', f);
          }

        fprintf(f, "--%s\n"
	    "Content-type: text/rfc822-headers\n\n",
	  bound);

        fflush(f);

	tctx.u.fd = fileno(f);
        tctx.options = topt_add_return_path | topt_no_body;
        transport_filter_argv = NULL;
        return_path = sender_address;


        transport_write_message(&tctx, 0);
        fflush(f);

        fprintf(f,"\n--%s--\n", bound);

        fflush(f);


        (void)fclose(f);
        if (child_close(pid, 0) == 0)
          {
          warning_count = count;
          update_spool = TRUE;
          }
        }
      }
    }


  deliver_domain = NULL;


  if (f.deliver_firsttime)
    {
    f.deliver_firsttime = FALSE;
    update_spool = TRUE;
    }


  if (f.deliver_freeze)
    {
    if (freeze_tell && freeze_tell[0] != 0 && !f.local_error_message)
      {
      uschar *s = string_copy(frozen_info);
      uschar *ss = Ustrstr(s, " by the system filter: ");

      if (ss != NULL)
        {
        ss[21] = '.';
        ss[22] = '\n';
        }

      ss = s;
      while (*ss != 0)
        {
        if (*ss == '\\' && ss[1] == 'n')
          {
          *ss++ = ' ';
          *ss++ = '\n';
          }
        else ss++;
        }
      moan_tell_someone(freeze_tell, addr_defer, US"Message frozen",
        "Message %s has been frozen%s.\nThe sender is <%s>.\n", message_id,
        s, sender_address);
      }


    deliver_msglog("*** Frozen%s\n", frozen_info);
    log_write(0, LOG_MAIN, "Frozen%s", frozen_info);
    }


  DEBUG(D_deliver)
    debug_printf("delivery deferred: update_spool=%d header_rewritten=%d\n",
      update_spool, f.header_rewritten);

  if (update_spool || f.header_rewritten)

    (void)spool_write_header(message_id, SW_DELIVERING, NULL);
  }


if (message_logs) (void)fclose(message_log);


if (journal_fd >= 0) (void)close(journal_fd);

if (remove_journal)
  {
  uschar * fname = spool_fname(US"input", message_subdir, id, US"-J");

  if (Uunlink(fname) < 0 && errno != ENOENT)
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to unlink %s: %s", fname,
      strerror(errno));


#ifdef SUPPORT_MOVE_FROZEN_MESSAGES
  if (f.deliver_freeze && move_frozen_messages)
    (void)spool_move_message(id, message_subdir, US"", US"F");
#endif
  }


(void)close(deliver_datafile);
deliver_datafile = -1;
DEBUG(D_deliver) debug_printf("end delivery of %s\n", id);


search_tidyup();
acl_where = ACL_WHERE_UNKNOWN;
return final_yield;
}
