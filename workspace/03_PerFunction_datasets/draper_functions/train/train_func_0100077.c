sti_dwmac_parse_data(struct sti_dwmac *dwmac,
				struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct regmap *regmap;
	int err;

	if (!np)
		return -EINVAL;


	dwmac->clk_sel_reg = -ENXIO;
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sti-clkconf");
	if (res)
		dwmac->clk_sel_reg = res->start;

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscon");
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	err = of_property_read_u32_index(np, "st,syscon", 1, &dwmac->ctrl_reg);
	if (err) {
		dev_err(dev, "Can't get sysconfig ctrl offset (%d)\n", err);
		return err;
	}

	dwmac->dev = dev;
	dwmac->interface = of_get_phy_mode(np);
	dwmac->regmap = regmap;
	dwmac->ext_phyclk = of_property_read_bool(np, "st,ext-phyclk");
	dwmac->tx_retime_src = TX_RETIME_SRC_NA;
	dwmac->speed = SPEED_100;

	if (IS_PHY_IF_MODE_GBIT(dwmac->interface)) {
		const char *rs;

		dwmac->tx_retime_src = TX_RETIME_SRC_CLKGEN;

		err = of_property_read_string(np, "st,tx-retime-src", &rs);
		if (err < 0) {
			dev_warn(dev, "Use internal clock source\n");
		} else {
			if (!strcasecmp(rs, "clk_125"))
				dwmac->tx_retime_src = TX_RETIME_SRC_CLK_125;
			else if (!strcasecmp(rs, "txclk"))
				dwmac->tx_retime_src = TX_RETIME_SRC_TXCLK;
		}
		dwmac->speed = SPEED_1000;
	}

	dwmac->clk = devm_clk_get(dev, "sti-ethclk");
	if (IS_ERR(dwmac->clk)) {
		dev_warn(dev, "No phy clock provided...\n");
		dwmac->clk = NULL;
	}

	return 0;
}
