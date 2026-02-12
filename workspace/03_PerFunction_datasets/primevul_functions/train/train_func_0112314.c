static void event_invalid_cap (IRC_SERVER_REC *server, const char *data, const char *from)
{


	server->cap_complete = FALSE;
	irc_send_cmd_now(server, "CAP END");
}
