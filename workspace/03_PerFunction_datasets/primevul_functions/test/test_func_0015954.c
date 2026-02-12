has_special_wildchar(char_u *p)
{
    for ( ; *p; MB_PTR_ADV(p))
    {

	if (*p == '\r' || *p == '\n')
	    break;

	if (*p == '\\' && p[1] != NUL && p[1] != '\r' && p[1] != '\n')
	    ++p;
	else if (vim_strchr((char_u *)SPECIAL_WILDCHAR, *p) != NULL)
	{

	    if (*p == '{' && vim_strchr(p, '}') == NULL)
		continue;

	    if ((*p == '`' || *p == '\'') && vim_strchr(p, *p) == NULL)
		continue;
	    return TRUE;
	}
    }
    return FALSE;
}
