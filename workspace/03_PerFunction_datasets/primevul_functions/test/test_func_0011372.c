hgr_search_file(
	qf_list_T *qfl,
	char_u *fname,
	vimconv_T *p_vc,
	regmatch_T *p_regmatch)
{
    FILE	*fd;
    long	lnum;

    fd = mch_fopen((char *)fname, "r");
    if (fd == NULL)
	return;

    lnum = 1;
    while (!vim_fgets(IObuff, IOSIZE, fd) && !got_int)
    {
	char_u    *line = IObuff;


	if (p_vc->vc_type != CONV_NONE && has_non_ascii(IObuff))
	{
	    line = string_convert(p_vc, IObuff, NULL);
	    if (line == NULL)
		line = IObuff;
	}

	if (vim_regexec(p_regmatch, line, (colnr_T)0))
	{
	    int	l = (int)STRLEN(line);


	    while (l > 0 && line[l - 1] <= ' ')
		line[--l] = NUL;

	    if (qf_add_entry(qfl,
			NULL,
			fname,
			NULL,
			0,
			line,
			lnum,
			0,
			(int)(p_regmatch->startp[0] - line)
			+ 1,
			(int)(p_regmatch->endp[0] - line)
			+ 1,
			FALSE,
			NULL,
			0,
			1,
			TRUE
			) == QF_FAIL)
	    {
		got_int = TRUE;
		if (line != IObuff)
		    vim_free(line);
		break;
	    }
	}
	if (line != IObuff)
	    vim_free(line);
	++lnum;
	line_breakcheck();
    }
    fclose(fd);
}
