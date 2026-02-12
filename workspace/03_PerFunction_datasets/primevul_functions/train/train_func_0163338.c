int rfc822_valid_msgid (const char *msgid)
{


  unsigned int l, i;

  if (!msgid || !*msgid)
    return -1;

  l = mutt_strlen (msgid);
  if (l < 5)
    return -1;
  if (msgid[0] != '<' || msgid[l-1] != '>')
    return -1;
  if (!(strrchr (msgid, '@')))
    return -1;


  for (i = 0; i < l; i++)
    if ((unsigned char)msgid[i] > 127)
      return -1;

  return 0;
}
