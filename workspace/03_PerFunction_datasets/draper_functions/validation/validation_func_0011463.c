luaO_chunkid (char *out, const char *source, size_t bufflen) {
  size_t l = strlen(source);
  if (*source == '=') {
    if (l <= bufflen)
      memcpy(out, source + 1, l * sizeof(char));
    else {
      addstr(out, source + 1, bufflen - 1);
      *out = '\0';
    }
  }
  else if (*source == '@') {
    if (l <= bufflen)
      memcpy(out, source + 1, l * sizeof(char));
    else {
      addstr(out, RETS, LL(RETS));
      bufflen -= LL(RETS);
      memcpy(out, source + 1 + l - bufflen, bufflen * sizeof(char));
    }
  }
  else {
    const char *nl = strchr(source, '\n');
    addstr(out, PRE, LL(PRE));
    bufflen -= LL(PRE RETS POS) + 1;
    if (l < bufflen && nl == NULL) {
      addstr(out, source, l);
    }
    else {
      if (nl != NULL) l = nl - source;
      if (l > bufflen) l = bufflen;
      addstr(out, source, l);
      addstr(out, RETS, LL(RETS));
    }
    memcpy(out, POS, (LL(POS) + 1) * sizeof(char));
  }
}
