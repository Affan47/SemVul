get_short_pathname(char_u **fnamep, char_u **bufp, int *fnamelen)
{
    int		l, len;
    WCHAR	*newbuf;
    WCHAR	*wfname;

    len = MAXPATHL;
    newbuf = malloc(len * sizeof(*newbuf));
    if (newbuf == NULL)
	return FAIL;

    wfname = enc_to_utf16(*fnamep, NULL);
    if (wfname == NULL)
    {
	vim_free(newbuf);
	return FAIL;
    }

    l = GetShortPathNameW(wfname, newbuf, len);
    if (l > len - 1)
    {


	WCHAR *newbuf_t = newbuf;
	newbuf = vim_realloc(newbuf, (l + 1) * sizeof(*newbuf));
	if (newbuf == NULL)
	{
	    vim_free(wfname);
	    vim_free(newbuf_t);
	    return FAIL;
	}

	l = GetShortPathNameW(wfname, newbuf, l+1);
    }
    if (l != 0)
    {
	char_u *p = utf16_to_enc(newbuf, NULL);

	if (p != NULL)
	{
	    vim_free(*bufp);
	    *fnamep = *bufp = p;
	}
	else
	{
	    vim_free(wfname);
	    vim_free(newbuf);
	    return FAIL;
	}
    }
    vim_free(wfname);
    vim_free(newbuf);

    *fnamelen = l == 0 ? l : (int)STRLEN(*bufp);
    return OK;
}
