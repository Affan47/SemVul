cin_skipcomment(char_u *s)
{
    while (*s)
    {
	char_u *prev_s = s;

	s = skipwhite(s);


	if (curbuf->b_ind_hash_comment != 0 && s != prev_s && *s == '#')
	{
	    s += STRLEN(s);
	    break;
	}
	if (*s != '/')
	    break;
	++s;
	if (*s == '/')
	{
	    s += STRLEN(s);
	    break;
	}
	if (*s != '*')
	    break;
	for (++s; *s; ++s)
	    if (s[0] == '*' && s[1] == '/')
	    {
		s += 2;
		break;
	    }
    }
    return s;
}
