static void php_reg_eprint(int err, regex_t* re) {
  char *buf = nullptr, *message = nullptr;
  size_t len;
  size_t buf_len;

#ifdef REG_ITOA

  buf_len = regerror(REG_ITOA | err, re, nullptr, 0);
  if (buf_len) {
    buf = (char *)req::malloc_noptrs(buf_len);
    if (!buf) return;

    regerror(REG_ITOA | err, re, buf, buf_len);
  }
#else
  buf_len = 0;
#endif
  len = regerror(err, re, nullptr, 0);
  if (len) {
    message = (char *)req::malloc_noptrs(buf_len + len + 2);
    if (!message) {
      return;
    }
    if (buf_len) {
      snprintf(message, buf_len, "%s: ", buf);
      buf_len += 1;
    }

    regerror(err, re, message + buf_len, len);
    raise_warning("%s", message);
  }
  req::free(buf);
  req::free(message);
}
