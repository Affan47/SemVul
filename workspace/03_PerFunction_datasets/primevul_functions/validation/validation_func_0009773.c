static inline bool list_add_tail_lockless(struct list_head *new,
					  struct list_head *head)
{
	struct list_head *prev;


	if (cmpxchg(&new->next, new, head) != new)
		return false;


	prev = xchg(&head->prev, new);


	prev->next = new;
	new->prev = prev;

	return true;
}
