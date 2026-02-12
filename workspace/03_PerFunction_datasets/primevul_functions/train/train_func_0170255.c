static int client_parse_command(struct imap_client *client,
				const struct imap_arg **args_r)
{
	switch (imap_parser_read_args(client->parser, 0, 0, args_r)) {
	case -1:

		if (!client_handle_parser_error(client, client->parser)) {

			return 0;
		}
		return -1;
	case -2:

		return 0;
	default:

		if (!client_skip_line(client))
			i_unreached();
		return 1;
	}
}
