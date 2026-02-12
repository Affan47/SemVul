paragraph_start(linenr_T lnum)
{
    char_u	*p;
    int		leader_len = 0;
    char_u	*leader_flags = NULL;
    int		next_leader_len;
    char_u	*next_leader_flags;
    int		do_comments;

    if (lnum <= 1)
	return TRUE;

    p = ml_get(lnum - 1);
    if (*p == NUL)
	return TRUE;

    do_comments = has_format_option(FO_Q_COMS);
    if (fmt_check_par(lnum - 1, &leader_len, &leader_flags, do_comments))
	return TRUE;

    if (fmt_check_par(lnum, &next_leader_len, &next_leader_flags, do_comments))
	return TRUE;

    if (has_format_option(FO_WHITE_PAR) && !ends_in_white(lnum - 1))
	return TRUE;

    if (has_format_option(FO_Q_NUMBER) && (get_number_indent(lnum) > 0))
	return TRUE;

    if (!same_leader(lnum - 1, leader_len, leader_flags,
					  next_leader_len, next_leader_flags))
	return TRUE;

    return FALSE;
}
