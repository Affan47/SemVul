intel_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	void __iomem *gpsr, *gpcr;

	if (value) {
		gpsr = gpio_reg(chip, offset, GPSR);
		writel(BIT(offset % 32), gpsr);
	} else {
		gpcr = gpio_reg(chip, offset, GPCR);
		writel(BIT(offset % 32), gpcr);
	}
}
