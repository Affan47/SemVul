simu_back_one (struct ndm_session *sess, int over_file_mark)
{
	struct ndm_tape_agent *	ta = &sess->tape_acb;
	struct simu_gap		gap;
	off_t			cur_pos;
	off_t			new_pos;
	int			rc;

	cur_pos = lseek (ta->tape_fd, (off_t)0, 1);

	rc = read (ta->tape_fd, &gap, sizeof gap);
	if (rc != sizeof gap || gap.magic != SIMU_GAP_MAGIC)
		goto bail_out;

	new_pos = cur_pos;
	new_pos -= sizeof gap + gap.prev_size;

	ta->sent_leom = 0;


	lseek (ta->tape_fd, new_pos, 0);

	rc = read (ta->tape_fd, &gap, sizeof gap);
	if (rc != sizeof gap || gap.magic != SIMU_GAP_MAGIC)
		goto bail_out;

	switch (gap.rectype) {
	case SIMU_GAP_RT_BOT:

		ta->tape_state.file_num.value = 0;
		ta->tape_state.blockno.value = 0;

		return 0;

	case SIMU_GAP_RT_EOT:

		goto bail_out;

	case SIMU_GAP_RT_DATA:

		if (ta->tape_state.blockno.value > 0)
			ta->tape_state.blockno.value--;
		lseek (ta->tape_fd, new_pos, 0);
		return SIMU_GAP_RT_DATA;

	case SIMU_GAP_RT_FILE:
		ta->tape_state.blockno.value = 0;
		if (!over_file_mark) {
			lseek (ta->tape_fd, cur_pos, 0);
			return 0;
		}
		if (ta->tape_state.file_num.value > 0)
			ta->tape_state.file_num.value--;
		lseek (ta->tape_fd, new_pos, 0);
		return SIMU_GAP_RT_FILE;

	default:

		goto bail_out;
	}

  bail_out:
	lseek (ta->tape_fd, cur_pos, 0);
	return -1;
}
