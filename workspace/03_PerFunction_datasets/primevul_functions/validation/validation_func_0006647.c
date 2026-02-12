static inline bool slab_free_freelist_hook(struct kmem_cache *s,
					   void **head, void **tail)
{

	void *object;
	void *next = *head;
	void *old_tail = *tail ? *tail : *head;
	int rsize;


	*head = NULL;
	*tail = NULL;

	do {
		object = next;
		next = get_freepointer(s, object);

		if (slab_want_init_on_free(s)) {


			memset(object, 0, s->object_size);
			rsize = (s->flags & SLAB_RED_ZONE) ? s->red_left_pad
							   : 0;
			memset((char *)object + s->inuse, 0,
			       s->size - s->inuse - rsize);

		}

		if (!slab_free_hook(s, object)) {

			set_freepointer(s, object, *head);
			*head = object;
			if (!*tail)
				*tail = object;
		}
	} while (object != old_tail);

	if (*head == *tail)
		*tail = NULL;

	return *head != NULL;
}
