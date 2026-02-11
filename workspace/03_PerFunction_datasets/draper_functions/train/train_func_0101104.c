window_selection_start(Win *win) {
	if (win->sel.start != EPOS && win->sel.end != EPOS)
		return;
	size_t pos = window_cursor_get(win);
	win->sel.start = win->sel.end = pos;
	window_draw(win);
	window_cursor_to(win, pos);
}
