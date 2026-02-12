void rw_curr_act_stats(int ifd, int *curr, long *cnt, int *eosaf,
		       unsigned int act_id, int *reset, struct file_activity *file_actlst,
		       struct tm *rectime, char *file,
		       struct file_magic *file_magic)
{
	int rtype;
	int next, reset_cd;


	seek_file_position(ifd, DO_RESTORE);

	if (DISPLAY_FIELD_LIST(fmt[f_position]->options)) {

		list_fields(act_id);
	}


	copy_structures(act, id_seq, record_hdr, !*curr, 2);

	*cnt  = count;
	reset_cd = 1;

	do {

		*eosaf = read_next_sample(ifd, IGNORE_RESTART | DONT_READ_CPU_NR,
					  *curr, file, &rtype, 0, file_magic,
					  file_actlst, rectime, UEOF_STOP);

		if (!*eosaf && (rtype != R_RESTART) && (rtype != R_COMMENT)) {
			next = generic_write_stats(*curr, tm_start.use, tm_end.use, *reset, cnt,
						   NULL, rectime, reset_cd, act_id);
			reset_cd = 0;

			if (next) {


				*curr ^= 1;
				if (*cnt > 0) {
					(*cnt)--;
				}
			}
			*reset = FALSE;
		}
	}
	while (*cnt && !*eosaf && (rtype != R_RESTART));

	*reset = TRUE;
}
