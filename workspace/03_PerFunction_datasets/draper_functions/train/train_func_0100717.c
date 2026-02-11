ses_arglist(fd, cmd, gap, fullname, flagp)
    FILE	*fd;
    char	*cmd;
    garray_T	*gap;
    int		fullname;
    unsigned	*flagp;
{
    int		i;
    char_u	buf[MAXPATHL];
    char_u	*s;

    if (gap->ga_len == 0)
	return put_line(fd, "silent! argdel *");
    if (fputs(cmd, fd) < 0)
	return FAIL;
    for (i = 0; i < gap->ga_len; ++i)
    {

	s = alist_name(&((aentry_T *)gap->ga_data)[i]);
	if (s != NULL)
	{
	    if (fullname)
	    {
		(void)vim_FullName(s, buf, MAXPATHL, FALSE);
		s = buf;
	    }
	    if (fputs(" ", fd) < 0 || ses_put_fname(fd, s, flagp) == FAIL)
		return FAIL;
	}
    }
    return put_eol(fd);
}
