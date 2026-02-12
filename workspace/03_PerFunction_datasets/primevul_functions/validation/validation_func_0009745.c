static int do_epoll_wait(int epfd, struct epoll_event __user *events,
			 int maxevents, int timeout)
{
	int error;
	struct fd f;
	struct eventpoll *ep;


	if (maxevents <= 0 || maxevents > EP_MAX_EVENTS)
		return -EINVAL;


	if (!access_ok(events, maxevents * sizeof(struct epoll_event)))
		return -EFAULT;


	f = fdget(epfd);
	if (!f.file)
		return -EBADF;


	error = -EINVAL;
	if (!is_file_epoll(f.file))
		goto error_fput;


	ep = f.file->private_data;


	error = ep_poll(ep, events, maxevents, timeout);

error_fput:
	fdput(f);
	return error;
}
