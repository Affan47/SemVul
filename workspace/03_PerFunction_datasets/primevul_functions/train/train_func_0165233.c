void __qdisc_run(struct net_device *dev)
{
	unsigned long start_time = jiffies;

	while (qdisc_restart(dev)) {
		if (netif_queue_stopped(dev))
			break;


		if (need_resched() || jiffies != start_time) {
			netif_schedule(dev);
			break;
		}
	}

	clear_bit(__LINK_STATE_QDISC_RUNNING, &dev->state);
}
