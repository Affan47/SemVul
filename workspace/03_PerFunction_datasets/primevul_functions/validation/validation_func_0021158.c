read_sofo_section(FILE *fd, slang_T *slang)
{
    int		cnt;
    char_u	*from, *to;
    int		res;

    slang->sl_sofo = TRUE;


    from = read_cnt_string(fd, 2, &cnt);
    if (cnt < 0)
	return cnt;


    to = read_cnt_string(fd, 2, &cnt);
    if (cnt < 0)
    {
	vim_free(from);
	return cnt;
    }


    if (from != NULL && to != NULL)
	res = set_sofo(slang, from, to);
    else if (from != NULL || to != NULL)
	res = SP_FORMERROR;
    else
	res = 0;

    vim_free(from);
    vim_free(to);
    return res;
}
