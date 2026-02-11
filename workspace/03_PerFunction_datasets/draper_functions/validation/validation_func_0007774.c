evthread_notify_drain_default(evutil_socket_t fd, short what, void *arg)
{
	unsigned char buf[1024];
	struct event_base *base = arg;
#ifdef WIN32
	while (recv(fd, (char*)buf, sizeof(buf), 0) > 0)
		;
#else
	while (read(fd, (char*)buf, sizeof(buf)) > 0)
		;
#endif

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	base->is_notify_pending = 0;
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}
