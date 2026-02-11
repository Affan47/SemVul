clipped(int idx) {
	int ic;
	sraRegionPtr r0, r1, r2;
	int x1, y1, w1, h1;
	Window win;
	int clip = 0;

	if (idx < 0) {
		return 0;
	}
	r0 = sraRgnCreateRect(0, 0, dpy_x, dpy_y);

	x1 = cache_list[idx].x;
	y1 = cache_list[idx].y;
	w1 = cache_list[idx].width;
	h1 = cache_list[idx].height;

	win = cache_list[idx].win;

	r1 = sraRgnCreateRect(x1, y1, x1+w1, y1+h1);
	sraRgnAnd(r1, r0);

	for (ic = old_stack_n - 1; ic >= 0; ic--) {
		int xc, yc, wc, hc, idx2;

		if (old_stack[ic] == win) {
			break;
		}
		if (old_stack_mapped[ic] == 0) {
			continue;
		}
		idx2 = lookup_old_stack_index(ic);
		if (idx2 < 0) {
			continue;
		}
		if (cache_list[idx2].win == win) {
			break;
		}
		if (cache_list[idx2].map_state != IsViewable) {
			continue;
		}
		xc = cache_list[idx2].x;
		yc = cache_list[idx2].y;
		wc = cache_list[idx2].width;
		hc = cache_list[idx2].height;

		r2 = sraRgnCreateRect(xc, yc, xc+wc, yc+hc);
		sraRgnAnd(r2, r0);
		if (sraRgnAnd(r2, r1)) {
if (0) fprintf(stderr, "clip[0x%lx]: 0x%lx, %d/%d\n", win, cache_list[idx2].win, ic, idx2);
			clip = 1;
		}
		sraRgnDestroy(r2);
		if (clip) {
			break;
		}
	}
	sraRgnDestroy(r0);
	sraRgnDestroy(r1);
if (0) fprintf(stderr, "clip[0x%lx]: %s\n", win, clip ? "clipped" : "no-clipped");
	return clip;
}
