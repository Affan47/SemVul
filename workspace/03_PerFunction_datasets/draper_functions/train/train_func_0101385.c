do_stop(void)
{
	int			cnt;
	pgpid_t		pid;
	struct stat statbuf;

	pid = get_pgpid();

	if (pid == 0)
	{
		write_stderr(_("%s: PID file \"%s\" does not exist\n"), progname, pid_file);
		write_stderr(_("Is server running?\n"));
		exit(1);
	}
	else if (pid < 0)
	{
		pid = -pid;
		write_stderr(_("%s: cannot stop server; "
					   "single-user server is running (PID: %ld)\n"),
					 progname, pid);
		exit(1);
	}

	if (kill((pid_t) pid, sig) != 0)
	{
		write_stderr(_("%s: could not send stop signal (PID: %ld): %s\n"), progname, pid,
					 strerror(errno));
		exit(1);
	}

	if (!do_wait)
	{
		print_msg(_("server shutting down\n"));
		return;
	}
	else
	{


		if (shutdown_mode == SMART_MODE &&
			stat(backup_file, &statbuf) == 0 &&
			stat(recovery_file, &statbuf) != 0)
		{
			print_msg(_("WARNING: online backup mode is active\n"
						"Shutdown will not complete until pg_stop_backup() is called.\n\n"));
		}

		print_msg(_("waiting for server to shut down..."));

		for (cnt = 0; cnt < wait_seconds; cnt++)
		{
			if ((pid = get_pgpid()) != 0)
			{
				print_msg(".");
				pg_usleep(1000000);
			}
			else
				break;
		}

		if (pid != 0)
		{
			print_msg(_(" failed\n"));

			write_stderr(_("%s: server does not shut down\n"), progname);
			exit(1);
		}
		print_msg(_(" done\n"));

		print_msg(_("server stopped\n"));
	}
}
