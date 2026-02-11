e1000_force_mac_fc(struct e1000_hw *hw)
{
	u32 ctrl;


	ctrl = er32(CTRL);


	switch (hw->fc) {
	case E1000_FC_NONE:
		ctrl &= (~(E1000_CTRL_TFCE | E1000_CTRL_RFCE));
		break;
	case E1000_FC_RX_PAUSE:
		ctrl &= (~E1000_CTRL_TFCE);
		ctrl |= E1000_CTRL_RFCE;
		break;
	case E1000_FC_TX_PAUSE:
		ctrl &= (~E1000_CTRL_RFCE);
		ctrl |= E1000_CTRL_TFCE;
		break;
	case E1000_FC_FULL:
		ctrl |= (E1000_CTRL_TFCE | E1000_CTRL_RFCE);
		break;
	default:
		e_dbg("Flow control param set incorrectly\n");
		return -E1000_ERR_CONFIG;
	}


	if (hw->mac_type == e1000_82542_rev2_0)
		ctrl &= (~E1000_CTRL_TFCE);

	ew32(CTRL, ctrl);
	return E1000_SUCCESS;
}
