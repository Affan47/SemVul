static int imap_mbox_check(struct Mailbox *m)
{
  imap_allow_reopen(m);
  int rc = imap_check_mailbox(m, false);


  imap_disallow_reopen(m);

  return rc;
}
