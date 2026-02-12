do_sub_msg(
    int	    count_only)
{


    if (((sub_nsubs > p_report && (KeyTyped || sub_nlines > 1 || p_report < 1))
		|| count_only)
	    && messaging())
    {
	char	*msg_single;
	char	*msg_plural;

	if (got_int)
	    STRCPY(msg_buf, _("(Interrupted) "));
	else
	    *msg_buf = NUL;

	msg_single = count_only
		    ? NGETTEXT("%ld match on %ld line",
					  "%ld matches on %ld line", sub_nsubs)
		    : NGETTEXT("%ld substitution on %ld line",
				   "%ld substitutions on %ld line", sub_nsubs);
	msg_plural = count_only
		    ? NGETTEXT("%ld match on %ld lines",
					 "%ld matches on %ld lines", sub_nsubs)
		    : NGETTEXT("%ld substitution on %ld lines",
				  "%ld substitutions on %ld lines", sub_nsubs);

	vim_snprintf_add(msg_buf, sizeof(msg_buf),
				 NGETTEXT(msg_single, msg_plural, sub_nlines),
				 sub_nsubs, (long)sub_nlines);

	if (msg(msg_buf))

	    set_keep_msg((char_u *)msg_buf, 0);
	return TRUE;
    }
    if (got_int)
    {
	emsg(_(e_interrupted));
	return TRUE;
    }
    return FALSE;
}
