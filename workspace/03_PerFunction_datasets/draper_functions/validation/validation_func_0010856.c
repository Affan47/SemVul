get_tile_info4(int tile_index)
{
	int code;
	code=ssrj_vram4[tile_index<<1]+(ssrj_vram4[(tile_index<<1)+1]<<8);
	SET_TILE_INFO(
		0,
		code&1023,
		((code>>12)&0x3)+12,
	  ((code & 0x8000) ? TILE_FLIPX:0) |( (code & 0x4000) ? TILE_FLIPY:0)	)
}
