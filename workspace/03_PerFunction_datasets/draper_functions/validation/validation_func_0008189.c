parseAddrAddr(const char * xmlFile, char * buf, bool pd)
{

    unsigned long timestamp, pref=DHCPV6_INFINITY, valid=DHCPV6_INFINITY;
    int prefix = CLIENT_DEFAULT_PREFIX_LENGTH;
    SPtr<TIPv6Addr> addr = 0;
    SPtr<TAddrAddr> addraddr;
    char * x;

    if (strstr(buf, "<AddrAddr") || strstr(buf, "<AddrPrefix")) {
              timestamp=pref=valid=0;
              addr = 0;
              if ((x=strstr(buf,"timestamp"))) {
                  timestamp = atoi(x+11);
              }
              if ((x=strstr(buf,"pref="))) {
                  pref = atoi(x+6);
              }
              if ((x=strstr(buf,"valid"))) {
                  valid = atoi(x+7);
              }
              if(pd==false) {
                  if ((x=strstr(buf,"prefix="))) {
                      prefix = atoi(x+8);
                  }
              }
              else {
                  if ((x=strstr(buf,"length="))) {
                      prefix = atoi(x+8);
                  }
              }
              if ((x=strstr(buf,">"))) {
                  if(pd==false)
                      x = strstr(x, "</AddrAddr>");
                  else
                      x = strstr(x, "</AddrPrefix>");
                  if (x)
                      *x = 0;
                  addr = new TIPv6Addr(strstr(buf,">")+1, true);
                  Log(Debug) << "Parsed addr=" << addr->getPlain() << ", pref=" << pref << ", valid=" << valid << ",ts=" << timestamp << LogEnd;

              }
              if (addr && timestamp && pref && valid && pd==false) {
                  addraddr = new TAddrAddr(addr, pref, valid, prefix);
                  addraddr->setTimestamp(timestamp);
              }
    }
    return addraddr;
}
