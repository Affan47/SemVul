audit_set_pid(int fd, uint32_t pid, rep_wait_t wmode)
{
	struct audit_status s;
	struct audit_reply rep;
	struct pollfd pfd[1];
	int rc;

	memset(&s, 0, sizeof(s));
	s.mask    = AUDIT_STATUS_PID;
	s.pid     = pid;
	rc = audit_send(fd, AUDIT_SET, &s, sizeof(s));
	if (rc < 0) {
		audit_msg(audit_priority(errno),
			"Error setting audit daemon pid (%s)",
			strerror(-rc));
		return rc;
	}
	if (wmode == WAIT_NO)
		return 1;


	pfd[0].fd = fd;
	pfd[0].events = POLLIN;
	do {
		rc = poll(pfd, 1, 100);
	} while (rc < 0 && errno == EINTR);

	(void)audit_get_reply(fd, &rep, GET_REPLY_NONBLOCKING, 0);
	return 1;
}
