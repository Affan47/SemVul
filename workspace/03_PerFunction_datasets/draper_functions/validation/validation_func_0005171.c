etree_detach(etree_t *tree, void *item)
{
	node_t *n;

	etree_check(tree);
	g_assert(item != NULL);

	n = ptr_add_offset(item, tree->offset);

	if (NULL == n->parent) {

		g_assert(NULL == n->sibling);
		g_assert(n == tree->root);
		tree->root = NULL;
		tree->count = 0;
	} else {
		node_t *parent = n->parent;

		if (n == parent->child) {
			if (etree_is_extended(tree)) {
				nodex_t *px = (nodex_t *) parent;
				if (n == px->last_child) {
					g_assert(NULL == n->sibling);
					px->child = px->last_child = NULL;
				} else {
					g_assert(NULL != n->sibling);
					parent->child = n->sibling;
				}
			} else {
				parent->child = n->sibling;
			}
		} else {
			node_t *cn;
			bool found = FALSE;


			for (cn = parent->child; cn != NULL; cn = cn->sibling) {
				if (cn->sibling == n) {
					found = TRUE;
					break;
				}
			}

			g_assert(found);

			cn->sibling = n->sibling;


			if (etree_is_extended(tree)) {
				nodex_t *px = (nodex_t *) parent;

				if (n == px->last_child) {
					g_assert(NULL == n->sibling);
					px->last_child = cn;
				}
			}
		}

		n->sibling = NULL;
		tree->count = 0;
	}
}
