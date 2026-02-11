cfhsi_abort_tx(struct cfhsi *cfhsi)
{
	struct sk_buff *skb;

	for (;;) {
		spin_lock_bh(&cfhsi->lock);
		skb = cfhsi_dequeue(cfhsi);
		if (!skb)
			break;

		cfhsi->ndev->stats.tx_errors++;
		cfhsi->ndev->stats.tx_dropped++;
		cfhsi_update_aggregation_stats(cfhsi, skb, -1);
		spin_unlock_bh(&cfhsi->lock);
		kfree_skb(skb);
	}
	cfhsi->tx_state = CFHSI_TX_STATE_IDLE;
	if (!test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		mod_timer(&cfhsi->inactivity_timer,
			jiffies + cfhsi->cfg.inactivity_timeout);
	spin_unlock_bh(&cfhsi->lock);
}
