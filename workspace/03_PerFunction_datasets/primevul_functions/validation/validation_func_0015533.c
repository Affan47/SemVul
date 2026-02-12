ConnStateData::parseProxyProtocolHeader()
{


    if (inBuf.startsWith(Proxy2p0magic))
        return parseProxy2p0();


    if (inBuf.startsWith(Proxy1p0magic))
        return parseProxy1p0();


    if (inBuf.length() >= Proxy2p0magic.length()) {


        return proxyProtocolError("PROXY protocol error: invalid header");
    }


    return false;
}
