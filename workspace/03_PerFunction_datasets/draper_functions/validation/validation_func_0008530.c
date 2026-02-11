get_myaddr(void)
{
    int             sd, i, lastlen = 0;
    struct ifconf   ifc;
    struct ifreq   *ifrp = NULL;
    in_addr_t       addr;
    char           *buf = NULL;

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return 0;
    }


    for (i = 8;; i += 8) {
        buf = (char *) calloc(i, sizeof(struct ifreq));
        if (buf == NULL) {
            close(sd);
            return 0;
        }
        ifc.ifc_len = i * sizeof(struct ifreq);
        ifc.ifc_buf = (caddr_t) buf;

        if (ioctl(sd, SIOCGIFCONF, (char *) &ifc) < 0) {
            if (errno != EINVAL || lastlen != 0) {


                free(buf);
                close(sd);
                return 0;
            }


        } else {
            if (ifc.ifc_len == lastlen) {


                break;
            }
            lastlen = ifc.ifc_len;
        }
        free(buf);
    }

    for (ifrp = ifc.ifc_req;
        (char *)ifrp < (char *)ifc.ifc_req + ifc.ifc_len;
#ifdef HAVE_STRUCT_SOCKADDR_SA_LEN
        ifrp = (struct ifreq *)(((char *) ifrp) +
                                sizeof(ifrp->ifr_name) +
                                ifrp->ifr_addr.sa_len)
#else
        ifrp++
#endif
        ) {
        if (ifrp->ifr_addr.sa_family != AF_INET) {
            continue;
        }
        addr = ((struct sockaddr_in *) &(ifrp->ifr_addr))->sin_addr.s_addr;

        if (ioctl(sd, SIOCGIFFLAGS, (char *) ifrp) < 0) {
            continue;
        }
        if ((ifrp->ifr_flags & IFF_UP)
#ifdef IFF_RUNNING
            && (ifrp->ifr_flags & IFF_RUNNING)
#endif
            && !(ifrp->ifr_flags & IFF_LOOPBACK)
            && addr != LOOPBACK) {


#ifdef SYS_IOCTL_H_HAS_SIOCGIFADDR
            if (ioctl(sd, SIOCGIFADDR, (char *) ifrp) < 0) {
                continue;
            }
            addr =
                ((struct sockaddr_in *) &(ifrp->ifr_addr))->sin_addr.
                s_addr;
#endif
            free(buf);
            close(sd);
            return addr;
        }
    }
    free(buf);
    close(sd);
    return 0;
}
