read_prefcond_section(FILE *fd, slang_T *lp)
{
    int		cnt;
    int		i;
    int		n;
    char_u	*p;
    char_u	buf[MAXWLEN + 1];


    cnt = get2c(fd);
    if (cnt <= 0)
	return SP_FORMERROR;

    lp->sl_prefprog = (regprog_T **)alloc_clear(
					 (unsigned)sizeof(regprog_T *) * cnt);
    if (lp->sl_prefprog == NULL)
	return SP_OTHERERROR;
    lp->sl_prefixcnt = cnt;

    for (i = 0; i < cnt; ++i)
    {

	n = getc(fd);
	if (n < 0 || n >= MAXWLEN)
	    return SP_FORMERROR;


	if (n > 0)
	{
	    buf[0] = '^';
	    p = buf + 1;
	    while (n-- > 0)
		*p++ = getc(fd);
	    *p = NUL;
	    lp->sl_prefprog[i] = vim_regcomp(buf, RE_MAGIC + RE_STRING);
	}
    }
    return 0;
}
