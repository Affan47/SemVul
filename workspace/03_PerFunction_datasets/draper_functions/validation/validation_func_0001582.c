l2tp_send_SCCRQ(void *peer_addr)
{
	struct l2tp_conn_t *conn = l2tp_tunnel_self();
	struct l2tp_packet_t *pack = NULL;
	uint16_t chall_len;
	int err;

	log_tunnel(log_info2, conn, "sending SCCRQ\n");

	pack = l2tp_packet_alloc(2, Message_Type_Start_Ctrl_Conn_Request,
				 &conn->peer_addr, conn->hide_avps,
				 conn->secret, conn->secret_len);
	if (pack == NULL) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " packet allocation failed\n");
		goto err;
	}

	if (l2tp_packet_add_int16(pack, Protocol_Version,
				  L2TP_V2_PROTOCOL_VERSION, 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}
	if (l2tp_packet_add_string(pack, Host_Name, conf_host_name, 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}
	if (l2tp_packet_add_int32(pack, Framing_Capabilities,
				  conn->framing_cap, 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}
	if (l2tp_packet_add_int16(pack, Assigned_Tunnel_ID,
				  conn->tid, 1) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}
	if (l2tp_packet_add_string(pack, Vendor_Name, "accel-ppp", 0) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}
	if (l2tp_packet_add_int16(pack, Recv_Window_Size, conn->recv_queue_sz,
				  1) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " adding data to packet failed\n");
		goto pack_err;
	}

	if (u_randbuf(&chall_len, sizeof(chall_len), &err) < 0) {
		if (err)
			log_tunnel(log_error, conn, "impossible to send SCCRQ:"
				   " reading from urandom failed: %s\n",
				   strerror(err));
		else
			log_tunnel(log_error, conn, "impossible to send SCCRQ:"
				   " end of file reached while reading"
				   " from urandom\n");
		goto pack_err;
	}
	chall_len = (chall_len & 0x007F) + MD5_DIGEST_LENGTH;
	if (l2tp_tunnel_genchall(chall_len, conn, pack) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " Challenge generation failed\n");
		goto pack_err;
	}

	l2tp_tunnel_send(conn, pack);

	if (l2tp_tunnel_push_sendqueue(conn) < 0) {
		log_tunnel(log_error, conn, "impossible to send SCCRQ:"
			   " transmitting messages from send queue failed\n");
		goto err;
	}

	conn->state = STATE_WAIT_SCCRP;

	return;

pack_err:
	l2tp_packet_free(pack);
err:
	l2tp_tunnel_free(conn);
}
