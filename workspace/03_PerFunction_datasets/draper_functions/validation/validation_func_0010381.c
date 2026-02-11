udc_enable(struct goku_udc *dev)
{

	if (readl(&dev->regs->power_detect) & PW_DETECT)
		ep0_start(dev);
	else {
		DBG(dev, "%s\n", __func__);
		dev->int_enable = INT_PWRDETECT;
		writel(dev->int_enable, &dev->regs->int_enable);
	}
}
