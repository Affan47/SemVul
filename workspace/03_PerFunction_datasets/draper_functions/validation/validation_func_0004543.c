append(string& s, unsigned long long x, int width) {
  Assert(*PAD_END == '\0' && width < PAD_END - PAD);
  int written = snprintf(buf, BUF_LEN, "%llu", x);
  if (written < width) s += PAD_END - width + written;
  buf[BUF_LEN - 1] = '\0';
  return s += buf;
}
