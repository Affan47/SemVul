i40e_set_channels(struct net_device *dev,
			      struct ethtool_channels *ch)
{
	struct i40e_netdev_priv *np = netdev_priv(dev);
	unsigned int count = ch->combined_count;
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	int new_count;


	if (vsi->type != I40E_VSI_MAIN)
		return -EINVAL;


	if (!count || ch->rx_count || ch->tx_count)
		return -EINVAL;


	if (ch->other_count != ((pf->flags & I40E_FLAG_FD_SB_ENABLED) ? 1 : 0))
		return -EINVAL;


	if (count > i40e_max_channels(vsi))
		return -EINVAL;


	new_count = i40e_reconfig_rss_queues(pf, count);
	if (new_count > 0)
		return 0;
	else
		return -EINVAL;
}
