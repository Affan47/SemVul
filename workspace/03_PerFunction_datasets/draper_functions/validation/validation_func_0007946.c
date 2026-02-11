niu_get_nfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
		       u32 *rule_locs)
{
	struct niu *np = netdev_priv(dev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXFH:
		ret = niu_get_hash_opts(np, cmd);
		break;
	case ETHTOOL_GRXRINGS:
		cmd->data = np->num_rx_rings;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = tcam_get_valid_entry_cnt(np);
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = niu_get_ethtool_tcam_entry(np, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = niu_get_ethtool_tcam_all(np, cmd, rule_locs);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
