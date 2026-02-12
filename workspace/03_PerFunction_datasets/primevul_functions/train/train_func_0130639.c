sudo_askpass(const char *askpass, const char *prompt)
{
    static char buf[SUDO_CONV_REPL_MAX + 1], *pass;
    struct sigaction sa, savechld;
    enum tgetpass_errval errval;
    int pfd[2], status;
    pid_t child;
    debug_decl(sudo_askpass, SUDO_DEBUG_CONV);


    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = SIG_DFL;
    (void) sigaction(SIGCHLD, &sa, &savechld);

    if (pipe2(pfd, O_CLOEXEC) == -1)
	sudo_fatal(U_("unable to create pipe"));

    child = sudo_debug_fork();
    if (child == -1)
	sudo_fatal(U_("unable to fork"));

    if (child == 0) {

	if (dup3(pfd[1], STDOUT_FILENO, 0) == -1) {
	    sudo_warn("dup3");
	    _exit(255);
	}
	if (setuid(ROOT_UID) == -1)
	    sudo_warn("setuid(%d)", ROOT_UID);

	closefrom(STDERR_FILENO + 1);

	restore_limits();

	unlimit_nproc();
	if (setgid(user_details.gid)) {
	    sudo_warn(U_("unable to set gid to %u"), (unsigned int)user_details.gid);
	    _exit(255);
	}
	if (setuid(user_details.uid)) {
	    sudo_warn(U_("unable to set uid to %u"), (unsigned int)user_details.uid);
	    _exit(255);
	}
	restore_nproc();
	execl(askpass, askpass, prompt, (char *)NULL);
	sudo_warn(U_("unable to run %s"), askpass);
	_exit(255);
    }


    (void) close(pfd[1]);
    pass = getln(pfd[0], buf, sizeof(buf), 0, &errval);
    (void) close(pfd[0]);

    tgetpass_display_error(errval);


    for (;;) {
	pid_t rv = waitpid(child, &status, 0);
	if (rv == -1 && errno != EINTR)
	    break;
	if (rv != -1 && !WIFSTOPPED(status))
	    break;
    }

    if (pass == NULL)
	errno = EINTR;


    (void) sigaction(SIGCHLD, &savechld, NULL);

    debug_return_str_masked(pass);
}
