static void hso_net_tx_timeout(struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);

	if (!odev)
		return;


	dev_warn(&net->dev, "Tx timed out.\n");


	if (odev->mux_bulk_tx_urb &&
	    (odev->mux_bulk_tx_urb->status == -EINPROGRESS))
		usb_unlink_urb(odev->mux_bulk_tx_urb);


	net->stats.tx_errors++;
}
