set_view_attr(struct view *view, enum line_type type)
{
	if (!view->curline->selected && view->curtype != type) {
		(void) wattrset(view->win, get_line_attr(type));
		wchgat(view->win, -1, 0, type, NULL);
		view->curtype = type;
	}
}
