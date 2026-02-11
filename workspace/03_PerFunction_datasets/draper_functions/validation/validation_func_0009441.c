dosomethingTimeoutCbk (TimeoutId id, void *data)
{
  Connection cxn = (Connection) data ;

  ASSERT (id == cxn->dosomethingTimerId) ;

  show_stats(cxn);


  if ((cxn->lmtp_state == LMTP_DISCONNECTED) &&
      (cxn->lmtp_sleepTimerId == 0) &&
      QueueItems(&(cxn->lmtp_todeliver_q)) > 0)
  {
      if (lmtp_Connect(cxn) != RET_OK)
	  prepareReopenCbk(cxn, 1);
  }

  if ((cxn->imap_state == IMAP_DISCONNECTED) &&
      (cxn->imap_sleepTimerId == 0) &&
      (QueueItems(&(cxn->imap_controlMsg_q)) > 0))
  {
      if (imap_Connect(cxn) != RET_OK)
	  prepareReopenCbk(cxn, 0);
  }


  if ((cxn->lmtp_state == LMTP_AUTHED_IDLE) &&
      QueueItems(&(cxn->lmtp_todeliver_q)) > 0) {
      lmtp_sendmessage(cxn,NULL);
  } else if (cxn->lmtp_state == LMTP_AUTHED_IDLE) {
      lmtp_noop(cxn);
  }

  if ((cxn->imap_state == IMAP_IDLE_AUTHED) &&
      (QueueItems(&(cxn->imap_controlMsg_q)) > 0)) {
      imap_ProcessQueue(cxn);
  } else if (cxn->imap_state == IMAP_IDLE_AUTHED) {
      imap_noop(cxn);
  }


  clearTimer (cxn->dosomethingTimerId) ;

  cxn->dosomethingTimerId = prepareSleep (dosomethingTimeoutCbk,
					  cxn->dosomethingTimeout, cxn);
}
