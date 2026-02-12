mono_thread_get_abort_signal (void)
{
#ifdef HOST_WIN32
	return -1;
#else
#ifndef	SIGRTMIN
#ifdef SIGUSR1
	return SIGUSR1;
#else
	return -1;
#endif
#else
	static int abort_signum = -1;
	int i;
	if (abort_signum != -1)
		return abort_signum;

	for (i = SIGRTMIN + 1; i < SIGRTMAX; ++i) {
		struct sigaction sinfo;
		sigaction (i, NULL, &sinfo);
		if (sinfo.sa_handler == SIG_DFL && (void*)sinfo.sa_sigaction == (void*)SIG_DFL) {
			abort_signum = i;
			return i;
		}
	}

	return SIGRTMIN;
#endif
#endif
}
