inflate_unzip_internal(STATE_PARAM transformer_state_t *xstate)
{
	IF_DESKTOP(long long) int n = 0;
	ssize_t nwrote;


	gunzip_window = xmalloc(GUNZIP_WSIZE);
	gunzip_outbuf_count = 0;
	gunzip_bytes_out = 0;
	gunzip_src_fd = xstate->src_fd;


	method = -1;
	need_another_block = 1;
	resume_copy = 0;
	gunzip_bk = 0;
	gunzip_bb = 0;


	gunzip_crc_table = crc32_new_table_le();
	gunzip_crc = ~0;

	error_msg = "corrupted data";
	if (setjmp(error_jmp)) {

		bb_simple_error_msg(error_msg);
		n = -1;
		goto ret;
	}

	while (1) {
		int r = inflate_get_next_window(PASS_STATE_ONLY);
		nwrote = transformer_write(xstate, gunzip_window, gunzip_outbuf_count);
		if (nwrote == (ssize_t)-1) {
			n = -1;
			goto ret;
		}
		IF_DESKTOP(n += nwrote;)
		if (r == 0) break;
	}


	if (gunzip_bk >= 8) {


		bytebuffer_offset--;
		bytebuffer[bytebuffer_offset] = gunzip_bb & 0xff;
		gunzip_bb >>= 8;
		gunzip_bk -= 8;
	}
 ret:

	free(gunzip_window);
	free(gunzip_crc_table);
	return n;
}
