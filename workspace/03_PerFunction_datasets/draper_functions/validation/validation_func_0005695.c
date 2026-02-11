mf624_irq_handler(int irq, struct uio_info *info)
{
	void __iomem *INTCSR_reg = info->mem[0].internal_addr + INTCSR;

	if ((ioread32(INTCSR_reg) & INTCSR_ADINT_ENABLE)
	    && (ioread32(INTCSR_reg) & INTCSR_ADINT_STATUS)) {
		mf624_disable_interrupt(ADC, info);
		return IRQ_HANDLED;
	}

	if ((ioread32(INTCSR_reg) & INTCSR_CTR4INT_ENABLE)
	    && (ioread32(INTCSR_reg) & INTCSR_CTR4INT_STATUS)) {
		mf624_disable_interrupt(CTR4, info);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}
