callbacks_drawingarea_expose_event (GtkWidget *widget, GdkEventExpose *event)
{
	if (screenRenderInfo.renderType <= GERBV_RENDER_TYPE_GDK_XOR) {
		GdkPixmap *new_pixmap;
		GdkGC *gc = gdk_gc_new(widget->window);


		new_pixmap = gdk_pixmap_new(widget->window,
					widget->allocation.width,
					widget->allocation.height,
					-1);

		gdk_gc_set_foreground(gc, &mainProject->background);

		gdk_draw_rectangle(new_pixmap, gc, TRUE,
			       event->area.x, event->area.y,
			       event->area.width, event->area.height);


		if (screen.pixmap != NULL) {
		gdk_draw_pixmap(new_pixmap,
				widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
				screen.pixmap,
				event->area.x - screen.off_x,
				event->area.y - screen.off_y,
				event->area.x, event->area.y,
				event->area.width, event->area.height);
		}


		gdk_draw_pixmap(widget->window,
			    widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			    new_pixmap,
			    event->area.x, event->area.y,
			    event->area.x, event->area.y,
			    event->area.width, event->area.height);

		gdk_pixmap_unref(new_pixmap);
		gdk_gc_unref(gc);


		if (screen.state == IN_ZOOM_OUTLINE) {
			render_draw_zoom_outline(screen.centered_outline_zoom);
		}
		else if (screen.state == IN_MEASURE) {
			render_draw_measure_distance();
		}
		if (screen.tool == MEASURE && screen.state != IN_MEASURE) {
			render_toggle_measure_line();
		}

		return FALSE;
	}

	cairo_t *cr;
	int width, height;
	int x_off=0, y_off=0;
	GdkDrawable *drawable = widget->window;

	if (GDK_IS_WINDOW(widget->window)) {

		GdkWindow *window = GDK_WINDOW(widget->window);
	      gdk_window_get_internal_paint_info (window,
	                                          &drawable, &x_off, &y_off);
	}
	gdk_drawable_get_size (drawable, &width, &height);

#if defined(WIN32) || defined(QUARTZ)

	cr = gdk_cairo_create (GDK_WINDOW(widget->window));
#else
	cairo_surface_t *buffert;

	GdkVisual *visual = gdk_drawable_get_visual (drawable);
	buffert = (gpointer) cairo_xlib_surface_create (GDK_DRAWABLE_XDISPLAY (drawable),
	                                          GDK_DRAWABLE_XID (drawable),
	                                          GDK_VISUAL_XVISUAL (visual),
	                                          event->area.width, event->area.height);
	cr = cairo_create (buffert);
#endif
	cairo_translate (cr, -event->area.x + screen.off_x, -event->area.y + screen.off_y);
	render_project_to_cairo_target (cr);
	cairo_destroy (cr);
#if !defined(WIN32) && !defined(QUARTZ)
	cairo_surface_destroy (buffert);
#endif

	if (screen.tool == MEASURE)
		render_toggle_measure_line();
	return FALSE;
}
