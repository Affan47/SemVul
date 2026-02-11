kaweth_usb_transmit_complete(struct urb *urb)
{
	struct kaweth_device *kaweth = urb->context;
	struct sk_buff *skb = kaweth->tx_skb;
	int status = urb->status;

	if (unlikely(status != 0))
		if (status != -ENOENT)
			dev_dbg(&urb->dev->dev, "%s: TX status %d.\n",
				kaweth->net->name, status);

	netif_wake_queue(kaweth->net);
	dev_kfree_skb_irq(skb);
}
