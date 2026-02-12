receive_msg(BOOL extract_recip)
{
int  i;
int  rc = FAIL;
int  msg_size = 0;
int  process_info_len = Ustrlen(process_info);
int  error_rc = (error_handling == ERRORS_SENDER)?
       errors_sender_rc : EXIT_FAILURE;
int  header_size = 256;
int  start, end, domain;
int  id_resolution;
int  had_zero = 0;
int  prevlines_length = 0;

register int ptr = 0;

BOOL contains_resent_headers = FALSE;
BOOL extracted_ignored = FALSE;
BOOL first_line_ended_crlf = TRUE_UNSET;
BOOL smtp_yield = TRUE;
BOOL yield = FALSE;

BOOL resents_exist = FALSE;
uschar *resent_prefix = US"";
uschar *blackholed_by = NULL;
uschar *blackhole_log_msg = US"";
enum {NOT_TRIED, TMP_REJ, PERM_REJ, ACCEPTED} cutthrough_done = NOT_TRIED;

flock_t lock_data;
error_block *bad_addresses = NULL;

uschar *frozen_by = NULL;
uschar *queued_by = NULL;

uschar *errmsg;
gstring * g;
struct stat statbuf;


uschar *smtp_reply = NULL;
uschar *user_msg, *log_msg;


header_line *h, *next;


BOOL date_header_exists = FALSE;


header_line *from_header = NULL;
header_line *subject_header = NULL;
header_line *msgid_header = NULL;
header_line *received_header;

#ifdef EXPERIMENTAL_DMARC
int dmarc_up = 0;
#endif


uschar *timestamp;
int tslen;


search_tidyup();


if (extract_recip || !smtp_input)
  cancel_cutthrough_connection(TRUE, US"not smtp input");


received_header = header_list = header_last = store_get(sizeof(header_line));
header_list->next = NULL;
header_list->type = htype_old;
header_list->text = NULL;
header_list->slen = 0;


next = store_get(sizeof(header_line));
next->text = store_get(header_size);


message_id[0] = 0;
data_file = NULL;
data_fd = -1;
spool_name = US"";
message_size = 0;
warning_count = 0;
received_count = 1;

if (thismessage_size_limit <= 0) thismessage_size_limit = INT_MAX;


message_linecount = body_linecount = body_zerocount =
  max_received_linelength = 0;

#ifndef DISABLE_DKIM


if (smtp_input && !smtp_batched_input && !dkim_disable_verify)
  dkim_exim_verify_init(chunking_state <= CHUNKING_OFFERED);
#endif

#ifdef EXPERIMENTAL_DMARC

dmarc_up = dmarc_init();
#endif


(void)gettimeofday(&message_id_tv, NULL);


received_time = message_id_tv;


if (smtp_input) os_non_restarting_signal(SIGALRM, data_timeout_handler);


else if (receive_timeout > 0)
  {
  os_non_restarting_signal(SIGALRM, data_timeout_handler);
  alarm(receive_timeout);
  }


signal(SIGTERM, data_sigterm_sigint_handler);
signal(SIGINT, data_sigterm_sigint_handler);


for (;;)
  {
  int ch = (receive_getc)(GETC_BUFFER_UNLIMITED);


  if (ch == EOF && smtp_input )
    {
    smtp_reply = handle_lost_connection(US" (header)");
    smtp_yield = FALSE;
    goto TIDYUP;
    }


  if (ptr >= header_size - 4)
    {
    int oldsize = header_size;

    header_size *= 2;
    if (!store_extend(next->text, oldsize, header_size))
      {
      BOOL release_ok = store_last_get[store_pool] == next->text;
      uschar *newtext = store_get(header_size);
      memcpy(newtext, next->text, ptr);
      if (release_ok) store_release(next->text);
      next->text = newtext;
      }
    }


  if (ch == 0) had_zero++;


  if (ch == EOF) goto EOL;


  if (ch == '\n')
    {
    if (first_line_ended_crlf == TRUE_UNSET) first_line_ended_crlf = FALSE;
      else if (first_line_ended_crlf) receive_ungetc(' ');
    goto EOL;
    }


  if (ptr == 0 && ch == '.' && (smtp_input || dot_ends))
    {
    ch = (receive_getc)(GETC_BUFFER_UNLIMITED);
    if (ch == '\r')
      {
      ch = (receive_getc)(GETC_BUFFER_UNLIMITED);
      if (ch != '\n')
        {
        receive_ungetc(ch);
        ch = '\r';
        }
      }
    if (ch == '\n')
      {
      message_ended = END_DOT;
      store_reset(next);
      next = NULL;
      break;
      }


    if (!smtp_input)
      {
      next->text[ptr++] = '.';
      message_size++;
      }
    }


  if (ch == '\r')
    {
    ch = (receive_getc)(GETC_BUFFER_UNLIMITED);
    if (ch == '\n')
      {
      if (first_line_ended_crlf == TRUE_UNSET) first_line_ended_crlf = TRUE;
      goto EOL;
      }


    ch = (receive_ungetc)(ch);
    next->text[ptr++] = '\n';
    message_size++;
    ch = ' ';
    }


  next->text[ptr++] = ch;
  message_size++;


  if (message_size >= header_maxsize)
    {
    next->text[ptr] = 0;
    next->slen = ptr;
    next->type = htype_other;
    next->next = NULL;
    header_last->next = next;
    header_last = next;

    log_write(0, LOG_MAIN, "ridiculously long message header received from "
      "%s (more than %d characters): message abandoned",
      sender_host_unknown? sender_ident : sender_fullhost, header_maxsize);

    if (smtp_input)
      {
      smtp_reply = US"552 Message header is ridiculously long";
      receive_swallow_smtp();
      goto TIDYUP;
      }

    else
      {
      give_local_error(ERRMESS_VLONGHEADER,
        string_sprintf("message header longer than %d characters received: "
         "message not accepted", header_maxsize), US"", error_rc, stdin,
           header_list->next);

      }
    }

  continue;


  EOL:


  receive_linecount++;
  message_linecount++;


  if (ptr - prevlines_length > max_received_linelength)
    max_received_linelength = ptr - prevlines_length;
  prevlines_length = ptr + 1;


  next->text[ptr++] = '\n';
  message_size++;


  if (ptr == 1)
    {
    store_reset(next);
    next = NULL;
    break;
    }


  if (ch != EOF)
    {
    int nextch = (receive_getc)(GETC_BUFFER_UNLIMITED);
    if (nextch == ' ' || nextch == '\t')
      {
      next->text[ptr++] = nextch;
      message_size++;
      continue;
      }
    else if (nextch != EOF) (receive_ungetc)(nextch);
    else ch = EOF;
    }


  next->text[ptr] = 0;
  next->slen = ptr;
  store_reset(next->text + ptr + 1);


  if (message_size > thismessage_size_limit) break;


  if (header_last == header_list &&
       (!smtp_input
         ||
         (sender_host_address != NULL &&
           verify_check_host(&ignore_fromline_hosts) == OK)
         ||
         (sender_host_address == NULL && ignore_fromline_local)
       ) &&
       regex_match_and_setup(regex_From, next->text, 0, -1))
    {
    if (!sender_address_forced)
      {
      uschar *uucp_sender = expand_string(uucp_from_sender);
      if (uucp_sender == NULL)
        {
        log_write(0, LOG_MAIN|LOG_PANIC,
          "expansion of \"%s\" failed after matching "
          "\"From \" line: %s", uucp_from_sender, expand_string_message);
        }
      else
        {
        int start, end, domain;
        uschar *errmess;
        uschar *newsender = parse_extract_address(uucp_sender, &errmess,
          &start, &end, &domain, TRUE);
        if (newsender != NULL)
          {
          if (domain == 0 && newsender[0] != 0)
            newsender = rewrite_address_qualify(newsender, FALSE);

          if (filter_test != FTEST_NONE || receive_check_set_sender(newsender))
            {
            sender_address = newsender;

            if (trusted_caller || filter_test != FTEST_NONE)
              {
              authenticated_sender = NULL;
              originator_name = US"";
              sender_local = FALSE;
              }

            if (filter_test != FTEST_NONE)
              printf("Sender taken from \"From \" line\n");
            }
          }
        }
      }
    }


  else
    {
    uschar *p = next->text;


    if (isspace(*p)) break;
    while (mac_isgraph(*p) && *p != ':') p++;
    while (isspace(*p)) p++;
    if (*p != ':')
      {
      body_zerocount = had_zero;
      break;
      }


    if (had_zero > 0)
      for (p = next->text; p < next->text + ptr; p++) if (*p == 0) *p = '?';


    p = next->text + ptr - 2;
    for (;;)
      {
      while (*p == ' ' || *p == '\t') p--;
      if (*p != '\n') break;
      ptr = (p--) - next->text + 1;
      message_size -= next->slen - ptr;
      next->text[ptr] = 0;
      next->slen = ptr;
      }


    next->type = htype_other;
    next->next = NULL;
    header_last->next = next;
    header_last = next;


    if (header_line_maxsize > 0 && next->slen > header_line_maxsize)
      {
      log_write(0, LOG_MAIN, "overlong message header line received from "
        "%s (more than %d characters): message abandoned",
        sender_host_unknown? sender_ident : sender_fullhost,
        header_line_maxsize);

      if (smtp_input)
        {
        smtp_reply = US"552 A message header line is too long";
        receive_swallow_smtp();
        goto TIDYUP;
        }

      else
        {
        give_local_error(ERRMESS_VLONGHDRLINE,
          string_sprintf("message header line longer than %d characters "
           "received: message not accepted", header_line_maxsize), US"",
           error_rc, stdin, header_list->next);

        }
      }


    if (!resents_exist && strncmpic(next->text, US"resent-", 7) == 0)
      {
      resents_exist = TRUE;
      resent_prefix = US"Resent-";
      }
    }


  if (!first_line_ended_crlf && chunking_state > CHUNKING_OFFERED)
    {
    log_write(L_size_reject, LOG_MAIN|LOG_REJECT, "rejected from <%s>%s%s%s%s: "
      "Non-CRLF-terminated header, under CHUNKING: message abandoned",
      sender_address,
      sender_fullhost ? " H=" : "", sender_fullhost ? sender_fullhost : US"",
      sender_ident ? " U=" : "",    sender_ident ? sender_ident : US"");
    smtp_printf("552 Message header not CRLF terminated\r\n", FALSE);
    bdat_flush_data();
    smtp_reply = US"";
    goto TIDYUP;
    }


  if (ch == EOF) { next = NULL; break; }


  header_size = 256;
  next = store_get(sizeof(header_line));
  next->text = store_get(header_size);
  ptr = 0;
  had_zero = 0;
  prevlines_length = 0;
  }


DEBUG(D_receive)
  {
  debug_printf(">>Headers received:\n");
  for (h = header_list->next; h; h = h->next)
    debug_printf("%s", h->text);
  debug_printf("\n");
  }


if (smtp_input && (receive_feof)())
  {
  smtp_reply = handle_lost_connection(US" (after header)");
  smtp_yield = FALSE;
  goto TIDYUP;
  }


if (filter_test != FTEST_NONE && header_list->next == NULL)
  printf("Warning: no message headers read\n");


for (h = header_list->next; h; h = h->next)
  {
  BOOL is_resent = strncmpic(h->text, US"resent-", 7) == 0;
  if (is_resent) contains_resent_headers = TRUE;

  switch (header_checkname(h, is_resent))
    {
    case htype_bcc:
    h->type = htype_bcc;
    break;

    case htype_cc:
    h->type = htype_cc;
    break;


    case htype_date:
    if (!resents_exist || is_resent) date_header_exists = TRUE;
    break;


    case htype_delivery_date:
    if (delivery_date_remove) h->type = htype_old;
    break;


    case htype_envelope_to:
    if (envelope_to_remove) h->type = htype_old;
    break;


    case htype_from:
    h->type = htype_from;
    if (!resents_exist || is_resent)
      {
      from_header = h;
      if (!smtp_input)
        {
        int len;
        uschar *s = Ustrchr(h->text, ':') + 1;
        while (isspace(*s)) s++;
        len = h->slen - (s - h->text) - 1;
        if (Ustrlen(originator_login) == len &&
	    strncmpic(s, originator_login, len) == 0)
          {
          uschar *name = is_resent? US"Resent-From" : US"From";
          header_add(htype_from, "%s: %s <%s@%s>\n", name, originator_name,
            originator_login, qualify_domain_sender);
          from_header = header_last;
          h->type = htype_old;
          DEBUG(D_receive|D_rewrite)
            debug_printf("rewrote \"%s:\" header using gecos\n", name);
         }
        }
      }
    break;


    case htype_id:
    if (msgid_header == NULL && (!resents_exist || is_resent))
      {
      msgid_header = h;
      h->type = htype_id;
      }
    break;


    case htype_received:
    h->type = htype_received;
    received_count++;
    break;


    case htype_reply_to:
    h->type = htype_reply_to;
    break;


    case htype_return_path:
    if (return_path_remove) h->type = htype_old;


    if (filter_test != FTEST_NONE)
      {
      uschar *start = h->text + 12;
      uschar *end = start + Ustrlen(start);
      while (isspace(*start)) start++;
      while (end > start && isspace(end[-1])) end--;
      if (*start == '<' && end[-1] == '>')
        {
        start++;
        end--;
        }
      return_path = string_copyn(start, end - start);
      printf("Return-path taken from \"Return-path:\" header line\n");
      }
    break;


    case htype_sender:
    h->type = ((!active_local_sender_retain &&
                (
                (sender_local && !trusted_caller && !suppress_local_fixups)
                  || submission_mode
                )
               ) &&
               (!resents_exist||is_resent))?
      htype_old : htype_sender;
    break;


    case htype_subject:
    subject_header = h;
    break;


    case htype_to:
    h->type = htype_to;


    break;
    }
  }


if (extract_recip)
  {
  int rcount = 0;
  error_block **bnext = &bad_addresses;

  if (extract_addresses_remove_arguments)
    {
    while (recipients_count-- > 0)
      {
      uschar *s = rewrite_address(recipients_list[recipients_count].address,
        TRUE, TRUE, global_rewrite_rules, rewrite_existflags);
      tree_add_nonrecipient(s);
      }
    recipients_list = NULL;
    recipients_count = recipients_list_max = 0;
    }


  for (h = header_list->next; h; h = h->next)
    {
    if ((h->type == htype_to || h->type == htype_cc || h->type == htype_bcc) &&
        (!contains_resent_headers || strncmpic(h->text, US"resent-", 7) == 0))
      {
      uschar *s = Ustrchr(h->text, ':') + 1;
      while (isspace(*s)) s++;

      parse_allow_group = TRUE;

      while (*s != 0)
        {
        uschar *ss = parse_find_address_end(s, FALSE);
        uschar *recipient, *errmess, *p, *pp;
        int start, end, domain;


        if (recipients_max > 0 && ++rcount > recipients_max)
          {
          give_local_error(ERRMESS_TOOMANYRECIP, US"too many recipients",
            US"message rejected: ", error_rc, stdin, NULL);

          }


        pp = recipient = store_get(ss - s + 1);
        for (p = s; p < ss; p++) if (*p != '\n') *pp++ = *p;
        *pp = 0;

#ifdef SUPPORT_I18N
	{
	BOOL b = allow_utf8_domains;
	allow_utf8_domains = TRUE;
#endif
        recipient = parse_extract_address(recipient, &errmess, &start, &end,
          &domain, FALSE);

#ifdef SUPPORT_I18N
	if (string_is_utf8(recipient))
	  message_smtputf8 = TRUE;
	else
	  allow_utf8_domains = b;
	}
#endif


        if (recipient == NULL && Ustrcmp(errmess, "empty address") != 0)
          {
          int len = Ustrlen(s);
          error_block *b = store_get(sizeof(error_block));
          while (len > 0 && isspace(s[len-1])) len--;
          b->next = NULL;
          b->text1 = string_printing(string_copyn(s, len));
          b->text2 = errmess;
          *bnext = b;
          bnext = &(b->next);
          }


        else if (recipient != NULL)
          {
          if (tree_search(tree_nonrecipients, recipient) == NULL)
            receive_add_recipient(recipient, -1);
          else
            extracted_ignored = TRUE;
          }


        s = ss + (*ss? 1:0);
        while (isspace(*s)) s++;
        }

      parse_allow_group = FALSE;
      parse_found_group = FALSE;


      if (h->type == htype_bcc) h->type = htype_old;
      }
    }

  }


Ustrncpy(message_id, string_base62((long int)(message_id_tv.tv_sec)), 6);
message_id[6] = '-';
Ustrncpy(message_id + 7, string_base62((long int)getpid()), 6);


if (host_number_string != NULL)
  {
  id_resolution = (BASE_62 == 62)? 5000 : 10000;
  sprintf(CS(message_id + MESSAGE_ID_LENGTH - 3), "-%2s",
    string_base62((long int)(
      host_number * (1000000/id_resolution) +
        message_id_tv.tv_usec/id_resolution)) + 4);
  }


else
  {
  id_resolution = (BASE_62 == 62)? 500 : 1000;
  sprintf(CS(message_id + MESSAGE_ID_LENGTH - 3), "-%2s",
    string_base62((long int)(message_id_tv.tv_usec/id_resolution)) + 4);
  }


(void)string_format(process_info + process_info_len,
  PROCESS_INFO_SIZE - process_info_len, " id=%s", message_id);


message_subdir[0] = split_spool_directory ? message_id[5] : 0;


if (msgid_header == NULL &&
      ((sender_host_address == NULL && !suppress_local_fixups)
        || submission_mode))
  {
  uschar *p;
  uschar *id_text = US"";
  uschar *id_domain = primary_hostname;


  if (message_id_domain != NULL)
    {
    uschar *new_id_domain = expand_string(message_id_domain);
    if (new_id_domain == NULL)
      {
      if (!expand_string_forcedfail)
        log_write(0, LOG_MAIN|LOG_PANIC,
          "expansion of \"%s\" (message_id_header_domain) "
          "failed: %s", message_id_domain, expand_string_message);
      }
    else if (*new_id_domain != 0)
      {
      id_domain = new_id_domain;
      for (p = id_domain; *p != 0; p++)
        if (!isalnum(*p) && *p != '.') *p = '-';
      }
    }


  if (message_id_text != NULL)
    {
    uschar *new_id_text = expand_string(message_id_text);
    if (new_id_text == NULL)
      {
      if (!expand_string_forcedfail)
        log_write(0, LOG_MAIN|LOG_PANIC,
          "expansion of \"%s\" (message_id_header_text) "
          "failed: %s", message_id_text, expand_string_message);
      }
    else if (*new_id_text != 0)
      {
      id_text = new_id_text;
      for (p = id_text; *p != 0; p++)
        if (mac_iscntrl_or_special(*p)) *p = '-';
      }
    }


  header_add_at_position(!resents_exist, NULL, FALSE, htype_id,
    "%sMessage-Id: <%s%s%s@%s>\n", resent_prefix, message_id_external,
    (*id_text == 0)? "" : ".", id_text, id_domain);
  }


if (LOGGING(received_recipients))
  {
  raw_recipients = store_get(recipients_count * sizeof(uschar *));
  for (i = 0; i < recipients_count; i++)
    raw_recipients[i] = string_copy(recipients_list[i].address);
  raw_recipients_count = recipients_count;
  }


for (i = 0; i < recipients_count; i++)
  recipients_list[i].address =
    rewrite_address(recipients_list[i].address, TRUE, TRUE,
      global_rewrite_rules, rewrite_existflags);


if (from_header == NULL &&
    ((sender_host_address == NULL && !suppress_local_fixups)
      || submission_mode))
  {
  uschar *oname = US"";


  if (sender_host_address == NULL)
    {
    if (!trusted_caller || sender_name_forced ||
         (!smtp_input && !sender_address_forced))
      oname = originator_name;
    }


  else
    {
    if (submission_name != NULL) oname = submission_name;
    }


  if (sender_address[0] == 0)
    {
    uschar *fromstart, *fromend;

    fromstart = string_sprintf("%sFrom: %s%s", resent_prefix,
      oname, (oname[0] == 0)? "" : " <");
    fromend = (oname[0] == 0)? US"" : US">";

    if (sender_local || local_error_message)
      {
      header_add(htype_from, "%s%s@%s%s\n", fromstart,
        local_part_quote(originator_login), qualify_domain_sender,
        fromend);
      }
    else if (submission_mode && authenticated_id != NULL)
      {
      if (submission_domain == NULL)
        {
        header_add(htype_from, "%s%s@%s%s\n", fromstart,
          local_part_quote(authenticated_id), qualify_domain_sender,
          fromend);
        }
      else if (submission_domain[0] == 0)
        {
        header_add(htype_from, "%s%s%s\n", fromstart, authenticated_id,
          fromend);
        }
      else
        {
        header_add(htype_from, "%s%s@%s%s\n", fromstart,
          local_part_quote(authenticated_id), submission_domain,
          fromend);
        }
      from_header = header_last;
      }
    }


  else
    {
    header_add(htype_from, "%sFrom: %s%s%s%s\n", resent_prefix,
      oname,
      (oname[0] == 0)? "" : " <",
      (sender_address_unrewritten == NULL)?
        sender_address : sender_address_unrewritten,
      (oname[0] == 0)? "" : ">");

    from_header = header_last;
    }
  }


if (from_header != NULL &&
     (active_local_from_check &&
       ((sender_local && !trusted_caller && !suppress_local_fixups) ||
        (submission_mode && authenticated_id != NULL))
     ))
  {
  BOOL make_sender = TRUE;
  int start, end, domain;
  uschar *errmess;
  uschar *from_address =
    parse_extract_address(Ustrchr(from_header->text, ':') + 1, &errmess,
      &start, &end, &domain, FALSE);
  uschar *generated_sender_address;

  if (submission_mode)
    {
    if (submission_domain == NULL)
      {
      generated_sender_address = string_sprintf("%s@%s",
        local_part_quote(authenticated_id), qualify_domain_sender);
      }
    else if (submission_domain[0] == 0)
      {
      generated_sender_address = string_sprintf("%s",
        authenticated_id);
      }
    else
      {
      generated_sender_address = string_sprintf("%s@%s",
        local_part_quote(authenticated_id), submission_domain);
      }
    }
  else
    generated_sender_address = string_sprintf("%s@%s",
      local_part_quote(originator_login), qualify_domain_sender);


  if (from_address != NULL)
    {
    int slen;
    uschar *at = (domain == 0)? NULL : from_address + domain - 1;

    if (at != NULL) *at = 0;
    from_address += route_check_prefix(from_address, local_from_prefix);
    slen = route_check_suffix(from_address, local_from_suffix);
    if (slen > 0)
      {
      memmove(from_address+slen, from_address, Ustrlen(from_address)-slen);
      from_address += slen;
      }
    if (at != NULL) *at = '@';

    if (strcmpic(generated_sender_address, from_address) == 0 ||
      (domain == 0 && strcmpic(from_address, originator_login) == 0))
        make_sender = FALSE;
    }


  if (make_sender)
    {
    if (submission_mode && submission_name == NULL)
      header_add(htype_sender, "%sSender: %s\n", resent_prefix,
        generated_sender_address);
    else
      header_add(htype_sender, "%sSender: %s <%s>\n",
        resent_prefix,
        submission_mode? submission_name : originator_name,
        generated_sender_address);
    }


  if (submission_mode && sender_address[0] != 0)
    {
    if (sender_address_unrewritten == NULL)
      sender_address_unrewritten = sender_address;
    sender_address = generated_sender_address;
    if (Ustrcmp(sender_address_unrewritten, generated_sender_address) != 0)
      log_write(L_address_rewrite, LOG_MAIN,
        "\"%s\" from env-from rewritten as \"%s\" by submission mode",
        sender_address_unrewritten, generated_sender_address);
    }
  }


if (global_rewrite_rules != NULL && sender_address_unrewritten == NULL &&
    sender_address[0] != 0)
  {
  sender_address = rewrite_address(sender_address, FALSE, TRUE,
    global_rewrite_rules, rewrite_existflags);
  DEBUG(D_receive|D_rewrite)
    debug_printf("rewritten sender = %s\n", sender_address);
  }


for (h = header_list->next; h; h = h->next)
  {
  header_line *newh = rewrite_header(h, NULL, NULL, global_rewrite_rules,
    rewrite_existflags, TRUE);
  if (newh) h = newh;
  }


if (!date_header_exists &&
      ((sender_host_address == NULL && !suppress_local_fixups)
        || submission_mode))
  header_add_at_position(!resents_exist, NULL, FALSE, htype_other,
    "%sDate: %s\n", resent_prefix, tod_stamp(tod_full));

search_tidyup();


DEBUG(D_receive)
  {
  debug_printf(">>Headers after rewriting and local additions:\n");
  for (h = header_list->next; h != NULL; h = h->next)
    debug_printf("%c %s", h->type, h->text);
  debug_printf("\n");
  }


if (filter_test != FTEST_NONE)
  {
  process_info[process_info_len] = 0;
  return message_ended == END_DOT;
  }


if (chunking_state > CHUNKING_OFFERED)
  cancel_cutthrough_connection(FALSE, US"chunking active");


if (cutthrough.fd >= 0 && cutthrough.delivery)
  {
  if (received_count > received_headers_max)
    {
    cancel_cutthrough_connection(TRUE, US"too many headers");
    if (smtp_input) receive_swallow_smtp();
    log_write(0, LOG_MAIN|LOG_REJECT, "rejected from <%s>%s%s%s%s: "
      "Too many \"Received\" headers",
      sender_address,
      sender_fullhost ? "H=" : "", sender_fullhost ? sender_fullhost : US"",
      sender_ident ? "U=" : "", sender_ident ? sender_ident : US"");
    message_id[0] = 0;
    smtp_reply = US"550 Too many \"Received\" headers - suspected mail loop";
    goto TIDYUP;
    }
  received_header_gen();
  add_acl_headers(ACL_WHERE_RCPT, US"MAIL or RCPT");
  (void) cutthrough_headers_send();
  }


spool_name = spool_fname(US"input", message_subdir, message_id, US"-D");
DEBUG(D_receive) debug_printf("Data file name: %s\n", spool_name);

if ((data_fd = Uopen(spool_name, O_RDWR|O_CREAT|O_EXCL, SPOOL_MODE)) < 0)
  {
  if (errno == ENOENT)
    {
    (void) directory_make(spool_directory,
		        spool_sname(US"input", message_subdir),
			INPUT_DIRECTORY_MODE, TRUE);
    data_fd = Uopen(spool_name, O_RDWR|O_CREAT|O_EXCL, SPOOL_MODE);
    }
  if (data_fd < 0)
    log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Failed to create spool file %s: %s",
      spool_name, strerror(errno));
  }


