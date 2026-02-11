stmmac_ethtool_op_set_eee(struct net_device *dev,
				     struct ethtool_eee *edata)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	priv->eee_enabled = edata->eee_enabled;

	if (!priv->eee_enabled)
		stmmac_disable_eee_mode(priv);
	else {


		priv->eee_enabled = stmmac_eee_init(priv);
		if (!priv->eee_enabled)
			return -EOPNOTSUPP;


		priv->tx_lpi_timer = edata->tx_lpi_timer;
	}

	return phy_ethtool_set_eee(priv->phydev, edata);
}
