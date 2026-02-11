main(int argc, char *argv[])
{
#ifdef HAVE_IPV6
    int i;
    for (i = 1; i < argc; i++) {
	struct addrinfo hints, *res, *aii;
	int x;

	if (i > 1)
	    printf("\n");
	printf("=== argument %s ===\n", argv[i]);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	x = getaddrinfo(argv[i], NULL, &hints, &res);
	if (x) {
	    fprintf(stderr, "getaddrinfo \"%s\" failure: %s\n", argv[i], gai_strerror(x));
	    continue;
	}

	for (aii = res; aii != NULL; aii=aii->ai_next) {
	    printf("--> at position %p got address ", (void *)aii);
	    pat(aii->ai_addr);
	    memcpy(&tstaddr, aii->ai_addr, aii->ai_addrlen);
	    x = checkpeerlocal(0);
	    printf("checkpeerlocal(\"%s\") returns %d%s%s\n", argv[i], x, x == -1 ? " " : "", x == -1 ? gai_strerror(x) : "");
	}

	freeaddrinfo(res);
    }
#else
    int r;
    (void)argc; (void)argv;
    printf("checkpeerlocal returned: %d\n", (r = checkpeerlocal(0)));
    if (r == -1) printf("errno: %d (%s)\n", errno, strerror(errno));
#endif
    return 0;
}
