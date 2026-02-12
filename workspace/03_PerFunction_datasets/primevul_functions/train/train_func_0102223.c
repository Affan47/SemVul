match_checkcompoundpattern(
    char_u	*ptr,
    int		wlen,
    garray_T	*gap)
{
    int		i;
    char_u	*p;
    int		len;

    for (i = 0; i + 1 < gap->ga_len; i += 2)
    {
	p = ((char_u **)gap->ga_data)[i + 1];
	if (STRNCMP(ptr + wlen, p, STRLEN(p)) == 0)
	{


	    p = ((char_u **)gap->ga_data)[i];
	    len = (int)STRLEN(p);
	    if (len <= wlen && STRNCMP(ptr + wlen - len, p, len) == 0)
		return TRUE;
	}
    }
    return FALSE;
}
