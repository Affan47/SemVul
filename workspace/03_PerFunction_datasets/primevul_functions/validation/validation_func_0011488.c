int imap_login(struct ImapAccountData *adata)
{
  if (!adata)
    return -1;

  if (adata->state == IMAP_DISCONNECTED)
  {
    mutt_buffer_reset(&adata->cmdbuf);
    imap_open_connection(adata);
  }
  if (adata->state == IMAP_CONNECTED)
  {
    if (imap_authenticate(adata) == IMAP_AUTH_SUCCESS)
    {
      adata->state = IMAP_AUTHENTICATED;
      FREE(&adata->capstr);
      if (adata->conn->ssf != 0)
      {
        mutt_debug(LL_DEBUG2, "Communication encrypted at %d bits\n",
                   adata->conn->ssf);
      }
    }
    else
      mutt_account_unsetpass(&adata->conn->account);
  }
  if (adata->state == IMAP_AUTHENTICATED)
  {

    imap_exec(adata, "CAPABILITY", IMAP_CMD_PASS);

#ifdef USE_ZLIB

    if ((adata->capabilities & IMAP_CAP_COMPRESS) && C_ImapDeflate &&
        (imap_exec(adata, "COMPRESS DEFLATE", IMAP_CMD_PASS) == IMAP_EXEC_SUCCESS))
    {
      mutt_debug(LL_DEBUG2, "IMAP compression is enabled on connection to %s\n",
                 adata->conn->account.host);
      mutt_zstrm_wrap_conn(adata->conn);
    }
#endif


    if (C_ImapRfc5161 && (adata->capabilities & IMAP_CAP_ENABLE))
      imap_exec(adata, "ENABLE UTF8=ACCEPT", IMAP_CMD_QUEUE);


    if (adata->capabilities & IMAP_CAP_QRESYNC)
    {
      adata->capabilities |= IMAP_CAP_CONDSTORE;
      if (C_ImapRfc5161 && C_ImapQresync)
        imap_exec(adata, "ENABLE QRESYNC", IMAP_CMD_QUEUE);
    }


    adata->delim = '/';
    imap_exec(adata, "LIST \"\" \"\"", IMAP_CMD_QUEUE);


    imap_exec(adata, NULL, IMAP_CMD_NO_FLAGS);


    if (adata->mailbox)
    {
      imap_mbox_select(adata->mailbox);
    }
  }

  if (adata->state < IMAP_AUTHENTICATED)
    return -1;

  return 0;
}
