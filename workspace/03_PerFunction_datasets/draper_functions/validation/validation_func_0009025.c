msproxy_sessionsend(void)
{
	const char *function = "msproxy_sessionsend()";
	int i, max;
	struct socksfd_t *socksfd;

	slog(LOG_DEBUG, "%s", function);

	for (i = 0, max = getdtablesize(); i < max; ++i) {
		if ((socksfd = socks_getaddr((unsigned int)i)) == NULL)
			continue;

		if (socksfd->state.version != MSPROXY_V2)
			continue;

		msproxy_sessionend(socksfd->control, &socksfd->state.msproxy);
	}
}
