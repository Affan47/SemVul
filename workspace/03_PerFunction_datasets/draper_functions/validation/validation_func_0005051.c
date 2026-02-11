httpc_demux(http_session_t * session) {

	int meta_len;
	char meta_len_buf;
	char * meta_buf;

	if (read_socket(session->sock, &meta_len_buf, 1) != 1)
		return -1;

	meta_len = 16 * meta_len_buf;
	meta_buf = calloc(meta_len+1, 1);
	if (read_socket(session->sock, meta_buf, meta_len) != meta_len)
		return -1;

	meta_buf[meta_len] = '\0';

	if (meta_len > 0 && session->fdec != NULL && session->fdec->meta_cb != NULL) {
		metadata_t * meta = metadata_from_mpeg_stream_data(meta_buf);
		meta->fdec = session->fdec;
		session->fdec->meta = meta;
		httpc_add_headers_meta(session, meta);
		session->fdec->meta_cb(meta, session->fdec->meta_cbdata);
	}

	free(meta_buf);
	return 0;
}
