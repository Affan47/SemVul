pat_has_uppercase(char_u *pat)
{
    char_u *p = pat;
    magic_T magic_val = MAGIC_ON;


    (void)skip_regexp_ex(pat, NUL, magic_isset(), NULL, NULL, &magic_val);

    while (*p != NUL)
    {
	int		l;

	if (has_mbyte && (l = (*mb_ptr2len)(p)) > 1)
	{
	    if (enc_utf8 && utf_isupper(utf_ptr2char(p)))
		return TRUE;
	    p += l;
	}
	else if (*p == '\\' && magic_val <= MAGIC_ON)
	{
	    if (p[1] == '_' && p[2] != NUL)
		p += 3;
	    else if (p[1] == '%' && p[2] != NUL)
		p += 3;
	    else if (p[1] != NUL)
		p += 2;
	    else
		p += 1;
	}
	else if ((*p == '%' || *p == '_') && magic_val == MAGIC_ALL)
	{
	    if (p[1] != NUL)
		p += 2;
	    else
		p++;
	}
	else if (MB_ISUPPER(*p))
	    return TRUE;
	else
	    ++p;
    }
    return FALSE;
}
