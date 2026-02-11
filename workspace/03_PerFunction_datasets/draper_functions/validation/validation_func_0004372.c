cmd_head(char *cmdline, char **cmd, char **arg)
{
	int cl;

	while (isspace(*cmdline))
		cmdline ++;
	if (*cmdline == 0) {
		*cmd = NULL;
		if (arg)
			*arg = NULL;
		return 0;
	}
	*cmd = cmdline;
	while (isalnum(*cmdline))
		cmdline ++;
	cl = cmdline - *cmd;
	if (*cmdline == 0) {
		if (arg)
			*arg = NULL;
		return cl;
	}
	while (isspace(*cmdline))
		cmdline ++;
	if (*cmdline == 0) {
		if (arg)
			*arg = NULL;
		return cl;
	}
	if (arg)
		*arg = cmdline;
	return cl;
}
