read_line(const char *prompt, int start)
{
    TBOOLEAN more = FALSE;
    int last = 0;

    current_prompt = prompt;


    if (start == 0) {
	c_token = num_tokens = 0;
	gp_input_line[0] = '\0';
    }

    do {

	if (gp_get_string(gp_input_line + start, gp_input_line_len - start,
		         ((more) ? ">" : prompt))
	    == (char *) NULL)
	{

	    if (interactive)
		(void) putc('\n', stderr);
	    gp_input_line[start] = NUL;
	    inline_num++;
	    if (start > 0 && curly_brace_count == 0)
		more = FALSE;
	    else
		return (1);
	} else {


	    last = strlen(gp_input_line) - 1;
	    if (last >= 0) {
		if (gp_input_line[last] == '\n') {
		    gp_input_line[last] = NUL;
		    if (last > 0 && gp_input_line[last-1] == '\r')
			gp_input_line[--last] = NUL;

		    if (last > 0)
			--last;
		} else if (last + 2 >= gp_input_line_len) {
		    extend_input_line();

		    start = last + 1;
		    more = TRUE;
		    continue;

		}
		if (gp_input_line[last] == '\\') {

		    start = last;
		    more = TRUE;
		} else
		    more = FALSE;
	    } else
		more = FALSE;
	}
    } while (more);
    return (0);
}
