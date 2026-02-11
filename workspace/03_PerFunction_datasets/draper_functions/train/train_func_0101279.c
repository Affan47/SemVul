run(const struct init_action *a)
{
	pid_t pid;


	sigprocmask_allsigs(SIG_BLOCK);
	if (BB_MMU && (a->action_type & ASKFIRST))
		pid = fork();
	else
		pid = vfork();
	if (pid < 0)
		message(L_LOG | L_CONSOLE, "can't fork");
	if (pid) {
		sigprocmask_allsigs(SIG_UNBLOCK);
		return pid;
	}


	reset_sighandlers_and_unblock_sigs();


	setsid();


	if (!open_stdio_to_tty(a->terminal))
		_exit(EXIT_FAILURE);


	if (BB_MMU && (a->action_type & ASKFIRST)) {
		static const char press_enter[] ALIGN1 =
#ifdef CUSTOMIZED_BANNER
#include CUSTOMIZED_BANNER
#endif
			"\nPlease press Enter to activate this console. ";
		char c;


		dbg_message(L_LOG, "waiting for enter to start '%s'"
					"(pid %d, tty '%s')\n",
				a->command, getpid(), a->terminal);
		full_write(STDOUT_FILENO, press_enter, sizeof(press_enter) - 1);
		while (safe_read(STDIN_FILENO, &c, 1) == 1 && c != '\n')
			continue;
	}


	if (ENABLE_FEATURE_INIT_COREDUMPS) {
		if (access("/.init_enable_core", F_OK) == 0) {
			struct rlimit limit;
			limit.rlim_cur = RLIM_INFINITY;
			limit.rlim_max = RLIM_INFINITY;
			setrlimit(RLIMIT_CORE, &limit);
		}
	}


	message(L_LOG, "starting pid %d, tty '%s': '%s'",
			  getpid(), a->terminal, a->command);


	init_exec(a->command);

	_exit(-1);
}
