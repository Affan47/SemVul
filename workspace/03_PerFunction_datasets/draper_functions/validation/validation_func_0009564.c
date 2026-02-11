qlcnic_83xx_set_led(struct net_device *netdev,
			 enum ethtool_phys_id_state state)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int err = -EIO, active = 1;

	if (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) {
		netdev_warn(netdev,
			    "LED test is not supported in non-privileged mode\n");
		return -EOPNOTSUPP;
	}

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		if (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
			return -EBUSY;

		if (test_bit(__QLCNIC_RESETTING, &adapter->state))
			break;

		err = qlcnic_83xx_config_led(adapter, active, 0);
		if (err)
			netdev_err(netdev, "Failed to set LED blink state\n");
		break;
	case ETHTOOL_ID_INACTIVE:
		active = 0;

		if (test_bit(__QLCNIC_RESETTING, &adapter->state))
			break;

		err = qlcnic_83xx_config_led(adapter, active, 0);
		if (err)
			netdev_err(netdev, "Failed to reset LED blink state\n");
		break;

	default:
		return -EINVAL;
	}

	if (!active || err)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	return err;
}
