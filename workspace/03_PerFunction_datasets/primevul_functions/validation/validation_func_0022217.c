do_string_and_free(char *cmdline)
{
#ifdef USE_MOUSE
    if (display_ipc_commands())
	fprintf(stderr, "%s\n", cmdline);
#endif

    lf_push(NULL, NULL, cmdline);
    while (gp_input_line_len < strlen(cmdline) + 1)
	extend_input_line();
    strcpy(gp_input_line, cmdline);
    screen_ok = FALSE;
    command_exit_requested = do_line();


    if (command_exit_requested) {
	while (lf_head && !lf_head->name) {
	    FPRINTF((stderr,"pop one level of non-file LFS\n"));
	    lf_pop();
	}
    } else
	lf_pop();
}
