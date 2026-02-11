drawing_area_motion_event_cb (GtkWidget * widget, GdkEventMotion * event, gpointer user_data)
{
	if (gi_dragging) {
		gi_x_drag = event->x / prefs.tile_size;
		gi_y_drag = event->y / prefs.tile_size;
		gi_gem_dragged = -1;
	}

	return FALSE;
}
