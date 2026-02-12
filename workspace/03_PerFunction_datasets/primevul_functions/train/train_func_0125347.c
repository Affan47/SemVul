void imap_keepalive (void)
{
  CONNECTION *conn;
  CONTEXT *ctx = NULL;
  IMAP_DATA *idata;

  conn = mutt_socket_head ();
  while (conn)
  {
    if (conn->account.type == MUTT_ACCT_TYPE_IMAP)
    {
      int need_free = 0;

      idata = (IMAP_DATA*) conn->data;

      if (idata->state >= IMAP_AUTHENTICATED
	  && time(NULL) >= idata->lastread + ImapKeepalive)
      {
	if (idata->ctx)
	  ctx = idata->ctx;
	else
	{
	  ctx = safe_calloc (1, sizeof (CONTEXT));
	  ctx->data = idata;


	  need_free = 1;
	}


	imap_check_mailbox (ctx, NULL, 1);
	if (need_free)
	  FREE (&ctx);
      }
    }

    conn = conn->next;
  }
}
