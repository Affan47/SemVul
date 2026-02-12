vte_sequence_handler_cb (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	long i;
	VteScreen *screen;
	VteCell *pcell;
	screen = terminal->pvt->screen;


	rowdata = _vte_terminal_ensure_row(terminal);


	for (i = 0; i <= screen->cursor_current.col; i++) {
		if (i < (glong) _vte_row_data_length (rowdata)) {

			pcell = _vte_row_data_get_writable (rowdata, i);
			*pcell = screen->color_defaults;
		} else {

			_vte_row_data_append (rowdata, &screen->color_defaults);
		}
	}

	_vte_invalidate_cells(terminal,
			      0, screen->cursor_current.col+1,
			      screen->cursor_current.row, 1);


	terminal->pvt->text_deleted_flag = TRUE;
}
