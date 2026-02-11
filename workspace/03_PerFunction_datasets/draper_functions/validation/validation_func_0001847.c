add_var_table(tlist, buf, len)
	struct tablelist **tlist;
	char *buf;
	int len;
{
	if (add_cmd_table(tlist, buf, len) < 0)
		error("Warning: environment variables from lesskey file unavailable", NULL_PARG);
}
