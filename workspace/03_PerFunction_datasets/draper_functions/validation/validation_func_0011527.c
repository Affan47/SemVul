mlx4_en_filter_rfs(struct net_device *net_dev, const struct sk_buff *skb,
		   u16 rxq_index, u32 flow_id)
{
	struct mlx4_en_priv *priv = netdev_priv(net_dev);
	struct mlx4_en_filter *filter;
	const struct iphdr *ip;
	const __be16 *ports;
	u8 ip_proto;
	__be32 src_ip;
	__be32 dst_ip;
	__be16 src_port;
	__be16 dst_port;
	int nhoff = skb_network_offset(skb);
	int ret = 0;

	if (skb->protocol != htons(ETH_P_IP))
		return -EPROTONOSUPPORT;

	ip = (const struct iphdr *)(skb->data + nhoff);
	if (ip_is_fragment(ip))
		return -EPROTONOSUPPORT;

	if ((ip->protocol != IPPROTO_TCP) && (ip->protocol != IPPROTO_UDP))
		return -EPROTONOSUPPORT;
	ports = (const __be16 *)(skb->data + nhoff + 4 * ip->ihl);

	ip_proto = ip->protocol;
	src_ip = ip->saddr;
	dst_ip = ip->daddr;
	src_port = ports[0];
	dst_port = ports[1];

	spin_lock_bh(&priv->filters_lock);
	filter = mlx4_en_filter_find(priv, src_ip, dst_ip, ip_proto,
				     src_port, dst_port);
	if (filter) {
		if (filter->rxq_index == rxq_index)
			goto out;

		filter->rxq_index = rxq_index;
	} else {
		filter = mlx4_en_filter_alloc(priv, rxq_index,
					      src_ip, dst_ip, ip_proto,
					      src_port, dst_port, flow_id);
		if (!filter) {
			ret = -ENOMEM;
			goto err;
		}
	}

	queue_work(priv->mdev->workqueue, &filter->work);

out:
	ret = filter->id;
err:
	spin_unlock_bh(&priv->filters_lock);

	return ret;
}
