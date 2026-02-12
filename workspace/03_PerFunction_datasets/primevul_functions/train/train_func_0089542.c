void imap_get_parent_path(char *output, const char *path, size_t olen)
{
  struct ImapMbox mx;
  struct ImapData *idata = NULL;
  char mbox[LONG_STRING] = "";

  if (imap_parse_path(path, &mx) < 0)
  {
    mutt_str_strfcpy(output, path, olen);
    return;
  }

  idata = imap_conn_find(&mx.account, MUTT_IMAP_CONN_NONEW);
  if (!idata)
  {
    mutt_str_strfcpy(output, path, olen);
    return;
  }


  imap_fix_path(idata, mx.mbox, mbox, sizeof(mbox));


  imap_get_parent(mbox, mbox, sizeof(mbox), idata->delim);


  imap_qualify_path(output, olen, &mx, mbox);
  FREE(&mx.mbox);
}
