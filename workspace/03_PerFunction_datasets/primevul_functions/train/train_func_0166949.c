vte_sequence_handler_cb (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	long i;
	VteScreen *screen;
	struct vte_charcell *pcell;
	screen = terminal->pvt->screen;


	rowdata = _vte_terminal_ensure_row(terminal);


	for (i = 0; i <= screen->cursor_current.col; i++) {
		if (i < (glong) rowdata->cells->len) {

			pcell = &g_array_index(rowdata->cells,
					       struct vte_charcell,
					       i);
			*pcell = screen->color_defaults;
		} else {

			g_array_append_val(rowdata->cells,
					   screen->color_defaults);
		}
	}

	_vte_invalidate_cells(terminal,
			      0, screen->cursor_current.col+1,
			      screen->cursor_current.row, 1);


	terminal->pvt->text_deleted_flag = TRUE;
}
