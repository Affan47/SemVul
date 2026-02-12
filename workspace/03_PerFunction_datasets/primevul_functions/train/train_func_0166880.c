vte_sequence_handler_so (VteTerminal *terminal, GValueArray *params)
{
	char *standout;


	standout = _vte_termcap_find_string(terminal->pvt->termcap,
					    terminal->pvt->emulation,
					    "so");
	g_assert(standout != NULL);

	if (vte_terminal_termcap_string_same_as_for (terminal, standout, "mb") )
		vte_sequence_handler_mb (terminal, params);
	else if (vte_terminal_termcap_string_same_as_for (terminal, standout, "md") )
		vte_sequence_handler_md (terminal, params);
	else if (vte_terminal_termcap_string_same_as_for (terminal, standout, "mh") )
		vte_sequence_handler_mh (terminal, params);
	else if (vte_terminal_termcap_string_same_as_for (terminal, standout, "mr") )
		vte_sequence_handler_mr (terminal, params);
	else if (vte_terminal_termcap_string_same_as_for (terminal, standout, "us") )
		vte_sequence_handler_us (terminal, params);
	else {

		terminal->pvt->screen->defaults.attr.standout = 1;
	}

	g_free(standout);
}
