update_permanent_hw_address (NMDevice *dev)
{
	NMDeviceEthernet *self = NM_DEVICE_ETHERNET (dev);
	NMDeviceEthernetPrivate *priv = NM_DEVICE_ETHERNET_GET_PRIVATE (self);
	struct ifreq req;
	struct ethtool_perm_addr *epaddr = NULL;
	int fd, ret;

	fd = socket (PF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		nm_log_warn (LOGD_HW, "couldn't open control socket.");
		return;
	}


	memset (&req, 0, sizeof (struct ifreq));
	strncpy (req.ifr_name, nm_device_get_iface (dev), IFNAMSIZ);

	epaddr = g_malloc0 (sizeof (struct ethtool_perm_addr) + ETH_ALEN);
	epaddr->cmd = ETHTOOL_GPERMADDR;
	epaddr->size = ETH_ALEN;
	req.ifr_data = (void *) epaddr;

	errno = 0;
	ret = ioctl (fd, SIOCETHTOOL, &req);
	if ((ret < 0) || !nm_ethernet_address_is_valid ((struct ether_addr *) epaddr->data)) {
		nm_log_dbg (LOGD_HW | LOGD_ETHER, "(%s): unable to read permanent MAC address (error %d)",
		            nm_device_get_iface (dev), errno);

		memcpy (epaddr->data, priv->hw_addr, ETH_ALEN);
	}

	if (memcmp (&priv->perm_hw_addr, epaddr->data, ETH_ALEN)) {
		memcpy (&priv->perm_hw_addr, epaddr->data, ETH_ALEN);
		g_object_notify (G_OBJECT (dev), NM_DEVICE_ETHERNET_PERMANENT_HW_ADDRESS);
	}

	g_free (epaddr);
	close (fd);
}
