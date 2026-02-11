lbs_wait_for_ds_awake(struct lbs_private *priv)
{
	int ret = 0;

	lbs_deb_enter(LBS_DEB_CMD);

	if (priv->is_deep_sleep) {
		if (!wait_event_interruptible_timeout(priv->ds_awake_q,
					!priv->is_deep_sleep, (10 * HZ))) {
			netdev_err(priv->dev, "ds_awake_q: timer expired\n");
			ret = -1;
		}
	}

	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}
