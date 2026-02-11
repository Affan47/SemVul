rot_left(hb_tree *tree, hb_node *node)
{
	int hc;
	hb_node *rlink, *parent;

	ASSERT(tree != NULL);
	ASSERT(node != NULL);
	ASSERT(node->rlink != NULL);

	rlink = node->rlink;
	node->rlink = rlink->llink;
	if (rlink->llink)
		rlink->llink->parent = node;
	parent = node->parent;
	rlink->parent = parent;
	if (parent) {
		if (parent->llink == node)
			parent->llink = rlink;
		else
			parent->rlink = rlink;
	} else {
		tree->root = rlink;
	}
	rlink->llink = node;
	node->parent = rlink;

	hc = rlink->bal != 0;
	node->bal  -= 1 + MAX(rlink->bal, 0);
	rlink->bal -= 1 - MIN(node->bal, 0);
	return hc;
}
