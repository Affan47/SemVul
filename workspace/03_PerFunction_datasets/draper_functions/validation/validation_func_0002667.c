netx_handler(int irq, struct uio_info *dev_info)
{
	void __iomem *int_enable_reg = dev_info->mem[0].internal_addr
					+ DPM_HOST_INT_EN0;
	void __iomem *int_status_reg = dev_info->mem[0].internal_addr
					+ DPM_HOST_INT_STAT0;


	if (!(ioread32(int_enable_reg) & ioread32(int_status_reg)
		& DPM_HOST_INT_MASK))
		return IRQ_NONE;


	iowrite32(ioread32(int_enable_reg) & ~DPM_HOST_INT_GLOBAL_EN,
		int_enable_reg);
	return IRQ_HANDLED;
}
