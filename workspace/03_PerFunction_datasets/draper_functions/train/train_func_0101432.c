get_stlforce_mlow_tile_info(int tile_index)
{
	int tileno,colour;

	tileno = stlforce_mlow_videoram[tile_index] & 0x0fff;
	colour = stlforce_mlow_videoram[tile_index] & 0xe000;
	colour = colour >> 13;
	colour += 8;
	tileno += 0x1000;

	SET_TILE_INFO(0,tileno,colour,0)
}
