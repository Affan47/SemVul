elist_replace(elist_t *list, void *old, void *new)
{
	link_t *ol, *nl;

	elist_check(list);
	g_assert(old != NULL);
	g_assert(new != NULL);

	if G_UNLIKELY(old == new)
		return;

	ol = ptr_add_offset(old, list->offset);
	nl = ptr_add_offset(new, list->offset);

	elist_link_replace_internal(list, ol, nl, TRUE);

	*nl = *ol;
	ol->next = ol->prev = NULL;
}
