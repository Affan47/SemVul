void temac_indirect_out32_locked(struct temac_local *lp, int reg, u32 value)
{


	if (WARN_ON(temac_indirect_busywait(lp)))
		return;

	temac_iow(lp, XTE_LSW0_OFFSET, value);
	temac_iow(lp, XTE_CTL0_OFFSET, CNTLREG_WRITE_ENABLE_MASK | reg);


	WARN_ON(temac_indirect_busywait(lp));
}
