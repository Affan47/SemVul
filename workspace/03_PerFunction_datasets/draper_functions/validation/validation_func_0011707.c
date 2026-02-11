handle_events()
{
    struct timeval timo;

    kill_link = open_ccp_flag = 0;
    if (sigsetjmp(sigjmp, 1) == 0) {
	sigprocmask(SIG_BLOCK, &signals_handled, NULL);
	if (got_sighup || got_sigterm || got_sigusr2 || got_sigchld) {
	    sigprocmask(SIG_UNBLOCK, &signals_handled, NULL);
	} else {
	    waiting = 1;
	    sigprocmask(SIG_UNBLOCK, &signals_handled, NULL);
	    wait_input(timeleft(&timo));
	}
    }
    waiting = 0;
    calltimeout();
    if (got_sighup) {
	info("Hangup (SIGHUP)");
	kill_link = 1;
	got_sighup = 0;
	if (status != EXIT_HANGUP)
	    status = EXIT_USER_REQUEST;
    }
    if (got_sigterm) {
	info("Terminating on signal %d", got_sigterm);
	kill_link = 1;
	asked_to_quit = 1;
	persist = 0;
	status = EXIT_USER_REQUEST;
	got_sigterm = 0;
    }
    if (got_sigchld) {
	got_sigchld = 0;
	reap_kids();
    }
    if (got_sigusr2) {
	open_ccp_flag = 1;
	got_sigusr2 = 0;
    }
}
