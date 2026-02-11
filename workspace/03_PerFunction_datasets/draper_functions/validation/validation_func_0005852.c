watcher_create()
{
	private_watcher_t *this;
	int flags;

	INIT(this,
		.public = {
			.add = _add,
			.remove = _remove_,
			.destroy = _destroy,
		},
		.fds = linked_list_create(),
		.mutex = mutex_create(MUTEX_TYPE_DEFAULT),
		.condvar = condvar_create(CONDVAR_TYPE_DEFAULT),
		.jobs = linked_list_create(),
		.notify = {-1, -1},
	);

	if (pipe(this->notify) == 0)
	{

		flags = fcntl(this->notify[0], F_GETFL);
		if (flags == -1 ||
			fcntl(this->notify[0], F_SETFL, flags | O_NONBLOCK) == -1)
		{
			DBG1(DBG_LIB, "setting watcher notify pipe read-end non-blocking "
				 "failed: %s", strerror(errno));
		}
	}
	else
	{
		DBG1(DBG_LIB, "creating watcher notify pipe failed: %s",
			 strerror(errno));
	}
	return &this->public;
}
