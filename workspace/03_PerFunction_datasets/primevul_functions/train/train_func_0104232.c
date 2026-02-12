IMAP_DATA* imap_conn_find (const ACCOUNT* account, int flags)
{
  CONNECTION* conn = NULL;
  ACCOUNT* creds = NULL;
  IMAP_DATA* idata = NULL;
  int new = 0;

  while ((conn = mutt_conn_find (conn, account)))
  {
    if (!creds)
      creds = &conn->account;
    else
      memcpy (&conn->account, creds, sizeof (ACCOUNT));

    idata = (IMAP_DATA*)conn->data;
    if (flags & MUTT_IMAP_CONN_NONEW)
    {
      if (!idata)
      {

        mutt_socket_free (conn);
        return NULL;
      }
      else if (idata->state < IMAP_AUTHENTICATED)
        continue;
    }
    if (flags & MUTT_IMAP_CONN_NOSELECT && idata && idata->state >= IMAP_SELECTED)
      continue;
    if (idata && idata->status == IMAP_FATAL)
      continue;
    break;
  }
  if (!conn)
    return NULL;


  if (!idata)
  {
    idata = imap_new_idata ();
    conn->data = idata;
    idata->conn = conn;
    new = 1;
  }

  if (idata->state == IMAP_DISCONNECTED)
    imap_open_connection (idata);
  if (idata->state == IMAP_CONNECTED)
  {
    if (!imap_authenticate (idata))
    {
      idata->state = IMAP_AUTHENTICATED;
      FREE (&idata->capstr);
      new = 1;
      if (idata->conn->ssf)
	dprint (2, (debugfile, "Communication encrypted at %d bits\n",
		    idata->conn->ssf));
    }
    else
      mutt_account_unsetpass (&idata->conn->account);
  }
  if (new && idata->state == IMAP_AUTHENTICATED)
  {

    imap_exec (idata, "CAPABILITY", IMAP_CMD_FAIL_OK);

#if defined(USE_ZLIB)

    if (mutt_bit_isset (idata->capabilities, COMPRESS_DEFLATE))
    {
      if (option (OPTIMAPDEFLATE) &&
	  imap_exec (idata, "COMPRESS DEFLATE", IMAP_CMD_FAIL_OK) == 0)
	mutt_zstrm_wrap_conn (idata->conn);
    }
#endif


    if (mutt_bit_isset (idata->capabilities, ENABLE))
      imap_exec (idata, "ENABLE UTF8=ACCEPT", IMAP_CMD_QUEUE);


    if (mutt_bit_isset (idata->capabilities, QRESYNC))
    {
      mutt_bit_set (idata->capabilities, CONDSTORE);
      if (option (OPTIMAPQRESYNC))
        imap_exec (idata, "ENABLE QRESYNC", IMAP_CMD_QUEUE);
    }


    idata->delim = '/';
    imap_exec (idata, "LIST \"\" \"\"", IMAP_CMD_QUEUE);
    if (option (OPTIMAPCHECKSUBSCRIBED))
      imap_exec (idata, "LSUB \"\" \"*\"", IMAP_CMD_QUEUE);


    imap_exec (idata, NULL, IMAP_CMD_FAIL_OK);
  }

  if (idata->state < IMAP_AUTHENTICATED)
    return NULL;

  return idata;
}
