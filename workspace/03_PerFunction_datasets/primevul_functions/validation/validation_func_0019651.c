static int flush_grep(struct grep_opt *opt,
		      int argc, int arg0, const char **argv, int *kept)
{
	int status;
	int count = argc - arg0;
	const char *kept_0 = NULL;

	if (count <= 2) {


		if (kept)
			die("insanely many options to grep");


		if (count == 1 &&
		    !opt->name_only &&
		    !opt->unmatch_name_only &&
		    !opt->count) {
			argv[argc++] = "/dev/null";
			argv[argc] = NULL;
		}
	}

	else if (kept) {


		*kept = 2;
		kept_0 = argv[argc-2];
		argv[argc-2] = NULL;
		argc -= 2;
	}

	status = exec_grep(argc, argv);

	if (kept_0) {


		argv[arg0++] = kept_0;
		argv[arg0] = argv[argc+1];
	}
	return status;
}
