vte_sequence_handler_ce (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	VteScreen *screen;

	screen = terminal->pvt->screen;

	rowdata = _vte_terminal_ensure_row(terminal);
	g_assert(rowdata != NULL);


	if ((glong) _vte_row_data_length (rowdata) > screen->cursor_current.col) {
		_vte_row_data_shrink (rowdata, screen->cursor_current.col);

		terminal->pvt->text_deleted_flag = TRUE;
	}
	if (screen->fill_defaults.attr.back != VTE_DEF_BG) {

		_vte_row_data_fill (rowdata, &screen->fill_defaults, terminal->column_count);
	}
	rowdata->attr.soft_wrapped = 0;

	_vte_invalidate_cells(terminal,
			      screen->cursor_current.col,
			      terminal->column_count -
			      screen->cursor_current.col,
			      screen->cursor_current.row, 1);
}
