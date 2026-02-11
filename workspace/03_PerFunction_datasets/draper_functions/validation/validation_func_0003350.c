xnode_tree_find_depth(xnode_t *root, unsigned depth,
	match_fn_t func, void *data)
{
	etree_t t;

	xnode_check(root);
	g_assert(uint_is_non_negative(depth));

	etree_init_root(&t, root, TRUE, offsetof(xnode_t, node));
	return etree_find_depth(&t, depth, func, data);
}
