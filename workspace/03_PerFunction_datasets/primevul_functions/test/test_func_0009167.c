skip_substitute(char_u *start, int delimiter)
{
    char_u *p = start;

    while (p[0])
    {
	if (p[0] == delimiter)
	{
	    *p++ = NUL;
	    break;
	}
	if (p[0] == '\\' && p[1] != 0)
	    ++p;
	MB_PTR_ADV(p);
    }
    return p;
}
