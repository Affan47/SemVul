qla2x00_quiesce_io(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct scsi_qla_host *vp;

	ql_dbg(ql_dbg_dpc, vha, 0x401d,
	    "Quiescing I/O - ha=%p.\n", ha);

	atomic_set(&ha->loop_down_timer, LOOP_DOWN_TIME);
	if (atomic_read(&vha->loop_state) != LOOP_DOWN) {
		atomic_set(&vha->loop_state, LOOP_DOWN);
		qla2x00_mark_all_devices_lost(vha, 0);
		list_for_each_entry(vp, &ha->vp_list, list)
			qla2x00_mark_all_devices_lost(vp, 0);
	} else {
		if (!atomic_read(&vha->loop_down_timer))
			atomic_set(&vha->loop_down_timer,
					LOOP_DOWN_TIME);
	}

	qla2x00_eh_wait_for_pending_commands(vha, 0, 0, WAIT_HOST);
}
