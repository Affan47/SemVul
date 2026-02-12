postmaster_forkexec(int argc, char *argv[])
{
	Port		port;


	memset(&port, 0, sizeof(port));
	return internal_forkexec(argc, argv, &port);
}
