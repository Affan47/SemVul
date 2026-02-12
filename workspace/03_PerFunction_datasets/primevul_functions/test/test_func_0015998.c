skiphex(char_u *q)
{
    char_u	*p = q;

    while (vim_isxdigit(*p))
	++p;
    return p;
}
