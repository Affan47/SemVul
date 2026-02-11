usbpn_close(struct net_device *dev)
{
	struct usbpn_dev *pnd = netdev_priv(dev);
	unsigned i;
	unsigned num = pnd->data_intf->cur_altsetting->desc.bInterfaceNumber;

	netif_stop_queue(dev);

	for (i = 0; i < rxq_size; i++) {
		struct urb *req = pnd->urbs[i];

		if (!req)
			continue;
		usb_kill_urb(req);
		usb_free_urb(req);
		pnd->urbs[i] = NULL;
	}

	return usb_set_interface(pnd->usb, num, !pnd->active_setting);
}
