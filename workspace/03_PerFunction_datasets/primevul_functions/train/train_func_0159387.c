add_acl_headers(int where, uschar *acl_name)
{
header_line *h, *next;
header_line *last_received = NULL;

switch(where)
  {
  case ACL_WHERE_DKIM:
  case ACL_WHERE_MIME:
  case ACL_WHERE_DATA:
    if (  cutthrough.fd >= 0 && cutthrough.delivery
       && (acl_removed_headers || acl_added_headers))
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "Header modification in data ACLs"
			" will not take effect on cutthrough deliveries");
    return;
    }
  }

if (acl_removed_headers)
  {
  DEBUG(D_receive|D_acl) debug_printf_indent(">>Headers removed by %s ACL:\n", acl_name);

  for (h = header_list; h; h = h->next) if (h->type != htype_old)
    {
    const uschar * list = acl_removed_headers;
    int sep = ':';
    uschar *s;
    uschar buffer[128];

    while ((s = string_nextinlist(&list, &sep, buffer, sizeof(buffer))))
      if (header_testname(h, s, Ustrlen(s), FALSE))
	{
	h->type = htype_old;
        DEBUG(D_receive|D_acl) debug_printf_indent("  %s", h->text);
	}
    }
  acl_removed_headers = NULL;
  DEBUG(D_receive|D_acl) debug_printf_indent(">>\n");
  }

if (!acl_added_headers) return;
DEBUG(D_receive|D_acl) debug_printf_indent(">>Headers added by %s ACL:\n", acl_name);

for (h = acl_added_headers; h; h = next)
  {
  next = h->next;

  switch(h->type)
    {
    case htype_add_top:
    h->next = header_list;
    header_list = h;
    DEBUG(D_receive|D_acl) debug_printf_indent("  (at top)");
    break;

    case htype_add_rec:
    if (last_received == NULL)
      {
      last_received = header_list;
      while (!header_testname(last_received, US"Received", 8, FALSE))
        last_received = last_received->next;
      while (last_received->next != NULL &&
             header_testname(last_received->next, US"Received", 8, FALSE))
        last_received = last_received->next;
      }
    h->next = last_received->next;
    last_received->next = h;
    DEBUG(D_receive|D_acl) debug_printf_indent("  (after Received:)");
    break;

    case htype_add_rfc:

    last_received = header_list;
    while ( (last_received->next != NULL) &&
            ( (header_testname(last_received->next, US"Received", 8, FALSE)) ||
              (header_testname_incomplete(last_received->next, US"Resent-", 7, FALSE)) ) )
              last_received = last_received->next;


    h->next = last_received->next;
    last_received->next = h;
    DEBUG(D_receive|D_acl) debug_printf_indent("  (before any non-Received: or Resent-*: header)");
    break;

    default:
    h->next = NULL;
    header_last->next = h;
    break;
    }

  if (h->next == NULL) header_last = h;


  h->type = header_checkname(h, FALSE);
  if (h->type >= 'a') h->type = htype_other;

  DEBUG(D_receive|D_acl) debug_printf_indent("  %s", header_last->text);
  }

acl_added_headers = NULL;
DEBUG(D_receive|D_acl) debug_printf_indent(">>\n");
}
