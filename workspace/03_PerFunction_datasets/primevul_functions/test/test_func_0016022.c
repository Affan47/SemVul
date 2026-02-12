pathcmp(const char *p, const char *q, int maxlen)
{
    int		i, j;
    int		c1, c2;
    const char	*s = NULL;

    for (i = 0, j = 0; maxlen < 0 || (i < maxlen && j < maxlen);)
    {
	c1 = PTR2CHAR((char_u *)p + i);
	c2 = PTR2CHAR((char_u *)q + j);


	if (c1 == NUL)
	{
	    if (c2 == NUL)
		return 0;
	    s = q;
	    i = j;
	    break;
	}


	if (c2 == NUL)
	{
	    s = p;
	    break;
	}

	if ((p_fic ? MB_TOUPPER(c1) != MB_TOUPPER(c2) : c1 != c2)
#ifdef BACKSLASH_IN_FILENAME

		&& !((c1 == '/' && c2 == '\\')
		    || (c1 == '\\' && c2 == '/'))
#endif
		)
	{
	    if (vim_ispathsep(c1))
		return -1;
	    if (vim_ispathsep(c2))
		return 1;
	    return p_fic ? MB_TOUPPER(c1) - MB_TOUPPER(c2)
		    : c1 - c2;
	}

	i += mb_ptr2len((char_u *)p + i);
	j += mb_ptr2len((char_u *)q + j);
    }
    if (s == NULL)
	return 0;

    c1 = PTR2CHAR((char_u *)s + i);
    c2 = PTR2CHAR((char_u *)s + i + mb_ptr2len((char_u *)s + i));

    if (c2 == NUL
	    && i > 0
	    && !after_pathsep((char_u *)s, (char_u *)s + i)
#ifdef BACKSLASH_IN_FILENAME
	    && (c1 == '/' || c1 == '\\')
#else
	    && c1 == '/'
#endif
       )
	return 0;
    if (s == q)
	return -1;
    return 1;
}
