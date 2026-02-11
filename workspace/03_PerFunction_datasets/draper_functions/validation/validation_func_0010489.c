dump_raw(Trace *pTrace,
               unsigned int tbi,
               char *buf, int bufsize)
  {
    if (!pTrace)
      return 0;

    int n = TraceType::dump_raw(pTrace, tbi,buf,bufsize);

    buf += n;
    bufsize -= n;

    unsigned int tv = pTrace->get(tbi);


    int  m = snprintf(buf, bufsize,
                      "  Option Reg: was 0x%0X ", tv & 0xff);

    return m>0 ? (m+n) : n;
  }
