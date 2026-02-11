sig_complete_filename(GList **list, WINDOW_REC *window,
				  const char *word, const char *line, int *want_space)
{
	g_return_if_fail(list != NULL);
	g_return_if_fail(word != NULL);
	g_return_if_fail(line != NULL);

	if (*line != '\0') return;

	*list = filename_complete(word, NULL);
	if (*list != NULL) {
		*want_space = FALSE;
		signal_stop();
	}
}
