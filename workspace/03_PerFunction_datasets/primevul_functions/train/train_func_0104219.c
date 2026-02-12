int imap_check_mailbox (CONTEXT *ctx, int *index_hint, int force)
{


  IMAP_DATA* idata;
  int result = 0;

  idata = (IMAP_DATA*) ctx->data;


  if (!force && option (OPTIMAPIDLE) && mutt_bit_isset (idata->capabilities, IDLE)
      && (idata->state != IMAP_IDLE || time(NULL) >= idata->lastread + ImapKeepalive))
  {
    if (imap_cmd_idle (idata) < 0)
      return -1;
  }
  if (idata->state == IMAP_IDLE)
  {
    while ((result = mutt_socket_poll (idata->conn, 0)) > 0)
    {
      if (imap_cmd_step (idata) != IMAP_CMD_CONTINUE)
      {
        dprint (1, (debugfile, "Error reading IDLE response\n"));
        return -1;
      }
    }
    if (result < 0)
    {
      dprint (1, (debugfile, "Poll failed, disabling IDLE\n"));
      mutt_bit_unset (idata->capabilities, IDLE);
    }
  }

  if ((force ||
       (idata->state != IMAP_IDLE && time(NULL) >= idata->lastread + Timeout))
      && imap_exec (idata, "NOOP", IMAP_CMD_POLL) != 0)
    return -1;


  imap_cmd_finish (idata);

  if (idata->check_status & IMAP_EXPUNGE_PENDING)
    result = MUTT_REOPENED;
  else if (idata->check_status & IMAP_NEWMAIL_PENDING)
    result = MUTT_NEW_MAIL;
  else if (idata->check_status & IMAP_FLAGS_PENDING)
    result = MUTT_FLAGS;

  idata->check_status = 0;

  return result;
}
