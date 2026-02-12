get_arglist(garray_T *gap, char_u *str, int escaped)
{
    ga_init2(gap, (int)sizeof(char_u *), 20);
    while (*str != NUL)
    {
	if (ga_grow(gap, 1) == FAIL)
	{
	    ga_clear(gap);
	    return FAIL;
	}
	((char_u **)gap->ga_data)[gap->ga_len++] = str;


	if (!escaped)
	    return OK;


	str = do_one_arg(str);
    }
    return OK;
}
