slset_clear(struct slset *s, void (*deallocator)(void *))
{
	struct slset_entry *i;
	struct slset_entry *n;

	for (i = s->first; i != NULL; ) {
		n = i;
		i = i->next;
		deallocator(n);
	}

	s->first = NULL;
}
