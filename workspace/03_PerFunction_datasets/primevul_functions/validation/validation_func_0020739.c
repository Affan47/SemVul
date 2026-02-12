perform_setup(struct daemon* daemon, struct config_file* cfg, int debug_mode,
	const char** cfgfile, int need_pidfile)
{
#ifdef HAVE_KILL
	int pidinchroot;
#endif
#ifdef HAVE_GETPWNAM
	struct passwd *pwd = NULL;

	if(cfg->username && cfg->username[0]) {
		if((pwd = getpwnam(cfg->username)) == NULL)
			fatal_exit("user '%s' does not exist.", cfg->username);

	}
#endif
#ifdef UB_ON_WINDOWS
	w_config_adjust_directory(cfg);
#endif


#ifdef HAVE_SSL
	if(!(daemon->rc = daemon_remote_create(cfg)))
		fatal_exit("could not set up remote-control");
	if(cfg->ssl_service_key && cfg->ssl_service_key[0]) {
		if(!(daemon->listen_sslctx = listen_sslctx_create(
			cfg->ssl_service_key, cfg->ssl_service_pem, NULL)))
			fatal_exit("could not set up listen SSL_CTX");
		if(cfg->tls_ciphers && cfg->tls_ciphers[0]) {
			if (!SSL_CTX_set_cipher_list(daemon->listen_sslctx, cfg->tls_ciphers)) {
				fatal_exit("failed to set tls-cipher %s", cfg->tls_ciphers);
			}
		}
#ifdef HAVE_SSL_CTX_SET_CIPHERSUITES
		if(cfg->tls_ciphersuites && cfg->tls_ciphersuites[0]) {
			if (!SSL_CTX_set_ciphersuites(daemon->listen_sslctx, cfg->tls_ciphersuites)) {
				fatal_exit("failed to set tls-ciphersuites %s", cfg->tls_ciphersuites);
			}
		}
#endif
		if(cfg->tls_session_ticket_keys.first &&
			cfg->tls_session_ticket_keys.first->str[0] != 0) {
			if(!listen_sslctx_setup_ticket_keys(daemon->listen_sslctx, cfg->tls_session_ticket_keys.first)) {
				fatal_exit("could not set session ticket SSL_CTX");
			}
		}
	}
	if(!(daemon->connect_sslctx = connect_sslctx_create(NULL, NULL,
		cfg->tls_cert_bundle, cfg->tls_win_cert)))
		fatal_exit("could not set up connect SSL_CTX");
#endif


	if(cfg->use_syslog) {
		log_init(cfg->logfile, cfg->use_syslog, cfg->chrootdir);
	}


#ifdef HAVE_KILL

	pidinchroot = need_pidfile && (!(cfg->chrootdir && cfg->chrootdir[0]) ||
				(cfg->chrootdir && cfg->chrootdir[0] &&
				strncmp(cfg->pidfile, cfg->chrootdir,
				strlen(cfg->chrootdir))==0));


	if(cfg->pidfile && cfg->pidfile[0] && need_pidfile) {

		if(cfg->pidfile[0] == '/')
			daemon->pidfile = strdup(cfg->pidfile);
		else	daemon->pidfile = fname_after_chroot(cfg->pidfile,
				cfg, 1);
		if(!daemon->pidfile)
			fatal_exit("pidfile alloc: out of memory");
		checkoldpid(daemon->pidfile, pidinchroot);
	}
#endif


	if(!debug_mode && cfg->do_daemonize) {
		detach();
	}


#ifdef HAVE_KILL
	if(cfg->pidfile && cfg->pidfile[0] && need_pidfile) {
		writepid(daemon->pidfile, getpid());
		if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1 &&
			pidinchroot) {
#  ifdef HAVE_CHOWN
			if(chown(daemon->pidfile, cfg_uid, cfg_gid) == -1) {
				verbose(VERB_QUERY, "cannot chown %u.%u %s: %s",
					(unsigned)cfg_uid, (unsigned)cfg_gid,
					daemon->pidfile, strerror(errno));
			}
#  endif
		}
	}
