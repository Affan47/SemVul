qf_goto_win_with_qfl_file(int qf_fnum)
{
    win_T	*win;
    win_T	*altwin;

    win = curwin;
    altwin = NULL;
    for (;;)
    {
	if (win->w_buffer->b_fnum == qf_fnum)
	    break;
	if (win->w_prev == NULL)
	    win = lastwin;
	else
	    win = win->w_prev;

	if (IS_QF_WINDOW(win))
	{


	    if ((swb_flags & SWB_USELAST) && win_valid(prevwin))
		win = prevwin;
	    else if (altwin != NULL)
		win = altwin;
	    else if (curwin->w_prev != NULL)
		win = curwin->w_prev;
	    else
		win = curwin->w_next;
	    break;
	}


	if (altwin == NULL && !win->w_p_pvw && bt_normal(win->w_buffer))
	    altwin = win;
    }

    win_goto(win);
}
