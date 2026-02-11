log_hexdump (ACE_Log_Priority log_priority,
                          const char *buffer,
                          size_t size,
                          const ACE_TCHAR *text)
{


  if (this->log_priority_enabled (log_priority) == 0)
    return 0;

  ACE_TCHAR* buf = 0;
  size_t const buf_sz =
    ACE_Log_Record::MAXLOGMSGLEN - ACE_Log_Record::VERBOSE_LEN - 58;
  ACE_NEW_RETURN (buf, ACE_TCHAR[buf_sz], -1);

  ACE_TCHAR *msg_buf = 0;
  const size_t text_sz = text ? ACE_OS::strlen(text) : 0;
  ACE_NEW_RETURN (msg_buf,
                  ACE_TCHAR[text_sz + 58],
                 -1);

  buf[0] = 0;

  size_t const len = ACE::format_hexdump
    (buffer, size, buf, buf_sz / sizeof (ACE_TCHAR) - text_sz);

  int sz = 0;

  if (text)
    sz = ACE_OS::sprintf (msg_buf,
#if !defined (ACE_WIN32) && defined (ACE_USES_WCHAR)
                          ACE_TEXT ("%ls - "),
#else
                          ACE_TEXT ("%s - "),
#endif
                          text);

  sz += ACE_OS::sprintf (msg_buf + sz,
                         ACE_TEXT ("HEXDUMP ")
                         ACE_SIZE_T_FORMAT_SPECIFIER
                         ACE_TEXT (" bytes"),
                         size);

  if (len < size)
    ACE_OS::sprintf (msg_buf + sz,
                     ACE_TEXT (" (showing first ")
                     ACE_SIZE_T_FORMAT_SPECIFIER
                     ACE_TEXT (" bytes)"),
                     len);


  this->log (log_priority,
             ACE_TEXT ("%s\n%s"),
             msg_buf,
             buf);

  delete [] msg_buf;
  delete [] buf;
  return 0;
}
