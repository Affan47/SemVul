OS__add_stack_el(struct _stack *st) {
	struct _stack_el *nel;


	if(st->cur_ptr && st->cur_ptr->next) {
		nel = st->cur_ptr->next;
		nel->bits_chopped = 0;
		nel->got = 0;

	} else {
		nel = (struct _stack_el *)CALLOC(1, sizeof(struct _stack_el));
		if(nel == NULL)
			return NULL;

		if(st->tail) {

			nel->cont_level = st->tail->cont_level + 1;
			st->tail->next = nel;
		}
		nel->prev = st->tail;
		st->tail = nel;
	}

	st->cur_ptr = nel;

	return nel;
}
