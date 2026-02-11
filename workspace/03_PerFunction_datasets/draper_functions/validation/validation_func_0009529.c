window_line_up(Win *win) {
	Cursor *cursor = &win->cursor;
	if (cursor->line->prev && cursor->line->prev->prev &&
	    cursor->line->lineno != cursor->line->prev->lineno &&
	    cursor->line->prev->lineno != cursor->line->prev->prev->lineno)
		return window_screenline_up(win);
	size_t bol = text_line_begin(win->text, cursor->pos);
	size_t prev = text_line_prev(win->text, bol);
	size_t pos = text_line_offset(win->text, prev, cursor->pos - bol);
	window_cursor_to(win, pos);
	return cursor->pos;
}
