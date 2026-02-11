armada375_init_sensor(struct platform_device *pdev,
				  struct armada_thermal_priv *priv)
{
	unsigned long reg;

	reg = readl(priv->control + 4);
	reg &= ~(A375_UNIT_CONTROL_MASK << A375_UNIT_CONTROL_SHIFT);
	reg &= ~A375_READOUT_INVERT;
	reg &= ~A375_HW_RESETn;

	writel(reg, priv->control + 4);
	mdelay(20);

	reg |= A375_HW_RESETn;
	writel(reg, priv->control + 4);
	mdelay(50);
}
