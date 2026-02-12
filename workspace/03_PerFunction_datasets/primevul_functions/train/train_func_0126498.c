static BOOL check_response(int *errno_value, int more_errno, uschar *buffer,
  int *yield, uschar **message)
{
*yield = '4';


if (*errno_value == ETIMEDOUT)
  {
  *message = string_sprintf("LMTP timeout after %s", big_buffer);
  if (transport_count > 0)
    *message = string_sprintf("%s (%d bytes written)", *message,
      transport_count);
  *errno_value = 0;
  return FALSE;
  }


if (*errno_value == ERRNO_SMTPFORMAT)
  {
  *message = string_sprintf("Malformed LMTP response after %s: %s",
    big_buffer, string_printing(buffer));
  return FALSE;
  }


if (*errno_value == ERRNO_FILTER_FAIL)
  {
  *message = string_sprintf("transport filter process failed (%d)%s",
    more_errno,
    (more_errno == EX_EXECFAILED)? ": unable to execute command" : "");
  return FALSE;
  }


if (*errno_value == ERRNO_CHHEADER_FAIL)
  {
  *message =
    string_sprintf("failed to expand headers_add or headers_remove: %s",
      expand_string_message);
  return FALSE;
  }


if (*errno_value == ERRNO_WRITEINCOMPLETE)
  {
  *message = string_sprintf("failed to write a data block");
  return FALSE;
  }


if (buffer[0] != 0)
  {
  const uschar *s = string_printing(buffer);
  *message = string_sprintf("LMTP error after %s: %s", big_buffer, s);
  *yield = buffer[0];
  return TRUE;
  }


if (*errno_value == 0)
  {
  *errno_value = ERRNO_SMTPCLOSED;
  *message = string_sprintf("LMTP connection closed after %s", big_buffer);
  }

return FALSE;
}
