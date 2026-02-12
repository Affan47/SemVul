ins_compl_show_filename(void)
{
    char	*lead = _("match in file");
    int		space = sc_col - vim_strsize((char_u *)lead) - 2;
    char_u	*s;
    char_u	*e;

    if (space <= 0)
	return;


    for (s = e = compl_shown_match->cp_fname; *e != NUL; MB_PTR_ADV(e))
    {
	space -= ptr2cells(e);
	while (space < 0)
	{
	    space += ptr2cells(s);
	    MB_PTR_ADV(s);
	}
    }
    msg_hist_off = TRUE;
    vim_snprintf((char *)IObuff, IOSIZE, "%s %s%s", lead,
	    s > compl_shown_match->cp_fname ? "<" : "", s);
    msg((char *)IObuff);
    msg_hist_off = FALSE;
    redraw_cmdline = FALSE;
}
