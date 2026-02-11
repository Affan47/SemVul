get_fg_tile_info(int tile_index)
{
	int code = safarir_ram[tile_index];
	int flags = ((tile_index & 0x1d) && (tile_index & 0x1e)) ? 0 : TILE_IGNORE_TRANSPARENCY;

	SET_TILE_INFO(1, code & 0x7f, code >> 7, flags)
}
