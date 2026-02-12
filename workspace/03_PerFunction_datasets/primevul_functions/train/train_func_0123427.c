win_close_buffer(win_T *win, int action, int abort_if_last)
{
#ifdef FEAT_SYN_HL

    if (win->w_buffer != NULL)
	reset_synblock(win);
#endif

#ifdef FEAT_QUICKFIX

    if (win->w_buffer != NULL && bt_quickfix(win->w_buffer))
	win->w_buffer->b_p_bl = FALSE;
#endif


    if (win->w_buffer != NULL)
    {
	bufref_T    bufref;

	set_bufref(&bufref, curbuf);
	win->w_closing = TRUE;
	close_buffer(win, win->w_buffer, action, abort_if_last);
	if (win_valid_any_tab(win))
	    win->w_closing = FALSE;


	if (!bufref_valid(&bufref))
	    curbuf = firstbuf;
    }
}
