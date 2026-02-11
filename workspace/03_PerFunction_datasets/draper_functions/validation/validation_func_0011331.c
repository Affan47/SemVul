main(int argc, char *argv[]) {
  char           *address = NULL;
  unsigned short port = 1500;
  int            retval = EXIT_SUCCESS, quiet = 0;


  int c;
  while ((c = getopt(argc, argv, "hs:p:b:t:q")) >= 0) {
    switch (c) {
    case 's':
      if (address != NULL)
        free(address);

      address = strdup(optarg);
      break;

    case 'p':
      port = atoi(optarg);
      break;

    case 'b':
      buffer_size = (unsigned short)atoi(optarg);
      break;

    case 'q':
      quiet = 1;
      break;

    case 'h':
    default:
      usage();
      retval = EXIT_SUCCESS;
      goto exit;
    }
  }


  fec_rb_init(buffer_size);

  if (address == NULL) {
#ifdef WITH_IPV6
    address = strdup("ff02::4");
#else
    address = strdup("0.0.0.0");
#endif
  }


  int sock;
#ifdef WITH_IPV6
  sock = net_udp6_recv_socket(address, port);
#else
  sock = net_udp4_recv_socket(address, port);
#endif
  if (sock < 0) {
    fprintf(stderr, "Could not open socket\n");
    retval = EXIT_FAILURE;
    goto exit;
  }

  if (!pob_mainloop(sock, quiet))
    retval = EXIT_FAILURE;

  if (close(sock) < 0)
    perror("close");

 exit:
  fec_rb_destroy();

  if (address != NULL)
    free(address);

  return retval;
}
