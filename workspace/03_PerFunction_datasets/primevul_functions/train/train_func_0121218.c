void read_stats(void)
{
	int curr = 1;
	unsigned long lines;
	unsigned int rows;
	int dis_hdr = 0;


	setbuf(stdout, NULL);


	read_header_data();

	if (!get_activity_nr(act, AO_SELECTED, COUNT_ACTIVITIES)) {

		print_collect_error();
	}


	dis_hdr = check_line_hdr();

	lines = rows = get_win_height();


	allocate_structures(act);


	print_report_hdr(flags, &rectime, &file_hdr);


	read_sadc_stat_bunch(0);

	if (!interval) {

		write_stats_startup(0);
	}


	copy_structures(act, id_seq, record_hdr, 2, 0);


	memset(&int_act, 0, sizeof(int_act));
	int_act.sa_handler = int_handler;
	int_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &int_act, NULL);


	do {


		read_sadc_stat_bunch(curr);
		if (sigint_caught) {


			curr ^= 1;
			break;
		}


		if (!dis_hdr) {
			dis = lines / rows;
			if (dis) {
				lines %= rows;
			}
			lines++;
		}
		write_stats(curr, USE_SADC, &count, NO_TM_START, tm_end.use,
			    NO_RESET, ALL_ACTIVITIES, TRUE);

		if (record_hdr[curr].record_type == R_LAST_STATS) {

			read_header_data();
			allocate_structures(act);
		}

		if (count > 0) {
			count--;
		}
		if (count) {
			curr ^= 1;
		}
	}
	while (count);


	dis = dis_hdr;
	if (avg_count) {
		write_stats_avg(curr, USE_SADC, ALL_ACTIVITIES);
	}
}
