smsc75xx_phy_initialize(struct usbnet *dev)
{
	int bmcr, ret, timeout = 0;


	dev->mii.dev = dev->net;
	dev->mii.mdio_read = smsc75xx_mdio_read;
	dev->mii.mdio_write = smsc75xx_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = SMSC75XX_INTERNAL_PHY_ID;


	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);

	do {
		msleep(10);
		bmcr = smsc75xx_mdio_read(dev->net, dev->mii.phy_id, MII_BMCR);
		if (bmcr < 0) {
			netdev_warn(dev->net, "Error reading MII_BMCR\n");
			return bmcr;
		}
		timeout++;
	} while ((bmcr & BMCR_RESET) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout on PHY Reset\n");
		return -EIO;
	}

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP |
		ADVERTISE_PAUSE_ASYM);
	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_CTRL1000,
		ADVERTISE_1000FULL);


	ret = smsc75xx_mdio_read(dev->net, dev->mii.phy_id, PHY_INT_SRC);
	if (ret < 0) {
		netdev_warn(dev->net, "Error reading PHY_INT_SRC\n");
		return ret;
	}

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_SRC, 0xffff);

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_MASK,
		PHY_INT_MASK_DEFAULT);
	mii_nway_restart(&dev->mii);

	netif_dbg(dev, ifup, dev->net, "phy initialised successfully\n");
	return 0;
}
