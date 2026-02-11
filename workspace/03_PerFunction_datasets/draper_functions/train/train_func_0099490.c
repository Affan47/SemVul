pfs_listen( int fd, int backlog )
{
	BEGIN
	debug(D_LIBCALL,"listen %d %d",fd,backlog);
	result = ::listen(pfs_current->table->get_real_fd(fd),backlog);
	END
}
