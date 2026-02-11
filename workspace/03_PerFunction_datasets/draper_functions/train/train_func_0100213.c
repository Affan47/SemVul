event_silence_list(IRC_SERVER_REC *server, const char *data)
{
	char *params, *nick, *mask;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 3, NULL, &nick, &mask);
	printformat(server, NULL, MSGLEVEL_CRAP,
		    IRCTXT_SILENCE_LINE, nick, mask);
	g_free(params);
}
