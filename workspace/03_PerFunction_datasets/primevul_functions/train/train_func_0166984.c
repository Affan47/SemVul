vte_sequence_handler_se (VteTerminal *terminal, GValueArray *params)
{
	char *standout;


	standout = _vte_termcap_find_string(terminal->pvt->termcap,
					    terminal->pvt->emulation,
					    "so");
	g_assert(standout != NULL);

	if (vte_terminal_termcap_string_same_as_for (terminal, standout, "mb")    ||
	    vte_terminal_termcap_string_same_as_for (terminal, standout, "md")     ||
	    vte_terminal_termcap_string_same_as_for (terminal, standout, "mh")     ||
	    vte_terminal_termcap_string_same_as_for (terminal, standout, "mr")  ||
	    vte_terminal_termcap_string_same_as_for (terminal, standout, "us") )
	{
		vte_sequence_handler_me (terminal, params);
	} else {

		terminal->pvt->screen->defaults.attr.standout = 0;
	}

	g_free(standout);
}
