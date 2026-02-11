parseAddrPrefix(const char * xmlFile, char * buf, bool pd)
{

    unsigned long timestamp, pref, valid, length;
    SPtr<TIPv6Addr> addr = 0;
    SPtr<TAddrPrefix> addraddr;
    char * x;

    if (strstr(buf, "<AddrAddr") || strstr(buf, "<AddrPrefix")) {
              timestamp=pref=valid=length=0;
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
              if(pd==true) {
                  if ((x=strstr(buf,"length="))) {
                      length = atoi(x+8);
                  }
              }
              else {
                  if ((x=strstr(buf,"prefix="))) {
                      length = atoi(x+8);
                  }
              }
              if ((x=strstr(buf,">"))) {
                  if(pd==true)
                      x = strstr(x, "</AddrPrefix>");
                  else
                      x = strstr(x, "</AddrAddr>");
                  if (x)
                      *x = 0;
                  addr = new TIPv6Addr(strstr(buf,">")+1, true);
                  Log(Debug) << "Parsed prefix " << addr->getPlain() << "/"
                             << length << ", pref=" << pref << ", valid=" << valid
                             << ",ts=" << timestamp << LogEnd;
              }
              if (addr && timestamp && pref && valid && pd==true) {
                  addraddr = new TAddrPrefix(addr, pref, valid, length);
                  addraddr->setTimestamp(timestamp);
              }
    }
    return addraddr;
}
