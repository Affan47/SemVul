Lock_AF_UNIX(const char *unixSocketDir, const char *unixSocketPath)
{

	if (unixSocketPath[0] == '@')
		return STATUS_OK;


	CreateSocketLockFile(unixSocketPath, true, unixSocketDir);


	(void) unlink(unixSocketPath);


	sock_paths = lappend(sock_paths, pstrdup(unixSocketPath));

	return STATUS_OK;
}