if (fchown(data_fd, exim_uid, exim_gid))
  log_write(0, LOG_MAIN|LOG_PANIC_DIE,
    "Failed setting ownership on spool file %s: %s",
    spool_name, strerror(errno));
(void)fchmod(data_fd, SPOOL_MODE);


data_file = fdopen(data_fd, "w+");
lock_data.l_type = F_WRLCK;
lock_data.l_whence = SEEK_SET;
lock_data.l_start = 0;
lock_data.l_len = SPOOL_DATA_START_OFFSET;

if (fcntl(data_fd, F_SETLK, &lock_data) < 0)
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Cannot lock %s (%d): %s", spool_name,
    errno, strerror(errno));


fprintf(data_file, "%s-D\n", message_id);
if (next != NULL)
  {
  uschar *s = next->text;
  int len = next->slen;
  len = fwrite(s, 1, len, data_file);  len = len;
  body_linecount++;
  }


if (!ferror(data_file) && !(receive_feof)() && message_ended != END_DOT)
  {
  if (smtp_input)
    {
    message_ended = chunking_state <= CHUNKING_OFFERED
      ? read_message_data_smtp(data_file)
      : spool_wireformat
      ? read_message_bdat_smtp_wire(data_file)
      : read_message_bdat_smtp(data_file);
    receive_linecount++;
    }
  else message_ended = read_message_data(data_file);

  receive_linecount += body_linecount;
  message_linecount += body_linecount;

  switch (message_ended)
    {


    case END_EOF:
      if (smtp_input)
	{
	Uunlink(spool_name);
	cancel_cutthrough_connection(TRUE, US"sender closed connection");
	message_id[0] = 0;
	smtp_reply = handle_lost_connection(US"");
	smtp_yield = FALSE;
	goto TIDYUP;
	}
      break;


    case END_SIZE:
      Uunlink(spool_name);
      cancel_cutthrough_connection(TRUE, US"mail too big");
      if (smtp_input) receive_swallow_smtp();

      log_write(L_size_reject, LOG_MAIN|LOG_REJECT, "rejected from <%s>%s%s%s%s: "
	"message too big: read=%d max=%d",
	sender_address,
	(sender_fullhost == NULL)? "" : " H=",
	(sender_fullhost == NULL)? US"" : sender_fullhost,
	(sender_ident == NULL)? "" : " U=",
	(sender_ident == NULL)? US"" : sender_ident,
	message_size,
	thismessage_size_limit);

      if (smtp_input)
	{
	smtp_reply = US"552 Message size exceeds maximum permitted";
	message_id[0] = 0;
	goto TIDYUP;
	}
      else
	{
	fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
	give_local_error(ERRMESS_TOOBIG,
	  string_sprintf("message too big (max=%d)", thismessage_size_limit),
	  US"message rejected: ", error_rc, data_file, header_list);

	}
      break;


    case END_PROTOCOL:
      Uunlink(spool_name);
      cancel_cutthrough_connection(TRUE, US"sender protocol error");
      smtp_reply = US"";
      message_id[0] = 0;
      goto TIDYUP;
    }
  }


