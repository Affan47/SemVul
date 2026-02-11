checkout_action_common(
	checkout_data *data,
	int action,
	const git_diff_delta *delta,
	const git_index_entry *wd)
{
	git_checkout_notify_t notify = GIT_CHECKOUT_NOTIFY_NONE;

	if (action <= 0)
		return action;

	if ((data->strategy & GIT_CHECKOUT_UPDATE_ONLY) != 0)
		action = (action & ~CHECKOUT_ACTION__REMOVE);

	if ((action & CHECKOUT_ACTION__UPDATE_BLOB) != 0) {
		if (S_ISGITLINK(delta->new_file.mode))
			action = (action & ~CHECKOUT_ACTION__UPDATE_BLOB) |
				CHECKOUT_ACTION__UPDATE_SUBMODULE;

		notify = GIT_CHECKOUT_NOTIFY_UPDATED;
	}

	if ((action & CHECKOUT_ACTION__CONFLICT) != 0)
		notify = GIT_CHECKOUT_NOTIFY_CONFLICT;

	if (notify != GIT_CHECKOUT_NOTIFY_NONE &&
		checkout_notify(data, notify, delta, wd) != 0)
		return GIT_EUSER;

	return action;
}
