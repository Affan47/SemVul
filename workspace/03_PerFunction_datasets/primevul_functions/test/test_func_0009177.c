do_move(linenr_T line1, linenr_T line2, linenr_T dest)
{
    char_u	*str;
    linenr_T	l;
    linenr_T	extra;
    linenr_T	num_lines;
    linenr_T	last_line;
#ifdef FEAT_FOLDING
    win_T	*win;
    tabpage_T	*tp;
#endif

    if (dest >= line1 && dest < line2)
    {
	emsg(_(e_cannot_move_range_of_lines_into_itself));
	return FAIL;
    }


    if (dest == line1 - 1 || dest == line2)
    {


	if (dest >= line1)
	    curwin->w_cursor.lnum = dest;
	else
	    curwin->w_cursor.lnum = dest + (line2 - line1) + 1;

	return OK;
    }

    num_lines = line2 - line1 + 1;


    if (u_save(dest, dest + 1) == FAIL)
	return FAIL;
    for (extra = 0, l = line1; l <= line2; l++)
    {
	str = vim_strsave(ml_get(l + extra));
	if (str != NULL)
	{
	    ml_append(dest + l - line1, str, (colnr_T)0, FALSE);
	    vim_free(str);
	    if (dest < line1)
		extra++;
	}
    }


    last_line = curbuf->b_ml.ml_line_count;
    mark_adjust_nofold(line1, line2, last_line - line2, 0L);
    if (dest >= line2)
    {
	mark_adjust_nofold(line2 + 1, dest, -num_lines, 0L);
#ifdef FEAT_FOLDING
	FOR_ALL_TAB_WINDOWS(tp, win) {
	    if (win->w_buffer == curbuf)
		foldMoveRange(&win->w_folds, line1, line2, dest);
	}
#endif
	if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	{
	    curbuf->b_op_start.lnum = dest - num_lines + 1;
	    curbuf->b_op_end.lnum = dest;
	}
    }
    else
    {
	mark_adjust_nofold(dest + 1, line1 - 1, num_lines, 0L);
#ifdef FEAT_FOLDING
	FOR_ALL_TAB_WINDOWS(tp, win) {
	    if (win->w_buffer == curbuf)
		foldMoveRange(&win->w_folds, dest + 1, line1 - 1, line2);
	}
#endif
	if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	{
	    curbuf->b_op_start.lnum = dest + 1;
	    curbuf->b_op_end.lnum = dest + num_lines;
	}
    }
    if ((cmdmod.cmod_flags & CMOD_LOCKMARKS) == 0)
	curbuf->b_op_start.col = curbuf->b_op_end.col = 0;
    mark_adjust_nofold(last_line - num_lines + 1, last_line,
					     -(last_line - dest - extra), 0L);


    if (u_save(line1 + extra - 1, line2 + extra + 1) == FAIL)
	return FAIL;

    for (l = line1; l <= line2; l++)
	ml_delete_flags(line1 + extra, ML_DEL_MESSAGE);

    if (!global_busy && num_lines > p_report)
	smsg(NGETTEXT("%ld line moved", "%ld lines moved", num_lines),
			(long)num_lines);


    if (dest >= line1)
	curwin->w_cursor.lnum = dest;
    else
	curwin->w_cursor.lnum = dest + (line2 - line1) + 1;

    if (line1 < dest)
    {
	dest += num_lines + 1;
	last_line = curbuf->b_ml.ml_line_count;
	if (dest > last_line + 1)
	    dest = last_line + 1;
	changed_lines(line1, 0, dest, 0L);
    }
    else
	changed_lines(dest + 1, 0, line1 + num_lines, 0L);

    return OK;
}
