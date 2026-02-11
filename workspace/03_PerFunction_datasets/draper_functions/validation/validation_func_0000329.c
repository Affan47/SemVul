rinoo_sched_waitfor(t_sched_node *node, t_sched_mode mode)
{
	int error;

	XASSERT(mode != RINOO_MODE_NONE, -1);

	if (node->error != 0) {
		error = node->error;
		rinoo_sched_remove(node);
		errno = error;
		return -1;
	}
	if ((node->received & mode) == mode) {
		node->received -= mode;
		return 0;
	}
	if ((node->waiting & mode) != mode) {
		if (node->waiting == RINOO_MODE_NONE) {
			if (unlikely(rinoo_epoll_insert(node, mode) != 0)) {
				return -1;
			}
			list_put(&node->sched->nodes, &node->lnode);
		} else {
			if (unlikely(rinoo_epoll_addmode(node, node->waiting | mode) != 0)) {
				return -1;
			}
		}
	}
	node->mode = mode;
	node->waiting |= mode;
	node->task = rinoo_task_driver_getcurrent(node->sched);
	node->sched->nbpending++;
	if (unlikely(node->task == &node->sched->driver.main)) {
		while ((node->received & mode) != mode) {
			rinoo_sched_poll(node->sched);
			if (node->error != 0) {
				error = node->error;
				rinoo_sched_remove(node);
				errno = error;
				node->sched->nbpending--;
				return -1;
			}
		}
		node->sched->nbpending--;
		return 0;
	}
	if (rinoo_task_release(node->sched) != 0 && node->error == 0) {
		node->error = errno;
	}
	node->sched->nbpending--;

	node->task = NULL;
	if (node->error != 0) {
		error = node->error;
		rinoo_sched_remove(node);
		errno = error;
		return -1;
	}
	if ((node->received & mode) != mode) {
		rinoo_sched_remove(node);

		errno = ETIMEDOUT;
		return -1;
	}
	node->received -= mode;
	return 0;
}
