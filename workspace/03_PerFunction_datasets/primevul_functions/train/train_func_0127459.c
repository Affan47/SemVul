static enum_func_status
php_mysqlnd_greet_read(MYSQLND_CONN_DATA * conn, void * _packet)
{
	zend_uchar buf[2048];
	const zend_uchar * p = buf;
	const zend_uchar * const begin = buf;
	const zend_uchar * pad_start = NULL;
	MYSQLND_PACKET_GREET *packet= (MYSQLND_PACKET_GREET *) _packet;
	MYSQLND_ERROR_INFO * error_info = conn->error_info;
	MYSQLND_PFC * pfc = conn->protocol_frame_codec;
	MYSQLND_VIO * vio = conn->vio;
	MYSQLND_STATS * stats = conn->stats;
	MYSQLND_CONNECTION_STATE * connection_state = &conn->state;

	DBG_ENTER("php_mysqlnd_greet_read");

	if (FAIL == mysqlnd_read_packet_header_and_body(&(packet->header), pfc, vio, stats, error_info, connection_state, buf, sizeof(buf), "greeting", PROT_GREET_PACKET)) {
		DBG_RETURN(FAIL);
	}
	BAIL_IF_NO_MORE_DATA;

	packet->authentication_plugin_data.s = packet->intern_auth_plugin_data;
	packet->authentication_plugin_data.l = sizeof(packet->intern_auth_plugin_data);

	if (packet->header.size < sizeof(buf)) {


		buf[packet->header.size] = '\0';
	}

	packet->protocol_version = uint1korr(p);
	p++;
	BAIL_IF_NO_MORE_DATA;

	if (ERROR_MARKER == packet->protocol_version) {
		php_mysqlnd_read_error_from_line(p, packet->header.size - 1,
										 packet->error, sizeof(packet->error),
										 &packet->error_no, packet->sqlstate
										);


		if (packet->error_no == 1040) {
			memcpy(packet->sqlstate, "08004", MYSQLND_SQLSTATE_LENGTH);
		}
		DBG_RETURN(PASS);
	}

	packet->server_version = estrdup((char *)p);
	p+= strlen(packet->server_version) + 1;
	BAIL_IF_NO_MORE_DATA;

	packet->thread_id = uint4korr(p);
	p+=4;
	BAIL_IF_NO_MORE_DATA;

	memcpy(packet->authentication_plugin_data.s, p, SCRAMBLE_LENGTH_323);
	p+= SCRAMBLE_LENGTH_323;
	BAIL_IF_NO_MORE_DATA;


	p++;
	BAIL_IF_NO_MORE_DATA;

	packet->server_capabilities = uint2korr(p);
	p+= 2;
	BAIL_IF_NO_MORE_DATA;
	DBG_INF_FMT("4.1 server_caps=%u\n", (uint32_t) packet->server_capabilities);

	packet->charset_no = uint1korr(p);
	p++;
	BAIL_IF_NO_MORE_DATA;

	packet->server_status = uint2korr(p);
	p+= 2;
	BAIL_IF_NO_MORE_DATA;


	pad_start = p;
	p+= 13;
	BAIL_IF_NO_MORE_DATA;

	if ((size_t) (p - buf) < packet->header.size) {

		memcpy(packet->authentication_plugin_data.s + SCRAMBLE_LENGTH_323, p, SCRAMBLE_LENGTH - SCRAMBLE_LENGTH_323);
		p+= SCRAMBLE_LENGTH - SCRAMBLE_LENGTH_323;
		p++;
	} else {
		packet->pre41 = TRUE;
	}


	if ((size_t) (p - buf) < packet->header.size) {

		p--;


		DBG_INF_FMT("additional 5.5+ caps=%u\n", (uint32_t) uint2korr(pad_start));
		packet->server_capabilities |= ((uint32_t) uint2korr(pad_start)) << 16;

		packet->authentication_plugin_data.l = uint1korr(pad_start + 2);
		if (packet->authentication_plugin_data.l > SCRAMBLE_LENGTH) {

			char * new_auth_plugin_data = emalloc(packet->authentication_plugin_data.l);


			memcpy(new_auth_plugin_data, packet->authentication_plugin_data.s, SCRAMBLE_LENGTH);

			memcpy(new_auth_plugin_data + SCRAMBLE_LENGTH, p, packet->authentication_plugin_data.l - SCRAMBLE_LENGTH);
			p+= (packet->authentication_plugin_data.l - SCRAMBLE_LENGTH);
			packet->authentication_plugin_data.s = new_auth_plugin_data;
		}
	}

	if (packet->server_capabilities & CLIENT_PLUGIN_AUTH) {
		BAIL_IF_NO_MORE_DATA;

		packet->auth_protocol = estrdup((char *)p);
		p+= strlen(packet->auth_protocol) + 1;
	}

	DBG_INF_FMT("proto=%u server=%s thread_id=%u",
				packet->protocol_version, packet->server_version, packet->thread_id);

	DBG_INF_FMT("server_capabilities=%u charset_no=%u server_status=%i auth_protocol=%s scramble_length=%u",
				packet->server_capabilities, packet->charset_no, packet->server_status,
				packet->auth_protocol? packet->auth_protocol:"n/a", packet->authentication_plugin_data.l);

	DBG_RETURN(PASS);
premature_end:
	DBG_ERR_FMT("GREET packet %d bytes shorter than expected", p - begin - packet->header.size);
	php_error_docref(NULL, E_WARNING, "GREET packet "MYSQLND_SZ_T_SPEC" bytes shorter than expected",
					 p - begin - packet->header.size);
	DBG_RETURN(FAIL);
}
