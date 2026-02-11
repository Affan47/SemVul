ixgbe_release_swfw_sync_X550em(struct ixgbe_hw *hw, u32 mask)
{
	if (mask & IXGBE_GSSR_I2C_MASK)
		ixgbe_set_mux(hw, 0);

	ixgbe_release_swfw_sync_X540(hw, mask);
}