#else
	(void)daemon;
	(void)need_pidfile;
#endif


#ifdef HAVE_GETPWNAM
	if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1) {
#ifdef HAVE_SETUSERCONTEXT


		if(setusercontext(NULL, pwd, cfg_uid, (unsigned)
			LOGIN_SETALL & ~LOGIN_SETUSER & ~LOGIN_SETGROUP) != 0)
			log_warn("unable to setusercontext %s: %s",
				cfg->username, strerror(errno));
#else
		(void)pwd;
#endif
	}
#endif


#ifdef HAVE_CHROOT
	if(cfg->chrootdir && cfg->chrootdir[0]) {
		if(chdir(cfg->chrootdir)) {
			fatal_exit("unable to chdir to chroot %s: %s",
				cfg->chrootdir, strerror(errno));
		}
		verbose(VERB_QUERY, "chdir to %s", cfg->chrootdir);
		if(chroot(cfg->chrootdir))
			fatal_exit("unable to chroot to %s: %s",
				cfg->chrootdir, strerror(errno));
		if(chdir("/"))
			fatal_exit("unable to chdir to / in chroot %s: %s",
				cfg->chrootdir, strerror(errno));
		verbose(VERB_QUERY, "chroot to %s", cfg->chrootdir);
		if(strncmp(*cfgfile, cfg->chrootdir,
			strlen(cfg->chrootdir)) == 0)
			(*cfgfile) += strlen(cfg->chrootdir);


		if(daemon->pidfile && daemon->pidfile[0] &&
			strncmp(daemon->pidfile, cfg->chrootdir,
			strlen(cfg->chrootdir))==0) {
			char* old = daemon->pidfile;
			daemon->pidfile = strdup(old+strlen(cfg->chrootdir));
			free(old);
			if(!daemon->pidfile)
				log_err("out of memory in pidfile adjust");
		}
		daemon->chroot = strdup(cfg->chrootdir);
		if(!daemon->chroot)
			log_err("out of memory in daemon chroot dir storage");
	}
#else
	(void)cfgfile;
#endif

	if(cfg->directory && cfg->directory[0]) {
		char* dir = cfg->directory;
		if(cfg->chrootdir && cfg->chrootdir[0] &&
			strncmp(dir, cfg->chrootdir,
			strlen(cfg->chrootdir)) == 0)
			dir += strlen(cfg->chrootdir);
		if(dir[0]) {
			if(chdir(dir)) {
				fatal_exit("Could not chdir to %s: %s",
					dir, strerror(errno));
			}
			verbose(VERB_QUERY, "chdir to %s", dir);
		}
	}


#ifdef HAVE_GETPWNAM
	if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1) {
#  ifdef HAVE_INITGROUPS
		if(initgroups(cfg->username, cfg_gid) != 0)
			log_warn("unable to initgroups %s: %s",
				cfg->username, strerror(errno));
#  endif
#  ifdef HAVE_ENDPWENT
		endpwent();
#  endif

#ifdef HAVE_SETRESGID
		if(setresgid(cfg_gid,cfg_gid,cfg_gid) != 0)
#elif defined(HAVE_SETREGID) && !defined(DARWIN_BROKEN_SETREUID)
		if(setregid(cfg_gid,cfg_gid) != 0)
#else
		if(setgid(cfg_gid) != 0)
#endif
			fatal_exit("unable to set group id of %s: %s",
				cfg->username, strerror(errno));
#ifdef HAVE_SETRESUID
		if(setresuid(cfg_uid,cfg_uid,cfg_uid) != 0)
#elif defined(HAVE_SETREUID) && !defined(DARWIN_BROKEN_SETREUID)
		if(setreuid(cfg_uid,cfg_uid) != 0)
#else
		if(setuid(cfg_uid) != 0)
#endif
			fatal_exit("unable to set user id of %s: %s",
				cfg->username, strerror(errno));
		verbose(VERB_QUERY, "drop user privileges, run as %s",
			cfg->username);
	}
#endif


	if(!cfg->use_syslog)
		log_init(cfg->logfile, cfg->use_syslog, cfg->chrootdir);
}
