p_xi(XImage *xi, Visual *visual, int win_depth, int *w) {
	RAWFB_RET(NULL)

#if NO_X11
	if (!xi || !visual || !win_depth || !w) {}
	return NULL;
#else
	if (xi == NULL || *w < dpy_x) {
		char *d;
		if (xi) {
			XDestroyImage(xi);
		}
		if (win_depth != 24) {
			if (win_depth > 8) {
				d = (char *) malloc(dpy_x * 2);
			} else {
				d = (char *) malloc(dpy_x * 1);
			}
		} else {
			d = (char *) malloc(dpy_x * 4);
		}
		*w = dpy_x;
		xi = XCreateImage(dpy, visual, win_depth, ZPixmap, 0, d,
		    dpy_x, 1, 8, 0);
	}
	return xi;
#endif
}
