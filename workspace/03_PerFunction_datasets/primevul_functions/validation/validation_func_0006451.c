ins_compl_add_infercase(
    char_u	*str_arg,
    int		len,
    int		icase,
    char_u	*fname,
    int		dir,
    int		cont_s_ipos)
{
    char_u	*str = str_arg;
    char_u	*p;
    int		char_len;
    int		compl_char_len;
    int		min_len;
    int		flags = 0;
    int		res;
    char_u	*tofree = NULL;

    if (p_ic && curbuf->b_p_inf && len > 0)
    {


	if (has_mbyte)
	{
	    p = str;
	    char_len = 0;
	    while (*p != NUL)
	    {
		MB_PTR_ADV(p);
		++char_len;
	    }
	}
	else
	    char_len = len;


	if (has_mbyte)
	{
	    p = compl_orig_text;
	    compl_char_len = 0;
	    while (*p != NUL)
	    {
		MB_PTR_ADV(p);
		++compl_char_len;
	    }
	}
	else
	    compl_char_len = compl_length;


	min_len = char_len < compl_char_len ? char_len : compl_char_len;

	str = ins_compl_infercase_gettext(str, char_len,
					  compl_char_len, min_len, &tofree);
    }
    if (cont_s_ipos)
	flags |= CP_CONT_S_IPOS;
    if (icase)
	flags |= CP_ICASE;

    res = ins_compl_add(str, len, fname, NULL, NULL, dir, flags, FALSE);
    vim_free(tofree);
    return res;
}
