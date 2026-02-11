mboxdriver_cached_logout(mailsession * session)
{
  struct mbox_cached_session_state_data * cached_data;
  int r;

  r = write_max_uid_value(session);

  cached_data = get_cached_data(session);

  mbox_flags_store_process(cached_data->mbox_flags_directory,
			   cached_data->mbox_quoted_mb,
			   cached_data->mbox_flags_store);

  r = mailsession_logout(get_ancestor(session));
  if (r != MAIL_NO_ERROR)
    return r;

  free_state(cached_data);

  return MAIL_NO_ERROR;
}
