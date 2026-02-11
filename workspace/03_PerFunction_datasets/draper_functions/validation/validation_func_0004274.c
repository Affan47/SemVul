adns_globalsystemfailure(adns_state ads) {
  adns__consistency(ads,0,cc_entex);

  while (ads->udpw.head) adns__query_fail(ads->udpw.head, adns_s_systemfail);
  while (ads->tcpw.head) adns__query_fail(ads->tcpw.head, adns_s_systemfail);

  switch (ads->tcpstate) {
  case server_connecting:
  case server_ok:
    adns__tcp_broken(ads,0,0);
    break;
  case server_disconnected:
  case server_broken:
    break;
  default:
    abort();
  }
  adns__consistency(ads,0,cc_entex);
}
