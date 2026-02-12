_vte_terminal_clear_screen (VteTerminal *terminal)
{
	long i, initial, row;
	VteScreen *screen;
	screen = terminal->pvt->screen;
	initial = screen->insert_delta;
	row = screen->cursor_current.row - screen->insert_delta;
	initial = _vte_ring_next(screen->row_data);

	for (i = 0; i < terminal->row_count; i++)
		_vte_terminal_ring_append (terminal, TRUE);


	screen->insert_delta = initial;
	screen->cursor_current.row = row + screen->insert_delta;
	_vte_terminal_adjust_adjustments(terminal);

	_vte_invalidate_all(terminal);

	terminal->pvt->text_deleted_flag = TRUE;
}
