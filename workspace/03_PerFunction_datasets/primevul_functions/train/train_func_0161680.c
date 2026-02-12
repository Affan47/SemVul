static u16 bond_select_queue(struct net_device *dev, struct sk_buff *skb,
			     struct net_device *sb_dev)
{


	u16 txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;


	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb_get_queue_mapping(skb);

	if (unlikely(txq >= dev->real_num_tx_queues)) {
		do {
			txq -= dev->real_num_tx_queues;
		} while (txq >= dev->real_num_tx_queues);
	}
	return txq;
}
