get_alpha_tile_info(int tile_index)
{
	UINT16 data = atarigen_alpha32[tile_index / 2] >> (16 * (~tile_index & 1));
	int code = data & 0xfff;
	int color = (data >> 12) & 0x0f;
	SET_TILE_INFO(1, code, color, 0);
}
