sstate_readline(upstype_t *ups)
{
	int	i, ret;
	char	buf[SMALLBUF];

	if ((!ups) || (ups->sock_fd < 0)) {
		return;
	}

	ret = read(ups->sock_fd, buf, sizeof(buf));

	if (ret < 0) {
		switch(errno)
		{
		case EINTR:
		case EAGAIN:
			return;

		default:
			upslog_with_errno(LOG_WARNING, "Read from UPS [%s] failed", ups->name);
			sstate_disconnect(ups);
			return;
		}
	}

	for (i = 0; i < ret; i++) {

		switch (pconf_char(&ups->sock_ctx, buf[i]))
		{
		case 1:

			if (parse_args(ups, ups->sock_ctx.numargs, ups->sock_ctx.arglist)) {
			        time(&ups->last_heard);
			}
			continue;

		case 0:
			continue;

		default:

			upslogx(LOG_NOTICE, "Parse error on sock: %s", ups->sock_ctx.errmsg);
			return;
		}
	}
}
