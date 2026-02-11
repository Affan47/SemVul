sig_handle_timer(int signum)
{
	int saved_errno = errno;

	if (!--timer_save_value) {
		timer_save_value = timer_save_interval;

		event_save = event_pending = 1;
	}

	if (!--timer_ticksafety_value) {
		timer_ticksafety_value = timer_ticksafety_interval;

		event_ticksafety = event_pending = 1;
	}

	if (john_main_process) {
		int c;
#if OS_FORK
		int new_abort = 0, new_status = 0;
#endif
		while ((c = tty_getchar()) >= 0) {
			if (c == 3 || c == 'q') {
#if OS_FORK
				new_abort = 1;
#endif
				sig_handle_abort(0);
			} else {
#if OS_FORK
				new_status = 1;
#endif
				event_status = event_pending = 1;
			}
		}

#if OS_FORK
		if (new_abort || new_status)
			signal_children(new_abort ? SIGTERM : SIGUSR2);
#endif
	}

#if !OS_TIMER
	signal(SIGALRM, sig_handle_timer);
#elif !defined(SA_RESTART) && !defined(__DJGPP__)
	sig_install_timer();
#endif

	errno = saved_errno;
}
