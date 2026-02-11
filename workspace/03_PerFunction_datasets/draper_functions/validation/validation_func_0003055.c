ixgbe_fc_enable_82598(struct ixgbe_hw *hw)
{
	u32 fctrl_reg;
	u32 rmcs_reg;
	u32 reg;
	u32 fcrtl, fcrth;
	u32 link_speed = 0;
	int i;
	bool link_up;


	if (!hw->fc.pause_time)
		return IXGBE_ERR_INVALID_LINK_SETTINGS;


	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		if ((hw->fc.current_mode & ixgbe_fc_tx_pause) &&
		    hw->fc.high_water[i]) {
			if (!hw->fc.low_water[i] ||
			    hw->fc.low_water[i] >= hw->fc.high_water[i]) {
				hw_dbg(hw, "Invalid water mark configuration\n");
				return IXGBE_ERR_INVALID_LINK_SETTINGS;
			}
		}
	}


	hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
	if (link_up && link_speed == IXGBE_LINK_SPEED_1GB_FULL) {
		switch (hw->fc.requested_mode) {
		case ixgbe_fc_full:
			hw->fc.requested_mode = ixgbe_fc_tx_pause;
			break;
		case ixgbe_fc_rx_pause:
			hw->fc.requested_mode = ixgbe_fc_none;
			break;
		default:

			break;
		}
	}


	ixgbe_fc_autoneg(hw);


	fctrl_reg = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	fctrl_reg &= ~(IXGBE_FCTRL_RFCE | IXGBE_FCTRL_RPFCE);

	rmcs_reg = IXGBE_READ_REG(hw, IXGBE_RMCS);
	rmcs_reg &= ~(IXGBE_RMCS_TFCE_PRIORITY | IXGBE_RMCS_TFCE_802_3X);


	switch (hw->fc.current_mode) {
	case ixgbe_fc_none:


		break;
	case ixgbe_fc_rx_pause:


		fctrl_reg |= IXGBE_FCTRL_RFCE;
		break;
	case ixgbe_fc_tx_pause:


		rmcs_reg |= IXGBE_RMCS_TFCE_802_3X;
		break;
	case ixgbe_fc_full:

		fctrl_reg |= IXGBE_FCTRL_RFCE;
		rmcs_reg |= IXGBE_RMCS_TFCE_802_3X;
		break;
	default:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		return IXGBE_ERR_CONFIG;
	}


	fctrl_reg |= IXGBE_FCTRL_DPF;
	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl_reg);
	IXGBE_WRITE_REG(hw, IXGBE_RMCS, rmcs_reg);


	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		if ((hw->fc.current_mode & ixgbe_fc_tx_pause) &&
		    hw->fc.high_water[i]) {
			fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
			fcrth = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), fcrtl);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), fcrth);
		} else {
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), 0);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), 0);
		}

	}


	reg = hw->fc.pause_time * 0x00010001;
	for (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);


	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.pause_time / 2);

	return 0;
}
