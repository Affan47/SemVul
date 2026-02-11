mlx4_en_do_set_rx_mode(struct work_struct *work)
{
	struct mlx4_en_priv *priv = container_of(work, struct mlx4_en_priv,
						 rx_mode_task);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct net_device *dev = priv->dev;

	mutex_lock(&mdev->state_lock);
	if (!mdev->device_up) {
		en_dbg(HW, priv, "Card is not up, ignoring rx mode change.\n");
		goto out;
	}
	if (!priv->port_up) {
		en_dbg(HW, priv, "Port is down, ignoring rx mode change.\n");
		goto out;
	}

	if (!netif_carrier_ok(dev)) {
		if (!mlx4_en_QUERY_PORT(mdev, priv->port)) {
			if (priv->port_state.link_state) {
				priv->last_link_state = MLX4_DEV_EVENT_PORT_UP;
				netif_carrier_on(dev);
				en_dbg(LINK, priv, "Link Up\n");
			}
		}
	}

	if (dev->priv_flags & IFF_UNICAST_FLT)
		mlx4_en_do_uc_filter(priv, dev, mdev);


	if ((dev->flags & IFF_PROMISC) ||
	    (priv->flags & MLX4_EN_FLAG_FORCE_PROMISC)) {
		mlx4_en_set_promisc_mode(priv, mdev);
		goto out;
	}


	if (priv->flags & MLX4_EN_FLAG_PROMISC)
		mlx4_en_clear_promisc_mode(priv, mdev);

	mlx4_en_do_multicast(priv, dev, mdev);
out:
	mutex_unlock(&mdev->state_lock);
}