os_non_restarting_signal(SIGALRM, sigalrm_handler);


if (fflush(data_file) == EOF || ferror(data_file) ||
    EXIMfsync(fileno(data_file)) < 0 || (receive_ferror)())
  {
  uschar *msg_errno = US strerror(errno);
  BOOL input_error = (receive_ferror)() != 0;
  uschar *msg = string_sprintf("%s error (%s) while receiving message from %s",
    input_error? "Input read" : "Spool write",
    msg_errno,
    (sender_fullhost != NULL)? sender_fullhost : sender_ident);

  log_write(0, LOG_MAIN, "Message abandoned: %s", msg);
  Uunlink(spool_name);
  cancel_cutthrough_connection(TRUE, US"error writing spoolfile");

  if (smtp_input)
    {
    if (input_error)
      smtp_reply = US"451 Error while reading input data";
    else
      {
      smtp_reply = US"451 Error while writing spool file";
      receive_swallow_smtp();
      }
    message_id[0] = 0;
    goto TIDYUP;
    }

  else
    {
    fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
    give_local_error(ERRMESS_IOERR, msg, US"", error_rc, data_file,
      header_list);

    }
  }


DEBUG(D_receive) debug_printf("Data file written for message %s\n", message_id);


if (extract_recip && (bad_addresses != NULL || recipients_count == 0))
  {
  DEBUG(D_receive)
    {
    if (recipients_count == 0) debug_printf("*** No recipients\n");
    if (bad_addresses != NULL)
      {
      error_block *eblock = bad_addresses;
      debug_printf("*** Bad address(es)\n");
      while (eblock != NULL)
        {
        debug_printf("  %s: %s\n", eblock->text1, eblock->text2);
        eblock = eblock->next;
        }
      }
    }

  fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);


  if (error_handling == ERRORS_SENDER)
    {
    if (!moan_to_sender(
          (bad_addresses == NULL)?
            (extracted_ignored? ERRMESS_IGADDRESS : ERRMESS_NOADDRESS) :
          (recipients_list == NULL)? ERRMESS_BADNOADDRESS : ERRMESS_BADADDRESS,
          bad_addresses, header_list, data_file, FALSE))
      error_rc = (bad_addresses == NULL)? EXIT_NORECIPIENTS : EXIT_FAILURE;
    }
  else
    {
    if (bad_addresses == NULL)
      {
      if (extracted_ignored)
        fprintf(stderr, "exim: all -t recipients overridden by command line\n");
      else
        fprintf(stderr, "exim: no recipients in message\n");
      }
    else
      {
      fprintf(stderr, "exim: invalid address%s",
        (bad_addresses->next == NULL)? ":" : "es:\n");
      while (bad_addresses != NULL)
        {
        fprintf(stderr, "  %s: %s\n", bad_addresses->text1,
          bad_addresses->text2);
        bad_addresses = bad_addresses->next;
        }
      }
    }

  if (recipients_count == 0 || error_handling == ERRORS_STDERR)
    {
    Uunlink(spool_name);
    (void)fclose(data_file);
    exim_exit(error_rc, US"receiving");
    }
  }


