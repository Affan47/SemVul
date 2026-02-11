eb_cli_help(const char *cmd)
{
	unsigned int i = 0;

	printf("Usage: %s [OPTION]...\n", cmd);
	printf("An integrated instant messenger program.\n");
	printf("Supports AIM, ICQ, MSN, Yahoo!, Jabber, and IRC.\n\n");

#if defined (HAVE_GETOPT) || defined (HAVE_GETOPT_LONG)

	for (i = 0; options[i].help != NULL; i++) {
#ifdef HAVE_GETOPT_LONG

		printf("  %c%c  %2s%15s  %s\n",
			(options[i].s_opt == ' ' ? ' ' : '-'),
			options[i].s_opt,
			(options[i].l_opt == NULL ? "  " : "--"),
			options[i].l_opt, options[i].help);

#else


		printf("  %c%c  %s\n",
			(options[i].s_opt == ' ' ? ' ' : '-'),
			options[i].s_opt, options[i].help);

#endif
	}

#endif
}
