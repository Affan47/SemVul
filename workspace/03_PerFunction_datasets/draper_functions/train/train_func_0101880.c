flist_remove_obj(flist *list, void *object)
{
	flist *tl = list;

	while (tl && tl->object != object)
	{
		tl = tl->next;
	}

	if (tl == NULL)
	{
		return NULL;
	}

	if (tl->prev)
	{
		tl->prev->next = tl->next;
	}
	if (tl->next)
	{
		tl->next->prev = tl->prev;
	}
	if (list == tl)
	{
		list = list->next;
	}
	free(tl);

	return list;
}
