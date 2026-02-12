skipbin(char_u *q)
{
    char_u	*p = q;

    while (vim_isbdigit(*p))
	++p;
    return p;
}
