char *imap_get_qualifier(char *buf)
{
  char *s = buf;


  s = imap_next_word(s);

  s = imap_next_word(s);

  return s;
}
