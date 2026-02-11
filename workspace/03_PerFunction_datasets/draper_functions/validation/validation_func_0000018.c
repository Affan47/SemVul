log_init(char *program_name, int size)
{
	logdbg(stderr,"enter log_init\n");
	openlog(program_name, 0, LOG_DAEMON);

	if (logarea_init(size))
		return 1;

	return 0;
}
