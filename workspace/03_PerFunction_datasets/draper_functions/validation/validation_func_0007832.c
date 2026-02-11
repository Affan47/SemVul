arg_parse(int argc, char *argv[])
{
	int sel = 0;
	ps_argc = argc;
	ps_argv = argv;
	thisarg = 0;

	while (++thisarg < ps_argc) {
		flagptr = ps_argv[thisarg];
		switch (*flagptr) {
		case '0'...'9':
			show_args = 1;
			parse_pid(flagptr);
			break;
		case '-':
			flagptr++;
			parse_sysv_option();
			break;
		default:
			show_args = 1;
			parse_bsd_option();
			break;
		}
	}

	if (want_one_pid)
		sel++;
	if (want_one_command)
		sel++;
	if (select_notty || select_all)
		sel++;
	if (sel > 1 || select_notty > 1 || select_all > 1 || bsd_c_option > 1
	    || old_h_option > 1)
		usage();
	if (bsd_c_option)
		show_args = 0;
}
