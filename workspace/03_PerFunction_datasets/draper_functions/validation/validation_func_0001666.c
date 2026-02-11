confirm(char *cmd, char *file)
{
	char buf[BUFSIZ];

	if (!interactive)
		return (1);
	printf("%s %s? ", cmd, file);
	fflush(stdout);
	if (fgets(buf, sizeof buf, stdin) == NULL)
		return (0);
	return (*buf == 'y' || *buf == 'Y');
}
