getdigits(char_u **pp)
{
    char_u	*p;
    long	retval;

    p = *pp;
    retval = atol((char *)p);
    if (*p == '-')
	++p;
    p = skipdigits(p);
    *pp = p;
    return retval;
}
