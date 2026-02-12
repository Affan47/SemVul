win_close(win_T *win, int free_buf)
{
    win_T	*wp;
    int		other_buffer = FALSE;
    int		close_curwin = FALSE;
    int		dir;
    int		help_window = FALSE;
    tabpage_T   *prev_curtab = curtab;
    frame_T	*win_frame = win->w_frame->fr_parent;

    if (ERROR_IF_POPUP_WINDOW)
	return FAIL;

    if (last_window())
    {
	emsg(_("E444: Cannot close last window"));
	return FAIL;
    }

    if (win->w_closing || (win->w_buffer != NULL
					       && win->w_buffer->b_locked > 0))
	return FAIL;
    if (win_unlisted(win))
    {
	emsg(_("E813: Cannot close autocmd or popup window"));
	return FAIL;
    }
    if ((firstwin == aucmd_win || lastwin == aucmd_win) && one_window())
    {
	emsg(_("E814: Cannot close window, only autocmd window would remain"));
	return FAIL;
    }


    if (close_last_window_tabpage(win, free_buf, prev_curtab))
      return FAIL;


    if (bt_help(win->w_buffer))
	help_window = TRUE;
    else
	clear_snapshot(curtab, SNAP_HELP_IDX);

    if (win == curwin)
    {
#ifdef FEAT_JOB_CHANNEL
	leaving_window(curwin);
#endif


	wp = frame2win(win_altframe(win, NULL));


	if (wp->w_buffer != curbuf)
	{
	    other_buffer = TRUE;
	    win->w_closing = TRUE;
	    apply_autocmds(EVENT_BUFLEAVE, NULL, NULL, FALSE, curbuf);
	    if (!win_valid(win))
		return FAIL;
	    win->w_closing = FALSE;
	    if (last_window())
		return FAIL;
	}
	win->w_closing = TRUE;
	apply_autocmds(EVENT_WINLEAVE, NULL, NULL, FALSE, curbuf);
	if (!win_valid(win))
	    return FAIL;
	win->w_closing = FALSE;
	if (last_window())
	    return FAIL;
#ifdef FEAT_EVAL

	if (aborting())
	    return FAIL;
#endif
    }

#ifdef FEAT_GUI


    if (gui.in_use)
	out_flush();
#endif

#ifdef FEAT_TEXT_PROP
    if (popup_win_closed(win) && !win_valid(win))
	return FAIL;
#endif
    win_close_buffer(win, free_buf ? DOBUF_UNLOAD : 0, TRUE);

    if (only_one_window() && win_valid(win) && win->w_buffer == NULL
	    && (last_window() || curtab != prev_curtab
		|| close_last_window_tabpage(win, free_buf, prev_curtab)))
    {


	if (curwin->w_buffer == NULL)
	    curwin->w_buffer = curbuf;
	getout(0);
    }


    if (curtab != prev_curtab && win_valid_any_tab(win)
						      && win->w_buffer == NULL)
    {

	win_close_othertab(win, FALSE, prev_curtab);
	return FAIL;
    }


    if (!win_valid(win) || last_window()
	    || close_last_window_tabpage(win, free_buf, prev_curtab))
	return FAIL;


    ++split_disallowed;


    wp = win_free_mem(win, &dir, NULL);


    if (win == curwin)
    {
	curwin = wp;
#ifdef FEAT_QUICKFIX
	if (wp->w_p_pvw || bt_quickfix(wp->w_buffer))
	{


	    for (;;)
	    {
		if (wp->w_next == NULL)
		    wp = firstwin;
		else
		    wp = wp->w_next;
		if (wp == curwin)
		    break;
		if (!wp->w_p_pvw && !bt_quickfix(wp->w_buffer))
		{
		    curwin = wp;
		    break;
		}
	    }
	}
#endif
	curbuf = curwin->w_buffer;
	close_curwin = TRUE;


	check_cursor();
    }
    if (p_ea && (*p_ead == 'b' || *p_ead == dir))


	win_equal(curwin, curwin->w_frame->fr_parent == win_frame, dir);
    else
	win_comp_pos();
    if (close_curwin)
    {
	win_enter_ext(wp, FALSE, TRUE, FALSE, TRUE, TRUE);
	if (other_buffer)

	    apply_autocmds(EVENT_BUFENTER, NULL, NULL, FALSE, curbuf);
    }

    --split_disallowed;


    last_status(FALSE);


    if (help_window)
	restore_snapshot(SNAP_HELP_IDX, close_curwin);

#if defined(FEAT_GUI)

    if (gui.in_use && !win_hasvertsplit())
	gui_init_which_components(NULL);
#endif

    redraw_all_later(NOT_VALID);
    return OK;
}
