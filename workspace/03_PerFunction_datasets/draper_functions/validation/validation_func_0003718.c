move_timeout_handler(gpointer data)
{
	PanelWidget   *panel = data;

	g_return_val_if_fail(PANEL_IS_WIDGET(data),FALSE);

	if(been_moved &&
	   panel->currently_dragged_applet) {
		panel_widget_applet_move_to_cursor(panel);
		been_moved = FALSE;
		return TRUE;
	}
	been_moved = FALSE;

	if(panel->currently_dragged_applet && repeat_if_outside) {
		GtkWidget       *widget;
		GtkAllocation   allocation;
		GdkDevice       *device;
		int             x,y;
		int             w,h;

		widget = panel->currently_dragged_applet->applet;

		device = gdk_device_manager_get_client_pointer (gdk_display_get_device_manager (gtk_widget_get_display (widget)));
		gdk_window_get_device_position(gtk_widget_get_window (widget), device, &x, &y, NULL);

		gtk_widget_get_allocation (widget, &allocation);
		w = allocation.width;
		h = allocation.height;


		if(!(x>=0 && x<=w && y>=0 && y<=h))
			return TRUE;
	}

	moving_timeout = 0;

	return FALSE;
}
