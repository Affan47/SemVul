main(int argc, char **argv)
{
	int i, retval = 0, dflag = 0, kflag = 0;
	const char *target_user = NULL, *user = NULL, *tty = NULL;
	struct passwd *pwd;
	struct timeval tv;
	fd_set write_fds;
	char path[BUFLEN];
	struct stat st;


	if ((fstat(STDIN_FILENO, &st) == -1) ||
	    (fstat(STDOUT_FILENO, &st) == -1) ||
	    (fstat(STDERR_FILENO, &st) == -1)) {

		return 3;
	}


	while ((i = getopt(argc, argv, "dk")) != -1) {
		switch (i) {
			case 'd':
				dflag++;
				break;
			case 'k':
				kflag++;
				break;
			default:
				fprintf(stderr, USAGE, argv[0]);
				return 1;
				break;
		}
	}


	if ((kflag + dflag) > 1) {
		fprintf(stderr, USAGE, argv[0]);
		return 1;
	}


	if (geteuid() != 0) {
		fprintf(stderr, "%s must be setuid root\n",
			argv[0]);
		retval = 2;
	}


	tty = ttyname(STDIN_FILENO);
	if ((tty == NULL) || (strlen(tty) == 0)) {
		tty = ttyname(STDOUT_FILENO);
	}
	if ((tty == NULL) || (strlen(tty) == 0)) {
		tty = ttyname(STDERR_FILENO);
	}
	if ((tty == NULL) || (strlen(tty) == 0)) {
		tty = "unknown";
	}


	pwd = getpwuid(getuid());
	if (pwd == NULL) {
		retval = 4;
	}


	user = strdup(pwd->pw_name);
	if (user == NULL) {
		retval = 4;
	} else {
		target_user = (optind < argc) ? argv[optind] : user;
		if ((strchr(target_user, '.') != NULL) ||
		    (strchr(target_user, '/') != NULL) ||
		    (strchr(target_user, '%') != NULL)) {
			fprintf(stderr, "unknown user: %s\n",
				target_user);
			retval = 4;
		}
	}


	if (retval == 0) {
		tty = check_tty(tty);
		if (tty == NULL) {
			fprintf(stderr, "invalid tty\n");
			retval = 6;
		}
	}

	do {

		if (retval == 0) {
			if (check_dir_perms(NULL, TIMESTAMPDIR) != PAM_SUCCESS) {
				retval = 5;
			}
		}

		if (retval == 0) {

			format_timestamp_name(path, sizeof(path), TIMESTAMPDIR,
					      tty, user, target_user);
		}

		if (retval == 0) {
			if (kflag) {

				if (lstat(path, &st) != -1) {
					retval = unlink(path);
				}
			} else {

				if (lstat(path, &st) != -1) {

					if (check_login_time(user, st.st_mtime) != PAM_SUCCESS) {
						retval = 7;
					} else if (!timestamp_good(st.st_mtime, time(NULL),
							    DEFAULT_TIMESTAMP_TIMEOUT) == PAM_SUCCESS) {
						retval = 7;
					}
				} else {
					retval = 7;
				}
			}
		}

		if (dflag > 0) {
			struct timeval now;

			signal(SIGPIPE, SIG_DFL);
			fprintf(stdout, "%d\n", retval);
			fflush(stdout);

			gettimeofday(&now, NULL);
			tv.tv_sec = CHECK_INTERVAL;

			tv.tv_usec = 1000000 - now.tv_usec;
			if (now.tv_usec < 500000)
				tv.tv_sec--;
			FD_ZERO(&write_fds);
			FD_SET(STDOUT_FILENO, &write_fds);
			select(STDOUT_FILENO + 1,
			       NULL, NULL, &write_fds,
			       &tv);
			retval = 0;
		}
	} while (dflag > 0);

	return retval;
}
