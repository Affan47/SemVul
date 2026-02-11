__update_iterators(struct list *l, void *old_item, void *new_item)
{
	struct list_iterator *i;

	for (i = l->l_iter; i; i = i->i_next) {
		if (i->i_cur == old_item)
			i->i_cur = new_item;
	}
}
