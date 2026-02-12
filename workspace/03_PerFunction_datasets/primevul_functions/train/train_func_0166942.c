vte_sequence_handler_sr (VteTerminal *terminal, GValueArray *params)
{
	long start, end;
	VteScreen *screen;

	screen = terminal->pvt->screen;

	if (screen->scrolling_restricted) {
		start = screen->scrolling_region.start + screen->insert_delta;
		end = screen->scrolling_region.end + screen->insert_delta;
	} else {
		start = terminal->pvt->screen->insert_delta;
		end = start + terminal->row_count - 1;
	}

	if (screen->cursor_current.row == start) {


		vte_remove_line_internal(terminal, end);
		vte_insert_line_internal(terminal, start);

		_vte_terminal_scroll_region(terminal, start, end - start + 1, 1);
		_vte_invalidate_cells(terminal,
				      0, terminal->column_count,
				      start, 2);
	} else {

		screen->cursor_current.row--;
	}

	_vte_terminal_adjust_adjustments(terminal);

	terminal->pvt->text_modified_flag = TRUE;
}
