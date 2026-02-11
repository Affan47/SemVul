ndmta_local_mover_read (struct ndm_session *sess,
  unsigned long long offset, unsigned long long length)
{
	struct ndm_tape_agent *	ta = &sess->tape_acb;
	struct ndmp9_mover_get_state_reply *ms = &ta->mover_state;
	char *			errstr = 0;

	if (ms->state != NDMP9_MOVER_STATE_ACTIVE
	 && ms->state != NDMP9_MOVER_STATE_LISTEN) {
		errstr = "mover_state !ACTIVE";
		goto senderr;
	}
	if (ms->bytes_left_to_read > 0) {
		errstr = "byte_left_to_read";
		goto senderr;
	}
	if (ms->data_connection_addr.addr_type != NDMP9_ADDR_LOCAL) {
		errstr = "mover_addr !LOCAL";
		goto senderr;
	}
	if (ms->mode != NDMP9_MOVER_MODE_WRITE) {
		errstr = "mover_mode !WRITE";
		goto senderr;
	}

	ms->seek_position = offset;
	ms->bytes_left_to_read = length;
	ta->mover_want_pos = offset;

	return 0;

  senderr:
	if (errstr) {
		ndmalogf (sess, 0, 2, "local_read error why=%s", errstr);
	}

	return -1;
}
