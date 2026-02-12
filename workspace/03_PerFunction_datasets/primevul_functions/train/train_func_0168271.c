static void NOINLINE retrieve_file_data(FILE *dfp)
{
#if ENABLE_FEATURE_WGET_STATUSBAR || ENABLE_FEATURE_WGET_TIMEOUT
# if ENABLE_FEATURE_WGET_TIMEOUT
	unsigned second_cnt = G.timeout_seconds;
# endif
	struct pollfd polldata;

	polldata.fd = fileno(dfp);
	polldata.events = POLLIN | POLLPRI;
#endif
	if (!(option_mask32 & WGET_OPT_QUIET)) {
		if (G.output_fd == 1)
			fprintf(stderr, "writing to stdout\n");
		else
			fprintf(stderr, "saving to '%s'\n", G.fname_out);
	}
	progress_meter(PROGRESS_START);

	if (G.chunked)
		goto get_clen;


	while (1) {

#if ENABLE_FEATURE_WGET_STATUSBAR || ENABLE_FEATURE_WGET_TIMEOUT


		ndelay_on(polldata.fd);
#endif
		while (1) {
			int n;
			unsigned rdsz;

#if ENABLE_FEATURE_WGET_STATUSBAR || ENABLE_FEATURE_WGET_TIMEOUT


			clearerr(dfp);
#endif
			errno = 0;
			rdsz = sizeof(G.wget_buf);
			if (G.got_clen) {
				if (G.content_len < (off_t)sizeof(G.wget_buf)) {
					if ((int)G.content_len <= 0)
						break;
					rdsz = (unsigned)G.content_len;
				}
			}
			n = fread(G.wget_buf, 1, rdsz, dfp);

			if (n > 0) {
				xwrite(G.output_fd, G.wget_buf, n);
#if ENABLE_FEATURE_WGET_STATUSBAR
				G.transferred += n;
#endif
				if (G.got_clen) {
					G.content_len -= n;
					if (G.content_len == 0)
						break;
				}
#if ENABLE_FEATURE_WGET_TIMEOUT
				second_cnt = G.timeout_seconds;
#endif
				goto bump;
			}


			if (errno != EAGAIN) {
				if (ferror(dfp)) {
					progress_meter(PROGRESS_END);
					bb_simple_perror_msg_and_die(bb_msg_read_error);
				}
				break;
			}

#if ENABLE_FEATURE_WGET_STATUSBAR || ENABLE_FEATURE_WGET_TIMEOUT


			if (safe_poll(&polldata, 1, 1000) == 0) {
# if ENABLE_FEATURE_WGET_TIMEOUT
				if (second_cnt != 0 && --second_cnt == 0) {
					progress_meter(PROGRESS_END);
					bb_simple_error_msg_and_die("download timed out");
				}
# endif


			}
#endif
 bump:


			progress_meter(PROGRESS_BUMP);
		}

#if ENABLE_FEATURE_WGET_STATUSBAR || ENABLE_FEATURE_WGET_TIMEOUT
		clearerr(dfp);
		ndelay_off(polldata.fd);
#endif
		if (!G.chunked)
			break;


		fgets_trim_sanitize(dfp, NULL);
 get_clen:

		fgets_trim_sanitize(dfp, NULL);
		errno = 0;
		G.content_len = STRTOOFF(G.wget_buf, NULL, 16);


		if (G.content_len < 0 || errno)
			bb_error_msg_and_die("bad chunk length '%s'", G.wget_buf);
		if (G.content_len == 0)
			break;
		G.got_clen = 1;


	}


	G.chunked = 0;
	G.got_clen = 1;
	progress_meter(PROGRESS_END);
	if (G.content_len != 0) {
		bb_simple_perror_msg_and_die("connection closed prematurely");

	}


	{
		off_t pos = lseek(G.output_fd, 0, SEEK_CUR);
		if (pos != (off_t)-1)
			ftruncate(G.output_fd, pos);
	}

	if (!(option_mask32 & WGET_OPT_QUIET)) {
		if (G.output_fd == 1)
			fprintf(stderr, "written to stdout\n");
		else
			fprintf(stderr, "'%s' saved\n", G.fname_out);
	}
}
