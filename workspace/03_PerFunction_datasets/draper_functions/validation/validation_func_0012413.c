__bch_bset_search(struct btree_keys *b, struct bset_tree *t,
			       const struct bkey *search)
{
	struct bset_search_iter i;


	if (unlikely(!t->size)) {
		i.l = t->data->start;
		i.r = bset_bkey_last(t->data);
	} else if (bset_written(b, t)) {


		if (unlikely(bkey_cmp(search, &t->end) >= 0))
			return bset_bkey_last(t->data);

		if (unlikely(bkey_cmp(search, t->data->start) < 0))
			return t->data->start;

		i = bset_search_tree(t, search);
	} else {
		BUG_ON(!b->nsets &&
		       t->size < bkey_to_cacheline(t, bset_bkey_last(t->data)));

		i = bset_search_write_set(t, search);
	}

	if (btree_keys_expensive_checks(b)) {
		BUG_ON(bset_written(b, t) &&
		       i.l != t->data->start &&
		       bkey_cmp(tree_to_prev_bkey(t,
			  inorder_to_tree(bkey_to_cacheline(t, i.l), t)),
				search) > 0);

		BUG_ON(i.r != bset_bkey_last(t->data) &&
		       bkey_cmp(i.r, search) <= 0);
	}

	while (likely(i.l != i.r) &&
	       bkey_cmp(i.l, search) <= 0)
		i.l = bkey_next(i.l);

	return i.l;
}
