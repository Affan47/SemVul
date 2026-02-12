check_for_bom(
    char_u	*p,
    long	size,
    int		*lenp,
    int		flags)
{
    char	*name = NULL;
    int		len = 2;

    if (p[0] == 0xef && p[1] == 0xbb && size >= 3 && p[2] == 0xbf
	    && (flags == FIO_ALL || flags == FIO_UTF8 || flags == 0))
    {
	name = "utf-8";
	len = 3;
    }
    else if (p[0] == 0xff && p[1] == 0xfe)
    {
	if (size >= 4 && p[2] == 0 && p[3] == 0
	    && (flags == FIO_ALL || flags == (FIO_UCS4 | FIO_ENDIAN_L)))
	{
	    name = "ucs-4le";
	    len = 4;
	}
	else if (flags == (FIO_UCS2 | FIO_ENDIAN_L))
	    name = "ucs-2le";
	else if (flags == FIO_ALL || flags == (FIO_UTF16 | FIO_ENDIAN_L))

	    name = "utf-16le";
    }
    else if (p[0] == 0xfe && p[1] == 0xff
	    && (flags == FIO_ALL || flags == FIO_UCS2 || flags == FIO_UTF16))
    {

	if (flags == FIO_UCS2)
	    name = "ucs-2";
	else
	    name = "utf-16";
    }
    else if (size >= 4 && p[0] == 0 && p[1] == 0 && p[2] == 0xfe
	    && p[3] == 0xff && (flags == FIO_ALL || flags == FIO_UCS4))
    {
	name = "ucs-4";
	len = 4;
    }

    *lenp = len;
    return (char_u *)name;
}
