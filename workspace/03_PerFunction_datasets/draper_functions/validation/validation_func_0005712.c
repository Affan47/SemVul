nntp_mailstorage_connect(struct mailstorage * storage)
{
  struct nntp_mailstorage * nntp_storage;
  mailsession_driver * driver;
  int r;
  int res;
  mailsession * session;

  nntp_storage = storage->sto_data;

  if (nntp_storage->nntp_cached)
    driver = nntp_cached_session_driver;
  else
    driver = nntp_session_driver;

  r = mailstorage_generic_connect_with_local_address(driver,
      nntp_storage->nntp_servername, nntp_storage->nntp_port,
      nntp_storage->nntp_local_address, nntp_storage->nntp_local_port,
      nntp_storage->nntp_command,
      nntp_storage->nntp_connection_type,
      NNTPDRIVER_CACHED_SET_CACHE_DIRECTORY,
      nntp_storage->nntp_cache_directory,
      NNTPDRIVER_CACHED_SET_FLAGS_DIRECTORY,
      nntp_storage->nntp_flags_directory,
      &session);
  switch (r) {
  case MAIL_NO_ERROR_NON_AUTHENTICATED:
  case MAIL_NO_ERROR_AUTHENTICATED:
  case MAIL_NO_ERROR:
    break;
  default:
    res = r;
    goto err;
  }

  r = mailstorage_generic_auth(session, r,
      nntp_storage->nntp_connection_type,
      nntp_storage->nntp_login,
      nntp_storage->nntp_password);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto free;
  }

  storage->sto_session = session;

  return MAIL_NO_ERROR;

 free:
  mailsession_free(session);
 err:
  return res;
}
