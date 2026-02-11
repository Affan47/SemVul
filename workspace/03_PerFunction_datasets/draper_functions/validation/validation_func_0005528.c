canvasUpdateArea(w, x, y, width, height)
CanvasWidget w;
unsigned x, y, width, height;
{
	unsigned cw, ch;

	cw = w->core.width;
	ch = w->core.height;
	if (x >= cw) x = cw-1;
	if (y >= ch) y = ch-1;
	if (x + width > cw) width = cw - x;
	if (y + height > ch) height = ch - y;

	XCopyArea(XtDisplay(w), w->canvas.picture, XtWindow(w),
		  w->canvas.copyGC, x, y, width, height,
		  x, y);
}
