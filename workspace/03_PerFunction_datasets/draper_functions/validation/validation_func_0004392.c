create_tcp_dispatch(dns_requestmgr_t *requestmgr, isc_sockaddr_t *srcaddr,
		    isc_sockaddr_t *destaddr, dns_dispatch_t **dispatchp)
{
	isc_result_t result;
	isc_socket_t *socket = NULL;
	isc_sockaddr_t src;
	unsigned int attrs;
	isc_sockaddr_t bind_any;

	result = isc_socket_create(requestmgr->socketmgr,
				   isc_sockaddr_pf(destaddr),
				   isc_sockettype_tcp, &socket);
	if (result != ISC_R_SUCCESS)
		return (result);
#ifndef BROKEN_TCP_BIND_BEFORE_CONNECT
	if (srcaddr == NULL) {
		isc_sockaddr_anyofpf(&bind_any,
				     isc_sockaddr_pf(destaddr));
		result = isc_socket_bind(socket, &bind_any, 0);
	} else {
		src = *srcaddr;
		isc_sockaddr_setport(&src, 0);
		result = isc_socket_bind(socket, &src, 0);
	}
	if (result != ISC_R_SUCCESS)
		goto cleanup;
#endif
	attrs = 0;
	attrs |= DNS_DISPATCHATTR_TCP;
	attrs |= DNS_DISPATCHATTR_PRIVATE;
	if (isc_sockaddr_pf(destaddr) == AF_INET)
		attrs |= DNS_DISPATCHATTR_IPV4;
	else
		attrs |= DNS_DISPATCHATTR_IPV6;
	attrs |= DNS_DISPATCHATTR_MAKEQUERY;
	result = dns_dispatch_createtcp(requestmgr->dispatchmgr,
					socket, requestmgr->taskmgr,
					4096, 2, 1, 1, 3, attrs,
					dispatchp);
cleanup:
	isc_socket_detach(&socket);
	return (result);
}
