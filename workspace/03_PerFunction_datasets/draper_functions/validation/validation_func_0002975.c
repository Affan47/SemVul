kOnControl(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	int arg = 0;
	gfx_map_mask_t map;
	int xstart, ystart;
	int xlen = 1, ylen = 1;


	if (argc == 2 || argc == 4)
		map = GFX_MASK_CONTROL;
	else {
		arg = 1;
		map = (gfx_map_mask_t) SKPV(0);
	}

	ystart = SKPV(arg+1);
	xstart = SKPV(arg);

	if (argc > 3) {
		ylen = SKPV(arg+3) - ystart;
		xlen = SKPV(arg+2) - xstart;
	}

	return make_reg(0, gfxop_scan_bitmask(s->gfx_state, gfx_rect(xstart, ystart + 10, xlen, ylen), map));
}
