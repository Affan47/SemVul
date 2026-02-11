collapse_all(void *node)
{
	if (has_children(node)) {
		adjust(node, false);
		void *tmp = get_child(node, 1);
		while (tmp) {
			collapse_all(tmp);
			tmp = get_next_node(tmp);
		}
	}
}
