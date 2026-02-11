main(int argc, char **argv)
{
	struct msg_data all_msgs, msg;
	struct store *ctx = NULL;
	int uid = 0;
	int ofs = 0;
	int r;
	int total, n = 0;
	int nongit_ok;


	arc4_init();

	setup_git_directory_gently(&nongit_ok);
	git_config(git_imap_config, NULL);

	if (!server.port)
		server.port = server.use_ssl ? 993 : 143;

	if (!imap_folder) {
		fprintf(stderr, "no imap store specified\n");
		return 1;
	}
	if (!server.host) {
		if (!server.tunnel) {
			fprintf(stderr, "no imap host specified\n");
			return 1;
		}
		server.host = "tunnel";
	}


	if (!read_message(stdin, &all_msgs)) {
		fprintf(stderr, "nothing to send\n");
		return 1;
	}

	total = count_messages(&all_msgs);
	if (!total) {
		fprintf(stderr, "no messages to send\n");
		return 1;
	}


	ctx = imap_open_store(&server);
	if (!ctx) {
		fprintf(stderr, "failed to open store\n");
		return 1;
	}

	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
	ctx->name = imap_folder;
	while (1) {
		unsigned percent = n * 100 / total;
		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);
		if (!split_msg(&all_msgs, &msg, &ofs))
			break;
		r = imap_store_msg(ctx, &msg, &uid);
		if (r != DRV_OK)
			break;
		n++;
	}
	fprintf(stderr, "\n");

	imap_close_store(ctx);

	return 0;
}
