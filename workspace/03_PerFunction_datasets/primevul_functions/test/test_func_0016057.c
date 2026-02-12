vim_FullName(
    char_u	*fname,
    char_u	*buf,
    int		len,
    int		force)
{
    int		retval = OK;
    int		url;

    *buf = NUL;
    if (fname == NULL)
	return FAIL;

    url = path_with_url(fname);
    if (!url)
	retval = mch_FullName(fname, buf, len, force);
    if (url || retval == FAIL)
    {

	vim_strncpy(buf, fname, len - 1);
    }
#if defined(MSWIN)
    slash_adjust(buf);
#endif
    return retval;
}
