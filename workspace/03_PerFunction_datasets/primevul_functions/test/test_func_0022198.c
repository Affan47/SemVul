vte_sequence_handler_cd (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	glong i;
	VteScreen *screen;

	screen = terminal->pvt->screen;


	i = screen->cursor_current.row;
	if (i < _vte_ring_next(screen->row_data)) {

		rowdata = _vte_ring_index_writable (screen->row_data, i);

		if (rowdata)
			_vte_row_data_shrink (rowdata, screen->cursor_current.col);
	}

	for (i = screen->cursor_current.row + 1;
	     i < _vte_ring_next(screen->row_data);
	     i++) {

		rowdata = _vte_ring_index_writable (screen->row_data, i);

		if (rowdata)
			_vte_row_data_shrink (rowdata, 0);
	}

	for (i = screen->cursor_current.row;
	     i < screen->insert_delta + terminal->row_count;
	     i++) {

		if (_vte_ring_contains (screen->row_data, i)) {
			rowdata = _vte_ring_index_writable (screen->row_data, i);
			g_assert(rowdata != NULL);
		} else {
			rowdata = _vte_terminal_ring_append (terminal, FALSE);
		}

		_vte_row_data_fill (rowdata, &screen->fill_defaults, terminal->column_count);
		rowdata->attr.soft_wrapped = 0;

		_vte_invalidate_cells(terminal,
				      0, terminal->column_count,
				      i, 1);
	}


	terminal->pvt->text_deleted_flag = TRUE;
}
