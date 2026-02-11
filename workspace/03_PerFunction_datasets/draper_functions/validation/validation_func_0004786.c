_xmmsv_list_clear (xmmsv_list_t *l)
{
	xmmsv_list_iter_t *it;
	x_list_t *n;
	int i;


	for (i = 0; i < l->size; i++) {
		xmmsv_unref (l->list[i]);
	}


	free (l->list);
	l->list = NULL;

	l->size = 0;
	l->allocated = 0;


	for (n = l->iterators; n; n = n->next) {
		it = (xmmsv_list_iter_t *) n->data;
		it->position = 0;
	}
}
