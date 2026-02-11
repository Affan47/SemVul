e1000_check_for_link_vf(struct e1000_hw *hw)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val = E1000_SUCCESS;
	u32 in_msg = 0;


	if (!mbx->ops.check_for_rst(hw) || !mbx->timeout)
		mac->get_link_status = true;

	if (!mac->get_link_status)
		goto out;


	if (!(er32(STATUS) & E1000_STATUS_LU))
		goto out;


	if (mbx->ops.read(hw, &in_msg, 1))
		goto out;


	if (!(in_msg & E1000_VT_MSGTYPE_CTS)) {

		if (in_msg & E1000_VT_MSGTYPE_NACK)
			ret_val = -E1000_ERR_MAC_INIT;
		goto out;
	}


	if (!mbx->timeout) {
		ret_val = -E1000_ERR_MAC_INIT;
		goto out;
	}


	mac->get_link_status = false;

out:
	return ret_val;
}
