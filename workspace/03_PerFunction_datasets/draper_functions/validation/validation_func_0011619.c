do_promote(void)
{
	FILE	   *prmfile;
	pgpid_t		pid;
	struct stat statbuf;

	pid = get_pgpid(false);

	if (pid == 0)
	{
		write_stderr(_("%s: PID file \"%s\" does not exist\n"), progname, pid_file);
		write_stderr(_("Is server running?\n"));
		exit(1);
	}
	else if (pid < 0)
	{
		pid = -pid;
		write_stderr(_("%s: cannot promote server; "
					   "single-user server is running (PID: %ld)\n"),
					 progname, pid);
		exit(1);
	}


	if (stat(recovery_file, &statbuf) != 0)
	{
		write_stderr(_("%s: cannot promote server; "
					   "server is not in standby mode\n"),
					 progname);
		exit(1);
	}


	snprintf(promote_file, MAXPGPATH, "%s/promote", pg_data);

	if ((prmfile = fopen(promote_file, "w")) == NULL)
	{
		write_stderr(_("%s: could not create promote signal file \"%s\": %s\n"),
					 progname, promote_file, strerror(errno));
		exit(1);
	}
	if (fclose(prmfile))
	{
		write_stderr(_("%s: could not write promote signal file \"%s\": %s\n"),
					 progname, promote_file, strerror(errno));
		exit(1);
	}

	sig = SIGUSR1;
	if (kill((pid_t) pid, sig) != 0)
	{
		write_stderr(_("%s: could not send promote signal (PID: %ld): %s\n"),
					 progname, pid, strerror(errno));
		if (unlink(promote_file) != 0)
			write_stderr(_("%s: could not remove promote signal file \"%s\": %s\n"),
						 progname, promote_file, strerror(errno));
		exit(1);
	}

	print_msg(_("server promoting\n"));
}
