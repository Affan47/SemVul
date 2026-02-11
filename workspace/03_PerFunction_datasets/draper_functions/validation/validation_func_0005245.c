main(int argc, char **argv) {
  fd_set readset, errorset;
  int max_fd;

  memset(&id_addr_queue, 0, sizeof(id_addr_queue));
  memset(&delay_queue, 0, sizeof(delay_queue));
  if (0 != parse_args(argc, argv))
    return EXIT_FAILURE;
  if (0 != parse_ip_list())
    return EXIT_FAILURE;
  if (0 != parse_chnroute())
    return EXIT_FAILURE;
  if (0 != resolve_dns_servers())
    return EXIT_FAILURE;
  if (0 != dns_init_sockets())
    return EXIT_FAILURE;

  printf("%s\n", version);
  max_fd = MAX(local_sock, remote_sock) + 1;
  while (1) {
    FD_ZERO(&readset);
    FD_ZERO(&errorset);
    FD_SET(local_sock, &readset);
    FD_SET(local_sock, &errorset);
    FD_SET(remote_sock, &readset);
    FD_SET(remote_sock, &errorset);
    struct timeval timeout = {
      .tv_sec = 1,
      .tv_usec = 0,
    };
    if (-1 == select(max_fd, &readset, NULL, &errorset, &timeout)) {
      ERR("select");
      return EXIT_FAILURE;
    }
    check_and_send_delay();
    if (FD_ISSET(local_sock, &errorset)) {

      VERR("local_sock error\n");
      return EXIT_FAILURE;
    }
    if (FD_ISSET(remote_sock, &errorset)) {

      VERR("remote_sock error\n");
      return EXIT_FAILURE;
    }
    if (FD_ISSET(local_sock, &readset))
      dns_handle_local();
    if (FD_ISSET(remote_sock, &readset))
      dns_handle_remote();
  }
  return EXIT_SUCCESS;
}
