getHighestFileDescriptor() {
#if defined(F_MAXFD)
	int ret;

	do {
		ret = fcntl(0, F_MAXFD);
	} while (ret == -1 && errno == EINTR);
	if (ret == -1) {
		ret = getFileDescriptorLimit();
	}
	return ret;

#else
	int p[2], ret, flags;
	pid_t pid = -1;
	int result = -1;


	p[0] = p[1] = -1;
	do {
		ret = pipe(p);
	} while (ret == -1 && errno == EINTR);
	if (ret == -1) {
		goto done;
	}


	do {
		flags = fcntl(p[0], F_GETFL);
	} while (flags == -1 && errno == EINTR);
	if (flags == -1) {
		goto done;
	}
	do {
		fcntl(p[0], F_SETFL, flags | O_NONBLOCK);
	} while (ret == -1 && errno == EINTR);
	if (ret == -1) {
		goto done;
	}

	do {
		pid = asyncFork();
	} while (pid == -1 && errno == EINTR);

	if (pid == 0) {


		resetSignalHandlersAndMask();

		struct sigaction action;
		action.sa_handler = _exit;
		action.sa_flags   = SA_RESTART;
		sigemptyset(&action.sa_mask);
		sigaction(SIGSEGV, &action, NULL);
		sigaction(SIGPIPE, &action, NULL);
		sigaction(SIGBUS, &action, NULL);
		sigaction(SIGILL, &action, NULL);
		sigaction(SIGFPE, &action, NULL);
		sigaction(SIGABRT, &action, NULL);

		DIR *dir = NULL;
		#ifdef __APPLE__

			dir = opendir("/dev/fd");
		#else


			struct stat dirbuf1, dirbuf2;
			if (stat("/dev", &dirbuf1) == -1
			 || stat("/dev/fd", &dirbuf2) == -1) {
				_exit(1);
			}
			if (dirbuf1.st_dev != dirbuf2.st_dev) {
				dir = opendir("/dev/fd");
			}
		#endif
		if (dir == NULL) {
			dir = opendir("/proc/self/fd");
			if (dir == NULL) {
				_exit(1);
			}
		}

		struct dirent *ent;
		union {
			int highest;
			char data[sizeof(int)];
		} u;
		u.highest = -1;

		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] != '.') {
				int number = atoi(ent->d_name);
				if (number > u.highest) {
					u.highest = number;
				}
			}
		}
		if (u.highest != -1) {
			ssize_t ret, written = 0;
			do {
				ret = write(p[1], u.data + written, sizeof(int) - written);
				if (ret == -1) {
					_exit(1);
				}
				written += ret;
			} while (written < (ssize_t) sizeof(int));
		}
		closedir(dir);
		_exit(0);

	} else if (pid == -1) {
		goto done;

	} else {
		close(p[1]);
		p[1] = -1;

		union {
			int highest;
			char data[sizeof(int)];
		} u;
		ssize_t ret, bytesRead = 0;
		struct pollfd pfd;
		pfd.fd = p[0];
		pfd.events = POLLIN;

		do {
			do {


				ret = poll(&pfd, 1, 30);
			} while (ret == -1 && errno == EINTR);
			if (ret <= 0) {
				goto done;
			}

			do {
				ret = read(p[0], u.data + bytesRead, sizeof(int) - bytesRead);
			} while (ret == -1 && ret == EINTR);
			if (ret == -1) {
				if (errno != EAGAIN) {
					goto done;
				}
			} else if (ret == 0) {
				goto done;
			} else {
				bytesRead += ret;
			}
		} while (bytesRead < (ssize_t) sizeof(int));

		result = u.highest;
		goto done;
	}

done:

	if (p[0] != -1) {
		close(p[0]);
	}
	if (p[1] != -1) {
		close(p[1]);
	}
	if (pid != -1) {
		do {
			ret = kill(pid, SIGKILL);
		} while (ret == -1 && errno == EINTR);
		do {
			ret = waitpid(pid, NULL, 0);
		} while (ret == -1 && errno == EINTR);
	}

	if (result == -1) {
		result = getFileDescriptorLimit();
	}
	return result;
#endif
}
