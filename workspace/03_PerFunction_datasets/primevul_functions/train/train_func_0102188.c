match_compoundrule(slang_T *slang, char_u *compflags)
{
    char_u	*p;
    int		i;
    int		c;


    for (p = slang->sl_comprules; *p != NUL; ++p)
    {


	for (i = 0; ; ++i)
	{
	    c = compflags[i];
	    if (c == NUL)

		return TRUE;
	    if (*p == '/' || *p == NUL)
		break;
	    if (*p == '[')
	    {
		int match = FALSE;


		++p;
		while (*p != ']' && *p != NUL)
		    if (*p++ == c)
			match = TRUE;
		if (!match)
		    break;
	    }
	    else if (*p != c)
		break;
	    ++p;
	}


	p = vim_strchr(p, '/');
	if (p == NULL)
	    break;
    }


    return FALSE;
}
