void handle_curr_act_stats(int ifd, off_t fpos, int *curr, long *cnt, int *eosaf,
			   int rows, unsigned int act_id, int *reset,
			   struct file_activity *file_actlst, char *file,
			   struct file_magic *file_magic, void *rec_hdr_tmp,
			   int endian_mismatch, int arch_64, size_t b_size)
{
	int p, reset_cd;
	unsigned long lines = 0;
	unsigned char rtype;
	int davg = 0, next, inc = 0;

	if (lseek(ifd, fpos, SEEK_SET) < fpos) {
		perror("lseek");
		exit(2);
	}


	copy_structures(act, id_seq, record_hdr, !*curr, 2);

	*cnt  = count;


	p = get_activity_position(act, act_id, EXIT_IF_NOT_FOUND);
	if (act[p]->bitmap) {
		inc = count_bits(act[p]->bitmap->b_array,
				 BITMAP_SIZE(act[p]->bitmap->b_size));
	}
	reset_cd = 1;

	do {


		*eosaf = read_record_hdr(ifd, rec_hdr_tmp, &record_hdr[*curr],
					 &file_hdr, arch_64, endian_mismatch, UEOF_STOP, b_size);
		rtype = record_hdr[*curr].record_type;

		if (!*eosaf && (rtype != R_RESTART) && (rtype != R_COMMENT)) {

			read_file_stat_bunch(act, *curr, ifd, file_hdr.sa_act_nr, file_actlst,
					     endian_mismatch, arch_64, file, file_magic, UEOF_STOP);
		}

		if ((lines >= rows) || !lines) {
			lines = 0;
			dish = 1;
		}
		else
			dish = 0;

		if (!*eosaf && (rtype != R_RESTART)) {

			if (rtype == R_COMMENT) {

				next = print_special_record(&record_hdr[*curr], flags + S_F_LOCAL_TIME,
							    &tm_start, &tm_end, R_COMMENT, ifd,
							    &rectime, file, 0,
							    file_magic, &file_hdr, act, &sar_fmt,
							    endian_mismatch, arch_64);
				if (next && lines) {


					lines++;
				}
				continue;
			}


			next = write_stats(*curr, USE_SA_FILE, cnt, tm_start.use, tm_end.use,
					   *reset, act_id, reset_cd);
			reset_cd = 0;
			if (next && (*cnt > 0)) {
				(*cnt)--;
			}

			if (next) {
				davg++;
				*curr ^= 1;

				if (inc) {
					lines += inc;
				}
				else {
					lines += act[p]->nr[*curr];
				}
			}
			*reset = FALSE;
		}
	}
	while (*cnt && !*eosaf && (rtype != R_RESTART));


	if (davg) {
		write_stats_avg(!*curr, USE_SA_FILE, act_id);
	}

	*reset = TRUE;
}
