download_tmpfile(char *outfile)
{
	int fd;
	char *cp, path[MAXPATHLEN];

	if (outfile == NULL)
	{
		cp = getenv("TMPDIR");
		if (cp == NULL)
			cp = "/tmp";

		snprintf(path, sizeof(path), "%s/download-XXXXXX", cp);
		fd = mkstemp(path);
		if (fd == -1)
		{
			fprintf(stderr, "  ! cannot open temp file: "
				"mkstemp(\"%s\"): %s\n",
				path, strerror(errno));
			return -1;
		}
		unlink(path);
	}
	else
	{
		fd = open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666);
		if (fd == -1)
		{
			fprintf(stderr, "  ! cannot open file: "
				"open(\"%s\"): %s\n",
				outfile, strerror(errno));
			return -1;
		}
	}

	return fd;
}
