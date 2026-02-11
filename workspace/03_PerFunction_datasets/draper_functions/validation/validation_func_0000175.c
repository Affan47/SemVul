deco16_pf34_set_gfxbank(int small, int big)
{
	static int last_big=-1;

	if (last_big!=big) {
		if (pf3_tilemap_16x16)
			tilemap_mark_all_tiles_dirty(pf3_tilemap_16x16);
		if (pf4_tilemap_16x16)
			tilemap_mark_all_tiles_dirty(pf4_tilemap_16x16);
		last_big=big;
	}
	deco16_pf34_16x16_gfx_bank=big;
}
