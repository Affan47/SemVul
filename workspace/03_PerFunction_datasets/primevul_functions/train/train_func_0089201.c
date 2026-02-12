term_write(const char *buf, uint len)
{


  if (term_selecting() && cfg.suspbuf_max > 0) {

    if (len > cfg.suspbuf_max - term.suspbuf_pos)
      term_flush();

    if (len <= cfg.suspbuf_max - term.suspbuf_pos) {

      if (term.suspbuf_pos + len > term.suspbuf_size) {
        term.suspbuf_size = term.suspbuf_pos + len;
        term.suspbuf = renewn(term.suspbuf, term.suspbuf_size);
      }
      memcpy(term.suspbuf + term.suspbuf_pos, buf, len);
      term.suspbuf_pos += len;
      return;
    }


  }

  term_do_write(buf, len);
}
