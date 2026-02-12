_vte_terminal_clear_current_line (VteTerminal *terminal)
{
	VteRowData *rowdata;
	VteScreen *screen;

	screen = terminal->pvt->screen;


	if (_vte_ring_next(screen->row_data) > screen->cursor_current.row) {

		rowdata = _vte_ring_index(screen->row_data, VteRowData *,
					  screen->cursor_current.row);
		g_assert(rowdata != NULL);

		if (rowdata->cells->len > 0) {
			g_array_set_size(rowdata->cells, 0);
		}


		vte_g_array_fill(rowdata->cells,
				 &screen->fill_defaults,
				 terminal->column_count);
		rowdata->soft_wrapped = 0;

		_vte_invalidate_cells(terminal,
				      0, terminal->column_count,
				      screen->cursor_current.row, 1);
	}


	terminal->pvt->text_deleted_flag = TRUE;
}
