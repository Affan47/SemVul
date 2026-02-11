activate(struct window *window)
{
	if (active_window)
		active_window->repaint = TRUE;
	active_window = window;
	title(window);
	window->repaint = TRUE;
	return window;
}
