bnx2_chk_missed_msi(struct bnx2 *bp)
{
	struct bnx2_napi *bnapi = &bp->bnx2_napi[0];
	u32 msi_ctrl;

	if (bnx2_has_work(bnapi)) {
		msi_ctrl = BNX2_RD(bp, BNX2_PCICFG_MSI_CONTROL);
		if (!(msi_ctrl & BNX2_PCICFG_MSI_CONTROL_ENABLE))
			return;

		if (bnapi->last_status_idx == bp->idle_chk_status_idx) {
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl &
				~BNX2_PCICFG_MSI_CONTROL_ENABLE);
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl);
			bnx2_msi(bp->irq_tbl[0].vector, bnapi);
		}
	}

	bp->idle_chk_status_idx = bnapi->last_status_idx;
}
