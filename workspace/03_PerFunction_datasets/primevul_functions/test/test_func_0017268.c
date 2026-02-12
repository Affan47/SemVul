int __close_range(unsigned fd, unsigned max_fd, unsigned int flags)
{
	struct task_struct *me = current;
	struct files_struct *cur_fds = me->files, *fds = NULL;

	if (flags & ~(CLOSE_RANGE_UNSHARE | CLOSE_RANGE_CLOEXEC))
		return -EINVAL;

	if (fd > max_fd)
		return -EINVAL;

	if (flags & CLOSE_RANGE_UNSHARE) {
		int ret;
		unsigned int max_unshare_fds = NR_OPEN_MAX;


		if (!(flags & CLOSE_RANGE_CLOEXEC)) {


			rcu_read_lock();
			if (max_fd >= last_fd(files_fdtable(cur_fds)))
				max_unshare_fds = fd;
			rcu_read_unlock();
		}

		ret = unshare_fd(CLONE_FILES, max_unshare_fds, &fds);
		if (ret)
			return ret;


		if (fds)
			swap(cur_fds, fds);
	}

	if (flags & CLOSE_RANGE_CLOEXEC)
		__range_cloexec(cur_fds, fd, max_fd);
	else
		__range_close(cur_fds, fd, max_fd);

	if (fds) {


		task_lock(me);
		me->files = cur_fds;
		task_unlock(me);
		put_files_struct(fds);
	}

	return 0;
}
