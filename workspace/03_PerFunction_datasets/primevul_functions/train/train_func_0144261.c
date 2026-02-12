static void ps_files_open(ps_files *data, const char *key TSRMLS_DC)
{
	char buf[MAXPATHLEN];
	struct stat sbuf;
	int ret;

	if (data->fd < 0 || !data->lastkey || strcmp(key, data->lastkey)) {
		if (data->lastkey) {
			efree(data->lastkey);
			data->lastkey = NULL;
		}

		ps_files_close(data);

		if (php_session_valid_key(key) == FAILURE) {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "The session id is too long or contains illegal characters, valid characters are a-z, A-Z, 0-9 and '-,'");
			return;
		}

		if (!ps_files_path_create(buf, sizeof(buf), data, key)) {
			return;
		}

		data->lastkey = estrdup(key);


#ifdef O_NOFOLLOW
		data->fd = VCWD_OPEN_MODE(buf, O_CREAT | O_RDWR | O_BINARY | O_NOFOLLOW, data->filemode);
#else


		if(PG(open_basedir) && lstat(buf, &sbuf) == 0 && S_ISLNK(sbuf.st_mode) && php_check_open_basedir(buf TSRMLS_CC)) {
			return;
		}
		data->fd = VCWD_OPEN_MODE(buf, O_CREAT | O_RDWR | O_BINARY, data->filemode);
#endif

		if (data->fd != -1) {
#ifndef PHP_WIN32


			if (fstat(data->fd, &sbuf) || (sbuf.st_uid != 0 && sbuf.st_uid != getuid() && sbuf.st_uid != geteuid())) {
				close(data->fd);
				data->fd = -1;
				return;
			}
#endif
			do {
				ret = flock(data->fd, LOCK_EX);
			} while (ret == -1 && errno == EINTR);

#ifdef F_SETFD
# ifndef FD_CLOEXEC
#  define FD_CLOEXEC 1
# endif
			if (fcntl(data->fd, F_SETFD, FD_CLOEXEC)) {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "fcntl(%d, F_SETFD, FD_CLOEXEC) failed: %s (%d)", data->fd, strerror(errno), errno);
			}
#endif
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "open(%s, O_RDWR) failed: %s (%d)", buf, strerror(errno), errno);
		}
	}
}
