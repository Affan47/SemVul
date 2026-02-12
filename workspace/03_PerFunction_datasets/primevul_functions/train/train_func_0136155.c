void logic2_display_loop(int ifd, char *file, struct file_activity *file_actlst,
			 struct file_magic *file_magic, struct tm *rectime, void *dparm)
{
	int i, p;
	int curr = 1, rtype;
	int eosaf = TRUE, reset = FALSE;
	long cnt = 1;


	do {


		do {
			if (read_next_sample(ifd, IGNORE_NOTHING, 0,
					     file, &rtype, 0, file_magic, file_actlst,
					     rectime, UEOF_STOP))

				return;
		}
		while ((rtype == R_RESTART) || (rtype == R_COMMENT) ||
		       (tm_start.use && (datecmp(rectime, &tm_start, FALSE) < 0)) ||
		       (tm_end.use && (datecmp(rectime, &tm_end, FALSE) >= 0)));


		copy_structures(act, id_seq, record_hdr, 2, 0);


		reset = TRUE;


		seek_file_position(ifd, DO_SAVE);


		if (DISPLAY_HORIZONTALLY(flags)) {


			rw_curr_act_stats(ifd, &curr, &cnt, &eosaf,
					  ALL_ACTIVITIES, &reset, file_actlst,
					  rectime, file, file_magic);
		}
		else {

			for (i = 0; i < NR_ACT; i++) {

				if (!id_seq[i])
					continue;

				p = get_activity_position(act, id_seq[i], EXIT_IF_NOT_FOUND);
				if (!IS_SELECTED(act[p]->options))
					continue;

				if (!HAS_MULTIPLE_OUTPUTS(act[p]->options)) {
					rw_curr_act_stats(ifd, &curr, &cnt, &eosaf,
							  act[p]->id, &reset, file_actlst,
							  rectime, file, file_magic);
				}
				else {
					unsigned int optf, msk;

					optf = act[p]->opt_flags;

					for (msk = 1; msk < 0x100; msk <<= 1) {
						if ((act[p]->opt_flags & 0xff) & msk) {
							act[p]->opt_flags &= (0xffffff00 + msk);

							rw_curr_act_stats(ifd, &curr, &cnt, &eosaf,
									  act[p]->id, &reset, file_actlst,
									  rectime, file,
									  file_magic);
							act[p]->opt_flags = optf;
						}
					}
				}
			}
		}

		if (!cnt) {

			do {
				eosaf = read_next_sample(ifd, IGNORE_RESTART | DONT_READ_CPU_NR,
							 curr, file, &rtype, 0, file_magic,
							 file_actlst, rectime, UEOF_STOP);
			}
			while (!eosaf && (rtype != R_RESTART));
		}


		if (!eosaf && (record_hdr[curr].record_type == R_RESTART)) {
			print_special_record(&record_hdr[curr], flags, &tm_start, &tm_end,
					     R_RESTART, ifd, rectime, file, 0,
					     file_magic, &file_hdr, act, fmt[f_position],
					     endian_mismatch, arch_64);
		}
	}
	while (!eosaf);
}
