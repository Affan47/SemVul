e2_utils_get_abs_pos (GtkWidget *widget, gint *x, gint *y)
{
	if (GTK_WIDGET_TOPLEVEL (widget))
		gdk_window_get_position (widget->window, x, y);
	else
	{
		GdkWindow *window;
		GtkWidget *current = widget;
		while (GTK_WIDGET_NO_WINDOW (current) && (current = gtk_widget_get_parent(current)) != NULL) {}

		if (current != NULL)
			window = current->window;
		else
			window = app.main_window->window;

		gdk_window_get_origin (window, x, y);

		*x += widget->allocation.x;
		*y += widget->allocation.y;
	}
}
