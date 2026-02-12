static void server_exit(void)
{
	int rv;

	if (lock_fd >= 0) {


		rv = ftruncate(lock_fd, 0);
		(void)rv;
		unlink_lockfile(lock_fd);
	}
	log_info("exiting");
}
