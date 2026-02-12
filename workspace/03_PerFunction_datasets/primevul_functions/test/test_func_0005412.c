str_to_reg(
    yankreg_T	*y_ptr,
    int		yank_type,
    char_u	*str,
    long	len,
    long	blocklen,
    int		str_list)
{
    int		type;
    int		lnum;
    long	start;
    long	i;
    int		extra;
    int		newlines;
    int		extraline = 0;
    int		append = FALSE;
    char_u	*s;
    char_u	**ss;
    char_u	**pp;
    long	maxlen;

    if (y_ptr->y_array == NULL)
	y_ptr->y_size = 0;

    if (yank_type == MAUTO)
	type = ((str_list || (len > 0 && (str[len - 1] == NL
					    || str[len - 1] == CAR)))
							     ? MLINE : MCHAR);
    else
	type = yank_type;


    newlines = 0;
    if (str_list)
    {
	for (ss = (char_u **) str; *ss != NULL; ++ss)
	    ++newlines;
    }
    else
    {
	for (i = 0; i < len; i++)
	    if (str[i] == '\n')
		++newlines;
	if (type == MCHAR || len == 0 || str[len - 1] != '\n')
	{
	    extraline = 1;
	    ++newlines;
	}
	if (y_ptr->y_size > 0 && y_ptr->y_type == MCHAR)
	{
	    append = TRUE;
	    --newlines;
	}
    }


    if (y_ptr->y_size + newlines == 0)
    {
	VIM_CLEAR(y_ptr->y_array);
	return;
    }


    pp = lalloc_clear((y_ptr->y_size + newlines) * sizeof(char_u *), TRUE);
    if (pp == NULL)
	return;
    for (lnum = 0; lnum < y_ptr->y_size; ++lnum)
	pp[lnum] = y_ptr->y_array[lnum];
    vim_free(y_ptr->y_array);
    y_ptr->y_array = pp;
    maxlen = 0;


    if (str_list)
    {
	for (ss = (char_u **) str; *ss != NULL; ++ss, ++lnum)
	{
	    pp[lnum] = vim_strsave(*ss);
	    if (type == MBLOCK)
	    {
		int charlen = mb_string2cells(*ss, -1);

		if (charlen > maxlen)
		    maxlen = charlen;
	    }
	}
    }
    else
    {
	for (start = 0; start < len + extraline; start += i + 1)
	{
	    int charlen = 0;

	    for (i = start; i < len; ++i)
	    {
		if (str[i] == '\n')
		    break;
		if (type == MBLOCK)
		    charlen += mb_ptr2cells_len(str + i, len - i);
	    }
	    i -= start;
	    if (charlen > maxlen)
		maxlen = charlen;
	    if (append)
	    {
		--lnum;
		extra = (int)STRLEN(y_ptr->y_array[lnum]);
	    }
	    else
		extra = 0;
	    s = alloc(i + extra + 1);
	    if (s == NULL)
		break;
	    if (extra)
		mch_memmove(s, y_ptr->y_array[lnum], (size_t)extra);
	    if (append)
		vim_free(y_ptr->y_array[lnum]);
	    if (i > 0)
		mch_memmove(s + extra, str + start, (size_t)i);
	    extra += i;
	    s[extra] = NUL;
	    y_ptr->y_array[lnum++] = s;
	    while (--extra >= 0)
	    {
		if (*s == NUL)
		    *s = '\n';
		++s;
	    }
	    append = FALSE;
	}
    }
    y_ptr->y_type = type;
    y_ptr->y_size = lnum;
    if (type == MBLOCK)
	y_ptr->y_width = (blocklen < 0 ? maxlen - 1 : blocklen);
    else
	y_ptr->y_width = 0;
# ifdef FEAT_VIMINFO
    y_ptr->y_time_set = vim_time();
# endif
}
