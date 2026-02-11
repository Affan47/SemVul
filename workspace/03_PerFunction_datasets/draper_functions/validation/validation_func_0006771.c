cfhsi_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct cfhsi *cfhsi = NULL;
	int start_xfer = 0;
	int timer_active;
	int prio;

	if (!dev)
		return -EINVAL;

	cfhsi = netdev_priv(dev);

	switch (skb->priority) {
	case TC_PRIO_BESTEFFORT:
	case TC_PRIO_FILLER:
	case TC_PRIO_BULK:
		prio = CFHSI_PRIO_BEBK;
		break;
	case TC_PRIO_INTERACTIVE_BULK:
		prio = CFHSI_PRIO_VI;
		break;
	case TC_PRIO_INTERACTIVE:
		prio = CFHSI_PRIO_VO;
		break;
	case TC_PRIO_CONTROL:
	default:
		prio = CFHSI_PRIO_CTL;
		break;
	}

	spin_lock_bh(&cfhsi->lock);


	cfhsi_update_aggregation_stats(cfhsi, skb, 1);


	skb_queue_tail(&cfhsi->qhead[prio], skb);


	if (WARN_ON(test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))) {
		spin_unlock_bh(&cfhsi->lock);
		cfhsi_abort_tx(cfhsi);
		return -EINVAL;
	}


	if (!cfhsi->flow_off_sent &&
		cfhsi_tx_queue_len(cfhsi) > cfhsi->cfg.q_high_mark &&
		cfhsi->cfdev.flowctrl) {
		cfhsi->flow_off_sent = 1;
		cfhsi->cfdev.flowctrl(cfhsi->ndev, OFF);
	}

	if (cfhsi->tx_state == CFHSI_TX_STATE_IDLE) {
		cfhsi->tx_state = CFHSI_TX_STATE_XFER;
		start_xfer = 1;
	}

	if (!start_xfer) {

		bool aggregate_ready =
			cfhsi_can_send_aggregate(cfhsi) &&
			del_timer(&cfhsi->aggregation_timer) > 0;
		spin_unlock_bh(&cfhsi->lock);
		if (aggregate_ready)
			cfhsi_start_tx(cfhsi);
		return 0;
	}


	timer_active = del_timer_sync(&cfhsi->inactivity_timer);

	spin_unlock_bh(&cfhsi->lock);

	if (timer_active) {
		struct cfhsi_desc *desc = (struct cfhsi_desc *)cfhsi->tx_buf;
		int len;
		int res;


		len = cfhsi_tx_frm(desc, cfhsi);
		WARN_ON(!len);


		res = cfhsi->ops->cfhsi_tx(cfhsi->tx_buf, len, cfhsi->ops);
		if (WARN_ON(res < 0)) {
			netdev_err(cfhsi->ndev, "%s: TX error %d.\n",
				__func__, res);
			cfhsi_abort_tx(cfhsi);
		}
	} else {

		if (!test_and_set_bit(CFHSI_WAKE_UP, &cfhsi->bits))
			queue_work(cfhsi->wq, &cfhsi->wake_up_work);
	}

	return 0;
}
