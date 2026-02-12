static i40e_status i40e_force_link_state(struct i40e_pf *pf, bool is_up)
{
	struct i40e_aq_get_phy_abilities_resp abilities;
	struct i40e_aq_set_phy_config config = {0};
	struct i40e_hw *hw = &pf->hw;
	i40e_status err;
	u64 mask;
	u8 speed;


	err = i40e_aq_get_phy_capabilities(hw, false, true, &abilities,
					   NULL);
	if (err) {
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		return err;
	}
	speed = abilities.link_speed;


	err = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					   NULL);
	if (err) {
		dev_err(&pf->pdev->dev,
			"failed to get phy cap., ret =  %s last_status =  %s\n",
			i40e_stat_str(hw, err),
			i40e_aq_str(hw, hw->aq.asq_last_status));
		return err;
	}


	if (is_up && abilities.phy_type != 0 && abilities.link_speed != 0)
		return I40E_SUCCESS;


	mask = I40E_PHY_TYPES_BITMASK;
	config.phy_type = is_up ? cpu_to_le32((u32)(mask & 0xffffffff)) : 0;
	config.phy_type_ext = is_up ? (u8)((mask >> 32) & 0xff) : 0;

	config.abilities = abilities.abilities;
	if (abilities.link_speed != 0)
		config.link_speed = abilities.link_speed;
	else
		config.link_speed = speed;
	config.eee_capability = abilities.eee_capability;
	config.eeer = abilities.eeer_val;
	config.low_power_ctrl = abilities.d3_lpan;
	config.fec_config = abilities.fec_cfg_curr_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;
	err = i40e_aq_set_phy_config(hw, &config, NULL);

	if (err) {
		dev_err(&pf->pdev->dev,
			"set phy config ret =  %s last_status =  %s\n",
			i40e_stat_str(&pf->hw, err),
			i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		return err;
	}


	err = i40e_update_link_info(hw);
	if (err) {


		msleep(1000);
		i40e_update_link_info(hw);
	}

	i40e_aq_set_link_restart_an(hw, true, NULL);

	return I40E_SUCCESS;
}
