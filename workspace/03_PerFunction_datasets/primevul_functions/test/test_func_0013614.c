static int changedline (const Proto *p, int oldpc, int newpc) {
  if (p->lineinfo == NULL)
    return 0;
  if (newpc - oldpc < MAXIWTHABS / 2) {
    int delta = 0;
    int pc = oldpc;
    for (;;) {
      int lineinfo = p->lineinfo[++pc];
      if (lineinfo == ABSLINEINFO)
        break;
      delta += lineinfo;
      if (pc == newpc)
        return (delta != 0);
    }
  }


  return (luaG_getfuncline(p, oldpc) != luaG_getfuncline(p, newpc));
}
