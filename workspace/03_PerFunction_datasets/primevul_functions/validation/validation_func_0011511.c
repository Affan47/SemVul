static void imap_logout(struct ImapAccountData *adata)
{


  if (adata->state == IMAP_DISCONNECTED)
  {
    return;
  }

  adata->status = IMAP_BYE;
  imap_cmd_start(adata, "LOGOUT");
  if ((C_ImapPollTimeout <= 0) || (mutt_socket_poll(adata->conn, C_ImapPollTimeout) != 0))
  {
    while (imap_cmd_step(adata) == IMAP_RES_CONTINUE)
      ;
  }
  mutt_socket_close(adata->conn);
  adata->state = IMAP_DISCONNECTED;
}
