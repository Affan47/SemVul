file_open(struct archive *a, void *client_data)
{
	int flags;
	struct write_file_data *mine;
	struct stat st;

	mine = (struct write_file_data *)client_data;
	flags = O_WRONLY | O_CREAT | O_TRUNC | O_BINARY;


	if (mine->mbs_filename) {
		mine->fd = open(mine->filename.m, flags, 0666);
		if (mine->fd < 0) {
			archive_set_error(a, errno, "Failed to open '%s'",
			    mine->filename.m);
			return (ARCHIVE_FATAL);
		}

		if (fstat(mine->fd, &st) != 0) {
			archive_set_error(a, errno, "Couldn't stat '%s'",
			    mine->filename.m);
			return (ARCHIVE_FATAL);
		}
	} else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		mine->fd = _wopen(mine->filename.w, flags, 0666);
		if (mine->fd < 0 && errno == ENOENT) {
			wchar_t *fullpath;
			fullpath = __la_win_permissive_name_w(mine->filename.w);
			if (fullpath != NULL) {
				mine->fd = _wopen(fullpath, flags, 0666);
				free(fullpath);
			}
		}
		if (mine->fd < 0) {
			archive_set_error(a, errno, "Failed to open '%S'",
			    mine->filename.w);
			return (ARCHIVE_FATAL);
		}

		if (fstat(mine->fd, &st) != 0) {
			archive_set_error(a, errno, "Couldn't stat '%S'",
			    mine->filename.w);
			return (ARCHIVE_FATAL);
		}
#else
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Unexpedted operation in archive_write_open_filename");
		return (ARCHIVE_FATAL);
#endif
	}


	if (archive_write_get_bytes_in_last_block(a) < 0) {
		if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) ||
		    S_ISFIFO(st.st_mode))

			archive_write_set_bytes_in_last_block(a, 0);
		else

			archive_write_set_bytes_in_last_block(a, 1);
	}


	if (S_ISREG(st.st_mode))
		archive_write_set_skip_file(a, st.st_dev, st.st_ino);

	return (ARCHIVE_OK);
}
