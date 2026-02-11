sig_message_private(SERVER_REC *server, const char *msg,
				const char *nick, const char *address)
{
	if (ignore_check(server, nick, address, NULL, msg, MSGLEVEL_MSGS))
		signal_stop();
}
