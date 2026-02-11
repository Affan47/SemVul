enc28j60_setlink(struct net_device *ndev, u8 autoneg, u16 speed, u8 duplex)
{
	struct enc28j60_net *priv = netdev_priv(ndev);
	int ret = 0;

	if (!priv->hw_enable) {


		if (autoneg == AUTONEG_DISABLE && speed == SPEED_10)
			priv->full_duplex = (duplex == DUPLEX_FULL);
		else {
			if (netif_msg_link(priv))
				dev_warn(&ndev->dev,
					"unsupported link setting\n");
			ret = -EOPNOTSUPP;
		}
	} else {
		if (netif_msg_link(priv))
			dev_warn(&ndev->dev, "Warning: hw must be disabled "
				"to set link mode\n");
		ret = -EBUSY;
	}
	return ret;
}
