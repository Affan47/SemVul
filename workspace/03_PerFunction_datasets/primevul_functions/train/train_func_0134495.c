static netdev_tx_t hso_net_start_xmit(struct sk_buff *skb,
					    struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);
	int result;


	netif_stop_queue(net);
	if (hso_get_activity(odev->parent) == -EAGAIN) {
		odev->skb_tx_buf = skb;
		return NETDEV_TX_OK;
	}


	DUMP1(skb->data, skb->len);

	memcpy(odev->mux_bulk_tx_buf, skb->data, skb->len);
	hso_dbg(0x1, "len: %d/%d\n", skb->len, MUX_BULK_TX_BUF_SIZE);


	usb_fill_bulk_urb(odev->mux_bulk_tx_urb,
			  odev->parent->usb,
			  usb_sndbulkpipe(odev->parent->usb,
					  odev->out_endp->
					  bEndpointAddress & 0x7F),
			  odev->mux_bulk_tx_buf, skb->len, write_bulk_callback,
			  odev);


	odev->mux_bulk_tx_urb->transfer_flags |= URB_ZERO_PACKET;


	result = usb_submit_urb(odev->mux_bulk_tx_urb, GFP_ATOMIC);
	if (result) {
		dev_warn(&odev->parent->interface->dev,
			"failed mux_bulk_tx_urb %d\n", result);
		net->stats.tx_errors++;
		netif_start_queue(net);
	} else {
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->len;
	}
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}
