check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
    int flags, int checking_linkname)
{
#if !defined(HAVE_LSTAT) && \
    !(defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT))

	(void)path;
	(void)error_number;
	(void)error_string;
	(void)flags;
	(void)checking_linkname;
	return (ARCHIVE_OK);
#else
	int res = ARCHIVE_OK;
	char *tail;
	char *head;
	int last;
	char c;
	int r;
	struct stat st;
	int chdir_fd;
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
	int fd;
#endif


	if(path[0] == '\0')
	    return (ARCHIVE_OK);


	chdir_fd = la_opendirat(AT_FDCWD, ".");
	__archive_ensure_cloexec_flag(chdir_fd);
	if (chdir_fd < 0) {
		fsobj_error(a_eno, a_estr, errno,
		    "Could not open ", path);
		return (ARCHIVE_FATAL);
	}
	head = path;
	tail = path;
	last = 0;


	if(tail == path && tail[0] == '/')
		++tail;


	while (!last) {


		while (*tail == '/')
		    ++tail;

		while (*tail != '\0' && *tail != '/')
			++tail;

		last = (tail[0] == '\0') || (tail[0] == '/' && tail[1] == '\0');

		c = tail[0];
		tail[0] = '\0';

#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
		r = fstatat(chdir_fd, head, &st, AT_SYMLINK_NOFOLLOW);
#else
		r = lstat(head, &st);
#endif
		if (r != 0) {
			tail[0] = c;

			if (errno == ENOENT) {
				break;
			} else {


				fsobj_error(a_eno, a_estr, errno,
				    "Could not stat ", path);
				res = ARCHIVE_FAILED;
				break;
			}
		} else if (S_ISDIR(st.st_mode)) {
			if (!last) {
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				fd = la_opendirat(chdir_fd, head);
				if (fd < 0)
					r = -1;
				else {
					r = 0;
					close(chdir_fd);
					chdir_fd = fd;
				}
#else
				r = chdir(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not chdir ", path);
					res = (ARCHIVE_FATAL);
					break;
				}

				head = tail + 1;
			}
		} else if (S_ISLNK(st.st_mode)) {
			if (last && checking_linkname) {
#ifdef HAVE_LINKAT


				res = ARCHIVE_OK;
#else


				tail[0] = c;
				fsobj_error(a_eno, a_estr, errno,
				    "Cannot write hardlink to symlink ",
				    path);
				res = ARCHIVE_FAILED;
#endif
				break;
			} else
			if (last) {


#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = unlinkat(chdir_fd, head, 0);
#else
				r = unlink(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not remove symlink ",
					    path);
					res = ARCHIVE_FAILED;
					break;
				}


				tail[0] = c;


				res = ARCHIVE_OK;
				break;
			} else if (flags & ARCHIVE_EXTRACT_UNLINK) {

#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = unlinkat(chdir_fd, head, 0);
#else
				r = unlink(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot remove intervening "
					    "symlink ", path);
					res = ARCHIVE_FAILED;
					break;
				}
				tail[0] = c;
			} else if ((flags &
			    ARCHIVE_EXTRACT_SECURE_SYMLINKS) == 0) {


#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = fstatat(chdir_fd, head, &st, 0);
#else
				r = la_stat(head, &st);
#endif
				if (r != 0) {
					tail[0] = c;
					if (errno == ENOENT) {
						break;
					} else {
						fsobj_error(a_eno, a_estr,
						    errno,
						    "Could not stat ", path);
						res = (ARCHIVE_FAILED);
						break;
					}
				} else if (S_ISDIR(st.st_mode)) {
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
					fd = la_opendirat(chdir_fd, head);
					if (fd < 0)
						r = -1;
					else {
						r = 0;
						close(chdir_fd);
						chdir_fd = fd;
					}
#else
					r = chdir(head);
#endif
					if (r != 0) {
						tail[0] = c;
						fsobj_error(a_eno, a_estr,
						    errno,
						    "Could not chdir ", path);
						res = (ARCHIVE_FATAL);
						break;
					}


					head = tail + 1;
				} else {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot extract through "
					    "symlink ", path);
					res = ARCHIVE_FAILED;
					break;
				}
			} else {
				tail[0] = c;
				fsobj_error(a_eno, a_estr, 0,
				    "Cannot extract through symlink ", path);
				res = ARCHIVE_FAILED;
				break;
			}
		}

		tail[0] = c;
		if (tail[0] != '\0')
			tail++;
	}

	tail[0] = c;
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)


	if (chdir_fd >= 0)
		close(chdir_fd);
#elif HAVE_FCHDIR

	if (chdir_fd >= 0) {
		r = fchdir(chdir_fd);
		if (r != 0) {
			fsobj_error(a_eno, a_estr, errno,
			    "chdir() failure", "");
		}
		close(chdir_fd);
		chdir_fd = -1;
		if (r != 0) {
			res = (ARCHIVE_FATAL);
		}
	}
#endif

	return res;
#endif
}
