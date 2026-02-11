format_address(const unsigned char *address)
{
    static char buf[4][INET6_ADDRSTRLEN];
    static int i = 0;
    i = (i + 1) % 4;
    if(v4mapped(address))
       inet_ntop(AF_INET, address + 12, buf[i], INET6_ADDRSTRLEN);
    else
       inet_ntop(AF_INET6, address, buf[i], INET6_ADDRSTRLEN);
    return buf[i];
}
