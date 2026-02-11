ganv_canvas_base_paint_rect(GanvCanvasBase* canvas, gint x0, gint y0, gint x1, gint y1)
{
	gint draw_x1, draw_y1;
	gint draw_x2, draw_y2;
	gint draw_width, draw_height;

	g_return_if_fail(!canvas->need_update);

	draw_x1 = MAX(x0, canvas->layout.hadjustment->value - canvas->zoom_xofs);
	draw_y1 = MAX(y0, canvas->layout.vadjustment->value - canvas->zoom_yofs);
	draw_x2 = MIN(draw_x1 + GTK_WIDGET(canvas)->allocation.width, x1);
	draw_y2 = MIN(draw_y1 + GTK_WIDGET(canvas)->allocation.height, y1);

	draw_width  = draw_x2 - draw_x1;
	draw_height = draw_y2 - draw_y1;

	if (( draw_width < 1) || ( draw_height < 1) ) {
		return;
	}

	canvas->redraw_x1 = draw_x1;
	canvas->redraw_y1 = draw_y1;
	canvas->redraw_x2 = draw_x2;
	canvas->redraw_y2 = draw_y2;
	canvas->draw_xofs = draw_x1;
	canvas->draw_yofs = draw_y1;

	cairo_t* cr = gdk_cairo_create(canvas->layout.bin_window);

	double wx, wy;
	ganv_canvas_base_window_to_world(canvas, 0, 0, &wx, &wy);
	cairo_translate(cr, -wx, -wy);

	if (canvas->root->object.flags & GANV_ITEM_VISIBLE) {
		(*GANV_ITEM_GET_CLASS(canvas->root)->draw)(
		    canvas->root, cr,
		    draw_x1, draw_y1,
		    draw_width, draw_height);
	}

	cairo_destroy(cr);
}
