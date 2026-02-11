io_file_readline(lua_State *L, FILE *fp, MSize chop)
{
  MSize m = LUAL_BUFFERSIZE, n = 0, ok = 0;
  char *buf;
  for (;;) {
    buf = lj_str_needbuf(L, &G(L)->tmpbuf, m);
    if (fgets(buf+n, m-n, fp) == NULL) break;
    n += (MSize)strlen(buf+n);
    ok |= n;
    if (n && buf[n-1] == '\n') { n -= chop; break; }
    if (n >= m - 64) m += m;
  }
  setstrV(L, L->top++, lj_str_new(L, buf, (size_t)n));
  lj_gc_check(L);
  return (int)ok;
}
