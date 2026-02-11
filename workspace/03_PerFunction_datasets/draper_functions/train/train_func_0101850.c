ex_copen(eap)
    exarg_T	*eap;
{
    qf_info_T	*qi = &ql_info;
    int		height;
    win_T	*win;
    tabpage_T	*prevtab = curtab;
    buf_T	*qf_buf;
    win_T	*oldwin = curwin;

    if (eap->cmdidx == CMD_lopen || eap->cmdidx == CMD_lwindow)
    {
	qi = GET_LOC_LIST(curwin);
	if (qi == NULL)
	{
	    EMSG(_(e_loclist));
	    return;
	}
    }

    if (eap->addr_count != 0)
	height = eap->line2;
    else
	height = QF_WINHEIGHT;

#ifdef FEAT_VISUAL
    reset_VIsual_and_resel();
#endif
#ifdef FEAT_GUI
    need_mouse_correct = TRUE;
#endif


    win = qf_find_win(qi);

    if (win != NULL && cmdmod.tab == 0)
	win_goto(win);
    else
    {
	qf_buf = qf_find_buf(qi);


	win = curwin;

	if (eap->cmdidx == CMD_copen || eap->cmdidx == CMD_cwindow)

	    win_goto(lastwin);
	if (win_split(height, WSP_BELOW | WSP_NEWLOC) == FAIL)
	    return;
	RESET_BINDING(curwin);

	if (eap->cmdidx == CMD_lopen || eap->cmdidx == CMD_lwindow)
	{


	    curwin->w_llist_ref = win->w_llist;
	    win->w_llist->qf_refcount++;
	}

	if (oldwin != curwin)
	    oldwin = NULL;
	if (qf_buf != NULL)

	    (void)do_ecmd(qf_buf->b_fnum, NULL, NULL, NULL, ECMD_ONE,
					     ECMD_HIDE + ECMD_OLDBUF, oldwin);
	else
	{

	    (void)do_ecmd(0, NULL, NULL, NULL, ECMD_ONE, ECMD_HIDE, oldwin);

	    set_option_value((char_u *)"swf", 0L, NULL, OPT_LOCAL);
	    set_option_value((char_u *)"bt", 0L, (char_u *)"quickfix",
								   OPT_LOCAL);
	    set_option_value((char_u *)"bh", 0L, (char_u *)"wipe", OPT_LOCAL);
	    RESET_BINDING(curwin);
#ifdef FEAT_DIFF
	    curwin->w_p_diff = FALSE;
#endif
#ifdef FEAT_FOLDING
	    set_option_value((char_u *)"fdm", 0L, (char_u *)"manual",
								   OPT_LOCAL);
#endif
	}


	if (curtab == prevtab
#ifdef FEAT_VERTSPLIT
		&& curwin->w_width == Columns
#endif
	   )
	    win_setheight(height);
	curwin->w_p_wfh = TRUE;
	if (win_valid(win))
	    prevwin = win;
    }


    qf_fill_buffer(qi);

    if (qi->qf_lists[qi->qf_curlist].qf_title != NULL)
	qf_set_title(qi);

    curwin->w_cursor.lnum = qi->qf_lists[qi->qf_curlist].qf_index;
    curwin->w_cursor.col = 0;
    check_cursor();
    update_topline();
}