if (received_header->text == NULL)
  {
  received_header_gen();


  message_body_size = (fstat(data_fd, &statbuf) == 0)?
    statbuf.st_size - SPOOL_DATA_START_OFFSET : -1;


  add_acl_headers(ACL_WHERE_RCPT, US"MAIL or RCPT");
  }
else
  message_body_size = (fstat(data_fd, &statbuf) == 0)?
    statbuf.st_size - SPOOL_DATA_START_OFFSET : -1;


deliver_datafile = data_fd;
user_msg = NULL;

enable_dollar_recipients = TRUE;

if (recipients_count == 0)
  blackholed_by = recipients_discarded ? US"MAIL ACL" : US"RCPT ACL";

else
  {


  if (smtp_input && !smtp_batched_input)
    {

#ifndef DISABLE_DKIM
    if (!dkim_disable_verify)
      {

      dkim_exim_verify_finish();


      if (acl_smtp_dkim && dkim_verify_signers && *dkim_verify_signers)
        {
        uschar * dkim_verify_signers_expanded =
          expand_string(dkim_verify_signers);
	gstring * results = NULL;
	int signer_sep = 0;
	const uschar * ptr;
	uschar * item;
	gstring * seen_items = NULL;
	int old_pool = store_pool;

	store_pool = POOL_PERM;

        if (!(ptr = dkim_verify_signers_expanded))
          log_write(0, LOG_MAIN|LOG_PANIC,
            "expansion of dkim_verify_signers option failed: %s",
            expand_string_message);


	rc = OK;
	while ((item = string_nextinlist(&ptr, &signer_sep, NULL, 0)))
	  {

	  if (!item || !*item) continue;


	  if (seen_items)
	    {
	    uschar * seen_item;
	    const uschar * seen_items_list = string_from_gstring(seen_items);
	    int seen_sep = ':';
	    BOOL seen_this_item = FALSE;

	    while ((seen_item = string_nextinlist(&seen_items_list, &seen_sep,
						  NULL, 0)))
	      if (Ustrcmp(seen_item,item) == 0)
		{
		seen_this_item = TRUE;
		break;
		}

	    if (seen_this_item)
	      {
	      DEBUG(D_receive)
		debug_printf("acl_smtp_dkim: skipping signer %s, "
		  "already seen\n", item);
	      continue;
	      }

	    seen_items = string_catn(seen_items, ":", 1);
	    }
	  seen_items = string_cat(seen_items, item);

	  rc = dkim_exim_acl_run(item, &results, &user_msg, &log_msg);
	  if (rc != OK)
	    {
	    DEBUG(D_receive)
	      debug_printf("acl_smtp_dkim: acl_check returned %d on %s, "
		"skipping remaining items\n", rc, item);
	    cancel_cutthrough_connection(TRUE, US"dkim acl not ok");
	    break;
	    }
	  }
	dkim_verify_status = string_from_gstring(results);
	store_pool = old_pool;
	add_acl_headers(ACL_WHERE_DKIM, US"DKIM");
	if (rc == DISCARD)
	  {
	  recipients_count = 0;
	  blackholed_by = US"DKIM ACL";
	  if (log_msg)
	    blackhole_log_msg = string_sprintf(": %s", log_msg);
	  }
	else if (rc != OK)
	  {
	  Uunlink(spool_name);
	  if (smtp_handle_acl_fail(ACL_WHERE_DKIM, rc, user_msg, log_msg) != 0)
	    smtp_yield = FALSE;
	  smtp_reply = US"";
	  message_id[0] = 0;
	  goto TIDYUP;
	  }
        }
      else
	dkim_exim_verify_log_all();
      }
#endif

#ifdef WITH_CONTENT_SCAN
    if (recipients_count > 0 &&
        acl_smtp_mime != NULL &&
        !run_mime_acl(acl_smtp_mime, &smtp_yield, &smtp_reply, &blackholed_by))
      goto TIDYUP;
#endif

#ifdef EXPERIMENTAL_DMARC
    dmarc_up = dmarc_store_data(from_header);
#endif

#ifndef DISABLE_PRDR
    if (prdr_requested && recipients_count > 1 && acl_smtp_data_prdr)
      {
      unsigned int c;
      int all_pass = OK;
      int all_fail = FAIL;

      smtp_printf("353 PRDR content analysis beginning\r\n", TRUE);

      for (c = 0; recipients_count > c; c++)
        {
	uschar * addr= recipients_list[c].address;
	uschar * msg= US"PRDR R=<%s> %s";
	uschar * code;
        DEBUG(D_receive)
          debug_printf("PRDR processing recipient %s (%d of %d)\n",
                       addr, c+1, recipients_count);
        rc = acl_check(ACL_WHERE_PRDR, addr,
                       acl_smtp_data_prdr, &user_msg, &log_msg);


        all_pass |= rc;

        all_fail &= rc;

        switch (rc)
          {
          case OK: case DISCARD: code = US"250"; break;
          case DEFER:            code = US"450"; break;
          default:               code = US"550"; break;
          }
	if (user_msg != NULL)
	  smtp_user_msg(code, user_msg);
	else
	  {
	  switch (rc)
            {
            case OK: case DISCARD:
              msg = string_sprintf(CS msg, addr, "acceptance");        break;
            case DEFER:
              msg = string_sprintf(CS msg, addr, "temporary refusal"); break;
            default:
              msg = string_sprintf(CS msg, addr, "refusal");           break;
            }
          smtp_user_msg(code, msg);
	  }
	if (log_msg)       log_write(0, LOG_MAIN, "PRDR %s %s", addr, log_msg);
	else if (user_msg) log_write(0, LOG_MAIN, "PRDR %s %s", addr, user_msg);
	else               log_write(0, LOG_MAIN, "%s", CS msg);

	if (rc != OK) { receive_remove_recipient(addr); c--; }
        }

      smtp_reply = string_sprintf("%s id=%s message %s",
		       all_fail == FAIL ? US"550" : US"250",
		       message_id,
                       all_fail == FAIL
		         ? US"rejected for all recipients"
			 : all_pass == OK
			   ? US"accepted"
			   : US"accepted for some recipients");
      if (recipients_count == 0)
        {
        message_id[0] = 0;
	goto TIDYUP;
	}
      }
    else
      prdr_requested = FALSE;
#endif


    if (acl_smtp_data != NULL && recipients_count > 0)
      {
      rc = acl_check(ACL_WHERE_DATA, NULL, acl_smtp_data, &user_msg, &log_msg);
      add_acl_headers(ACL_WHERE_DATA, US"DATA");
      if (rc == DISCARD)
        {
        recipients_count = 0;
        blackholed_by = US"DATA ACL";
        if (log_msg)
          blackhole_log_msg = string_sprintf(": %s", log_msg);
	cancel_cutthrough_connection(TRUE, US"data acl discard");
        }
      else if (rc != OK)
        {
        Uunlink(spool_name);
	cancel_cutthrough_connection(TRUE, US"data acl not ok");
#ifdef WITH_CONTENT_SCAN
        unspool_mbox();
#endif
#ifdef EXPERIMENTAL_DCC
	dcc_ok = 0;
#endif
        if (smtp_handle_acl_fail(ACL_WHERE_DATA, rc, user_msg, log_msg) != 0)
          smtp_yield = FALSE;
        smtp_reply = US"";
        message_id[0] = 0;
        goto TIDYUP;
        }
      }
    }


  else
    {

#ifdef WITH_CONTENT_SCAN
    if (acl_not_smtp_mime != NULL &&
        !run_mime_acl(acl_not_smtp_mime, &smtp_yield, &smtp_reply,
          &blackholed_by))
      goto TIDYUP;
#endif

    if (acl_not_smtp != NULL)
      {
      uschar *user_msg, *log_msg;
      rc = acl_check(ACL_WHERE_NOTSMTP, NULL, acl_not_smtp, &user_msg, &log_msg);
      if (rc == DISCARD)
        {
        recipients_count = 0;
        blackholed_by = US"non-SMTP ACL";
        if (log_msg != NULL)
          blackhole_log_msg = string_sprintf(": %s", log_msg);
        }
      else if (rc != OK)
        {
        Uunlink(spool_name);
#ifdef WITH_CONTENT_SCAN
        unspool_mbox();
#endif
#ifdef EXPERIMENTAL_DCC
	dcc_ok = 0;
#endif


        if (log_reject_target != 0)
          log_write(0, log_reject_target, "F=<%s> rejected by non-SMTP ACL: %s",
            sender_address, log_msg);

        if (user_msg == NULL) user_msg = US"local configuration problem";
        if (smtp_batched_input)
          {
          moan_smtp_batch(NULL, "%d %s", 550, user_msg);

          }
        else
          {
          fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
          give_local_error(ERRMESS_LOCAL_ACL, user_msg,
            US"message rejected by non-SMTP ACL: ", error_rc, data_file,
              header_list);

          }
        }
      add_acl_headers(ACL_WHERE_NOTSMTP, US"non-SMTP");
      }
    }


  if (deliver_freeze) frozen_by = US"ACL";
  if (queue_only_policy) queued_by = US"ACL";
  }

