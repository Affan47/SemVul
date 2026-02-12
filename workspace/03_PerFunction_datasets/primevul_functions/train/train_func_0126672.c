acl_verify(int where, address_item *addr, const uschar *arg,
  uschar **user_msgptr, uschar **log_msgptr, int *basic_errno)
{
int sep = '/';
int callout = -1;
int callout_overall = -1;
int callout_connect = -1;
int verify_options = 0;
int rc;
BOOL verify_header_sender = FALSE;
BOOL defer_ok = FALSE;
BOOL callout_defer_ok = FALSE;
BOOL no_details = FALSE;
BOOL success_on_redirect = FALSE;
address_item *sender_vaddr = NULL;
uschar *verify_sender_address = NULL;
uschar *pm_mailfrom = NULL;
uschar *se_mailfrom = NULL;


uschar *slash = Ustrchr(arg, '/');
const uschar *list = arg;
uschar *ss = string_nextinlist(&list, &sep, big_buffer, big_buffer_size);
verify_type_t * vp;

if (!ss) goto BAD_VERIFY;


for (vp= verify_type_list;
     CS vp < CS verify_type_list + sizeof(verify_type_list);
     vp++
    )
  if (vp->alt_opt_sep ? strncmpic(ss, vp->name, vp->alt_opt_sep) == 0
                      : strcmpic (ss, vp->name) == 0)
   break;
if (CS vp >= CS verify_type_list + sizeof(verify_type_list))
  goto BAD_VERIFY;

if (vp->no_options && slash)
  {
  *log_msgptr = string_sprintf("unexpected '/' found in \"%s\" "
    "(this verify item has no options)", arg);
  return ERROR;
  }
if (!(vp->where_allowed & BIT(where)))
  {
  *log_msgptr = string_sprintf("cannot verify %s in ACL for %s",
		  vp->name, acl_wherenames[where]);
  return ERROR;
  }
switch(vp->value)
  {
  case VERIFY_REV_HOST_LKUP:
    if (!sender_host_address) return OK;
    if ((rc = acl_verify_reverse(user_msgptr, log_msgptr)) == DEFER)
      while ((ss = string_nextinlist(&list, &sep, NULL, 0)))
	if (strcmpic(ss, US"defer_ok") == 0)
	  return OK;
    return rc;

  case VERIFY_CERT:


    if (tls_in.certificate_verified) return OK;
    *user_msgptr = US"no verified certificate";
    return FAIL;

  case VERIFY_HELO:


    if (!f.helo_verified && !f.helo_verify_failed) smtp_verify_helo();
    return f.helo_verified ? OK : FAIL;

  case VERIFY_CSA:


    rc = acl_verify_csa(list);
    *log_msgptr = *user_msgptr = string_sprintf("client SMTP authorization %s",
                                              csa_reason_string[rc]);
    csa_status = csa_status_string[rc];
    DEBUG(D_acl) debug_printf_indent("CSA result %s\n", csa_status);
    return csa_return_code[rc];

#ifdef EXPERIMENTAL_ARC
  case VERIFY_ARC:
    {
    const uschar * condlist = CUS string_nextinlist(&list, &sep, NULL, 0);
    int csep = 0;
    uschar * cond;

    if (!(arc_state = acl_verify_arc())) return DEFER;
    DEBUG(D_acl) debug_printf_indent("ARC verify result %s %s%s%s\n", arc_state,
      arc_state_reason ? "(":"", arc_state_reason, arc_state_reason ? ")":"");

    if (!condlist) condlist = US"none:pass";
    while ((cond = string_nextinlist(&condlist, &csep, NULL, 0)))
      if (Ustrcmp(arc_state, cond) == 0) return OK;
    return FAIL;
    }
#endif

  case VERIFY_HDR_SYNTAX:


    rc = verify_check_headers(log_msgptr);
    if (rc != OK && *log_msgptr)
      if (smtp_return_error_details)
	*user_msgptr = string_sprintf("Rejected after DATA: %s", *log_msgptr);
      else
	acl_verify_message = *log_msgptr;
    return rc;

  case VERIFY_HDR_NAMES_ASCII:


    rc = verify_check_header_names_ascii(log_msgptr);
    if (rc != OK && smtp_return_error_details && *log_msgptr)
      *user_msgptr = string_sprintf("Rejected after DATA: %s", *log_msgptr);
    return rc;

  case VERIFY_NOT_BLIND:


    if ((rc = verify_check_notblind()) != OK)
      {
      *log_msgptr = string_sprintf("bcc recipient detected");
      if (smtp_return_error_details)
        *user_msgptr = string_sprintf("Rejected after DATA: %s", *log_msgptr);
      }
    return rc;


  case VERIFY_HDR_SNDR:
    verify_header_sender = TRUE;
    break;

  case VERIFY_SNDR:


    {
    uschar *s = ss + 6;
    if (*s == 0)
      verify_sender_address = sender_address;
    else
      {
      while (isspace(*s)) s++;
      if (*s++ != '=') goto BAD_VERIFY;
      while (isspace(*s)) s++;
      verify_sender_address = string_copy(s);
      }
    }
    break;

  case VERIFY_RCPT:
    break;
  }


while ((ss = string_nextinlist(&list, &sep, big_buffer, big_buffer_size))
      != NULL)
  {
  if (strcmpic(ss, US"defer_ok") == 0) defer_ok = TRUE;
  else if (strcmpic(ss, US"no_details") == 0) no_details = TRUE;
  else if (strcmpic(ss, US"success_on_redirect") == 0) success_on_redirect = TRUE;


  else if (strcmpic(ss, US"callout_defer_ok") == 0)
    {
    callout_defer_ok = TRUE;
    if (callout == -1) callout = CALLOUT_TIMEOUT_DEFAULT;
    }

  else if (strcmpic(ss, US"check_postmaster") == 0)
     {
     pm_mailfrom = US"";
     if (callout == -1) callout = CALLOUT_TIMEOUT_DEFAULT;
     }


  else if (strncmpic(ss, US"callout", 7) == 0)
    {
    callout = CALLOUT_TIMEOUT_DEFAULT;
    ss += 7;
    if (*ss != 0)
      {
      while (isspace(*ss)) ss++;
      if (*ss++ == '=')
        {
	const uschar * sublist = ss;
        int optsep = ',';
        uschar *opt;
        uschar buffer[256];
        while (isspace(*sublist)) sublist++;

        while ((opt = string_nextinlist(&sublist, &optsep, buffer, sizeof(buffer))))
          {
	  callout_opt_t * op;
	  double period = 1.0F;

	  for (op= callout_opt_list; op->name; op++)
	    if (strncmpic(opt, op->name, Ustrlen(op->name)) == 0)
	      break;

	  verify_options |= op->flag;
	  if (op->has_option)
	    {
	    opt += Ustrlen(op->name);
            while (isspace(*opt)) opt++;
            if (*opt++ != '=')
              {
              *log_msgptr = string_sprintf("'=' expected after "
                "\"%s\" in ACL verify condition \"%s\"", op->name, arg);
              return ERROR;
              }
            while (isspace(*opt)) opt++;
	    }
	  if (op->timeval && (period = readconf_readtime(opt, 0, FALSE)) < 0)
	    {
	    *log_msgptr = string_sprintf("bad time value in ACL condition "
	      "\"verify %s\"", arg);
	    return ERROR;
	    }

	  switch(op->value)
	    {
            case CALLOUT_DEFER_OK:		callout_defer_ok = TRUE; break;
            case CALLOUT_POSTMASTER:		pm_mailfrom = US"";	break;
            case CALLOUT_FULLPOSTMASTER:	pm_mailfrom = US"";	break;
            case CALLOUT_MAILFROM:
              if (!verify_header_sender)
                {
                *log_msgptr = string_sprintf("\"mailfrom\" is allowed as a "
                  "callout option only for verify=header_sender (detected in ACL "
                  "condition \"%s\")", arg);
                return ERROR;
                }
              se_mailfrom = string_copy(opt);
  	      break;
            case CALLOUT_POSTMASTER_MAILFROM:	pm_mailfrom = string_copy(opt); break;
            case CALLOUT_MAXWAIT:		callout_overall = period;	break;
            case CALLOUT_CONNECT:		callout_connect = period;	break;
            case CALLOUT_TIME:			callout = period;		break;
	    }
          }
        }
      else
        {
        *log_msgptr = string_sprintf("'=' expected after \"callout\" in "
          "ACL condition \"%s\"", arg);
        return ERROR;
        }
      }
    }


  else
    {
    *log_msgptr = string_sprintf("unknown option \"%s\" in ACL "
      "condition \"verify %s\"", ss, arg);
    return ERROR;
    }
  }

if ((verify_options & (vopt_callout_recipsender|vopt_callout_recippmaster)) ==
      (vopt_callout_recipsender|vopt_callout_recippmaster))
  {
  *log_msgptr = US"only one of use_sender and use_postmaster can be set "
    "for a recipient callout";
  return ERROR;
  }


if (verify_header_sender)
  {
  int verrno;

  if ((rc = verify_check_header_address(user_msgptr, log_msgptr, callout,
    callout_overall, callout_connect, se_mailfrom, pm_mailfrom, verify_options,
    &verrno)) != OK)
    {
    *basic_errno = verrno;
    if (smtp_return_error_details)
      {
      if (!*user_msgptr && *log_msgptr)
        *user_msgptr = string_sprintf("Rejected after DATA: %s", *log_msgptr);
      if (rc == DEFER) f.acl_temp_details = TRUE;
      }
    }
  }


else if (verify_sender_address)
  {
  if ((verify_options & (vopt_callout_recipsender|vopt_callout_recippmaster)))
    {
    *log_msgptr = US"use_sender or use_postmaster cannot be used for a "
      "sender verify callout";
    return ERROR;
    }

  sender_vaddr = verify_checked_sender(verify_sender_address);
  if (sender_vaddr != NULL &&
      callout <= 0)
    {


    if (testflag(sender_vaddr, af_verify_routed))
      rc = OK;
    else
      {
      rc = sender_vaddr->special_action;
      *basic_errno = sender_vaddr->basic_errno;
      }
    HDEBUG(D_acl) debug_printf_indent("using cached sender verify result\n");
    }


  else
    {
    BOOL routed = TRUE;
    uschar *save_address_data = deliver_address_data;

    sender_vaddr = deliver_make_addr(verify_sender_address, TRUE);
#ifdef SUPPORT_I18N
    if ((sender_vaddr->prop.utf8_msg = message_smtputf8))
      {
      sender_vaddr->prop.utf8_downcvt =       message_utf8_downconvert == 1;
      sender_vaddr->prop.utf8_downcvt_maybe = message_utf8_downconvert == -1;
      }
#endif
    if (no_details) setflag(sender_vaddr, af_sverify_told);
    if (verify_sender_address[0] != 0)
      {


      if (verify_sender_address == sender_address)
        sender_address_unrewritten = sender_address;
      else
        verify_options |= vopt_fake_sender;

      if (success_on_redirect)
        verify_options |= vopt_success_on_redirect;


      rc = verify_address(sender_vaddr, NULL, verify_options, callout,
        callout_overall, callout_connect, se_mailfrom, pm_mailfrom, &routed);

      HDEBUG(D_acl) debug_printf_indent("----------- end verify ------------\n");

      if (rc != OK)
        *basic_errno = sender_vaddr->basic_errno;
      else
	DEBUG(D_acl)
	  {
	  if (Ustrcmp(sender_vaddr->address, verify_sender_address) != 0)
	    debug_printf_indent("sender %s verified ok as %s\n",
	      verify_sender_address, sender_vaddr->address);
	  else
	    debug_printf_indent("sender %s verified ok\n",
	      verify_sender_address);
	  }
      }
    else
      rc = OK;


    if (routed) setflag(sender_vaddr, af_verify_routed);
    if (callout > 0) setflag(sender_vaddr, af_verify_callout);
    sender_vaddr->special_action = rc;
    sender_vaddr->next = sender_verified_list;
    sender_verified_list = sender_vaddr;


    deliver_address_data = save_address_data;
    }


  sender_address_data = sender_vaddr->prop.address_data;
  }


else
  {
  address_item addr2;

  if (success_on_redirect)
    verify_options |= vopt_success_on_redirect;


  addr2 = *addr;
  rc = verify_address(&addr2, NULL, verify_options|vopt_is_recipient, callout,
    callout_overall, callout_connect, se_mailfrom, pm_mailfrom, NULL);
  HDEBUG(D_acl) debug_printf_indent("----------- end verify ------------\n");

  *basic_errno = addr2.basic_errno;
  *log_msgptr = addr2.message;
  *user_msgptr = (addr2.user_message != NULL)?
    addr2.user_message : addr2.message;


  if (testflag((&addr2), af_pass_message)) f.acl_temp_details = TRUE;


  deliver_address_data = addr2.prop.address_data;
  }


if (rc == DEFER && (defer_ok ||
   (callout_defer_ok && *basic_errno == ERRNO_CALLOUTDEFER)))
  {
  HDEBUG(D_acl) debug_printf_indent("verify defer overridden by %s\n",
    defer_ok? "defer_ok" : "callout_defer_ok");
  rc = OK;
  }


if (rc != OK && verify_sender_address != NULL)
  {
  if (rc != DEFER)
    *log_msgptr = *user_msgptr = US"Sender verify failed";
  else if (*basic_errno != ERRNO_CALLOUTDEFER)
    *log_msgptr = *user_msgptr = US"Could not complete sender verify";
  else
    {
    *log_msgptr = US"Could not complete sender verify callout";
    *user_msgptr = smtp_return_error_details? sender_vaddr->user_message :
      *log_msgptr;
    }

  sender_verified_failed = sender_vaddr;
  }


if (addr != NULL)
  {
  deliver_domain = addr->domain;
  deliver_localpart = addr->local_part;
  }
return rc;


BAD_VERIFY:
*log_msgptr = string_sprintf("expected \"sender[=address]\", \"recipient\", "
  "\"helo\", \"header_syntax\", \"header_sender\", \"header_names_ascii\" "
  "or \"reverse_host_lookup\" at start of ACL condition "
  "\"verify %s\"", arg);
return ERROR;
}
