static int tun_net_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	DBG(KERN_INFO "%s: tun_net_xmit %d\n", tun->dev->name, skb->len);


	if (!tun->tfile)
		goto drop;


	if (!check_filter(&tun->txflt, skb))
		goto drop;

	if (skb_queue_len(&tun->readq) >= dev->tx_queue_len) {
		if (!(tun->flags & TUN_ONE_QUEUE)) {


			netif_stop_queue(dev);


			dev->stats.tx_fifo_errors++;
		} else {


			goto drop;
		}
	}


	skb_queue_tail(&tun->readq, skb);
	dev->trans_start = jiffies;


	if (tun->flags & TUN_FASYNC)
		kill_fasync(&tun->fasync, SIGIO, POLL_IN);
	wake_up_interruptible(&tun->socket.wait);
	return 0;

drop:
	dev->stats.tx_dropped++;
	kfree_skb(skb);
	return 0;
}
