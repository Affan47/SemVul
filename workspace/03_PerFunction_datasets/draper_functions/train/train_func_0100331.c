netsnmp_udpbase_sendto(int fd, struct in_addr *srcip, int if_index,
                           struct sockaddr *remote, void *data, int len)
{
    struct iovec iov;
    struct msghdr m = { 0 };
    char          cmsg[CMSG_SPACE(cmsg_data_size)];
    int           rc;

    iov.iov_base = data;
    iov.iov_len  = len;

    m.msg_name		= remote;
    m.msg_namelen	= sizeof(struct sockaddr_in);
    m.msg_iov		= &iov;
    m.msg_iovlen	= 1;
    m.msg_flags		= 0;

    if (srcip && srcip->s_addr != INADDR_ANY) {
        struct cmsghdr *cm;

        DEBUGMSGTL(("udpbase:sendto", "sending from %s\n", inet_ntoa(*srcip)));

        memset(cmsg, 0, sizeof(cmsg));

        m.msg_control    = &cmsg;
        m.msg_controllen = sizeof(cmsg);

        cm = CMSG_FIRSTHDR(&m);
        cm->cmsg_len = CMSG_LEN(cmsg_data_size);

#if  defined(linux) && defined(IP_PKTINFO)
        cm->cmsg_level = SOL_IP;
        cm->cmsg_type = IP_PKTINFO;

        {
            struct in_pktinfo ipi = { 0 };
            ipi.ipi_ifindex = 0;
            ipi.ipi_spec_dst.s_addr = srcip->s_addr;
            memcpy(CMSG_DATA(cm), &ipi, sizeof(ipi));
        }

        rc = sendmsg(fd, &m, NETSNMP_NOSIGNAL|NETSNMP_DONTWAIT);
        if (rc >= 0 || errno != EINVAL)
            return rc;


        DEBUGMSGTL(("udpbase:sendto", "re-sending on iface %d\n", if_index));

        {
            struct in_pktinfo ipi = { 0 };
            ipi.ipi_ifindex = if_index;
            ipi.ipi_spec_dst.s_addr = INADDR_ANY;
            memcpy(CMSG_DATA(cm), &ipi, sizeof(ipi));
        }
#elif defined(IP_SENDSRCADDR)
        cm->cmsg_level = IPPROTO_IP;
        cm->cmsg_type = IP_SENDSRCADDR;
        memcpy((struct in_addr *)CMSG_DATA(cm), srcip, sizeof(struct in_addr));
#endif
        rc = sendmsg(fd, &m, NETSNMP_NOSIGNAL|NETSNMP_DONTWAIT);
        if (rc >= 0 || errno != EINVAL)
            return rc;

        DEBUGMSGTL(("udpbase:sendto", "re-sending without source address\n"));
        m.msg_control = NULL;
        m.msg_controllen = 0;
    }

    return sendmsg(fd, &m, NETSNMP_NOSIGNAL|NETSNMP_DONTWAIT);
}
