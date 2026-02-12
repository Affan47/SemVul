String string_replace(const char *s, int len, int start, int length,
                      const char *replacement, int len_repl) {
  assert(s);
  assert(replacement);
  assert(len >= 0);


  if (start < 0) {
    start = len + start;
    if (start < 0) {
      start = 0;
    }
  }
  if (start > len) {
    start = len;
  }


  if (length < 0) {
    length = (len - start) + length;
    if (length < 0) {
      length = 0;
    }
  }

  if (length > len) {
    length = len;
  }


  if (length > len - start) {
    length = len - start;
  }

  String retString(len + len_repl - length, ReserveString);
  char *ret = retString.bufferSlice().ptr;

  int ret_len = 0;
  if (start) {
    memcpy(ret, s, start);
    ret_len += start;
  }
  if (len_repl) {
    memcpy(ret + ret_len, replacement, len_repl);
    ret_len += len_repl;
  }
  len -= (start + length);
  if (len) {
    memcpy(ret + ret_len, s + start + length, len);
    ret_len += len;
  }
  retString.setSize(ret_len);
  return retString;
}
