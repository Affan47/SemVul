static int sr9700_bind(struct usbnet *dev, struct usb_interface *intf)
{
	struct net_device *netdev;
	struct mii_if_info *mii;
	u8 addr[ETH_ALEN];
	int ret;

	ret = usbnet_get_endpoints(dev, intf);
	if (ret)
		goto out;

	netdev = dev->net;

	netdev->netdev_ops = &sr9700_netdev_ops;
	netdev->ethtool_ops = &sr9700_ethtool_ops;
	netdev->hard_header_len += SR_TX_OVERHEAD;
	dev->hard_mtu = netdev->mtu + netdev->hard_header_len;

	dev->rx_urb_size = 3072;

	mii = &dev->mii;
	mii->dev = netdev;
	mii->mdio_read = sr_mdio_read;
	mii->mdio_write = sr_mdio_write;
	mii->phy_id_mask = 0x1f;
	mii->reg_num_mask = 0x1f;

	sr_write_reg(dev, SR_NCR, NCR_RST);
	udelay(20);


	if (sr_read(dev, SR_PAR, ETH_ALEN, addr) < 0) {
		netdev_err(netdev, "Error reading MAC address\n");
		ret = -ENODEV;
		goto out;
	}
	eth_hw_addr_set(netdev, addr);


	sr_write_reg(dev, SR_PRR, PRR_PHY_RST);

	msleep(20);
	sr_write_reg(dev, SR_PRR, 0);

	udelay(2 * 1000);


	sr9700_set_multicast(netdev);

	sr_mdio_write(netdev, mii->phy_id, MII_BMCR, BMCR_RESET);
	sr_mdio_write(netdev, mii->phy_id, MII_ADVERTISE, ADVERTISE_ALL |
		      ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(mii);

out:
	return ret;
}
