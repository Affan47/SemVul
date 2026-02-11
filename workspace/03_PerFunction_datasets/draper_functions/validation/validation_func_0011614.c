isl_schedule_node_insert_mark(
	__isl_take isl_schedule_node *node, __isl_take isl_id *mark)
{
	isl_schedule_tree *tree;

	if (check_insert(node) < 0)
		node = isl_schedule_node_free(node);

	tree = isl_schedule_node_get_tree(node);
	tree = isl_schedule_tree_insert_mark(tree, mark);
	node = isl_schedule_node_graft_tree(node, tree);

	return node;
}
