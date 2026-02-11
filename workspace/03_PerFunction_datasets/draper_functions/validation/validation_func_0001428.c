e1000_hash_mc_addr_vf(struct e1000_hw *hw, u8 *mc_addr)
{
	u32 hash_value, hash_mask;
	u8 bit_shift = 0;


	hash_mask = (hw->mac.mta_reg_count * 32) - 1;


	while (hash_mask >> bit_shift != 0xFF)
		bit_shift++;

	hash_value = hash_mask & (((mc_addr[4] >> (8 - bit_shift)) |
				  (((u16)mc_addr[5]) << bit_shift)));

	return hash_value;
}
