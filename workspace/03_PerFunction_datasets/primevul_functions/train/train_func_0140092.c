static void bnx2x_sp_task(struct work_struct *work)
{
	struct bnx2x *bp = container_of(work, struct bnx2x, sp_task.work);

	DP(BNX2X_MSG_SP, "sp task invoked\n");


	smp_rmb();
	if (atomic_read(&bp->interrupt_occurred)) {


		u16 status = bnx2x_update_dsb_idx(bp);

		DP(BNX2X_MSG_SP, "status %x\n", status);
		DP(BNX2X_MSG_SP, "setting interrupt_occurred to 0\n");
		atomic_set(&bp->interrupt_occurred, 0);


		if (status & BNX2X_DEF_SB_ATT_IDX) {
			bnx2x_attn_int(bp);
			status &= ~BNX2X_DEF_SB_ATT_IDX;
		}


		if (status & BNX2X_DEF_SB_IDX) {
			struct bnx2x_fastpath *fp = bnx2x_fcoe_fp(bp);

			if (FCOE_INIT(bp) &&
			    (bnx2x_has_rx_work(fp) || bnx2x_has_tx_work(fp))) {


				local_bh_disable();
				napi_schedule(&bnx2x_fcoe(bp, napi));
				local_bh_enable();
			}


			bnx2x_eq_int(bp);
			bnx2x_ack_sb(bp, bp->igu_dsb_id, USTORM_ID,
				     le16_to_cpu(bp->def_idx), IGU_INT_NOP, 1);

			status &= ~BNX2X_DEF_SB_IDX;
		}


		if (unlikely(status))
			DP(BNX2X_MSG_SP,
			   "got an unknown interrupt! (status 0x%x)\n", status);


		bnx2x_ack_sb(bp, bp->igu_dsb_id, ATTENTION_ID,
			     le16_to_cpu(bp->def_att_idx), IGU_INT_ENABLE, 1);
	}


	if (test_and_clear_bit(BNX2X_AFEX_PENDING_VIFSET_MCP_ACK,
			       &bp->sp_state)) {
		bnx2x_link_report(bp);
		bnx2x_fw_command(bp, DRV_MSG_CODE_AFEX_VIFSET_ACK, 0);
	}
}
