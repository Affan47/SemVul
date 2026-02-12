vte_sequence_handler_ta (VteTerminal *terminal, GValueArray *params)
{
	VteScreen *screen;
	long newcol, col;


	screen = terminal->pvt->screen;
	newcol = col = screen->cursor_current.col;

	g_assert (col >= 0);

	if (terminal->pvt->tabstops != NULL) {

		for (newcol++; newcol < VTE_TAB_MAX; newcol++) {
			if (_vte_terminal_get_tabstop(terminal, newcol)) {
				break;
			}
		}
	}


	if (newcol >= terminal->column_count) {
		newcol = terminal->column_count - 1;
	}


	if (col < newcol) {
		VteRowData *rowdata = _vte_terminal_ensure_row (terminal);


		if ((glong) rowdata->cells->len > col)
		{
			struct vte_charcell *cell;
			guint i;
			for (i = rowdata->cells->len; (glong) i > col; i--) {
				cell = &g_array_index(rowdata->cells,
						      struct vte_charcell, i - 1);
				if (cell->attr.fragment || cell->c != 0)
					break;
			}
			g_array_set_size(rowdata->cells, i);
		}

		if ((glong) rowdata->cells->len <= col)
		  {
		    struct vte_charcell cell;

		    vte_g_array_fill (rowdata->cells,
				      &screen->fill_defaults,
				      col);

		    cell.attr = screen->fill_defaults.attr;
		    cell.attr.invisible = 1;
		    cell.attr.columns = newcol - col;
		    if (cell.attr.columns != newcol - col)
		      {


		       goto fallback_tab;
		      }
		    cell.c = '\t';
		    g_array_append_vals(rowdata->cells, &cell, 1);

		    cell.attr = screen->fill_defaults.attr;
		    cell.attr.fragment = 1;
		    vte_g_array_fill (rowdata->cells,
				      &cell,
				newcol);
		  }
		else
		  {
		  fallback_tab:
		    vte_g_array_fill (rowdata->cells,
				      &screen->fill_defaults,
				      newcol);
		  }

		_vte_invalidate_cells (terminal,
				screen->cursor_current.col,
				newcol - screen->cursor_current.col,
				screen->cursor_current.row, 1);
		screen->cursor_current.col = newcol;
	}
}
