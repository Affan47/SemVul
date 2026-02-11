PR_Socket(PRInt32 domain, PRInt32 type, PRInt32 proto)
{
    PRIntn osfd;
    PRDescType ftype;
    PRFileDesc *fd = NULL;
#if defined(_PR_INET6_PROBE) || !defined(_PR_INET6)
    PRInt32 tmp_domain = domain;
#endif

    if (!_pr_initialized) _PR_ImplicitInitialization();

    if (pt_TestAbort()) return NULL;

    if (PF_INET != domain
        && PR_AF_INET6 != domain
#if defined(_PR_HAVE_SDP)
        && PR_AF_INET_SDP != domain
#if defined(SOLARIS)
        && PR_AF_INET6_SDP != domain
#endif
#endif
        && PF_UNIX != domain)
    {
        PR_SetError(PR_ADDRESS_NOT_SUPPORTED_ERROR, 0);
        return fd;
    }
	if (type == SOCK_STREAM) ftype = PR_DESC_SOCKET_TCP;
	else if (type == SOCK_DGRAM) ftype = PR_DESC_SOCKET_UDP;
	else
	{
		(void)PR_SetError(PR_ADDRESS_NOT_SUPPORTED_ERROR, 0);
		return fd;
	}
#if defined(_PR_HAVE_SDP)
#if defined(LINUX)
    if (PR_AF_INET_SDP == domain)
        domain = AF_INET_SDP;
#elif defined(SOLARIS)
    if (PR_AF_INET_SDP == domain) {
        domain = AF_INET;
        proto = PROTO_SDP;
    } else if(PR_AF_INET6_SDP == domain) {
        domain = AF_INET6;
        proto = PROTO_SDP;
    }
#endif
#endif
#if defined(_PR_INET6_PROBE)
	if (PR_AF_INET6 == domain)
		domain = _pr_ipv6_is_present() ? AF_INET6 : AF_INET;
#elif defined(_PR_INET6)
	if (PR_AF_INET6 == domain)
		domain = AF_INET6;
#else
	if (PR_AF_INET6 == domain)
		domain = AF_INET;
#endif

    osfd = socket(domain, type, proto);
    if (osfd == -1) pt_MapError(_PR_MD_MAP_SOCKET_ERROR, errno);
    else
    {
#ifdef _PR_IPV6_V6ONLY_PROBE
        if ((domain == AF_INET6) && _pr_ipv6_v6only_on_by_default)
        {
            int on = 0;
            (void)setsockopt(osfd, IPPROTO_IPV6, IPV6_V6ONLY,
                    &on, sizeof(on));
        }
#endif
        fd = pt_SetMethods(osfd, ftype, PR_FALSE, PR_FALSE);
        if (fd == NULL) close(osfd);
    }
#ifdef _PR_NEED_SECRET_AF
    if (fd != NULL) fd->secret->af = domain;
#endif
#if defined(_PR_INET6_PROBE) || !defined(_PR_INET6)
	if (fd != NULL) {


		if (PR_AF_INET6 == tmp_domain && PR_AF_INET == domain) {
			if (PR_FAILURE == _pr_push_ipv6toipv4_layer(fd)) {
				PR_Close(fd);
				fd = NULL;
			}
		}
	}
#endif
    return fd;
}
