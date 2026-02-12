rlgets(char *s, size_t n, const char *prompt)
{
    static char *line = (char *) NULL;
    static int leftover = -1;

    if (leftover == -1) {

	if (line != (char *) NULL) {
	    free(line);
	    line = NULL;


	}
	line = readline((interactive) ? prompt : "");
	leftover = 0;

	if (line && *line) {
#  if defined(READLINE) || defined(HAVE_LIBREADLINE)
	    int found;

	    using_history();


	    if (!is_history_command(line)) {
		if (!history_full) {
		    found = history_search(line, -1);
		    if (found != -1 && !strcmp(current_history()->line,line)) {

			HIST_ENTRY *removed = remove_history(where_history());

			if (removed) {
			    free(removed->line);
			    free(removed->data);
			    free(removed);
			}
		    }
		}
		add_history(line);
	    }
#  elif defined(HAVE_LIBEDITLINE)
	    if (!is_history_command(line)) {

		int found = 0;
		using_history();

		if (!history_full)
		    found = history_search(line, -1);
		if (found <= 0)
		    add_history(line);
	    }
#  endif
	}
    }
    if (line) {

	safe_strncpy(s, line + leftover, n);
	leftover += strlen(s);
	if (line[leftover] == NUL)
	    leftover = -1;
	return s;
    }
    return NULL;
}
