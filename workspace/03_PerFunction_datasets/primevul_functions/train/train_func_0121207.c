int main(int argc, char **argv)
{
	int opt = 1, sar_options = 0;
	int day_offset = 0;
	int i, rc, p, q;
	char dfile[MAX_FILE_LEN];
	char *t, *v;


	get_kb_shift();

	dfile[0] = '\0';

#ifdef USE_NLS

	init_nls();
#endif

	tm_start.use = tm_end.use = FALSE;


	allocate_bitmaps(act);


	init_structures();


	while (opt < argc) {

		if (!strcmp(argv[opt], "-I")) {
			if (!sar_options) {
				usage(argv[0]);
			}
			if (parse_sar_I_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-P")) {
			if (parse_sa_P_opt(argv, &opt, &flags, act)) {
				usage(argv[0]);
			}
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

		else if (!strcmp(argv[opt], "-O")) {

			if (!argv[++opt] || sar_options) {
				usage(argv[0]);
			}
			for (t = strtok(argv[opt], ","); t; t = strtok(NULL, ",")) {
				if (!strcmp(t, K_SKIP_EMPTY)) {
					flags |= S_F_SVG_SKIP;
				}
				else if (!strcmp(t, K_AUTOSCALE)) {
					flags |= S_F_SVG_AUTOSCALE;
				}
				else if (!strcmp(t, K_ONEDAY)) {
					flags |= S_F_SVG_ONE_DAY;
				}
				else if (!strcmp(t, K_SHOWIDLE)) {
					flags |= S_F_SVG_SHOW_IDLE;
				}
				else if (!strcmp(t, K_SHOWINFO)) {
					flags |= S_F_SVG_SHOW_INFO;
				}
				else if (!strcmp(t, K_DEBUG)) {
					flags |= S_F_RAW_DEBUG_MODE;
				}
				else if (!strncmp(t, K_HEIGHT, strlen(K_HEIGHT))) {
					v = t + strlen(K_HEIGHT);
					if (!strlen(v) || (strspn(v, DIGITS) != strlen(v))) {
						usage(argv[0]);
					}
					canvas_height = atoi(v);
					flags |= S_F_SVG_HEIGHT;
				}
				else if (!strcmp(t, K_PACKED)) {
					flags |= S_F_SVG_PACKED;
				}
				else if (!strcmp(t, K_SHOWTOC)) {
					flags |= S_F_SVG_SHOW_TOC;
				}
				else {
					usage(argv[0]);
				}
			}
			opt++;
		}

		else if ((strlen(argv[opt]) > 1) &&
			 (strlen(argv[opt]) < 4) &&
			 !strncmp(argv[opt], "-", 1) &&
			 (strspn(argv[opt] + 1, DIGITS) == (strlen(argv[opt]) - 1))) {
			if (dfile[0] || day_offset) {

				usage(argv[0]);
			}
			day_offset = atoi(argv[opt++] + 1);
		}

		else if (!strcmp(argv[opt], "--")) {
			sar_options = 1;
			opt++;
		}

		else if (!strcmp(argv[opt], "-m")) {
			if (!argv[++opt] || !sar_options) {
				usage(argv[0]);
			}

			if (parse_sar_m_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if (!strcmp(argv[opt], "-n")) {
			if (!argv[++opt] || !sar_options) {
				usage(argv[0]);
			}

			if (parse_sar_n_opt(argv, &opt, act)) {
				usage(argv[0]);
			}
		}

		else if (!strncmp(argv[opt], "-", 1)) {

			if (sar_options) {
				if ((rc = parse_sar_opt(argv, &opt, act, &flags, C_SADF)) != 0) {
					if (rc == 1) {
						usage(argv[0]);
					}
					exit(1);
				}
			}
			else {

				for (i = 1; *(argv[opt] + i); i++) {

					switch (*(argv[opt] + i)) {

					case 'C':
						flags |= S_F_COMMENT;
						break;

					case 'c':
						if (format) {
							usage(argv[0]);
						}
						format = F_CONV_OUTPUT;
						break;

					case 'd':
						if (format) {
							usage(argv[0]);
						}
						format = F_DB_OUTPUT;
						break;

					case 'g':
						if (format) {
							usage(argv[0]);
						}
						format = F_SVG_OUTPUT;
						break;

					case 'h':
						flags |= S_F_HORIZONTALLY;
						break;

					case 'H':
						flags |= S_F_HDR_ONLY;
						break;

					case 'j':
						if (format) {
							usage(argv[0]);
						}
						format = F_JSON_OUTPUT;
						break;

					case 'p':
						if (format) {
							usage(argv[0]);
						}
						format = F_PPC_OUTPUT;
						break;

					case 'r':
						if (format) {
							usage(argv[0]);
						}
						format = F_RAW_OUTPUT;
						break;

					case 'T':
						flags |= S_F_LOCAL_TIME;
						break;

					case 't':
						flags |= S_F_TRUE_TIME;
						break;

					case 'U':
						flags |= S_F_SEC_EPOCH;
						break;

					case 'x':
						if (format) {
							usage(argv[0]);
						}
						format = F_XML_OUTPUT;
						break;

					case 'V':
						print_version();
						break;

					default:
						usage(argv[0]);
					}
				}
			}
			opt++;
		}


		else if (strspn(argv[opt], DIGITS) != strlen(argv[opt])) {
			if (dfile[0] || day_offset) {

				usage(argv[0]);
			}

			strncpy(dfile, argv[opt++], MAX_FILE_LEN);
			dfile[MAX_FILE_LEN - 1] = '\0';

			check_alt_sa_dir(dfile, 0, -1);
		}

		else if (interval < 0) {

			if (strspn(argv[opt], DIGITS) != strlen(argv[opt])) {
				usage(argv[0]);
			}
			interval = atol(argv[opt++]);
			if (interval <= 0) {
				usage(argv[0]);
			}
		}

		else {

			if (strspn(argv[opt], DIGITS) != strlen(argv[opt])) {
				usage(argv[0]);
			}
			if (count) {

				usage(argv[0]);
			}
			count = atol(argv[opt++]);
			if (count < 0) {
				usage(argv[0]);
			}
			else if (!count) {
				count = -1;
			}
		}
	}


	if (!dfile[0]) {
		set_default_file(dfile, day_offset, -1);
	}

	if (tm_start.use && tm_end.use && (tm_end.tm_hour < tm_start.tm_hour)) {
		tm_end.tm_hour += 24;
	}

	if (USE_PRETTY_OPTION(flags)) {
		dm_major = get_devmap_major();
	}


	if ((PRINT_LOCAL_TIME(flags) + PRINT_TRUE_TIME(flags) +
	    PRINT_SEC_EPOCH(flags)) > 1) {
		usage(argv[0]);
	}


	if (!count) {
		count = -1;
	}


	select_default_activity(act);


	check_format_options();

	if (interval < 0) {
		interval = 1;
	}

	if (format == F_CONV_OUTPUT) {

		convert_file(dfile, act);
	}
	else {

		read_stats_from_file(dfile);
	}


	free_bitmaps(act);

	return 0;
}
