ev_ses_started(struct ap_session *ses)
{
	pid_t pid;
	char *argv[8];
	char *env[4];
	char ipaddr[17];
	char peer_ipaddr[17];
	char peername[64];
	char calling_sid[64];
	char called_sid[64];
	struct pppd_compat_pd *pd = find_pd(ses);

	if (!pd)
		return;

	argv[4] = ipaddr;
	argv[5] = peer_ipaddr;
	fill_argv(argv, pd, conf_ip_up);

	env[0] = peername;
	env[1] = calling_sid;
	env[2] = called_sid;
	env[3] = NULL;
	fill_env(env, pd);

	if (conf_ip_up) {
		sigchld_lock();
		pid = fork();
		if (pid > 0) {
			pd->ip_up_hnd.pid = pid;
			sigchld_register_handler(&pd->ip_up_hnd);
			if (conf_verbose)
				log_ppp_info2("pppd_compat: ip-up started (pid %i)\n", pid);
			sigchld_unlock();
		} else if (pid == 0) {
			sigset_t set;
			sigfillset(&set);
			pthread_sigmask(SIG_UNBLOCK, &set, NULL);

			execve(conf_ip_up, argv, env);
			log_emerg("pppd_compat: exec '%s': %s\n", conf_ip_up, strerror(errno));
			_exit(EXIT_FAILURE);
		} else
			log_error("pppd_compat: fork: %s\n", strerror(errno));
	}

	pd->started = 1;
}
