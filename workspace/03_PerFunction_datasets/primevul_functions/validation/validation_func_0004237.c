static void connection_handle_response_end_state(request_st * const r, connection * const con) {
	if (r->http_version > HTTP_VERSION_1_1) {
		h2_retire_con(r, con);
		r->keep_alive = 0;


		r->http_status = 100;
	}


	if (r->http_status) plugins_call_handle_request_done(r);

	if (r->state != CON_STATE_ERROR) ++con->srv->con_written;

	if (r->reqbody_length != r->reqbody_queue.bytes_in
	    || r->state == CON_STATE_ERROR) {

		r->keep_alive = 0;

		if (&r->write_queue != con->write_queue) {
			chunkqueue_free(con->write_queue);
			con->write_queue = &r->write_queue;
		}
	}

        if (r->keep_alive) {
		request_reset(r);
		config_reset_config(r);
		con->is_readable = 1;

		r->bytes_read_ckpt = con->bytes_read;
		r->bytes_written_ckpt = con->bytes_written;
#if 0
		r->start_hp.tv_sec = con->read_idle_ts = log_epoch_secs;
#endif
		connection_set_state(r, CON_STATE_REQUEST_START);
	} else {
		connection_handle_shutdown(con);
	}
}
