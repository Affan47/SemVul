static int qrtr_tun_send(struct qrtr_endpoint *ep, struct sk_buff *skb)
{
	struct qrtr_tun *tun = container_of(ep, struct qrtr_tun, ep);

	skb_queue_tail(&tun->queue, skb);


	wake_up_interruptible(&tun->readq);

	return 0;
}
