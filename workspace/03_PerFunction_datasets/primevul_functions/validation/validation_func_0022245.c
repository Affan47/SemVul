replotrequest()
{


    if (END_OF_COMMAND) {
	char *rest_args = &gp_input_line[token[c_token].start_index];
	size_t replot_len = strlen(replot_line);
	size_t rest_len = strlen(rest_args);


	memmove(gp_input_line,rest_args,rest_len+1);

	while (gp_input_line_len < replot_len+rest_len+1)
	    extend_input_line();


	memmove(gp_input_line+replot_len,gp_input_line,rest_len+1);

	memcpy(gp_input_line, replot_line, replot_len);
    } else {
	char *replot_args = NULL;
	int last_token = num_tokens - 1;


	size_t newlen = strlen(replot_line) + token[last_token].start_index
		      + token[last_token].length - token[c_token].start_index + 3;

	m_capture(&replot_args, c_token, last_token);
	while (gp_input_line_len < newlen)
	    extend_input_line();
	strcpy(gp_input_line, replot_line);
	strcat(gp_input_line, ", ");
	strcat(gp_input_line, replot_args);
	free(replot_args);
    }
    plot_token = 0;
    SET_REFRESH_OK(E_REFRESH_NOT_OK, 0);

    screen_ok = FALSE;
    num_tokens = scanner(&gp_input_line, &gp_input_line_len);
    c_token = 1;

    if (almost_equals(0,"test")) {
	c_token = 0;
	test_command();
    } else if (almost_equals(0,"s$plot"))
	plot3drequest();
    else
	plotrequest();
}
