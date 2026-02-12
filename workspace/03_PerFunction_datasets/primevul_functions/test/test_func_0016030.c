shorten_dir_len(char_u *str, int trim_len)
{
    char_u	*tail, *s, *d;
    int		skip = FALSE;
    int		dirchunk_len = 0;

    tail = gettail(str);
    d = str;
    for (s = str; ; ++s)
    {
	if (s >= tail)
	{
	    *d++ = *s;
	    if (*s == NUL)
		break;
	}
	else if (vim_ispathsep(*s))
	{
	    *d++ = *s;
	    skip = FALSE;
	    dirchunk_len = 0;
	}
	else if (!skip)
	{
	    *d++ = *s;
	    if (*s != '~' && *s != '.')
	    {
		++dirchunk_len;


		if (dirchunk_len >= trim_len)
		    skip = TRUE;
	    }

	    if (has_mbyte)
	    {
		int l = mb_ptr2len(s);

		while (--l > 0)
		    *d++ = *++s;
	    }
	}
    }
}
