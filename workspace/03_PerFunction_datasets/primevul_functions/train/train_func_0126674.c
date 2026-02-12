acl_check(int where, uschar *recipient, uschar *s, uschar **user_msgptr,
  uschar **log_msgptr)
{
int rc;
address_item adb;
address_item *addr = NULL;

*user_msgptr = *log_msgptr = NULL;
sender_verified_failed = NULL;
ratelimiters_cmd = NULL;
log_reject_target = LOG_MAIN|LOG_REJECT;

#ifndef DISABLE_PRDR
if (where==ACL_WHERE_RCPT || where==ACL_WHERE_VRFY || where==ACL_WHERE_PRDR)
#else
if (where==ACL_WHERE_RCPT || where==ACL_WHERE_VRFY)
#endif
  {
  adb = address_defaults;
  addr = &adb;
  addr->address = recipient;
  if (deliver_split_address(addr) == DEFER)
    {
    *log_msgptr = US"defer in percent_hack_domains check";
    return DEFER;
    }
#ifdef SUPPORT_I18N
  if ((addr->prop.utf8_msg = message_smtputf8))
    {
    addr->prop.utf8_downcvt =       message_utf8_downconvert == 1;
    addr->prop.utf8_downcvt_maybe = message_utf8_downconvert == -1;
    }
#endif
  deliver_domain = addr->domain;
  deliver_localpart = addr->local_part;
  }

acl_where = where;
acl_level = 0;
rc = acl_check_internal(where, addr, s, user_msgptr, log_msgptr);
acl_level = 0;
acl_where = ACL_WHERE_UNKNOWN;


switch (where)
  {
  case ACL_WHERE_RCPT:
#ifndef DISABLE_PRDR
  case ACL_WHERE_PRDR:
#endif

    if (f.host_checking_callout)
      cancel_cutthrough_connection(TRUE, US"host-checking mode");

    else if (  rc == OK
	    && cutthrough.delivery
	    && rcpt_count > cutthrough.nrcpt
	    )
      {
      if ((rc = open_cutthrough_connection(addr)) == DEFER)
	if (cutthrough.defer_pass)
	  {
	  uschar * s = addr->message;

	  while (*s) s++;
	  do --s; while (!isdigit(*s));
	  if (*--s && isdigit(*s) && *--s && isdigit(*s)) *user_msgptr = s;
	  f.acl_temp_details = TRUE;
	  }
	else
	  {
	  HDEBUG(D_acl) debug_printf_indent("cutthrough defer; will spool\n");
	  rc = OK;
	  }
      }
    else HDEBUG(D_acl) if (cutthrough.delivery)
      if (rcpt_count <= cutthrough.nrcpt)
	debug_printf_indent("ignore cutthrough request; nonfirst message\n");
      else if (rc != OK)
	debug_printf_indent("ignore cutthrough request; ACL did not accept\n");
    break;

  case ACL_WHERE_PREDATA:
    if (rc == OK)
      cutthrough_predata();
    else
      cancel_cutthrough_connection(TRUE, US"predata acl not ok");
    break;

  case ACL_WHERE_QUIT:
  case ACL_WHERE_NOTQUIT:


    {
    uschar prev = smtp_connection_had[smtp_ch_index-2];
    BOOL dropverify = !(prev == SCH_DATA || prev == SCH_BDAT);

    cancel_cutthrough_connection(dropverify, US"quit or conndrop");
    break;
    }

  default:
    break;
  }

deliver_domain = deliver_localpart = deliver_address_data =
  deliver_domain_data = sender_address_data = NULL;


if (rc == DISCARD)
  {
  if (where > ACL_WHERE_NOTSMTP || where == ACL_WHERE_PREDATA)
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "\"discard\" verb not allowed in %s "
      "ACL", acl_wherenames[where]);
    return ERROR;
    }
  return DISCARD;
  }


if (rc == FAIL_DROP && where == ACL_WHERE_MAILAUTH)
  {
  log_write(0, LOG_MAIN|LOG_PANIC, "\"drop\" verb not allowed in %s "
    "ACL", acl_wherenames[where]);
  return ERROR;
  }


*user_msgptr = string_split_message(*user_msgptr);
if (fake_response != OK)
  fake_response_text = string_split_message(fake_response_text);

return rc;
}
