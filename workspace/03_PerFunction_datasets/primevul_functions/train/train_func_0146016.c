cin_has_js_key(char_u *text)
{
    char_u *s = skipwhite(text);
    int	    quote = -1;

    if (*s == '\'' || *s == '"')
    {

	quote = *s;
	++s;
    }
    if (!vim_isIDc(*s))
	return FALSE;

    while (vim_isIDc(*s))
	++s;
    if (*s == quote)
	++s;

    s = cin_skipcomment(s);


    return (*s == ':' && s[1] != ':');
}
