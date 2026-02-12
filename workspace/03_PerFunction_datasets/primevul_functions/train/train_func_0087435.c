leaving_window(win_T *win)
{

    if (!bt_prompt(win->w_buffer))
	return;


    win->w_buffer->b_prompt_insert = restart_edit;
    if (restart_edit != 0 && mode_displayed)
	clear_cmdline = TRUE;
    restart_edit = NUL;


    if (State & INSERT)
    {
	stop_insert_mode = TRUE;
	if (win->w_buffer->b_prompt_insert == NUL)
	    win->w_buffer->b_prompt_insert = 'A';
    }
}
