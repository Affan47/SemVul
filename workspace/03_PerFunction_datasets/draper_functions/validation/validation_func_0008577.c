main(int argc, char *argv[])
{
  int size;
  char *buf;
  int64_t count, i, delta;
  struct timeval start, stop;

  ssize_t len;
  size_t sofar;

  int yes = 1;
  int ret;
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints;
  struct addrinfo *res;
  int sockfd, new_fd;

  if (argc != 5) {
    printf ("usage: tcp_local_lat <bind-to> <port> <message-size> <roundtrip-count>\n");
    return 1;
  }

  size = atoi(argv[3]);
  count = atol(argv[4]);

  buf = malloc(size);
  if (buf == NULL) {
    perror("malloc");
    return 1;
  }

  printf("message size: %i octets\n", size);
  printf("roundtrip count: %lli\n", count);

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  if ((ret = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
    return 1;
  }

  if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
    perror("socket");
    exit(1);
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
    perror("bind");
    exit(1);
  }

  if (listen(sockfd, 1) == -1) {
    perror("listen");
    exit(1);
  }

  addr_size = sizeof their_addr;

  if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size)) == -1) {
    perror("accept");
    exit(1);
  }

  for (i = 0; i < count; i++) {

    for (sofar = 0; sofar < size; ) {
      len = read(new_fd, buf, size - sofar);
      if (len == -1) {
	perror("read");
	return 1;
      }
      sofar += len;
    }

    if (write(new_fd, buf, size) != size) {
      perror("write");
      return 1;
    }
  }

  return 0;
}
