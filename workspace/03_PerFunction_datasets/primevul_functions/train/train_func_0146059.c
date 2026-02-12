after_label(char_u *l)
{
    for ( ; *l; ++l)
    {
	if (*l == ':')
	{
	    if (l[1] == ':')
		++l;
	    else if (!cin_iscase(l + 1, FALSE))
		break;
	}
	else if (*l == '\'' && l[1] && l[2] == '\'')
	    l += 2;
    }
    if (*l == NUL)
	return NULL;
    l = cin_skipcomment(l + 1);
    if (*l == NUL)
	return NULL;
    return l;
}
