libsmtp_close(struct libsmtp_session_struct *libsmtp_session)
{
  if (!libsmtp_session->stream)
	{
		if (libsmtp_session->socket >= 0)
		{
			close (libsmtp_session->socket);
			libsmtp_session->socket = -1;
		}
	}
	else
	{
		GB.Stream.Block(libsmtp_session->stream, libsmtp_session->was_blocking);
	}

  return LIBSMTP_NOERR;
}
