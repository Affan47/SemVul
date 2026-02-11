nm_netlink_iface_to_index (const char *iface)
{
	NMNetlinkMonitor *self;
	NMNetlinkMonitorPrivate *priv;
	int idx;

	g_return_val_if_fail (iface != NULL, -1);

	self = nm_netlink_monitor_get ();
	priv = NM_NETLINK_MONITOR_GET_PRIVATE (self);

	nl_cache_refill (priv->nlh_sync, priv->link_cache);
	idx = rtnl_link_name2i (priv->link_cache, iface);
	g_object_unref (self);

	return idx;
}
