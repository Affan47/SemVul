config_from_file(vty_t *vty, FILE *fp)
{
	int ret;
	vector_t *vline;

	while (fgets(vty->buf, VTY_BUFSIZ, fp)) {
		vline = cmd_make_strvec(vty->buf);


		if (vline == NULL)
			continue;


		ret = cmd_execute_command_strict(vline, vty, NULL);


		while (ret != CMD_SUCCESS && ret != CMD_WARNING &&
		       ret != CMD_ERR_NOTHING_TODO && vty->node != CONFIG_NODE) {
			vty->node = node_parent(vty->node);
			ret = cmd_execute_command_strict (vline, vty, NULL);
		}

		cmd_free_strvec(vline);

		if (ret != CMD_SUCCESS && ret != CMD_WARNING &&
		    ret != CMD_ERR_NOTHING_TODO)
			return ret;
	}

	return CMD_SUCCESS;
}
