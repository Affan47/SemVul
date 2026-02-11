velocity_set_settings(struct net_device *dev,
				 struct ethtool_cmd *cmd)
{
	struct velocity_info *vptr = netdev_priv(dev);
	u32 speed = ethtool_cmd_speed(cmd);
	u32 curr_status;
	u32 new_status = 0;
	int ret = 0;

	curr_status = check_connection_type(vptr->mac_regs);
	curr_status &= (~VELOCITY_LINK_FAIL);

	new_status |= ((cmd->autoneg) ? VELOCITY_AUTONEG_ENABLE : 0);
	new_status |= ((speed == SPEED_1000) ? VELOCITY_SPEED_1000 : 0);
	new_status |= ((speed == SPEED_100) ? VELOCITY_SPEED_100 : 0);
	new_status |= ((speed == SPEED_10) ? VELOCITY_SPEED_10 : 0);
	new_status |= ((cmd->duplex == DUPLEX_FULL) ? VELOCITY_DUPLEX_FULL : 0);

	if ((new_status & VELOCITY_AUTONEG_ENABLE) &&
	    (new_status != (curr_status | VELOCITY_AUTONEG_ENABLE))) {
		ret = -EINVAL;
	} else {
		enum speed_opt spd_dpx;

		if (new_status & VELOCITY_AUTONEG_ENABLE)
			spd_dpx = SPD_DPX_AUTO;
		else if ((new_status & VELOCITY_SPEED_1000) &&
			 (new_status & VELOCITY_DUPLEX_FULL)) {
			spd_dpx = SPD_DPX_1000_FULL;
		} else if (new_status & VELOCITY_SPEED_100)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_100_FULL : SPD_DPX_100_HALF;
		else if (new_status & VELOCITY_SPEED_10)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_10_FULL : SPD_DPX_10_HALF;
		else
			return -EOPNOTSUPP;

		vptr->options.spd_dpx = spd_dpx;

		velocity_set_media_mode(vptr, new_status);
	}

	return ret;
}
