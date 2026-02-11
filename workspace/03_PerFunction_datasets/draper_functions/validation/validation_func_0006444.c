eof_dns_socket(int idx)
{
  putlog(LOG_MISC, "*", "DNS Error: socket closed.");
  killsock(dcc[idx].sock);

  if (init_dns_network()) {
    putlog(LOG_MISC, "*", "DNS socket successfully reopened!");
    dcc[idx].sock = resfd;
    dcc[idx].timeval = now;
  } else
    lostdcc(idx);
}
