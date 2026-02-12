int imap_exec_msgset (IMAP_DATA* idata, const char* pre, const char* post,
                      int flag, int changed, int invert)
{
  HEADER** hdrs = NULL;
  short oldsort;
  BUFFER* cmd;
  int pos;
  int rc;
  int count = 0, reopen_set = 0;

  cmd = mutt_buffer_new ();


  if (idata->reopen & IMAP_REOPEN_ALLOW)
  {
    idata->reopen &= ~IMAP_REOPEN_ALLOW;
    reopen_set = 1;
  }
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = idata->ctx->hdrs;
    idata->ctx->hdrs = safe_malloc (idata->ctx->msgcount * sizeof (HEADER*));
    memcpy (idata->ctx->hdrs, hdrs, idata->ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (idata->ctx->hdrs, idata->ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  pos = 0;

  do
  {
    mutt_buffer_clear (cmd);
    mutt_buffer_add_printf (cmd, "%s ", pre);
    rc = imap_make_msg_set (idata, cmd, flag, changed, invert, &pos);
    if (rc > 0)
    {
      mutt_buffer_add_printf (cmd, " %s", post);
      if (imap_exec (idata, cmd->data, IMAP_CMD_QUEUE))
      {
        rc = -1;
        goto out;
      }
      count += rc;
    }
  }
  while (rc > 0);

  rc = count;

out:
  mutt_buffer_free (&cmd);
  if ((oldsort != Sort) || hdrs)
  {
    Sort = oldsort;
    FREE (&idata->ctx->hdrs);
    idata->ctx->hdrs = hdrs;
  }
  if (reopen_set)
    idata->reopen |= IMAP_REOPEN_ALLOW;

  return rc;
}
