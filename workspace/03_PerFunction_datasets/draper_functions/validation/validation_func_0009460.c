rw_sa_stat_loop(long count, struct tm *rectime, int stdfd, int ofd,
		     char ofile[])
{
	int do_sa_rotat = 0;
	unsigned int save_flags;
	char new_ofile[MAX_FILE_LEN];

	new_ofile[0] = '\0';


	memset(&int_act, 0, sizeof(int_act));
	int_act.sa_handler = (void *) int_handler;
	sigaction(SIGINT, &int_act, NULL);


	do {


		reset_stats();


		record_hdr.ust_time = get_time(rectime, 0);
		record_hdr.hour     = rectime->tm_hour;
		record_hdr.minute   = rectime->tm_min;
		record_hdr.second   = rectime->tm_sec;


		if (do_sa_rotat) {
			record_hdr.record_type = R_LAST_STATS;
		}
		else {
			record_hdr.record_type = R_STATS;
		}


		read_stats();

		if (stdfd >= 0) {
			save_flags = flags;
			flags &= ~S_F_LOCK_FILE;
			write_stats(stdfd);
			flags = save_flags;
		}


		record_hdr.record_type = R_STATS;
		if (ofile[0]) {
			write_stats(ofd);
		}

		if (do_sa_rotat) {


			do_sa_rotat = FALSE;

			if (fdatasync(ofd) < 0) {

				perror("fdatasync");
				exit(4);
			}
			close(ofd);
			strcpy(ofile, new_ofile);


			sa_sys_init();


			open_ofile(&ofd, ofile);


			if (stdfd >= 0) {
				setup_file_hdr(stdfd);
			}


			write_stats(ofd);
		}


		fflush(stdout);

		if (count > 0) {
			count--;
		}

		if (count) {
			pause();
		}


		if (WANT_SA_ROTAT(flags)) {

			set_default_file(rectime, new_ofile, 0);

			if (strcmp(ofile, new_ofile)) {
				do_sa_rotat = TRUE;
			}
		}
	}
	while (count);


	CLOSE(stdfd);
	CLOSE(ofd);
}
