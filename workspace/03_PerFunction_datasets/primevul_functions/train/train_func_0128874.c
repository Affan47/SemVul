do_insert_char_pre(int c)
{
    char_u	*res;
    char_u	buf[MB_MAXBYTES + 1];
    int		save_State = State;


    if (!has_insertcharpre())
	return NULL;

    if (has_mbyte)
	buf[(*mb_char2bytes)(c, buf)] = NUL;
    else
    {
	buf[0] = c;
	buf[1] = NUL;
    }


    ++textlock;
    set_vim_var_string(VV_CHAR, buf, -1);

    res = NULL;
    if (ins_apply_autocmds(EVENT_INSERTCHARPRE))
    {


	if (STRCMP(buf, get_vim_var_str(VV_CHAR)) != 0)
	    res = vim_strsave(get_vim_var_str(VV_CHAR));
    }

    set_vim_var_string(VV_CHAR, NULL, -1);
    --textlock;


    State = save_State;

    return res;
}
