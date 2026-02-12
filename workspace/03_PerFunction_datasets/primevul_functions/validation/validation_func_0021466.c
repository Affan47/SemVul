isdn_net_init(struct net_device *ndev)
{
	ushort max_hlhdr_len = 0;
	int drvidx;

	ether_setup(ndev);
	ndev->header_ops = NULL;


	ndev->mtu = 1500;
	ndev->flags = IFF_NOARP|IFF_POINTOPOINT;
	ndev->type = ARPHRD_ETHER;
	ndev->addr_len = ETH_ALEN;


	ndev->tx_queue_len = 30;


	ndev->open = &isdn_net_open;
	ndev->hard_start_xmit = &isdn_net_start_xmit;


	for (drvidx = 0; drvidx < ISDN_MAX_DRIVERS; drvidx++)
		if (dev->drv[drvidx])
			if (max_hlhdr_len < dev->drv[drvidx]->interface->hl_hdrlen)
				max_hlhdr_len = dev->drv[drvidx]->interface->hl_hdrlen;

	ndev->hard_header_len = ETH_HLEN + max_hlhdr_len;
	ndev->stop = &isdn_net_close;
	ndev->get_stats = &isdn_net_get_stats;
	ndev->do_ioctl = NULL;
	return 0;
}
