handle_skinny_show_settings(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	switch (cmd) {
	case CLI_INIT:
		e->command = "skinny show settings";
		e->usage =
			"Usage: skinny show settings\n"
			"       Lists all global configuration settings of the Skinny subsystem.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 3)
		return CLI_SHOWUSAGE;

	ast_cli(a->fd, "\nGlobal Settings:\n");
	ast_cli(a->fd, "  Skinny Port:            %d\n", ntohs(bindaddr.sin_port));
	ast_cli(a->fd, "  Bindaddress:            %s\n", ast_inet_ntoa(bindaddr.sin_addr));
	ast_cli(a->fd, "  KeepAlive:              %d\n", keep_alive);
	ast_cli(a->fd, "  Date Format:            %s\n", date_format);
	ast_cli(a->fd, "  Voice Mail Extension:   %s\n", S_OR(vmexten, "(not set)"));
	ast_cli(a->fd, "  Reg. context:           %s\n", S_OR(regcontext, "(not set)"));
	ast_cli(a->fd, "  Jitterbuffer enabled:   %s\n", AST_CLI_YESNO(ast_test_flag(&global_jbconf, AST_JB_ENABLED)));
	 if (ast_test_flag(&global_jbconf, AST_JB_ENABLED)) {
		ast_cli(a->fd, "  Jitterbuffer forced:    %s\n", AST_CLI_YESNO(ast_test_flag(&global_jbconf, AST_JB_FORCED)));
		ast_cli(a->fd, "  Jitterbuffer max size:  %ld\n", global_jbconf.max_size);
		ast_cli(a->fd, "  Jitterbuffer resync:    %ld\n", global_jbconf.resync_threshold);
		ast_cli(a->fd, "  Jitterbuffer impl:      %s\n", global_jbconf.impl);
		if (!strcasecmp(global_jbconf.impl, "adaptive")) {
			ast_cli(a->fd, "  Jitterbuffer tgt extra: %ld\n", global_jbconf.target_extra);
		}
		ast_cli(a->fd, "  Jitterbuffer log:       %s\n", AST_CLI_YESNO(ast_test_flag(&global_jbconf, AST_JB_LOG)));
	}

	return CLI_SUCCESS;
}
