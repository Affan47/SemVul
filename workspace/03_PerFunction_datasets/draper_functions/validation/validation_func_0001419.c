mailesmtp_rcpt(mailsmtp * session,
		    const char * to,
		    int notify,
		    const char * orcpt)
{
  int r;
  char command[SMTP_STRING_SIZE];
  char notify_str[30] = "";
  char notify_info_str[30] = "";

  if (notify != 0 && session->esmtp & MAILSMTP_ESMTP_DSN) {
    if (notify & MAILSMTP_DSN_NOTIFY_SUCCESS)
      strcat(notify_info_str, ",SUCCESS");
    if (notify & MAILSMTP_DSN_NOTIFY_FAILURE)
      strcat(notify_info_str, ",FAILURE");
    if (notify & MAILSMTP_DSN_NOTIFY_DELAY)
      strcat(notify_info_str, ",DELAY");

    if (notify & MAILSMTP_DSN_NOTIFY_NEVER)
      strcpy(notify_info_str, ",NEVER");

    notify_info_str[0] = '=';

    strcpy(notify_str, " NOTIFY");
    strcat(notify_str, notify_info_str);
  }

  if (orcpt && session->esmtp & MAILSMTP_ESMTP_DSN)
    snprintf(command, SMTP_STRING_SIZE, "RCPT TO:<%s>%s ORCPT=%s\r\n",
	     to, notify_str, orcpt);
  else
    snprintf(command, SMTP_STRING_SIZE, "RCPT TO:<%s>%s\r\n", to, notify_str);

  r = send_command(session, command);
  if (r == -1)
    return MAILSMTP_ERROR_STREAM;
  r = read_response(session);

  switch (r) {
  case 250:
    return MAILSMTP_NO_ERROR;

  case 251:
    return MAILSMTP_NO_ERROR;

  case 550:
  case 450:
    return MAILSMTP_ERROR_MAILBOX_UNAVAILABLE;

  case 551:
    return MAILSMTP_ERROR_USER_NOT_LOCAL;

  case 552:
    return MAILSMTP_ERROR_EXCEED_STORAGE_ALLOCATION;

  case 553:
    return MAILSMTP_ERROR_MAILBOX_NAME_NOT_ALLOWED;

  case 451:
    return MAILSMTP_ERROR_IN_PROCESSING;

  case 452:
    return MAILSMTP_ERROR_INSUFFICIENT_SYSTEM_STORAGE;

  case 503:
    return MAILSMTP_ERROR_BAD_SEQUENCE_OF_COMMAND;

  case 0:
    return MAILSMTP_ERROR_STREAM;

  default:
    return MAILSMTP_ERROR_UNEXPECTED_CODE;
  }
}
