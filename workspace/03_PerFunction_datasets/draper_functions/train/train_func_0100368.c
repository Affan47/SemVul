target_alua_state_check(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned char *cdb = cmd->t_task_cdb;
	struct se_lun *lun = cmd->se_lun;
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	int out_alua_state, nonop_delay_msecs;

	if (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)
		return 0;
	if (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		return 0;


	if (atomic_read(&lun->lun_tg_pt_secondary_offline)) {
		pr_debug("ALUA: Got secondary offline status for local"
				" target port\n");
		set_ascq(cmd, ASCQ_04H_ALUA_OFFLINE);
		return TCM_CHECK_CONDITION_NOT_READY;
	}

	if (!lun->lun_tg_pt_gp)
		return 0;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	out_alua_state = atomic_read(&tg_pt_gp->tg_pt_gp_alua_access_state);
	nonop_delay_msecs = tg_pt_gp->tg_pt_gp_nonop_delay_msecs;


	spin_unlock(&lun->lun_tg_pt_gp_lock);


	if (out_alua_state == ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED)
		return 0;

	switch (out_alua_state) {
	case ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		core_alua_state_nonoptimized(cmd, cdb, nonop_delay_msecs);
		break;
	case ALUA_ACCESS_STATE_STANDBY:
		if (core_alua_state_standby(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_UNAVAILABLE:
		if (core_alua_state_unavailable(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_TRANSITION:
		if (core_alua_state_transition(cmd, cdb))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;
	case ALUA_ACCESS_STATE_LBA_DEPENDENT:
		if (core_alua_state_lba_dependent(cmd, tg_pt_gp))
			return TCM_CHECK_CONDITION_NOT_READY;
		break;


	case ALUA_ACCESS_STATE_OFFLINE:
	default:
		pr_err("Unknown ALUA access state: 0x%02x\n",
				out_alua_state);
		return TCM_INVALID_CDB_FIELD;
	}

	return 0;
}
