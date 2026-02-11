mcs_net_open(struct net_device *netdev)
{
	struct mcs_cb *mcs = netdev_priv(netdev);
	char hwname[16];
	int ret = 0;

	ret = usb_clear_halt(mcs->usbdev,
			     usb_sndbulkpipe(mcs->usbdev, mcs->ep_in));
	if (ret)
		goto error1;
	ret = usb_clear_halt(mcs->usbdev,
			     usb_rcvbulkpipe(mcs->usbdev, mcs->ep_out));
	if (ret)
		goto error1;

	ret = mcs_setup_transceiver(mcs);
	if (ret)
		goto error1;

	ret = -ENOMEM;


	mcs->receiving = 0;
	mcs->rx_buff.truesize = IRDA_SKB_MAX_MTU;
	mcs->rx_buff.skb = dev_alloc_skb(IRDA_SKB_MAX_MTU);
	if (!mcs->rx_buff.skb)
		goto error1;

	skb_reserve(mcs->rx_buff.skb, 1);
	mcs->rx_buff.head = mcs->rx_buff.skb->data;


	sprintf(hwname, "usb#%d", mcs->usbdev->devnum);
	mcs->irlap = irlap_open(netdev, &mcs->qos, hwname);
	if (!mcs->irlap) {
		net_err_ratelimited("mcs7780: irlap_open failed\n");
		goto error2;
	}

	if (!mcs_setup_urbs(mcs))
		goto error3;

	ret = mcs_receive_start(mcs);
	if (ret)
		goto error4;

	netif_start_queue(netdev);
	return 0;

error4:
	usb_free_urb(mcs->rx_urb);
	usb_free_urb(mcs->tx_urb);
error3:
	irlap_close(mcs->irlap);
error2:
	kfree_skb(mcs->rx_buff.skb);
error1:
	return ret;
}
