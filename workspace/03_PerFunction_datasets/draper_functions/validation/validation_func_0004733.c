fifo_remove(fifo_t *f)
{
	GList *prev;
	void *data;

	if (f->count == 0)
		return NULL;

	g_assert(f->tail != NULL);

	data = f->tail->data;
	prev = g_list_previous(f->tail);

	if (prev == NULL) {
		g_assert(f->tail == f->head);
		g_assert(f->count == 1);
		f->head = f->tail = g_list_remove(f->head, data);
	} else {
		IGNORE_RESULT(g_list_remove_link(prev, f->tail));
		g_list_free_1(f->tail);
		f->tail = prev;
	}

	f->count--;

	g_assert(f->count == 0 || f->head != NULL);
	g_assert(f->count == 0 || f->tail != NULL);
	g_assert(f->head == NULL || f->count != 0);
	g_assert(f->tail == NULL || f->count != 0);

	return data;
}
