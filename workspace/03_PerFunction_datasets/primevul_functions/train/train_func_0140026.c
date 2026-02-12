static void bnx2x_sp_prod_update(struct bnx2x *bp)
{
	int func = BP_FUNC(bp);


	mb();

	REG_WR16(bp, BAR_XSTRORM_INTMEM + XSTORM_SPQ_PROD_OFFSET(func),
		 bp->spq_prod_idx);
	mmiowb();
}
