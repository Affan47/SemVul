vte_sequence_handler_cd (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	glong i;
	VteScreen *screen;

	screen = terminal->pvt->screen;


	i = screen->cursor_current.row;
	if (i < _vte_ring_next(screen->row_data)) {

		rowdata = _vte_ring_index(screen->row_data, VteRowData *, i);

		if ((rowdata != NULL) &&
		    ((glong) rowdata->cells->len > screen->cursor_current.col)) {
			g_array_set_size(rowdata->cells,
					 screen->cursor_current.col);
		}
	}

	for (i = screen->cursor_current.row + 1;
	     i < _vte_ring_next(screen->row_data);
	     i++) {

		rowdata = _vte_ring_index(screen->row_data, VteRowData *, i);

		if ((rowdata != NULL) && (rowdata->cells->len > 0)) {
			g_array_set_size(rowdata->cells, 0);
		}
	}

	for (i = screen->cursor_current.row;
	     i < screen->insert_delta + terminal->row_count;
	     i++) {

		if (_vte_ring_contains(screen->row_data, i)) {
			rowdata = _vte_ring_index(screen->row_data,
						  VteRowData *, i);
			g_assert(rowdata != NULL);
		} else {
			if (terminal->pvt->free_row) {
				rowdata = _vte_reset_row_data (terminal,
						terminal->pvt->free_row,
						FALSE);
			} else {
				rowdata = _vte_new_row_data(terminal);
			}
			terminal->pvt->free_row =
				_vte_ring_append(screen->row_data, rowdata);
		}

		vte_g_array_fill(rowdata->cells,
				 &screen->fill_defaults,
				 terminal->column_count);
		rowdata->soft_wrapped = 0;

		_vte_invalidate_cells(terminal,
				      0, terminal->column_count,
				      i, 1);
	}


	terminal->pvt->text_deleted_flag = TRUE;
}
