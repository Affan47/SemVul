write_cached_envelope(struct mail_cache_db * cache_db,
    MMAPString * mmapstr,
    mailsession * session, uint32_t num,
    struct mailimf_fields * fields)
{
  int r;
  char keyname[PATH_MAX];
  int res;
  struct mailpop3_msg_info * info;
  mailpop3 * pop3;

  pop3 = get_pop3_session(session);

  r = mailpop3_get_msg_info(pop3, num, &info);
  switch (r) {
  case MAILPOP3_ERROR_BAD_STATE:
    return MAIL_ERROR_BAD_STATE;
  case MAILPOP3_ERROR_NO_SUCH_MESSAGE:
    return MAIL_ERROR_MSG_NOT_FOUND;
  case MAILPOP3_NO_ERROR:
    break;
  default:
    return MAIL_ERROR_FETCH;
  }

  snprintf(keyname, PATH_MAX, "%s-envelope", info->msg_uidl);

  r = generic_cache_fields_write(cache_db, mmapstr, keyname, fields);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto err;
  }

  return MAIL_NO_ERROR;

 err:
  return res;
}
