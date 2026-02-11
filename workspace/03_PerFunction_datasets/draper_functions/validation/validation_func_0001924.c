aim_ssi_itemlist_del(struct aim_ssi_item **list,
	struct aim_ssi_item *del)
{
	if (!list || !(*list) || !del)
		return -EINVAL;


	if (*list == del) {
		*list = (*list)->next;
	} else {
		struct aim_ssi_item *cur;
		for (cur = *list; (cur->next && (cur->next != del));
			cur = cur->next) ;
		if (cur->next)
			cur->next = cur->next->next;
	}


	free(del->name);
	aim_freetlvchain(&del->data);
	free(del);

	return 0;
}
