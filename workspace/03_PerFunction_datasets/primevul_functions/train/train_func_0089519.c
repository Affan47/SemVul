void imap_clean_path(char *path, size_t plen)
{
  struct ImapMbox mx;
  struct ImapData *idata = NULL;
  char mbox[LONG_STRING] = "";

  if (imap_parse_path(path, &mx) < 0)
    return;

  idata = imap_conn_find(&mx.account, MUTT_IMAP_CONN_NONEW);
  if (!idata)
    return;


  imap_fix_path(idata, mx.mbox, mbox, sizeof(mbox));


  imap_qualify_path(path, plen, &mx, mbox);
}
