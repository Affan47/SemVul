show_pat_in_path(
    char_u  *line,
    int	    type,
    int	    did_show,
    int	    action,
    FILE    *fp,
    linenr_T *lnum,
    long    count)
{
    char_u  *p;

    if (did_show)
	msg_putchar('\n');
    else if (!msg_silent)
	gotocmdline(TRUE);
    if (got_int)
	return;
    for (;;)
    {
	p = line + STRLEN(line) - 1;
	if (fp != NULL)
	{

	    if (p >= line && *p == '\n')
		--p;
	    if (p >= line && *p == '\r')
		--p;
	    *(p + 1) = NUL;
	}
	if (action == ACTION_SHOW_ALL)
	{
	    sprintf((char *)IObuff, "%3ld: ", count);
	    msg_puts((char *)IObuff);
	    sprintf((char *)IObuff, "%4ld", *lnum);

	    msg_puts_attr((char *)IObuff, HL_ATTR(HLF_N));
	    msg_puts(" ");
	}
	msg_prt_line(line, FALSE);
	out_flush();


	if (got_int || type != FIND_DEFINE || p < line || *p != '\\')
	    break;

	if (fp != NULL)
	{
	    if (vim_fgets(line, LSIZE, fp))
		break;
	    ++*lnum;
	}
	else
	{
	    if (++*lnum > curbuf->b_ml.ml_line_count)
		break;
	    line = ml_get(*lnum);
	}
	msg_putchar('\n');
    }
}
