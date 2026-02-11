list_apply_wrlocked(List *list, list_action_t *action, void *data)
{
	int err;

	if (!list || !action)
	{
		set_errno(EINVAL);
		return;
	}

	if ((err = list_wrlock(list)))
	{
		set_errno(err);
		return;
	}

	list_apply_unlocked(list, action, data);

	if ((err = list_unlock(list)))
		set_errno(err);
}
