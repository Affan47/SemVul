bz_write(bz_stream *strm, void* rbuf, ssize_t rlen, void *wbuf)
{
	int n, n2, ret;

	strm->avail_in = rlen;
	strm->next_in = rbuf;
	while (1) {
		strm->avail_out = IOBUF_SIZE;
		strm->next_out = wbuf;

		ret = BZ2_bzCompress(strm, rlen ? BZ_RUN : BZ_FINISH);
		if (ret != BZ_RUN_OK
		 && ret != BZ_FINISH_OK
		 && ret != BZ_STREAM_END
		) {
			bb_error_msg_and_die("internal error %d", ret);
		}

		n = IOBUF_SIZE - strm->avail_out;
		if (n) {
			n2 = full_write(STDOUT_FILENO, wbuf, n);
			if (n2 != n) {
				if (n2 >= 0)
					errno = 0;
				bb_perror_msg(n2 >= 0 ? "short write" : bb_msg_write_error);
				return -1;
			}
		}

		if (ret == BZ_STREAM_END)
			break;
		if (rlen && strm->avail_in == 0)
			break;
	}
	return 0 IF_DESKTOP( + strm->total_out );
}
