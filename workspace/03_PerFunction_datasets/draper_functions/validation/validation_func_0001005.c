dolog (struct sockaddr *sa, socklen_t salen, struct credentials *pcred)
{
  (void) getnameinfo (sa, salen, addrstr, sizeof (addrstr), NULL, 0, 0);

  free (pcred->remotehost);
  pcred->remotehost = sgetsave (addrstr);

#ifdef HAVE_SETPROCTITLE
  snprintf (proctitle, sizeof (proctitle), "%s: connected",
	    pcred->remotehost);
  setproctitle ("%s", proctitle);
#endif

  if (logging)
    syslog (LOG_INFO, "connection from %s", pcred->remotehost);
}
