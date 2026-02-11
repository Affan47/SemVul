nv_get_strings(struct net_device *dev, u32 stringset, u8 *buffer)
{
	switch (stringset) {
	case ETH_SS_STATS:
		memcpy(buffer, &nv_estats_str, nv_get_sset_count(dev, ETH_SS_STATS)*sizeof(struct nv_ethtool_str));
		break;
	case ETH_SS_TEST:
		memcpy(buffer, &nv_etests_str, nv_get_sset_count(dev, ETH_SS_TEST)*sizeof(struct nv_ethtool_str));
		break;
	}
}
