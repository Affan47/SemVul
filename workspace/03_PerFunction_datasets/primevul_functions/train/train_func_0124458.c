mm_session_pty_cleanup2(void *session)
{
	Session *s = session;
	Buffer m;

	if (s->ttyfd == -1)
		return;
	buffer_init(&m);
	buffer_put_cstring(&m, s->tty);
	mm_request_send(pmonitor->m_recvfd, MONITOR_REQ_PTYCLEANUP, &m);
	buffer_free(&m);


	if (close(s->ptymaster) < 0)
		error("close(s->ptymaster): %s", strerror(errno));


	s->ttyfd = -1;
}
