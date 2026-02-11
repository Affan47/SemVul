Mono_Unix_UnixSignal_uninstall (void* info)
{
#if defined(HAVE_SIGNAL)
	signal_info* h;
	int r = -1;

	if (acquire_mutex (&signals_mutex) == -1)
		return -1;

	h = info;

	if (h == NULL || h < signals || h > &signals [NUM_SIGNALS])
		errno = EINVAL;
	else {

		int signum = mph_int_get (&h->signum);
		if (h->have_handler && count_handlers (signum) == 1) {
			mph_sighandler_t p = signal (signum, h->handler);
			if (p != SIG_ERR)
				r = 0;
			h->handler      = NULL;
			h->have_handler = 0;
		}
		mph_int_set (&h->signum, 0);
	}

	release_mutex (&signals_mutex);

	return r;
#else
	g_error ("signal() is not supported by this platform");
	return 0;
#endif
}
