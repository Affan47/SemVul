cavan_window_find_by_point(struct double_link *link, struct cavan_input_message_point *point)
{
	struct double_link_node *node;
	struct cavan_window *win, *child;

	node = double_link_find(link, point, cavan_window_find_by_point_matcher);
	if (node == NULL)
	{
		return NULL;
	}

	win = double_link_get_container(link, node);
	child = cavan_window_find_by_point(&win->child_link, point);

	return child ? child : win;
}
