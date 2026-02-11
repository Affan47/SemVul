ptmxReadAll(int fd, const void *origBuf, size_t maxCount) {
  typedef int hdr;
  char *buf = (char *)origBuf;
  int rc;
  while ((rc = readOnePacket(fd, buf, maxCount)) > 0) {
    buf += rc;
  }
  *(hdr *)buf = 0;
  buf += sizeof(hdr);
  JASSERT(rc < 0 || buf - (char *)origBuf > 0)(rc)(origBuf)((void *)buf);
  return (rc < 0 ? rc : buf - (char *)origBuf);
}
