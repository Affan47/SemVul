qla2x00_perform_loop_resync(scsi_qla_host_t *ha)
{
	int32_t rval = 0;

	if (!test_and_set_bit(LOOP_RESYNC_ACTIVE, &ha->dpc_flags)) {

		atomic_set(&ha->loop_down_timer, 0);
		if (!(ha->device_flags & DFLG_NO_CABLE)) {
			atomic_set(&ha->loop_state, LOOP_UP);
			set_bit(LOCAL_LOOP_UPDATE, &ha->dpc_flags);
			set_bit(REGISTER_FC4_NEEDED, &ha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &ha->dpc_flags);

			rval = qla2x00_loop_resync(ha);
		} else
			atomic_set(&ha->loop_state, LOOP_DEAD);

		clear_bit(LOOP_RESYNC_ACTIVE, &ha->dpc_flags);
	}

	return rval;
}
