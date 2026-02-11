netsys_install_sigchld_handler(value dummy) {
#ifdef HAVE_POSIX_SIGNALS
    int code;
    struct sigaction action;
    int k;

    sigchld_lock(1, 1);

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_sigaction = sigchld_action;
    sigemptyset(&(action.sa_mask));
    action.sa_flags = SA_SIGINFO | SA_NOCLDSTOP;

    if (sigchld_list == NULL) {
	sigchld_list_len = 100;
	sigchld_list =
	    (struct sigchld_atom *) malloc(sigchld_list_len *
					   sizeof(struct sigchld_atom));
	if (sigchld_list == NULL)
	    failwith("Cannot allocate memory");

	for (k=0; k<sigchld_list_len; k++)
	    sigchld_list[k].pid = 0;
    };

    code = sigaction(SIGCHLD,
		     &action,
		     NULL);
    if (code == -1) {
	code = errno;
	sigchld_unlock(1);
	errno = code;
	uerror("sigaction", Nothing);
    };

    sigchld_unlock(1);

    return Val_unit;
#else
    invalid_argument("Netsys_posix.install_subprocess_handler not available");
#endif
}
