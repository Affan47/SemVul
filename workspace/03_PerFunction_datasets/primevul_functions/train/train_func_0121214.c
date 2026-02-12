int print_special_record(struct record_header *record_hdr, unsigned int l_flags,
			 struct tstamp *tm_start, struct tstamp *tm_end, int rtype, int ifd,
			 struct tm *rectime, struct tm *loctime, char *file, int tab,
			 struct file_magic *file_magic, struct file_header *file_hdr,
			 struct activity *act[], struct report_format *ofmt,
			 int endian_mismatch, int arch_64)
{
	char cur_date[TIMESTAMP_LEN], cur_time[TIMESTAMP_LEN];
	int dp = 1;
	int p;


	if (sa_get_record_timestamp_struct(l_flags, record_hdr, rectime, loctime))
		return 0;


	if (!loctime) {
		loctime = rectime;
	}


	if ((tm_start->use && (datecmp(loctime, tm_start) < 0)) ||
	    (tm_end->use && (datecmp(loctime, tm_end) > 0))) {

		dp = 0;
	}
	else {

		set_record_timestamp_string(l_flags, record_hdr,
					    cur_date, cur_time, TIMESTAMP_LEN, rectime);
	}

	if (rtype == R_RESTART) {

		file_hdr->sa_cpu_nr = read_nr_value(ifd, file, file_magic,
						    endian_mismatch, arch_64, TRUE);


		for (p = 0; p < NR_ACT; p++) {
			if (HAS_PERSISTENT_VALUES(act[p]->options)) {
				act[p]->nr_ini = file_hdr->sa_cpu_nr;
				if (act[p]->nr_ini > act[p]->nr_allocated) {
					reallocate_all_buffers(act[p], act[p]->nr_ini);
				}
			}
		}

		if (!dp)
			return 0;

		if (*ofmt->f_restart) {
			(*ofmt->f_restart)(&tab, F_MAIN, cur_date, cur_time,
					   !PRINT_LOCAL_TIME(l_flags) &&
					   !PRINT_TRUE_TIME(l_flags), file_hdr);
		}
	}
	else if (rtype == R_COMMENT) {
		char file_comment[MAX_COMMENT_LEN];


		replace_nonprintable_char(ifd, file_comment);

		if (!dp || !DISPLAY_COMMENT(l_flags))
			return 0;

		if (*ofmt->f_comment) {
			(*ofmt->f_comment)(&tab, F_MAIN, cur_date, cur_time,
					   !PRINT_LOCAL_TIME(l_flags) &&
					   !PRINT_TRUE_TIME(l_flags), file_comment,
					   file_hdr);
		}
	}

	return 1;
}
