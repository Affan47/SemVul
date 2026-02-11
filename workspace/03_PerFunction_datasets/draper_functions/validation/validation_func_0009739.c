mover_can_proceed (struct ndm_session *sess, int will_write)
{
	struct ndm_tape_agent *		ta = &sess->tape_acb;

	ndmos_tape_sync_state(sess);
	if (ta->tape_state.state != NDMP9_TAPE_STATE_OPEN)
		return NDMP9_DEV_NOT_OPEN_ERR;

	if (will_write && !NDMTA_TAPE_IS_WRITABLE(ta))
		return NDMP9_PERMISSION_ERR;

	return NDMP9_NO_ERR;
}
