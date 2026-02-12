int64_t BZ2File::readImpl(char * buf, int64_t length) {
  if (length == 0) {
    return 0;
  }
  assertx(m_bzFile);
  int len = BZ2_bzread(m_bzFile, buf, length);


  if (len <= 0) {
    setEof(true);
    if (len < 0) {
      return -1;
    }
  }
  return len;
}
