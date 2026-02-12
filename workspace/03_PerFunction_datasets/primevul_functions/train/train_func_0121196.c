int main(int argc, char **argv)
{
	int i, rc, opt = 1, args_idx = 1, p, q;
	int fd[2];
	int day_offset = 0;
	char from_file[MAX_FILE_LEN], to_file[MAX_FILE_LEN];
	char ltemp[1024];


	get_kb_shift();

	from_file[0] = to_file[0] = '\0';

#ifdef USE_NLS

	init_nls();
#endif


	init_colors();

	tm_start.use = tm_end.use = FALSE;


	allocate_bitmaps(act);

	init_structures();


	while (opt < argc) {

		if (!strcmp(argv[opt], "--sadc")) {

			which_sadc();
		}

		else if (!strncmp(argv[opt], "--dev=", 6)) {

			p = get_activity_position(act, A_DISK, EXIT_IF_NOT_FOUND);
			parse_sa_devices(argv[opt], act[p], MAX_DEV_LEN, &opt, 6);
		}

		else if (!strncmp(argv[opt], "--fs=", 5)) {

			p = get_activity_position(act, A_FS, EXIT_IF_NOT_FOUND);
			parse_sa_devices(argv[opt], act[p], MAX_FS_LEN, &opt, 5);
		}

		else if (!strncmp(argv[opt], "--iface=", 8)) {

			p = get_activity_position(act, A_NET_DEV, EXIT_IF_NOT_FOUND);
			parse_sa_devices(argv[opt], act[p], MAX_IFACE_LEN, &opt, 8);
			q = get_activity_position(act, A_NET_EDEV, EXIT_IF_NOT_FOUND);
			act[q]->item_list = act[p]->item_list;
			act[q]->item_list_sz = act[p]->item_list_sz;
			act[q]->options |= AO_LIST_ON_CMDLINE;
		}

		else if (!strcmp(argv[opt], "--help")) {

			display_help(argv[0]);
		}

		else if (!strcmp(argv[opt], "--human")) {

			flags |= S_F_UNIT;
			opt++;
		}

		else if (!strncmp(argv[opt], "--dec=", 6) && (strlen(argv[opt]) == 7)) {

			dplaces_nr = atoi(argv[opt] + 6);
			if ((dplaces_nr < 0) || (dplaces_nr > 2)) {
				usage(argv[0]);
			}
			opt++;
		}

		else if (!strcmp(argv[opt], "-I")) {

			if (parse_sar_I_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-D")) {

			flags |= S_F_SA_YYYYMMDD;
			opt++;
		}

		else if (!strcmp(argv[opt], "-P")) {

			if (parse_sa_P_opt(argv, &opt, &flags, act)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-o")) {
			if (to_file[0]) {

				usage(argv[0]);
			}

			if ((argv[++opt]) && strncmp(argv[opt], "-", 1) &&
			    (strspn(argv[opt], DIGITS) != strlen(argv[opt]))) {
				strncpy(to_file, argv[opt++], MAX_FILE_LEN);
				to_file[MAX_FILE_LEN - 1] = '\0';
			}
			else {
				strcpy(to_file, "-");
			}
		}

		else if (!strcmp(argv[opt], "-f")) {
			if (from_file[0] || day_offset) {

				usage(argv[0]);
			}

			if ((argv[++opt]) && strncmp(argv[opt], "-", 1) &&
			    (strspn(argv[opt], DIGITS) != strlen(argv[opt]))) {
				strncpy(from_file, argv[opt++], MAX_FILE_LEN);
				from_file[MAX_FILE_LEN - 1] = '\0';

				check_alt_sa_dir(from_file, day_offset, -1);
			}
			else {
				set_default_file(from_file, day_offset, -1);
			}
		}

		else if (!strcmp(argv[opt], "-s")) {

			if (parse_timestamp(argv, &opt, &tm_start, DEF_TMSTART)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-e")) {

			if (parse_timestamp(argv, &opt, &tm_end, DEF_TMEND)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-i")) {
			if (!argv[++opt] || (strspn(argv[opt], DIGITS) != strlen(argv[opt]))) {
				usage(argv[0]);
			}
			interval = atol(argv[opt++]);
			if (interval < 1) {
				usage(argv[0]);
			}
			flags |= S_F_INTERVAL_SET;
		}

		else if (!strcmp(argv[opt], "-m")) {
			if (!argv[++opt]) {
				usage(argv[0]);
			}

			if (parse_sar_m_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-n")) {
			if (!argv[++opt]) {
				usage(argv[0]);
			}

			if (parse_sar_n_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if ((strlen(argv[opt]) > 1) &&
			 (strlen(argv[opt]) < 4) &&
			 !strncmp(argv[opt], "-", 1) &&
			 (strspn(argv[opt] + 1, DIGITS) == (strlen(argv[opt]) - 1))) {
			if (from_file[0] || day_offset) {

				usage(argv[0]);
			}
			day_offset = atoi(argv[opt++] + 1);
		}

		else if (!strncmp(argv[opt], "-", 1)) {

			if ((rc = parse_sar_opt(argv, &opt, act, &flags, C_SAR)) != 0) {
				if (rc == 1) {
					usage(argv[0]);
				}
				exit(1);
			}
			opt++;
		}

		else if (interval < 0) {

			if (strspn(argv[opt], DIGITS) != strlen(argv[opt])) {
				usage(argv[0]);
			}
			interval = atol(argv[opt++]);
			if (interval < 0) {
				usage(argv[0]);
			}
		}

		else {

			if ((strspn(argv[opt], DIGITS) != strlen(argv[opt])) ||
			    !interval) {
				usage(argv[0]);
			}
			if (count) {

				usage(argv[0]);
			}
			count = atol(argv[opt++]);
			if (count < 1) {
				usage(argv[0]);
			}
		}
	}


	if ((argc == 1) ||
	    ((interval < 0) && !from_file[0] && !to_file[0])) {
		set_default_file(from_file, day_offset, -1);
	}

	if (tm_start.use && tm_end.use && (tm_end.tm_hour < tm_start.tm_hour)) {
		tm_end.tm_hour += 24;
	}


	if (from_file[0] && to_file[0]) {
		fprintf(stderr, _("-f and -o options are mutually exclusive\n"));
		exit(1);
	}

	if ((tm_start.use || INTERVAL_SET(flags)) && !from_file[0]) {
		fprintf(stderr,
			_("Not reading from a system activity file (use -f option)\n"));
		exit(1);
	}

	if (!interval && (from_file[0] || to_file[0])) {
		usage(argv[0]);
	}


	if (to_file[0] && day_offset) {
		usage(argv[0]);
	}

	if (USE_PRETTY_OPTION(flags)) {
		dm_major = get_devmap_major();
	}

	if (!count) {


		count = -1;
	}


	select_default_activity(act);


	if (!is_iso_time_fmt())
		flags |= S_F_PREFD_TIME_OUTPUT;


	if (from_file[0]) {
		if (interval < 0) {
			interval = 1;
		}


		read_stats_from_file(from_file);


		free_bitmaps(act);
		free_structures(act);

		return 0;
	}


	if (pipe(fd) == -1) {
		perror("pipe");
		exit(4);
	}

	switch (fork()) {

	case -1:
		perror("fork");
		exit(4);
		break;

	case 0:
		if (dup2(fd[1], STDOUT_FILENO) < 0) {
			perror("dup2");
			exit(4);
		}
		CLOSE_ALL(fd);


		salloc(0, SADC);


		if (interval < 0) {
			usage(argv[0]);
		}
		else if (!interval) {
			strcpy(ltemp, "1");


			salloc(args_idx++, ltemp);
		}
		else {
			sprintf(ltemp, "%ld", interval);
		}
		salloc(args_idx++, ltemp);


		if (count >= 0) {
			sprintf(ltemp, "%ld", count + 1);
			salloc(args_idx++, ltemp);
		}


		salloc(args_idx++, "-Z");


		if (to_file[0]) {

			if (USE_SA_YYYYMMDD(flags)) {
				salloc(args_idx++, "-D");
			}

			salloc(args_idx++, "-S");
			salloc(args_idx++, K_XALL);

			salloc(args_idx++, to_file);
		}
		else {


			salloc(args_idx++, "-S");
			strcpy(ltemp, K_A_NULL);
			for (i = 0; i < NR_ACT; i++) {
				if (IS_SELECTED(act[i]->options)) {
					strcat(ltemp, ",");
					strcat(ltemp, act[i]->name);
				}
			}
			salloc(args_idx++, ltemp);
		}


		args[args_idx] = NULL;


#ifdef DEBUG
		fprintf(stderr, "%s: 1.sadc: %s\n", __FUNCTION__, SADC_PATH);
#endif

		execv(SADC_PATH, args);
#ifdef DEBUG
		fprintf(stderr, "%s: 2.sadc: %s\n", __FUNCTION__, SADC);
#endif
		execvp(SADC, args);


		fprintf(stderr, _("Cannot find the data collector (%s)\n"), SADC);
		perror("exec");
		exit(4);
		break;

	default:
		if (dup2(fd[0], STDIN_FILENO) < 0) {
			perror("dup2");
			exit(4);
		}
		CLOSE_ALL(fd);


		read_stats();

		break;
	}


	free_bitmaps(act);
	free_structures(act);

	return 0;
}
