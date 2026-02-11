knot_zone_tree_find_less_or_equal(knot_zone_tree_t *tree,
                                        const knot_dname_t *owner,
                                        const knot_node_t **found,
                                        const knot_node_t **previous)
{
	if (tree == NULL || owner == NULL || found == NULL || previous == NULL) {
		return KNOT_EINVAL;
	}

	knot_node_t *f = NULL, *p = NULL;
	int ret = knot_zone_tree_get_less_or_equal(tree, owner, &f, &p);

	*found = f;
	*previous = p;

	return ret;
}
