void dev_deactivate(struct net_device *dev)
{
	struct Qdisc *qdisc;
	struct sk_buff *skb;
	int running;

	spin_lock_bh(&dev->queue_lock);
	qdisc = dev->qdisc;
	dev->qdisc = &noop_qdisc;

	qdisc_reset(qdisc);

	skb = dev->gso_skb;
	dev->gso_skb = NULL;
	spin_unlock_bh(&dev->queue_lock);

	kfree_skb(skb);

	dev_watchdog_down(dev);


	synchronize_rcu();


	do {
		while (test_bit(__LINK_STATE_QDISC_RUNNING, &dev->state))
			yield();


		spin_lock_bh(&dev->queue_lock);
		running = test_bit(__LINK_STATE_QDISC_RUNNING, &dev->state);
		spin_unlock_bh(&dev->queue_lock);


	} while (WARN_ON_ONCE(running));
}
