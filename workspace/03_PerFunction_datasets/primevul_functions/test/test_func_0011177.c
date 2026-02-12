qf_open_new_cwindow(qf_info_T *qi, int height)
{
    buf_T	*qf_buf;
    win_T	*oldwin = curwin;
    tabpage_T	*prevtab = curtab;
    int		flags = 0;
    win_T	*win;

    qf_buf = qf_find_buf(qi);


    win = curwin;

    if (IS_QF_STACK(qi) && cmdmod.cmod_split == 0)


	win_goto(lastwin);

    if (cmdmod.cmod_split == 0)
	flags = WSP_BELOW;
    flags |= WSP_NEWLOC;
    if (win_split(height, flags) == FAIL)
	return FAIL;
    RESET_BINDING(curwin);

    if (IS_LL_STACK(qi))
    {


	curwin->w_llist_ref = qi;
	qi->qf_refcount++;
    }

    if (oldwin != curwin)
	oldwin = NULL;
    if (qf_buf != NULL)
    {

	if (do_ecmd(qf_buf->b_fnum, NULL, NULL, NULL, ECMD_ONE,
		    ECMD_HIDE + ECMD_OLDBUF + ECMD_NOWINENTER, oldwin) == FAIL)
	    return FAIL;
    }
    else
    {

	if (do_ecmd(0, NULL, NULL, NULL, ECMD_ONE, ECMD_HIDE + ECMD_NOWINENTER,
							       oldwin) == FAIL)
	    return FAIL;


	qi->qf_bufnr = curbuf->b_fnum;
    }


    if (!bt_quickfix(curbuf))
	qf_set_cwindow_options();


    if (curtab == prevtab && curwin->w_width == Columns)
	win_setheight(height);
    curwin->w_p_wfh = TRUE;
    if (win_valid(win))
	prevwin = win;

    return OK;
}
