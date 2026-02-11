e1000_get_ethtool_stats(struct net_device *netdev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	int i;
	char *p = NULL;
	const struct e1000_stats *stat = e1000_gstrings_stats;

	e1000_update_stats(adapter);
	for (i = 0; i < E1000_GLOBAL_STATS_LEN; i++) {
		switch (stat->type) {
		case NETDEV_STATS:
			p = (char *)netdev + stat->stat_offset;
			break;
		case E1000_STATS:
			p = (char *)adapter + stat->stat_offset;
			break;
		default:
			WARN_ONCE(1, "Invalid E1000 stat type: %u index %d\n",
				  stat->type, i);
			break;
		}

		if (stat->sizeof_stat == sizeof(u64))
			data[i] = *(u64 *)p;
		else
			data[i] = *(u32 *)p;

		stat++;
	}

}
