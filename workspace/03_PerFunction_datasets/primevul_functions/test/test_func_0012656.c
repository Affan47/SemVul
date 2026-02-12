skip_comment(
    char_u   *line,
    int      process,
    int	     include_space,
    int      *is_comment)
{
    char_u *comment_flags = NULL;
    int    lead_len;
    int    leader_offset = get_last_leader_offset(line, &comment_flags);

    *is_comment = FALSE;
    if (leader_offset != -1)
    {


	while (*comment_flags)
	{
	    if (*comment_flags == COM_END
		    || *comment_flags == ':')
		break;
	    ++comment_flags;
	}
	if (*comment_flags != COM_END)
	    *is_comment = TRUE;
    }

    if (process == FALSE)
	return line;

    lead_len = get_leader_len(line, &comment_flags, FALSE, include_space);

    if (lead_len == 0)
	return line;


    while (*comment_flags)
    {
	if (*comment_flags == COM_END
		|| *comment_flags == ':')
	    break;
	++comment_flags;
    }


    if (*comment_flags == ':' || *comment_flags == NUL)
	line += lead_len;

    return line;
}
