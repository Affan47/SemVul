alloc_cc770dev(int sizeof_priv)
{
	struct net_device *dev;
	struct cc770_priv *priv;

	dev = alloc_candev(sizeof(struct cc770_priv) + sizeof_priv,
			   CC770_ECHO_SKB_MAX);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);

	priv->dev = dev;
	priv->can.bittiming_const = &cc770_bittiming_const;
	priv->can.do_set_bittiming = cc770_set_bittiming;
	priv->can.do_set_mode = cc770_set_mode;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;

	memcpy(priv->obj_flags, cc770_obj_flags, sizeof(cc770_obj_flags));

	if (sizeof_priv)
		priv->priv = (void *)priv + sizeof(struct cc770_priv);

	return dev;
}
