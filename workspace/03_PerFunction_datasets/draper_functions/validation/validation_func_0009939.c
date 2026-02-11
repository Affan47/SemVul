lbs_ret_host_sleep_cfg(struct lbs_private *priv, unsigned long dummy,
			struct cmd_header *resp)
{
	lbs_deb_enter(LBS_DEB_CMD);
	if (priv->is_host_sleep_activated) {
		priv->is_host_sleep_configured = 0;
		if (priv->psstate == PS_STATE_FULL_POWER) {
			priv->is_host_sleep_activated = 0;
			wake_up_interruptible(&priv->host_sleep_q);
		}
	} else {
		priv->is_host_sleep_configured = 1;
	}
	lbs_deb_leave(LBS_DEB_CMD);
	return 0;
}
