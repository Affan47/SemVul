aucmd_restbuf(
    aco_save_T	*aco)
{
    int dummy;

    if (aco->use_aucmd_win)
    {
	--curbuf->b_nwindows;


	block_autocmds();
	if (curwin != aucmd_win)
	{
	    tabpage_T	*tp;
	    win_T	*wp;

	    FOR_ALL_TAB_WINDOWS(tp, wp)
	    {
		if (wp == aucmd_win)
		{
		    if (tp != curtab)
			goto_tabpage_tp(tp, TRUE, TRUE);
		    win_goto(aucmd_win);
		    goto win_found;
		}
	    }
	}
win_found:


	(void)winframe_remove(curwin, &dummy, NULL);
	win_remove(curwin, NULL);
	aucmd_win_used = FALSE;
	last_status(FALSE);

	if (!valid_tabpage_win(curtab))

	    close_tabpage(curtab);

	restore_snapshot(SNAP_AUCMD_IDX, FALSE);
	(void)win_comp_pos();
	unblock_autocmds();

	if (win_valid(aco->save_curwin))
	    curwin = aco->save_curwin;
	else

	    curwin = firstwin;
#ifdef FEAT_EVAL
	vars_clear(&aucmd_win->w_vars->dv_hashtab);
	hash_init(&aucmd_win->w_vars->dv_hashtab);
#endif
	curbuf = curwin->w_buffer;

	vim_free(globaldir);
	globaldir = aco->globaldir;


	check_cursor();
	if (curwin->w_topline > curbuf->b_ml.ml_line_count)
	{
	    curwin->w_topline = curbuf->b_ml.ml_line_count;
#ifdef FEAT_DIFF
	    curwin->w_topfill = 0;
#endif
	}
#if defined(FEAT_GUI)

	gui_mch_enable_scrollbar(&aucmd_win->w_scrollbars[SBAR_LEFT], FALSE);
	gui_mch_enable_scrollbar(&aucmd_win->w_scrollbars[SBAR_RIGHT], FALSE);
	gui_may_update_scrollbars();
#endif
    }
    else
    {

	if (win_valid(aco->save_curwin))
	{


	    if (curwin == aco->new_curwin
		    && curbuf != aco->new_curbuf.br_buf
		    && bufref_valid(&aco->new_curbuf)
		    && aco->new_curbuf.br_buf->b_ml.ml_mfp != NULL)
	    {
# if defined(FEAT_SYN_HL) || defined(FEAT_SPELL)
		if (curwin->w_s == &curbuf->b_s)
		    curwin->w_s = &aco->new_curbuf.br_buf->b_s;
# endif
		--curbuf->b_nwindows;
		curbuf = aco->new_curbuf.br_buf;
		curwin->w_buffer = curbuf;
		++curbuf->b_nwindows;
	    }

	    curwin = aco->save_curwin;
	    curbuf = curwin->w_buffer;


	    check_cursor();
	}
    }
}
