_vte_terminal_clear_screen (VteTerminal *terminal)
{
	VteRowData *rowdata, *old_row;
	long i, initial, row;
	VteScreen *screen;
	screen = terminal->pvt->screen;
	initial = screen->insert_delta;
	row = screen->cursor_current.row - screen->insert_delta;

	old_row = terminal->pvt->free_row;
	for (i = 0; i < terminal->row_count; i++) {

		if (i == 0) {
			initial = _vte_ring_next(screen->row_data);
		}
		if (old_row) {
			rowdata = _vte_reset_row_data (terminal, old_row, TRUE);
		} else {
			rowdata = _vte_new_row_data_sized(terminal, TRUE);
		}
		old_row = _vte_ring_append(screen->row_data, rowdata);
	}
	terminal->pvt->free_row = old_row;


	screen->insert_delta = initial;
	screen->cursor_current.row = row + screen->insert_delta;
	_vte_terminal_adjust_adjustments(terminal);

	_vte_invalidate_all(terminal);

	terminal->pvt->text_deleted_flag = TRUE;
}