#ifdef WITH_CONTENT_SCAN
unspool_mbox();
#endif

#ifdef EXPERIMENTAL_DCC
dcc_ok = 0;
#endif


lseek(data_fd, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);


os_non_restarting_signal(SIGSEGV, local_scan_crash_handler);
os_non_restarting_signal(SIGFPE, local_scan_crash_handler);
os_non_restarting_signal(SIGILL, local_scan_crash_handler);
os_non_restarting_signal(SIGBUS, local_scan_crash_handler);

DEBUG(D_receive) debug_printf("calling local_scan(); timeout=%d\n",
  local_scan_timeout);
local_scan_data = NULL;

os_non_restarting_signal(SIGALRM, local_scan_timeout_handler);
if (local_scan_timeout > 0) alarm(local_scan_timeout);
rc = local_scan(data_fd, &local_scan_data);
alarm(0);
os_non_restarting_signal(SIGALRM, sigalrm_handler);

enable_dollar_recipients = FALSE;

store_pool = POOL_MAIN;
DEBUG(D_receive) debug_printf("local_scan() returned %d %s\n", rc,
  local_scan_data);

os_non_restarting_signal(SIGSEGV, SIG_DFL);
os_non_restarting_signal(SIGFPE, SIG_DFL);
os_non_restarting_signal(SIGILL, SIG_DFL);
os_non_restarting_signal(SIGBUS, SIG_DFL);


