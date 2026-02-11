show_settings(isc_boolean_t full, isc_boolean_t serv_only) {
	dig_server_t *srv;
	isc_sockaddr_t sockaddr;
	dig_searchlist_t *listent;
	isc_result_t result;

	srv = ISC_LIST_HEAD(server_list);

	while (srv != NULL) {
		char sockstr[ISC_SOCKADDR_FORMATSIZE];

		result = get_address(srv->servername, port, &sockaddr);
		check_result(result, "get_address");

		isc_sockaddr_format(&sockaddr, sockstr, sizeof(sockstr));
		printf("Default server: %s\nAddress: %s\n",
			srv->userarg, sockstr);
		if (!full)
			return;
		srv = ISC_LIST_NEXT(srv, link);
	}
	if (serv_only)
		return;
	printf("\nSet options:\n");
	printf("  %s\t\t\t%s\t\t%s\n",
	       tcpmode ? "vc" : "novc",
	       short_form ? "nodebug" : "debug",
	       debugging ? "d2" : "nod2");
	printf("  %s\t\t%s\n",
	       usesearch ? "search" : "nosearch",
	       recurse ? "recurse" : "norecurse");
	printf("  timeout = %d\t\tretry = %d\tport = %d\tndots = %d\n",
	       timeout, tries, port, ndots);
	printf("  querytype = %-8s\tclass = %s\n", deftype, defclass);
	printf("  srchlist = ");
	for (listent = ISC_LIST_HEAD(search_list);
	     listent != NULL;
	     listent = ISC_LIST_NEXT(listent, link)) {
		     printf("%s", listent->origin);
		     if (ISC_LIST_NEXT(listent, link) != NULL)
			     printf("/");
	}
	printf("\n");
}
