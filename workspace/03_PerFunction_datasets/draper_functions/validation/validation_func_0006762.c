dsp_fd_add(int fd,void (*callback)(int fd,void *user),void *user)
{
    FD_ENTRY *entry;

    for (entry = fd_idle; entry; entry = entry->next)
	if (entry->fd == fd) break;
    if (!entry)
	for (entry = fd_active; entry; entry = entry->next)
	    if (entry->fd == fd) break;
    if (entry) {
	fprintf(stderr,"dsp_fd_add: duplicate fd %d\n",fd);
	exit(1);
    }
    if (fd >= fds) fds = fd+1;
    FD_SET(fd,&r_set);
    entry = alloc_t(FD_ENTRY);
    entry->fd = fd;
    entry->callback = callback;
    entry->user = user;
    entry->next = fd_idle;
    fd_idle = entry;
}
