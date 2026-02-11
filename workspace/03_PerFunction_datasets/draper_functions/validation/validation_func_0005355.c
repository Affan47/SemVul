imap_mailstorage_get_folder_session(struct mailstorage * storage,
    char * pathname, mailsession ** result)
{
  mailsession * session;
  int r;
  int res;

  if (strcasecmp(pathname, "INBOX") == 0) {
    session = storage->sto_session;
  }
  else {
    r = imap_connect(storage, &session);
    if (r != MAIL_NO_ERROR) {
      res = r;
      goto err;
    }

    r = mailsession_select_folder(session, pathname);
    if (r != MAIL_NO_ERROR) {
      mailsession_logout(session);
      res = r;
      goto free;
    }
  }

  * result = session;

  return MAIL_NO_ERROR;

 free:
  mailsession_free(session);
 err:
  return res;
}
