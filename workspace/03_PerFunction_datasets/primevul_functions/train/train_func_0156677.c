set_address_from_dns(host_item *host, host_item **lastptr,
  const uschar *ignore_target_hosts, BOOL allow_ip,
  const uschar **fully_qualified_name,
  BOOL dnssec_request, BOOL dnssec_require, int whichrrs)
{
host_item *thishostlast = NULL;
BOOL v6_find_again = FALSE;
BOOL dnssec_fail = FALSE;
int i;
dns_answer * dnsa;

#ifndef DISABLE_TLS


host->certname = host->name;
#endif


if (allow_ip && string_is_ip_address(host->name, NULL) != 0)
  {
  #ifndef STAND_ALONE
  if (  ignore_target_hosts
     && verify_check_this_host(&ignore_target_hosts, NULL, host->name,
        host->name, NULL) == OK)
    return HOST_IGNORED;
  #endif

  host->address = host->name;
  return HOST_FOUND;
  }

dnsa = store_get_dns_answer();


#if HAVE_IPV6
  #ifndef STAND_ALONE
    if (  disable_ipv6
       || !(whichrrs & HOST_FIND_BY_AAAA)
       ||    dns_ipv4_lookup
          && match_isinlist(host->name, CUSS &dns_ipv4_lookup, 0,
	      &domainlist_anchor, NULL, MCL_DOMAIN, TRUE, NULL) == OK
       )
      i = 0;
    else
  #endif

  i = 1;


#else
  i = 0;
#endif

for (; i >= 0; i--)
  {
  static int types[] = { T_A, T_AAAA };
  int type = types[i];
  int randoffset = i == (whichrrs & HOST_FIND_IPV4_FIRST ? 1 : 0)
    ? 500 : 0;
  dns_scan dnss;

  int rc = dns_lookup_timerwrap(dnsa, host->name, type, fully_qualified_name);
  lookup_dnssec_authenticated = !dnssec_request ? NULL
    : dns_is_secure(dnsa) ? US"yes" : US"no";

  DEBUG(D_dns)
    if (  (dnssec_request || dnssec_require)
       && !dns_is_secure(dnsa)
       && dns_is_aa(dnsa)
       )
      debug_printf("DNS lookup of %.256s (A/AAAA) requested AD, but got AA\n", host->name);


  if (rc != DNS_SUCCEED)
    {
    if (i == 0)
      {
      if (host->address != NULL)
        i = HOST_FOUND;
      else if (rc == DNS_AGAIN || rc == DNS_FAIL || v6_find_again)
        i = HOST_FIND_AGAIN;
      else
	i = HOST_FIND_FAILED;
      goto out;
      }


    if (rc != DNS_NOMATCH && rc != DNS_NODATA) v6_find_again = TRUE;
    continue;
    }

  if (dnssec_request)
    {
    if (dns_is_secure(dnsa))
      {
      DEBUG(D_host_lookup) debug_printf("%s A DNSSEC\n", host->name);
      if (host->dnssec == DS_UNK)
	host->dnssec = DS_YES;
      }
    else
      {
      if (dnssec_require)
	{
	dnssec_fail = TRUE;
	DEBUG(D_host_lookup) debug_printf("dnssec fail on %s for %.256s",
		i>0 ? "AAAA" : "A", host->name);
	continue;
	}
      if (host->dnssec == DS_YES)
	{
	DEBUG(D_host_lookup) debug_printf("%s A cancel DNSSEC\n", host->name);
	host->dnssec = DS_NO;
	lookup_dnssec_authenticated = US"no";
	}
      }
    }


  fully_qualified_name = NULL;

  for (dns_record * rr = dns_next_rr(dnsa, &dnss, RESET_ANSWERS);
       rr;
       rr = dns_next_rr(dnsa, &dnss, RESET_NEXT)) if (rr->type == type)
    {
    dns_address * da = dns_address_from_rr(dnsa, rr);

    DEBUG(D_host_lookup)
      if (!da) debug_printf("no addresses extracted from A6 RR for %s\n",
	  host->name);


    for (; da; da = da->next)
      {
      #ifndef STAND_ALONE
      if (ignore_target_hosts != NULL &&
	    verify_check_this_host(&ignore_target_hosts, NULL,
	      host->name, da->address, NULL) == OK)
	{
	DEBUG(D_host_lookup)
	  debug_printf("ignored host %s [%s]\n", host->name, da->address);
	continue;
	}
      #endif


      if (thishostlast == NULL)
	{
	if (strcmpic(host->name, rr->name) != 0)
	  host->name = string_copy_dnsdomain(rr->name);
	host->address = da->address;
	host->sort_key = host->mx * 1000 + random_number(500) + randoffset;
	host->status = hstatus_unknown;
	host->why = hwhy_unknown;
	thishostlast = host;
	}


      else
	{
	int new_sort_key;
	host_item *next;


	for (next = host;; next = next->next)
	  {
	  if (Ustrcmp(CS da->address, next->address) == 0) break;
	  if (next == thishostlast) { next = NULL; break; }
	  }
	if (next != NULL) continue;


	new_sort_key = host->mx * 1000 + random_number(500) + randoffset;
	next = store_get(sizeof(host_item), FALSE);


	if (new_sort_key < host->sort_key)
	  {
	  *next = *host;
	  host->next = next;
	  host->address = da->address;
	  host->sort_key = new_sort_key;
	  if (thishostlast == host) thishostlast = next;
	  if (*lastptr == host) *lastptr = next;
	  }


	else
	  {
	  host_item *h = host;
	  while (h != thishostlast)
	    {
	    if (new_sort_key < h->next->sort_key) break;
	    h = h->next;
	    }
	  *next = *h;
	  h->next = next;
	  next->address = da->address;
	  next->sort_key = new_sort_key;
	  if (h == thishostlast) thishostlast = next;
	  if (h == *lastptr) *lastptr = next;
	  }
	}
      }
    }
  }


i = host->address
  ? HOST_FOUND
  : dnssec_fail
  ? HOST_FIND_SECURITY
  : HOST_IGNORED;

out:
  store_free_dns_answer(dnsa);
  return i;
}
