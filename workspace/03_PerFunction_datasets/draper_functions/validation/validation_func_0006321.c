qla83xx_check_nic_core_fw_alive(scsi_qla_host_t *base_vha)
{
	int rval = QLA_SUCCESS;
	unsigned long heart_beat_wait = jiffies + (1 * HZ);
	uint32_t heart_beat_counter1, heart_beat_counter2;

	do {
		if (time_after(jiffies, heart_beat_wait)) {
			ql_dbg(ql_dbg_p3p, base_vha, 0xb07c,
			    "Nic Core f/w is not alive.\n");
			rval = QLA_FUNCTION_FAILED;
			break;
		}

		qla83xx_idc_lock(base_vha, 0);
		qla83xx_rd_reg(base_vha, QLA83XX_FW_HEARTBEAT,
		    &heart_beat_counter1);
		qla83xx_idc_unlock(base_vha, 0);
		msleep(100);
		qla83xx_idc_lock(base_vha, 0);
		qla83xx_rd_reg(base_vha, QLA83XX_FW_HEARTBEAT,
		    &heart_beat_counter2);
		qla83xx_idc_unlock(base_vha, 0);
	} while (heart_beat_counter1 == heart_beat_counter2);

	return rval;
}
