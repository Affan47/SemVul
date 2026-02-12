static bool imap_client_input_next_cmd(struct client *_client)
{
	struct imap_client *client = (struct imap_client *)_client;
	const struct imap_arg *args;
	bool parsed;
	int ret;

	if (strcasecmp(client->cmd_name, "AUTHENTICATE") == 0) {


		ret = cmd_authenticate(client, &parsed);
		if (ret == 0 && !parsed)
			return FALSE;
	} else if (strcasecmp(client->cmd_name, "ID") == 0) {


		ret = cmd_id(client);
		if (ret == 0)
			return FALSE;
		if (ret < 0)
			ret = 1;
	} else {
		ret = client_parse_command(client, &args);
		if (ret < 0)
			return TRUE;
		if (ret == 0)
			return FALSE;
		ret = *client->cmd_tag == '\0' ? -1 :
			client_command_execute(client, client->cmd_name, args);
	}

	client->cmd_finished = TRUE;
	if (ret == -2 && strcasecmp(client->cmd_tag, "LOGIN") == 0) {
		client_send_reply(&client->common, IMAP_CMD_REPLY_BAD,
			"First parameter in line is IMAP's command tag, "
			"not the command name. Add that before the command, "
			"like: a login user pass");
	} else if (ret < 0) {
		if (!client_invalid_command(client))
			return FALSE;
	}

	return ret != 0 && !client->common.destroyed;
}
