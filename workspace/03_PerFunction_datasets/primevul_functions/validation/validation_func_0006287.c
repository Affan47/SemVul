static bool ldapsrv_call_read_next(struct ldapsrv_connection *conn)
{
	struct tevent_req *subreq;

	if (conn->pending_calls != NULL) {
		conn->limits.endtime = timeval_zero();

		ldapsrv_notification_retry_setup(conn->service, false);
	} else if (timeval_is_zero(&conn->limits.endtime)) {
		conn->limits.endtime =
			timeval_current_ofs(conn->limits.initial_timeout, 0);
	} else {
		conn->limits.endtime =
			timeval_current_ofs(conn->limits.conn_idle_time, 0);
	}

	if (conn->sockets.read_req != NULL) {
		return true;
	}


	subreq = tstream_read_pdu_blob_send(conn,
					    conn->connection->event.ctx,
					    conn->sockets.active,
					    7,
					    ldapsrv_packet_check,
					    conn);
	if (subreq == NULL) {
		ldapsrv_terminate_connection(conn, "ldapsrv_call_read_next: "
				"no memory for tstream_read_pdu_blob_send");
		return false;
	}
	if (!timeval_is_zero(&conn->limits.endtime)) {
		bool ok;
		ok = tevent_req_set_endtime(subreq,
					    conn->connection->event.ctx,
					    conn->limits.endtime);
		if (!ok) {
			ldapsrv_terminate_connection(
				conn,
				"ldapsrv_call_read_next: "
				"no memory for tevent_req_set_endtime");
			return false;
		}
	}
	tevent_req_set_callback(subreq, ldapsrv_call_read_done, conn);
	conn->sockets.read_req = subreq;
	return true;
}
