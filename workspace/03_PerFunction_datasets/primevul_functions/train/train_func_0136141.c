int read_next_sample(int ifd, int action, int curr, char *file, int *rtype, int tab,
		     struct file_magic *file_magic, struct file_activity *file_actlst,
		     struct tm *rectime, int oneof)
{
	int rc;
	char rec_hdr_tmp[MAX_RECORD_HEADER_SIZE];


	if ((rc = read_record_hdr(ifd, rec_hdr_tmp, &record_hdr[curr], &file_hdr,
			    arch_64, endian_mismatch, oneof, sizeof(rec_hdr_tmp))) != 0)

		return rc;

	*rtype = record_hdr[curr].record_type;

	if (*rtype == R_COMMENT) {
		if (action & IGNORE_COMMENT) {

			if (lseek(ifd, MAX_COMMENT_LEN, SEEK_CUR) < MAX_COMMENT_LEN) {
				if (oneof == UEOF_CONT)
					return 2;
				close(ifd);
				exit(2);
			}


			if (record_hdr[curr].extra_next && (skip_extra_struct(ifd, endian_mismatch, arch_64) < 0))
				return 2;

			if (action & SET_TIMESTAMPS) {
				sa_get_record_timestamp_struct(flags, &record_hdr[curr],
							       rectime);
			}
		}
		else {

			print_special_record(&record_hdr[curr], flags, &tm_start, &tm_end,
					     *rtype, ifd, rectime, file, tab,
					     file_magic, &file_hdr, act, fmt[f_position],
					     endian_mismatch, arch_64);
		}
	}
	else if (*rtype == R_RESTART) {
		if (action & IGNORE_RESTART) {


			if (!(action & DONT_READ_CPU_NR)) {
				file_hdr.sa_cpu_nr = read_nr_value(ifd, file, file_magic,
								   endian_mismatch, arch_64, TRUE);


				if (record_hdr[curr].extra_next && (skip_extra_struct(ifd, endian_mismatch, arch_64) < 0))
					return 2;
			}
			if (action & SET_TIMESTAMPS) {
				sa_get_record_timestamp_struct(flags, &record_hdr[curr], rectime);
			}
		}
		else {

			print_special_record(&record_hdr[curr], flags, &tm_start, &tm_end,
					     *rtype, ifd, rectime, file, tab,
					     file_magic, &file_hdr, act, fmt[f_position],
					     endian_mismatch, arch_64);
		}
	}
	else {


		if (read_file_stat_bunch(act, curr, ifd, file_hdr.sa_act_nr, file_actlst,
					 endian_mismatch, arch_64, file, file_magic, oneof) > 0)
			return 2;
		sa_get_record_timestamp_struct(flags, &record_hdr[curr], rectime);
	}

	return 0;
}
