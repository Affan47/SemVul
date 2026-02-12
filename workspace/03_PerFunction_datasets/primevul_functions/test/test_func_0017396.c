static void xemaclite_tx_timeout(struct net_device *dev, unsigned int txqueue)
{
	struct net_local *lp = netdev_priv(dev);
	unsigned long flags;

	dev_err(&lp->ndev->dev, "Exceeded transmit timeout of %lu ms\n",
		TX_TIMEOUT * 1000UL / HZ);

	dev->stats.tx_errors++;


	spin_lock_irqsave(&lp->reset_lock, flags);


	netif_stop_queue(dev);

	xemaclite_disable_interrupts(lp);
	xemaclite_enable_interrupts(lp);

	if (lp->deferred_skb) {
		dev_kfree_skb(lp->deferred_skb);
		lp->deferred_skb = NULL;
		dev->stats.tx_errors++;
	}


	netif_trans_update(dev);


	netif_wake_queue(dev);
	spin_unlock_irqrestore(&lp->reset_lock, flags);
}
