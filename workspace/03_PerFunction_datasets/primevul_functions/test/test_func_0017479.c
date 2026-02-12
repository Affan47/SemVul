invoke_tgetent(char_u *tbuf, char_u *term)
{
    int	    i;


    i = TGETENT(tbuf, term);
    if (i < 0
# ifdef TGETENT_ZERO_ERR
	    || i == 0
# endif
       )
    {


	(void)TGETENT(tbuf, "dumb");

	if (i < 0)
# ifdef TGETENT_ZERO_ERR
	    return _(e_cannot_open_termcap_file);
	if (i == 0)
# endif
#ifdef TERMINFO
	    return _(e_terminal_entry_not_found_in_terminfo);
#else
	    return _(e_terminal_entry_not_found_in_termcap);
#endif
    }
    return NULL;
}
