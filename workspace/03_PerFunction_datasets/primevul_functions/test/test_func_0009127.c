get_expr_indent(void)
{
    int		indent = -1;
    char_u	*inde_copy;
    pos_T	save_pos;
    colnr_T	save_curswant;
    int		save_set_curswant;
    int		save_State;
    int		use_sandbox = was_set_insecurely((char_u *)"indentexpr",
								   OPT_LOCAL);
    sctx_T	save_sctx = current_sctx;


    save_pos = curwin->w_cursor;
    save_curswant = curwin->w_curswant;
    save_set_curswant = curwin->w_set_curswant;
    set_vim_var_nr(VV_LNUM, curwin->w_cursor.lnum);
    if (use_sandbox)
	++sandbox;
    ++textlock;
    current_sctx = curbuf->b_p_script_ctx[BV_INDE];


    inde_copy = vim_strsave(curbuf->b_p_inde);
    if (inde_copy != NULL)
    {
	indent = (int)eval_to_number(inde_copy);
	vim_free(inde_copy);
    }

    if (use_sandbox)
	--sandbox;
    --textlock;
    current_sctx = save_sctx;


    save_State = State;
    State = MODE_INSERT;
    curwin->w_cursor = save_pos;
    curwin->w_curswant = save_curswant;
    curwin->w_set_curswant = save_set_curswant;
    check_cursor();
    State = save_State;


    if (did_throw && (vim_strchr(p_debug, 't') == NULL || trylevel == 0))
    {
	handle_did_throw();
	did_throw = FALSE;
    }


    if (indent < 0)
	indent = get_indent();

    return indent;
}
