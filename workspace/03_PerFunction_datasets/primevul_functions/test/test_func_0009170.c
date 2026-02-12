ex_drop(exarg_T *eap)
{
    int		split = FALSE;
    win_T	*wp;
    buf_T	*buf;
    tabpage_T	*tp;

    if (ERROR_IF_POPUP_WINDOW || ERROR_IF_TERM_POPUP_WINDOW)
	return;


    set_arglist(eap->arg);


    if (ARGCOUNT == 0)
	return;

    if (cmdmod.cmod_tab)
    {


	ex_all(eap);
    }
    else
    {


	buf = buflist_findnr(ARGLIST[0].ae_fnum);

	FOR_ALL_TAB_WINDOWS(tp, wp)
	{
	    if (wp->w_buffer == buf)
	    {
		goto_tabpage_win(tp, wp);
		curwin->w_arg_idx = 0;
		if (!bufIsChanged(curbuf))
		{
		    int save_ar = curbuf->b_p_ar;


		    curbuf->b_p_ar = TRUE;
		    buf_check_timestamp(curbuf, FALSE);
		    curbuf->b_p_ar = save_ar;
		}
		return;
	    }
	}


	if (!buf_hide(curbuf))
	{
	    ++emsg_off;
	    split = check_changed(curbuf, CCGD_AW | CCGD_EXCMD);
	    --emsg_off;
	}


	if (split)
	{
	    eap->cmdidx = CMD_sfirst;
	    eap->cmd[0] = 's';
	}
	else
	    eap->cmdidx = CMD_first;
	ex_rewind(eap);
    }
}
