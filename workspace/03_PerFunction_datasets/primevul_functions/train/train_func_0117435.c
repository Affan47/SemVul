int imap_check_mailbox (CONTEXT *ctx, int *index_hint, int force)
{


  IMAP_DATA* idata;
  int result = -1, poll_rc;

  idata = (IMAP_DATA*) ctx->data;


  if (!force && option (OPTIMAPIDLE) && mutt_bit_isset (idata->capabilities, IDLE)
      && (idata->state != IMAP_IDLE || time(NULL) >= idata->lastread + ImapKeepalive))
  {
    if (imap_cmd_idle (idata) < 0)
      goto errcleanup;
  }
  if (idata->state == IMAP_IDLE)
  {
    while ((poll_rc = mutt_socket_poll (idata->conn, 0)) > 0)
    {
      if (imap_cmd_step (idata) != IMAP_CMD_CONTINUE)
      {
        dprint (1, (debugfile, "Error reading IDLE response\n"));
        goto errcleanup;
      }
    }
    if (poll_rc < 0)
    {
      dprint (1, (debugfile, "Poll failed, disabling IDLE\n"));
      mutt_bit_unset (idata->capabilities, IDLE);
    }
  }

  if ((force ||
       (idata->state != IMAP_IDLE && time(NULL) >= idata->lastread + Timeout))
      && imap_exec (idata, "NOOP", IMAP_CMD_POLL) != 0)
    goto errcleanup;


  imap_cmd_finish (idata);

  result = 0;

errcleanup:

  if (idata->status == IMAP_FATAL)
  {
    if ((idata->reopen & IMAP_REOPEN_ALLOW) &&
        Context &&
        idata->ctx == Context)
    {
      if (imap_reconnect (&idata) == 0)
      {
        idata->check_status = 0;
        return MUTT_RECONNECTED;
      }
    }
    return -1;
  }

  if (idata->check_status & IMAP_EXPUNGE_PENDING)
    result = MUTT_REOPENED;
  else if (idata->check_status & IMAP_NEWMAIL_PENDING)
    result = MUTT_NEW_MAIL;
  else if (idata->check_status & IMAP_FLAGS_PENDING)
    result = MUTT_FLAGS;

  idata->check_status = 0;

  return result;
}
