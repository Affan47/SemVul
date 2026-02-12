static inline int handle_dev_cpu_collision(struct sk_buff *skb,
					   struct net_device *dev,
					   struct Qdisc *q)
{
	int ret;

	if (unlikely(dev->xmit_lock_owner == smp_processor_id())) {


		kfree_skb(skb);
		if (net_ratelimit())
			printk(KERN_WARNING "Dead loop on netdevice %s, "
			       "fix it urgently!\n", dev->name);
		ret = qdisc_qlen(q);
	} else {


		__get_cpu_var(netdev_rx_stat).cpu_collision++;
		ret = dev_requeue_skb(skb, dev, q);
	}

	return ret;
}
