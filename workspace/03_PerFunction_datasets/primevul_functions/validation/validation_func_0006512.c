get_userdefined_compl_info(colnr_T curs_col UNUSED)
{
    int		ret = FAIL;

#ifdef FEAT_COMPL_FUNC


    char_u	*line;
    typval_T	args[3];
    int		col;
    char_u	*funcname;
    pos_T	pos;
    int		save_State = State;
    callback_T	*cb;


    funcname = get_complete_funcname(ctrl_x_mode);
    if (*funcname == NUL)
    {
	semsg(_(e_option_str_is_not_set), ctrl_x_mode_function()
		? "completefunc" : "omnifunc");
	return FAIL;
    }

    args[0].v_type = VAR_NUMBER;
    args[0].vval.v_number = 1;
    args[1].v_type = VAR_STRING;
    args[1].vval.v_string = (char_u *)"";
    args[2].v_type = VAR_UNKNOWN;
    pos = curwin->w_cursor;
    ++textlock;
    cb = get_insert_callback(ctrl_x_mode);
    col = call_callback_retnr(cb, 2, args);
    --textlock;

    State = save_State;
    curwin->w_cursor = pos;
    validate_cursor();
    if (!EQUAL_POS(curwin->w_cursor, pos))
    {
	emsg(_(e_complete_function_deleted_text));
	return FAIL;
    }


    if (col == -2 || aborting())
	return FAIL;

    if (col == -3)
    {
	ctrl_x_mode = CTRL_X_NORMAL;
	edit_submode = NULL;
	if (!shortmess(SHM_COMPLETIONMENU))
	    msg_clr_cmdline();
	return FAIL;
    }


    compl_opt_refresh_always = FALSE;
    compl_opt_suppress_empty = FALSE;

    if (col < 0)
	col = curs_col;
    compl_col = col;
    if (compl_col > curs_col)
	compl_col = curs_col;


    line = ml_get(curwin->w_cursor.lnum);
    compl_length = curs_col - compl_col;
    compl_pattern = vim_strnsave(line + compl_col, compl_length);
    if (compl_pattern == NULL)
	return FAIL;

    ret = OK;
#endif

    return ret;
}
