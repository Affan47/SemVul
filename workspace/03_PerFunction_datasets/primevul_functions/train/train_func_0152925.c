format_lines(
    linenr_T	line_count,
    int		avoid_fex)
{
    int		max_len;
    int		is_not_par;
    int		next_is_not_par;
    int		is_end_par;
    int		prev_is_end_par = FALSE;
    int		next_is_start_par = FALSE;
    int		leader_len = 0;
    int		next_leader_len;
    char_u	*leader_flags = NULL;
    char_u	*next_leader_flags = NULL;
    int		do_comments;
    int		do_comments_list = 0;
    int		advance = TRUE;
    int		second_indent = -1;

    int		do_second_indent;
    int		do_number_indent;
    int		do_trail_white;
    int		first_par_line = TRUE;
    int		smd_save;
    long	count;
    int		need_set_indent = TRUE;
    linenr_T	first_line = curwin->w_cursor.lnum;
    int		force_format = FALSE;
    int		old_State = State;


    max_len = comp_textwidth(TRUE) * 3;


    do_comments = has_format_option(FO_Q_COMS);
    do_second_indent = has_format_option(FO_Q_SECOND);
    do_number_indent = has_format_option(FO_Q_NUMBER);
    do_trail_white = has_format_option(FO_WHITE_PAR);


    if (curwin->w_cursor.lnum > 1)
	is_not_par = fmt_check_par(curwin->w_cursor.lnum - 1
				, &leader_len, &leader_flags, do_comments);
    else
	is_not_par = TRUE;
    next_is_not_par = fmt_check_par(curwin->w_cursor.lnum
			  , &next_leader_len, &next_leader_flags, do_comments);
    is_end_par = (is_not_par || next_is_not_par);
    if (!is_end_par && do_trail_white)
	is_end_par = !ends_in_white(curwin->w_cursor.lnum - 1);

    curwin->w_cursor.lnum--;
    for (count = line_count; count != 0 && !got_int; --count)
    {

	if (advance)
	{
	    curwin->w_cursor.lnum++;
	    prev_is_end_par = is_end_par;
	    is_not_par = next_is_not_par;
	    leader_len = next_leader_len;
	    leader_flags = next_leader_flags;
	}


	if (count == 1 || curwin->w_cursor.lnum == curbuf->b_ml.ml_line_count)
	{
	    next_is_not_par = TRUE;
	    next_leader_len = 0;
	    next_leader_flags = NULL;
	}
	else
	{
	    next_is_not_par = fmt_check_par(curwin->w_cursor.lnum + 1
			  , &next_leader_len, &next_leader_flags, do_comments);
	    if (do_number_indent)
		next_is_start_par =
			   (get_number_indent(curwin->w_cursor.lnum + 1) > 0);
	}
	advance = TRUE;
	is_end_par = (is_not_par || next_is_not_par || next_is_start_par);
	if (!is_end_par && do_trail_white)
	    is_end_par = !ends_in_white(curwin->w_cursor.lnum);


	if (is_not_par)
	{
	    if (line_count < 0)
		break;
	}
	else
	{


	    if (first_par_line
		    && (do_second_indent || do_number_indent)
		    && prev_is_end_par
		    && curwin->w_cursor.lnum < curbuf->b_ml.ml_line_count)
	    {
		if (do_second_indent && !LINEEMPTY(curwin->w_cursor.lnum + 1))
		{
		    if (leader_len == 0 && next_leader_len == 0)
		    {

			second_indent =
				   get_indent_lnum(curwin->w_cursor.lnum + 1);
		    }
		    else
		    {
			second_indent = next_leader_len;
			do_comments_list = 1;
		    }
		}
		else if (do_number_indent)
		{
		    if (leader_len == 0 && next_leader_len == 0)
		    {

			second_indent =
				     get_number_indent(curwin->w_cursor.lnum);
		    }
		    else
		    {

			second_indent =
				     get_number_indent(curwin->w_cursor.lnum);
			do_comments_list = 1;
		    }
		}
	    }


	    if (curwin->w_cursor.lnum >= curbuf->b_ml.ml_line_count
		    || !same_leader(curwin->w_cursor.lnum,
					leader_len, leader_flags,
					   next_leader_len, next_leader_flags))
	    {


		if (next_leader_flags == NULL
			|| STRNCMP(next_leader_flags, "://", 3) != 0
			|| check_linecomment(ml_get_curline()) == MAXCOL)
		is_end_par = TRUE;
	    }


	    if (is_end_par || force_format)
	    {
		if (need_set_indent)
		{
		    int		indent = 0;


		    if (curwin->w_cursor.lnum == first_line)
			indent = get_indent();
		    else if (curbuf->b_p_lisp)
			indent = get_lisp_indent();
		    else
		    {
			if (cindent_on())
			{
			    indent =
# ifdef FEAT_EVAL
				 *curbuf->b_p_inde != NUL ? get_expr_indent() :
# endif
				 get_c_indent();
			}
			else
			    indent = get_indent();
		    }
		    (void)set_indent(indent, SIN_CHANGED);
		}


		State = MODE_NORMAL;
		coladvance((colnr_T)MAXCOL);
		while (curwin->w_cursor.col && vim_isspace(gchar_cursor()))
		    dec_cursor();


		State = MODE_INSERT;
		smd_save = p_smd;
		p_smd = FALSE;
		insertchar(NUL, INSCHAR_FORMAT
			+ (do_comments ? INSCHAR_DO_COM : 0)
			+ (do_comments && do_comments_list
						       ? INSCHAR_COM_LIST : 0)
			+ (avoid_fex ? INSCHAR_NO_FEX : 0), second_indent);
		State = old_State;
		p_smd = smd_save;
		second_indent = -1;

		need_set_indent = is_end_par;
		if (is_end_par)
		{


		    if (line_count < 0)
			break;
		    first_par_line = TRUE;
		}
		force_format = FALSE;
	    }


	    if (!is_end_par)
	    {
		advance = FALSE;
		curwin->w_cursor.lnum++;
		curwin->w_cursor.col = 0;
		if (line_count < 0 && u_save_cursor() == FAIL)
		    break;
		if (next_leader_len > 0)
		{
		    (void)del_bytes((long)next_leader_len, FALSE, FALSE);
		    mark_col_adjust(curwin->w_cursor.lnum, (colnr_T)0, 0L,
						    (long)-next_leader_len, 0);
		}
		else if (second_indent > 0)
		{
		    int indent = getwhitecols_curline();

		    if (indent > 0)
		    {
			(void)del_bytes(indent, FALSE, FALSE);
			mark_col_adjust(curwin->w_cursor.lnum,
					       (colnr_T)0, 0L, (long)-indent, 0);
		    }
		}
		curwin->w_cursor.lnum--;
		if (do_join(2, TRUE, FALSE, FALSE, FALSE) == FAIL)
		{
		    beep_flush();
		    break;
		}
		first_par_line = FALSE;

		if (STRLEN(ml_get_curline()) > (size_t)max_len)
		    force_format = TRUE;
		else
		    force_format = FALSE;
	    }
	}
	line_breakcheck();
    }
}
