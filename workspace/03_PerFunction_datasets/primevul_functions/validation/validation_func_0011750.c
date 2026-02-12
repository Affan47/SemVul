void mark_rect_as_modified(int x1, int y1, int x2, int y2, int force) {

	if (damage_time != 0) {


		int debug = 0;
		if (time(NULL) > damage_time + damage_delay) {
			if (! quiet) {
				rfbLog("damaging turned off.\n");
			}
			damage_time = 0;
			damage_delay = 0;
		} else {
			if (debug) {
				rfbLog("damaging viewer fb by not marking "
				    "rect: %d,%d,%d,%d\n", x1, y1, x2, y2);
			}
			return;
		}
	}


	if (rfb_fb == main_fb || force) {
		mark_wrapper(x1, y1, x2, y2);
		return;
	}

	if (cmap8to24) {
		bpp8to24(x1, y1, x2, y2);
	}

	if (scaling) {
		scale_and_mark_rect(x1, y1, x2, y2, 1);
	} else {
		mark_wrapper(x1, y1, x2, y2);
	}
}
