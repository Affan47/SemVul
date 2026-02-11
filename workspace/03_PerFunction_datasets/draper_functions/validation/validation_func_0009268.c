sig_complete_erase(WINDOW_REC *window, const char *word,
			       const char *linestart)
{
	const char *cmdchars;
        char *line, *cmd, *args, *signal;

	if (*linestart == '\0')
		return;


	cmdchars = settings_get_str("cmdchars");
        cmdchars = strchr(cmdchars, *linestart);
	if (cmdchars == NULL)
		return;


	line = linestart[1] == *cmdchars ? g_strdup(linestart+2) :
		expand_aliases(linestart+1);

	cmd = line_get_command(line, &args, FALSE);
	if (cmd == NULL) {
		g_free(line);
		return;
	}

	signal = g_strconcat("complete erase command ", cmd, NULL);
	signal_emit(signal, 3, window, word, args);

        g_free(signal);
	g_free(cmd);
	g_free(line);
}
