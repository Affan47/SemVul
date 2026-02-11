stmmac_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	if (!netif_running(dev))
		return -EINVAL;

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		if (!priv->phydev)
			return -EINVAL;
		ret = phy_mii_ioctl(priv->phydev, rq, cmd);
		break;
	case SIOCSHWTSTAMP:
		ret = stmmac_hwtstamp_ioctl(dev, rq);
		break;
	default:
		break;
	}

	return ret;
}
