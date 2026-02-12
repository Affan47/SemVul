update_screen(int type_arg)
{
    int		type = type_arg;
    win_T	*wp;
    static int	did_intro = FALSE;
#ifdef FEAT_GUI
    int		did_one = FALSE;
    int		did_undraw = FALSE;
    int		gui_cursor_col = 0;
    int		gui_cursor_row = 0;
#endif
    int		no_update = FALSE;
    int		save_pum_will_redraw = pum_will_redraw;


    if (!screen_valid(TRUE))
	return FAIL;

    if (type == VALID_NO_UPDATE)
    {
	no_update = TRUE;
	type = 0;
    }

#ifdef FEAT_EVAL
    {
	buf_T *buf;


	FOR_ALL_BUFFERS(buf)
	    invoke_listeners(buf);
    }
#endif

#ifdef FEAT_DIFF

    if (need_diff_redraw)
	diff_redraw(TRUE);
#endif

    if (must_redraw)
    {
	if (type < must_redraw)
	    type = must_redraw;


	must_redraw = 0;
    }


    if (curwin->w_lines_valid == 0 && type < NOT_VALID
#ifdef FEAT_TERMINAL
	    && !term_do_update_window(curwin)
#endif
		)
	type = NOT_VALID;


    if (!redrawing() || updating_screen)
    {
	redraw_later(type);
	must_redraw = type;
	if (type > INVERTED_ALL)
	    curwin->w_lines_valid = 0;
	return FAIL;
    }
    updating_screen = TRUE;

#ifdef FEAT_PROP_POPUP


    may_update_popup_mask(type);
#endif

#ifdef FEAT_SYN_HL
    ++display_tick;

#endif
    if (no_update)
	++no_win_do_lines_ins;


    if (msg_scrolled)
    {
	clear_cmdline = TRUE;
	if (msg_scrolled > Rows - 5)
	    type = CLEAR;
	else if (type != CLEAR)
	{
	    check_for_delay(FALSE);
	    if (screen_ins_lines(0, 0, msg_scrolled, (int)Rows, 0, NULL)
								       == FAIL)
		type = CLEAR;
	    FOR_ALL_WINDOWS(wp)
	    {
		if (wp->w_winrow < msg_scrolled)
		{
		    if (W_WINROW(wp) + wp->w_height > msg_scrolled
			    && wp->w_redr_type < REDRAW_TOP
			    && wp->w_lines_valid > 0
			    && wp->w_topline == wp->w_lines[0].wl_lnum)
		    {
			wp->w_upd_rows = msg_scrolled - W_WINROW(wp);
			wp->w_redr_type = REDRAW_TOP;
		    }
		    else
		    {
			wp->w_redr_type = NOT_VALID;
			if (W_WINROW(wp) + wp->w_height + wp->w_status_height
							       <= msg_scrolled)
			    wp->w_redr_status = TRUE;
		    }
		}
	    }
	    if (!no_update)
		redraw_cmdline = TRUE;
	    redraw_tabline = TRUE;
	}
	msg_scrolled = 0;
	need_wait_return = FALSE;
    }


    compute_cmdrow();


    if (need_highlight_changed)
	highlight_changed();

    if (type == CLEAR)
    {
	screenclear();
	type = NOT_VALID;

	must_redraw = 0;
    }

    if (clear_cmdline)
	check_for_delay(FALSE);

#ifdef FEAT_LINEBREAK


    if (curwin->w_redr_type < NOT_VALID
	   && curwin->w_nrwidth != ((curwin->w_p_nu || curwin->w_p_rnu)
				    ? number_width(curwin) : 0))
	curwin->w_redr_type = NOT_VALID;
#endif


    if (type == INVERTED)
	update_curswant();
    if (curwin->w_redr_type < type
	    && !((type == VALID
		    && curwin->w_lines[0].wl_valid
#ifdef FEAT_DIFF
		    && curwin->w_topfill == curwin->w_old_topfill
		    && curwin->w_botfill == curwin->w_old_botfill
#endif
		    && curwin->w_topline == curwin->w_lines[0].wl_lnum)
		|| (type == INVERTED
		    && VIsual_active
		    && curwin->w_old_cursor_lnum == curwin->w_cursor.lnum
		    && curwin->w_old_visual_mode == VIsual_mode
		    && (curwin->w_valid & VALID_VIRTCOL)
		    && curwin->w_old_curswant == curwin->w_curswant)
		))
	curwin->w_redr_type = type;


    if (redraw_tabline || type >= NOT_VALID)
	draw_tabline();

#ifdef FEAT_SYN_HL


    FOR_ALL_WINDOWS(wp)
    {
	if (wp->w_buffer->b_mod_set)
	{
	    win_T	*wwp;


	    for (wwp = firstwin; wwp != wp; wwp = wwp->w_next)
		if (wwp->w_buffer == wp->w_buffer)
		    break;
	    if (wwp == wp && syntax_present(wp))
		syn_stack_apply_changes(wp->w_buffer);
	}
    }
#endif

    if (pum_redraw_in_same_position())


	pum_will_redraw = TRUE;


#if defined(FEAT_SEARCH_EXTRA) || defined(FEAT_CLIPBOARD)
    did_update_one_window = FALSE;
#endif
#ifdef FEAT_SEARCH_EXTRA
    screen_search_hl.rm.regprog = NULL;
#endif
    FOR_ALL_WINDOWS(wp)
    {
	if (wp->w_redr_type != 0)
	{
	    cursor_off();
#ifdef FEAT_GUI
	    if (!did_one)
	    {
		did_one = TRUE;


		if (gui.in_use && (wp == curwin || cursor_is_sleeping()))
		{
		    gui_cursor_col = gui.cursor_col;
		    gui_cursor_row = gui.cursor_row;
		    gui_undraw_cursor();
		    did_undraw = TRUE;
		}
	    }
#endif
	    win_update(wp);
	}


	if (wp->w_redr_status)
	{
	    cursor_off();
	    win_redr_status(wp, TRUE);
	}
    }
#if defined(FEAT_SEARCH_EXTRA)
    end_search_hl();
#endif


    pum_will_redraw = save_pum_will_redraw;
    pum_may_redraw();


    FOR_ALL_WINDOWS(wp)
	wp->w_buffer->b_mod_set = FALSE;

#ifdef FEAT_PROP_POPUP

    update_popups(win_update);
#endif

#ifdef FEAT_TERMINAL
    FOR_ALL_WINDOWS(wp)


	term_did_update_window(wp);
#endif

    after_updating_screen(TRUE);


    if (clear_cmdline || redraw_cmdline || redraw_mode)
	showmode();

    if (no_update)
	--no_win_do_lines_ins;


    if (!did_intro)
	maybe_intro_message();
    did_intro = TRUE;

#ifdef FEAT_GUI


    if (gui.in_use)
    {
	if (did_undraw && !gui_mch_is_blink_off())
	{
	    mch_disable_flush();
	    out_flush();
	    mch_enable_flush();


	    gui.col = gui_cursor_col;
	    gui.row = gui_cursor_row;
	    gui.col = mb_fix_col(gui.col, gui.row);
	    gui_update_cursor(FALSE, FALSE);
	    gui_may_flush();
	    screen_cur_col = gui.col;
	    screen_cur_row = gui.row;
	}
	else
	    out_flush();
	gui_update_scrollbars(FALSE);
    }
#endif
    return OK;
}
