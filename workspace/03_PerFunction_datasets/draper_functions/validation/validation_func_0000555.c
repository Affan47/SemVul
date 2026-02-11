shutdown_levelmeter(void)
{
	prefs_set_bool(ap_prefs, "levelmeter", "active", levelmeter_running());

	stop_levelmeter();
	if (disp) {
					gdk_pixmap_unref(disp);
	}
	if (draw_pixmap) {
					gdk_pixmap_unref(draw_pixmap);
	}
	if (area) {
					gtk_widget_destroy(area);
					area = NULL;
	}
	if (gc) {
					gdk_gc_destroy(gc);
					gc = NULL;
	}
	if (scope_win) {
					gtk_widget_destroy(scope_win);
					scope_win = NULL;
	}
}
