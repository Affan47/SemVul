ConnStateData::parseProxy2p0()
{
    static const SBuf::size_type prefixLen = Proxy2p0magic.length();
    if (inBuf.length() < prefixLen + 4)
        return false;

    if ((inBuf[prefixLen] & 0xF0) != 0x20)
        return proxyProtocolError("PROXY/2.0 error: invalid version");

    const char command = (inBuf[prefixLen] & 0x0F);
    if ((command & 0xFE) != 0x00)
        return proxyProtocolError("PROXY/2.0 error: invalid command");

    const char family = (inBuf[prefixLen+1] & 0xF0) >>4;
    if (family > 0x3)
        return proxyProtocolError("PROXY/2.0 error: invalid family");

    const char proto = (inBuf[prefixLen+1] & 0x0F);
    if (proto > 0x2)
        return proxyProtocolError("PROXY/2.0 error: invalid protocol type");

    const char *clen = inBuf.rawContent() + prefixLen + 2;
    uint16_t len;
    memcpy(&len, clen, sizeof(len));
    len = ntohs(len);

    if (inBuf.length() < prefixLen + 4 + len)
        return false;

    inBuf.consume(prefixLen + 4);
    const SBuf extra = inBuf.consume(len);
    needProxyProtocolHeader_ = false;


    if (command == 0x00)
        return true;

    union pax {
        struct {
            struct in_addr src_addr;
            struct in_addr dst_addr;
            uint16_t src_port;
            uint16_t dst_port;
        } ipv4_addr;
        struct {
            struct in6_addr src_addr;
            struct in6_addr dst_addr;
            uint16_t src_port;
            uint16_t dst_port;
        } ipv6_addr;
#if NOT_SUPPORTED
        struct {
            uint8_t src_addr[108];
            uint8_t dst_addr[108];
        } unix_addr;
#endif
    };

    pax ipu;
    memcpy(&ipu, extra.rawContent(), sizeof(pax));


    debugs(33, 5, "PROXY/2.0 protocol on connection " << clientConnection);
    switch (family) {
    case 0x1:
        clientConnection->local = ipu.ipv4_addr.dst_addr;
        clientConnection->local.port(ntohs(ipu.ipv4_addr.dst_port));
        clientConnection->remote = ipu.ipv4_addr.src_addr;
        clientConnection->remote.port(ntohs(ipu.ipv4_addr.src_port));
        if ((clientConnection->flags & COMM_TRANSPARENT))
            clientConnection->flags ^= COMM_TRANSPARENT;
        break;
    case 0x2:
        clientConnection->local = ipu.ipv6_addr.dst_addr;
        clientConnection->local.port(ntohs(ipu.ipv6_addr.dst_port));
        clientConnection->remote = ipu.ipv6_addr.src_addr;
        clientConnection->remote.port(ntohs(ipu.ipv6_addr.src_port));
        if ((clientConnection->flags & COMM_TRANSPARENT))
            clientConnection->flags ^= COMM_TRANSPARENT;
        break;
    default:
        break;
    }
    debugs(33, 5, "PROXY/2.0 upgrade: " << clientConnection);
    return true;
}
