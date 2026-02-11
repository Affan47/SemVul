extend_tile_hint(int x, int y, int tw, int th, hint_t *hint) {
	int w = dpy_x - x;
	int h = dpy_y - y;

	if (w > tw) {
		w = tw;
	}
	if (h > th) {
		h = th;
	}

	if (hint->x > x) {
		hint->w += hint->x - x;
		hint->x = x;
	}
	if (hint->y > y) {
		hint->h += hint->y - y;
		hint->y = y;
	}

	if (hint->x + hint->w < x + w) {
		hint->w = x + w - hint->x;
	}
	if (hint->y + hint->h < y + h) {
		hint->h = y + h - hint->y;
	}
}
