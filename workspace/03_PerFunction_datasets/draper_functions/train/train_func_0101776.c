_nrrdGzDoFlush(gzFile file, int flush) {
  static const char me[]="_nrrdGzDoFlush";
  uInt len;
  int done = 0;
  _NrrdGzStream *s = (_NrrdGzStream*)file;

  if (s == NULL || s->mode != 'w') {
    biffAddf(NRRD, "%s: invalid stream or file mode", me);
    return Z_STREAM_ERROR;
  }

  s->stream.avail_in = 0;

  for (;;) {
    len = _NRRD_Z_BUFSIZE - s->stream.avail_out;

    if (len != 0) {
      if ((uInt)fwrite(s->outbuf, 1, len, s->file) != len) {
        s->z_err = Z_ERRNO;
        return Z_ERRNO;
      }
      s->stream.next_out = s->outbuf;
      s->stream.avail_out = _NRRD_Z_BUFSIZE;
    }
    if (done) break;
    s->z_err = deflate(&(s->stream), flush);


    if (len == 0 && s->z_err == Z_BUF_ERROR) s->z_err = Z_OK;


    done = (s->stream.avail_out != 0 || s->z_err == Z_STREAM_END);

    if (s->z_err != Z_OK && s->z_err != Z_STREAM_END) break;
  }
  return  s->z_err == Z_STREAM_END ? Z_OK : s->z_err;
}
