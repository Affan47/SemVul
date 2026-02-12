u32 ethtool_op_get_flags(struct net_device *dev)
{


	return dev->features & flags_dup_features;
}
