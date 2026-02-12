int write_stats(int curr, int read_from_file, long *cnt, int use_tm_start,
		int use_tm_end, int reset, unsigned int act_id, int reset_cd)
{
	int i;
	unsigned long long itv;
	static int cross_day = 0;

	if (reset_cd) {


		cross_day = 0;
	}


	if (read_from_file) {
		if (!next_slice(record_hdr[2].uptime_cs, record_hdr[curr].uptime_cs,
				reset, interval))

			return 0;
	}


	if (sa_get_record_timestamp_struct(flags + S_F_LOCAL_TIME, &record_hdr[!curr],
					   &rectime, NULL))
		return 0;
	set_record_timestamp_string(flags, &record_hdr[!curr],
				    NULL, timestamp[!curr], TIMESTAMP_LEN, &rectime);


	if (sa_get_record_timestamp_struct(flags + S_F_LOCAL_TIME, &record_hdr[curr],
					   &rectime, NULL))
		return 0;
	set_record_timestamp_string(flags, &record_hdr[curr],
				    NULL, timestamp[curr], TIMESTAMP_LEN, &rectime);


	if (use_tm_start && record_hdr[!curr].ust_time &&
	    (record_hdr[curr].ust_time > record_hdr[!curr].ust_time) &&
	    (record_hdr[curr].hour < record_hdr[!curr].hour)) {
		cross_day = 1;
	}

	if (cross_day) {


		rectime.tm_hour += 24;
	}


	if (use_tm_start && (datecmp(&rectime, &tm_start) < 0))

		return 0;


	get_itv_value(&record_hdr[curr], &record_hdr[!curr], &itv);


	if (use_tm_end && (datecmp(&rectime, &tm_end) > 0)) {

		*cnt = 0;
		return 0;
	}

	avg_count++;


	TEST_STDOUT(STDOUT_FILENO);

	for (i = 0; i < NR_ACT; i++) {

		if ((act_id != ALL_ACTIVITIES) && (act[i]->id != act_id))
			continue;

		if (IS_SELECTED(act[i]->options) && (act[i]->nr[curr] > 0)) {

			(*act[i]->f_print)(act[i], !curr, curr, itv);
		}
	}

	return 1;
}
