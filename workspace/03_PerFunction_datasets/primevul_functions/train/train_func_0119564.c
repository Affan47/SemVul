key_share_recv_params(gnutls_session_t session,
		      const uint8_t * data, size_t data_size)
{
	int ret;
	size_t size;
	unsigned gid;
	const version_entry_st *ver;
	const gnutls_group_entry_st *group;
	unsigned used_share = 0;

	if (session->security_parameters.entity == GNUTLS_SERVER) {
		ver = get_version(session);
		if (ver == NULL || ver->key_shares == 0)
			return gnutls_assert_val(0);

		DECR_LEN(data_size, 2);
		size = _gnutls_read_uint16(data);
		data += 2;

		if (data_size != size)
			return gnutls_assert_val(GNUTLS_E_UNEXPECTED_PACKET_LENGTH);


		if ((session->internals.hsk_flags & HSK_PSK_SELECTED) &&
		    (session->internals.hsk_flags & HSK_PSK_KE_MODE_PSK)) {
			reset_cand_groups(session);
			return 0;
		}

		while(data_size > 0) {
			DECR_LEN(data_size, 2);
			gid = _gnutls_read_uint16(data);
			data += 2;

			DECR_LEN(data_size, 2);
			size = _gnutls_read_uint16(data);
			data += 2;

			DECR_LEN(data_size, size);


			group = _gnutls_tls_id_to_group(gid);

			if (group != NULL)
				_gnutls_handshake_log("EXT[%p]: Received key share for %s\n", session, group->name);

			if (group != NULL && group == session->internals.cand_group) {
				_gnutls_session_group_set(session, group);

				ret = server_use_key_share(session, group, data, size);
				if (ret < 0)
					return gnutls_assert_val(ret);

				used_share = 1;
				break;

			}

			data += size;
			continue;
		}


		if (used_share == 0) {
			return gnutls_assert_val(GNUTLS_E_NO_COMMON_KEY_SHARE);
		}

		session->internals.hsk_flags |= HSK_KEY_SHARE_RECEIVED;
	} else {
		ver = get_version(session);
		if (unlikely(ver == NULL || ver->key_shares == 0))
			return gnutls_assert_val(GNUTLS_E_RECEIVED_ILLEGAL_PARAMETER);

		if (_gnutls_ext_get_msg(session) == GNUTLS_EXT_FLAG_HRR) {
			if (unlikely(!(session->internals.hsk_flags & HSK_HRR_RECEIVED)))
				return gnutls_assert_val(GNUTLS_E_RECEIVED_ILLEGAL_PARAMETER);

			DECR_LEN(data_size, 2);
			gid = _gnutls_read_uint16(data);

			group = _gnutls_tls_id_to_group(gid);
			if (group == NULL)
				return gnutls_assert_val(GNUTLS_E_RECEIVED_ILLEGAL_PARAMETER);

			_gnutls_handshake_log("EXT[%p]: HRR key share with %s\n", session, group->name);


			ret = _gnutls_session_supports_group(session, group->id);
			if (ret < 0) {
				_gnutls_handshake_log("EXT[%p]: received share for %s which is disabled\n", session, group->name);
				return gnutls_assert_val(ret);
			}

			_gnutls_session_group_set(session, group);

			return 0;
		}


		DECR_LEN(data_size, 2);
		gid = _gnutls_read_uint16(data);
		data += 2;

		DECR_LEN(data_size, 2);
		size = _gnutls_read_uint16(data);
		data+=2;

		if (data_size != size)
			return gnutls_assert_val(GNUTLS_E_UNEXPECTED_PACKET_LENGTH);

		group = _gnutls_tls_id_to_group(gid);
		if (group == NULL)
			return gnutls_assert_val(GNUTLS_E_RECEIVED_ILLEGAL_PARAMETER);


		ret = _gnutls_session_supports_group(session, group->id);
		if (ret < 0) {
			_gnutls_handshake_log("EXT[%p]: received share for %s which is disabled\n", session, group->name);
			return gnutls_assert_val(ret);
		}

		_gnutls_session_group_set(session, group);
		session->internals.hsk_flags |= HSK_KEY_SHARE_RECEIVED;

		ret = client_use_key_share(session, group, data, size);
		if (ret < 0)
			return gnutls_assert_val(ret);
	}

	return 0;
}
