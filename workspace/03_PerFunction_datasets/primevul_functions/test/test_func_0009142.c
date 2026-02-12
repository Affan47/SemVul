get_breakindent_win(
    win_T	*wp,
    char_u	*line)
{
    static int	    prev_indent = 0;
    static long	    prev_ts     = 0L;
    static char_u   *prev_line = NULL;
    static varnumber_T prev_tick = 0;
# ifdef FEAT_VARTABS
    static int      *prev_vts = NULL;
# endif
    static int      prev_list = 0;
    static int      prev_listopt = 0;

    static char_u   *prev_flp = NULL;
    int		    bri = 0;

    const int	    eff_wwidth = wp->w_width
			    - ((wp->w_p_nu || wp->w_p_rnu)
				&& (vim_strchr(p_cpo, CPO_NUMCOL) == NULL)
						? number_width(wp) + 1 : 0);


    if (prev_line != line || prev_ts != wp->w_buffer->b_p_ts
	    || prev_tick != CHANGEDTICK(wp->w_buffer)
	    || prev_listopt != wp->w_briopt_list
	    || (prev_flp == NULL
		|| (STRCMP(prev_flp, get_flp_value(wp->w_buffer)) != 0))
# ifdef FEAT_VARTABS
	    || prev_vts != wp->w_buffer->b_p_vts_array
# endif
	)
    {
	prev_line = line;
	prev_ts = wp->w_buffer->b_p_ts;
	prev_tick = CHANGEDTICK(wp->w_buffer);
# ifdef FEAT_VARTABS
	prev_vts = wp->w_buffer->b_p_vts_array;
	if (wp->w_briopt_vcol == 0)
	    prev_indent = get_indent_str_vtab(line,
				     (int)wp->w_buffer->b_p_ts,
				    wp->w_buffer->b_p_vts_array, wp->w_p_list);
# else
	if (wp->w_briopt_vcol == 0)
	    prev_indent = get_indent_str(line,
				     (int)wp->w_buffer->b_p_ts, wp->w_p_list);
# endif
	prev_listopt = wp->w_briopt_list;
	prev_list = 0;
	vim_free(prev_flp);
	prev_flp = vim_strsave(get_flp_value(wp->w_buffer));

	if (wp->w_briopt_list != 0 && wp->w_briopt_vcol == 0)
	{
	    regmatch_T	    regmatch;

	    regmatch.regprog = vim_regcomp(prev_flp,
				   RE_MAGIC + RE_STRING + RE_AUTO + RE_STRICT);

	    if (regmatch.regprog != NULL)
	    {
		regmatch.rm_ic = FALSE;
		if (vim_regexec(&regmatch, line, 0))
		{
		    if (wp->w_briopt_list > 0)
			prev_list = wp->w_briopt_list;
		    else
			prev_list = (*regmatch.endp - *regmatch.startp);
		}
		vim_regfree(regmatch.regprog);
	    }
	}
    }
    if (wp->w_briopt_vcol != 0)
    {

	bri = wp->w_briopt_vcol;
	prev_list = 0;
    }
    else
	bri = prev_indent + wp->w_briopt_shift;


    bri += win_col_off2(wp);


    if (wp->w_briopt_list != 0)
    {
	if (wp->w_briopt_list > 0)
	    bri += prev_list;
	else
	    bri = prev_list;
    }


    if (wp->w_briopt_sbr)
	bri -= vim_strsize(get_showbreak_value(wp));


    if (bri < 0)
	bri = 0;


    else if (bri > eff_wwidth - wp->w_briopt_min)
	bri = (eff_wwidth - wp->w_briopt_min < 0)
					   ? 0 : eff_wwidth - wp->w_briopt_min;

    return bri;
}
