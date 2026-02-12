term_check_multiplot_okay(TBOOLEAN f_interactive)
{
    FPRINTF((stderr, "term_multiplot_okay(%d)\n", f_interactive));

    if (!term_initialised)
	return;


    if (!f_interactive || (term->flags & TERM_CAN_MULTIPLOT) ||
	((gpoutfile != stdout) && !(term->flags & TERM_CANNOT_MULTIPLOT))
	) {

	term_suspend();
	return;
    }


    term_end_multiplot();


    if (term->flags & TERM_CANNOT_MULTIPLOT)
	int_error(NO_CARET, "This terminal does not support multiplot");
    else
	int_error(NO_CARET, "Must set output to a file or put all multiplot commands on one input line");
}
