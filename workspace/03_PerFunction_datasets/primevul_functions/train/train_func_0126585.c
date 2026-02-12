host_find_bydns(host_item *host, const uschar *ignore_target_hosts, int whichrrs,
  uschar *srv_service, uschar *srv_fail_domains, uschar *mx_fail_domains,
  const dnssec_domains *dnssec_d,
  const uschar **fully_qualified_name, BOOL *removed)
{
host_item *h, *last;
dns_record *rr;
int rc = DNS_FAIL;
int ind_type = 0;
int yield;
dns_answer dnsa;
dns_scan dnss;
BOOL dnssec_require = dnssec_d
		    && match_isinlist(host->name, CUSS &dnssec_d->require,
				    0, NULL, NULL, MCL_DOMAIN, TRUE, NULL) == OK;
BOOL dnssec_request = dnssec_require
		    || (  dnssec_d
		       && match_isinlist(host->name, CUSS &dnssec_d->request,
				    0, NULL, NULL, MCL_DOMAIN, TRUE, NULL) == OK);
dnssec_status_t dnssec;


if (fully_qualified_name != NULL) *fully_qualified_name = host->name;
dns_init((whichrrs & HOST_FIND_QUALIFY_SINGLE) != 0,
         (whichrrs & HOST_FIND_SEARCH_PARENTS) != 0,
	 dnssec_request);
f.host_find_failed_syntax = FALSE;


if (whichrrs & HOST_FIND_BY_SRV)
  {
  gstring * g;
  uschar * temp_fully_qualified_name;
  int prefix_length;

  g = string_fmt_append(NULL, "_%s._tcp.%n%.256s",
	srv_service, &prefix_length, host->name);
  temp_fully_qualified_name = string_from_gstring(g);
  ind_type = T_SRV;


  dnssec = DS_UNK;
  lookup_dnssec_authenticated = NULL;
  rc = dns_lookup_timerwrap(&dnsa, temp_fully_qualified_name, ind_type,
	CUSS &temp_fully_qualified_name);

  DEBUG(D_dns)
    if ((dnssec_request || dnssec_require)
	&& !dns_is_secure(&dnsa)
	&& dns_is_aa(&dnsa))
      debug_printf("DNS lookup of %.256s (SRV) requested AD, but got AA\n", host->name);

  if (dnssec_request)
    {
    if (dns_is_secure(&dnsa))
      { dnssec = DS_YES; lookup_dnssec_authenticated = US"yes"; }
    else
      { dnssec = DS_NO; lookup_dnssec_authenticated = US"no"; }
    }

  if (temp_fully_qualified_name != g->s && fully_qualified_name != NULL)
    *fully_qualified_name = temp_fully_qualified_name + prefix_length;


  if (rc == DNS_SUCCEED && dnssec_require && !dns_is_secure(&dnsa))
    {
    log_write(L_host_lookup_failed, LOG_MAIN,
		"dnssec fail on SRV for %.256s", host->name);
    rc = DNS_FAIL;
    }
  if (rc == DNS_FAIL || rc == DNS_AGAIN)
    {
    #ifndef STAND_ALONE
    if (match_isinlist(host->name, CUSS &srv_fail_domains, 0, NULL, NULL,
	MCL_DOMAIN, TRUE, NULL) != OK)
    #endif
      { yield = HOST_FIND_AGAIN; goto out; }
    DEBUG(D_host_lookup) debug_printf("DNS_%s treated as DNS_NODATA "
      "(domain in srv_fail_domains)\n", (rc == DNS_FAIL)? "FAIL":"AGAIN");
    }
  }


if (rc != DNS_SUCCEED  &&  whichrrs & HOST_FIND_BY_MX)
  {
  ind_type = T_MX;
  dnssec = DS_UNK;
  lookup_dnssec_authenticated = NULL;
  rc = dns_lookup_timerwrap(&dnsa, host->name, ind_type, fully_qualified_name);

  DEBUG(D_dns)
    if (  (dnssec_request || dnssec_require)
       && !dns_is_secure(&dnsa)
       && dns_is_aa(&dnsa))
      debug_printf("DNS lookup of %.256s (MX) requested AD, but got AA\n", host->name);

  if (dnssec_request)
    if (dns_is_secure(&dnsa))
      {
      DEBUG(D_host_lookup) debug_printf("%s MX DNSSEC\n", host->name);
      dnssec = DS_YES; lookup_dnssec_authenticated = US"yes";
      }
    else
      {
      dnssec = DS_NO; lookup_dnssec_authenticated = US"no";
      }

  switch (rc)
    {
    case DNS_NOMATCH:
      yield = HOST_FIND_FAILED; goto out;

    case DNS_SUCCEED:
      if (!dnssec_require || dns_is_secure(&dnsa))
	break;
      DEBUG(D_host_lookup)
	debug_printf("dnssec fail on MX for %.256s", host->name);
#ifndef STAND_ALONE
      if (match_isinlist(host->name, CUSS &mx_fail_domains, 0, NULL, NULL,
	  MCL_DOMAIN, TRUE, NULL) != OK)
	{ yield = HOST_FIND_SECURITY; goto out; }
#endif
      rc = DNS_FAIL;


    case DNS_FAIL:
    case DNS_AGAIN:
#ifndef STAND_ALONE
      if (match_isinlist(host->name, CUSS &mx_fail_domains, 0, NULL, NULL,
	  MCL_DOMAIN, TRUE, NULL) != OK)
#endif
	{ yield = HOST_FIND_AGAIN; goto out; }
      DEBUG(D_host_lookup) debug_printf("DNS_%s treated as DNS_NODATA "
	"(domain in mx_fail_domains)\n", (rc == DNS_FAIL)? "FAIL":"AGAIN");
      break;
    }
  }


if (rc != DNS_SUCCEED)
  {
  if (!(whichrrs & (HOST_FIND_BY_A | HOST_FIND_BY_AAAA)))
    {
    DEBUG(D_host_lookup) debug_printf("Address records are not being sought\n");
    yield = HOST_FIND_FAILED;
    goto out;
    }

  last = host;
  host->mx = MX_NONE;
  host->port = PORT_NONE;
  host->dnssec = DS_UNK;
  lookup_dnssec_authenticated = NULL;
  rc = set_address_from_dns(host, &last, ignore_target_hosts, FALSE,
    fully_qualified_name, dnssec_request, dnssec_require, whichrrs);


  if (rc == HOST_FOUND)
    rc = host_scan_for_local_hosts(host, &last, removed);
  else
    if (rc == HOST_IGNORED) rc = HOST_FIND_FAILED;

  DEBUG(D_host_lookup)
    {
    host_item *h;
    if (host->address != NULL)
      {
      if (fully_qualified_name != NULL)
        debug_printf("fully qualified name = %s\n", *fully_qualified_name);
      for (h = host; h != last->next; h = h->next)
        debug_printf("%s %s mx=%d sort=%d %s\n", h->name,
          (h->address == NULL)? US"<null>" : h->address, h->mx, h->sort_key,
          (h->status >= hstatus_unusable)? US"*" : US"");
      }
    }

  yield = rc;
  goto out;
  }


last = NULL;

for (rr = dns_next_rr(&dnsa, &dnss, RESET_ANSWERS);
     rr;
     rr = dns_next_rr(&dnsa, &dnss, RESET_NEXT)) if (rr->type == ind_type)
  {
  int precedence;
  int weight = 0;
  int port = PORT_NONE;
  const uschar * s = rr->data;
  uschar data[256];

  GETSHORT(precedence, s);


  if (ind_type == T_MX)
    weight = random_number(500);


  else
    {
    GETSHORT(weight, s);
    GETSHORT(port, s);
    }


  (void)dn_expand(dnsa.answer, dnsa.answer + dnsa.answerlen, s,
    (DN_EXPAND_ARG4_TYPE)data, sizeof(data));


  if (last != NULL)
    {
    host_item *prev = NULL;

    for (h = host; h != last->next; prev = h, h = h->next)
      {
      if (strcmpic(h->name, data) == 0)
        {
        DEBUG(D_host_lookup)
          debug_printf("discarded duplicate host %s (MX=%d)\n", data,
            (precedence > h->mx)? precedence : h->mx);
        if (precedence >= h->mx) goto NEXT_MX_RR;
        if (h == host)
          {
          h->mx = precedence;
          host->sort_key = precedence * 1000 + weight;
          goto NEXT_MX_RR;
          }


        prev->next = h->next;
        if (h == last) last = prev;
        break;
        }
      }
    }


  if (!last)
    {
    host->name = string_copy_dnsdomain(data);
    host->address = NULL;
    host->port = port;
    host->mx = precedence;
    host->sort_key = precedence * 1000 + weight;
    host->status = hstatus_unknown;
    host->why = hwhy_unknown;
    host->dnssec = dnssec;
    last = host;
    }


  else
    {
    int sort_key = precedence * 1000 + weight;
    host_item *next = store_get(sizeof(host_item));
    next->name = string_copy_dnsdomain(data);
    next->address = NULL;
    next->port = port;
    next->mx = precedence;
    next->sort_key = sort_key;
    next->status = hstatus_unknown;
    next->why = hwhy_unknown;
    next->dnssec = dnssec;
    next->last_try = 0;


    if (sort_key < host->sort_key)
      {
      host_item htemp;
      htemp = *host;
      *host = *next;
      *next = htemp;
      host->next = next;
      if (last == host) last = next;
      }


    else
      {
      for (h = host; h != last; h = h->next)
        {
        if (sort_key < h->next->sort_key)
          {
          next->next = h->next;
          h->next = next;
          break;
          }
        }


      if (h == last)
        {
        next->next = last->next;
        last->next = next;
        last = next;
        }
      }
    }

  NEXT_MX_RR: continue;
  }

if (!last)
  {
  yield = HOST_FIND_FAILED;
  goto out;
  }


if (ind_type == T_SRV)
  {
  host_item **pptr;

  if (host == last && host->name[0] == 0)
    {
    DEBUG(D_host_lookup) debug_printf("the single SRV record is \".\"\n");
    yield = HOST_FIND_FAILED;
    goto out;
    }

  DEBUG(D_host_lookup)
    {
    debug_printf("original ordering of hosts from SRV records:\n");
    for (h = host; h != last->next; h = h->next)
      debug_printf("  %s P=%d W=%d\n", h->name, h->mx, h->sort_key % 1000);
    }

  for (pptr = &host, h = host; h != last; pptr = &h->next, h = h->next)
    {
    int sum = 0;
    host_item *hh;


    for (hh = h; hh != last; hh = hh->next)
      {
      int weight = hh->sort_key % 1000;
      sum += weight;
      hh->sort_key = sum;
      if (hh->mx != hh->next->mx) break;
      }


    if (hh != h)
      {
      host_item *hhh;
      host_item **ppptr;
      int randomizer = random_number(sum + 1);

      for (ppptr = pptr, hhh = h;
           hhh != hh;
           ppptr = &(hhh->next), hhh = hhh->next)
        {
        if (hhh->sort_key >= randomizer) break;
        }


      if (hhh != h)
        {
        *ppptr = hhh->next;

        if (h == host)
          {
          host_item temp = *h;
          *h = *hhh;
          *hhh = temp;
          hhh->next = temp.next;
          h->next = hhh;
          }

        else
          {
          hhh->next = h;
          *pptr = hhh;
          h = hhh;
          }
        }
      }


    h->sort_key = h->mx * 1000 + random_number(500);
    }
  }


yield = HOST_FIND_FAILED;
dns_init(FALSE, FALSE,
	 dnssec_request || dnssec_require);

for (h = host; h != last->next; h = h->next)
  {
  if (h->address) continue;

  rc = set_address_from_dns(h, &last, ignore_target_hosts, allow_mx_to_ip,
    NULL, dnssec_request, dnssec_require,
    whichrrs & HOST_FIND_IPV4_ONLY
    ?  HOST_FIND_BY_A  :  HOST_FIND_BY_A | HOST_FIND_BY_AAAA);
  if (rc != HOST_FOUND)
    {
    h->status = hstatus_unusable;
    switch (rc)
      {
      case HOST_FIND_AGAIN:	yield = rc; h->why = hwhy_deferred; break;
      case HOST_FIND_SECURITY:	yield = rc; h->why = hwhy_insecure; break;
      case HOST_IGNORED:	h->why = hwhy_ignored; break;
      default:			h->why = hwhy_failed; break;
      }
    }
  }


if (ignore_target_hosts)
  {
  host_item *prev = NULL;
  for (h = host; h != last->next; h = h->next)
    {
    REDO:
    if (h->why != hwhy_ignored)
      prev = h;
    else if (prev == NULL)
      {
      if (h != last)
        {
        if (h->next == last) last = h;
        *h = *(h->next);
        goto REDO;
        }
      }
    else
      {
      prev->next = h->next;
      if (h == last) last = prev;
      }
    }

  if (host->why == hwhy_ignored) host->address = NULL;
  }


#if HAVE_IPV6
if (h != last && !disable_ipv6) for (h = host; h != last; h = h->next)
  {
  host_item temp;
  host_item *next = h->next;

  if (  h->mx != next->mx
     || !h->address
     )
    continue;

  if (  whichrrs & HOST_FIND_IPV4_FIRST
     ?     !Ustrchr(h->address, ':')
        || next->address
           && Ustrchr(next->address, ':')

     :     Ustrchr(h->address, ':')
        || next->address
           && !Ustrchr(next->address, ':')
     )
    continue;

  temp = *h;
  temp.next = next->next;
  *h = *next;
  h->next = next;
  *next = temp;
  }
#endif


host_remove_duplicates(host, &last);
rc = host_scan_for_local_hosts(host, &last, removed);
if (rc != HOST_FIND_FAILED) yield = rc;

DEBUG(D_host_lookup)
  {
  if (fully_qualified_name != NULL)
    debug_printf("fully qualified name = %s\n", *fully_qualified_name);
  debug_printf("host_find_bydns yield = %s (%d); returned hosts:\n",
    (yield == HOST_FOUND)? "HOST_FOUND" :
    (yield == HOST_FOUND_LOCAL)? "HOST_FOUND_LOCAL" :
    (yield == HOST_FIND_SECURITY)? "HOST_FIND_SECURITY" :
    (yield == HOST_FIND_AGAIN)? "HOST_FIND_AGAIN" :
    (yield == HOST_FIND_FAILED)? "HOST_FIND_FAILED" : "?",
    yield);
  for (h = host; h != last->next; h = h->next)
    {
    debug_printf("  %s %s MX=%d %s", h->name,
      !h->address ? US"<null>" : h->address, h->mx,
      h->dnssec == DS_YES ? US"DNSSEC " : US"");
    if (h->port != PORT_NONE) debug_printf("port=%d ", h->port);
    if (h->status >= hstatus_unusable) debug_printf("*");
    debug_printf("\n");
    }
  }

out:

dns_init(FALSE, FALSE, FALSE);
return yield;
}
