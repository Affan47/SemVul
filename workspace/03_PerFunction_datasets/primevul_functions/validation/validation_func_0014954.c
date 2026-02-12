void lj_debug_shortname(char *out, GCstr *str)
{
  const char *src = strdata(str);
  if (*src == '=') {
    strncpy(out, src+1, LUA_IDSIZE);
    out[LUA_IDSIZE-1] = '\0';
  } else if (*src == '@') {
    size_t len = str->len-1;
    src++;
    if (len >= LUA_IDSIZE) {
      src += len-(LUA_IDSIZE-4);
      *out++ = '.'; *out++ = '.'; *out++ = '.';
    }
    strcpy(out, src);
  } else {
    size_t len;
    for (len = 0; len < LUA_IDSIZE-12; len++)
      if (((const unsigned char *)src)[len] < ' ') break;
    strcpy(out, "[string \""); out += 9;
    if (src[len] != '\0') {
      if (len > LUA_IDSIZE-15) len = LUA_IDSIZE-15;
      strncpy(out, src, len); out += len;
      strcpy(out, "..."); out += 3;
    } else {
      strcpy(out, src); out += len;
    }
    strcpy(out, "\"]");
  }
}
