void imap_get_parent_path(const char *path, char *buf, size_t buflen)
{
  struct ImapAccountData *adata = NULL;
  struct ImapMboxData *mdata = NULL;
  char mbox[1024];

  if (imap_adata_find(path, &adata, &mdata) < 0)
  {
    mutt_str_copy(buf, path, buflen);
    return;
  }


  imap_get_parent(mdata->name, adata->delim, mbox, sizeof(mbox));


  imap_qualify_path(buf, buflen, &adata->conn->account, mbox);
  imap_mdata_free((void *) &mdata);
}
