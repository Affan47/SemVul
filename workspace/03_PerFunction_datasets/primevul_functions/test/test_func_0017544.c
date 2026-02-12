getlinecol(
    long	*cp,
    long	*rp)
{
    char_u	tbuf[TBUFSZ];

    if (T_NAME != NULL && *T_NAME != NUL && invoke_tgetent(tbuf, T_NAME) == NULL)
    {
	if (*cp == 0)
	    *cp = tgetnum("co");
	if (*rp == 0)
	    *rp = tgetnum("li");
    }
}
