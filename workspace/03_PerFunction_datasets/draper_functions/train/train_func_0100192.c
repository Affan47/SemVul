fetch_size(mailmessage * msg_info,
    size_t * result)
{
  char * msg;
  int r;

  r = fetch(msg_info, &msg, result);
  if (r != MAIL_NO_ERROR) {
    return r;
  }

  fetch_result_free(msg_info, msg);

  return MAIL_NO_ERROR;
}
