trapcmd(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	char *action;
	char **ap;
	int signo, exitcode;

	nextopt(nullstr);
	ap = argptr;
	if (!*ap) {
		for (signo = 0; signo < NSIG; signo++) {
			char *tr = trap_ptr[signo];
			if (tr) {


				out1fmt("trap -- %s %s\n",
						single_quote(tr),
						get_signame(signo));


			}
		}


		return 0;
	}

	action = NULL;
	if (ap[1])
		action = *ap++;
	exitcode = 0;
	while (*ap) {
		signo = get_signum(*ap);
		if (signo < 0) {

			ash_msg("%s: invalid signal specification", *ap);
			exitcode = 1;
			goto next;
		}
		INT_OFF;
		if (action) {
			if (LONE_DASH(action))
				action = NULL;
			else
				action = ckstrdup(action);
		}
		free(trap[signo]);
		if (action)
			may_have_traps = 1;
		trap[signo] = action;
		if (signo != 0)
			setsignal(signo);
		INT_ON;
 next:
		ap++;
	}
	return exitcode;
}
