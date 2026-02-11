expand_enter (struct servtab *sep)
{
  int err;
  struct addrinfo *result, *rp;
  struct protoent *proto;
  struct servtab *cp;


  if (strncmp (sep->se_proto, "tcp", 3) == 0)
    proto = getprotobyname ("tcp");
  else if (strncmp (sep->se_proto, "udp", 3) == 0)
    proto = getprotobyname ("udp");
  else
    proto = getprotobyname (sep->se_proto);

  if (!proto)
    {
      syslog (LOG_ERR, "%s: Unknown protocol", sep->se_proto);
      return 1;
    }

  err = inetd_getaddrinfo (sep, proto->p_proto, &result);
#if IPV6
  if (err == EAI_ADDRFAMILY
      && sep->se_family == AF_INET6 && sep->se_v4mapped)
    {

      sep->se_family = AF_INET;
      err = inetd_getaddrinfo (sep, proto->p_proto, &result);
    }
#endif
  if (err)
    {
      const char *errmsg;

      if (err == EAI_SYSTEM)
	errmsg = strerror (errno);
      else
	errmsg = gai_strerror (err);

      if (sep->se_node)
	{
	  if (debug)
	    fprintf (stderr, "resolution of %s %s/%s failed: %s\n",
		     sep->se_node, sep->se_service, sep->se_proto, errmsg);
	  syslog (LOG_ERR, "%s %s/%s: getaddrinfo: %s",
		  sep->se_node, sep->se_service, sep->se_proto, errmsg);
	}
      else
	{
	  if (debug)
	    fprintf (stderr, "resolution of %s/%s failed: %s\n",
		     sep->se_service, sep->se_proto, errmsg);
	  syslog (LOG_ERR, "%s/%s: getaddrinfo: %s",
		  sep->se_service, sep->se_proto, errmsg);
	}
      return 1;
    }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      memset (&sep->se_ctrladdr, 0, sizeof (sep->se_ctrladdr));
      memcpy (&sep->se_ctrladdr, rp->ai_addr, rp->ai_addrlen);
      sep->se_addrlen = rp->ai_addrlen;
      cp = enter (sep);
      servent_setup (cp);
    }

  freeaddrinfo (result);

  return 0;
}
