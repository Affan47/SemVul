fill_line (void)
{
	int hs = coord_hw_to_window_x (hsyncstartpos * 2);
	if (hs >= gfxvidinfo.drawbuffer.inwidth || hposblank) {
		hposblank = 3;
		fill_line2 (visible_left_border, gfxvidinfo.drawbuffer.inwidth);
	} else {
		fill_line2 (visible_left_border, hs);
		hposblank = 2;
		fill_line2 (visible_left_border + hs, gfxvidinfo.drawbuffer.inwidth);
	}
}
