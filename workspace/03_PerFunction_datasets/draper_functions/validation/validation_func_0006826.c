e1000_phy_is_accessible_pchlan(struct e1000_hw *hw)
{
	u16 phy_reg = 0;
	u32 phy_id = 0;
	s32 ret_val = 0;
	u16 retry_count;
	u32 mac_reg = 0;

	for (retry_count = 0; retry_count < 2; retry_count++) {
		ret_val = e1e_rphy_locked(hw, MII_PHYSID1, &phy_reg);
		if (ret_val || (phy_reg == 0xFFFF))
			continue;
		phy_id = (u32)(phy_reg << 16);

		ret_val = e1e_rphy_locked(hw, MII_PHYSID2, &phy_reg);
		if (ret_val || (phy_reg == 0xFFFF)) {
			phy_id = 0;
			continue;
		}
		phy_id |= (u32)(phy_reg & PHY_REVISION_MASK);
		break;
	}

	if (hw->phy.id) {
		if (hw->phy.id == phy_id)
			goto out;
	} else if (phy_id) {
		hw->phy.id = phy_id;
		hw->phy.revision = (u32)(phy_reg & ~PHY_REVISION_MASK);
		goto out;
	}


	if (hw->mac.type < e1000_pch_lpt) {
		hw->phy.ops.release(hw);
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		if (!ret_val)
			ret_val = e1000e_get_phy_id(hw);
		hw->phy.ops.acquire(hw);
	}

	if (ret_val)
		return false;
out:
	if ((hw->mac.type == e1000_pch_lpt) || (hw->mac.type == e1000_pch_spt)) {

		if (!(er32(FWSM) & E1000_ICH_FWSM_FW_VALID)) {

			e1e_rphy_locked(hw, CV_SMB_CTRL, &phy_reg);
			phy_reg &= ~CV_SMB_CTRL_FORCE_SMBUS;
			e1e_wphy_locked(hw, CV_SMB_CTRL, phy_reg);


			mac_reg = er32(CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			ew32(CTRL_EXT, mac_reg);
		}
	}

	return true;
}
