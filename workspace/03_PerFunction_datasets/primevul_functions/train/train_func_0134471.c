static int hso_net_close(struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);


	netif_stop_queue(net);

	clear_bit(HSO_NET_RUNNING, &odev->flags);

	hso_stop_net_device(odev->parent);


	return 0;
}
