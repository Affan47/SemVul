ses_put_fname(fd, name, flagp)
    FILE	*fd;
    char_u	*name;
    unsigned	*flagp;
{
    char_u	*sname;
    char_u	*p;
    int		retval = OK;

    sname = home_replace_save(NULL, name);
    if (sname == NULL)
	return FAIL;

    if (*flagp & SSOP_SLASH)
    {

	for (p = sname; *p != NUL; mb_ptr_adv(p))
	    if (*p == '\\')
		*p = '/';
    }


    p = vim_strsave_fnameescape(sname, FALSE);
    vim_free(sname);
    if (p == NULL)
	return FAIL;


    if (fputs((char *)p, fd) < 0)
	retval = FAIL;

    vim_free(p);
    return retval;
}