if (local_scan_data != NULL)
  {
  int len = Ustrlen(local_scan_data);
  if (len > LOCAL_SCAN_MAX_RETURN) len = LOCAL_SCAN_MAX_RETURN;
  local_scan_data = string_copyn(local_scan_data, len);
  }

if (rc == LOCAL_SCAN_ACCEPT_FREEZE)
  {
  if (!deliver_freeze)
    {
    deliver_freeze = TRUE;
    deliver_frozen_at = time(NULL);
    frozen_by = US"local_scan()";
    }
  rc = LOCAL_SCAN_ACCEPT;
  }
else if (rc == LOCAL_SCAN_ACCEPT_QUEUE)
  {
  if (!queue_only_policy)
    {
    queue_only_policy = TRUE;
    queued_by = US"local_scan()";
    }
  rc = LOCAL_SCAN_ACCEPT;
  }


if (rc == LOCAL_SCAN_ACCEPT)
  {
  if (local_scan_data != NULL)
    {
    uschar *s;
    for (s = local_scan_data; *s != 0; s++) if (*s == '\n') *s = ' ';
    }
  for (i = 0; i < recipients_count; i++)
    {
    recipient_item *r = recipients_list + i;
    r->address = rewrite_address_qualify(r->address, TRUE);
    if (r->errors_to != NULL)
      r->errors_to = rewrite_address_qualify(r->errors_to, TRUE);
    }
  if (recipients_count == 0 && blackholed_by == NULL)
    blackholed_by = US"local_scan";
  }


