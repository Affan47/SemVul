l_list_remove_link(LList *list, const LList *link)
{
	if (!link)
		return list;

	if (link->next)
		link->next->prev = link->prev;
	if (link->prev)
		link->prev->next = link->next;

	if (link == list)
		list = link->next;

	return list;
}
