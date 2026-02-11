print_host(const char *hostname, const char *header)
{


	struct addrinfo *result = NULL;
	int rc;
	struct addrinfo hint;

	memset(&hint, 0 , sizeof(hint));


	hint.ai_socktype = SOCK_STREAM;

	rc = getaddrinfo(hostname, NULL , &hint, &result);

	if (!rc) {
		struct addrinfo *cur = result;
		unsigned cnt = 0;

		printf("%-10s %s\n", header, hostname);

		while (cur) {
			char *dotted, *revhost;
			dotted = xmalloc_sockaddr2dotted_noport(cur->ai_addr);
			revhost = xmalloc_sockaddr2hostonly_noport(cur->ai_addr);

			printf("Address %u: %s%c", ++cnt, dotted, revhost ? ' ' : '\n');
			if (revhost) {
				puts(revhost);
				if (ENABLE_FEATURE_CLEAN_UP)
					free(revhost);
			}
			if (ENABLE_FEATURE_CLEAN_UP)
				free(dotted);
			cur = cur->ai_next;
		}
	} else {
#if ENABLE_VERBOSE_RESOLUTION_ERRORS
		bb_error_msg("can't resolve '%s': %s", hostname, gai_strerror(rc));
#else
		bb_error_msg("can't resolve '%s'", hostname);
#endif
	}
	if (ENABLE_FEATURE_CLEAN_UP)
		freeaddrinfo(result);
	return (rc != 0);
}
