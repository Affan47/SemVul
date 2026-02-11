sti_dwmac_init(struct platform_device *pdev, void *priv)
{
	struct sti_dwmac *dwmac = priv;
	struct regmap *regmap = dwmac->regmap;
	int iface = dwmac->interface;
	struct device *dev = dwmac->dev;
	struct device_node *np = dev->of_node;
	u32 reg = dwmac->ctrl_reg;
	u32 val;

	if (dwmac->clk)
		clk_prepare_enable(dwmac->clk);

	if (of_property_read_bool(np, "st,gmac_en"))
		regmap_update_bits(regmap, reg, EN_MASK, EN);

	regmap_update_bits(regmap, reg, MII_PHY_SEL_MASK, phy_intf_sels[iface]);

	val = (iface == PHY_INTERFACE_MODE_REVMII) ? 0 : ENMII;
	regmap_update_bits(regmap, reg, ENMII_MASK, val);

	dwmac->fix_retime_src(priv, dwmac->speed);

	return 0;
}
