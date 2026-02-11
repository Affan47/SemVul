cl_signal_set_action(int sig, void (*action)(int, siginfo_t *, void *)
,	sigset_t *mask, int flags, struct sigaction *oldact)
{
	struct sigaction sa;

	sa.sa_sigaction = action;
	sa.sa_mask = *mask;
	sa.sa_flags = flags;

	if(sigaction(sig, &sa, oldact) < 0) {
		cl_perror("cl_signal_set_action(): sigaction()");
		return(-1);
	}

	return(0);
}
