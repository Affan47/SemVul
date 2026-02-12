cin_islabel_skip(char_u **s)
{
    if (!vim_isIDc(**s))
	return FALSE;

    while (vim_isIDc(**s))
	(*s)++;

    *s = cin_skipcomment(*s);


    return (**s == ':' && *++*s != ':');
}
