eslist_link_remove_after_internal(eslist_t *list, slink_t *prevlk, slink_t *lk)
{
	g_assert(size_is_positive(list->count));
	eslist_invariant(list);

	if G_UNLIKELY(list->tail == lk)
		list->tail = prevlk;

	if (NULL == prevlk) {

		g_assert(list->head == lk);
		list->head = lk->next;
	} else {
		prevlk->next = lk->next;
	}

	lk->next = NULL;
	list->count--;

	safety_assert(eslist_invariant(list));
	safety_assert(eslist_length(list->head) == list->count);
}
