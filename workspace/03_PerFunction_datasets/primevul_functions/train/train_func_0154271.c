static int i40e_validate_and_set_switch_mode(struct i40e_vsi *vsi)
{
	u8 mode;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	int ret;

	ret = i40e_get_capabilities(pf, i40e_aqc_opc_list_dev_capabilities);
	if (ret)
		return -EINVAL;

	if (hw->dev_caps.switch_mode) {


		u32 switch_mode = hw->dev_caps.switch_mode &
				  I40E_SWITCH_MODE_MASK;
		if (switch_mode >= I40E_CLOUD_FILTER_MODE1) {
			if (switch_mode == I40E_CLOUD_FILTER_MODE2)
				return 0;
			dev_err(&pf->pdev->dev,
				"Invalid switch_mode (%d), only non-tunneled mode for cloud filter is supported\n",
				hw->dev_caps.switch_mode);
			return -EINVAL;
		}
	}


	mode = I40E_AQ_SET_SWITCH_BIT7_VALID;


	mode |= I40E_AQ_SET_SWITCH_L4_TYPE_TCP;


	mode |= I40E_AQ_SET_SWITCH_MODE_NON_TUNNEL;


	ret = i40e_aq_set_switch_config(hw, pf->last_sw_conf_flags,
					pf->last_sw_conf_valid_flags,
					mode, NULL);
	if (ret && hw->aq.asq_last_status != I40E_AQ_RC_ESRCH)
		dev_err(&pf->pdev->dev,
			"couldn't set switch config bits, err %s aq_err %s\n",
			i40e_stat_str(hw, ret),
			i40e_aq_str(hw,
				    hw->aq.asq_last_status));

	return ret;
}
