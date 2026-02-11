isl_schedule_node_foreach_ancestor_top_down(
	__isl_keep isl_schedule_node *node,
	int (*fn)(__isl_keep isl_schedule_node *node, void *user), void *user)
{
	int i, n;

	if (!node)
		return -1;

	n = isl_schedule_node_get_tree_depth(node);
	for (i = 0; i < n; ++i) {
		isl_schedule_node *ancestor;
		int r;

		ancestor = isl_schedule_node_copy(node);
		ancestor = isl_schedule_node_ancestor(ancestor, n - i);
		r = fn(ancestor, user);
		isl_schedule_node_free(ancestor);
		if (r < 0)
			return -1;
	}

	return 0;
}