else
  {
  uschar *istemp = US"";
  uschar *smtp_code;
  gstring * g;

  errmsg = local_scan_data;

  Uunlink(spool_name);
  switch(rc)
    {
    default:
    log_write(0, LOG_MAIN, "invalid return %d from local_scan(). Temporary "
      "rejection given", rc);
    goto TEMPREJECT;

    case LOCAL_SCAN_REJECT_NOLOGHDR:
    BIT_CLEAR(log_selector, log_selector_size, Li_rejected_header);


    case LOCAL_SCAN_REJECT:
    smtp_code = US"550";
    if (errmsg == NULL) errmsg =  US"Administrative prohibition";
    break;

    case LOCAL_SCAN_TEMPREJECT_NOLOGHDR:
    BIT_CLEAR(log_selector, log_selector_size, Li_rejected_header);


    case LOCAL_SCAN_TEMPREJECT:
    TEMPREJECT:
    smtp_code = US"451";
    if (errmsg == NULL) errmsg = US"Temporary local problem";
    istemp = US"temporarily ";
    break;
    }

  g = string_append(g, 2, US"F=",
    sender_address[0] == 0 ? US"<>" : sender_address);
  g = add_host_info_for_log(g);

  log_write(0, LOG_MAIN|LOG_REJECT, "%s %srejected by local_scan(): %.256s",
    string_from_gstring(g), istemp, string_printing(errmsg));

  if (smtp_input)
    {
    if (!smtp_batched_input)
      {
      smtp_respond(smtp_code, 3, TRUE, errmsg);
      message_id[0] = 0;
      smtp_reply = US"";
      goto TIDYUP;
      }
    else
      {
      moan_smtp_batch(NULL, "%s %s", smtp_code, errmsg);

      }
    }
  else
    {
    fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
    give_local_error(ERRMESS_LOCAL_SCAN, errmsg,
      US"message rejected by local scan code: ", error_rc, data_file,
        header_list);

    }
  }


signal(SIGTERM, SIG_IGN);
signal(SIGINT, SIG_IGN);


deliver_firsttime = TRUE;

#ifdef EXPERIMENTAL_BRIGHTMAIL
if (bmi_run == 1)
  {
  lseek(data_fd, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
  bmi_verdicts = bmi_process_message(header_list, data_fd);
  }
#endif


timestamp = expand_string(US"${tod_full}");
tslen = Ustrlen(timestamp);

memcpy(received_header->text + received_header->slen - tslen - 1,
  timestamp, tslen);


if (mua_wrapper)
  {
  deliver_freeze = FALSE;
  queue_only_policy = FALSE;
  }


if (host_checking || blackholed_by != NULL)
  {
  header_line *h;
  Uunlink(spool_name);
  msg_size = 0;
  for (h = header_list; h != NULL; h = h->next)
    if (h->type != '*') msg_size += h->slen;
  }


else
  if ((msg_size = spool_write_header(message_id, SW_RECEIVING, &errmsg)) < 0)
    {
    log_write(0, LOG_MAIN, "Message abandoned: %s", errmsg);
    Uunlink(spool_name);

    if (smtp_input)
      {
      smtp_reply = US"451 Error in writing spool file";
      message_id[0] = 0;
      goto TIDYUP;
      }
    else
      {
      fseek(data_file, (long int)SPOOL_DATA_START_OFFSET, SEEK_SET);
      give_local_error(ERRMESS_IOERR, errmsg, US"", error_rc, data_file,
        header_list);

      }
    }


receive_messagecount++;


message_id_tv.tv_usec = (message_id_tv.tv_usec/id_resolution) * id_resolution;
exim_wait_tick(&message_id_tv, id_resolution);


fflush(data_file);
fstat(data_fd, &statbuf);

msg_size += statbuf.st_size - SPOOL_DATA_START_OFFSET + 1;


g = string_get(256);

g = string_append(g, 2,
  fake_response == FAIL ? US"(= " : US"<= ",
  sender_address[0] == 0 ? US"<>" : sender_address);
if (message_reference)
  g = string_append(g, 2, US" R=", message_reference);

g = add_host_info_for_log(g);

#ifdef SUPPORT_TLS
if (LOGGING(tls_cipher) && tls_in.cipher)
  g = string_append(g, 2, US" X=", tls_in.cipher);
if (LOGGING(tls_certificate_verified) && tls_in.cipher)
  g = string_append(g, 2, US" CV=", tls_in.certificate_verified ? "yes":"no");
if (LOGGING(tls_peerdn) && tls_in.peerdn)
  g = string_append(g, 3, US" DN=\"", string_printing(tls_in.peerdn), US"\"");
if (LOGGING(tls_sni) && tls_in.sni)
  g = string_append(g, 3, US" SNI=\"", string_printing(tls_in.sni), US"\"");
#endif

if (sender_host_authenticated)
  {
  g = string_append(g, 2, US" A=", sender_host_authenticated);
  if (authenticated_id)
    {
    g = string_append(g, 2, US":", authenticated_id);
    if (LOGGING(smtp_mailauth) && authenticated_sender)
      g = string_append(g, 2, US":", authenticated_sender);
    }
  }

#ifndef DISABLE_PRDR
if (prdr_requested)
  g = string_catn(g, US" PRDR", 5);
#endif

#ifdef SUPPORT_PROXY
if (proxy_session && LOGGING(proxy))
  g = string_append(g, 2, US" PRX=", proxy_local_address);
#endif

if (chunking_state > CHUNKING_OFFERED)
  g = string_catn(g, US" K", 2);

sprintf(CS big_buffer, "%d", msg_size);
g = string_append(g, 2, US" S=", big_buffer);


if (LOGGING(8bitmime))
  {
  sprintf(CS big_buffer, "%d", body_8bitmime);
  g = string_append(g, 2, US" M8S=", big_buffer);
  }

if (*queue_name)
  g = string_append(g, 2, US" Q=", queue_name);


if (msgid_header)
  {
  uschar *old_id;
  BOOL save_allow_domain_literals = allow_domain_literals;
  allow_domain_literals = TRUE;
  old_id = parse_extract_address(Ustrchr(msgid_header->text, ':') + 1,
    &errmsg, &start, &end, &domain, FALSE);
  allow_domain_literals = save_allow_domain_literals;
  if (old_id != NULL)
    g = string_append(g, 2, US" id=", string_printing(old_id));
  }


if (LOGGING(subject) && subject_header != NULL)
  {
  int i;
  uschar *p = big_buffer;
  uschar *ss = expand_string(US"$h_subject:");


  *p++ = '\"';
  if (*ss != 0) for (i = 0; i < 100 && ss[i] != 0; i++)
    {
    if (ss[i] == '\"' || ss[i] == '\\') *p++ = '\\';
    *p++ = ss[i];
    }
  *p++ = '\"';
  *p = 0;
  g = string_append(g, 2, US" T=", string_printing(big_buffer));
  }


(void) string_from_gstring(g);


if (message_logs && !blackholed_by)
  {
  int fd;

  spool_name = spool_fname(US"msglog", message_subdir, message_id, US"");

  if (  (fd = Uopen(spool_name, O_WRONLY|O_APPEND|O_CREAT, SPOOL_MODE)) < 0
     && errno == ENOENT
     )
    {
    (void)directory_make(spool_directory,
			spool_sname(US"msglog", message_subdir),
			MSGLOG_DIRECTORY_MODE, TRUE);
    fd = Uopen(spool_name, O_WRONLY|O_APPEND|O_CREAT, SPOOL_MODE);
    }

  if (fd < 0)
    log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't open message log %s: %s",
      spool_name, strerror(errno));
  else
    {
    FILE *message_log = fdopen(fd, "a");
    if (message_log == NULL)
      {
      log_write(0, LOG_MAIN|LOG_PANIC, "Couldn't fdopen message log %s: %s",
        spool_name, strerror(errno));
      (void)close(fd);
      }
    else
      {
      uschar *now = tod_stamp(tod_log);
      fprintf(message_log, "%s Received from %s\n", now, g->s+3);
      if (deliver_freeze) fprintf(message_log, "%s frozen by %s\n", now,
        frozen_by);
      if (queue_only_policy) fprintf(message_log,
        "%s no immediate delivery: queued%s%s by %s\n", now,
        *queue_name ? " in " : "", *queue_name ? CS queue_name : "",
	queued_by);
      (void)fclose(message_log);
      }
    }
  }


