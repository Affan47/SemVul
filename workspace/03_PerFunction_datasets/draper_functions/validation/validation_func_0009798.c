DrawRuler(plot_struct * plot)
{
    if (plot->ruler_on) {
	int x = X(plot->ruler_x);
	int y = Y(plot->ruler_y);
	if (!gc_xor) {

	    GetGCXor(plot, &gc_xor);
	}

	XDrawLine(dpy, plot->window, gc_xor, x, 0, x, GRAPH_HEIGHT(plot));

	XDrawLine(dpy, plot->window, gc_xor, 0, y, plot->width, y);
    }
}
