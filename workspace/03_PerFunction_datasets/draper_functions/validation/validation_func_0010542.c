i40e_read_nvm_word_srctl(struct i40e_hw *hw, u16 offset,
					    u16 *data)
{
	i40e_status ret_code = I40E_ERR_TIMEOUT;
	u32 sr_reg;

	if (offset >= hw->nvm.sr_size) {
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: offset %d beyond Shadow RAM limit %d\n",
			   offset, hw->nvm.sr_size);
		ret_code = I40E_ERR_PARAM;
		goto read_nvm_exit;
	}


	ret_code = i40e_poll_sr_srctl_done_bit(hw);
	if (!ret_code) {

		sr_reg = ((u32)offset << I40E_GLNVM_SRCTL_ADDR_SHIFT) |
			 BIT(I40E_GLNVM_SRCTL_START_SHIFT);
		wr32(hw, I40E_GLNVM_SRCTL, sr_reg);


		ret_code = i40e_poll_sr_srctl_done_bit(hw);
		if (!ret_code) {
			sr_reg = rd32(hw, I40E_GLNVM_SRDATA);
			*data = (u16)((sr_reg &
				       I40E_GLNVM_SRDATA_RDDATA_MASK)
				    >> I40E_GLNVM_SRDATA_RDDATA_SHIFT);
		}
	}
	if (ret_code)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: Couldn't access Shadow RAM address: 0x%x\n",
			   offset);

read_nvm_exit:
	return ret_code;
}
