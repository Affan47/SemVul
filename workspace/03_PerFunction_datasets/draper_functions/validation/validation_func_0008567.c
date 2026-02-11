ixgbe_enable_lasi_ext_t_x550em(struct ixgbe_hw *hw)
{
	u32 status;
	u16 reg;
	bool lsc;


	status = ixgbe_get_lasi_ext_t_x550em(hw, &lsc);


	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
				      IXGBE_MDIO_AUTO_NEG_DEV_TYPE, &reg);
	if (status)
		return status;

	reg |= IXGBE_MDIO_PMA_TX_VEN_LASI_INT_EN;

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
				       IXGBE_MDIO_AUTO_NEG_DEV_TYPE, reg);
	if (status)
		return status;


	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				      IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				      &reg);
	if (status)
		return status;

	reg |= (IXGBE_MDIO_GLOBAL_INT_HI_TEMP_EN |
		IXGBE_MDIO_GLOBAL_INT_DEV_FAULT_EN);

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				       IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				       reg);
	if (status)
		return status;


	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				      IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				      &reg);
	if (status)
		return status;

	reg |= (IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN |
		IXGBE_MDIO_GLOBAL_ALARM_1_INT);

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				       IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				       reg);
	if (status)
		return status;


	status = hw->phy.ops.read_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				      IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				      &reg);
	if (status)
		return status;

	reg |= IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN;

	status = hw->phy.ops.write_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				       IXGBE_MDIO_VENDOR_SPECIFIC_1_DEV_TYPE,
				       reg);

	return status;
}
