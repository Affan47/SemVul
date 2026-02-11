logFormat(uint32_t style, const char* fmt, ...) {
  char buf[1024];
  size_t len;

  va_list ap;
  va_start(ap, fmt);
  len = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);

  if (len >= sizeof(buf))
    len = sizeof(buf) - 1;

  logString(style, buf, len);
}
