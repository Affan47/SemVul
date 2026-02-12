vte_sequence_handler_dl (VteTerminal *terminal, GValueArray *params)
{
	VteScreen *screen;
	long start, end, param, i;
	GValue *value;


	screen = terminal->pvt->screen;
	start = screen->cursor_current.row;
	if (screen->scrolling_restricted) {
		end = screen->insert_delta + screen->scrolling_region.end;
	} else {
		end = screen->insert_delta + terminal->row_count - 1;
	}


	param = 1;
	if ((params != NULL) && (params->n_values > 0)) {
		value = g_value_array_get_nth(params, 0);
		if (G_VALUE_HOLDS_LONG(value)) {
			param = g_value_get_long(value);
		}
	}


	for (i = 0; i < param; i++) {


		_vte_terminal_ring_remove (terminal, start);
		_vte_terminal_ring_insert (terminal, end, TRUE);

		_vte_terminal_adjust_adjustments(terminal);
	}


	_vte_terminal_scroll_region(terminal, start, end - start + 1, -param);


	terminal->pvt->text_deleted_flag = TRUE;
}
