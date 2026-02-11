ixgbe_check_cs4227(struct ixgbe_hw *hw)
{
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	s32 status;
	u16 value;
	u8 retry;

	for (retry = 0; retry < IXGBE_CS4227_RETRIES; retry++) {
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		if (status) {
			hw_err(hw, "semaphore failed with %d\n", status);
			msleep(IXGBE_CS4227_CHECK_DELAY);
			continue;
		}


		status = ixgbe_read_cs4227(hw, IXGBE_CS4227_SCRATCH, &value);
		if (!status && value == IXGBE_CS4227_RESET_COMPLETE)
			goto out;

		if (status || value != IXGBE_CS4227_RESET_PENDING)
			break;


		hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		msleep(IXGBE_CS4227_CHECK_DELAY);
	}

	if (retry == IXGBE_CS4227_RETRIES) {
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		if (status) {
			hw_err(hw, "semaphore failed with %d\n", status);
			return;
		}
	}


	status = ixgbe_reset_cs4227(hw);
	if (status) {
		hw_err(hw, "CS4227 reset failed: %d", status);
		goto out;
	}


	ixgbe_write_cs4227(hw, IXGBE_CS4227_SCRATCH,
			   IXGBE_CS4227_RESET_PENDING);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	usleep_range(10000, 12000);
	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	if (status) {
		hw_err(hw, "semaphore failed with %d", status);
		return;
	}


	status = ixgbe_write_cs4227(hw, IXGBE_CS4227_SCRATCH,
				    IXGBE_CS4227_RESET_COMPLETE);

out:
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	msleep(hw->eeprom.semaphore_delay);
}
