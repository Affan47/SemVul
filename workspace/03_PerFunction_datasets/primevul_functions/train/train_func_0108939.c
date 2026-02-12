eval_map_expr(
    char_u	*str,
    int		c)
{
    char_u	*res;
    char_u	*p;
    char_u	*expr;
    pos_T	save_cursor;
    int		save_msg_col;
    int		save_msg_row;


    expr = vim_strsave(str);
    if (expr == NULL)
	return NULL;
    vim_unescape_csi(expr);


    ++textlock;
    ++ex_normal_lock;
    set_vim_var_char(c);
    save_cursor = curwin->w_cursor;
    save_msg_col = msg_col;
    save_msg_row = msg_row;
    p = eval_to_string(expr, NULL, FALSE);
    --textlock;
    --ex_normal_lock;
    curwin->w_cursor = save_cursor;
    msg_col = save_msg_col;
    msg_row = save_msg_row;

    vim_free(expr);

    if (p == NULL)
	return NULL;

    res = vim_strsave_escape_csi(p);
    vim_free(p);

    return res;
}
