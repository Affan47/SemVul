vte_sequence_handler_SF (VteTerminal *terminal, GValueArray *params)
{

	vte_sequence_handler_multiple(terminal, params, vte_sequence_handler_sf);
}
