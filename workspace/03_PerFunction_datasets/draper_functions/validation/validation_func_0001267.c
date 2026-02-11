mvs_64xx_isr(struct mvs_info *mvi, int irq, u32 stat)
{
	void __iomem *regs = mvi->regs;


	mw32_f(MVS_INT_STAT, CINT_DONE);

	spin_lock(&mvi->lock);
	mvs_int_full(mvi);
	spin_unlock(&mvi->lock);

	return IRQ_HANDLED;
}
