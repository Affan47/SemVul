print_line(linenr_T lnum, int use_number, int list)
{
    int		save_silent = silent_mode;


    if (message_filtered(ml_get(lnum)))
	return;

    msg_start();
    silent_mode = FALSE;
    info_message = TRUE;
    print_line_no_prefix(lnum, use_number, list);
    if (save_silent)
    {
	msg_putchar('\n');
	cursor_on();
	out_flush();
	silent_mode = save_silent;
    }
    info_message = FALSE;
}
