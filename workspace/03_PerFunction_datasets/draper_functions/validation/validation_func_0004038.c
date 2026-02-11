get_pf2_tile_info(int tile_index)
{
	data16_t tile=sshangha_pf2_data[tile_index];
	SET_TILE_INFO(1,(tile&0xfff)|sshangha_pf2_bank,(tile>>12)|32,0)
}
