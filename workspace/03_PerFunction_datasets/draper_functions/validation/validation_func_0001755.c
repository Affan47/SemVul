copynsegs(from, to, n)
    register chr	*from;
    register chr	*to;
    register int	n;
{
    register chr	c;

    while ((*to++ = c = *from++) != '\0')
	if (c == '/' && --n <= 0)
	    break;

    if (c == '/')
	*--to = '\0';
}
