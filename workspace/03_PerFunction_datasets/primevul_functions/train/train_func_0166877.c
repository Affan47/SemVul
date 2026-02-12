vte_sequence_handler_insert_lines (VteTerminal *terminal, GValueArray *params)
{
	VteRowData *rowdata;
	GValue *value;
	VteScreen *screen;
	long param, end, row;
	int i;
	screen = terminal->pvt->screen;

	param = 1;

	if ((params != NULL) && (params->n_values > 0)) {
		value = g_value_array_get_nth(params, 0);
		if (G_VALUE_HOLDS_LONG(value)) {
			param = g_value_get_long(value);
		}
	}

	row = screen->cursor_current.row;
	if (screen->scrolling_restricted) {
		end = screen->insert_delta + screen->scrolling_region.end;
	} else {
		end = screen->insert_delta + terminal->row_count - 1;
	}

	for (i = 0; i < param; i++) {


		vte_remove_line_internal(terminal, end);
		vte_insert_line_internal(terminal, row);

		rowdata = _vte_ring_index(screen->row_data, VteRowData *, row);
		g_assert(rowdata != NULL);

		vte_g_array_fill(rowdata->cells,
				 &screen->fill_defaults,
				 terminal->column_count);
	}

	_vte_terminal_scroll_region(terminal, row, end - row + 1, param);

	_vte_terminal_adjust_adjustments(terminal);

	terminal->pvt->text_inserted_flag = TRUE;
}
