bnx2_ctx_wr(struct bnx2 *bp, u32 cid_addr, u32 offset, u32 val)
{
	offset += cid_addr;
	spin_lock_bh(&bp->indirect_lock);
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		int i;

		BNX2_WR(bp, BNX2_CTX_CTX_DATA, val);
		BNX2_WR(bp, BNX2_CTX_CTX_CTRL,
			offset | BNX2_CTX_CTX_CTRL_WRITE_REQ);
		for (i = 0; i < 5; i++) {
			val = BNX2_RD(bp, BNX2_CTX_CTX_CTRL);
			if ((val & BNX2_CTX_CTX_CTRL_WRITE_REQ) == 0)
				break;
			udelay(5);
		}
	} else {
		BNX2_WR(bp, BNX2_CTX_DATA_ADR, offset);
		BNX2_WR(bp, BNX2_CTX_DATA, val);
	}
	spin_unlock_bh(&bp->indirect_lock);
}
