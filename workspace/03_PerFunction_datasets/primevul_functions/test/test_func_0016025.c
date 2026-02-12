expand_backtick(
    garray_T	*gap,
    char_u	*pat,
    int		flags)
{
    char_u	*p;
    char_u	*cmd;
    char_u	*buffer;
    int		cnt = 0;
    int		i;


    cmd = vim_strnsave(pat + 1, STRLEN(pat) - 2);
    if (cmd == NULL)
	return -1;

#ifdef FEAT_EVAL
    if (*cmd == '=')
	buffer = eval_to_string(cmd + 1, TRUE);
    else
#endif
	buffer = get_cmd_output(cmd, NULL,
				(flags & EW_SILENT) ? SHELL_SILENT : 0, NULL);
    vim_free(cmd);
    if (buffer == NULL)
	return -1;

    cmd = buffer;
    while (*cmd != NUL)
    {
	cmd = skipwhite(cmd);
	p = cmd;
	while (*p != NUL && *p != '\r' && *p != '\n')
	    ++p;

	if (p > cmd)
	{
	    i = *p;
	    *p = NUL;
	    addfile(gap, cmd, flags);
	    *p = i;
	    ++cnt;
	}
	cmd = p;
	while (*cmd != NUL && (*cmd == '\r' || *cmd == '\n'))
	    ++cmd;
    }

    vim_free(buffer);
    return cnt;
}
