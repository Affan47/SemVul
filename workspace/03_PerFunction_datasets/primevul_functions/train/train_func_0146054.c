cin_iscase(
    char_u *s,
    int strict)
{
    s = cin_skipcomment(s);
    if (cin_starts_with(s, "case"))
    {
	for (s += 4; *s; ++s)
	{
	    s = cin_skipcomment(s);
	    if (*s == NUL)
		break;
	    if (*s == ':')
	    {
		if (s[1] == ':')
		    ++s;
		else
		    return TRUE;
	    }
	    if (*s == '\'' && s[1] && s[2] == '\'')
		s += 2;
	    else if (*s == '/' && (s[1] == '*' || s[1] == '/'))
		return FALSE;
	    else if (*s == '"')
	    {

		if (strict)
		    return FALSE;
		else
		    return TRUE;
	    }
	}
	return FALSE;
    }

    if (cin_isdefault(s))
	return TRUE;
    return FALSE;
}
