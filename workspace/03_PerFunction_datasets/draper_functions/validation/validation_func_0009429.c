find_next_line(struct view *view, unsigned long lineno, struct line *line)
{
	assert(view_is_displayed(view));

	if (!view->ops->grep(view, line))
		return FALSE;

	if (lineno - view->offset >= view->height) {
		view->offset = lineno;
		view->lineno = lineno;
		redraw_view(view);

	} else {
		unsigned long old_lineno = view->lineno - view->offset;

		view->lineno = lineno;
		draw_view_line(view, old_lineno);

		draw_view_line(view, view->lineno - view->offset);
		redrawwin(view->win);
		wrefresh(view->win);
	}

	report("Line %ld matches '%s'", lineno + 1, view->grep);
	return TRUE;
}
