addChooserHost(CARD16 connectionType,
               ARRAY8Ptr addr,
               char *closure ATTR_UNUSED)
{
    if (connectionType == FamilyBroadcast) {
        registerBroadcastForPing();
        return;
    }
    debug("internal host registration: %[*hhu, family %hx\n",
          addr->length, addr->data, connectionType);
    if (connectionType == FamilyInternet) {
        struct sockaddr_in in_addr;
        in_addr.sin_family = AF_INET;
        memmove(&in_addr.sin_addr, addr->data, 4);
        in_addr.sin_port = htons(XDM_UDP_PORT);
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
        in_addr.sin_len = sizeof(in_addr);
#endif
        registerHostaddr((struct sockaddr *)&in_addr, sizeof(in_addr),
#ifdef IN_MULTICAST
                         IN_MULTICAST(in_addr.sin_addr.s_addr) ?
                         BROADCAST_QUERY :
#endif
                         QUERY);
#if defined(IPv6) && defined(AF_INET6)
    } else if (connectionType == FamilyInternet6) {
        struct sockaddr_in6 in6_addr;
        in6_addr.sin6_family = AF_INET6;
        memmove(&in6_addr.sin6_addr, addr->data, 16);
        in6_addr.sin6_port = htons(XDM_UDP_PORT);
#ifdef HAVE_STRUCT_SOCKADDR_IN6_SIN6_LEN
        in6_addr.sin6_len = sizeof(in6_addr);
#endif
        registerHostaddr((struct sockaddr *)&in6_addr, sizeof(in6_addr),
                         IN6_IS_ADDR_MULTICAST(&in6_addr.sin6_addr) ?
                         BROADCAST_QUERY : QUERY);
#endif
    }
}
