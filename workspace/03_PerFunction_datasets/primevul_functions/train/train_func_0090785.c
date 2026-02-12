static int get_lower_vlan_dev_tc(struct net_device *dev,
				 struct netdev_nested_priv *priv)
{
	struct iboe_prio_tc_map *map = (struct iboe_prio_tc_map *)priv->data;

	if (is_vlan_dev(dev))
		map->output_tc = get_vlan_ndev_tc(dev, map->input_prio);
	else if (dev->num_tc)
		map->output_tc = netdev_get_prio_tc_map(dev, map->input_prio);
	else
		map->output_tc = 0;


	map->found = true;
	return 1;
}
