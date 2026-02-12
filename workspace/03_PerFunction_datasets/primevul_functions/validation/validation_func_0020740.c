run_daemon(const char* cfgfile, int cmdline_verbose, int debug_mode, int need_pidfile)
{
	struct config_file* cfg = NULL;
	struct daemon* daemon = NULL;
	int done_setup = 0;

	if(!(daemon = daemon_init()))
		fatal_exit("alloc failure");
	while(!daemon->need_to_exit) {
		if(done_setup)
			verbose(VERB_OPS, "Restart of %s.", PACKAGE_STRING);
		else	verbose(VERB_OPS, "Start of %s.", PACKAGE_STRING);


		if(!(cfg = config_create()))
			fatal_exit("Could not alloc config defaults");
		if(!config_read(cfg, cfgfile, daemon->chroot)) {
			if(errno != ENOENT)
				fatal_exit("Could not read config file: %s."
					" Maybe try unbound -dd, it stays on "
					"the commandline to see more errors, "
					"or unbound-checkconf", cfgfile);
			log_warn("Continuing with default config settings");
		}
		apply_settings(daemon, cfg, cmdline_verbose, debug_mode);
		if(!done_setup)
			config_lookup_uid(cfg);


		if(!daemon_open_shared_ports(daemon))
			fatal_exit("could not open ports");
		if(!done_setup) {
			perform_setup(daemon, cfg, debug_mode, &cfgfile, need_pidfile);
			done_setup = 1;
		} else {

			if(!cfg->use_syslog)
				log_init(cfg->logfile, 0, cfg->chrootdir);
		}

		daemon_fork(daemon);


		verbose(VERB_ALGO, "cleanup.");
		daemon_cleanup(daemon);
		config_delete(cfg);
	}
	verbose(VERB_ALGO, "Exit cleanup.");


	if(daemon->pidfile) {
		int fd;

		fd = open(daemon->pidfile, O_WRONLY | O_TRUNC, 0644);
		if(fd != -1)
			close(fd);

		unlink(daemon->pidfile);
	}
	daemon_delete(daemon);
}
