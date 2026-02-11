uu_lock(const char *tty_name)
{
	int fd, tmpfd, i;
	pid_t pid, pid_old;
	char lckname[sizeof(_PATH_UUCPLOCK) + MAXNAMLEN],
	     lcktmpname[sizeof(_PATH_UUCPLOCK) + MAXNAMLEN];
	int err, uuerr;

	pid = getpid();
	(void)snprintf(lcktmpname, sizeof(lcktmpname), _PATH_UUCPLOCK LOCKTMP,
			pid);
	(void)snprintf(lckname, sizeof(lckname), _PATH_UUCPLOCK LOCKFMT,
			tty_name);
	if ((tmpfd = creat(lcktmpname, 0664)) < 0)
		GORET(0, UU_LOCK_CREAT_ERR);

	for (i = 0; i < MAXTRIES; i++) {
		if (link (lcktmpname, lckname) < 0) {
			if (errno != EEXIST)
				GORET(1, UU_LOCK_LINK_ERR);


			if ((fd = open(lckname, O_RDONLY)) < 0)
				GORET(1, UU_LOCK_OPEN_ERR);

			if ((pid_old = get_pid (fd, &err)) == -1)
				GORET(2, UU_LOCK_READ_ERR);

			close(fd);

			if (kill(pid_old, 0) == 0 || errno != ESRCH)
				GORET(1, UU_LOCK_INUSE);


			(void)unlink(lckname);
		} else {
			if (!put_pid (tmpfd, pid))
				GORET(3, UU_LOCK_WRITE_ERR);
			break;
		}
	}
	GORET(1, (i >= MAXTRIES) ? UU_LOCK_TRY_ERR : UU_LOCK_OK);

ret3:
	(void)unlink(lckname);
	goto ret1;
ret2:
	(void)close(fd);
ret1:
	(void)close(tmpfd);
	(void)unlink(lcktmpname);
ret0:
	errno = err;
	return uuerr;
}
