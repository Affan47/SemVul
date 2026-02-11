lookup_host(struct s_whois_query *wq, const char *block)
{
  char deepfreeze[512];
  char *tmpdeep, *tmphost;
  struct jconfig *j;
  char *ret;

  if (!wq->query) return -1;
  if (!block)
    strcpy(deepfreeze, "jwhois|whois-servers");
  else
    sprintf(deepfreeze, "jwhois|%s", block);

  jconfig_set();
  j = jconfig_getone("jwhois", "whois-servers-domain");
  if (!j)
    whoisservers = WHOISSERVERS;
  else
    whoisservers = j->value;

  jconfig_set();
  j = jconfig_getone(deepfreeze, "type");
  if (!j || strncasecmp(j->value, "regex", 5) == 0)
    wq->host = find_regex(wq, deepfreeze);
  else if (strncasecmp(j->value, "cidr6", 5) == 0) {
#ifdef HAVE_INET_PTON_IPV6
    wq->host = find_cidr6(wq, deepfreeze);
#else
    printf("[%s]\n", _("Warning: Configuration file contains references to IPv6,"));
    printf("[%s]\n", _("         but jwhois was compiled without IPv6 support."));
#endif
  } else
    wq->host = find_cidr(wq, deepfreeze);

  if (!wq->host) wq->host = DEFAULTHOST;

  if (strncasecmp(wq->host, "struct", 6) == 0) {
    tmpdeep = wq->host+7;
    return lookup_host(wq, tmpdeep);
  }

  if (enable_whoisservers)
    if (strncasecmp(wq->host, "whois-servers", 13) == 0) {
      printf("[%s %s]\n", _("Querying"), whoisservers);
      return lookup_whois_servers(wq->query, wq);
    }

  wq->port = 0;
  if (strchr(wq->host, ' '))
    {
      tmphost = (char *)strchr(wq->host, ' ');
#ifdef HAVE_STRTOL
      wq->port = strtol((char *)(tmphost+1), &ret, 10);
      if (*ret != '\0')
	{
	  return -1;
	}
#else
      wq->port = atoi((char *)(tmphost+1));
#endif
      *tmphost = '\0';
    }
  return 0;
}
