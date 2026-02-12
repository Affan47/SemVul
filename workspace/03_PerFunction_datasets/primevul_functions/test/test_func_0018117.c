get_mouse_class(char_u *p)
{
    int		c;

    if (has_mbyte && MB_BYTE2LEN(p[0]) > 1)
	return mb_get_class(p);

    c = *p;
    if (c == ' ' || c == '\t')
	return 0;

    if (vim_iswordc(c))
	return 2;


    if (c != NUL && vim_strchr((char_u *)"-+*/%<>&|^!=", c) != NULL)
	return 1;
    return c;
}
