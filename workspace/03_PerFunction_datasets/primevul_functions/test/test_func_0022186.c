_vte_terminal_clear_above_current (VteTerminal *terminal)
{
	VteRowData *rowdata;
	long i;
	VteScreen *screen;
	screen = terminal->pvt->screen;


	for (i = screen->insert_delta; i < screen->cursor_current.row; i++) {
		if (_vte_ring_next(screen->row_data) > i) {

			rowdata = _vte_ring_index_writable (screen->row_data, i);
			g_assert(rowdata != NULL);

			_vte_row_data_shrink (rowdata, 0);

			_vte_row_data_fill (rowdata, &screen->fill_defaults, terminal->column_count);
			rowdata->attr.soft_wrapped = 0;

			_vte_invalidate_cells(terminal,
					0, terminal->column_count, i, 1);
		}
	}

	terminal->pvt->text_deleted_flag = TRUE;
}
