event_end_of_names(IRC_SERVER_REC *server, const char *data,
			       const char *nick)
{
	IRC_CHANNEL_REC *chanrec;
	char *params, *channel;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 2, NULL, &channel);

	chanrec = irc_channel_find(server, channel);
	if (chanrec == NULL || chanrec->names_got)
		print_event_received(server, data, nick, FALSE);
	g_free(params);
}
