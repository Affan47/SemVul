get_spec_reg(
    int		regname,
    char_u	**argp,
    int		*allocated,
    int		errmsg)
{
    int		cnt;

    *argp = NULL;
    *allocated = FALSE;
    switch (regname)
    {
	case '%':
	    if (errmsg)
		check_fname();
	    *argp = curbuf->b_fname;
	    return TRUE;

	case '#':
	    *argp = getaltfname(errmsg);
	    return TRUE;

#ifdef FEAT_EVAL
	case '=':
	    *argp = get_expr_line();
	    *allocated = TRUE;
	    return TRUE;
#endif

	case ':':
	    if (last_cmdline == NULL && errmsg)
		emsg(_(e_no_previous_command_line));
	    *argp = last_cmdline;
	    return TRUE;

	case '/':
	    if (last_search_pat() == NULL && errmsg)
		emsg(_(e_no_previous_regular_expression));
	    *argp = last_search_pat();
	    return TRUE;

	case '.':
	    *argp = get_last_insert_save();
	    *allocated = TRUE;
	    if (*argp == NULL && errmsg)
		emsg(_(e_no_inserted_text_yet));
	    return TRUE;

#ifdef FEAT_SEARCHPATH
	case Ctrl_F:
	case Ctrl_P:
	    if (!errmsg)
		return FALSE;
	    *argp = file_name_at_cursor(FNAME_MESS | FNAME_HYP
			    | (regname == Ctrl_P ? FNAME_EXP : 0), 1L, NULL);
	    *allocated = TRUE;
	    return TRUE;
#endif

	case Ctrl_W:
	case Ctrl_A:
	    if (!errmsg)
		return FALSE;
	    cnt = find_ident_under_cursor(argp, regname == Ctrl_W
				   ?  (FIND_IDENT|FIND_STRING) : FIND_STRING);
	    *argp = cnt ? vim_strnsave(*argp, cnt) : NULL;
	    *allocated = TRUE;
	    return TRUE;

	case Ctrl_L:
	    if (!errmsg)
		return FALSE;

	    *argp = ml_get_buf(curwin->w_buffer,
			curwin->w_cursor.lnum, FALSE);
	    return TRUE;

	case '_':
	    *argp = (char_u *)"";
	    return TRUE;
    }

    return FALSE;
}
