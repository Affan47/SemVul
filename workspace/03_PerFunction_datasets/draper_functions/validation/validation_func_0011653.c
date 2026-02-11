list_has_next(List *list)
{
	int has;

	if (!list)
		return set_errno(EINVAL);

	if (!list->lister && !(list->lister = lister_create_unlocked(list)))
			return -1;

	if ((has = lister_has_next(list->lister)) != 1)
	  list_break(list);

	return has;
}
