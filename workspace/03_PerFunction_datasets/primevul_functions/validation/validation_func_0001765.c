int vspprintf(char** pbuf, size_t , const char* format, ...) {
  int len;
  va_list ap;
  va_start(ap, format);
  len = xbuf_format_converter(pbuf, format, ap);
  va_end(ap);
  return len;
}
