btree_cmp_iters(const btree_iterator iter_a, const btree_iterator iter_b)
{
	btree_iterator a = {*iter_a}, b = {*iter_b};
	int ad, bd;

	ad = btree_deref(a);
	bd = btree_deref(b);


	if (!ad)
		return bd ? 1 : 0;
	if (!bd)
		return ad ? -1 : 0;


	if (a->node->depth < b->node->depth) {
		if (elevate(a, b))
			return -1;
	} else if (a->node->depth > b->node->depth) {
		if (elevate(b, a))
			return 1;
	}


	while (a->node != b->node) {
		ascend(a);
		ascend(b);
	}


	if (a->k < b->k)
		return -1;
	if (a->k > b->k)
		return 1;

	return 0;
}
