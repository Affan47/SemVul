stepd_pid_in_container(int fd, pid_t pid)
{
	int req = REQUEST_PID_IN_CONTAINER;
	bool rc;

	safe_write(fd, &req, sizeof(int));
	safe_write(fd, &pid, sizeof(pid_t));


	safe_read(fd, &rc, sizeof(bool));

	debug("Leaving stepd_pid_in_container");
	return rc;
rwfail:
	return false;
}
