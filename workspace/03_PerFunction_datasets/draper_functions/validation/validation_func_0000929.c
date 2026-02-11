vty_describe_fold(vty_t *vty, int cmd_width, unsigned int desc_width, desc_t *desc)
{
	char *buf;
	const char *cmd, *p;
	int pos;

	cmd = desc->cmd[0] == '.' ? desc->cmd + 1 : desc->cmd;

	if (desc_width <= 0) {
		vty_out(vty, "  %-*s  %s%s", cmd_width, cmd, desc->str, VTY_NEWLINE);
		return;
	}

	buf = (char *) MALLOC(strlen (desc->str) + 1);

	for (p = desc->str; strlen (p) > desc_width; p += pos + 1) {
		for (pos = desc_width; pos > 0; pos--)
			if (*(p + pos) == ' ')
				break;

		if (pos == 0)
			break;

		strncpy (buf, p, pos);
		buf[pos] = '\0';
		vty_out(vty, "  %-*s  %s%s", cmd_width, cmd, buf, VTY_NEWLINE);

		cmd = "";
	}

	vty_out(vty, "  %-*s  %s%s", cmd_width, cmd, p, VTY_NEWLINE);

	FREE(buf);
}
