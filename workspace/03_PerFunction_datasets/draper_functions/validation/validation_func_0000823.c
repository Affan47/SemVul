emac_rockchip_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct rockchip_priv_data *priv = netdev_priv(ndev);
	int err;

	err = arc_emac_remove(ndev);

	clk_disable_unprepare(priv->refclk);

	if (priv->regulator)
		regulator_disable(priv->regulator);

	free_netdev(ndev);
	return err;
}
