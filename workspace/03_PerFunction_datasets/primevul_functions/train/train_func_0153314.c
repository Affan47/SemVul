static int dwc3_byt_enable_ulpi_refclock(struct pci_dev *pci)
{
	void __iomem	*reg;
	u32		value;

	reg = pcim_iomap(pci, GP_RWBAR, 0);
	if (!reg)
		return -ENOMEM;

	value = readl(reg + GP_RWREG1);
	if (!(value & GP_RWREG1_ULPI_REFCLK_DISABLE))
		goto unmap;

	value &= ~GP_RWREG1_ULPI_REFCLK_DISABLE;
	writel(value, reg + GP_RWREG1);

	msleep(100);
unmap:
	pcim_iounmap(pci, reg);
	return 0;
}
