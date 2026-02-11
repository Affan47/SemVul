netsnmp_gethostbyaddr(const void *addr, socklen_t len, int type)
{
#if HAVE_GETHOSTBYADDR
    struct hostent *hp = NULL;
    struct sockaddr_in *saddr_in =
        NETSNMP_REMOVE_CONST(struct sockaddr_in *,addr);

    DEBUGMSGTL(("dns:gethostbyaddr", "resolving { AF_INET, %s:%hu }\n",
                inet_ntoa(saddr_in->sin_addr), ntohs(saddr_in->sin_port)));

#ifdef DNSSEC_LOCAL_VALIDATION
    val_status_t val_status;
    hp = val_gethostbyaddr(netsnmp_validator_context(),
                           (const void*)&saddr_in->sin_addr,
                           sizeof(struct in_addr), AF_INET, &val_status);
    DEBUGMSGTL(("dns:sec:val", "val_status %d / %s; trusted: %d\n",
                val_status, p_val_status(val_status),
                val_istrusted(val_status)));
    if (!val_istrusted(val_status)) {
        snmp_log(LOG_WARNING,
                 "The authenticity of DNS response is not trusted (%s)\n",
                 p_val_status(val_status));

        if (!netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
                                    NETSNMP_DS_LIB_DNSSEC_WARN_ONLY))
            hp = NULL;
    }
    else if (val_does_not_exist(val_status) && hp)
        hp = NULL;
#else
    hp = gethostbyaddr((const void*) &saddr_in->sin_addr,
                       sizeof(struct in_addr), AF_INET);
#endif
    if (hp == NULL) {
        DEBUGMSGTL(("dns:gethostbyaddr", "couldn't resolve addr\n"));
    } else if (hp->h_addrtype != AF_INET) {
        DEBUGMSGTL(("dns:gethostbyaddr",
                    "warning: response for addr not AF_INET!\n"));
    } else {
        DEBUGMSGTL(("dns:gethostbyaddr", "addr resolved okay\n"));
    }
    return hp;
#else
    NETSNMP_LOGONCE((LOG_ERR, "gethostbyaddr not available"));
    return NULL;
#endif
}
