close_last_window_tabpage(
    win_T	*win,
    int		free_buf,
    tabpage_T   *prev_curtab)
{
    if (ONE_WINDOW)
    {
	buf_T	*old_curbuf = curbuf;


	goto_tabpage_tp(alt_tabpage(), FALSE, TRUE);
	redraw_tabline = TRUE;


	if (valid_tabpage(prev_curtab) && prev_curtab->tp_firstwin == win)
	{
	    int	    h = tabline_height();

	    win_close_othertab(win, free_buf, prev_curtab);
	    if (h != tabline_height())
		shell_new_rows();
	}
#ifdef FEAT_JOB_CHANNEL
	entering_window(curwin);
#endif


	apply_autocmds(EVENT_TABCLOSED, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_WINENTER, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_TABENTER, NULL, NULL, FALSE, curbuf);
	if (old_curbuf != curbuf)
	    apply_autocmds(EVENT_BUFENTER, NULL, NULL, FALSE, curbuf);
	return TRUE;
    }
    return FALSE;
}
