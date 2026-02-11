sort_by_value(struct sym *list)
{
	int			i, n;
	struct sym	*a, *b, *todo, *t;

	head_ptr = (struct sym *) malloc(sizeof(struct sym));
	head_ptr->next = list;
	a = tail_ptr;

	for (n=1; a != head_ptr->next; n = n + n)
	{
		todo = head_ptr->next;
		list = head_ptr;

		while (todo != tail_ptr)
		{
			t = todo;
			a = t;

			for (i=1; i<n; i++)
				t = t->next;

			b = t->next;
			t->next = tail_ptr;
			t = b;

			for (i=1; i<n; i++)
				t = t->next;

			todo = t->next;
			t->next = tail_ptr;
			list->next = merge_by_value(a, b);

			for (i=1; i<=n+n; i++)
				list = list->next;
		}
	}

	return(head_ptr->next);
}
