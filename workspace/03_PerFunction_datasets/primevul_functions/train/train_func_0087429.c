win_alloc(win_T *after UNUSED, int hidden UNUSED)
{
    win_T	*new_wp;


    new_wp = ALLOC_CLEAR_ONE(win_T);
    if (new_wp == NULL)
	return NULL;

    if (win_alloc_lines(new_wp) == FAIL)
    {
	vim_free(new_wp);
	return NULL;
    }

    new_wp->w_id = ++last_win_id;

#ifdef FEAT_EVAL

    new_wp->w_vars = dict_alloc();
    if (new_wp->w_vars == NULL)
    {
	win_free_lsize(new_wp);
	vim_free(new_wp);
	return NULL;
    }
    init_var_dict(new_wp->w_vars, &new_wp->w_winvar, VAR_SCOPE);
#endif


    block_autocmds();


    if (!hidden)
	win_append(after, new_wp);
    new_wp->w_wincol = 0;
    new_wp->w_width = Columns;


    new_wp->w_topline = 1;
#ifdef FEAT_DIFF
    new_wp->w_topfill = 0;
#endif
    new_wp->w_botline = 2;
    new_wp->w_cursor.lnum = 1;
    new_wp->w_scbind_pos = 1;


    new_wp->w_p_so = -1;
    new_wp->w_p_siso = -1;


    new_wp->w_fraction = 0;
    new_wp->w_prev_fraction_row = -1;

#ifdef FEAT_GUI
    if (gui.in_use)
    {
	gui_create_scrollbar(&new_wp->w_scrollbars[SBAR_LEFT],
		SBAR_LEFT, new_wp);
	gui_create_scrollbar(&new_wp->w_scrollbars[SBAR_RIGHT],
		SBAR_RIGHT, new_wp);
    }
#endif
#ifdef FEAT_FOLDING
    foldInitWin(new_wp);
#endif
    unblock_autocmds();
#ifdef FEAT_SEARCH_EXTRA
    new_wp->w_match_head = NULL;
    new_wp->w_next_match_id = 4;
#endif
    return new_wp;
}
