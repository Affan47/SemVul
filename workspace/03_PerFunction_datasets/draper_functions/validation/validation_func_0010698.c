draw(ModeInfo * mi, driftstruct * dp, Drawable d)
{
	Display    *display = MI_DISPLAY(mi);
	GC          gc = MI_GC(mi);
	double      x = dp->x;
	double      y = dp->y;
	int         fixed_x, fixed_y, npix, c, n;

	if (dp->fuse) {
		dp->fuse--;
		return;
	}
	if (!(x > -1.0 && x < 1.0 && y > -1.0 && y < 1.0))
		return;

	fixed_x = (int) ((dp->width / 2) * (x + 1.0));
	fixed_y = (int) ((dp->height / 2) * (y + 1.0));

	if (!dp->rainbow) {

		dp->pts[dp->npoints].x = fixed_x;
		dp->pts[dp->npoints].y = fixed_y;
		dp->npoints++;
		if (dp->npoints == MAXBATCH1) {
			XSetForeground(display, gc, dp->pixcol);
			XDrawPoints(display, d, gc, dp->pts, dp->npoints, CoordModeOrigin);
			dp->npoints = 0;
		}
	} else {

		npix = MI_NPIXELS(mi);
		c = (int) (dp->c * npix);

		if (c < 0)
			c = 0;
		if (c >= npix)
			c = npix - 1;
		n = dp->ncpoints[c];
		dp->cpts[c * MAXBATCH2 + n].x = fixed_x;
		dp->cpts[c * MAXBATCH2 + n].y = fixed_y;
		if (++dp->ncpoints[c] == MAXBATCH2) {
			XSetForeground(display, gc, MI_PIXEL(mi, c));
			XDrawPoints(display, d, gc, &(dp->cpts[c * MAXBATCH2]),
				    dp->ncpoints[c], CoordModeOrigin);
			dp->ncpoints[c] = 0;
		}
	}
}