receive_call_bombout = TRUE;


if (smtp_input && sender_host_address != NULL && !sender_host_notsocket &&
    !receive_smtp_buffered())
  {
  struct timeval tv;
  fd_set select_check;
  FD_ZERO(&select_check);
  FD_SET(fileno(smtp_in), &select_check);
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  if (select(fileno(smtp_in) + 1, &select_check, NULL, NULL, &tv) != 0)
    {
    int c = (receive_getc)(GETC_BUFFER_UNLIMITED);
    if (c != EOF) (receive_ungetc)(c); else
      {
      smtp_notquit_exit(US"connection-lost", NULL, NULL);
      smtp_reply = US"";
      smtp_yield = FALSE;


      g->ptr = 0;
      g = string_cat(g, US"SMTP connection lost after final dot");
      g = add_host_info_for_log(g);
      log_write(0, LOG_MAIN, "%s", string_from_gstring(g));


      Uunlink(spool_fname(US"input", message_subdir, message_id, US"-D"));
      Uunlink(spool_fname(US"input", message_subdir, message_id, US"-H"));
      Uunlink(spool_fname(US"msglog", message_subdir, message_id, US""));

      goto TIDYUP;
      }
    }
  }


if(cutthrough.fd >= 0 && cutthrough.delivery)
  {
  uschar * msg = cutthrough_finaldot();

  switch(msg[0])
    {
    case '2':
      cutthrough_done = ACCEPTED;
      break;

    case '4':

      if (cutthrough.defer_pass) smtp_reply = string_copy_malloc(msg);


    default:
      cutthrough_done = TMP_REJ;
      break;

    case '5':
      smtp_reply = string_copy_malloc(msg);
      cutthrough_done = PERM_REJ;
      break;
    }
  }

#ifndef DISABLE_PRDR
if(!smtp_reply || prdr_requested)
#else
if(!smtp_reply)
#endif
  {
  log_write(0, LOG_MAIN |
    (LOGGING(received_recipients)? LOG_RECIPIENTS : 0) |
    (LOGGING(received_sender)? LOG_SENDER : 0),
    "%s", g->s);


  if (deliver_freeze) log_write(0, LOG_MAIN, "frozen by %s", frozen_by);
  if (queue_only_policy) log_write(L_delay_delivery, LOG_MAIN,
    "no immediate delivery: queued%s%s by %s",
    *queue_name ? " in " : "", *queue_name ? CS queue_name : "",
    queued_by);
  }
receive_call_bombout = FALSE;

store_reset(g);


if (deliver_freeze && freeze_tell != NULL && freeze_tell[0] != 0)
  {
  moan_tell_someone(freeze_tell, NULL, US"Message frozen on arrival",
    "Message %s was frozen on arrival by %s.\nThe sender is <%s>.\n",
    message_id, frozen_by, sender_address);
  }


TIDYUP:
process_info[process_info_len] = 0;
if (data_file != NULL) (void)fclose(data_file);


signal(SIGTERM, SIG_DFL);
signal(SIGINT, SIG_DFL);


if (smtp_input)
  {
  yield = smtp_yield;


  if (!smtp_batched_input)
    {
    if (!smtp_reply)
      {
      if (fake_response != OK)
        smtp_respond(fake_response == DEFER ? US"450" : US"550",
	  3, TRUE, fake_response_text);


      else if (user_msg)
        {
        uschar *code = US"250";
        int len = 3;
        smtp_message_code(&code, &len, &user_msg, NULL, TRUE);
        smtp_respond(code, len, TRUE, user_msg);
        }


      else if (chunking_state > CHUNKING_OFFERED)
	{
        smtp_printf("250- %u byte chunk, total %d\r\n250 OK id=%s\r\n", FALSE,
	    chunking_datasize, message_size+message_linecount, message_id);
	chunking_state = CHUNKING_OFFERED;
	}
      else
        smtp_printf("250 OK id=%s\r\n", FALSE, message_id);

      if (host_checking)
        fprintf(stdout,
          "\n**** SMTP testing: that is not a real message id!\n\n");
      }


    else if (smtp_reply[0] != 0)
      if (fake_response != OK && (smtp_reply[0] == '2'))
        smtp_respond((fake_response == DEFER)? US"450" : US"550", 3, TRUE,
          fake_response_text);
      else
        smtp_printf("%.1024s\r\n", FALSE, smtp_reply);

    switch (cutthrough_done)
      {
      case ACCEPTED:
	log_write(0, LOG_MAIN, "Completed");
      case PERM_REJ:

	Uunlink(spool_fname(US"input", message_subdir, message_id, US"-D"));
	Uunlink(spool_fname(US"input", message_subdir, message_id, US"-H"));
	Uunlink(spool_fname(US"msglog", message_subdir, message_id, US""));
	break;

      case TMP_REJ:
	if (cutthrough.defer_pass)
	  {
	  Uunlink(spool_fname(US"input", message_subdir, message_id, US"-D"));
	  Uunlink(spool_fname(US"input", message_subdir, message_id, US"-H"));
	  Uunlink(spool_fname(US"msglog", message_subdir, message_id, US""));
	  }
      default:
	break;
      }
    if (cutthrough_done != NOT_TRIED)
      {
      message_id[0] = 0;
      cutthrough.delivery = cutthrough.callout_hold_only = FALSE;
      cutthrough.defer_pass = FALSE;
      }
    }


  else if (smtp_reply)
    moan_smtp_batch(NULL, "%s", smtp_reply);
  }


if (blackholed_by)
  {
  const uschar *detail = local_scan_data
    ? string_printing(local_scan_data)
    : string_sprintf("(%s discarded recipients)", blackholed_by);
  log_write(0, LOG_MAIN, "=> blackhole %s%s", detail, blackhole_log_msg);
  log_write(0, LOG_MAIN, "Completed");
  message_id[0] = 0;
  }


header_list = header_last = NULL;

return yield;
}
