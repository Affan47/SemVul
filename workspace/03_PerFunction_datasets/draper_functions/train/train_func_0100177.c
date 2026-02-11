parse_network (char *net_s, struct in6_addr *network)
{
    int type;
    char *t;
    if (NULL != (t = strchr(net_s, ':'))) {
        type = AF_INET6;
        if (!inet_pton(type, net_s, network)) {
            perror("parse_nets6");
            return -1;
        }
        dlog("Network6 %-36s \t -> %08x:%08x:%08x:%08x\n",
               net_s,
               IP6ADDR(network)
              );
    } else {
        type = AF_INET;
        if (!inet_pton(type, net_s, &IP4ADDR(network))) {
            perror("parse_nets");
            return -1;
        }
        dlog("Network4 %16s \t-> 0x%08x\n", net_s, IP4ADDR(network));
    }
    return type;
}
