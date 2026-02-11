uv__buf_count(uv_buf_t bufs[], int bufcnt) {
  size_t total = 0;
  int i;

  for (i = 0; i < bufcnt; i++) {
    total += bufs[i].len;
  }

  return total;
}
