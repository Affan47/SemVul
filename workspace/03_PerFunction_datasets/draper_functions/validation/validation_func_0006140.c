eel_canvas_w2c_d (EelCanvas *canvas, double wx, double wy, double *cx, double *cy)
{
	double zoom;

	g_return_if_fail (EEL_IS_CANVAS (canvas));

	zoom = canvas->pixels_per_unit;

	if (cx)
		*cx = (wx - canvas->scroll_x1)*zoom + canvas->zoom_xofs;
	if (cy)
		*cy = (wy - canvas->scroll_y1)*zoom + canvas->zoom_yofs;
}
