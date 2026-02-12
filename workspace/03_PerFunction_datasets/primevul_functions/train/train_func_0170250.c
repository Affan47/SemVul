static bool client_handle_input(struct imap_client *client)
{
	i_assert(!client->common.authenticating);

	if (client->cmd_finished) {


		client->cmd_tag = NULL;
		client->cmd_name = NULL;
		imap_parser_reset(client->parser);


		if (client->skip_line) {
			if (!client_skip_line(client))
				return FALSE;
                        client->skip_line = FALSE;
		}

		client->cmd_finished = FALSE;
	}

	if (client->cmd_tag == NULL) {
                client->cmd_tag = imap_parser_read_word(client->parser);
		if (client->cmd_tag == NULL)
			return FALSE;
		if (!imap_is_valid_tag(client->cmd_tag) ||
		    strlen(client->cmd_tag) > IMAP_TAG_MAX_LEN) {


			client->cmd_tag = "";
		}
	}

	if (client->cmd_name == NULL) {
                client->cmd_name = imap_parser_read_word(client->parser);
		if (client->cmd_name == NULL)
			return FALSE;
	}
	return client->common.v.input_next_cmd(&client->common);
}
