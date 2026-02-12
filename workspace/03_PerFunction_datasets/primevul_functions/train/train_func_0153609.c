u32 temac_indirect_in32_locked(struct temac_local *lp, int reg)
{


	if (WARN_ON(temac_indirect_busywait(lp)))
		return -ETIMEDOUT;

	temac_iow(lp, XTE_CTL0_OFFSET, reg);


	if (WARN_ON(temac_indirect_busywait(lp)))
		return -ETIMEDOUT;

	return temac_ior(lp, XTE_LSW0_OFFSET);
}
