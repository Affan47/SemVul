void imap_get_parent(const char *mbox, char delim, char *buf, size_t buflen)
{

  if (mbox != buf)
    mutt_str_copy(buf, mbox, buflen);

  int n = mutt_str_len(buf);


  for (n--; (n >= 0) && (buf[n] != delim); n--)
    ;


  if (n > 0)
  {

    buf[n] = '\0';
  }
  else
  {
    buf[0] = (n == 0) ? delim : '\0';
  }
}
