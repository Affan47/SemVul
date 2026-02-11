dns_resolv ( struct interface *resolv,
			const char *name, struct sockaddr *sa ) {
	struct dns_request *dns;
	char *fqdn;
	int rc;


	if ( ! nameserver.st_family ) {
		DBG ( "DNS not attempting to resolve \"%s\": "
		      "no DNS servers\n", name );
		rc = -ENXIO_NO_NAMESERVER;
		goto err_no_nameserver;
	}


	fqdn = dns_qualify_name ( name );
	if ( ! fqdn ) {
		rc = -ENOMEM;
		goto err_qualify_name;
	}


	dns = zalloc ( sizeof ( *dns ) );
	if ( ! dns ) {
		rc = -ENOMEM;
		goto err_alloc_dns;
	}
	ref_init ( &dns->refcnt, NULL );
	intf_init ( &dns->resolv, &dns_resolv_desc, &dns->refcnt );
	intf_init ( &dns->socket, &dns_socket_desc, &dns->refcnt );
	timer_init ( &dns->timer, dns_timer_expired, &dns->refcnt );
	memcpy ( &dns->sa, sa, sizeof ( dns->sa ) );


	dns->query.dns.flags = htons ( DNS_FLAG_QUERY | DNS_FLAG_OPCODE_QUERY |
				       DNS_FLAG_RD );
	dns->query.dns.qdcount = htons ( 1 );
	dns->qinfo = ( void * ) dns_make_name ( fqdn, dns->query.payload );
	dns->qinfo->qtype = htons ( DNS_TYPE_A );
	dns->qinfo->qclass = htons ( DNS_CLASS_IN );


	if ( ( rc = xfer_open_socket ( &dns->socket, SOCK_DGRAM,
				       ( struct sockaddr * ) &nameserver,
				       NULL ) ) != 0 ) {
		DBGC ( dns, "DNS %p could not open socket: %s\n",
		       dns, strerror ( rc ) );
		goto err_open_socket;
	}


	dns_send_packet ( dns );


	intf_plug_plug ( &dns->resolv, resolv );
	ref_put ( &dns->refcnt );
	free ( fqdn );
	return 0;

 err_open_socket:
 err_alloc_dns:
	ref_put ( &dns->refcnt );
 err_qualify_name:
	free ( fqdn );
 err_no_nameserver:
	return rc;
}
