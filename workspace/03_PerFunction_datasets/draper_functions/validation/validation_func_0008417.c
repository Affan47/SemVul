ins_del()
{
    int	    temp;

    if (stop_arrow() == FAIL)
	return;
    if (gchar_cursor() == NUL)
    {
	temp = curwin->w_cursor.col;
	if (!can_bs(BS_EOL)
		|| u_save((linenr_T)(curwin->w_cursor.lnum - 1),
		    (linenr_T)(curwin->w_cursor.lnum + 2)) == FAIL
		|| do_join(FALSE) == FAIL)
	    vim_beep();
	else
	    curwin->w_cursor.col = temp;
    }
    else if (del_char(FALSE) == FAIL)
	vim_beep();
    did_ai = FALSE;
#ifdef FEAT_SMARTINDENT
    did_si = FALSE;
    can_si = FALSE;
    can_si_back = FALSE;
#endif
    AppendCharToRedobuff(K_DEL);
}
