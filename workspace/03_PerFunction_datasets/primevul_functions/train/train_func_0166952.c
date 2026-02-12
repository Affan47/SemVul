vte_sequence_handler_send_primary_device_attributes (VteTerminal *terminal, GValueArray *params)
{

	vte_terminal_feed_child(terminal, "\e[?62;9;c", -1);
}
