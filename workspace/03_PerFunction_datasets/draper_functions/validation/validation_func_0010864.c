grecs_list_locate(struct grecs_list *lp, void *data)
{
	struct grecs_list_entry *ep;
	int (*cmp)(const void *, const void *) = lp->cmp ? lp->cmp : _ptrcmp;

	for (ep = lp->head; ep; ep = ep->next) {
		if (cmp(ep->data, data) == 0)
			return ep->data;
	}
	return NULL;
}
