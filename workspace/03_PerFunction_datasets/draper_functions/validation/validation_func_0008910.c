bnx2_fw_sync(struct bnx2 *bp, u32 msg_data, int ack, int silent)
{
	int i;
	u32 val;

	bp->fw_wr_seq++;
	msg_data |= bp->fw_wr_seq;
	bp->fw_last_msg = msg_data;

	bnx2_shmem_wr(bp, BNX2_DRV_MB, msg_data);

	if (!ack)
		return 0;


	for (i = 0; i < (BNX2_FW_ACK_TIME_OUT_MS / 10); i++) {
		msleep(10);

		val = bnx2_shmem_rd(bp, BNX2_FW_MB);

		if ((val & BNX2_FW_MSG_ACK) == (msg_data & BNX2_DRV_MSG_SEQ))
			break;
	}
	if ((msg_data & BNX2_DRV_MSG_DATA) == BNX2_DRV_MSG_DATA_WAIT0)
		return 0;


	if ((val & BNX2_FW_MSG_ACK) != (msg_data & BNX2_DRV_MSG_SEQ)) {
		msg_data &= ~BNX2_DRV_MSG_CODE;
		msg_data |= BNX2_DRV_MSG_CODE_FW_TIMEOUT;

		bnx2_shmem_wr(bp, BNX2_DRV_MB, msg_data);
		if (!silent) {
			pr_err("fw sync timeout, reset code = %x\n", msg_data);
			bnx2_dump_mcp_state(bp);
		}

		return -EBUSY;
	}

	if ((val & BNX2_FW_MSG_STATUS_MASK) != BNX2_FW_MSG_STATUS_OK)
		return -EIO;

	return 0;
}
