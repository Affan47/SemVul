ohci_platform_power_on(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct ohci_platform_priv *priv = hcd_to_ohci_priv(hcd);
	int clk, ret, phy_num;

	for (clk = 0; clk < OHCI_MAX_CLKS && priv->clks[clk]; clk++) {
		ret = clk_prepare_enable(priv->clks[clk]);
		if (ret)
			goto err_disable_clks;
	}

	for (phy_num = 0; phy_num < priv->num_phys; phy_num++) {
		ret = phy_init(priv->phys[phy_num]);
		if (ret)
			goto err_exit_phy;
		ret = phy_power_on(priv->phys[phy_num]);
		if (ret) {
			phy_exit(priv->phys[phy_num]);
			goto err_exit_phy;
		}
	}

	return 0;

err_exit_phy:
	while (--phy_num >= 0) {
		phy_power_off(priv->phys[phy_num]);
		phy_exit(priv->phys[phy_num]);
	}
err_disable_clks:
	while (--clk >= 0)
		clk_disable_unprepare(priv->clks[clk]);

	return ret;
}
