do_shell (char *filename)
{
	char cmdbuf[COMMAND_BUF];
	int rc;
	char *expanded;

	kill_line ();
	putchar('!');
	fflush (stdout);
	promptlen = 1;
	if (lastp)
		putsout(shell_line);
	else {
		ttyin (cmdbuf, sizeof(cmdbuf)-2, '!');
		expanded = 0;
		rc = expand (&expanded, cmdbuf);
		if (expanded) {
			if (strlen(expanded) < sizeof(shell_line))
				strcpy(shell_line, expanded);
			else
				rc = -1;
			free(expanded);
		}
		if (rc < 0) {
			putserr(_("  Overflow\n"));
			prompt (filename);
			return;
		} else if (rc > 0) {
			kill_line ();
			promptlen = printf("!%s", shell_line);
		}
	}
	fflush (stdout);
	putcerr('\n');
	promptlen = 0;
	shellp = 1;
	execute (filename, shell, shell, "-c", shell_line, 0);
}
