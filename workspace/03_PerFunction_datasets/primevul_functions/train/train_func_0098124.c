int mg_vasprintf(char **buf, size_t size, const char *fmt, va_list ap) {
  va_list ap_copy;
  int len;

  va_copy(ap_copy, ap);
  len = vsnprintf(*buf, size, fmt, ap_copy);
  va_end(ap_copy);

  if (len < 0) {


    *buf = NULL;
    while (len < 0) {
      free(*buf);
      if (size == 0) size = 5;
      size *= 2;
      if ((*buf = (char *) calloc(1, size)) == NULL) {
        len = -1;
        break;
      }
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, size - 1, fmt, ap_copy);
      va_end(ap_copy);
    }


    if (*buf != NULL) (*buf)[len] = 0;

  } else if (len >= (int) size) {

    if ((*buf = (char *) calloc(1, (size_t) len + 1)) == NULL) {
      len = -1;
    } else {
      va_copy(ap_copy, ap);
      len = vsnprintf(*buf, (size_t) len + 1, fmt, ap_copy);
      va_end(ap_copy);
    }
  }

  return len;
}
