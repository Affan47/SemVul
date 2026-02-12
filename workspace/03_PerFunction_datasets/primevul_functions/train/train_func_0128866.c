internal_format(
    int		textwidth,
    int		second_indent,
    int		flags,
    int		format_only,
    int		c)
{
    int		cc;
    int		save_char = NUL;
    int		haveto_redraw = FALSE;
    int		fo_ins_blank = has_format_option(FO_INS_BLANK);
    int		fo_multibyte = has_format_option(FO_MBYTE_BREAK);
    int		fo_white_par = has_format_option(FO_WHITE_PAR);
    int		first_line = TRUE;
    colnr_T	leader_len;
    int		no_leader = FALSE;
    int		do_comments = (flags & INSCHAR_DO_COM);
#ifdef FEAT_LINEBREAK
    int		has_lbr = curwin->w_p_lbr;


    curwin->w_p_lbr = FALSE;
#endif


    if (!curbuf->b_p_ai && !(State & VREPLACE_FLAG))
    {
	cc = gchar_cursor();
	if (VIM_ISWHITE(cc))
	{
	    save_char = cc;
	    pchar_cursor('x');
	}
    }


    while (!got_int)
    {
	int	startcol;
	int	wantcol;
	int	foundcol;
	int	end_foundcol = 0;
	colnr_T	len;
	colnr_T	virtcol;
	int	orig_col = 0;
	char_u	*saved_text = NULL;
	colnr_T	col;
	colnr_T	end_col;
	int	wcc;

	virtcol = get_nolist_virtcol()
		+ char2cells(c != NUL ? c : gchar_cursor());
	if (virtcol <= (colnr_T)textwidth)
	    break;

	if (no_leader)
	    do_comments = FALSE;
	else if (!(flags & INSCHAR_FORMAT)
				       && has_format_option(FO_WRAP_COMS))
	    do_comments = TRUE;


	if (do_comments)
	    leader_len = get_leader_len(ml_get_curline(), NULL, FALSE, TRUE);
	else
	    leader_len = 0;


	if (leader_len == 0)
	    no_leader = TRUE;
	if (!(flags & INSCHAR_FORMAT)
		&& leader_len == 0
		&& !has_format_option(FO_WRAP))

	    break;
	if ((startcol = curwin->w_cursor.col) == 0)
	    break;


	coladvance((colnr_T)textwidth);
	wantcol = curwin->w_cursor.col;

	curwin->w_cursor.col = startcol;
	foundcol = 0;


	while ((!fo_ins_blank && !has_format_option(FO_INS_VI))
		    || (flags & INSCHAR_FORMAT)
		    || curwin->w_cursor.lnum != Insstart.lnum
		    || curwin->w_cursor.col >= Insstart.col)
	{
	    if (curwin->w_cursor.col == startcol && c != NUL)
		cc = c;
	    else
		cc = gchar_cursor();
	    if (WHITECHAR(cc))
	    {

		end_col = curwin->w_cursor.col;


		wcc = 0;
		while (curwin->w_cursor.col > 0 && WHITECHAR(cc))
		{
		    dec_cursor();
		    cc = gchar_cursor();


		    if (wcc < 2)
		        wcc++;
		}
		if (curwin->w_cursor.col == 0 && WHITECHAR(cc))
		    break;


		if (has_format_option(FO_PERIOD_ABBR) && cc == '.' && wcc < 2)
		    continue;


		if (curwin->w_cursor.col < leader_len)
		    break;
		if (has_format_option(FO_ONE_LETTER))
		{

		    if (curwin->w_cursor.col == 0)
			break;

		    if (curwin->w_cursor.col <= leader_len)
			break;
		    col = curwin->w_cursor.col;
		    dec_cursor();
		    cc = gchar_cursor();

		    if (WHITECHAR(cc))
			continue;
		    curwin->w_cursor.col = col;
		}

		inc_cursor();

		end_foundcol = end_col + 1;
		foundcol = curwin->w_cursor.col;
		if (curwin->w_cursor.col <= (colnr_T)wantcol)
		    break;
	    }
	    else if (cc >= 0x100 && fo_multibyte)
	    {

		if (curwin->w_cursor.col != startcol)
		{

		    if (curwin->w_cursor.col < leader_len)
			break;
		    col = curwin->w_cursor.col;
		    inc_cursor();

		    if (foundcol != curwin->w_cursor.col)
		    {
			foundcol = curwin->w_cursor.col;
			end_foundcol = foundcol;
			if (curwin->w_cursor.col <= (colnr_T)wantcol)
			    break;
		    }
		    curwin->w_cursor.col = col;
		}

		if (curwin->w_cursor.col == 0)
		    break;

		col = curwin->w_cursor.col;

		dec_cursor();
		cc = gchar_cursor();

		if (WHITECHAR(cc))
		    continue;

		if (curwin->w_cursor.col < leader_len)
		    break;

		curwin->w_cursor.col = col;

		foundcol = curwin->w_cursor.col;
		end_foundcol = foundcol;
		if (curwin->w_cursor.col <= (colnr_T)wantcol)
		    break;
	    }
	    if (curwin->w_cursor.col == 0)
		break;
	    dec_cursor();
	}

	if (foundcol == 0)
	{
	    curwin->w_cursor.col = startcol;
	    break;
	}


	undisplay_dollar();


	if (State & VREPLACE_FLAG)
	    orig_col = startcol;
	else
	    replace_offset = startcol - end_foundcol;


	curwin->w_cursor.col = foundcol;
	while ((cc = gchar_cursor(), WHITECHAR(cc))
		    && (!fo_white_par || curwin->w_cursor.col < startcol))
	    inc_cursor();
	startcol -= curwin->w_cursor.col;
	if (startcol < 0)
	    startcol = 0;

	if (State & VREPLACE_FLAG)
	{


	    saved_text = vim_strsave(ml_get_cursor());
	    curwin->w_cursor.col = orig_col;
	    if (saved_text == NULL)
		break;
	    saved_text[startcol] = NUL;


	    if (!fo_white_par)
		backspace_until_column(foundcol);
	}
	else
	{

	    if (!fo_white_par)
		curwin->w_cursor.col = foundcol;
	}


	open_line(FORWARD, OPENLINE_DELSPACES + OPENLINE_MARKFIX
		+ (fo_white_par ? OPENLINE_KEEPTRAIL : 0)
		+ (do_comments ? OPENLINE_DO_COM : 0)
		+ ((flags & INSCHAR_COM_LIST) ? OPENLINE_COM_LIST : 0)
		, ((flags & INSCHAR_COM_LIST) ? second_indent : old_indent));
	if (!(flags & INSCHAR_COM_LIST))
	    old_indent = 0;

	replace_offset = 0;
	if (first_line)
	{
	    if (!(flags & INSCHAR_COM_LIST))
	    {


		if (second_indent < 0 && has_format_option(FO_Q_NUMBER))
		    second_indent =
				 get_number_indent(curwin->w_cursor.lnum - 1);
		if (second_indent >= 0)
		{
		    if (State & VREPLACE_FLAG)
			change_indent(INDENT_SET, second_indent,
							    FALSE, NUL, TRUE);
		    else
			if (leader_len > 0 && second_indent - leader_len > 0)
		    {
			int i;
			int padding = second_indent - leader_len;


			for (i = 0; i < padding; i++)
			    ins_str((char_u *)" ");
		    }
		    else
		    {
			(void)set_indent(second_indent, SIN_CHANGED);
		    }
		}
	    }
	    first_line = FALSE;
	}

	if (State & VREPLACE_FLAG)
	{


	    ins_bytes(saved_text);
	    vim_free(saved_text);
	}
	else
	{


	    curwin->w_cursor.col += startcol;
	    len = (colnr_T)STRLEN(ml_get_curline());
	    if (curwin->w_cursor.col > len)
		curwin->w_cursor.col = len;
	}

	haveto_redraw = TRUE;
#ifdef FEAT_CINDENT
	can_cindent = TRUE;
#endif

	did_ai = FALSE;
#ifdef FEAT_SMARTINDENT
	did_si = FALSE;
	can_si = FALSE;
	can_si_back = FALSE;
#endif
	line_breakcheck();
    }

    if (save_char != NUL)
	pchar_cursor(save_char);

#ifdef FEAT_LINEBREAK
    curwin->w_p_lbr = has_lbr;
#endif
    if (!format_only && haveto_redraw)
    {
	update_topline();
	redraw_curbuf_later(VALID);
    }
}
