handle_upload_common(int is_append, int is_unique)
{
	struct stat statbuf;
	char *tempname;
	off_t bytes_transferred;
	off_t offset;
	int local_file_fd;
	int remote_fd;

	offset = G.restart_pos;
	G.restart_pos = 0;

	if (!port_or_pasv_was_seen())
		return;

	tempname = NULL;
	local_file_fd = -1;
	if (is_unique) {
		tempname = xstrdup(" FILE: uniq.XXXXXX");
		local_file_fd = mkstemp(tempname + 7);
	} else if (G.ftp_arg) {
		int flags = O_WRONLY | O_CREAT | O_TRUNC;
		if (is_append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		if (offset)
			flags = O_WRONLY | O_CREAT;
		local_file_fd = open(G.ftp_arg, flags, 0666);
	}

	if (local_file_fd < 0
	 || fstat(local_file_fd, &statbuf) != 0
	 || !S_ISREG(statbuf.st_mode)
	) {
		WRITE_ERR(FTP_UPLOADFAIL);
		if (local_file_fd >= 0)
			goto close_local_and_bail;
		return;
	}
	G.local_file_fd = local_file_fd;

	if (offset)
		xlseek(local_file_fd, offset, SEEK_SET);

	remote_fd = get_remote_transfer_fd(tempname ? tempname : " Ok to send data");
	free(tempname);

	if (remote_fd < 0)
		goto close_local_and_bail;

	bytes_transferred = bb_copyfd_eof(remote_fd, local_file_fd);
	close(remote_fd);
	if (bytes_transferred < 0)
		WRITE_ERR(FTP_BADSENDFILE);
	else
		WRITE_OK(FTP_TRANSFEROK);

 close_local_and_bail:
	close(local_file_fd);
	G.local_file_fd = 0;
}
