cli_realtime_destroy(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	int res = -1;

	switch (cmd) {
	case CLI_INIT:
		e->command = "realtime destroy";
		e->usage =
			"Usage: realtime destroy <family> <colmatch1> <valuematch1> [<colmatch2> <valuematch2> [... <colmatch5> <valuematch5>]]\n"
			"       Remove a stored row using the RealTime driver.\n"
			"       You must supply a family name and name/value pairs (up to 5).\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc < 5) {
		return CLI_SHOWUSAGE;
	} else if (a->argc == 5) {
		res = ast_destroy_realtime(a->argv[2], a->argv[3], a->argv[4], SENTINEL);
	} else if (a->argc == 7) {
		res = ast_destroy_realtime(a->argv[2], a->argv[3], a->argv[4], a->argv[5], a->argv[6], SENTINEL);
	} else if (a->argc == 9) {
		res = ast_destroy_realtime(a->argv[2], a->argv[3], a->argv[4], a->argv[5], a->argv[6], a->argv[7], a->argv[8], SENTINEL);
	} else if (a->argc == 11) {
		res = ast_destroy_realtime(a->argv[2], a->argv[3], a->argv[4], a->argv[5], a->argv[6], a->argv[7], a->argv[8], a->argv[9], a->argv[10], SENTINEL);
	} else if (a->argc == 13) {
		res = ast_destroy_realtime(a->argv[2], a->argv[3], a->argv[4], a->argv[5], a->argv[6], a->argv[7], a->argv[8], a->argv[9], a->argv[10], a->argv[11], a->argv[12], SENTINEL);
	} else {
		return CLI_SHOWUSAGE;
	}

	if (res < 0) {
		ast_cli(a->fd, "Failed to remove record. Check the debug log for possible SQL related entries.\n");
		return CLI_FAILURE;
	}

	ast_cli(a->fd, "Removed %d RealTime record%s.\n", res, ESS(res));

	return CLI_SUCCESS;
}
