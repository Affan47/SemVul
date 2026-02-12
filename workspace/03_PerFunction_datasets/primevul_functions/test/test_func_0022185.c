vte_sequence_handler_screen_alignment_test (VteTerminal *terminal, GValueArray *params)
{
	long row;
	VteRowData *rowdata;
	VteScreen *screen;
	VteCell cell;

	screen = terminal->pvt->screen;

	for (row = terminal->pvt->screen->insert_delta;
	     row < terminal->pvt->screen->insert_delta + terminal->row_count;
	     row++) {

		while (_vte_ring_next(screen->row_data) <= row)
			_vte_terminal_ring_append (terminal, FALSE);
		_vte_terminal_adjust_adjustments(terminal);
		rowdata = _vte_ring_index_writable (screen->row_data, row);
		g_assert(rowdata != NULL);

		_vte_row_data_shrink (rowdata, 0);

		_vte_terminal_emit_text_deleted(terminal);

		cell.c = 'E';
		cell.attr = basic_cell.cell.attr;
		cell.attr.columns = 1;
		_vte_row_data_fill (rowdata, &cell, terminal->column_count);
		_vte_terminal_emit_text_inserted(terminal);
	}
	_vte_invalidate_all(terminal);


	terminal->pvt->text_modified_flag = TRUE;
}
