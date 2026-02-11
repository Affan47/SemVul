service_ldap(char *ip, int sp, unsigned char options, char *miscptr, FILE * fp, int port, char version, int auth_method) {
  int run = 1, next_run = 1, sock = -1;
  int myport = PORT_LDAP, mysslport = PORT_LDAP_SSL;

  hydra_register_socket(sp);
  if (memcmp(hydra_get_next_pair(), &HYDRA_EXIT, sizeof(HYDRA_EXIT)) == 0)
    return;
  while (1) {
    switch (run) {
    case 1:
      if (sock >= 0)
        sock = hydra_disconnect(sock);

      if ((options & OPTION_SSL) == 0) {
        if (port != 0)
          myport = port;
        sock = hydra_connect_tcp(ip, myport);
        port = myport;
      } else {
        if (port != 0)
          mysslport = port;
        sock = hydra_connect_ssl(ip, mysslport);
        port = mysslport;
      }
      if (sock < 0) {
        if (verbose || debug)
          hydra_report(stderr, "[ERROR] Child with pid %d terminating, can not connect\n", (int) getpid());
        hydra_child_exit(1);
      }
      counter = 1;
      if (tls_required) {

        char confidentiality_required[] = "\x30\x1d\x02\x01\x01\x77\x18\x80\x16\x31\x2e\x33\x2e\x36\x2e\x31\x2e\x34\x2e\x31\x2e\x31\x34\x36\x36\x2e\x32\x30\x30\x33\x37";

        if (hydra_send(sock, confidentiality_required, strlen(confidentiality_required), 0) < 0)
          hydra_child_exit(1);

        if ((buf = (unsigned char *) hydra_receive_line(sock)) == NULL)
          hydra_child_exit(1);

        if ((buf[0] != 0 && buf[9] == 0) || (buf[0] != 32 && buf[9] == 32)) {

          if ((hydra_connect_to_ssl(sock) == -1) && verbose) {
            hydra_report(stderr, "[ERROR] Can't use TLS\n");
            hydra_child_exit(1);
          } else {
            if (verbose)
              hydra_report(stderr, "[VERBOSE] TLS connection done\n");
            counter++;
          }
        } else {
          hydra_report(stderr, "[ERROR] Can't use TLS %s\n", buf);
          hydra_child_exit(1);
        }
      }
      next_run = 2;
      break;
    case 2:
      next_run = start_ldap(sock, ip, port, options, miscptr, fp, version, auth_method);
      counter++;
      break;
    case 3:
      if (sock >= 0)
        sock = hydra_disconnect(sock);
      hydra_child_exit(0);
      return;
    default:
      hydra_report(stderr, "[ERROR] Caught unknown return code, exiting!\n");
      hydra_child_exit(2);
    }
    run = next_run;
  }
}
