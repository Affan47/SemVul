tdb_expand_file(struct tdb_context *tdb, tdb_off_t size, tdb_off_t addition)
{
	char buf[8192];

	if (tdb->read_only || tdb->traverse_read) {
		tdb->ecode = TDB_ERR_RDONLY;
		return -1;
	}

	if (ftruncate(tdb->fd, size+addition) == -1) {
		char b = 0;
		ssize_t written = pwrite(tdb->fd,  &b, 1, (size+addition) - 1);
		if (written == 0) {

			written = pwrite(tdb->fd,  &b, 1, (size+addition) - 1);
		}
		if (written == 0) {

			errno = ENOSPC;
		}
		if (written != 1) {
			TDB_LOG((tdb, TDB_DEBUG_FATAL, "expand_file to %d failed (%s)\n",
				 size+addition, strerror(errno)));
			return -1;
		}
	}


	memset(buf, TDB_PAD_BYTE, sizeof(buf));
	while (addition) {
		size_t n = addition>sizeof(buf)?sizeof(buf):addition;
		ssize_t written = pwrite(tdb->fd, buf, n, size);
		if (written == 0) {

			written = pwrite(tdb->fd, buf, n, size);
		}
		if (written == 0) {

			TDB_LOG((tdb, TDB_DEBUG_FATAL, "expand_file write "
				"returned 0 twice: giving up!\n"));
			errno = ENOSPC;
			return -1;
		} else if (written == -1) {
			TDB_LOG((tdb, TDB_DEBUG_FATAL, "expand_file write of "
				 "%d bytes failed (%s)\n", (int)n,
				 strerror(errno)));
			return -1;
		} else if (written != n) {
			TDB_LOG((tdb, TDB_DEBUG_WARNING, "expand_file: wrote "
				 "only %d of %d bytes - retrying\n", (int)written,
				 (int)n));
		}
		addition -= written;
		size += written;
	}
	return 0;
}
