handle_cli_ooh323_set_debug(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	switch (cmd) {
	case CLI_INIT:
		e->command = "ooh323 set debug [off]";
		e->usage =
			"Usage: ooh323 set debug [off]\n"
			"		 Enables/Disables debugging of OOH323 channel driver\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc < 3 || a->argc > 4)
		return CLI_SHOWUSAGE;
	if (a->argc == 4 && strcasecmp(a->argv[3], "off"))
		return CLI_SHOWUSAGE;

	gH323Debug = (a->argc == 4) ? FALSE : TRUE;
	ast_cli(a->fd, "OOH323 Debugging %s\n", gH323Debug ? "Enabled" : "Disabled");

	return CLI_SUCCESS;
}
